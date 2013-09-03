#include <QDesktopWidget>
#include <QApplication>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <string>
#include "spacewars.h"
#include "database.h"
using namespace std;

//set window size and center the window on the screen
void center(QWidget * widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 800;
  int HEIGHT = 700;
  

  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();
 
  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget->setGeometry(x, y, WIDTH, HEIGHT);
  widget->setFixedSize(WIDTH, HEIGHT);

  //set window background color to black
  QPalette pal;
  pal.setColor(QPalette::Background, Qt::black);
  widget->setAutoFillBackground(true);
  widget->setPalette(pal);
}


int main(int argc, char* argv[])
{
  QApplication app(argc, (char **) argv);  

  srand ( time(NULL) );
     
  char selection[125];
  char selection2[125];
  string userName, friendName;
  string year;
  int ret;
  Database DB;
  ifstream fin;
  ofstream fout;
  SpaceWars * window;

	//open the file, and read it
	fin.open("db.txt");
	char* status = DB.readFromFile(fin);
	if ((int)strlen(status) >0)
	{
		cout << status << endl;
	}
	fin.close();

	DB.isEverybodyBi();

  //loop, printing the top menu
  while (TRUE)
  {
	  cout << "\nNumber of users: "  << DB.getUsers()
		  << " Number of relations: " << DB.getNumberRelations() << endl; 
	  cout << "Please enter one of the following commands: " << endl;
	  cout << "(+) Add user account" << endl;
	  cout << "(-) Delete user account" << endl;
	  cout << "(l) Log onto user account" << endl;
	  cout << "(h) List all users sorted by high score" << endl;
	  cout << "(q) Quit" << endl;
	  cin >> selection;

	  //make sure that what the user entered was only 1 character
	  if (strlen(selection) > 1)
	  {
		  cout << "Please make a valid selection." << endl;
		  continue;
	  }


	  switch (selection[0])
	  {
		case '+':
			//add a user
			cout << "Enter user name: \t";
			cin.ignore();
			getline(cin, userName, '\n');
			if (!DB.validName((char*)userName.c_str())) 
				cout << "Please enter a valid user name.\n";
			else if (!DB.userUnique((char*)userName.c_str()))
				cout << "Please enter a unique user name.\n";
			else
			{
				cout << "Enter year: \t\t";
			
				getline(cin, year, '\n');
				if (!DB.validYear((char*)year.c_str()))
					cout << "Please enter a valid year.\n";
				else
				{
					DB.addUser((char*)userName.c_str(), DB.getMaxId() + 1, atoi((char*)year.c_str()));
					DB.setMaxId(DB.getMaxId() + 1);
					cout << userName << " successfully added!" << endl;
				}
			}
			break;
		case '-':
			//delete a user
			cout << "Enter user name: \t";
			cin.ignore();
			getline(cin, userName, '\n');
			DB.deleteUser((char*)userName.c_str());
			break;
		case 'l':
			//log the user on if the name is found in the userList
			cout << "Enter user name: \t";
			cin.ignore();
			getline(cin, userName, '\n');
			if (DB.userFound((char*)userName.c_str()))
			{
				DB.outputLogin((char*)userName.c_str());
				bool loggedOn = TRUE;

				//loop, printing the logged on menu
				while (loggedOn == TRUE)
				{
				cout << "\nPlease Enter one of the following commands: " << endl;
				cout << "(a) List all usernames" << endl;
				cout << "(f) Add a friend for " << userName << endl;
				cout << "(d) De-friend one of " << userName << "'s friends" << endl;
				cout << "(s) Sort all " << userName << "'s friends by high score" << endl;
				cout << "(h) List all users sorted by high score" << endl;
				cout << "(b) Shortest-path to " << userName << " from any user" << endl;
				cout << "(p) Play game" << endl;
				cout << "(x) Log off" << endl;
				cin >> selection2;

				//print an error message if the user's selection is more than one character
				if (strlen(selection2) > 1)
				{
					cout << "Please make a valid selection." << endl;
					continue;
				}

				int index;
				int highScore;

					switch (selection2[0])
					{
						case 'a':
							//list all usernames
							DB.printUsernames();
							break;
						case 'f':
							//add the friend
							cout << "Enter user name: \t";
							cin.ignore();
							getline(cin, friendName, '\n');
							DB.addFriend((char*)userName.c_str(), (char*)friendName.c_str());
							break;
						case 'd':
							//delete the friend
							cout << "Enter user name: \t";
							cin.ignore();
							getline(cin, friendName, '\n');
							DB.deleteFriend((char*)userName.c_str(), (char*)friendName.c_str());
							break;
						case 's':
							//sort the user's friendlist by high score
							DB.printFriendsByScore((char*)userName.c_str());
							break;
						case 'h':
							//print user vector, sorted by high scores
							DB.printByHighScore();
							break;
						case 'b':
							//shortest path to current user
							cout << "Enter user name: \t";
							cin.ignore();
							getline(cin, friendName, '\n');
							DB.minPath((char*)userName.c_str(), (char*)friendName.c_str());
							break;
						case 'p':
							//initialize the window
							window = new SpaceWars;
							window->setWindowTitle("Space Wars");
							window->show();
							center(window);
							ret = app.exec();
							//check and set the high score
							index = DB.getIndex((char*)userName.c_str());
							highScore = window->updateScore(DB.getScore(index));
							DB.setScore(highScore, index);
							delete window;
							break;
						case 'x':
							//log off
							loggedOn = FALSE;
							break;
						default:
							//print error message
							cout << "Sorry, please make a valid selection." << endl;
							break;
					}
				}
			}
			//don't log on if the user doesn't exist
			else
			{
				cout << "User " << userName << " not found." << endl;
			}
			break;
		case 'h':
			//print user vector, sorted by high scores
			DB.printByHighScore();
			break;
		case 'q':
			//write to file and exit the program
			fout.open("db.txt");
			DB.printToFile(fout);
			fout.close();
			return 0;
			break;
		default:
			//print error message
			cout << "Sorry, please make a valid selection." << endl;
			break;
	  }

  }

  return ret;
}
