#include <vector>
using namespace std;

class User
{
	public:
		User();
		~User();
		int id, year, score;
		char name[128];
		vector<int> friends;
};