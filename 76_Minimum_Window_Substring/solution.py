from collections import defaultdict


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        # Stores the required frequency of each character in t.
        #
        # Example:
        # t = "AABC"
        # t_dict = {"A": 2, "B": 1, "C": 1}
        t_dict = defaultdict(int)

        # Stores the frequency of relevant characters currently
        # inside the sliding window [lP, rP].
        temp_dict = defaultdict(int)

        # lP = left boundary of the sliding window
        # rP = right boundary of the sliding window
        lP, rP = 0, 0

        # Stores:
        #   res_min[0] -> starting index of best window
        #   res_min[1] -> ending index of best window
        #   res_min[2] -> length of best window
        #
        # Initially, no valid window has been found, so its length
        # is set to infinity.
        res_min = [0, 0, float('inf')]

        # Tracks whether at least one valid window has been found.
        found_match = False

        # Build the frequency table for the characters required by t.
        for c in t:
            t_dict[c] += 1

        # Number of distinct characters that must satisfy their
        # required frequencies.
        #
        # Example:
        # t = "AABC"
        # need = 3  -> A, B, and C
        need = len(t_dict)

        # Number of distinct required characters whose required
        # frequencies are currently satisfied inside the window.
        have = 0

        # Expand the sliding window by moving rP from left to right.
        while rP < len(s):

            # Only characters that are actually required by t
            # need to be tracked in temp_dict.
            if t_dict.get(s[rP], 0) != 0:
                temp_dict[s[rP]] += 1

                # A character becomes "satisfied" exactly when its
                # frequency in the current window reaches the
                # frequency required by t.
                if (temp_dict[s[rP]] == t_dict[s[rP]]): have += 1

            # When all required character frequencies are satisfied,
            # the current window is valid.
            #
            # Try to shrink it from the left to find the smallest
            # possible valid window.
            while have == need:
                found_match = True

                # Update the best window if the current one is smaller.
                if min(res_min[2], rP - lP + 1) != res_min[2]:
                    res_min[0], res_min[1], res_min[2] = lP, rP, min(res_min[2], rP - lP + 1)
                
                # Remove s[lP] from the current window.
                #
                # If it is a required character, update its frequency
                # and determine whether removing it caused that
                # character to become unsatisfied.
                if t_dict.get(s[lP], 0) != 0:
                    temp_dict[s[lP]] -= 1

                    # If the current frequency drops below the
                    # required frequency, the window is no longer
                    # valid, so decrement have.
                    if (temp_dict[s[lP]] < t_dict[s[lP]]): have -= 1

                # Shrink the window from the left.
                lP += 1

            # Expand the window to the right.
            rP += 1
        
        # If a valid window was found, return the substring represented
        # by the best [start, end] indices.
        #
        # Otherwise, return an empty string.
        return s[res_min[0] : res_min[1] + 1] if found_match else ""

print(Solution().minWindow("cabwefgewcwaefgcf", "cae"))
