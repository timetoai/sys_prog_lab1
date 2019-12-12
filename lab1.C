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
int (*comparator)(const char*, const char*);
void qs(char** s_arr, int first, int last);
void swap(char** s1,  char** s2);
FILE *fi = stdin, *fo = stdout;


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

	if (argv[optind])
	{
		if ((fi = fopen(argv[optind], "r")) == NULL)
		{
			printf("Can't open file for input");
			exit(1);
		}
		if (argv[optind + 1])
			if ((fo = fopen(argv[optind + 1], "w")) == NULL)
			{
				printf("Can't open file for output");
				exit(1);
			}
	}

	//Считывание строк
	int len = 1000;
	char *buf = (char*) malloc(len), **ptr = NULL; if (buf == NULL) display_mem_err();
	int ch_count = 0, str_count = 0;
	char *line = NULL;
	while(fgets(buf, len, fi))
	{
		int buf_len = strlen(buf);
		line = (char*) realloc(line, buf_len + ch_count + 1); if (line == NULL) display_mem_err();
		strcpy(line + ch_count, buf);
		ch_count += buf_len;
		if (strchr(buf, '\n'))
		{
			ptr = (char**) realloc(ptr, (str_count + 1)*sizeof(char*)); if (ptr == NULL) display_mem_err();
			*(ptr + str_count) = (char*) malloc(ch_count + 1); if (*(ptr + str_count) == NULL) display_mem_err();
			strcpy(*(ptr+str_count), line);
			free(line);
			line = NULL;
			str_count++;
			ch_count = 0;
		}
	}
	free(buf);

	// Задание функции для сравнения с учётом введенных ключей
	if (ignore_case) 
	{
		comparator = strcasecmp;
	}
	else 
	{
		comparator = strcmp;
	}
	// Сортировка строк
	for (int i = 0; i < str_count; i++)
		for (int j = 0; j < str_count; j++)
			if ((i<j) && strcasecmp(ptr[i], ptr[j]) > 0) 
				swap(&ptr[i], &ptr[j]);
				
	//Вывод уникальных строк
	for (int i = 0; i < str_count; i++)
	{
		while ((i + 1 < str_count) && (comparator(ptr[i],ptr[i+1]) == 0)) i++;
		if (i && (i + 1 < str_count) && comparator(ptr[i], ptr[i+1]) != 0 && comparator(ptr[i], ptr[i-1]) != 0) fputs(ptr[i], fo);
		if ((i == 0) && comparator(ptr[i],ptr[i+1]) != 0) fputs(ptr[i], fo);
		if ((i + 1 == str_count) && comparator(ptr[i-1], ptr[i])) fputs(ptr[i], fo);
	}

	//Освобождение памяти, закрытие файлов
	if (fi != stdin)
	{
		fclose(fi);
	}
	if (fo != stdout)
	{
		fclose(fo);
	}
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
	printf("%s", "Usage: lab1 [-i] [input_file [output_file]]\r\nProgram takes array of strings and prints unique\r\nOptions:\r\n-i, ignore cases\r\n");
	exit(1);
}

// Вспомогательная функция дkя сортировки, меняет укзазатели на строки местами
void swap(char** s1, char** s2)
	{
		char* temp = *s1;
		*s1 = *s2;
		*s2 = temp;
	}