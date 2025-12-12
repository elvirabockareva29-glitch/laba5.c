//Работа с умным массивом, initArray - создает пустой массив, loadFromFile - Загружает пациентов бинарного файла, saveToFile - сохраняет пациентов (массив) в файл, далее происходят операции с базой данных
// то есть вывод пациентов, добавление, удаление, изменение, поиск по имени и возрасту
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

void initArray(SmartArray* arr) {
    arr->data = NULL;
    arr->size = 0;
}

void loadFromFile(SmartArray* arr, const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    int bytes = ftell(f);
    rewind(f);

    arr->size = bytes / sizeof(Patient);
    arr->data = malloc(arr->size * sizeof(Patient));

    if (arr->size > 0)
        fread(arr->data, sizeof(Patient), arr->size, f);

    fclose(f);
}

void saveToFile(SmartArray* arr, const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;

    fwrite(arr->data, sizeof(Patient), arr->size, f);
    fclose(f);
}

void printPatients(SmartArray* arr) {
    if (arr->size == 0) {
        printf("База пуста.\n");
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        printf("%d) %s | %d лет | диагноз: %s\n",
            i + 1,
            arr->data[i].name,
            arr->data[i].age,
            arr->data[i].diagnosis
        );
    }
}

void addPatient(SmartArray* arr, const char* filename) {
    arr->size++;
    arr->data = realloc(arr->data, arr->size * sizeof(Patient));

    Patient* p = &arr->data[arr->size - 1];

    printf("Введите имя: ");
    scanf("%49s", p->name);
    printf("Введите возраст: ");
    scanf("%d", &p->age);
    printf("Введите диагноз: ");
    scanf("%49s", p->diagnosis);

    saveToFile(arr, filename);
    printf("Пациент добавлен.\n");
}

void deletePatient(SmartArray* arr, const char* filename) {
    if (arr->size == 0) {
        printf("База пуста.\n");
        return;
    }

    int id;
    printf("Введите номер пациента для удаления: ");
    scanf("%d", &id);

    if (id < 1 || id > arr->size) {
        printf("Неверный номер.\n");
        return;
    }

    for (int i = id - 1; i < arr->size - 1; i++)
        arr->data[i] = arr->data[i + 1];

    arr->size--;
    arr->data = realloc(arr->data, arr->size * sizeof(Patient));

    saveToFile(arr, filename);
    printf("Пациент удалён.\n");
}

void editPatient(SmartArray* arr, const char* filename) {
    if (arr->size == 0) {
        printf("База пуста.\n");
        return;
    }

    int id;
    printf("Введите номер пациента для редактирования: ");
    scanf("%d", &id);

    if (id < 1 || id > arr->size) {
        printf("Неверный номер.\n");
        return;
    }

    Patient* p = &arr->data[id - 1];

    printf("Новое имя: ");
    scanf("%49s", p->name);
    printf("Новый возраст: ");
    scanf("%d", &p->age);
    printf("Новый диагноз: ");
    scanf("%49s", p->diagnosis);

    saveToFile(arr, filename);
    printf("Данные обновлены.\n");
}

void searchPatients(SmartArray* arr) {
    if (arr->size == 0) {
        printf("База пуста.\n");
        return;
    }

    int mode;
    printf("Поиск по: 1 — имени, 2 — возрасту: ");
    scanf("%d", &mode);

    if (mode == 1) {
        char name[50];
        printf("Введите имя: ");
        scanf("%49s", name);

        for (int i = 0; i < arr->size; i++) {
            if (strcmp(arr->data[i].name, name) == 0)
                printf("%d) %s | %d | %s\n",
                    i + 1, arr->data[i].name, arr->data[i].age, arr->data[i].diagnosis);
        }
    }
    else if (mode == 2) {
        int age;
        printf("Введите возраст: ");
        scanf("%d", &age);

        for (int i = 0; i < arr->size; i++) {
            if (arr->data[i].age == age)
                printf("%d) %s | %d | %s\n",
                    i + 1, arr->data[i].name, arr->data[i].age, arr->data[i].diagnosis);
        }
    }
    else {
        printf("Ошибка выбора.\n");
    }
}
