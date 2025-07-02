#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Vigenere cipher alg on C
c_vigenere_naive_example

https://github.com/maxence-depire/vigenere-encryption/tree/main
https://www.sanfoundry.com/c-program-implement-vigenere-cypher/
https://www.geeksforgeeks.org/dsa/vigenere-cipher/
https://github.com/phillbush/vigenere
https://rosettacode.org/wiki/Vigen%C3%A8re_cipher
https://japp.io/cryptography/vigenere-cipher-algorithm-program-in-c-c/
https://www.cprograms4future.com/p/program-219-vigenere-cipher.html
*/

void upper_case(char *src) {
    while (*src != '\0') {
        *src = toupper(*src);
        src++;
    }
}

char* generate_key(const char *text, const char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);
    char *generated_key = (char*)malloc(text_len + 1);
    if (generated_key == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0, j = 0; i < text_len; ++i, ++j) {
        if (j == key_len) {
            j = 0;
        }
        generated_key[i] = key[j];
    }
    generated_key[text_len] = '\0';

    return generated_key;
}

char* vigenere(const char *text, const char *key, int encrypt) {
    int text_len = strlen(text);
    char *result = (char*)malloc(text_len + 1);
    if (result == NULL) {
        perror("memory alloc issue");
        exit(EXIT_FAILURE);
    }
    char *upper_text = strdup(text);
    char *upper_key = strdup(key);

    upper_case(upper_text);
    upper_case(upper_key);

    char *generated_key = generate_key(upper_text, upper_key);
    for (int i = 0; i < text_len; ++i) {
        if (isalpha(upper_text[i])) {
            int shift = encrypt ?
                (upper_text[i] - 'A') + (generated_key[i] - 'A') :
                (upper_text[i] - 'A') - (generated_key[i] - 'A');
            result[i] = (char)(((shift + 26) % 26) + 'A');
        } else {
            result[i] = upper_text[i];
        }
    }
    result[text_len] = '\0';
    free(upper_text);
    free(upper_key);
    free(generated_key);

    return result;
}

int main() {
    char *plaintext = "Simple Text";
    char *key = "somekey";

    char *ciphertext = vigenere(plaintext, key, 1);
    char *decrypted_text = vigenere(ciphertext, key, 0);

    printf("Text: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Cipher text: %s\n", ciphertext);
    printf("Decrypted text: %s\n", decrypted_text);

    free(ciphertext);
    free(decrypted_text);

    return 0;
}
