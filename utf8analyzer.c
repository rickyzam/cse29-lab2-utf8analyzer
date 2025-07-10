#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// prints a substring of the input string containing only the first 6 codepoints
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
	// printf("%s\n", *p);
    } else {
    }

        // next codepoint
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
        cp_count++;
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
uint8_t codepoint_size(char c) {
        if (c == '\0')
                return 0;
        int codepoint_size = 0;
        for(int j = 0;(c>>(7-j))&1!=0;j++){
                codepoint_size++;}
        if(codepoint_size==0){
                return 1;}
        if(1>codepoint_size>=4){
                return -1;}
        else{
                return codepoint_size;}
}

int32_t utf8_strlen(char str[]) {
        int count = 0;
        for(int i = 0; str[i]!='\0';i++){
                unsigned char byte = (unsigned char)str[i];
                if(byte<0x80||byte>0xBF){
                        count++;}
        }
        return count;
}
int32_t codepoint_at(char str[], int32_t byte_index) {
        int32_t result = 0;
        char first_byte = str[byte_index];
        if (((first_byte>>6)&3)==2){
                return -1;}
        else{
                uint8_t size = codepoint_size(first_byte);
                first_byte = first_byte << size;
                first_byte = first_byte >>size;
                result |= first_byte;
                for(int i = 1; i<size; i++){
                        result = result<<6;
                        result |= str[byte_index+i]&127;
                }
                return result;
        }
}
void utf8info(char string[]){
        printf("Number of Codepoints: %d\n", utf8_strlen(string));
        int count = 0;
        printf("Codepoints are: ");
        for(int i =0; i<sizeof(string); i++){
                unsigned char byte = (unsigned char)string[i];
                if (byte<0x80||byte>0xBF){
                        printf("%d ", codepoint_at(string, i));
                }
        }
        printf("\n");
        for(int i = 0; i<sizeof(string); i++){
                unsigned char byte = (unsigned char)string[i];
                if (byte<0x80||byte>0xBF){
                        printf("%d ", codepoint_size(byte));
                }
        }

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }
    is_ascii(argv[1]); // valid ascii or not 
    capitalize_ascii(argv[1]); //ugrading the string 
    length(argv[1]); // length of string in bytes.
    utf8info(argv[1]);
    first6Substring(argv[1]);
    animalEmojis(argv[1]);

    // incCdptAtIndex3(argv[1]);
    // implement the UTF-8 analyzer here

}
