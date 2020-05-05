/*31. Next Permutation
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
The replacement must be in-place and use only constant extra memory.
Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1 */


/*Complexity Analysis
Time complexity  : O(n). In worst case, only two scans of the whole array are needed.
Space complexity : O(1). No extra space is used. In place replacements are done.*/

template <typename T>
class Solution
{
	void nexPermutation(std::vector<T> nums)
	{
		int i = nums.size() - 2;
		while (i >= 0 && nums[i + 1] <= nums[i]) {
			i--;
		}
		if (i >= 0) 
		{
			int j = nums.size() - 1;
			while (j >= 0 && nums[j] <= nums[i]) {
				j--;
			}
			swap(nums, i, j);
		}
		reverse(nums, i + 1);
	}

	 void reverse(std::vector<T>& nums, int start) {
		int i = start, j = nums.size() - 1;
		while (i < j) {
			swap(nums, i, j);
			i++;
			j--;
		}
	}

	void swap(std::vector<T>& nums, int i, int j) {
		using std::swap;
		swap(nums[i], nums[j])
	}
};
