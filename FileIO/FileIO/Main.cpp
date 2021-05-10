#include <iostream>;
#include <fstream>;

#include <chrono>;
#include <thread>;

#include "Player.h";

// Initializes functions to the compiler
int Add(Player** player, int profileCount, int maxPlayers, bool* save);
void Sort(Player** player, int profileCount, bool* save);
void Edit(Player** player, int profileCount, bool* save);
int Delete(Player** player, int profileCount, bool* save);
bool End(Player** player, int maxPlayer, bool* save);
void Print(Player** player, int profileCount);
void Save(Player** player, int profileCount, bool* save);

int main()
{
	// Checks for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int maxPlayers = 24;
	char command[6];
	bool run = true;
	bool* save = new bool;
	*save = false;

	Player** player = new Player * [maxPlayers];

	std::ifstream file;

	// Opens a file in ./Files/players.dat
	file.open("./Files/players.dat", std::ios::in | std::ios::binary);
	int profileCount = 0;
	
	// Reads the data from the file and writes the data to the player array 
	if (file.is_open())
	{
		while (!file.eof() && file.peek() != EOF)
		{
			player[profileCount] = new Player();
			file.read((char*)player[profileCount], sizeof(Player));
			profileCount++;
		}
	}

	file.close();

	// Keeps looping while the application is running
	while (run == true)
	{
		Print(player, profileCount);

		std::cout << "Would you like to ADD, SORT, EDIT, DELETE, SAVE or END to end the program" << std::endl;
		std::cin >> command;
	
		// Converts all Uppercase letters to lowercase X -> x
		for (int i = 0; i < strlen(command-1); i++)
		{
			if (command[i] >= 65 && command[i] <= 90)
			{
				command[i] = command[i] + 32;
			}
		}

		// Runs appropriate function depending on the command given
		if (strcmp(command, "add") == 0)
		{
			profileCount = Add(player, profileCount, maxPlayers, save);
		}

		else if (strcmp(command, "sort") == 0)
		{
			Sort(player, profileCount, save);
		}

		else if (strcmp(command, "edit") == 0)
		{
			Edit(player, profileCount, save);
		}

		else if (strcmp(command, "delete") == 0)
		{
			profileCount = Delete(player, profileCount, save);
		}

		else if (strcmp(command, "end") == 0)
		{
			run = End(player, profileCount, save);
		}

		else if (strcmp(command, "save") == 0)
		{
			Save(player, profileCount, save);
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	return 0;
}

// Adds another player to the player array
int Add(Player** player, int profileCount, int maxPlayers, bool* save)
{
	system("CLS");
	char name[24];
	int score;
	
	// Makes sure you can't add more than 10 people
	if (profileCount < maxPlayers)
	{
		// Creates a new player profile
		std::cout << "Creating a new player!" << std::endl;
		player[profileCount] = new Player();

		std::cout << "Name: " ;
		std::cin >> name;

		// Converts all Uppercase letters to lowercase X -> x
		for (int i = 0; i < strlen(name - 1); i++)
		{
			if (name[i] >= 65 && name[i] <= 90)
			{
				name[i] = name[i] + 32;
			}
		}

		for (int i = 0; i < profileCount; i++)
		{
			if (strcmp(name, player[i]->GetName()) == 0)
			{
				std::cout << " Thst profile already exists! please choose another name";
				Add(player, profileCount, maxPlayers, save);
			}
		}

		player[profileCount]->SetName(name);

		std::cout << "Score: ";
		std::cin >> score;
		player[profileCount]->SetScore(score);
		profileCount += 1;
		std::cout << "Total players: " << profileCount << std::endl;
	}

	else
	{
		std::cout << "There are too many profiles (max 10) to add another, please delete a profile before adding a new one" << std::endl;
		std::cout << "Press ENTER to continue!";
		system("PAUSE");
	}
	*save = false;
	return profileCount;
}

// Sorts the player profiles using bubble sort
void Sort(Player** player, int profileCount, bool* save)
{
	system("CLS");
	bool sorted = false;

	Player* p1;

	// Starts the bubble sort using p1 as a temporary data container
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < profileCount - 1; i++)
		{
			if (strcmp(player[i]->GetName(), player[i + 1]->GetName()) > 0)
			{
				sorted = false;
	
				p1 = player[i];
				player[i] = player[i + 1];
				player[i + 1] = p1;
			}
		}
	}
	*save = false;
}

