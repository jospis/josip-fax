#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


struct Student {
    char ime[20];
    char prezime[20];
    int bodovi;
};

int countStudentsInFile(const char* filename) {
    FILE* datoteka = fopen(filename, "r");

    if (datoteka == NULL) {
        printf("Datoteka nije otvorena\n");
        return 1;
    }

    char buffer[256];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), datoteka) != NULL) {
        if (buffer[0] != '\n' && buffer[0] != '\0') {
            count++;
        }
    }

    fclose(datoteka);
    return count;
}

void readStudentsFromFile(const char* filename, struct Student studenti[], int count) {
    FILE* datoteka = fopen(filename, "r");

    if (datoteka == NULL) {
        printf("Datoteka nije otvorena\n");
        return 2;
    }

    int n = 0;
    char buffer[256];
    while (n < count && fgets(buffer, sizeof(buffer), datoteka) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\0') {
            continue; 
        }
        if (sscanf(buffer, "%s %s %d", studenti[n].ime, studenti[n].prezime, &studenti[n].bodovi) == 3) {
            n++;
        }
    }

    fclose(datoteka);
}

void calculateRelativeScores(struct Student studenti[], double rbodovi[], int count) {
    double max_bodovi = 70;

    for (int i = 0; i < count; i++) {
        rbodovi[i] = (studenti[i].bodovi / max_bodovi) * 100;
    }
}

void printStudents(struct Student studenti[], double rbodovi[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %s %d %.2f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rbodovi[i]);
    }
}

int main() {

    const int count = countStudentsInFile("imena.txt");
    struct Student* studenti = (struct Student*)malloc(count * sizeof(struct Student));
    double rbodovi[10];

    readStudentsFromFile("imena.txt", studenti, count);
    calculateRelativeScores(studenti, rbodovi, count);
    printStudents(studenti, rbodovi, count);

    free(studenti);
    return 0;
}