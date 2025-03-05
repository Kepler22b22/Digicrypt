#ifndef PRIME_UTILS_H
#define PRIME_UTILS_H

#include <cstdlib>
#include <ctime>

// Function to check if a number is prime
bool is_prime(long long n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Function to generate a large random prime number up to 1e6
long long generate_random_prime() {
    long long num;
    do {
        num = 100000 + (rand() % 900000); // Generate a number between 100000 and 999999
    } while (!is_prime(num));
    return num;
}

// Function to generate a random encryption exponent e that is coprime with (p-1)
long long generate_random_exponent(long long p) {
    long long e;
    do {
        e = 3 + (rand() % (p - 4)); // Ensure e is at least 3 and less than p-1
    } while (gcd(e, p - 1) != 1);
    return e;
}

#endif // PRIME_UTILS_H
