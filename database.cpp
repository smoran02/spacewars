#include "database.h"
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

Database::Database()
{
	//initialize number of users and the highest ID value to 0
	users = 0;
	maxId = 0;
}

Database::~Database()
{

}

bool Database::validName(char* name)
{
  for (int i = 0; i < strlen(name); i++)
  {
      if (( ! isalnum(name[i]) && (name[i] != '_')))
         return false;
  }

  //if we fall out of the loop, all characters valid
  return true;
}

bool Database::validYear(int year)
{
	//validate that the year is within the given range
	if (year >= 1 && year <= 5)
		return true;
	else
	{
		return false;
	}
}

bool Database::validYear(char* year)
{
	//validate that the year is only digits
	for (int i = 1; i < (int)strlen(year); i++)
	{
		if (!isdigit(year[i]))
		{
			return false;
		}
	}

	//validate the year

	int yearInt = atoi(year);

	if (!validYear(yearInt))
	{
			return false;
	}
	return true;
}

bool Database::validId(int id)
{
	//make sure the id is within the given range
	if (id >= 1 && id <= 1000000000)
		return true;
	else
		return false;
}

bool Database::validScore(int score)
{
	//need to make sure this is an integer
	return true;
}

bool Database::userUnique(char* name)
{
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (strcmp(userList[i].name, name) == 0)
			return false;
	}

	//if we get here, the username is unique

	return true;
}

bool Database::userUnique(int Id)
{
    for (int i = 0; i < (int)userList.size(); i++)
    {
       if (Id == userList[i].id)
         return false;
    }

    //if we get here, the id is unique

    return true;
}

bool Database::userFound(char* name)
{
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (strcmp(userList[i].name, name) == 0)
		{
			return true;
		}
	}
	
	//if we get here, the username was not found in the list
	return false;
}

int Database::userCountFromFile(ifstream& fin, int& line_count)
{
	char line[128];

	fin.getline(line, sizeof(line));
	line_count++;

	//verify that this line contains a number

	for (int i = 0; i < (int)strlen(line); i++)
	{
		if (!isdigit(line[i]))
		{
			sprintf(report, "Invalid user count on line %d (must be numeric)", line_count);
			return -1;
		}
	}

	//if we get here, we have a valid numeric string
	//convert to integer

	int count = atoi(line);
	return count; 
}

int Database::userIdFromFile(ifstream& fin, int& line_count)
{
	char line[128];

	fin.getline(line, sizeof(line));
	line_count++;

	//verify that this line contains a number

	for (int i = 0; i < (int)strlen(line); i++)
	{
		if (!isdigit(line[i]))
		{
			sprintf(report, "Invalid user id on line %d (must be numeric)", line_count);
			return -1;
		}
	}

	//if we get to here, we have a valid numeric string  
	//make sure it is a valid userId (1 thru 1,000,000,000).

	int id = atoi(line);

	if (!validId(id))
	{
		sprintf(report, "Invalid user id on line %d (must be between 1 and 1,000,000,000)", line_count);
		return -1;
	}

	//the id must be unique

	if (!userUnique(id))
	{
		sprintf(report, "Duplicate user id on line %d (must be unique)", line_count);
		return -1;
	}

	//the id is valid and unique, so return it

	if (maxId < id)
		maxId = id;

	return id;
}

void Database::userNameFromFile(ifstream& fin, int& line_count, char* name)
{
	char line[256];

	name[0] = '\0';

	fin.getline(line, sizeof(line));
	line_count++;

	//verify the line starts with <tab>

	if (line[0] != '\t')
	{
		sprintf(report, "Invalid format on line %d, line must start with tab character", line_count);
		return;
	}

	//the name can contain only alphanumeric and underscore characters

	if (!validName(&line[1]))
	{
		sprintf(report, "Invalid name on line %d (must be alphanumeric or underscore characters only)", line_count);
		return;
	}

	//the user name must be unique

	if (!userUnique(&line[1]))
	{
		sprintf(report, "Duplicate user name on line %d (must be unique)", line_count);
		return;
	}

	//the user name is valid, so return it

	strcpy(name, &line[1]);
}

