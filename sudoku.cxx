#include <utility>
#include <vector>
#include <deque>
#include <iterator>

using std::deque;
using std::pair;
using std::vector;

#define CELL 4
#define LINE (CELL * CELL)

class Grid {
private:
    char _grid[LINE][LINE];

public:
    typedef pair<unsigned, unsigned> cell;
    typedef vector<cell> cells;

    /**
     * Iterate through cells.
     */
    class iterator :
        public std::iterator<std::random_access_iterator_tag, cell> {
    private:
        friend class Grid;
        Grid &_g;
        unsigned _pos;

        iterator(Grid &g) : _g(g), _pos(0) {};
        iterator(Grid &g, unsigned i) : _g(g) {
            if (i > LINE * LINE)
                i = LINE * LINE;
            _pos = i;
        };

        iterator(const iterator &it) : _g(it._g), _pos(it._pos) {};

        /** Advance to the next cell. The cell LINE * LINE is the end value. */
        iterator &operator++() {
            if (_pos < LINE * LINE) {
                _pos++;
            }

            return *this;
        };

        iterator &operator+(unsigned i) {
            _pos += i;
            if (_pos >= LINE * LINE) {
                _pos = LINE * LINE;
            }

            return *this;
        };

        iterator &operator-(unsigned i) {
            int j = _pos - i;
            if (j < 0)
                _pos = 0;
            else
                _pos = j;

            return *this;
        };

        /** Back up to the previous cell. */
        iterator &operator--() {
            if (_pos > 0) {
                _pos--;
            }

            return *this;
        };

        bool operator==(const iterator &it) {
            return _pos == it._pos;
        };

        bool operator!=(const iterator &it) {
            return _pos != it._pos;
        };

        iterator &operator=(const iterator &it) {
            _pos = it._pos;
            _g = it._g;
            return *this;
        };

        cell operator*() {
            return cell(_pos / LINE, _pos % LINE);
        };
    };

    iterator begin() {
        return iterator(*this);
    };

    iterator end() {
        return iterator(*this, LINE * LINE);
    };

    const bool conflict(const cell &c) const {
        unsigned x(c.first);
        unsigned y(c.second);

        if (_grid[x][y] == '-')
            return false;

        for (unsigned i = 0; i < LINE; i++) {
            if (i == x)
                continue;

            if (_grid[i][y] == _grid[x][y])
                return true;
        }

        for (unsigned i = 0; i < LINE; i++) {
            if (i == y)
                continue;

            if (_grid[x][i] == _grid[x][y])
                return true;
        }

        unsigned reg_x = x / CELL * CELL;
        unsigned reg_y = y / CELL * CELL;

        for (unsigned i = reg_x; i < reg_x + CELL; i++) {
            for (unsigned j = reg_y; j < reg_y + CELL; j++) {
                if (i == x && j == y)
                    continue;

                if (_grid[x][y] == _grid[i][j])
                    return true;
            }
        }
        return false;
    };

    const bool complete() const {
        for (int i = 0; i < LINE; i++) {
            for (int j = 0; j < LINE; j++) {
                if (_grid[i][j] == '-')
                    return false;
            }
        }

        return true;
    };
};

class CSP {
private:
    deque<Grid::cell> _work;
    Grid _grid;
public:
    CSP(const Grid &g) : _grid(g) {

    }
};

int main(int argc, char **argv) {
    return 0;
}
