#include "List.h"
#include"Node.h"


using namespace std;

int main()
{
	List<int> list = List<int>();
	int i = 1;
	list.push_back(i);
	list.push_back(1);
	list.push_back(1);
	list.push_back(1);
	cout << list;
	system("pause");
	return 0;
}