int Database::yearFromFile(ifstream& fin, int& line_count)
{
	char line[128];

	fin.getline(line, sizeof(line));
	line_count++;

	//verify the line starts with <tab>

	if (line[0] != '\t')
	{
		sprintf(report, "Invalid format on line %d, line must start with tab character", line_count);
		return -1;
	}

	//verify that this line contains a number

	for (int i = 1; i < (int)strlen(line); i++)
	{
		if (!isdigit(line[i]))
		{
			sprintf(report, "Invalid year on line %d (must be numeric)", line_count);
			return -1;
		}
	}

	//validate the year

	int year = atoi(&line[1]);

	if (!validYear(year))
	{
			sprintf(report, "Invalid year on line %d (must be between 1 and 5)", line_count);
			return -1;
	}

	//if we get here, we have a valid year

	return year; 
}

int Database::scoreFromFile(ifstream& fin, int& line_count)
{
	char line[128];

	fin.getline(line, sizeof(line));
	line_count++;

	//verify the line starts with <tab>

	if (line[0] != '\t')
	{
		sprintf(report, "Invalid format on line %d, line must start with tab character", line_count);
		return -1;
	}

	//verify that this line contains a number

	for (int i = 1; i < (int)strlen(line); i++)
	{
		if (!isdigit(line[i]))
		{
			sprintf(report, "Invalid score on line %d (must be numeric)", line_count);
			return -1;
		}
	}

	//if we get here, we have a valid score

	int score = atoi(&line[1]);
	return score; 
}

int Database::friendsFromFile(ifstream& fin, int& line_count, vector<int>& friend_ids)
{
	char line[1024];

	fin.getline(line, sizeof(line));
	line_count++;

	//verify the line starts with <tab>

	if (line[0] != '\t')
	{
		sprintf(report, "Invalid format on line %d, line must start with tab character", line_count);
		return -1;
	}

	//each friend id will be separated by a <tab>
	//get each id and make sure it is valid

	char* friend_id = strtok(&line[1], "\t");

	while (friend_id != NULL)
	{
		char temp[64];
		
		strcpy(temp, friend_id);

		//make sure this id contains only numerics

		for (int i = 0; i < (int)strlen(temp); i++)
		{
			if (!isdigit(temp[i]))
			{
				sprintf(report, "Invalid friend user id on line %d (must be numeric)", line_count);
				return -1;
			}
		}

		//make sure it is a valid id (1 thru 1,000,000,000)

		int id = atoi(friend_id);

		if (!validId(id))
		{
			sprintf(report, "Invalid friend user id on line %d (must be between 1 and 1,000,000,000)", line_count);
			return -1;
		}

		//the friend id is valid, add it to our list of friends

		friend_ids.push_back(id);

		//get the next friend id

		friend_id = strtok(NULL, "\t");
	}

	//the friend ids were valid, return the number of friends

	return ((int)friend_ids.size());
}

char* Database::readFromFile(ifstream& fin)
{
	int line_count = 0;

	//we will validate input as we read data from the file
	//and terminate the reading if any errors are encountered.

	//the first line must be a count of users in the database.

	users = userCountFromFile(fin, line_count);
	//line_count++;
	
	if (users == -1)
	{
		return report;   //report invalid user count
	}

	//the remainder of the file comes in blocks of 5 lines each,
	//with the following format:
	//   user_id (numeric, 1 thru 1,000,000,000)
	//   <tab>user_name (string, alphanumeric and underscores only)
	//   <tab>year (numeric, 1 thru 5)
	//   <tab>score (numeric)
	//   <tab>friend ids (numeric, 1 thru 1,000,000,000, separated by <tab>)

	while(!fin.eof())
	{
		//get the user id

		int id = userIdFromFile(fin, line_count);

		if (id == -1)
			return report;  //report invalid Id

		// get the user name

		char name[256];

		if (!fin.eof())
		{
			userNameFromFile(fin, line_count, name);

			if ((int)strlen(name) == 0)
				return report;  //report invalid user name
		}

		//get the year

		int year;

		if (!fin.eof())
		{
			year = yearFromFile(fin, line_count);

			if (year == -1)
				return report;  //report invalid year
		}

		//get the score

		int score;

		if (!fin.eof())
		{
			score = scoreFromFile(fin, line_count);

			if (score == -1)
				return report;  //report invalid score
		}

		//get the friends

		vector<int> friend_ids;
		int friend_count = 0;

		if (!fin.eof())
		{
			friend_count = friendsFromFile(fin, line_count, friend_ids);

			if (friend_count == -1)
				return report;  //report invalid friend id
		}

		//make sure we read 5 lines from the database

		int check = line_count - 1;

		if ((check % 5) != 0)
		{
			sprintf (report, "Error at line %d - line count must be 5*n + 1, where n is the number of users", line_count);
			return report;
		}

		//the data for this user is valid.  Add it to our
		//user list

		User new_user;

		new_user.id = id;
		strcpy(new_user.name, name);
		new_user.year = year;
		new_user.score = score;
		
		for (int i = 0; i < friend_count; i++)
			new_user.friends.push_back(friend_ids[i]);
			
		userList.push_back(new_user);
	}

	//we are done with loading the database and
	//there are no errors.  Return an empty string.

	report[0] = '\0';
	return report;
}

