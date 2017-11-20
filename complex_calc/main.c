#include "calculator.h"


int main () {
    int ch;

    do {
	printf("1. Сложение\n");
	printf("2. Вычитание\n");
	printf("3. Умножение\n");
	printf("4. Деление\n");
	printf("5. Выход\n");
	printf("Выберите действие: ");
	scanf("%d", &ch);
	switch (ch) {
	    case 1:
		sum ();
		break;
	    case 2:
		sub ();
		break;
	    case 3:
		mul ();
		break;
	    case 4:
		del ();
		break;
	    case 5:
		printf("Инициализирую выход\n");
		break;
	    default:
		printf("Попробуйте снова\n");
		break;
	}
    } while (ch != 5);
    return 0;
}
