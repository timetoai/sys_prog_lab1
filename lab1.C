#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#define MAXLENGTH 1000

static const char *optString = "i";
int opt = 0;
bool ignore_case = false;
void display_usage();
void display_mem_err();
int strsmpi(const char* str1, const char* str2);

int main(int argc, char *argv[])
{
	// проверка наличия ключей
	opt = getopt(argc, argv, optString);
	while(opt != -1)
	{
		switch(opt)
		{
			case 'i':
				ignore_case = true;
				break;
			default:
				display_usage();
		}
		opt = getopt(argc, argv, optString);
	}

	int str_count = 0;
	char **ptr = (char **) malloc(sizeof (*char));
	if (!ptr) {display_mem_err();}
	
	// считывание строк
	if (!ptr[str_count]) {display_mem_err();}
	while(fgets(ptr[str_count], MAXLENGTH, stdin))
	{
		str_count++;
		ptr = (char **) realloc(ptr, (str_count + 1) * sizeof (*char));
		ptr[str_count - 1] = (char *) realloc(ptr[str_count - 1], strlen(ptr[str_count - 1]) * sizeof(char));
		ptr[str_count] = (char *) malloc(sizeof char[1000]);
		if (!(ptr && ptr[str_count - 1] && ptr[str_count])) {display_mem_err();}
	}

	// Задание функции для сравнения с учётом введенных ключей
	int (*comparator)(const char*, const char*);
	if (ignore_case) 
	{
		comparator = strcmpi;
	}
	else 
	{
		comparator = strcmp;
	}
	// Сортировка строк
	for (int i = 0; i < str_count; i++)
	{
		
	}
}

// В случае нехватки памяти выводит ошибку и прекращает работу
void display_mem_err()
{
	printf("%s", "\r\nNot enough memory for execution\r\n");
	exit(1);
}

// В случае ввода несуществующих ключей выводит справку об использовании
void display_usage()
{
	printf("%s", "\r\nUsage: lab1 - takes array of strings and prints unique\r\nOptions:\r\n-i, ignore cases\r\n");
	exit(1);
}

// Сравнение строк без учёта регистра
int strsmpi(const char* str1, const char* str2)
{
	char *buf1 = (char*) malloc(strlen(str1) * sizeof(char));
	char *buf2 = (char*) malloc(strlen(str2) * sizeof(char));
	if (!(buf1 && buf2)) {display_mem_err();}
	strcpy(buf1, str1);
	strcpy(buf2, str2);

	for (int i = 0; i < strlen(buf1); i++)
	{
		if (isalpha(buf1[i]) && isupper(buf1[i])) {buf1[i] = to_lower(buf1[i]);}
	}
	for (int i = 0; i < strlen(buf2); i++)
	{
		if (isalpha(buf2[i]) && isupper(buf2[i])) {buf2[i] = to_lower(buf2[i]);}
	}

	int res = strcmp(buf1, buf2);
	free(buf1);
	free(buf2);
	return res;
}