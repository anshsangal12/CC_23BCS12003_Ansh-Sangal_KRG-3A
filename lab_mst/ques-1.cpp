#include<iostream>
#include<vector>
using namespace std;

int solution(vector<int>& nums){
    int ones = 0, twos = 0;

    for(int i=0; i<nums.size(); i++){
        ones = (ones ^ nums[i]) & ~twos;
        twos = (twos ^ nums[i]) & ~ones;
    }

    return ones;
}

int main(){
    vector<int> nums = {2,2,3,2,3,3,4};
    cout << solution(nums);
}