#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define NONE -1

int arr[12][6][7] = { 0 };
int basicyear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

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
	int none_count = -1;
	int total_count = 0;

	// 1월1일 무슨 요일인지 계산
	k = sum % 7;
	//시작 요일에 맞춰 정렬
	for (i = 0; i < 12; i++) {
		for (j = 0; j < k; j++)
			arr[i][0][j] = NONE;

		if(isLeap(year) && i == 1)
			sum += 29;
		else sum += basicyear[i];

		k = sum % 7;
	}

	for (i = 0; i < 12; i++) {
		for (j = 0; j < 6; j++) {
			for (k = 0; k < 7; k++) {
				if (isLeap(year) && (total_count - none_count) > 29 && i == 1) break;
				if (!isLeap(year) && (total_count - none_count) > basicyear[i] || (total_count - none_count) > basicyear[i] && i != 1) break;
				if (arr[i][j][k] == NONE) {
					none_count++;
				} else {
					arr[i][j][k] = total_count - none_count;
				}
				total_count++;
			}
		}
		total_count = 0;
		none_count = -1;
	}
}

int printCalendar(int year) {
	int i, j, k, m;
	int month = 1;
	int day = 0;
	for (i = 0; i < 3; i++) {
		for(j = 0; j < 4; j++)
			printf("                         %d                           ", month++);
		printf("\n");
		for (j = 0; j < 4; j++)
			printf("SUN     MON     TUS     WED     THU     FRI     SAT  ");
		printf("\n");
		for (j = 0; j < 4; j++)
			printf("===================================================  ");
		printf("\n");

		for (j = 0; j < 6; j++){
			for (k = (i*4); k < i * 4 + 4; k++) {
				for (m = 0; m < 7; m++) {
					if (arr[k][j][m] == NONE || arr[k][j][m] == 0) {
						if (m == 6) printf("   ");
						else printf("        ");
						continue;
					} else {
						if ((arr[k][j][m] / 10) > 0)
							printf(" ");
						else printf("  ");
						printf("%d", arr[k][j][m]);
						if(m != 6) 
							printf("     ");
					}
				}
				printf("  ");
			}
			printf("\n");
		}
		printf("\n\n");
	}

	memset(arr, 0, sizeof(arr));
}

int main(void) {
	int year;

	while (1) {
		printf("Programming Language assignment #1(Exit : -1)\n");
		printf("Year (ex.2020): ");
		scanf("%d", &year);
		if (year == NONE) break;
		assignCalendar(year, countDay(year));
		printCalendar(year);
	}
	return 0;
}
