#include "HuffmanTree.h"

int main()
{
	std::ofstream fout;
	fout.open("fout.txt");

	HuffmanTree huff;
	char* message = (char*)"it is a test string";
	try
	{
		char* code = huff.code(message);
		/*char* new_message = huff.decode(code);
		cout << new_message;*/
		fout << message << endl;
		fout << code << endl;
		double ec = strlen(code) / strlen(message) / 8;
		fout << strlen(code) << "/ (" << strlen(message) << "*8) = " << ec << endl;
		huff.clear();
		cout << "_______________________";

		message = (char*)"it is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change";
		code = huff.code(message);
		fout << message<<endl;
		fout << code<<endl;
		ec = strlen(code) / strlen(message) / 8;
		fout << strlen(code) << "/ (" << strlen(message) << "*8) = " << ec << endl;
		huff.clear();
		cout << "_______________________";

		message = (char*)"of course it is happening in your head, but why on the earth should that mean it s not real?";
		code = huff.code(message);
		fout << message << endl;
		fout << code << endl;
		ec = strlen(code) / strlen(message) / 8;
		fout << strlen(code) << "/ (" << strlen(message) << "*8) = " << ec << endl;
		huff.clear();
		cout << "_______________________";
	}
	catch (invalid_argument e)
	{
		cout << e.what();
	}
	catch (runtime_error e)
	{
		cout << e.what();
	}
	fout.close();
	_getch();
	return 0;
}