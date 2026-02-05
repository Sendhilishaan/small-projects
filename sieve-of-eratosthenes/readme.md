# Prime Number Generator

A C implementation of the Sieve of Eratosthenes algorithm for finding all prime numbers up to a given limit n.

## Algorithm Overview

The Sieve of Eratosthenes is an ancient algorithm for finding all primes up to a specified integer. It works by iteratively marking the multiples of each prime as composite, leaving only the primes unmarked.

### History

- Invented by Eratosthenes of Cyrene, a Greek mathematician, philosopher, poet, and musictheorist, around 240 BCE
- Eratosthenes was the chief librarian at the Library of Alexandria
- Eratosthenes was also famous for calculating the Earth's circumference with remarkable accuracy
- Remains one of the most efficient algorithms for finding all primes below a moderate limit

## Correctness Proof

- By FTA, every composite number has a prime factor p ≤ √n
- The algorithm marks all multiples of each prime p, ensuring every composite is marked
- Any unmarked number after processing all primes up to √n has no prime divisors less than or equal to √n, and therefore must itself be prime

### Storage for Prime Results

Uses the Rosser-Schoenfeld upper bound to estimate π(n), the number of primes less than or equal to n:

- For n < 17: π(n) ≤ n
- For n ≥ 17: π(n) < 1.26 × n / ln(n)

This ensures calloc allocates sufficient space without significant waste.
