#include "Map.h"

int main()
{
	Map<char*, int> map;
	////
	int num[] = { 41, 67, 34, 0, 69,/*5*/ 24, 78, 58, 62, 64, /*2*/5, 45, 81, 27, 61, /*3*/91, 92, 42, 28, 36,/*4*/ 93, 4, 2, 53, 94 };
	char** keys = (char**)malloc(25 * sizeof(char*));
	for (size_t i = 0; i < 25; i++)
	{
		keys[i] = (char*)malloc(3 * sizeof(char));
		keys[i][0] = 'a' + num[i] / 10;
		keys[i][1] = 'a' + num[i] % 10;
		keys[i][2] = 0;
	}
	////

	for (size_t i = 0; i < 25; i++)
	{
		try
		{
			map.insert(keys[i], num[i]);
		}
		catch (invalid_argument e)
		{
			cout << e.what() << "; " << keys[i] << ';' << num[i] << endl;
		}
	}
	cout << endl;
	map.out();
	List<int> values_list = map.get_values();
	List<char*> keys_list = map.get_keys();
	cout << values_list<<endl;
	cout << keys_list;

	for (size_t i = 0; i < 25; i++)
	{

		int r = rand() % 25;
		cout << i << ") key: " << keys[r] <<", val: "<<num[r] << endl;
		try
		{
			map.remove(keys[r]);
		}
		catch (runtime_error e)
		{
			cout << e.what() << "; " << keys[r] << ';' << num[r] << endl;
		}
		//int check = root->black_height();
		if (map.is_ok()) cout << "OK" << endl;
		else
		{
			cout << ":(((";
			i = 25;
		}
	}

	_getch();
	return 0;
}