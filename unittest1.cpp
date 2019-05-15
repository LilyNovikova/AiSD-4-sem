#include "stdafx.h"
#include "CppUnitTest.h"
#include "../lab4_3_3/HuffmanTree.h"

using namespace std;

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

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		//it is a test string
		TEST_METHOD(test_string)
		{
			HuffmanTree huff;
			char* message = (char*)"it is a test string";
			char* code = huff.code(message);
			char* new_message = huff.decode(code);
			Assert::AreEqual(0, compare_str(message, new_message));
		}

		//it is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change
		TEST_METHOD(darwin_quote)
		{
			HuffmanTree huff;
			char* message = (char*)"it is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change";
			char* code = huff.code(message);
			char* new_message = huff.decode(code);
			Assert::AreEqual(0, compare_str(message, new_message));
		}
		//empty message
		TEST_METHOD(empty_string)
		{
			HuffmanTree huff;
			char* message = (char*)"";
			try
			{
				char* code = huff.code(message);
			}
			catch (invalid_argument e)
			{
				cout << e.what();
				Assert::AreEqual("Message to code is empty", e.what());
			}
		}

		//aaaaaaaaaaaa
		TEST_METHOD(aaaaaa)
		{
			HuffmanTree huff;
			char* message = (char*)"aaaaaaaaaaaa";
			char* code = huff.code(message);
			char* new_message = huff.decode(code);
			Assert::AreEqual(0, compare_str(message, new_message));
		}

		//a
		TEST_METHOD(one_letter)
		{
			HuffmanTree huff;
			char* message = (char*)"a";
			char* code = huff.code(message);
			char* new_message = huff.decode(code);
			Assert::AreEqual(0, compare_str(message, new_message));
		}

	};
}