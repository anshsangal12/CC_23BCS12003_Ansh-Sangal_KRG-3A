const express = require('express');
const cors = require('cors');
const { v4: uuidv4 } = require('uuid');

const {
  S3Client,
  PutObjectCommand,
  GetObjectCommand
} = require('@aws-sdk/client-s3');

const { getSignedUrl } = require('@aws-sdk/s3-request-presigner');

const app = express();
app.use(cors());
app.use(express.json());

const PORT = 3000;

// 🔐 CONFIG
const BUCKET_NAME = 'lifecycle-demo-12';
const REGION = 'ap-south-1';

const s3 = new S3Client({
  region: REGION,
  credentials: {
    accessKeyId: process.env.AWS_ACCESS_KEY_ID,
    secretAccessKey: process.env.AWS_SECRET_ACCESS_KEY,
  },
});

// 🧠 In-memory store (replace with DB later)
const files = new Map();


// ✅ 1. GENERATE UPLOAD URL
app.get('/api/generate-upload-url', async (req, res) => {
  try {
    const { fileName, fileType, fileSize } = req.query;

    if (!fileName || !fileType || !fileSize) {
      return res.status(400).json({ success: false, error: 'Missing params' });
    }

    const fileId = uuidv4();
    const key = `uploads/${new Date().toISOString().split('T')[0]}/${fileId}/${fileName}`;

    // 🔥 IMPORTANT: Only sign what you will send
    const command = new PutObjectCommand({
      Bucket: BUCKET_NAME,
      Key: key,
      ContentType: fileType, // MUST match frontend
    });

    const uploadUrl = await getSignedUrl(s3, command, {
      expiresIn: 300, // 5 minutes
    });

    // Save metadata
    files.set(fileId, {
      fileId,
      fileName,
      fileType,
      fileSize,
      key,
      uploadTimestamp: new Date().toISOString(),
      downloadCount: 0,
      status: 'pending',
    });

    res.json({
      success: true,
      uploadUrl,
      fileId,
      fileKey: key,
    });

  } catch (err) {
    console.error(err);
    res.status(500).json({ success: false, error: 'Failed to generate URL' });
  }
});


// ✅ 2. CONFIRM UPLOAD
app.post('/api/confirm-upload', (req, res) => {
  const { fileId } = req.body;

  const file = files.get(fileId);
  if (!file) {
    return res.status(404).json({ success: false, error: 'File not found' });
  }

  file.status = 'active';

  res.json({
    success: true,
    file,
  });
});


// ✅ 3. GENERATE DOWNLOAD URL
app.get('/api/generate-download-url', async (req, res) => {
  try {
    const { fileId } = req.query;

    const file = files.get(fileId);
    if (!file) {
      return res.status(404).json({ success: false, error: 'File not found' });
    }

    const command = new GetObjectCommand({
      Bucket: BUCKET_NAME,
      Key: file.key,
    });

    const downloadUrl = await getSignedUrl(s3, command, {
      expiresIn: 300,
    });

    file.downloadCount++;

    res.json({
      success: true,
      downloadUrl,
      file,
    });

  } catch (err) {
    res.status(500).json({ success: false, error: 'Failed to generate download URL' });
  }
});


// ✅ 4. HISTORY
app.get('/api/history', (req, res) => {
  res.json({
    success: true,
    files: Array.from(files.values()).reverse(),
  });
});


app.listen(PORT, () => {
  console.log(`🚀 Server running on http://localhost:${PORT}`);
});
