import sys
from collections import deque
import math
import itertools as IT

LINE = 16
CELL = 4

class Grid:
    def __init__(self, fp):
        ls = []

        for l in fp:
            ls.append(list(l.strip()))
        self._grid = ls

    def empty(self):
        return ((x, y)
                for x in range(LINE)
                for y in range(LINE)
                if self._grid[x][y] == '-')

    def __getitem__(self, i):
        return self._grid[i]

    def __str__(self):
        return '\n'.join(''.join(l) for l in self._grid)

    def complete(self):
        return not any(c == '-' for c in IT.chain(*self._grid))

class BackTrack:
    def __init__(self, grid):
        self._grid = grid
        self._queue = deque()
        [self._queue.appendleft(c) for c in self._grid.empty()]

    def __getitem__(self, i):
        return self._grid[i]

    def conflict(self, grid_c, grid_r):
        C = self[grid_c][grid_r]

        if(C == '-'):
            return False

        # Pull this into the locals() to save time
        grid = self._grid._grid

        for i in range(LINE):
            if(i == grid_r): continue
            if(grid[grid_c][i] == C):
                return True

        for i in range(LINE):
            if(i == grid_c): continue
            if(grid[i][grid_r] == C):
                return True

        box_c = grid_c // CELL * CELL
        box_r = grid_r // CELL * CELL

        for x in range(box_c, box_c+CELL):
            for y in range(box_r, box_r+CELL):
                if( x != grid_c and y != grid_r):
                    if(grid[x][y] == C):
                        return True
        return False

    def __call__(self):
        if(self._grid.complete()):
            return True

        g_y, g_x = self._queue.popleft()

        # Pull this into locals() to improve performance
        grid = self._grid._grid
        for i in range(LINE):
            value = hex(i+1)[-1].upper()
            grid[g_y][g_x] = str(value)
            if(self.conflict(g_y, g_x)):
                grid[g_y][g_x] = '-'
                continue

            if self():
                return True
            else:
                grid[g_y][g_x] = '-'
        self._queue.appendleft((g_y, g_x))
        return False

if __name__ == "__main__":
    grid = Grid(open(sys.argv[1], "r"))
    b = BackTrack(grid)
    b()
    print(str(grid))
