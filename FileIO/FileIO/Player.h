#pragma once

class Player
{
public:

	// Returns the players name
	const char* GetName();

	// Sets the players name
	void SetName(const char* name);

	// Returns the players score
	int GetScore();

	// Sets the players score
	void SetScore(int score);

	// Returns the players position in queue
	int GetPos();
	
	// Sets the players position in queue
	void SetPos(int pos);

private:

	// Players name
	char m_Name[24];

	// Players score
	int m_Score;

	// Players position
	int m_Pos;
};

