class Solution {
    struct Node {
        int next[26];
        int best;  // index of the best string for this suffix
        Node() {
            fill(next, next + 26, -1);
            best = -1;
        }
    };

    vector<Node> trie;

    bool better(int i, int j, const vector<string>& wordsContainer) {
        if (j == -1) return true;
        int li = wordsContainer[i].size();
        int lj = wordsContainer[j].size();
        if (li != lj) return li < lj;
        return i < j;
    }

    void updateBest(int node, int idx, const vector<string>& wordsContainer) {
        if (better(idx, trie[node].best, wordsContainer)) {
            trie[node].best = idx;
        }
    }

public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        trie.clear();
        trie.push_back(Node());  // root

        // Build trie on reversed container words
        for (int i = 0; i < (int)wordsContainer.size(); ++i) {
            int node = 0;
            updateBest(node, i, wordsContainer);  // empty suffix also considered
            const string& s = wordsContainer[i];
            for (int k = (int)s.size() - 1; k >= 0; --k) {
                int c = s[k] - 'a';
                if (trie[node].next[c] == -1) {
                    trie[node].next[c] = (int)trie.size();
                    trie.push_back(Node());
                }
                node = trie[node].next[c];
                updateBest(node, i, wordsContainer);
            }
        }

        // Answer queries
        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (const string& q : wordsQuery) {
            int node = 0;
            for (int k = (int)q.size() - 1; k >= 0; --k) {
                int c = q[k] - 'a';
                if (trie[node].next[c] == -1) break;
                node = trie[node].next[c];
            }
            ans.push_back(trie[node].best);
        }

        return ans;
    }
};