#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// prints a substring of the input string containing only the first 6 codepoints
// 

void encode_utf8(uint32_t num, char dest[]);
void first6Substring(const char str[])
{
    const char *p = str;
    int cp_index = 0;
    const char *byte_start = NULL;
    const char *byte_end = NULL;

    while (*p) {
        if ((unsigned char)*p < 0x80 || ((*p & 0xC0) != 0x80)) {
            // new codepoint start
            if (cp_index == 0) {
                byte_start = p;
            }
            if (cp_index == 6) {
                byte_end = p;
                break;
            }
            cp_index++;
        }
        p++;
    }

    if (!byte_start) {
        byte_start = p;
    }
    if (!byte_end) {
        byte_end = p;
    }

    size_t len = byte_end - byte_start;
    char buffer[len + 1];
    memcpy(buffer, byte_start, len);
    buffer[len] = '\0';

    printf("%s\n", buffer);
}

void incCdptAtIndex3(const char str[])
{
	
}

void animalEmojis(const char str[])
{
    const unsigned char *p = (const unsigned char *)str;
    int cp_count = 0;
    char dest[100] = {};

    while (*p) {
            uint32_t codepoint = 0;
            if (*p < 0x80) {
                codepoint = *p;
            } else if ((*p & 0xE0) == 0xC0) {
                codepoint = (*p & 0x1F) << 6;
                p++;
                codepoint |= (*p & 0x3F);
            } else if ((*p & 0xF0) == 0xE0) {
                codepoint = (*p & 0x0F) << 12;
                p++;
                codepoint |= (*p & 0x3F) << 6;
                p++;
                codepoint |= (*p & 0x3F);
            } else if ((*p & 0xF8) == 0xF0) {
                codepoint = (*p & 0x07) << 18;
                p++;
                codepoint |= (*p & 0x3F) << 12;
                p++;
                codepoint |= (*p & 0x3F) << 6;
                p++;
                codepoint |= (*p & 0x3F);
            }

            // check if animal emoji
            if ((codepoint >= 0x1F400 && codepoint <= 0x1F43F) ||
                (codepoint >= 0x1F980 && codepoint <= 0x1F9AE)) {
		    encode_utf8(codepoint, dest);
		    printf("%s ", dest);
            } else {
            }

        if (*p < 0x80) { 
            p++; 
        } else if ((*p & 0xE0) == 0xC0) { 
            p += 2; 
        } else if ((*p & 0xF0) == 0xE0) { 
            p += 3; 
        } else if ((*p & 0xF8) == 0xF0) { 
            p += 4; 
        } else { 
            // Invalid UTF-8, just skip this byte 
            p++; 
        } 
    }
    puts("\n");
}

void encode_utf8(uint32_t num, char dest[]) {
        //TODO: Complete this function

        const uint8_t leading_mask[5] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0 };

        if (num <= 0x7F)
        {
                dest[0] = num;
                dest[1] = dest[2] = dest[3] = 0;
                return;
        }

        int num_bytes;
        if (num <= 0x7FF) num_bytes = 2;
        else if (num <= 0xFFFF) num_bytes = 3;
        else if (num <= 0x10FFFF) num_bytes = 4;
        else
        {
                dest[0] = dest[1] = dest[2] = dest[3] = 0;
                return;
        }

        for (int i = num_bytes - 1; i > 0; i--) {
                dest[i] = (char)((num & 0x3F) | 0x80);
                num >>= 6;
        }

        dest[0] = (char)(leading_mask[num_bytes] | num);

        for (int i = num_bytes; i < 4; i++)
        {
                dest[i] = 0;
        }

}


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
    first6Substring(argv[1]);
    animalEmojis(argv[1]);

    // incCdptAtIndex3(argv[1]);
    // implement the UTF-8 analyzer here
}
