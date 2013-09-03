#include <vector>
#include <fstream>
#include <string>
#include "user.h"
using namespace std;


class Database
{
	public:
		Database();
		~Database();
		bool validName(char*);
		bool validFriendId(int);
		bool validYear(int);
		bool validYear(char*);
		bool validScore(int);
		bool userUnique(char*);
		bool userUnique(int);
		bool userFound(char*);
		void addUser(char*, int, int);
		void deleteUser(char*);
		void addFriend(char*, char*);
		void deleteFriend(char*, char*);
		int getNumberRelations();
		int getUsers();
		void setMaxId(int);
		int getMaxId();
		string getYear(int);
		void printFriendNames(int);
		char* getName(int);
		int getIndex(int);
		int getIndex(char*);
		int getId(char*);
		User getUser(char*);
		int getScore(int);
		void setScore(int, int);

		bool  validId(int id);
		char* readFromFile(ifstream&);
		int   userCountFromFile(ifstream& fin, int& line_count);
		int   userIdFromFile(ifstream& fin, int& line_count);
		void  userNameFromFile(ifstream& fin, int& line_count, char* name);
		int   yearFromFile(ifstream& fin, int& line_count);
		int   scoreFromFile(ifstream& fin, int& line_count);
		int   friendsFromFile(ifstream& fin, int& line_count, vector<int>& friend_ids);
		
		void printToFile(ofstream& fout);
		void outputLogin(char*);
		void printUsernames();
		void printByHighScore();
		void printFriendsByScore(char*);
		void minPath(char*, char*);

		bool friendIsBi(int, int);
		int isEverybodyBi();
		

	private:
		vector<User> userList;
		int users, relations, maxId;
		char report[1024];

};