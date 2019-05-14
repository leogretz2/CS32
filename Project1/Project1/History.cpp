#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
	for(int r = 0; r < nRows; r++)
		for(int c = 0; c < nCols; c++)
			h_grid[r][c] = '.';  // Initializes the history grid to all dots

}

bool History::record(int r, int c) {
	if (r <= 0 || c <= 0 || r > MAXROWS || c > MAXCOLS)
		return false;
	switch(h_grid[r-1][c-1]) {
		case '.':
			h_grid[r-1][c-1] = 'A'; // One Zombie killed
			break;
		case 'Y':
		case 'Z':
			h_grid[r-1][c-1] = 'Z'; // 26 Zombies now killed
			break;
		default:
			h_grid[r-1][c-1]++;	// One letter higher if in the middle
			break;
	} 
	return true;
}

void History::display() const {
	int r, c;
	
	clearScreen();

	// Draw the history grid
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
			cout << h_grid[r][c];
		cout << endl;
	}
	cout << endl;
}