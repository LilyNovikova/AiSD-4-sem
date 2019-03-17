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

//���� ������ �� ������������ �������
char* str_in_sym(char c);

//����������� ������ �� ������ �������
char* str_by_sym(char c, char* s, int &j);

//������� ������ � �����
int str_to_int(char* s);

//����� � ������
char* int_to_str(int r);

//�������� ������
char* copy_str(char* s);

//����� ��������� � ������
int contain(char *str, char *pod);

char* const_to_string(char c[]);

//��������� �����
int compare_str(char* s1, char* s2);

//
//char** str_split(char* s, char p, int *n);

//����������� �����
char *con_str(char *c1, char *c2);

//���������� n �������� � ������
char* add_nchar(char c, int n, char* s);

//�������� �������� �������
char* cut_char(char c, char* s);