#ifndef CIPHER_H
#define CIPHER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

// Function to get current date. eg. Mar03.txt
std::string get_current_date_filename() {
    // Get current date
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Define month abbreviations
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Format the filename as MonDD.txt (e.g., Mar03.txt)
    std::ostringstream oss;
    oss << months[ltm->tm_mon] << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << ".txt";
    
    return oss.str();
}


// Function to compute (base^exp) % mod using modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1;  // Divide exp by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

// Function to compute the Greatest Common Divisor (GCD)
long long gcd(long long a, long long b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// Function to compute modular inverse using Extended Euclidean Algorithm
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;  // Ensure positive result
    return x1;
}

// Function to convert a string into number blocks using ASCII values
std::vector<long long> text_to_numbers(const std::string &text) {
    std::vector<long long> numbers;
    size_t i = 0;
    
    while (i < text.size()) {
        if (text[i] == '\n') {
            numbers.push_back(-1);  // Special marker for empty lines
            i++;
        } else {
            long long num = static_cast<unsigned char>(text[i]) * 256;
            if (i + 1 < text.size() && text[i + 1] != '\n') {
                num += static_cast<unsigned char>(text[i + 1]);
                i++;
            }
            numbers.push_back(num);
            i++;
        }
    }
    
    return numbers;
}

// Function to convert number blocks back to text
std::string numbers_to_text(const std::vector<long long> &numbers) {
    std::string text;
    
    for (long long num : numbers) {
        if (num == -1) {
            text += '\n';  // Restore empty line
        } else {
            char first = static_cast<char>(num / 256);
            char second = static_cast<char>(num % 256);
            text += first;
            if (second >= 32 && second <= 126) text += second;
        }
    }
    
    return text;
}

// Encrypt function
std::vector<long long> encrypt(const std::vector<long long> &plaintext, long long e, long long p) {
    std::vector<long long> ciphertext;
    for (long long num : plaintext) {
        ciphertext.push_back(mod_exp(num, e, p));
    }
    return ciphertext;
}

// Decrypt function
std::vector<long long> decrypt(const std::vector<long long> &ciphertext, long long d, long long p) {
    std::vector<long long> plaintext;
    for (long long num : ciphertext) {
        plaintext.push_back(mod_exp(num, d, p));
    }
    return plaintext;
}

// Function to read text from a file
std::string read_from_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        exit(1);
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

// Function to write text to a file
void write_to_file(const std::string &filename, const std::string &content) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot write to file " << filename << std::endl;
        exit(1);
    }
    file << content;
    file.close();
}

#endif  // CIPHER_H