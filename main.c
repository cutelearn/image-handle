#include <stdio.h>
#include <stdlib.h>

void save_image(unsigned char image[512][512], char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Cannot open file: %s\n", filename);
        exit(1);
    }
    fwrite(image, sizeof(unsigned char), 512 * 512, file);
    fclose(file);
}

int main() {
    FILE *inputFile;
    unsigned char image[512][512];
    unsigned char processed_image[512][512];
    int i, j, k, l;

    // 讀取影像
    inputFile = fopen("input.raw", "rb");
    if (inputFile == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    size_t read_count = fread(image, sizeof(unsigned char), 512 * 512, inputFile);
    if (read_count != 512 * 512) {
        printf("Failed to read the entire file.\n");
        exit(1);
    }
    fclose(inputFile);

    // 1. 鏡像
    for (i = 0; i < 512; i++) {
        for (j = 0; j < 512; j++) {
            processed_image[i][511 - j] = image[i][j];
        }
    }
    save_image(processed_image, "mirrored.raw");

    // 2. 翻轉
    for (i = 0; i < 512; i++) {
        for (j = 0; j < 512; j++) {
            processed_image[511 - i][j] = image[i][j];
        }
    }
    save_image(processed_image, "flipped.raw");

    // 3. 90度逆時鐘旋轉
    for (i = 0; i < 512; i++) {
        for (j = 0; j < 512; j++) {
            processed_image[511 - j][i] = image[i][j];
        }
    }
    save_image(processed_image, "rotated_90.raw");

    // 4. 負片
    for (i = 0; i < 512; i++) {
        for (j = 0; j < 512; j++) {
            processed_image[i][j] = 255 - image[i][j];
        }
    }
    save_image(processed_image, "negative.raw");

    // 5. 模糊化
    for (i = 1; i < 511; i++) {
        for (j = 1; j < 511; j++) {
            int sum = 0;
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    sum += image[i + k][j + l];
                }
            }
            processed_image[i][j] = sum / 9;
        }
    }
    save_image(processed_image, "blurred.raw");

    return 0;
}
