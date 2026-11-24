#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    FILE *in = NULL;
    if (argc == 3){
        in = fopen(argv[2], "rb");
    } else{
        in = fopen("input.bin", "rb");
        while (fgetc(in) != '\n'){
        }
    }
    fseek(in,18,SEEK_CUR);
    int32_t width, height;
    fread(&width, 4, 1, in);
    fread(&height, 4, 1, in);
    if (height<0){
        height = -height;
    }
    if (argc==3){
        printf("%d %d\n", width, height);
    } else{
        FILE *out = fopen("output.txt", "w");
        fprintf(out, "%d %d\n", width, height);
        fclose(out);

    }
    fclose(in);
    return 0;
}