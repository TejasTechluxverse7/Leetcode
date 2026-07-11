class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        ans = []

        def backtrack(idx, parts, curr):
            # If 4 parts are formed
            if parts == 4:
                if idx == len(s):
                    ans.append(".".join(curr))
                return

            # Try segments of length 1 to 3
            for length in range(1, 4):
                if idx + length > len(s):
                    break

                part = s[idx:idx + length]

                # No leading zeros
                if len(part) > 1 and part[0] == '0':
                    break

                # Value must be <= 255
                if int(part) <= 255:
                    curr.append(part)
                    backtrack(idx + length, parts + 1, curr)
                    curr.pop()

        # Quick pruning
        if len(s) < 4 or len(s) > 12:
            return []

        backtrack(0, 0, [])
        return ans