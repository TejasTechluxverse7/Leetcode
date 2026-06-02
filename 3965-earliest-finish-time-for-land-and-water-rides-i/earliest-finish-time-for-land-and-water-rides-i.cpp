class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        int ans = INT_MAX;
        int n = landStartTime.size();
        int m = waterStartTime.size();

        // Land ride first, then water ride
        for (int i = 0; i < n; i++) {
            int landFinish = landStartTime[i] + landDuration[i];
            for (int j = 0; j < m; j++) {
                int waterFinish = max(landFinish, waterStartTime[j]) + waterDuration[j];
                ans = min(ans, waterFinish);
            }
        }

        // Water ride first, then land ride
        for (int j = 0; j < m; j++) {
            int waterFinish = waterStartTime[j] + waterDuration[j];
            for (int i = 0; i < n; i++) {
                int landFinish = max(waterFinish, landStartTime[i]) + landDuration[i];
                ans = min(ans, landFinish);
            }
        }

        return ans;
    }
};