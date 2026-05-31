class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());
        
        long long currentMass = mass;
        for (int a : asteroids) {
            if (currentMass < a) return false;
            currentMass += a;
        }
        return true;
    }
};