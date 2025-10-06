/*
Smallest subarray with sum greater than x

Given a number x and an array of integers arr, find the smallest subarray with sum greater than the given value. If such a subarray do not exist return 0 in that case.

Examples:

Input: x = 51, arr[] = [1, 4, 45, 6, 0, 19]
Output: 3
Explanation: Minimum length subarray is [4, 45, 6]
Input: x = 100, arr[] = [1, 10, 5, 2, 7]
Output: 0
Explanation: No subarray exist
*/


int smallestSubWithSum(int x, vector<int>& arr) {
    int size = arr.size();
    int ans = INT_MAX;
    int sum = 0;

    int left = 0;
    int right = 0;
    
    while (right < arr.size()) {
        sum += arr[right];
        
        while (sum > x && left <= right) {
            sum -= arr[left];
            ans = min(ans, (right - left) + 1);
            left++;
        }
        
        right++;
    }
    
    return ans == INT_MAX ? 0 : ans;
}

int main() {
    vector<int> arr = {2,4,6,3,7,9};
    int min = smallestSubWithSum(15, arr);
    cout << min;
    return 0;
}