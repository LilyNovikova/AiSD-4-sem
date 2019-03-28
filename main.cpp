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
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	cout << "List:" << endl;
	cout << list <<endl;
	cout << "List size" << endl;
	cout << list.get_size();
	list.insert(5, 0);
	cout << "List after insert(5,0)" << endl;
	cout << list <<endl;
	list.pop_front();
	cout << "List after pop_front" << endl;
	cout << list <<endl;
	list.push_back(9);
	cout << "List after push_back(9)" << endl;
	cout << list <<endl;
	list.at(3);
	cout << "List element #3" << endl;
	cout << list.at(3) <<endl;
	list.set(3, 0);
	cout << "List after set(3,0)" << endl;
	cout << list <<endl;
	list.remove(3);
	cout << "List after remove(3)" << endl;
	cout << list <<endl;

	_getch();
	return 0;
}