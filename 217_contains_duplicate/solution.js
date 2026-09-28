/**
 * @param {number[]} nums
 * @return {boolean}
 */
var containsDuplicate = function(nums) {
  const hashh = new Set()
  
  for (let i = 0; i < nums.length; i++) {
    if(hashh.has(nums[i])) return true
    hashh.add(nums[i])
  }
  return false
};