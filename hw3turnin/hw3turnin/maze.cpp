class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	if (sr == er && sc == ec)
		return true;
	maze[sr][sc] = 'A';
	for (int i = 0; i < 4; i++) {
		int row = 0;
		int col = 0;
		switch (i) {
		case 0: row = sr + 1; col = sc; break;
		case 1: col = sc - 1; row = sr; break;
		case 2: row = sr - 1; col = sc;  break;
		case 3: col = sc + 1; row = sr; break;
		}
		if (maze[row][col] == '.') {
			if (pathExists(maze, nRows, nCols, row, col, er, ec))
				return true;
		}
	}
	return false;
}