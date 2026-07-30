/*
LeetCode 516: Longest Palindromic Subsequence

Given a string s, return the length of its longest palindromic subsequence. A subsequence is formed by deleting zero or more characters without changing the order of the remaining characters.

Example
Input:  s = "bbbab"
Output: 4

Longest palindromic subsequence: "bbbb"

A subsequence does not need to be contiguous.
*/

/*
Dynamic Programming Approach

Define:

dp[i][j] = length of the longest palindromic subsequence
           inside substring s[i...j]

There are two cases.

Case 1: Characters match

When:
s[i] == s[j]

Both characters can be included in the palindrome:

dp[i][j] = 2 + dp[i + 1][j - 1]

Case 2: Characters do not match

When:
s[i] != s[j]
We must skip either the left character or the right character:

dp[i][j] = max(
    dp[i + 1][j],
    dp[i][j - 1]
)
Base case

Every single character is a palindrome of length 1:

dp[i][i] = 1
*/


#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(const string& s) {
        int n = static_cast<int>(s.size());

        if (n == 0) {
            return 0;
        }

        vector<vector<int>> dp(
            n,
            vector<int>(n, 0)
        );

        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }

       for (int length = 2; length <= n; ++length) {
            for (int left = 0; left + length - 1 < n; ++left) {
                int right = left + length - 1;

                if (s[left] == s[right]) {
                    if (length == 2){ 
                        dp[left][right] = 2;
                    }

                    else {
                        dp[left][right] = 2 + dp[left + 1][right - 1];
                    }
                } else {
                    dp[left][right] = max(dp[left + 1][right], dp[left][right - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};

void runTest(
    const string& input,
    int expected
) {
    Solution solution;
    int actual = solution.longestPalindromeSubseq(input);

    cout << "Input: \"" << input << "\"\n";
    cout << "Expected: " << expected << '\n';
    cout << "Actual: " << actual << '\n';
    cout << (actual == expected ? "PASS" : "FAIL");
    cout << "\n\n";
}

int main() {
    runTest("bbbab", 4);
    runTest("cbbd", 2);
    runTest("a", 1);
    runTest("abcde", 1);
    runTest("racecar", 7);
    runTest("agbdba", 5);
    runTest("aaaa", 4);

    return 0;
}
