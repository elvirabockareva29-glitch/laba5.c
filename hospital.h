//заголовочный файл, описывает структуру patient - данные о пациенте, структура SmartArray - умный массив, содержит объвление функций,которые используются в hospital.c and main.c
#ifndef HOSPITAL_H
#define HOSPITAL_H

typedef struct {
    char name[50];
    int age;
    char diagnosis[50];
} Patient;

typedef struct {
    Patient* data;
    int size;
} SmartArray;

void initArray(SmartArray* arr);
void loadFromFile(SmartArray* arr, const char* filename);
void saveToFile(SmartArray* arr, const char* filename);

void printPatients(SmartArray* arr);
void addPatient(SmartArray* arr, const char* filename);
void deletePatient(SmartArray* arr, const char* filename);
void editPatient(SmartArray* arr, const char* filename);
void searchPatients(SmartArray* arr);

#endif
