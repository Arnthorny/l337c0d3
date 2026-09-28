#include <stdio.h>


/**
 * @brief Returns the smaller of two integers.
 *
 * This helper function is used to determine the limiting height of a
 * container formed by two vertical lines. The container's height is
 * constrained by whichever of the two lines is shorter.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The smaller of a and b.
 */
int min(int a, int b) {
    return a < b ? a : b;
}


/**
 * @brief Finds the maximum amount of water that can be contained.
 *
 * The function solves the "Container With Most Water" problem using the
 * two-pointer technique.
 *
 * INTUITION:
 *
 * A container is formed by two vertical lines at positions lP and rP.
 * Its area is:
 *
 *     area = min(height[lP], height[rP]) * (rP - lP)
 *
 * The first pointer starts at the leftmost line and the second pointer
 * starts at the rightmost line. This gives us the maximum possible width.
 *
 * At each step, we calculate the area formed by the two current lines.
 *
 * We then move the pointer corresponding to the shorter line:
 *
 *     if (height[lP] <= height[rP])
 *         move lP to the right
 *     else
 *         move rP to the left
 *
 * WHY MOVE THE SHORTER LINE?
 *
 * The area is limited by the shorter line. If the left line is shorter,
 * moving the right pointer inward would reduce the width while keeping
 * the limiting height unchanged (or potentially making it even smaller).
 * Therefore, such a move cannot produce a better area.
 *
 * Instead, we move the shorter line in the hope of finding a taller line
 * that can increase the limiting height enough to compensate for the
 * reduced width.
 *
 * This allows us to eliminate many possible pairs without checking every
 * combination.
 *
 * The process continues until the two pointers meet.
 *
 * @param height An array containing the heights of the vertical lines.
 * @param heightSize Number of elements in the height array.
 * @return The maximum area of water that can be contained.
 *
 * TIME COMPLEXITY:
 * O(n)
 *
 * The two pointers move toward each other, and each pointer moves at most
 * n times. Therefore, the total number of iterations is linear.
 *
 * SPACE COMPLEXITY:
 * O(1)
 *
 * Only a fixed number of integer variables are used regardless of the
 * size of the input array.
 */
int maxArea(int* height, int heightSize) {
    int i, lP = 0, rP = heightSize - 1, max_val = 0, tmp_area = 0;


    while (lP <= rP)
    {
        tmp_area = min(height[lP], height[rP]) * (rP - lP);
        
        if (height[lP] <= height[rP]) lP++;
        else rP --;

        max_val = max_val > tmp_area ? max_val : tmp_area;
    }
    
    return max_val;       
}


int main(void) {
    int height[] = {1,7,2,5,4,7,3,6};

    int heightSize = 8;

    printf("%d\n", maxArea(height, heightSize));
}