#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Lab4_2_1/Map.h"

//prints n symbols
char* print_nchar(char c, size_t n)
{
	char* str = (char*)malloc((n + 1) * sizeof(char));
	for (int i = 0; i < n; i++)
		str[i] = c;
	str[n] = 0;
	return str;
}

char * copy_str(char * str)
{

	char *new_str = nullptr;
	if (str)
	{
		new_str = new char(strlen(str) + 1);
		if (new_str)
		{
			for (int i = 0; i < strlen(str); i++)
				*(new_str + i) = *(str + i);
			*(new_str + strlen(str)) = '\0';
		}
	}
	return new_str;
}

char *con_str(char *str1, char *str2)
{
	int len1,
		len2;
	if (!str1)
		len1 = 0;
	else len1 = strlen(str1);
	if (!str2)
		len2 = 0;
	else len2 = strlen(str2);

	int len = len1 + len2;
	if (!len) return nullptr;
	int i = 0;
	int j = 0;
	char *str = (char*)malloc((len + 1) * sizeof(char));
	if (str)
	{
		while (i < len1)
			str[i++] = str1[i];
		while (i + j < len)
			str[i + j++] = str2[j];
		str[len] = '\0';
	}
	return str;
}

//if s1 = s2 returns 0, if s1 > s2 returns 1, if s1 < s2 returns -1 
int compare_str(char * s1, char * s2)
{
	if (!s1 && !s2)
		return 0;
	if (s1 && !s2)
		return 1;
	if (!s1 && s2)
		return -1;

	int len = strlen(s1) > strlen(s2) ? strlen(s2) : strlen(s1);

	for (int i = 0; i <= len; i++)
	{
		if (s1[i] > s2[i])
			return 1;
		if (s1[i] < s2[i])
			return -1;
	}
	return 0;
}

char * char_to_str(char c)
{
	char* str = nullptr;
	if (c == 0)
	{
		str = (char*)malloc(sizeof(char));
		str[0] = 0;
	}
	else
	{
		str = (char*)malloc(2 * sizeof(char));
		str[0] = c;
		str[1] = 0;
	}

	return str;
}

bool contain(char *str, char *substr)
{
	if (!substr)
		return 1;
	if (!str)
		return 0;
	int flag_find = 0;                //Флаг нахождения подстроки в строке
	for (int i = 0; ((i < strlen(str)) && !flag_find); i++)
	{
		int f_match = 1;            //Флаг совпадения строк
		for (int j = 0; ((j < strlen(substr)) && f_match); j++)
		{
			if (substr[j] != str[i + j]) f_match = 0;
		}
		if (f_match) flag_find = 1;
	}
	return flag_find;
}

void SetColor(ConsoleColors text, ConsoleColors background)//ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		//insert
		TEST_METHOD(insert)
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

			map.insert((char*)"ab", 1);
			Assert::IsTrue(map.is_ok());
		}

		TEST_METHOD(insert_twice)
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
			try
			{
				map.insert((char*)"aa", 0);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "This is key is already in tree");
			}
		}

		TEST_METHOD(insert_empty_key)
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
			try
			{
				map.insert((char*)"", 0);
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Empty key");
			}
		}

		//remove
		TEST_METHOD(remove)
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
			map.remove((char*)"aa");
			Assert::IsTrue(map.is_ok());
		}
		TEST_METHOD(remove_last)
		{
			Map<char*, int> map;

			map.insert((char*)"aa", 0);

			map.remove((char*)"aa");
			Assert::IsTrue(map.is_empty());
		}
		TEST_METHOD(remove_nonexisting)
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
			try
			{
				map.remove((char*)"ab");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Attemt of removing nonexisting element");
			}
		}
		TEST_METHOD(remove_empty_key)
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
			try
			{
				map.remove((char*)"");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Empty key");
			}
		}

		//find
		TEST_METHOD(find_empty_key)
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
			try
			{
				int val = map.find((char*)"");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "Key to find is empty");
			}
		}
		TEST_METHOD(find_nonexisting)
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
			try
			{
				int val = map.find((char*)"ab");
			}
			catch (invalid_argument e)
			{
				Assert::AreEqual(e.what(), "No such element in the map");
			}
		}
		TEST_METHOD(find)
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


			int val = map.find((char*)"aa");
			Assert::AreEqual(0, val);
		}
	};
}
