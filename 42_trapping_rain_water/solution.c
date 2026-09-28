#include <stdio.h>

#define MAX_HEIGHT_LEN 20001

/**
 * @brief Calculates the amount of rainwater that can be trapped between
 *        vertical bars represented by the height array.
 *
 * INTUITION:
 *
 * Water can be trapped at index i if there are taller bars on both the
 * left and right sides of it.
 *
 * The amount of water that can sit above height[i] is determined by the
 * shorter of:
 *
 *     1. The tallest bar to the left (including height[i])
 *     2. The tallest bar to the right (including height[i])
 *
 * Therefore:
 *
 *     water[i] = min(left_max[i], right_max[i]) - height[i]
 *
 * If this value is negative, no water can be stored at that position,
 * so it contributes 0 to the total.
 *
 * This implementation precomputes the required maximum heights:
 *
 *     pref_arr[i] = tallest bar from index 0 through i
 *
 *     suff_arr[i] = tallest bar from index i through heightSize - 1
 *
 * Once these arrays are built, each position can be evaluated in O(1)
 * time using the formula above.
 *
 * The overall approach therefore consists of three passes:
 *
 *     1. Build the prefix maximum array.
 *     2. Build the suffix maximum array.
 *     3. Calculate the trapped water at every position.
 *
 * @param height An array containing the heights of the vertical bars.
 * @param heightSize Number of elements in the height array.
 *
 * @return The total amount of rainwater that can be trapped.
 *
 * TIME COMPLEXITY:
 * O(n)
 *
 * The function makes three linear passes over the input array. Each pass
 * takes O(n), so the total time complexity remains O(n).
 *
 * SPACE COMPLEXITY:
 * O(n)
 *
 * Two additional arrays, pref_arr and suff_arr, are allocated with
 * capacity MAX_HEIGHT_LEN. The amount of information actually used is
 * proportional to heightSize, giving O(n) auxiliary space.
 */
int trap(int* height, int heightSize) {
    int pref_arr[MAX_HEIGHT_LEN], suff_arr[MAX_HEIGHT_LEN], i = 0;
    int curr_tallest = 0, total_water = 0, curr_water = 0;
    int tmp_small_val = 0;

    curr_tallest = height[0];
    for (i = 0; i < heightSize; i++){
        curr_tallest = curr_tallest > height[i] ? curr_tallest : height[i];
        pref_arr[i] = curr_tallest;
    }

    curr_tallest = height[heightSize - 1];
    for (i = heightSize - 1; i >= 0; i--){
        curr_tallest = curr_tallest > height[i] ? curr_tallest : height[i];
        suff_arr[i] = curr_tallest;
    }

    for (i = 0; i < heightSize; i++){
        // if (i == 0 || i == heightSize - 1) continue;
        tmp_small_val = pref_arr[i] < suff_arr[i] ? pref_arr[i] : suff_arr[i];
        curr_water = tmp_small_val - height[i];
        total_water += curr_water > 0 ? curr_water : 0;
    }
    return total_water;
    
}


int main(void) {
    int height[] = {0,1,0,2,1,0,1,3,2,1,2,1};

    int heightSize = 12;

    printf("%d\n", trap(height, heightSize));
}