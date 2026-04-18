from typing import List

class Solution:
    def findMedianSortedArrays(self, a: List[int], b: List[int]) -> float:
        if len(a) > len(b):
            a, b = b, a
        
        m, n = len(a), len(b)
        l, r = 0, m
        
        while l <= r:
            i = (l + r) // 2
            j = (m + n + 1) // 2 - i
            
            aL = float('-inf') if i == 0 else a[i-1]
            aR = float('inf') if i == m else a[i]
            bL = float('-inf') if j == 0 else b[j-1]
            bR = float('inf') if j == n else b[j]
            
            if aL <= bR and bL <= aR:
                if (m + n) % 2:
                    return max(aL, bL)
                return (max(aL, bL) + min(aR, bR)) / 2
            elif aL > bR:
                r = i - 1
            else:
                l = i + 1