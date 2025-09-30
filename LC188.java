/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/

class Solution {
    public int maxProfit(int k, int[] prices) {
        int n = prices.length;
        int[][][] dp = new int[n + 1][2][k + 1];

        for (int ind = n - 1; ind >= 0; ind--) {
            for (int buy = 0; buy < 2; buy++) {
                for (int cap = 1; cap <= k; cap++) {
                    int profit = 0;
                    if (buy == 1) {
                        int take = -prices[ind] + dp[ind + 1][0][cap];
                        int noTake = dp[ind + 1][1][cap];
                        profit = Math.max(take, noTake);
                    } else {
                        int sell = prices[ind] + dp[ind + 1][1][cap - 1];
                        int noSell = dp[ind + 1][0][cap];
                        profit = Math.max(sell, noSell);
                    }
                    dp[ind][buy][cap] = profit;
                }
            }
        }
        return dp[0][1][k];
    }
}