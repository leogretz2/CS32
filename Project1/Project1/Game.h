#ifndef GAME_H
#define GAME_H

class Arena;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nZombies);
	~Game();

	// Accessor
	int decodeDirection(char dir);

	// Mutator
	void play();

private:
	Arena* m_arena;
};

#endif