void Database::addUser(char* name, int id, int year)
{
	//take the given information and add the new user to the userlist
	//increase the total number of users by 1	
	User newUser;
	strcpy(newUser.name, name);
	newUser.id = id;
	newUser.year = year;
	newUser.score = 0;
	userList.push_back(newUser);
	users++;
}

void Database::deleteUser(char* name)
{
	int idCheck = -1;
	int place = -1;
	
	for (int i = 0; i < (int)userList.size(); i++)
	{
		//if the name is found, set the appropriate variables to the id and the index
		if (strcmp(userList[i].name, name) == 0)
		{
			idCheck = userList[i].id;
			place = i;
		}
	
	}

	//delete all dangling friend references
	for (int i = 0; i < (int)userList.size(); i++)
	{
		for (int j = 0; j < (int)userList[i].friends.size(); j++)
		{
			if (userList[i].friends[j] == idCheck)
				userList[i].friends.erase(userList[i].friends.begin() + j);
		}
	}

	//if place changed value, the index should be deleted
	if (place != -1)
	{
		userList.erase(userList.begin() + place);
		users--;
		cout << name << " successfully deleted!" << endl;
	}

	//otherwise, no deletion occurred
	else
	{
		cout << "Sorry, " << name << " not found in user list." << endl;
	}
}

void Database::addFriend(char* name1, char* name2)
{
	//return indices for the usernames
	int A = this->getIndex(name1);
	int B = this->getIndex(name2);

	//if the name you are adding does not exist, print error message and return
	if (B == -1)
	{
		cout << "User " << name2 << " not found." << endl;
		return;
	}
	int idCheck = this->getId(name2);
	bool duplicate = false;
	
	//ensure that name2 does not already exist in the friend vector of name1
	for (int i = 0; i < (int)userList[A].friends.size(); i++)
	{
		if (userList[A].friends[i] == idCheck)
		{
			duplicate = true;
			
		}
	}
	
	if (duplicate == false)
	{
		//if B is not already in the friend vector of A
		userList[A].friends.push_back(userList[B].id);
		userList[B].friends.push_back(userList[A].id);
		cout << "User " << userList[B].name << " added to " << userList[A].name << "'s friend list." << endl;
	}
	//otherwise, B is already in the friend vector of A
	else
	{
		cout << "User " << userList[B].name << " is already " << userList[A].name << "'s friend." << endl;
	}
}



int Database::getNumberRelations()
{
	//the number of relations can be determined by
	//summing the friends for each user, then dividing
	//by two (because if you are a friend of X, then X
	//must be your friend as well)

	int relations = 0;

	for (int i = 0; i < (int)userList.size(); i++)
	{
		relations += (int)userList[i].friends.size();
	}

	return (relations/2);
}

int Database::getUsers()
{
	return users;
}

void Database::printToFile(ofstream& fout)
{
	//print the list to file in the appropriate format
	fout << users;
	for (int i = 0; i < (int)userList.size(); i++)
	{
		fout << endl << userList[i].id << endl;
		fout << "\t" << userList[i].name << endl;
		fout << "\t" << userList[i].year << endl;
		fout << "\t" << userList[i].score << endl;
		fout << "\t";
		for (int j = 0; j < (int)userList[i].friends.size(); j++)
		{
			fout << userList[i].friends[j] << "\t";
		}
	}
}

void Database::outputLogin(char* name)
{
	//print the information when a user logs on
	int idCheck = this->getIndex(name);

	cout << "\nNumber of users: "  << this->getUsers()
		  << " Number of relations: " << this->getNumberRelations() << endl;
	cout << "User logged on:" << endl;
	cout << "User name:\t" << userList[idCheck].name << endl;
	cout << "Year: \t\t" << this->getYear(userList[idCheck].id) << endl;
	cout << "High Score:\t" << userList[idCheck].score << endl;
	cout << "Friends: \t";
	this->printFriendNames(userList[idCheck].id);
}

