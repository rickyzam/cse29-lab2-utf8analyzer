#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


// checks if string is ascii or not 
uint8_t is_ascii(char string[]) {
        // Implement is_ascii in the body of this function!

	int final = 1;
	for(int i = 0; i<strlen(string); i++){
        	char c = string[i];
        	if (c>>7 != 0) {
        		final = 0;
			printf("%s", "Valid Ascii: false\n");
        		return final;
    		}
	}
	printf("%s", "Valid Ascii: true\n");
	return final;
}

//capitalises the string. 
void capitalize_ascii(char str[]) {
        // Implement capitalize_ascii in the body of this function!
	// int count = 0;
    	for (int i = 0; str[i] != '\0'; i++) {
        	if (str[i] >= 'a' && str[i] <= 'z') {
            	str[i] -= 32;
            	// count++;
        	}
    	}
	printf("Upgaraded ASCII: %s\n", str);
}

//finds length in no of byte
void length(char str[]){
	printf("Length in bytes: %lu\n", strlen(str));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
    is_ascii(argv[1]); // valid ascii or not 
    capitalize_ascii(argv[1]); //ugrading the string 
    length(argv[1]); // length of string in bytes.

}
