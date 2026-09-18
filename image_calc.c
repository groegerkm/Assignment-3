#include "barcode.h"
#include "common.h"
#include "loader.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
    // TODO: parse the arguments in argv.
    char* barcode_value = argv[1];// You can expect argv[1] to be the digits to encode 
    int width = atoi(argv[2]);// You can expect argv[2] to be the integer width   
    int height = atoi(argv[3]);// You can expect argv[3] to be the integer height
    char* output_image_path = argv[4];// You can expect argv[4] to be the output filepath.
    

    if(argc != 5) {
        printf("Incorrect number of arguments. Expected: ./build/image_calc <barcode_value> <width> <height> <output_image_path>\n");
        return -1;
    }


    // TODO: call barcode
    struct image* barcode_image = barcode(barcode_value, width, height);

    // TODO: save result to file
    saveimage(output_image_path, barcode_image);

    free(barcode_image->pixels);
    free(barcode_image);
}
