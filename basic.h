#pragma once
#include "stdio.h"
#include "conio.h"
#include "cstdlib"
#include "iostream"
#include <string.h>
#include <stdexcept>

//number of digits
int number_of_digits(int i);

//print n chars
void print_nchar(char c, int n);

//ввод строки до определнного символа
char* str_in_sym(char c);

//копирование строки до опредл символа
char* str_by_sym(char c, char* s, int &j);

//перевод строки в число
int str_to_int(char* s);

//число в строку
char* int_to_str(int r);

//копирует строку
char* copy_str(char* s);

//поиск подстроки в строке
int contain(char *str, char *pod);

char* const_to_string(char c[]);

//сравнение строк
int compare_str(char* s1, char* s2);

//
//char** str_split(char* s, char p, int *n);

//объединение строк
char *con_str(char *c1, char *c2);

//добавление n символов к строке
char* add_nchar(char c, int n, char* s);

//удаление повторов символа
char* cut_char(char c, char* s);