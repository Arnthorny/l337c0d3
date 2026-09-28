#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int, bool> hashh = {};

        for (size_t i = 0; i < nums.size(); i++)
        {
            if(hashh.count(nums[i])) return true;
            hashh[nums[i]] = true;
        }
        return false;
    }
};