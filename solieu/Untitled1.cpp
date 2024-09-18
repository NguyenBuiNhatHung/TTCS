#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANDOM_NUMBERS 10000

int main() {
    FILE *file;
    char filename[] = "points2.inp";
    int number;
    int i;

    // M? file d? ghi
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Không th? m? file.\n");
        return 1;
    }

    // Ghi s? 1000000000 vào dòng d?u tiên
    fprintf(file, "10000\n");

    // Ghi 1000000000 s? ng?u nhiên t? 1 d?n 1000000000 vào các dòng ti?p theo
    srand(time(0)); // Kh?i t?o seed cho hàm srand s? d?ng th?i gian hi?n t?i
    for (i = 0; i < NUM_RANDOM_NUMBERS; i++) {
        if (i != 0) {
            fprintf(file, " ");
        }
        number = rand() % 10000 + 1; // Sinh s? ng?u nhiên t? 1 d?n 1000000000
        fprintf(file, "%d", number);
    }

    // Ðóng file
    fclose(file);

    return 0;
}
