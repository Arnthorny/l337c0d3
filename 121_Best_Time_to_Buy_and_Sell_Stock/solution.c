/**
 * @brief Calculates the maximum profit that can be obtained from buying
 *        and selling a stock once.
 *
 * INTUITION:
 * ----------
 * The goal is to find:
 *
 *     maximum(prices[sell] - prices[buy])
 *
 * subject to the condition that the buying day occurs before the
 * selling day.
 *
 * Instead of checking every possible pair of buy and sell days, we
 * maintain the lowest price encountered so far in `mini_price`.
 *
 * For every current price:
 *
 *     1. If the current price is greater than `mini_price`, we can
 *        potentially make a profit by buying at `mini_price` and
 *        selling at the current price.
 *
 *     2. Calculate the potential profit:
 *
 *            prices[i] - mini_price
 *
 *     3. Compare it with the best profit found so far and keep the
 *        larger value in `max_profit`.
 *
 *     4. If the current price is lower than or equal to `mini_price`,
 *        it becomes the new cheapest buying price.
 *
 * The important observation is that when processing a day, we only need
 * to know the cheapest price that occurred before it. We do not need to
 * remember every previous price.
 *
 * EXAMPLE:
 * --------
 *
 *     prices = [7, 1, 5, 3, 6, 4]
 *
 * Processing the array:
 *
 *     price = 7
 *     mini_price = 7
 *
 *     price = 1
 *     mini_price = 1
 *
 *     price = 5
 *     profit = 5 - 1 = 4
 *     max_profit = 4
 *
 *     price = 3
 *     profit = 3 - 1 = 2
 *     max_profit remains 4
 *
 *     price = 6
 *     profit = 6 - 1 = 5
 *     max_profit = 5
 *
 *     price = 4
 *     profit = 4 - 1 = 3
 *     max_profit remains 5
 *
 * Therefore, the maximum profit is 5, obtained by buying at 1 and
 * selling at 6.
 *
 * WHY THIS WORKS:
 * ---------------
 * For every possible selling day, `mini_price` represents the cheapest
 * price at which we could have bought before that day.
 *
 * Therefore:
 *
 *     current price - mini_price
 *
 * is the maximum profit obtainable if we sell on the current day.
 *
 * By keeping the largest such profit in `max_profit`, we obtain the
 * overall maximum profit after one pass through the array.
 *
 * TIME COMPLEXITY:
 * ----------------
 * O(n)
 *
 * The array is traversed exactly once, where n is `pricesSize`.
 *
 * SPACE COMPLEXITY:
 * -----------------
 * O(1)
 *
 * Only a fixed number of variables are used regardless of the size
 * of the input array.
 */
int maxProfit(int* prices, int pricesSize) {
    int mini_price = prices[0];
    int max_profit = 0, i = 0, tmp_profit = 0;

    for (i = 0; i < pricesSize; i++)
    {
        tmp_profit = prices[i] - mini_price;
        max_profit = max_profit > tmp_profit ? max_profit : tmp_profit;

        mini_price = prices[i] < mini_price ? prices[i] : mini_price;
    }
    return max_profit;
    
}
