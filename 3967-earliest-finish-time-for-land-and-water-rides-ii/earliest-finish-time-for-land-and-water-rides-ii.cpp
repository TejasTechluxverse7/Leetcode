class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        long long bestLandFinish = LLONG_MAX;
        for (int i = 0; i < (int)landStartTime.size(); ++i) {
            bestLandFinish = min(bestLandFinish,
                                 1LL * landStartTime[i] + landDuration[i]);
        }

        long long bestWaterFinish = LLONG_MAX;
        for (int j = 0; j < (int)waterStartTime.size(); ++j) {
            bestWaterFinish = min(bestWaterFinish,
                                  1LL * waterStartTime[j] + waterDuration[j]);
        }

        long long ans = LLONG_MAX;

        // Land first, then water
        for (int j = 0; j < (int)waterStartTime.size(); ++j) {
            long long finish = max(bestLandFinish, 1LL * waterStartTime[j]) + waterDuration[j];
            ans = min(ans, finish);
        }

        // Water first, then land
        for (int i = 0; i < (int)landStartTime.size(); ++i) {
            long long finish = max(bestWaterFinish, 1LL * landStartTime[i]) + landDuration[i];
            ans = min(ans, finish);
        }

        return (int)ans;
    }
};