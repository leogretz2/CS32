#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"


class History
{
	public:
		History(int nRows, int nCols);	// Constructor
		bool record(int r, int c);		// Records where a zombie was killed
		void display() const;			// Displays the history grid
	private:
		int m_rows;
		int m_cols;
		char h_grid[MAXROWS][MAXCOLS];
};

#endif