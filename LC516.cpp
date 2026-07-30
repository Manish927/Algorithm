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
