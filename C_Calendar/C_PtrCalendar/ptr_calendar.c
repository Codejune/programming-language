#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define NONE -1

int*** arr;
int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

void setArr(void) {
	int i, j;
	int*** first_cursor;
	int** second_cursor;
	arr = (int***)calloc(12, sizeof(int**));
	first_cursor = arr;
	for (i = 0; i < 12; i++) {
		*first_cursor = (int**)calloc(6, sizeof(int*));
		second_cursor = *first_cursor;
		first_cursor++;
		for (j = 0; j < 6; j++) {
			*second_cursor = (int*)calloc(7, sizeof(int));
			second_cursor++;
		}
	}
}

int isLeap(int year) {
	/*
	1) 4년으로 나뉘면 윤달(2/29)존재.
	2) 그러나 100년으로도 나뉘면 윤달 없음.
	3) 또한 400년으로 나뉘면 윤달 존재
	*/
	if ((year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0))
		return TRUE;
	else return FALSE;
}

int countDay(int year) {
	int sum = 365;
	int i;
	for (i = 1; i < year; i++)
		if (isLeap(i))
			sum += 366;
		else sum += 365;
	return sum;
}

void assignCalendar(int year, int sum) {
	int i, j, k;
	int*** first_cursor = arr;
	int** second_cursor;
	int* third_cursor;
	int none_count = -1;
	int total_count = 0;

	// 1월1일 무슨 요일인지 계산
	k = sum % 7;
	//시작 요일에 맞춰 정렬
	for (i = 0; i < 12; i++) {
		second_cursor = *first_cursor;
		third_cursor = *second_cursor;
		for (j = 0; j < k; j++) {
			*third_cursor = NONE;
			third_cursor++;
		}
		if (isLeap(year) && i == 1)
			sum += 29;
		else sum += basicyear[i];
		first_cursor++;
		k = sum % 7;
	}

	first_cursor = arr;
	for (i = 0; i < 12; i++) {
		second_cursor = *first_cursor;
		for (j = 0; j < 6; j++) {
			third_cursor = *second_cursor;
			for (k = 0; k < 7; k++) {
				if(isLeap(year)){
						if(((total_count - none_count) > 29) && (i == 1)) break;
						else if((total_count - none_count) > basicyear[i] && i != 1) break;
				}
				else if((total_count - none_count) > basicyear[i]) break;  
				if (*third_cursor == NONE) {
					none_count++;
				} else {
					*third_cursor = total_count - none_count;
				}
				total_count++;
				third_cursor++;

			}
			second_cursor++;
		}
		first_cursor++;
		total_count = 0;
		none_count = -1;
	}
}

int printCalendar(int year) {
	int*** first_cursor;
	int** second_cursor;
	int* third_cursor;
	int i, j, k, m;
	int month = 1;
	int day = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			printf("                         %d                           ", month++);
		printf("\n");
		for (j = 0; j < 4; j++)
			printf("SUN     MON     TUS     WED     THU     FRI     SAT  ");
		printf("\n");
		for (j = 0; j < 4; j++)
			printf("===================================================  ");
		printf("\n");

		for (j = 0; j < 6; j++) {
			first_cursor = arr;
			for (k = 0; k < i * 4; k++)
				first_cursor++;
			for (k = (i * 4); k < i * 4 + 4; k++) {
				second_cursor = *first_cursor;
				for (m = 0; m < j; m++)
					second_cursor++;
				third_cursor = *second_cursor;
				for (m = 0; m < 7; m++) {
					if (*third_cursor == NONE || *third_cursor == 0) {
						if (m == 6) printf("   ");
						else printf("        ");
						third_cursor++;
						continue;
					}
					else {
						if ((*third_cursor / 10) > 0)
							printf(" ");
						else printf("  ");
						printf("%d", *third_cursor);
						if (m != 6)
							printf("     ");
						third_cursor++;
					}
				}
				first_cursor++;
				printf("  ");
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

int main(void) {
	int year;
	setArr();
	while (1) {
		printf("Programming Language assignment #2(Exit : -1)\n");
		printf("Year (ex.2020): ");
		scanf("%d", &year);
		if (year == NONE) break;
		assignCalendar(year, countDay(year));
		printCalendar(year);
	}
	return 0;
}