// Edits a previously created profile, using binary search
void Edit(Player** player, int profileCount, bool* save)
{
	system("CLS");
	Print(player, profileCount);

	char name[24]; 
	int min = 0;
	int max = profileCount - 1;
	int mid = (min + max) / 2;
	bool search = false;
	int editProfile;

	std::cout << "What profile would you like to change?" << std::endl;
	std::cin >> name;

	// Converts all Uppercase letters to lowercase X -> x
	for (int i = 0; i < strlen(name - 1); i++)
	{
		if (name[i] >= 65 && name[i] <= 90)
		{
			name[i] = name[i] + 32;
		}
	}

	// Starts the birary search 
	while (search == false)
	{
		// the two names are the same
		if (strcmp(name, player[mid]->GetName()) == 0)
		{
			// Search complete
			editProfile = mid;
			search = true;
		}

		// The searched name had a lower alphanumerical value compared to the midpoints player name
		else if (strcmp(name, player[mid]->GetName()) < 0)
		{
			max = mid - 1;
		}

		// The searched name had a higher alphanumerical value compared to the midpoints player name
		else if (strcmp(name, player[mid]->GetName()) > 0)
		{
			min = mid + 1;
		}
		mid = (min + max) / 2;
	}

	// Creates and sets the new name and score
	char newName[24];
	int score;

	std::cout << "Chosen Profile" << std::endl;
	std::cout << "Current name: " << player[editProfile]->GetName() << std::endl;
	std::cout << "Current Score: " << player[editProfile]->GetScore() << std::endl << std::endl;

	std::cout << "New name: ";
	std::cin >> newName;

	// Converts all Uppercase letters to lowercase X -> x
	for (int i = 0; i < strlen(newName - 1); i++)
	{
		if (newName[i] >= 65 && newName[i] <= 90)
		{
			newName[i] = newName[i] + 32;
		}
	}

	player[editProfile]->SetName(newName);

	std::cout << "New score: ";
	std::cin >> score;
	std::cout << std:: endl;
	player[editProfile]->SetScore(score);

	std::cout << "Profile changed!";
	
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	system("CLS");
	*save = false;
}

// Deletes selected player using binary search
int Delete(Player** player, int profileCount, bool* save)
{
	system("CLS");
	Print(player, profileCount);

	char name[24];
	int min = 0;
	int max = profileCount - 1;
	int mid = (min + max) / 2;
	bool search = false;
	int delProfile;

	std::cout << "What profile would you like to delete?" << std::endl;
	std::cin >> name;

	// Converts all Uppercase letters to lowercase X -> x
	for (int i = 0; i < strlen(name - 1); i++)
	{
		if (name[i] >= 65 && name[i] <= 90)
		{
			name[i] = name[i] + 32;
		}
	}

	// Starts the binary search
	while (search == false)
	{
		// Creates a lowercase version of the players name
		char nameLC[24];
		strcpy_s(nameLC, sizeof(nameLC), player[mid]->GetName());

		// The two names are the same
		if (strcmp(name, nameLC) == 0)
		{
			// Search complete
			delProfile = mid;
			search = true;
		}

		// The searched name had a lower alphanumerical value compared to the midpoints player name
		else if (strcmp(name, nameLC) < 0)
		{
			max = mid - 1;
		}

		// The searched name had a higher alphanumerical value compared to the midpoints player name
		else if (strcmp(name, nameLC) > 0)
		{
			min = mid + 1;
		}
		mid = (min + max) / 2;
	}

	// Deletes and nullifies the desired player
	if (player[delProfile])
	{
		delete player[delProfile];
		player[delProfile] = nullptr;
	}

	// Shifts the profiles so the nulled profile goes towards the end of the array
	for (int i = 0; i < profileCount - 1; i++)
	{
		if (player[i] == nullptr)
		{
			player[i] = player[i + 1];
			player[i + 1] = nullptr;
		}
	}

	profileCount -=1;

	std::cout << "Profile deleted!";

	Print(player, profileCount);
	std::this_thread::sleep_for(std::chrono::milliseconds(1400));
	system("CLS");

	*save = false;
	return profileCount;
}

// Prints all the current players profiles
void Print(Player** player, int profileCount)
{
	system("CLS");
	std::cout << "Current profiles: " << std::endl << std::endl;
	
	// Checks how many profiles are in the array and prints appropriate response
	if (profileCount == 0)
	{
		std::cout << "NULL" << std::endl;
	}

	else if (profileCount > 0)
	{
		for (int i = 0; i < profileCount; i ++)
		{
			std::cout << "Player " << i + 1 << std::endl;
			std::cout << "Name: " << player[i]->GetName() << std::endl;
			std::cout << "Score: " << player[i]->GetScore() << std::endl << std::endl;
		}
	}
}

// Saves/writes the array of player data to a .dat file in binary
void Save(Player** player, int profileCount, bool* save)
{
	system("CLS");
	std::cout << "Saving file";

	// Creates a output file and outputs to the file at './Files/players.dat'
	std::ofstream file;
	file.open("./Files/players.dat", std::ios_base::out | std::ios_base::binary);
	if (file.is_open())
	{
		// Cycles through all the players accounted for and writes their data to the file
		for (int i = 0; i < profileCount; i++)
		{
			file.write((char*)player[i], sizeof(Player));
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	system("CLS");
	std::cout << "File saved!";
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	system("CLS");

	*save = true;
}

// Ends the program safely, deleting and nullifying any pointers
bool End(Player** player, int profileCount, bool* save)
{

	if (*save == false)
	{
		char choice[4];

		std::cout << "You have not saved your changes, would you like to save? yes/no" << std::endl;
		std::cin >> choice;

		// Converts all Uppercase letters to lowercase X -> x
		for (int i = 0; i < strlen(choice - 1); i++)
		{
			if (choice[i] >= 65 && choice[i] <= 90)
			{
				choice[i] = choice[i] + 32;
			}
		}

		if (strcmp(choice, "yes") == 0)
		{
			Save(player, profileCount, save);
		}

		else if (strcmp(choice, "no"))
		{
		}
	}

	else if (*save == true)
	{
	}
	// deletes and nullifies all elements of the 'player' array
	for (int i = 0; i < profileCount; i++)
	{
		if (player[i])
		{
			delete player[i];
			player[i] = nullptr;
		}
	}

	// Deletes and nullifies the array 'player'
	if (player)
	{
		delete[] player;
		player = nullptr;
	}

	delete save;
	save = nullptr;

	return false;
}
