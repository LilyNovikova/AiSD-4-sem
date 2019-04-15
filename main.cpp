#include "ListTree.h"

using namespace std;

int main()
{
	ListTree huff;

	char* message = (char*)"it is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change";
	char* code, *mess;
	try
	{
		code = huff.code(message);
		//cout << "code: " << code << endl;
		mess = huff.decode(code);
		//cout << "mess: " << mess << endl;

		//cout << "alphabet:";
		//(huff.get_alphbet())->output_list();
		//cout << "coding tree: " << endl;
		//huff.output_tree();
		if (compare_str(message, mess) == 0) cout << "ok";
		else cout << "error";
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