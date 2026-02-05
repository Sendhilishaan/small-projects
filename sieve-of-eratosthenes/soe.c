#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	size_t capacity;
	size_t count;
	int* nums;
} arr;

#define marked 1
#define unmarked 0

int main(int argc, char* argv[]) {
	if (argc != 2){
		printf("Usage: int n > 2");
		return 0;
	}

	int n = strtol(argv[1], NULL, 10);

	if (!(n > 2)) {
		printf("Usage: int n > 2");
		return 0;
	}

	arr numbers;
	arr primes;

	// Rosser and Schoenfeld bound for π(n)
	size_t approx_cap;
	if (n < 17) {
		approx_cap = n;
	}

	else {
		approx_cap = 1.26 * n / log(n);
	}

	primes.nums = calloc(approx_cap, sizeof(int));
	primes.capacity = approx_cap;
	primes.count = 0;

	// 3 to n, not including even numbers
	numbers.nums = malloc(sizeof(int) * ((n+1) / 2) - 1);
	numbers.count = (n+1) / 2;
	numbers.count = 0;

	// sieve algorithm
	for (int p = 3; p < n - (n % p); p += 2) {
		
	}

	return 1;
}

