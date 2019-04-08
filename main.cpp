#include "ListTree.h"

using namespace std;

int main()
{
	ListTree huff;

	char* code = huff.code((char*)"it is a test string");
	
	cout << "code: " << code << endl;
	char* mess = huff.decode(code);
	cout << "mess: " << mess << endl;
	cout << "alphabet:";
	(huff.get_alphbet())->output_list();
	cout << "coding tree: " << endl;
	huff.output_tree();
	_getch();
	return 0;
}