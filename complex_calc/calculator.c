#include "calculator.h"

void sum () {
    int r1, r2, i1, i2;
    printf("Введите вещественную часть первого числа: ");
    scanf("%d", &r1);
    printf("Введите мнимую часть первого числа: ");
    scanf("%d", &i1);
    printf("Введите вещественную часть второго числа: ");
    scanf("%d", &r2);
    printf("Введите мнимую часть второго числа: ");
    scanf("%d", &i2);
    i1 = i1 + i2;
    if (i1 > 0) {
	printf("Сумма этих чисел равна: %d + i%d\n", r1 + r2, i1);
    } else if (i1 < 0) {
	printf("Сумма этих чисел равна: %d - i%d\n", r1 + r2, -1 * i1);
    } else {
	printf("Сумма этих чисел равна: %d\n", r1 + r2);
    }
}

void sub () {
    int r1, r2, i1, i2;
    printf("Введите вещественную часть первого числа: ");
    scanf("%d", &r1);
    printf("Введите мнимую часть первого числа: ");
    scanf("%d", &i1);
    printf("Введите вещественную часть второго числа: ");
    scanf("%d", &r2);
    printf("Введите мнимую часть второго числа: ");
    scanf("%d", &i2);
    i1 = i1 - i2;
    if (i1 > 0) {
	printf("Вычитание этих чисел равна: %d + i%d\n", r1 - r2, i1);
    } else if (i1 < 0) {
	printf("Вычитание этих чисел равна: %d - i%d\n", r1 - r2, -1 * i1);
    } else {
	printf("Вычитание этих чисел равна: %d\n", r1 - r2);
    }
}

void mul () {
    int r1, r2, i1, i2, i;
    printf("Введите вещественную часть первого числа: ");
    scanf("%d", &r1);
    printf("Введите мнимую часть первого числа: ");
    scanf("%d", &i1);
    printf("Введите вещественную часть второго числа: ");
    scanf("%d", &r2);
    printf("Введите мнимую часть второго числа: ");
    scanf("%d", &i2);
    i = r1 * i2 + r2 * i1;
    if (i > 0) {
	printf("Умножение этих чисел равна: %d + i%d\n", r1 * r2 - i1 * i2, i);
    } else if (i < 0) {
	printf("Умножение этих чисел равна: %d - i%d\n", r1 * r2 - i1 * i2, -1 * i);
    } else {
	printf("Умножение этих чисел равна: %d\n", r1 * r2 - i1 * i2);
    }
}


void del () {
    int r1, r2, i1, i2, i;
    printf("Введите вещественную часть первого числа: ");
    scanf("%d", &r1);
    printf("Введите мнимую часть первого числа: ");
    scanf("%d", &i1);
    printf("Введите вещественную часть второго числа: ");
    scanf("%d", &r2);
    printf("Введите мнимую часть второго числа: ");
    scanf("%d", &i2);
    i = (r1 * (-1 * i2) + r2 * i1) / (r2 * r2 - i2 * i2);
    if (i > 0) {
	printf("Деление этих чисел равна: %d + i%d\n", (r1 * r2 + i1 * i2) / (r2 * r2 - i2 *i2), i);
    } else if (i < 0) {
	printf("Умножение этих чисел равна: %d - i%d\n", (r1 * r2 + i1 * i2) / (r2 * r2 - i2 * i2), -1 * i);
    } else {
	printf("Умножение этих чисел равна: %d\n", (r1 * r2 + i1 * i2) / (r2 * r2 - i2 * i2));
    }
}