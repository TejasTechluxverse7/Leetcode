class Solution:
    def reverse(self, x: int) -> int:
        res = 0
        sign = -1 if x < 0 else 1
        x = abs(x)
        
        while x:
            d = x % 10
            x //= 10
            
            if res > (2**31 - 1) // 10 or (res == (2**31 - 1) // 10 and d > 7):
                return 0
            
            res = res * 10 + d
        
        return sign * res