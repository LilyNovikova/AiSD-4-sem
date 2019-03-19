#include "List.h"
#include"Node.h"


using namespace std;

int main()
{
	List<int> list = List<int>();
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.insert(5, 0);
	cout << list;
	cout << "::" << endl;
	cout<<list.at(0);
	cout << list.at(1);
	cout << list.at(2);
	cout << list.at(3);
	system("pause");
	return 0;
}