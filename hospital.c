//Работа с умным массивом, initArray - создает пустой массив, loadFromFile - Загружает пациентов бинарного файла, saveToFile - сохраняет пациентов (массив) в файл, далее происходят операции с базой данных
// то есть вывод пациентов, добавление, удаление, изменение, поиск по имени и возрасту
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
        printf("База данных пуста\n");
        return;
    }

    for (int i = 0; i < arr->size; i++) {
        printf("%d) %s, %d лет, %s\n",
               i + 1,
               arr->data[i].name,
               arr->data[i].age,
               arr->data[i].diagnosis);
    }
}

void addPatient(SmartArray* arr, const char* filename) {
    arr->data = realloc(arr->data,
                         (arr->size + 1) * sizeof(Patient));

    Patient* p = &arr->data[arr->size];

    printf("Имя: ");
    scanf("%s", p->name);

    printf("Возраст: ");
    scanf("%d", &p->age);

    printf("Диагноз: ");
    scanf("%s", p->diagnosis);

    arr->size++;
    saveToFile(arr, filename);
}

void deletePatient(SmartArray* arr, const char* filename) {
    int n;
    printf("Введите номер пациента: ");
    scanf("%d", &n);

    if (n < 1 || n > arr->size) {
        printf("Неверный номер\n");
        return;
    }

    for (int i = n - 1; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
    arr->data = realloc(arr->data,
                         arr->size * sizeof(Patient));

    saveToFile(arr, filename);
}

void editPatient(SmartArray* arr, const char* filename) {
    int n;
    printf("Введите номер пациента: ");
    scanf("%d", &n);

    if (n < 1 || n > arr->size) {
        printf("Неверный номер\n");
        return;
    }

    Patient* p = &arr->data[n - 1];

    printf("Новое имя: ");
    scanf("%s", p->name);

    printf("Новый возраст: ");
    scanf("%d", &p->age);

    printf("Новый диагноз: ");
    scanf("%s", p->diagnosis);

    saveToFile(arr, filename);
}

void searchPatients(SmartArray* arr) {
    int choice;
    printf("Поиск:\n1. По имени\n2. По возрасту\n");
    scanf("%d", &choice);

    if (choice == 1) {
        char name[30];
        printf("Введите имя: ");
        scanf("%s", name);

        for (int i = 0; i < arr->size; i++) {
            if (strcmp(arr->data[i].name, name) == 0) {
                printf("%s %d %s\n",
                       arr->data[i].name,
                       arr->data[i].age,
                       arr->data[i].diagnosis);
            }
        }
    } else if (choice == 2) {
        int age;
        printf("Введите возраст: ");
        scanf("%d", &age);

        for (int i = 0; i < arr->size; i++) {
            if (arr->data[i].age == age) {
                printf("%s %d %s\n",
                       arr->data[i].name,
                       arr->data[i].age,
                       arr->data[i].diagnosis);
            }
        }
    }
}
