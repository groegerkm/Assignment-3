#include "barcode.h"
#include <stdio.h>
#include <string.h>
#define GET_BIT(value, bit) (((value) >> (bit)) & 1)

static void fill_digit(struct image *imageptr, int x, int value){
    for (int y = 0; y < imageptr->height; y++) {
        struct pixel *p = &imageptr->pixels[y * imageptr->width + x];

        if (value == 1) { //white
            p->r = 255;
            p->g = 255;
            p->b = 255;
        } else { // black
            p->r = 0;
            p->g = 0;
            p->b = 0;
        }
    }
}

static void fill_pattern(struct image* imageptr, int* x, const char* pattern){
    for (size_t i = 0; i < strlen(pattern); i++) {
        int bit = pattern[i] - '0';
        fill_digit(imageptr, *x, bit);
        (*x)++;
    }
}
struct image* barcode(char* data, int width, int height) {
    struct image* imageptr = malloc(sizeof(struct image));
    imageptr->width = width;
    imageptr->height = height;

    struct pixel* pixels = malloc(width * height * sizeof(struct pixel));
    imageptr->pixels = pixels;

    int x = 0;
    const char* LeftDigits[10] = {
    "1110010",
    "1100110",
    "1101100",
    "1010000",
    "1011100",
    "1001110",
    "1000010",
    "1000100",
    "1001000",
    "1110100"
    };

    const char* RightDigits[10] = {
    "0001101",
    "0011001",
    "0010011",
    "0101111",
    "0100011",
    "0110001",
    "0111101",
    "0111011",
    "0110111",
    "0001011"
    };

    const char* StartEnd = {
    "010"
    };

    const char* MiddleDigits = {
    "10101"
    };

    // Left quiet zone: 9 white columns
    for (int i = 0; i < 9; i++) {
        fill_digit(imageptr, x, 1);
        x++;
    }

    // Start = 010
    fill_pattern(imageptr, &x, StartEnd);

    // Left digits: data[0] through data[5], using LeftDigits[]
    for (int i = 0; i < 6; i++) {
        int digit = data[i] - '0';
        fill_pattern(imageptr, &x, LeftDigits[digit]);
    }
    
    // Middle = 10101 
    fill_pattern(imageptr, &x, MiddleDigits);

    // Right digits: data[6] through data[11], using RightDigits[]
    for (int i = 6; i < 12; i++) {
        int digit = data[i] - '0';
        fill_pattern(imageptr, &x, RightDigits[digit]);
    }

    // End = 010
    fill_pattern(imageptr, &x, StartEnd);

    // Right quiet zone: 9 white columns
    for (int i = 0; i < 9; i++) {
        fill_digit(imageptr, x++, 1);
    }

    return imageptr;
}



