//заголовочный файл, описывает структуру patient - данные о пациенте, структура SmartArray - умный массив, содержит объвление функций,которые используются в hospital.c and main.c
#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[30];
    int age;
    char diagnosis[30];
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
