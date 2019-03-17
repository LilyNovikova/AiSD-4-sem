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
	cout << list;
	system("pause");
	return 0;
}