#include <iostream>;
#include <fstream>;

#include <chrono>;
#include <thread>;

#include "Player.h";

void Add(Player** player, int profileCount, int maxPlayers);
void Sort(Player** player, int profileCount);
void Edit(Player** player, int profileCount);
void Delete(Player** player, int profileCount);
bool End();
void Print(Player** player, int profileCount);
void Save(Player** player, int profileCount);


int main()
{
	//At start of main()
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int maxPlayers = 10;
	char command[6];
	bool run = true;

	Player** player = new Player * [maxPlayers];

	std::ifstream file;

	file.open("players.dat", std::ios::in | std::ios::binary);
	int profileCount = 0;

	if (file.is_open())
	{
		while (!file.eof() && file.peek() != EOF)
		{
			player[profileCount] = new Player();
			file.read((char*)&player[profileCount], sizeof(Player));
			profileCount++;
		}
	}

	file.close();
	


	while (run == true)
	{
		Print(player, profileCount);

		std::cout << "Would you like to ADD, SORT, Edit, DELETE, SAVE or END to end the program" << std::endl;
		std::cin >> command;
	
		// Converts all Uppercase letters to lowercase X -> x
		for (int i = 0; i < 10; i++)
		{
			if (command[i] >= 65 && command[i] <= 90)
			{
				command[i] = command[i] + 32;
			}
		}

		if (strcmp(command, "add") == 0)
		{
			Add(player, profileCount, maxPlayers);
		}

		else if (strcmp(command, "sort") == 0)
		{
			Sort(player, profileCount);
		}

		else if (strcmp(command, "edit") == 0)
		{
			Edit(player, profileCount);
		}

		else if (strcmp(command, "delete") == 0)
		{
			Delete(player, profileCount);
		}

		else if (strcmp(command, "end") == 0)
		{
			End();
		}

		else if (strcmp(command, "save") == 0)
		{
			Save(player, profileCount);
		}

	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	return 0;
}

void Add(Player** player, int profileCount, int maxPlayers)
{
	char name[24];
	int score;
	
	if (profileCount < maxPlayers)
	{
		std::cout << "Creating a new player!" << std::endl;
		player[profileCount + 1] = new Player();

		std::cout << "Name: ";
		std::cin >> name;
		player[profileCount + 1]->SetName(name);

		std::cout << "Score: ";
		std::cin >> score;
		player[profileCount + 1]->SetScore(score);
		player[profileCount + 1]->SetPos(profileCount + 1);
	}

	else
	{
		std::cout << "There are too many profiles (max 10) to add another, please delete a profile before adding a new one";
	}
}

void Sort(Player** player, int profileCount)
{
	bool sorted = false;

	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < profileCount - 1; i++)
		{
			if (strcmp(player[i]->GetName(), player[i + 1]->GetName()) > 0)
			{
				sorted = false;

				int temp = player[i]->GetPos();
				player[i]->SetPos(player[i + 1]->GetPos());
				player[i + 1]->SetPos(temp);
			}
		}
	}
}

void Edit(Player** player, int profileCount)
{

}

void Delete(Player** player, int profileCount)
{

}

bool End()
{
	return false;
}

void Print(Player** player, int profileCount)
{
	for (int i = 0; i < profileCount; i ++)
	{
		std::cout << "Name: " << player[i]->GetName();
		std::cout << "Score: " << player[i]->GetScore();
	}
}
void Save(Player** player, int profileCount)
{
	std::ofstream file;
	file.open("players.dat", std::ios_base::out | std::ios_base::binary);
	if (file.is_open())
	{
		for (int i = 0; i < profileCount; i++)
		{
			file.write((char*)&player[i], sizeof(Player));
		}
	}
}