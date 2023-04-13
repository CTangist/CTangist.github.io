#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void numsSort(vector<int>& nums) {
        if (nums.size() > 1) {
            for (int i=0; i<nums.size()-1; ++i) {
                for (int j=i+1; j<nums.size(); ++j) {
                    if (nums[i] > nums[j]) {
                        int tmp = nums[i];
                        nums[i] = nums[j];
                        nums[j] = tmp;
                    }
                }
            }
        }
    }

    int binarySearch(vector<int>& nums, int start, int end, long long target) {
        if (start == end) {
            if (nums[start] == target) return start;
            else return -1;
        } else {
            int mid = (start + end) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] > target) return binarySearch(nums, start, mid, target);
            else return binarySearch(nums, mid+1, end, target);
        }
        
        return -1;
    }

    vector<vector<int> > twoSum(vector<int>& nums, int start, long long target) {
        vector<vector<int> > twoSumAns;
        if (nums.size() < 2) return twoSumAns;

        int flag = -1e9 - 1;
        for (int i=start; i<nums.size()-1; ++i) {
            while (i<nums.size()-1 && nums[i]==flag) i++;
            if (i >= nums.size()-1) break;
            flag = nums[i];

            int ansIndex = binarySearch(nums, i+1, nums.size()-1, target-nums[i]);
            if (ansIndex != -1) {
                vector<int> cur = {nums[i], nums[ansIndex]};
                twoSumAns.push_back(cur);
            }
        }

        return twoSumAns;
    }

    vector<vector<int> > threeSum(vector<int>& nums, int start, long long target) {
        vector<vector<int> > threeSumAns;
        if (nums.size() < 3) return threeSumAns;

        int flag = -1e9 - 1;
        for (int i=start; i<nums.size()-2; ++i) {
            while (i<nums.size()-2 && nums[i]==flag) i++;
            if (i >= nums.size()-2) break;
            flag = nums[i];

            vector<vector<int> > twoCur = twoSum(nums, i+1, target-nums[i]);
            if (twoCur.size()) {
                for (int j=0; j<twoCur.size(); ++j) {
                    vector<int> cur = {nums[i], twoCur[j][0], twoCur[j][1]};
                    threeSumAns.push_back(cur);
                }
            }
        }

        return threeSumAns;
    }

    vector<vector<int> > fourSum(vector<int>& nums, int target) {
        numsSort(nums);
        vector<vector<int> > fourSumAns;
        if (nums.size() < 4) return fourSumAns;
        int flag = -1e9 - 1;

        for (int i=0; i<nums.size()-3; ++i) {
            while (i<nums.size()-3 && nums[i]==flag) i++;
            if (i >= nums.size()-3) break;
            flag = nums[i];

            vector<vector<int> > threeCur = threeSum(nums, i+1, target-nums[i]);
            if (threeCur.size()) {
                for (int j=0; j<threeCur.size(); ++j) {
                    vector<int> cur = {nums[i], threeCur[j][0], threeCur[j][1], threeCur[j][2]};
                    fourSumAns.push_back(cur);
                }
            }
        }

        return fourSumAns;
    }
};

int main() {
    Solution* so = new Solution();
    vector<int> nums = {2, 2, 2, 2, 2};
    
    vector<vector<int> > ans = so->fourSum(nums, 8);
    for (int i=0; i<ans.size(); ++i) {
        for (int j=0; j<ans[i].size(); ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}