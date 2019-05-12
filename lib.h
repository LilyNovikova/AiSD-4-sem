#pragma once
#include "stdio.h"
#include "conio.h"
#include "cstdlib"
#include "iostream"
#include <string.h>
#include <stdexcept>
#include <stdlib.h>
#include<windows.h>

enum ConsoleColors
{
	Black = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	Red = 4,
	MAGENTA = 5,
	BROWN = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

using namespace std;

//print n chars
char* print_nchar(char c, size_t n);

//copy string
char* copy_str(char* str);

//join 2 strings
char *con_str(char *c1, char *c2);

//add a symbol to the tail of string
char* push_back_symbol(char* str, char symbol);

//cut a symbol from the head of string
char* pop_front_symbol(char* str);

//cut N symbols from the head of string
char* pop_front_nsymbols(char* str, size_t n);

//comparing strings
int compare_str(char* s1, char* s2);

//
char* char_to_str(char c);

//
bool contain(char *str, char *substr);

//
void SetColor(ConsoleColors text, ConsoleColors background);



/*std::ostream & operator <<(std::ostream & out, string str)
{
out << str.front();
return out;
}*/