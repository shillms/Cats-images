#include <stdio.h>
#include <stdint.h>

int main( int argc, char *argv[]){
    FILE *in = NULL;
    FILE *out = NULL;
    if (argc == 4){
        in = fopen(argv[2], "rb");
        out = fopen(argv[3], "wb");
    } else {
        in = fopen("input.bin", "rb");
        out = fopen("output.bmp", "wb");
        while (fgetc(in) != '\n'){
        }
    }
    uint8_t header[54];
    fread(header,1,54,in);
    fwrite(header,1,54,out);
    int32_t width = *(int32_t *)(header + 18);
    int32_t height = *(int32_t *)(header + 22);
        if (height < 0) {
        height = -height;
    }
    int width_bytes = width *3;
    int padding = (4-(width_bytes%4))%4;  //считаем сколько у нам не хватает байтов с в строке чтобы делилось на 4
    for (int y = 0;y<height;y++){
        for (int x = 0; x < width_bytes; x++){
            uint8_t byte;
            fread(&byte,1,1,in);
            byte = 255-byte;
            fwrite(&byte,1,1,out);
        }
    }
        for (int p = 0;p<padding;p++){
            uint8_t pad;
            fread(&pad,1,1,in);
            fwrite(&pad,1,1,out);
        }
    fclose(in);
    fclose(out);
    return 0;
}