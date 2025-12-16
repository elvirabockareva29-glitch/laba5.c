#include "hospital.h"

int main() {
    SmartArray arr;
    char filename[100];
    int choice;

    printf("Введите имя файла базы данных: ");
    scanf("%s", filename);

    initArray(&arr);
    loadFromFile(&arr, filename);

    while (1) {
        printf("\nМеню:\n");
        printf("1. Показать пациентов\n");
        printf("2. Добавить пациента\n");
        printf("3. Удалить пациента\n");
        printf("4. Редактировать пациента\n");
        printf("5. Поиск\n");
        printf("0. Выход\n");
        printf("Введите номер: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printPatients(&arr);
                break;
            case 2:
                addPatient(&arr, filename);
                break;
            case 3:
                deletePatient(&arr, filename);
                break;
            case 4:
                editPatient(&arr, filename);
                break;
            case 5:
                searchPatients(&arr);
                break;
            case 0:
                free(arr.data);
                return 0;
            default:
                printf("Неверный ввод\n");
        }
    }
}
