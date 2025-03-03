#include <openssl/evp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#define AES_BLOCK_SIZE 16  // AES block size is 16 bytes

void decryptAES(const std::string &inputFile, const std::string &outputFile) {
    std::ifstream ifp(inputFile, std::ios::binary);
    if (!ifp) {
        throw std::runtime_error("Error opening input file.");
    }

    std::ofstream ofp(outputFile, std::ios::binary);
    if (!ofp) {
        throw std::runtime_error("Error opening output file.");
    }

    std::vector<unsigned char> indata(AES_BLOCK_SIZE);
    std::vector<unsigned char> outdata(AES_BLOCK_SIZE);

    unsigned char ckey[AES_BLOCK_SIZE] = {'t', 'h', 'i', 's', 'k', 'e', 'y', 'i', 's', 'v', 'e', 'r', 'y', 'b', 'a', 'd'};
    unsigned char ivec[AES_BLOCK_SIZE] = {'d', 'o', 'n', 't', 'u', 's', 'e', 't', 'h', 'i', 's', 'i', 'n', 'p', 'u', 't'};

    // Use OpenSSL EVP API
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cfb(), nullptr, ckey, ivec);

    int outlen = 0;
    while (ifp.read(reinterpret_cast<char *>(indata.data()), AES_BLOCK_SIZE) || ifp.gcount() > 0) {
        size_t bytesRead = ifp.gcount();

        EVP_DecryptUpdate(ctx, outdata.data(), &outlen, indata.data(), bytesRead);
        ofp.write(reinterpret_cast<char *>(outdata.data()), outlen);
    }

    EVP_DecryptFinal_ex(ctx, outdata.data(), &outlen);
    ofp.write(reinterpret_cast<char *>(outdata.data()), outlen);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    try {
        decryptAES("encrypted_output.txt", "decrypted_output.txt");
        std::cout << "Decryption completed successfully.\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}