#include "basic.h"

int number_of_digits(int i)
{
	if (i == 0)
		return 1;
	int j = 0;
	if (i < 0)
		i = -i;
	for (; i > 0; j++, i /= 10);
	return j;
}

//
void print_nchar(char c, int n)
{
	for (int i = 0; i < n; i++)
		printf("%c", c);
}


//ввод строки до определнного символа
char* str_in_sym(char c)
{
	char a[25],
		g;
	int i = 0;

	do
	{
		g = _getche();
		if (g != c && g != 13)
		{
			a[i] = g;
			i++;
		}
	} while (g != c && i < 25);

	char* s = (char*)malloc((i + 1) * sizeof(char));
	for (int j = 0; j < i; j++)
		s[j] = a[j];
	if (i == 0)
		return NULL;
	s[i] = '\0';
	return s;
}

char * str_by_sym(char c, char * s, int& j)
{
	if (s == NULL) return NULL;
	int n = 0;
	char* s1 = NULL;
	if (j <= strlen(s))
	{
		char g;
		int k;
		for (int i = j; s[i] != c && i <= strlen(s); i++, j++)
		{

			k = i;
			s1 = (char*)realloc(s1, (n + 2) * sizeof(char));
			s1[n] = s[i];
			s1[n + 1] = '\0';
			n++;
		}
		g = s[k];
	}
	j++;
	return s1;

}

//перевод строки в число
int str_to_int(char* s)
{
	if (s == NULL)
		return NULL;

	if (*s == '\0')
		return NULL;

	int i = 0,
		n = 0,
		a = 0,
		sign;

	if (*s == '-')
	{
		sign = -1;
		i++;
	}
	else
		sign = 1;

	int flag = 1;

	do
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n *= 10;
			a = ((int)s[i]) - 48;
			n += a;
			i++;
		}
		else
		{
			n = NULL;
			flag = 0;
		}
	} while (s[i] != '\0' && flag);

	n *= sign;
	return n;
}

//
char* int_to_str(int r)
{
	char* s = NULL;
	int q = (r > 0) ? r : -r;
	if (q != NULL)
	{
		int i = 0;
		do
		{
			s = (char*)realloc(s, (i + 1) * sizeof(char));
			s[i] = q % 10 + 48;
			q /= 10;
			i++;
		} while (q > 0);
		//
		s = (char*)realloc(s, (i + 1) * sizeof(char));
		s[i] = '\0';
		//
		if (r < 0)
		{
			s = (char*)realloc(s, (i + 1) * sizeof(char));
			s[i] = '-';
			i++;
		}
		//
		s = (char*)realloc(s, (i + 1) * sizeof(char));
		s[i] = '\0';
		s = (char*)realloc(s, i * sizeof(char));
		//
		for (int j = 0; j < i / 2; j++)
		{
			char c = s[j];
			s[j] = s[i - j - 1];
			s[i - j - 1] = c;
		}
		s = (char*)realloc(s, (i + 1) * sizeof(char));
		s[i] = '\0';
	}
	return s;
}

//копирует строку
char* copy_str(char* s)
{
	char *str = NULL;

	if (s != NULL)
	{
		str = (char*)malloc((strlen(s) + 1) * sizeof(char));
		if (str != NULL)
		{
			int n = strlen(s);
			for (int i = 0; i < n; i++)
				*(str + i) = *(s + i);
			*(str + n) = '\0';
		}
		else
		{
			puts("Недостаточно памяти");
		}
	}
	return str;
}

//
int contain(char *str, char *pod)
{
	if (pod == NULL)
		return 1;
	if (str == NULL)
		return 0;
	int flag_find = 0;                //Флаг нахождения подстроки в строке
	for (int i = 0; ((i < strlen(str)) && !flag_find); i++)
	{
		int f_match = 0;            //Флаг нахождения несовпадения
		for (int j = 0; ((j < strlen(pod)) && !f_match); j++)
		{
			if (*(pod + j) != *(str + i + j)) f_match = 1;
		}
		if (!f_match) flag_find = 1;
	}
	return flag_find;
}

//перевод из const char* в char*
char* const_to_string(char c[])
{
	int n = strlen(c);
	char *s = (char*)malloc((n + 1) * sizeof(char));
	for (int i = 0; i < n; i++)
	{
		s[i] = c[i];
	}
	s[n] = '\0';

	return s;
}

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

char *con_str(char *c1, char *c2)
{
	int n1,
		n2;
	if (c1 == NULL)
		n1 = 0;
	else n1 = strlen(c1);
	if (c2 == NULL)
		n2 = 0;
	else n2 = strlen(c2);

	int n = n1 + n2;
	int i = 0;
	int j = 0;
	char *str = (char*)malloc((n + 1) * sizeof(char));

	if (n == 0)
		return NULL;
	while (i < n1)
		*(str + i++) = *(c1 + i);
	while (i + j < n)
		*(str + i + j++) = *(c2 + j);
	*(str + n) = '\0';
	return str;
}

char* add_nchar(char c, int n, char* s)
{
	if (s == NULL) return NULL;
	int len = n - strlen(s);
	char* new_s = (char*)malloc((len + 1) * sizeof(char));
	for (int i = 0; i < len; i++)
		new_s[i] = c;
	new_s[len] = '\0';
	return con_str(s, new_s);
}

char * cut_char(char c, char * s)
{
	char* s1 = NULL;
	if (s == NULL) return NULL;
	int i = 0;
	int n = 0;
	while (s[i] == c)
		i++;
	for (; i <= strlen(s) && n <= 25; i++)
		if (s[i] != c || s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
		{
			s1 = (char*)realloc(s1, (n + 2) * sizeof(char));
			s1[n] = s[i];
			s1[n + 1] = '\0';
			n++;
		}
	return s1;
}
