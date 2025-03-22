#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TEXT 1024

// Funcție pentru sortarea parolei și generarea ordinii coloanelor
void getColumnOrder(const char *password, int order[]) {
    int len = strlen(password);
    char sorted[len + 1];
    strcpy(sorted, password);

    // Sortăm parola
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (sorted[i] > sorted[j]) {
                char temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    int used[len]; // Marcam ce coloane am folosit
    memset(used, 0, sizeof(used));

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (password[i] == sorted[j] && !used[j]) {
                order[j] = i;
                used[j] = 1;  // Marcăm această poziție ca utilizată
                break;
            }
        }
    }
}


// Funcție pentru criptare
void encrypt(char *text, const char *password, FILE *fout) {
    int textLen = strlen(text);
    int N = strlen(password);
    int M = (textLen + N - 1) / N; // Calculăm numărul de linii

    char matrix[M][N];
    memset(matrix, '%', sizeof(matrix)); // Umplem cu 'X' pentru padding

    // Umplem matricea cu textul inițial
    int index = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N && index < textLen; j++) {
            matrix[i][j] = text[index++];
        }
    }

    // Obținem ordinea coloanelor
    int order[N];
    memset(order, -1, sizeof(order));
    getColumnOrder(password, order);

    // Scriem coloanele în ordinea determinată de parolă
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fputc(matrix[j][order[i]], fout);
        }
    }
}

// Funcție pentru decriptare
void decrypt(char *text, const char *password, FILE *fout) {
    int textLen = strlen(text);
    int N = strlen(password);
    int M = textLen / N; // Deoarece nu avem padding aici

    char matrix[M][N];
    memset(matrix, '%', sizeof(matrix));

    int order[N];
    memset(order, -1, sizeof(order));
    getColumnOrder(password, order);

    // Refacem matricea cu textul cifrat
    int index = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[j][order[i]] = text[index++];
        }
    }

    // Reconstruim textul decriptat
    char decryptedText[M * N + 1];  // Allocăm suficient spațiu pentru textul decriptat
    int decryptedIndex = 0;

    // Scriem textul original
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            decryptedText[decryptedIndex++] = matrix[i][j];
        }
    }
    decryptedText[decryptedIndex] = '\0'; // Adăugăm terminatorul de șir

    // Eliminăm caracterele '%' de la sfârșitul textului
    int finalLen = decryptedIndex;
    while (finalLen > 0 && decryptedText[finalLen - 1] == '%') {
        finalLen--;
    }

    decryptedText[finalLen] = '\0';  // Terminăm șirul corect

    // Scriem textul decriptat în fișier
    fputs(decryptedText, fout);
}

int main(int argc, char *argv[]) {
    if (argc < 7) {
        printf("Utilizare: %s -e|-d -p parola -i input.txt -o output.txt\n", argv[0]);
        return 1;
    }

    int encryptMode = (strcmp(argv[1], "-e") == 0);
    char *password = NULL;
    char *inputFile = NULL;
    char *outputFile = NULL;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) password = argv[++i];
        else if (strcmp(argv[i], "-i") == 0) inputFile = argv[++i];
        else if (strcmp(argv[i], "-o") == 0) outputFile = argv[++i];
    }

    if (!password || !inputFile || !outputFile) {
        printf("Toate argumentele (-p, -i, -o) sunt necesare!\n");
        return 1;
    }

    FILE *fin = fopen(inputFile, "r");
    FILE *fout = fopen(outputFile, "w");
    if (!fin || !fout) {
        perror("Eroare la deschiderea fișierelor");
        return 1;
    }

    char text[MAX_TEXT];
    fgets(text, MAX_TEXT, fin);
    fclose(fin);

    if (encryptMode)
        encrypt(text, password, fout);
    else
        decrypt(text, password, fout);

    fclose(fout);
    printf("Procesul a fost finalizat cu succes!\n");
    return 0;
}
