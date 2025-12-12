//главная программа: создает массив пациентов- initArray, загружает данные из файла-loadFromFile, показывает меню, запуск нужных функций
#include <stdio.h>
#include "hospital.h"

#define FILE_NAME "hospital.dat"

int main() {
    SmartArray arr;
    initArray(&arr);
    loadFromFile(&arr, FILE_NAME);

    int choice;

    while (1) {
        printf("\n===== МЕНЮ =====\n");
        printf("1. Показать всех пациентов\n");
        printf("2. Добавить пациента\n");
        printf("3. Удалить пациента\n");
        printf("4. Редактировать пациента\n");
        printf("5. Поиск\n");
        printf("0. Выход\n");
        printf("Выберите: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: printPatients(&arr); break;
        case 2: addPatient(&arr, FILE_NAME); break;
        case 3: deletePatient(&arr, FILE_NAME); break;
        case 4: editPatient(&arr, FILE_NAME); break;
        case 5: searchPatients(&arr); break;
        case 0: 
            saveToFile(&arr, FILE_NAME);
            printf("Выход...\n");
            return 0;
        default: printf("Ошибка ввода.\n");
        }
    }
}
