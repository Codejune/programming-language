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
	int num, denom;
	struct timeval begin_t;
	struct timeval end_t;

	while (1) {
		printf("Input number of prime numbers(exit: -1): ");
		scanf("%d", &input);
		if(input < 0)
			break;

		num = denom = 2;
		gettimeofday(&begin_t, NULL); // 측정 시작
		for (int i = 0; i < input; i++)
			while (1) {
				if (num % denom == 0)
					if(num == denom) {
#ifdef DEBUG
						printf("%-d ",denom);
#endif
						num++;
						denom=2;
						break;
					} else {
						num++;
						denom=2;
					}
				else denom++;
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





