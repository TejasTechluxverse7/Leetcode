class Solution {
public:
    int divide(int dividend, int divisor) {
        // Overflow case
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        // Determine sign
        bool negative = (dividend < 0) ^ (divisor < 0);

        // Use long long to avoid overflow
        long long a = labs((long long)dividend);
        long long b = labs((long long)divisor);

        long long ans = 0;

        while (a >= b) {
            long long temp = b;
            long long multiple = 1;

            // Find largest shifted divisor
            while ((temp << 1) <= a) {
                temp <<= 1;
                multiple <<= 1;
            }

            a -= temp;
            ans += multiple;
        }

        if (negative) ans = -ans;

        return (int)ans;
    }
};