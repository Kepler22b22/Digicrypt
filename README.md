# Author: Muqi Zhang
# Date: Mar 4 2025

"""My digital diary, safely locked away... or is it? If you can break the code, you deserve to read them :D """

This toolkit provides a simple and efficient way to encrypt and decrypt messages using modular exponentiation. The encryption is based on a randomly generated prime modulus and encryption exponent.

# Files Included

* cipher.h – Core encryption and decryption functions.

* prime_utils.h – Random prime and encryption exponent generation utilities.

* main.cpp – Example implementation demonstrating encryption and decryption.

# How It Works

1. A random prime modulus (p) and encryption exponent (e) are generated.

2. The decryption exponent (d) is computed.

3. The input message is encrypted using p and e.

4. The encrypted message is saved to a date-based file.

5. The encrypted message is decrypted using d to verify correctness. 

# Compilation and Usage

* Compile the Program

  mkdir build && cd build

  cmake ..

  make

* Alternatively, compile using g++:

  g++ main.cpp -o encryption_tool

* Run the Program

  ./encryption_tool

The program reads an input message from input.txt, encrypts it, and saves the encrypted output to a file based on the current date.

# Example Workflow

1. Create an input.txt file with the message you want to encrypt.

2. Run the program.

3. Note the generated (p, e, d) values for future decryption.

4. Check the saved encrypted file.

5. Verify decryption by checking the output printed on the screen.

# Future Enhancements

* Support for larger prime numbers.

* Improved key management.

* Integration with real-world cryptographic applications.

# License

This project is open-source. Feel free to use and modify it!
