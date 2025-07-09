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
	printf("%s\n", *p);
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }

    // incCdptAtIndex3(argv[1]);
    // implement the UTF-8 analyzer here
    first6Substring(argv[1]);
    animalEmojis(argv[1]);

}
