#include "ListTree.h"

using namespace std;

int main()
{
	ListTree huff;
	huff.add_to_alphabet((char*)"m", 1);
	huff.output_list();
	huff.add_to_alphabet((char*)"e", 2);
	huff.output_list();
	huff.add_to_alphabet((char*)"s", 2);
	huff.output_list();
	huff.add_to_alphabet((char*)"a", 1);
	huff.output_list();
	huff.add_to_alphabet((char*)"g", 1);
	huff.output_list();
	//huff.add_to_alphabet((char*)"a", 5);

	char* code = huff.code((char*)"message");
	huff.output_tree();
	cout << "code: " << code << endl;
	char* mess = huff.decode(code);
	cout << "mess: " << mess << endl;
	cout << "coding tree: " << endl;
	
	_getch();
	return 0;
}