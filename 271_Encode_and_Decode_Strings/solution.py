from typing import List


class Solution:
    def encode(self, strs: List[str]) -> str:
        """Encodes a list of strings into a single string.

        Logic:
        - Prefix each string with its character length followed by `*`.
        - Append the original string immediately after its length prefix.
        - The length prefix allows the decoder to determine exactly where
          each string ends, even if the string itself contains `*`.

        Example:
            ["hello", "world"] -> "5*hello5*world"

        Args:
            strs: List of strings to encode.

        Returns:
            A single encoded string containing all strings.
        """
        coded_str = ""

        for string in strs:
            coded_str += f"{len(string)}*{string}"

        return coded_str

    def decode(self, s: str) -> List[str]:
        """Decodes an encoded string back into a list of strings.

        Logic:
        - Start at the beginning of the encoded string.
        - Find the next `*`, which separates the string length from the
          string itself.
        - Convert the characters before `*` into an integer to get the
          length of the current string.
        - Use that length to extract exactly that many characters after `*`.
        - Add the extracted string to the result.
        - Move the pointer to the end of the extracted string and repeat
          until the entire encoded string has been processed.

        Example:
            "5*hello5*world" -> ["hello", "world"]

        Args:
            s: Encoded string produced by `encode`.

        Returns:
            The original list of strings.
        """
        decoded_strs = []
        prev_str_end = 0

        while prev_str_end < len(s):
            cur_delim_pos = s.find("*", prev_str_end)
            cur_str_len = int(s[prev_str_end:cur_delim_pos])

            cur_str = s[cur_delim_pos + 1 : cur_delim_pos + 1 + cur_str_len]
            decoded_strs.append(cur_str)

            prev_str_end = cur_delim_pos + 1 + cur_str_len

        return decoded_strs