string Database::getYear(int id)
{
	//print the appropriate string based on the year
	int idCheck = this->getIndex(id);

	if (userList[idCheck].year == 1)
		return "Freshman";
	else if (userList[idCheck].year == 2)
		return "Sophomore";
	else if (userList[idCheck].year == 3)
		return "Junior";
	else if (userList[idCheck].year == 4)
		return "Senior";
	else
		return "5th Year Senior";
}

void Database::printFriendNames(int id)
{
	//print the names of a user's friends, separated by a comma
	int idCheck = this->getIndex(id);
	
	for (int i = 0; i < (int)userList[idCheck].friends.size(); i++)
	{
		if (i == (int)userList[idCheck].friends.size() - 1)
			cout << getName(userList[idCheck].friends[i]);
		else		
			cout << getName(userList[idCheck].friends[i]) << ", ";
	}
	cout << endl;
}

char* Database::getName(int id)
{
	//return the name associated with a user id
	int idCheck = this->getIndex(id);
	
	return userList[idCheck].name;
}

int Database::getId(char* name)
{
	//get the id associated with a user name
	if (this->userFound(name))
	{
		for (int i = 0; i < (int)userList.size(); i++)
		{
			if (strcmp(userList[i].name, name) == 0)
			{
				return userList[i].id;
			}
		}
	}
	//if we get here, the user name was not found in the database
	else
	{
		cout << "User " << name << " not found." << endl;
	}
	return -1;
}

int Database::getIndex(int id)
{
	//return the index of a specific id
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (userList[i].id == id)
			return i;
	}
	//if we get here, the id was not found
	return -1;
}

int Database::getIndex(char* name)
{
	//return the index of a specific name
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (strcmp(userList[i].name, name) == 0)
		{
			return i;
		}
	}
	//if we get here, the name was not found
	return -1;
}

void Database::setMaxId(int id)
{
	maxId = id;
}

int Database::getMaxId()
{
	return maxId;
}

void Database::printUsernames()
{
	//print the user names in the userlist
	cout << endl;
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (i == (int)userList.size() - 1)
			cout << userList[i].name;
		else
			cout << userList[i].name << ", ";
	}
	cout << endl;
}

User Database::getUser(char* name)
{
	//return the user object associated with a name
	for (int i = 0; i < (int)userList.size(); i++)
	{
		if (strcmp(userList[i].name, name) == 0)
		{
			return userList[i];
		}
	}
	User temp;
	return temp;
}

void Database::printByHighScore()
{
	//make a vector to store the sorted information
	vector<User> sorted;

	for (int i = 0; i < (int)userList.size(); i++)
	{
		int highScore = userList[i].score;
		
		//if the sorted vector is empty, add the first score to it
		if (sorted.empty())
			sorted.push_back(userList[i]);
		else
		{
			//otherwise, check to see where the score belongs
			bool inserted = false;
			for (int j = 0; j < (int)sorted.size() && !inserted; j++)
			{	
				if (highScore > sorted[j].score)
				{
					//if it is bigger than the next score in the list, insert it at the correct position
					sorted.insert(sorted.begin() + j, userList[i]);
					inserted = true;
				}
			}
			//if we get to the end of the sorted vector, insert the score
			if (inserted == false)
				sorted.push_back(userList[i]);
		}
	}

	cout << endl;

	//output the names and scores separated by tabs
	for (int i = 0; i < (int)sorted.size(); i++)
	{
			cout << sorted[i].name << "\t\t" << sorted[i].score << endl;
	}
	cout << endl;

}

void Database::printFriendsByScore(char* name)
{
	//create a vector to store the sorted values
	vector<User> sorted;

	//only add friends of the given user to this vector
	int index = this->getIndex(name);

	for (int i = 0; i < (int)userList[index].friends.size(); i++)
	{
		int friendIndex = getIndex(userList[index].friends[i]);
		int highScore = userList[friendIndex].score;
		if (sorted.empty())
			sorted.push_back(userList[friendIndex]);
		else
		{
			bool inserted = false;
			for (int j = 0; j < (int)sorted.size() && !inserted; j++)
			{	
				if (highScore > sorted[j].score)
				{
					sorted.insert(sorted.begin() + j, userList[friendIndex]);
					inserted = true;
				}
			}
			if (inserted == false)
				sorted.push_back(userList[friendIndex]);
		}
	}

	cout << endl;

	//print the sorted vector
	for (int i = 0; i < (int)sorted.size(); i++)
	{
			cout << sorted[i].name << "\t\t" << sorted[i].score << endl;
	}
	cout << endl;
}

