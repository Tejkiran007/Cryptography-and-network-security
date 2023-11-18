#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

void prepare(char key[10], char keytab[5][5]) {
    int i, j, k, flag = 0, *dicty;
    dicty = (int *)calloc(26, sizeof(int));
    for (k = 0; k < strlen(key); k++) {
        if (key[k] != 'j')
            dicty[key[k] - 97] = 2;
    }
    dicty['j' - 97] = 1;

    i = 0;
    j = 0;
    for (k = 0; k < strlen(key); k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            keytab[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
    for (k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keytab[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void playfair(char ch1, char ch2, char keytab[5][5]) {
    int i, j, w, x, y, z;
    FILE *out;
    if ((out = fopen("cipher.txt", "a+")) == NULL) {
        printf("File Curupt");
        exit(0);
    }
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (ch1 == keytab[i][j]) {
                w = i;
                x = j;
            } else if (ch2 == keytab[i][j]) {
                y = i;
                z = j;
            }
        }
    }
    printf("\n");
    if (w == y) {
        x = (x + 1) % 5;
        z = (z + 1) % 5;
        printf("%c%c", keytab[w][x], keytab[y][z]);
        fprintf(out, "%c%c", keytab[w][x], keytab[y][z]);
    } else if (x == z) {
        w = (w + 1) % 5;
        y = (y + 1) % 5;
        printf("%c%c", keytab[w][x], keytab[y][z]);
        fprintf(out, "%c%c", keytab[w][x], keytab[y][z]);
    } else {
        printf("%c%c", keytab[w][z], keytab[y][x]);
        fprintf(out, "%c%c", keytab[w][z], keytab[y][x]);
    }
    fclose(out);
}

void main() {
    int i, j, len;
    char key[10], keytab[5][5], pt[50], ct[50];
    printf("\nEnter the key: ");
    scanf("%s", key);
    printf("\nEnter the plain text: ");
    scanf("%s", pt);
    printf("\n\nThe formed 5 X 5 matrix is as follows: \n\n");
    prepare(key, keytab);
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", keytab[i][j]);
        }
        printf("\n");
    }
    printf("\n\nThe cipher text is: ");
    if (strlen(pt) % 2 != 0) {
        len = strlen(pt) + 1;
    } else {
        len = strlen(pt);
    }
    for (i = 0; i < len; i += 2) {
        if (pt[i] == pt[i + 1]) {
            pt[i + 1] = 'x';
        }
        if (pt[i + 1] == '\0') {
            playfair(pt[i], 'x', keytab);
        } else {
            playfair(pt[i], pt[i + 1], keytab);
        }
    }
}
