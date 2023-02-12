#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define THREE_LINES 1
#define TWO_LINES  2

#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

char* StringInput(int* stringSize)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    printf("Введите строку: ");
    while(curChar != '\n')
    {
        curChar = getchar();

        int deltaVal = 0; // Определяет, на сколько изменится длина массива
        int lengthDif = 0;

        // Если мы стираем символы, а не пишем их,
        if (curChar == BACKSPACE_KEY)
        {
            deltaVal = -1; // то будем уменьшать длину массива
            lengthDif = 1; // и копировать строку до предпоследнего символа
        }

            // Иначе проверяем, входит ли введённый символ в диапазон печатных
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                deltaVal = 1; // Если да, то будем увеличивать длину на 1
                lengthDif = 2; // Не заполняем последние 2 символа -
                // оставляем место для введённого символа и '\0'
            }
            else
            {
                continue; // Если это не печатный символ, то пропускаем его
            }
        }

        // Если стирать больше нечего, но пользователь
        // всё равно жмёт Backspace.
        int newSize = curSize + deltaVal;
        if (newSize == 0)
        {
            continue; // то мы переходим на следующую итерацию - ждём '\n'
        }

        char* tmpStr = (char*)malloc(newSize * sizeof(char));
        if (tmpStr) // Проверяем, выделилась ли память
        {
            // Идём до предпоследнего символа, т.к. надо в конец записать '\0'
            for (int i = 0;
                 i < newSize - lengthDif;
                 ++i)
            {
                tmpStr[i] = userStr[i];
            }

            if (curChar != BACKSPACE_KEY) // Если введён печатный символ,
            {
                tmpStr[newSize - 2] = curChar; // Добавляем его в строку
                tmpStr[newSize - 1] = '\0';
            }
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            printf("Не могу выделить память под обновлённую строку!");
            break;
        }
    }

    *stringSize = curSize - 1;
    return userStr;
}

void RowFilling(char** firstUserStr, int* firstStrSize, char** secondUserStr,
                int* secondStrSize, char** thirdUserStr, int* thirdStrSize,
                int userChoice)
{
    printf("-------------------\n");
    printf("| Ввод трёх строк |\n");
    printf("-------------------\n");

    *firstUserStr = StringInput(firstStrSize);
    *secondUserStr = StringInput(secondStrSize);

    if (userChoice == THREE_LINES)
    {
        *thirdUserStr = StringInput(thirdStrSize);
    }

    printf("Первая введённая строка: %s\n", *firstUserStr);
    printf("Вторая введённая строка: %s\n", *secondUserStr);

    if (userChoice == THREE_LINES)
    {
        printf("Третья введённая строка: %s\n", *thirdUserStr);
    }
}

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);

    while (input != CORRECT_INPUT || inputChar != END_STRING
           || userInput < lowerBound || userInput > count)
    {
        if (userInput >= lowerBound && userInput <= count)
        {
            while ((inputChar = getchar()) != '\n');
        }
        userInput = 1;
        printf("Неверный ввод. Попробуйте снова.\n%s", message);
        input = scanf("%d%c", &userInput, &inputChar);
    }
    return userInput;
}

void PrintMenu(void)
{
    printf("---------------\n");
    printf("| Выбор ввода |\n");
    printf("---------------\n");
    printf("1 - Ввод 3 строк (комплексные числа и знак операции)\n");
    printf("2 - Ввод 2 строк (комплексное число и операция)\n");
}

int main()
{
    printf("-----------------------------------------------\n");
    printf("| Программа для работы с комплексными числами |\n");
    printf("-----------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";

    int userChoice, lowerBound = 1;
    int menuItemsCount = 2;

    char* firstUserStr = 0;
    int firstStrSize = 0;
    char* secondUserStr = 0;
    int secondStrSize = 0;
    char* thirdUserStr = 0;
    int thirdStrSize = 0;

    PrintMenu(); // выводим меню на экран

    // получаем номер выбранного пункта меню
    userChoice = CheckingInput(firstMessage, lowerBound,
                               menuItemsCount);

    RowFilling(&firstUserStr, &firstStrSize, &secondUserStr, &secondStrSize,
               &thirdUserStr, &thirdStrSize, userChoice);

    switch (userChoice)
    {

        case THREE_LINES:
            break;

        case TWO_LINES:
            break;

        default:
            free(firstUserStr);
            free(secondUserStr);
            free(thirdUserStr);
            printf("Выход...");
    }

    return 0;
}

