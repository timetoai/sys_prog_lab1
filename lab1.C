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
int strcmpi(const char* str1, const char* str2);
int (*comparator)(const char*, const char*);
void qs(char** s_arr, int first, int last);
void swap(char** s1,  char** s2);

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
	char **ptr = (char **) malloc(sizeof (char*));
	if (!ptr) {display_mem_err();}
	ptr[str_count] = (char *) malloc(sizeof(char[MAXLENGTH]));
	if (!ptr[str_count]) {display_mem_err();}
	
	// считывание строк
	while(fgets(ptr[str_count], MAXLENGTH, stdin))
	{
		str_count++;
		ptr = (char **) realloc(ptr, (str_count + 1) * sizeof (char*));
		ptr[str_count - 1] = (char *) realloc(ptr[str_count - 1], strlen(ptr[str_count - 1]) * sizeof(char));
		ptr[str_count] = (char *) malloc(sizeof(char[1000]));
		if (!(ptr && ptr[str_count - 1] && ptr[str_count])) {display_mem_err();}
	}

	// Задание функции для сравнения с учётом введенных ключей
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
		for (int j = i + 1; j < str_count; j++)
			if (comparator(ptr[i], ptr[j]) > 0) 
				swap(&ptr[i], &ptr[j]);
				
	//Вывод уникальных строк
	for (int i = 0; i < str_count; i++)
	{
		while ((i + 1 < str_count) && !comparator(ptr[i],ptr[i+1])) i++;
		if (i && comparator(ptr[i], ptr[i+1])) printf("%s", ptr[i]);
	}

	//Освобождение памяти
	for (int i = 0; i < str_count; i++)
	{
		free(ptr[i]);
	}
	free(ptr);
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
	printf("%s", "Usage: lab1 [-i]\r\nProgram takes array of strings and prints unique\r\nOptions:\r\n-i, ignore cases\r\n");
	exit(1);
}

// Сравнение строк без учёта регистра
int strcmpi(const char* str1, const char* str2)
{
	char *buf1 = (char*) malloc(strlen(str1) * sizeof(char));
	char *buf2 = (char*) malloc(strlen(str2) * sizeof(char));
	if (!(buf1 && buf2)) {display_mem_err();}
	strcpy(buf1, str1);
	strcpy(buf2, str2);

	for (int i = 0; i < strlen(buf1); i++)
	{
		if (isalpha(buf1[i]) && isupper(buf1[i])) {buf1[i] = tolower(buf1[i]);}
	}
	for (int i = 0; i < strlen(buf2); i++)
	{
		if (isalpha(buf2[i]) && isupper(buf2[i])) {buf2[i] = tolower(buf2[i]);}
	}

	int res = strcmp(buf1, buf2);
	free(buf1);
	free(buf2);
	return res;
}

// Вспомогательная функция дkя сортировки, меняет укзазатели на строки местами
void swap(char** s1, char** s2)
	{
		char* temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}