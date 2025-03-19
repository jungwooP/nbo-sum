#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t ntohl(uint32_t val)
{
    return (val & 0xFF000000) >> 24 | (val & 0x00FF0000) >> 8 | (val & 0x0000FF00) << 8 | (val & 0x000000FF) << 24;
}

int main(int argc, char *argv[])
{

    int flag = 1; // to check if it is the first one printed
    int flag2; //Data Found? 
    uint32_t sum = 0;
    uint32_t host, data; 
    int i;
	
    // CHECK FOR VALID FORMAT 
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return 1;
    }
     
    for (i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
            return 1;
        }

        // check file-size
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp); // CHECK SIZE
        rewind(fp); //to first position of file
        if (size < sizeof(uint32_t)) {
            fprintf(stderr, "Error: File %s should be at least 4 bytes\n", argv[i]);
            fclose(fp);
            return 1;
        }

        flag2 = 0;
        while (fread(&data, sizeof(data), 1, fp) == 1) {
            flag2 = 1;
            host = ntohl(data);

            if (!flag) {
                printf(" + ");
            }
            flag = 0;

            // PRINT WITH VALID PADDING
            printf("%u(0x%04x)", host, host);

            sum += host;
        }

        if (!flag2) {
            fprintf(stderr, "Error: File %s doesn't contains valid 4-byte integers\n", argv[i]);
            fclose(fp);
            return 1;
        }

        fclose(fp);
    }

    printf(" = %u(0x%04x)\n", sum, sum);

    return 0;
}

