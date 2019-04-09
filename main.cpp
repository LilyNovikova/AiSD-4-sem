#include "ListTree.h"

using namespace std;

int main()
{
	ListTree huff;

	char* code, *mess;
	try
	{
		code = huff.code((char*)"it is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change");
		cout << "code: " << code << endl;
		mess = huff.decode(code);
		cout << "mess: " << mess << endl;

		cout << "alphabet:";
		(huff.get_alphbet())->output_list();
		cout << "coding tree: " << endl;
		huff.output_tree();
	}
	catch (invalid_argument e)
	{
		cout << e.what() << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
	_getch();
	return 0;
}