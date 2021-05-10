#pragma once

class Player
{
public:

	// Returns the players name
	char* GetName();

	// Sets the players name
	void SetName(char* name);

	// Returns the players score
	int GetScore();

	// Sets the players score
	void SetScore(int score);

private:

	// Players score
	int m_Score;

	// Players name
	char m_Name[24];
};

