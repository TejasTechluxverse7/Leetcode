from typing import List

class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        rows = [0] * 9
        cols = [0] * 9
        boxes = [0] * 9
        empties = []

        def box_id(r: int, c: int) -> int:
            return (r // 3) * 3 + (c // 3)

        # Build initial masks and list of empty cells
        for r in range(9):
            for c in range(9):
                if board[r][c] == '.':
                    empties.append((r, c))
                else:
                    d = ord(board[r][c]) - ord('1')
                    bit = 1 << d
                    rows[r] |= bit
                    cols[c] |= bit
                    boxes[box_id(r, c)] |= bit

        def backtrack() -> bool:
            if not empties:
                return True

            # Choose the empty cell with the fewest possible candidates
            best_idx = -1
            best_mask = 0
            min_count = 10

            for i, (r, c) in enumerate(empties):
                used = rows[r] | cols[c] | boxes[box_id(r, c)]
                mask = (~used) & 0x1FF  # digits 1..9
                cnt = mask.bit_count()
                if cnt < min_count:
                    min_count = cnt
                    best_idx = i
                    best_mask = mask
                    if cnt == 1:
                        break

            r, c = empties.pop(best_idx)
            b = box_id(r, c)
            mask = best_mask

            while mask:
                bit = mask & -mask
                d = bit.bit_length() - 1

                board[r][c] = chr(ord('1') + d)
                rows[r] |= bit
                cols[c] |= bit
                boxes[b] |= bit

                if backtrack():
                    return True

                rows[r] ^= bit
                cols[c] ^= bit
                boxes[b] ^= bit
                board[r][c] = '.'

                mask -= bit

            empties.insert(best_idx, (r, c))
            return False

        backtrack()