#include <queue>
#include <string>
#include <iostream>

using namespace std;

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


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	queue<Coord> coordQueue;
	coordQueue.push(Coord(sr, sc));
	maze[sr][sc] = 'A';
	while (!coordQueue.empty()) {
		Coord curr = coordQueue.front();
		coordQueue.pop();
		if (curr.r() == er && curr.c() == ec)
			return true;
		if (maze[curr.r() + 1][curr.c()] == '.') {
			coordQueue.push(Coord(curr.r() + 1, curr.c()));
			maze[curr.r() + 1][curr.c()] = 'A';
		}
		if (maze[curr.r()][curr.c() - 1] == '.') {
			coordQueue.push(Coord(curr.r(), curr.c() - 1));
			maze[curr.r()][curr.c() - 1] = 'A';
		}
		if (maze[curr.r() - 1][curr.c()] == '.') {
			coordQueue.push(Coord(curr.r() - 1, curr.c()));
			maze[curr.r() - 1][curr.c()] = 'A';
		}
		if (maze[curr.r()][curr.c() + 1] == '.') {
			coordQueue.push(Coord(curr.r(), curr.c() + 1));
			maze[curr.r()][curr.c() + 1] = 'A';
		}
	}
	return false;
}