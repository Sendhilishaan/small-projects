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
	primes.nums[0] = 2;
	primes.count = 1;

	// 3 to n, not including even numbers
	numbers.nums = malloc(sizeof(int) * ((n+1) / 2) - 1);
	numbers.capacity = (n+1) / 2;
	numbers.count = 0;

	// sieve algorithm
	for (int p = 3; p <= n;) {

		primes.nums[primes.count] = p;
		primes.count++;
		
		for (int multiple = 3 * p; multiple <= n; multiple += 2 * p) {
			numbers.nums[(multiple - 3) / 2] = marked;
		}

		int p_check = p;

		for (int i = 2; p < n; i += 2) {
			if (numbers.nums[(p + i - 3) / 2] == unmarked) {
				p = p + i;
				break;
			}
		}

		if (p_check == p) { break; }

	}
	for (int x = 0; x < primes.count; x++) {
		printf("%d, ", primes.nums[x]);
	}

	free(numbers.nums);
	free(primes.nums);

	return 1;
}

