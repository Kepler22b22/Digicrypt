#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "cipher.h"
#include "prime_utils.h"

int main() {
    srand(time(0)); // Seed random number generator

    // Generate random prime modulus and encryption exponent
    long long p = generate_random_prime();
    long long e = generate_random_exponent(p);

    // Compute decryption exponent
    long long d = mod_inverse(e, p - 1);

    std::cout << "Generated Prime Modulus (p): " << p << std::endl;
    std::cout << "Generated Encryption Exponent (e): " << e << std::endl;
    std::cout << "Computed Decryption Exponent (d): " << d << std::endl;

    // Read input message
    std::string message = read_from_file("../../input.txt");
    std::vector<long long> plaintext_numbers = text_to_numbers(message);

    // Encrypt message
    std::vector<long long> ciphertext = encrypt(plaintext_numbers, e, p);

    // Save encrypted message to a date-based output file
    std::string filename = get_current_date_filename();
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: Cannot write to file " << filename << std::endl;
        return 1;
    }
    for (long long num : ciphertext) {
        outfile << num << " ";
    }
    outfile.close();

    std::cout << "Encrypted message saved to " << filename << std::endl;

    // Decrypt the message
    std::vector<long long> decrypted_numbers = decrypt(ciphertext, d, p);
    std::string decrypted_text = numbers_to_text(decrypted_numbers);

    // Print decrypted text
    std::cout << "Decrypted Text: " << std::endl << decrypted_text << std::endl;

    return 0;
}