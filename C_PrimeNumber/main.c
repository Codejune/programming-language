#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define SECOND_TO_MICRO 1000000

void version_3(int input);
void version_4(int input);
void version_5(int input);
void assign5(int input);
void ssu_runtime(struct timeval *begin_t, struct timeval *end_t);
struct timeval begin_t, end_t;

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
		assign5(input);
		version_3(input);
		version_4(input);
		version_5(input);
	}
}

/**
 * @brief 다음 소수를 구할 때 n-1까지의 모든 수 대입
 */
void version_3(int input)
{
	int op = 3;
	int *prime = (int *)malloc(sizeof(int) * input);
	int prime_count = 0;
	bool is_prime;

	gettimeofday(&begin_t, NULL); // 측정 시작

	prime[prime_count++] = 2;
	while (prime_count <= input) {

		is_prime = true; // 소수 확인 변수 초기화

		for (int i = 2; i < op; i++) // 최적 소수 인덱스 범위까지만 비교
			if (op % i == 0) { // 소수로 나누어 떨어지는 경우 == 합성수
				is_prime = false;
				break;
			}

		if (is_prime) // 나누어 떨어지는 경우가 없음 == 소수
			prime[prime_count++] = op;

		op += 2; // 홀수만 탐색
	}

	gettimeofday(&end_t, NULL); // 측정 종료
#ifdef DEBUG
	for (int i = 0; i < input; i++)
		printf("%-d ", prime[i]);
#endif
	printf("\nversion-3 complete\n");
	ssu_runtime(&begin_t, &end_t);
	free(prime);
}

/**
 * @brief 다음 소수를 구할 때 n-1까지의 모든 소수 대입
 */
void version_4(int input)
{
	int op = 3;
	int *prime = (int *)malloc(sizeof(int) * input);
	int prime_count = 0 ;
	bool is_prime;

	gettimeofday(&begin_t, NULL); // 측정 시작

	prime[prime_count++] = 2;
	while (prime_count <= input) {

		is_prime = true;

		for (int i = 0; i < prime_count; i++)
			if (op % prime[i] == 0) {
				is_prime = false;
				break;
			}

		if (is_prime)
			prime[prime_count++] = op;

		op += 2;
	}

	gettimeofday(&end_t, NULL);
#ifdef DEBUG
	for(int i = 0; i < input; i++)
		printf("%-d ", prime[i]);
#endif
	printf("\nversion-4 complete\n");
	ssu_runtime(&begin_t, &end_t);
	free(prime);
}

/**
 * @brief 다음 소수를 구할 때 m까지의 소수로만 대입해보기
 */
void version_5(int input)
{
	struct timeval begin_t, end_t;
	int op = 3;
	int limit_idx = 1; // 최적 소수 인덱스 범위
	int prime_count = 0; // 소수 개수 
	int *prime = (int *)malloc(sizeof(int) * input);
	bool is_prime; // 소수 확인 변수


	gettimeofday(&begin_t, NULL); // 측정 시작

	prime[prime_count++] = 2; // 소수 초기값 저장
	while (prime_count <= input) { // 소수 탐색

		is_prime = true; // 소수 확인 변수 초기화

		if (sqrt(op) == prime[limit_idx]) // 소수 판단 시 lim 범위 증가
			limit_idx++;

		for (int i = 0; i < limit_idx; i++) // 최적 소수 인덱스 범위까지만 비교
			if (op % prime[i] == 0) { // 소수로 나누어 떨어지는 경우 == 합성수
				is_prime = false;
				break;
			}


		if (is_prime) // 소수로 나누어 떨어지는 경우가 없음 == 소수
			prime[prime_count++] = op;

		op += 2; // 홀수만 탐색
	}

	gettimeofday(&end_t, NULL); // 측정 종료
#ifdef DEBUG
	for (int i = 0; i < input; i++)
		printf("%-d ", prime[i]);
#endif
	printf("\nversion-5 complete\n");
	ssu_runtime(&begin_t, &end_t);
	free(prime);
}

void assign5(int input)
{
	int num;
	int denom;

	gettimeofday(&begin_t, NULL); // 측정 종료
	num = denom = 2;
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

	gettimeofday(&end_t, NULL); // 측정 종료
	printf("\nassignment 5 algorithm complete\n");
	ssu_runtime(&begin_t, &end_t);

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
