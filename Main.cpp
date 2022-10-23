#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "Header.h"

int main()
{
	int first_choise;
	int flag=-1;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	printf("________________________________________\n   Программа продажи автобусных билетов\n");
	printf("________________________________________\n   Разработчик программы - Песков Н.А.\n");
	printf("\n   Существует ли хотя бы 1 учетная запись администратора?\n   1.Да\n   0.Нет\n   ");
	scanf_s("%d", &first_choise);
	number_check(first_choise);
	number_0_or_1(first_choise);
	if (first_choise == 1) {
	}
	else if (first_choise == 0) {
		writing_1_user_in_file();
	}
	writing_users_to_array();
	writing_data_to_array();
	while (flag!=0) {
		printf("\n_______Главное меню_______\n");
		printf("   0.Завершить программу\n");
		printf("   1.Войти в систему\n");
		printf("   2.Создать учетную запись без входа в систему\n");
		printf("   Выберите действие\n   ");
		scanf_s("%d", &flag);
		number_check(flag);
		if (flag == 0) {
		}
		else if (flag == 1) {
			choise = -1;
			input_login_and_password();
			if (data_mode == 1) {
				while (choise != 0) {
					administrator_menu();
				}
			}
			else if (data_mode == 0) {
				while (choise != 0) {
					user_menu();
				}
			}
		}
		else if (flag == 2) {
			create_user_without_access();
		}
		else {
			printf("   Ошибка при входе в систему\n");
		}
	}
	clear_memory();
	return 0;
}
