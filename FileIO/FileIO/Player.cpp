#include <iostream>;
#include "Player.h";

// Returns the players name
char* Player::GetName()
{
	return m_Name;
}

// Sets the players score
void Player::SetName(char* name)
{
	strcpy_s(m_Name, sizeof(m_Name), name);
}

// Return the players score
int Player::GetScore()
{
	return m_Score;
}

// Sets the players score
void Player::SetScore(int score)
{
	m_Score = score;
}

