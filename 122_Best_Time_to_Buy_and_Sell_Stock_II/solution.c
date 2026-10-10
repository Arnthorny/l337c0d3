#include <stdio.h>

#include <stdlib.h>

/**
 * Calculates the maximum profit from buying and selling a stock
 * multiple times.
 *
 * This solves the "Best Time to Buy and Sell Stock II" problem,
 * where unlimited transactions are allowed, provided a new stock
 * is not bought until the previous one has been sold.
 *
 * The algorithm observes that every positive increase between
 * consecutive days can be treated as a profitable transaction.
 *
 * For example:
 *
 *     prices = [7, 1, 5, 3, 6, 4]
 *
 *     7 -> 1 : 0 profit
 *     1 -> 5 : +4
 *     5 -> 3 : 0 profit
 *     3 -> 6 : +3
 *     6 -> 4 : 0 profit
 *
 *     total profit = 4 + 3 = 7
 *
 * `prev_price` stores the previous day's price. At each iteration,
 * `tmp_profit` calculates the positive price difference:
 *
 *     tmp_profit = max(prices[i] - prev_price, 0)
 *
 * `prev_price` is then updated to the current price so that the
 * next iteration compares the next pair of consecutive prices.
 *
 * This is equivalent to:
 *
 *     total_max += max(prices[i] - prices[i - 1], 0)
 *
 * The reason this works is that for unlimited transactions, a
 * continuous increase such as:
 *
 *     1 -> 2 -> 3 -> 4
 *
 * produces the same profit whether it is treated as one transaction
 * (buy at 1, sell at 4) or as multiple transactions:
 *
 *     (1 -> 2) + (2 -> 3) + (3 -> 4)
 *
 *     = 1 + 1 + 1
 *     = 3
 *
 * Time Complexity:
 *     O(n), where n is pricesSize.
 *     Each price is processed exactly once.
 *
 * Space Complexity:
 *     O(1).
 *     Only a constant number of variables are used.
 */
int maxProfit(int* prices, int pricesSize) {
    int prev_price = prices[0];
    int i = 0, tmp_profit = 0, total_max = 0;


    for (i = 0; i < pricesSize; i++)
    {
        tmp_profit = prices[i] - prev_price > 0 ? prices[i] - prev_price : 0;
        prev_price = prices[i];

        total_max += tmp_profit;

    }
    return total_max;
}


int main(void) {
    int prices[] = {7,1,5,3,6,4};
    int pricesSize = 6;

    printf("%d\n", maxProfit(prices, pricesSize));
}