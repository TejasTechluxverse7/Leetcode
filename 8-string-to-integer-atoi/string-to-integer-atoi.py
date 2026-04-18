class Solution:
    def myAtoi(self, s: str) -> int:
        i, n = 0, len(s)
        
        while i < n and s[i] == ' ':
            i += 1
        
        sign = 1
        if i < n and (s[i] == '+' or s[i] == '-'):
            if s[i] == '-':
                sign = -1
            i += 1
        
        res = 0
        INT_MAX, INT_MIN = 2**31 - 1, -2**31
        
        while i < n and s[i].isdigit():
            d = int(s[i])
            
            if res > INT_MAX // 10 or (res == INT_MAX // 10 and d > 7):
                return INT_MAX if sign == 1 else INT_MIN
            
            res = res * 10 + d
            i += 1
        
        return sign * res