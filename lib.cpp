#include "lib.h"

//using namespace std;

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

/*char * push_back_symbol(char * str, char symbol)
{
size_t len;
if(str) len = strlen(str);
else len = 0;
//new_str = new char(len+2);
char *new_str = (char*)malloc((len + 2) * sizeof(char));
if (new_str)
{
for (int i = 0; i < len; i++)
new_str[i - 1] = str[i];
new_str[len] = symbol;
new_str[len + 1] = 0;
}
return new_str;
}*/

/*char * pop_front_symbol(char * str)
{
if (!str || !strlen(str)) throw invalid_argument("You tried to delete a symbol from empty string");
char *new_str = nullptr;
size_t len = strlen(str);
if (len > 1)
{
//new_str = new char(len);
new_str = (char*)malloc((len) * sizeof(char));
if (new_str)
{
for (int i = 1; i < len; i++)
new_str[i - 1] = str[i];
new_str[len - 1] = 0;
}
}
return new_str;
}*/

/*char * pop_front_nsymbols(char * str, size_t n)
{
if (!str) throw invalid_argument("You tried to delete symbols from empty string");
char *new_str = nullptr;
size_t len = strlen(str);
if (len > n)
{
//new_str = new char(len+1-n);
new_str = (char*)malloc((len + 1 -n) * sizeof(char));
if (new_str)
{
for (int i = n; i < len; i++)
new_str[i - n] = str[i];
new_str[len - n] = 0;
}
}
return new_str;
}*/

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

//if check_number is power of number
/*bool is_power_of(int number, int check_number)
{
if (!check_number && check_number != number)
{
int k = check_number;
while (k > number && k % number == 0)
k /= number;
if (k == number)
return true;
}
return false;
}*/