void Database::deleteFriend(char* name1, char* name2)
{
	//get the indices of the two names
	int A = this->getIndex(name1);
	int B = this->getIndex(name2);
	bool friendFound = false;

	//if the name to be deleted isn't found, print an error message and return
	if (B == -1)
	{
		cout << "User " << name2 << " not found in " << name1 << "'s friend list." << endl;
		return;
	}

	//get the id's associated with the 2 names
	int idCheck = this->getId(name2);
	int idCheckA = this->getId(name1);

	//remove A from B's friend list
	//remove B from A's friend list
	for (int i = 0; i < (int)userList[A].friends.size(); i++)
	{
		if (userList[A].friends[i] == idCheck)
		{
			userList[A].friends.erase(userList[A].friends.begin() + i);		
			for (int j = 0; j < (int)userList[B].friends.size(); j++)
			{
				if (userList[B].friends[j] == idCheckA)
				{
					userList[B].friends.erase(userList[B].friends.begin() + j);
					cout << "User " << name2 << " removed from " << name1 << "'s friends list." << endl;
					friendFound = true;
				}
			}
		}
	}
	if (friendFound == false)
	{
		cout << "User " << name2 << " not found in " << name1 << "'s friend list." << endl;
	}
}

void Database::minPath(char* name1, char* name2)
{
	vector<User> path;
	//get the index into userList for the name1 name

	int name1Index = getIndex(name1);

	//get the index into userList for the name2 name

	int name2Index = getIndex(name2);

	if (name2Index == -1)
	{
		cout << "User " << name2 << " not found." << endl;
		return;
	}

	//use a queue-based Breadth Search First algorithm to find
	//the shortest path from the name1 to the name2

	vector<bool> visited (userList.size(), false);
	vector<int> rank (userList.size(), -1);

	vector<int> prev (userList.size(), -1);

	queue<int> bfs_queue;

	visited[name1Index] = true;
	rank[name1Index] = 0;
	bfs_queue.push(name1Index);

	while (!bfs_queue.empty())
	{
		int u = bfs_queue.front();
		bfs_queue.pop();

		for (int i = 0; i < (int)userList[u].friends.size(); i++)
		{
			int id = userList[u].friends[i];
			int v = getIndex(id);

			if (visited[v] == false)
			{
				visited[v] = true;
				rank[v] = rank[u] + 1;
				bfs_queue.push(v);
				prev[v]=u;
			}
		}		
	}

	//build the path from name1 to name2
	//If the rank at our destination node is -1, then
	//the node is unreachable
	
	if (rank[name2Index] == -1)
	{
		cout << "No path exists from " << name2 << " to " << name1 << "." << endl;
	}
	else
	{
		for (int node = name2Index; node != name1Index; node = prev[node])
		  path.push_back(userList[node]);

		path.push_back(userList[name1Index]);

		cout << "\nShortest path from " << name2 << " to " << name1 << " is:\t";
		for (int i = 0; i < (int)path.size(); i++)
		{
			if (i == (int)path.size() - 1)
				cout << getName(path[i].id);
			else		
				cout << getName(path[i].id) << ", ";
		}
		cout << endl;
	}

}

int Database::getScore(int index)
{
	return userList[index].score;
}

void Database::setScore(int score, int index)
{
	//set the high score and print a message
	if (score > userList[index].score)
	{
		userList[index].score = score;
		cout << "\nCongratulations! You set a new high score of " << score << "!" << endl;
	}
}

bool Database::friendIsBi(int id, int friendId)
{
	//find the friendId in userList and then search his friends

	int index = getIndex(friendId);

	if (index == -1)
		return false;  //friendId not found in userList

	//we found the friend, loop through his friends to make
	//sure "id" is in his friend list

	for (int i = 0; i < userList[index].friends.size(); i++)
	{
		if (id == userList[index].friends[i])
			return true;  //our friend is bi
	}

	//if we get here, our friend is not bi

	return false;
}

int Database::isEverybodyBi()
{
	//loop through all users making sure they have bi friends

	for (int i = 0; i < (int)userList.size(); i++)
	{
		int id = userList[i].id;

		//loop through this user's friends to make sure they are bi

		for (int j = 0; j < (int)userList[i].friends.size(); j++)
		{
			int friendId = userList[i].friends[j];

			if (!friendIsBi (id, friendId))
			{
				cout << "\nUser Id " << id << " has friend id " << friendId << " who is not bidirectional.\n";
				return -1;
			}
		}
	}

	//if we get here, all friends are bi!

	return 0;
}
