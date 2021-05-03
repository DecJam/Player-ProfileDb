#include <iostream>;
#include "Player.h";

// Returns the players name
const char* Player::GetName()
{
	return m_Name;
}

// Setsthe players score
void Player::SetName(const char* name)
{
	strcpy_s(m_Name, sizeof(m_Name), name);
}

// Return theplayers score
int Player::GetScore()
{
	return m_Score;
}

// Sets the players score
void Player::SetScore(int score)
{
	m_Score = score;
}

// Returns the player in queue
int Player::GetPos()
{
	return m_Pos;
}

// Sets the players position in queue
void Player::SetPos(int pos)
{
	m_Pos = pos;
}