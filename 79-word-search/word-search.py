from collections import Counter

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])

        board_count = Counter(ch for row in board for ch in row)
        word_count = Counter(word)

        for ch, cnt in word_count.items():
            if board_count[ch] < cnt:
                return False

        if board_count[word[0]] > board_count[word[-1]]:
            word = word[::-1]

        def dfs(r, c, idx):
            if idx == len(word):
                return True

            if (
                r < 0 or r >= m or
                c < 0 or c >= n or
                board[r][c] != word[idx]
            ):
                return False

            temp = board[r][c]
            board[r][c] = "#"

            found = (
                dfs(r + 1, c, idx + 1) or
                dfs(r - 1, c, idx + 1) or
                dfs(r, c + 1, idx + 1) or
                dfs(r, c - 1, idx + 1)
            )

            board[r][c] = temp
            return found

        for i in range(m):
            for j in range(n):
                if dfs(i, j, 0):
                    return True

        return False