#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define DEBUG
#define SECOND_TO_MICRO 1000000

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);

int main(void)
{
	int input;
	int num; // 소수 판별 대상
	int denom; // 나눌 수
	struct timeval begin_t;
	struct timeval end_t;

	while (1) {
		printf("Input number of prime numbers(exit: -1): ");
		scanf("%d", &input);
		if(input < 0)
			break;

		num = denom = 2;
		gettimeofday(&begin_t, NULL); // 측정 시작
		for (int i = 0; i < input; i++) // 출력할 소수의 개수 만큼 반복
			while (1) {
				if (num % denom == 0) //  나누었을 때 나머지가 0일 경우
					if (num == denom) { // 소수일 경우 (자신 이전에 나눌 수 있는 수가 없음)
#ifdef DEBUG
						printf("%-d ", denom); // 소수 출력
#endif
						num++; // 다음 수 탐색
						denom = 2; // denom 초기화
						break; // 다음 소수 탐색
					} else {  // 합성수일 경우 ( 자신 이전에 나눌 수 있는 수가 있음)
						num++; // 다음 수 탐색
						denom = 2; // denom 초기화
					}
				else denom++; // 모든 denom 탐색
			}
		printf("\nprocessing complete.\n");
		gettimeofday(&end_t, NULL);
		ssu_runtime(&begin_t, &end_t);
	}
}

void ssu_runtime(struct timeval *begin_t, struct timeval *end_t) // 실행시간 출력
{
	end_t->tv_sec -= begin_t->tv_sec;

	if(end_t->tv_usec < begin_t->tv_usec){
		end_t->tv_sec--;
		end_t->tv_usec += SECOND_TO_MICRO;
	}

	end_t->tv_usec -= begin_t->tv_usec;
	printf("Runtime: %ld:%06ld(sec:usec)\n", end_t->tv_sec, end_t->tv_usec);
}
