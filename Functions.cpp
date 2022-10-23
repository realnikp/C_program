#include <time.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include "Header.h"
#include <conio.h>
#include <iostream>
#define STR_SIZE 30
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

typedef struct user {        //структура с данными учетной записи
	char login[STR_SIZE];
	char password[STR_SIZE];
	int role;
	int access;
} User;

typedef struct bus {        //структура с данными автобусного рейса
	int number_of_trip;
	char type_of_bus[STR_SIZE];
	char destination[STR_SIZE];
	char depature_date[STR_SIZE];
	char depature_time[STR_SIZE];
	char arrival_time[STR_SIZE];
	int cost_of_ticket;
	int number_of_free;
	int number_of_sold;
} Bus;

User *users, user_buf, empty_user;
Bus *buses, bus_buf, empty_bus;
FILE* f1, * f2;
//f1 - запись пользователей
//f2 - запись данных о рейсах

int num_of_admins=1;        //количество администраторов
int size_of_users=1;        //количество пользователей
int size_of_buses;          //количество рейсов
extern int data_mode = -1;  //режим работы с данными в текущий момент
extern int choise = -1;     //выбор пользователя в меню

extern void input_login_and_password() {
	char c;
	int i = 0;
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	printf("_____________________\n");
	printf("\n   Введите логин\n   ");
	scanf_s("%s", user_buf.login, STR_SIZE);
	printf("   Введите пароль\n   ");
	while ((c = _getch()) != '\r')
	{
		user_buf.password[i++] = c;
		_putch('*');
	}
	while (i < STR_SIZE-2) {
		user_buf.password[i++] = NULL;
	}
	printf("\n_____________________\n");
	find_user(user_buf.login, user_buf.password);
}

extern int verify_login() {
	for (int i = 0; i < size_of_users-1; i++) {
		if (strcmp(users[size_of_users - 1].login,users[i].login)==0) {
			return 1;
		}
	}
	return 0;
}

extern void writing_users_to_array()
{
	if (!(fopen_s(&f1, "file1.dat", "r"))) {
		fseek(f1, 0, SEEK_END);// определение размера файла
		int lenth = ftell(f1);
		int i = 0;
		size_of_users = lenth / sizeof(User);
		users = (User*)calloc(size_of_users,sizeof(User));
		rewind(f1);
		while (fread(&users[i], sizeof(User), 1, f1))
		{
			i++;
		}

		fclose(f1);
	}
	else {
	}
}

extern void writing_data_to_array() {
	if (!(fopen_s(&f2, "file2.dat", "r"))) {
		fseek(f2, 0, SEEK_END);// определение размера файла
		int lenth = ftell(f2);
		int i = 0;
		size_of_buses = lenth / sizeof(Bus);
		buses = (Bus*)calloc(size_of_buses, sizeof(Bus));
		rewind(f2);
		while (fread(&buses[i], sizeof(Bus), 1, f2))
		{
			i++;
		}

		fclose(f2);
	}
	else {
	}
}

extern void writing_1_user_in_file() {
	char c;
	int i = 0;
	if (fopen_s(&f1, "file1.dat", "a+") == 0) {
		printf("\n____________________________________");
		printf("\n   Введите логин адмнистратора:\n   ");
		scanf_s("%s", user_buf.login, STR_SIZE);
		printf("\n   Введите пароль адмнистратора:\n   ");
		while ((c = _getch()) != '\r')
		{
			user_buf.password[i++] = c;
			_putch('*');
		}
		while (i < STR_SIZE-2) {
			user_buf.password[i++] = NULL;
		}
		printf("\n____________________________________\n");
		user_buf.role = 1;
		user_buf.access = 1;
		fwrite(&user_buf, sizeof(User), 1, f1);
		fclose(f1);
	}
	else {
		printf("   Файл не существует\n");
	}
}

extern void find_user(char* login, char* password) {
	int flag=0;
	int counter = 0;
	for (int i = 0; i < size_of_users; i++) {
		if (strcmp(login,users[i].login)==0 && strcmp(password, users[i].password) == 0 && users[i].access == 1) {
			flag++;
			switch (users[i].role) {
				case 0: 
					printf("\n   Вы вошли в систему как пользователь\n");
					break;
				case 1: 
					printf("\n   Вы вошли в систему как администратор\n");
					break;
				default:printf("\n   Ошибка\n");
			}
			data_mode = users[i].role;
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Такой учетной записи не существует или она заблокирована\n");
		data_mode = -1;
	}
}

extern void print_list_of_users() {
	printf("\n   Список пользователей\n");
	printf("——————————————————————————————————————"
		"————————————————————————————————————————————————"
		"—————————————————————————————————\n"
		"| № |     Логин     |     Пароль    | Роль | Доступ |\n "
		"——————————————————————————————————————"
		"———————————————————————————————————————————————"
		"——————————————————————————————————\n");
	for (int i = 0; i < size_of_users; i++) {
		printf("|%3d|%15s|%15s|%6d|%8d|\n", i+1, users[i].login, users[i].password, users[i].role, users[i].access);
		printf("——————————————————————————————————————"
		"————————————————————————————————————————————————"
			"——————————————————————————————————\n");
	}
}

extern void administrator_menu() {
	int choise_2;
	printf("\n   _______Модуль администратора_______\n");
	printf("   1.Управление учетными записями\n");
	printf("   2.Работа с данными\n");
	printf("   0.Выход\n");
	printf("   Выберите действие\n   ");
	scanf_s("%d", &choise);
	number_check(choise);
	if (choise == 0) {
	}
	else if (choise == 1) {
		do {
			printf("   1.Просмотр всех записей\n");
			printf("   2.Добавление новой записи\n");
			printf("   3.Редактирование записи\n");
			printf("   4.Удаление записи\n");
			printf("   5.Проверка записей, созданных пользователями\n");
			printf("   6.Сохранение всех учетных записей в файл\n");
			printf("   0.Выход\n");
			printf("   Выберите действие\n   ");
			scanf_s("%d", &choise_2);
			number_check(choise_2);
			switch (choise_2) {
			case 0:
				break;
			case 1:
				print_list_of_users();
				break;
			case 2:
				add_user();
				break;
			case 3:
				change_user();
				break;
			case 4:
				delete_user();
				break;
			case 5:
				check_users();
				break;
			case 6:
				writing_users_in_file();
				break;
			default:
				printf("   Некорректный выбор\n");
			}
		} while (choise_2 != 0);
	}
	else if (choise == 2) {
		do {
			printf("\n   _______А.Режим редактирования_______\n");
			printf("   1.Просмотр всех данных\n");
			printf("   2.Добавление новых данных\n");
			printf("   3.Редактирование данных\n");
			printf("   4.Удаление данных\n");
			printf("   5.Сохранение всех данных о рейсах в файл\n");
			printf("\n   _______Б.Режим обработки_______\n");
			printf("   6.Покупка билетов на конкретный рейс в требуемом количестве\n");
			printf("   7.Поиск данных\n");
			printf("   8.Сортировка данных\n");
			printf("   0.Выход\n");
			printf("   Выберите действие\n   ");
			scanf_s("%d", &choise_2);
			number_check(choise_2);
			switch (choise_2) {
			case 0:
				administrator_menu();
				break;
			case 1:
				print_data();
				break;
			case 2:
				add_data();
				break;
			case 3:
				change_data();
				break;
			case 4:
				delete_data();
				break;
			case 5:
				writing_data_in_file();
				break;
			case 6:
				buying_tickets();
				break;
			case 7:
				find_data();
				break;
			case 8:
				sort_data();
				break;
			default:
				printf("   Некорректный выбор\n");
			}
		} while (choise_2 != 0);
	}
	else {
		printf("   Некорректный выбор. Повторите попытку\n");
		administrator_menu();
	}
}

extern void user_menu() {
	printf("\n   _______Модуль пользователя_______\n");
	printf("   1.Просмотр всех данных\n");
	printf("   2.Покупка билетов на конкретный рейс в требуемом количестве\n");
	printf("   3.Поиск данных\n");
	printf("   4.Сортировка данных\n");
	printf("   0.Выход из модуля пользователя\n");
	printf("   Выберите действие\n   ");
	scanf_s("%d", &choise);
	number_check(choise);
	switch (choise) {
	case 0:
		break;
	case 1:
		print_data();
		break;
	case 2:
		buying_tickets();
		break;
	case 3:
		find_data();
		break;
	case 4:
		sort_data();
		break;
	default:
		printf("   Некорректный выбор. Повторите попытку\n");
	}
}

extern void add_user() {
	char c;
	int i = 0;
	int fl = -1;
	size_of_users++;
	get_memory_for_users();
	do {
		printf("\n   Введите логин нового пользователя. Логин не должен повторяться!:\n   ");
		scanf_s("%s", users[size_of_users - 1].login, STR_SIZE);
	} while (verify_login() != 0);
	printf("\n   Введите пароль нового пользователя:\n   ");
	while ((c = _getch()) != '\r')
	{
		users[size_of_users - 1].password[i++] = c;
		_putch('*');
	}
	while (i < STR_SIZE - 2) {
		users[size_of_users - 1].password[i++] = NULL;
	}
	printf("\n   Введите код доступа нового пользователя (0-пользователь, 1-администратор):\n   ");
	scanf_s("%d", &users[size_of_users - 1].role);
	number_check(users[size_of_users - 1].role);
	number_0_or_1(users[size_of_users - 1].role);
	if (users[size_of_users - 1].role == 1) {
		num_of_admins++;
	}
	users[size_of_users - 1].access = 1;
}

extern void change_user() {
	char c, *login_buf;
	int j = 0, buf = -1, flag = 0, choise_0 = 0;
	printf("   Введите логин для поиска\n   ");
	scanf_s("%s", user_buf.login, STR_SIZE);
	for (int i = 0; i < size_of_users; i++) {
		if (strcmp(user_buf.login, users[i].login) == 0) {
			flag++;
			printf("   Пользователь найден\n");
			printf("   1.Изменить логин\n");
			printf("   2.Изменить пароль\n");
			printf("   3.Изменить роль\n");
			printf("   4.Изменить доступ\n");
			printf("   0.Выйти в меню\n");
			printf("   Выберите действие\n   ");
			scanf_s("%d", &choise_0);
			switch (choise_0) {
			case 0: 
				administrator_menu();
				break;
			case 1: 
				printf("   Введите новый логин\n   ");
				scanf_s("%s", users[i].login, STR_SIZE);
				break;
			case 2:
				printf("   Введите новый пароль\n   ");
				while ((c = _getch()) != '\r')
				{
					users[i].password[j++] = c;
					_putch('*');
				}
				while (j<STR_SIZE-2)
				{
					users[i].password[j++] = NULL;
				}
				break;
			case 3:
				printf("   Введите новую роль (0-пользователь, 1-администратор)\n   ");
				buf = users[i].role;
				scanf_s("%d", &users[i].role);
				number_check(users[i].role);
				number_0_or_1(users[i].role);
				if (buf > users[i].role) {
					num_of_admins--;
				}
				else if (buf < users[i].role) {
					num_of_admins++;
				}
				break;
			case 4:
				buf = users[i].access;
				printf("   Введите новый код доступа (0-блокировать, 1-одобрить)\n   ");
				scanf_s("%d", &users[i].access);
				number_check(users[i].access);
				number_0_or_1(users[i].access);
				if (users[i].access > buf && users[i].role == 1) {
					num_of_admins++;
				}
				else if (users[i].access < buf && users[i].role == 1) {
					num_of_admins--;
				}
				break;
			default:
				printf("   Ошибка\n");
			}
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Такой учетной записи не существует\n");
	}
}

extern void delete_user() {
	int flag = 0;
	printf("   Введите логин для поиска пользователя, которого хотите удалить\n   ");
	scanf_s("%s", user_buf.login, STR_SIZE);
	for (int i = 0; i < size_of_users; i++) {
		if (strcmp(user_buf.login, users[i].login) == 0) {
			flag++;
			if (users[i].role == 1 && num_of_admins == 1) {
				printf("   Нельзя удалить последнего администратора !!!\n");
			}
			else {
				if (users[i].role == 1) {
					num_of_admins--;
				}
				for (int j = i; j < size_of_users - 1; j++) {
					users[j] = users[j + 1];
				}
				users[size_of_users - 1] = empty_user;
				size_of_users--;
				printf("   Пользователь удален\n");
			}
		}
		else { }
	}
	if (flag == 0) {
		printf("\n   Такой учетной записи не существует\n");
	}
}

extern void check_users() {
	int flag = 0;
	for (int i = 0; i < size_of_users; i++) {
		if (users[i].access == 0) {
			flag++;
			switch (users[i].role) {
			case 0:
				printf("   Пользователь %s хочет получить права пользователя\n", users[i].login);
				break;
			case 1:
				printf("   Пользователь %s хочет получить права администратора\n", users[i].login);
				break;
			}
			printf("   0.Заблокировать\n   1.Подтвердить запись\n   Выберите действие\n   ");
			scanf_s("%d", &choise);
			number_check(choise);
			number_0_or_1(choise);
			if (choise == 1) {
				users[i].access = 1;
			}
			else if(choise == 0) { 
			}
			else {
				printf("   Некорректное значение\n");
			}
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Неподтвержденные учетные записи отсутствуют\n");
	}
}

extern void get_memory_for_users() {
	User* users_new;
	users_new =(User*)calloc(size_of_users,sizeof(User));
	for (int i = 0; i < size_of_users-1; i++)
	{
		users_new[i] = users[i];
	}
	users = NULL;
	users = users_new;
}

extern void get_memory_for_data() {
	Bus* buses_new;
	buses_new = (Bus*)calloc(size_of_buses, sizeof(Bus));
	for (int i = 0; i < size_of_buses - 1; i++)
	{
		buses_new[i] = buses[i];
	}
	buses = NULL;
	buses = buses_new;
}

extern void writing_users_in_file() {
	if (fopen_s(&f1, "file1.dat", "w+") == 0)
	{
		for (int i = 0; i < size_of_users; i++) {
			fwrite(&users[i], sizeof(User), 1, f1);
		}
		fclose(f1);
	}
	else {
		printf("   Файл не существует\n");
	}
}

extern void print_data() {
	if (size_of_buses == 0) {
		printf("   Информация о рейсах отсутствует\n");
	}
	else {
		printf("\n   Список рейсов\n");
		printf("——————————————————————————————————————"
		    "————————————————————————————————————————————————"
		    "——————————————————————————————————\n"
			"| № | тип автобуса | пункт назначения | дата отпр  | время отпр | время приб | стоимость | кол-во ост | кол-во прод |\n "
			"——————————————————————————————————————"
			"———————————————————————————————————————————————"
			"——————————————————————————————————\n");
		for (int i = 0; i < size_of_buses; i++) {
			printf("|%3d|%14s|%18s|%12s|%12s|%12s|%11d|%12d|%13d|\n", buses[i].number_of_trip, buses[i].type_of_bus, buses[i].destination, buses[i].depature_date, buses[i].depature_time, buses[i].arrival_time, buses[i].cost_of_ticket, buses[i].number_of_free, buses[i].number_of_sold);
			printf("——————————————————————————————————————"
		    "————————————————————————————————————————————————"
	        "——————————————————————————————————\n");
		}
	}
}

extern void print_one_data(int num) {
	printf("——————————————————————————————————————"
		"————————————————————————————————————————————————"
		"——————————————————————————————————\n"
		"| № | тип автобуса | пункт назначения | дата отпр  | время отпр | время приб | стоимость | кол-во ост | кол-во прод |\n "
		"——————————————————————————————————————"
		"———————————————————————————————————————————————"
		"——————————————————————————————————\n");
		printf("|%3d|%14s|%18s|%12s|%12s|%12s|%11d|%12d|%13d|\n", buses[num].number_of_trip, buses[num].type_of_bus, buses[num].destination, buses[num].depature_date, buses[num].depature_time, buses[num].arrival_time, buses[num].cost_of_ticket, buses[num].number_of_free, buses[num].number_of_sold);
		printf("——————————————————————————————————————"
		"————————————————————————————————————————————————"
			"——————————————————————————————————\n");
}

extern void add_data() {
	size_of_buses++;
	get_memory_for_data();

	printf("   Введите номер нового рейса:\n   ");
	scanf_s("%d", &buses[size_of_buses - 1].number_of_trip);
	number_check(buses[size_of_buses - 1].number_of_trip);
	negative_number_check(buses[size_of_buses - 1].number_of_trip);

	printf("   Введите тип автобуса:\n   ");
	scanf_s("%s", buses[size_of_buses - 1].type_of_bus, STR_SIZE);

	printf("   Введите пункт назначения:\n   ");
	scanf_s("%s", buses[size_of_buses - 1].destination, STR_SIZE);

	printf("   Введите дату отправления:\n   ");
	scanf_s("%s", buses[size_of_buses - 1].depature_date, STR_SIZE);
	data_check(buses[size_of_buses - 1].depature_date);

	printf("   Введите время отправления:\n   ");
	scanf_s("%s", buses[size_of_buses - 1].depature_time, STR_SIZE);
	time_check(buses[size_of_buses - 1].depature_time);

	printf("   Введите время прибытия:\n   ");
	scanf_s("%s", buses[size_of_buses - 1].arrival_time, STR_SIZE);
	time_check(buses[size_of_buses - 1].arrival_time);

	printf("   Введите стоимость 1 билета:\n   ");
	scanf_s("%d", &buses[size_of_buses - 1].cost_of_ticket);
	number_check(buses[size_of_buses - 1].cost_of_ticket);
	negative_number_check(buses[size_of_buses - 1].cost_of_ticket);

	printf("   Введите количество оставшихся билетов:\n   ");
	scanf_s("%d", &buses[size_of_buses - 1].number_of_free);
	number_check(buses[size_of_buses - 1].number_of_free);
	negative_number_check(buses[size_of_buses - 1].number_of_free);

	printf("   Введите количество проданных билетов:\n   ");
	scanf_s("%d", &buses[size_of_buses - 1].number_of_sold);
	number_check(buses[size_of_buses - 1].number_of_sold);
	negative_number_check(buses[size_of_buses - 1].number_of_sold);
}

extern void change_data() {
	int j = 0, buf = -1, flag=0, total = 0, choise_0 = 0;
	printf("   Введите номер рейса для поиска\n   ");
	scanf_s("%d", &bus_buf.number_of_trip);
	number_check(bus_buf.number_of_trip);
	for (int i = 0; i < size_of_buses; i++) {
		if (bus_buf.number_of_trip == buses[i].number_of_trip) {
			flag++;
			printf("   Рейс найден\n");
			printf("   1.Изменить номер рейса\n");
			printf("   2.Изменить тип автобуса\n");
			printf("   3.Изменить пункт назначения\n");
			printf("   4.Изменить дату отправления\n");
			printf("   5.Изменить время отправления\n");
			printf("   6.Изменить время прибытия\n");
			printf("   7.Изменить стоимость 1 билета\n");
			printf("   8.Изменить количество оставшихся билетов (кол-во проданных билетов обновляется автоматически)\n");
			printf("   9.Изменить количесвто проданных билетов (кол-во оставшихся билетов обновляется автоматически)\n");
			printf("   0.Выйти в меню\n");
			printf("   Выберите действие\n   ");
			scanf_s("%d", &choise_0);
			switch (choise_0) {
			case 0:
				administrator_menu();
				break;
			case 1:
				printf("   Введите новый номер рейса\n   ");
				scanf_s("%d", &buses[i].number_of_trip);
				number_check(buses[i].number_of_trip);
				negative_number_check(buses[i].number_of_trip);
				break;
			case 2:
				printf("   Введите новый тип автобуса\n   ");
				scanf_s("%s", buses[i].type_of_bus, STR_SIZE);
				break;
			case 3:
				printf("   Введите новый пункт назначения\n   ");
				scanf_s("%s", buses[i].destination, STR_SIZE);
				break;
			case 4:
				printf("   Введите новую дату отправления\n   ");
				scanf_s("%s", buses[i].depature_date, STR_SIZE);
				data_check(buses[i].depature_date);
				break;
			case 5:
				printf("   Введите новое время отправления\n   ");
				scanf_s("%s", buses[i].depature_time, STR_SIZE);
				time_check(buses[i].depature_time);
				break;
			case 6:
				printf("   Введите новое время прибытия\n   ");
				scanf_s("%s", buses[i].arrival_time, STR_SIZE);
				time_check(buses[i].arrival_time);
				break;
			case 7:
				printf("   Введите новую стоимость 1 билета\n   ");
				scanf_s("%d", &buses[i].cost_of_ticket);
				number_check(buses[i].cost_of_ticket);
				negative_number_check(buses[i].cost_of_ticket);
				break;
			case 8:
				total = buses[i].number_of_free + buses[i].number_of_sold;
				printf("   Введите количество оставшихся билетов\n   ");
				scanf_s("%d", &buses[i].number_of_free);
				number_check(buses[i].number_of_free);
				negative_number_check(buses[i].number_of_free);
				buses[i].number_of_sold = total - buses[i].number_of_free;
				break;
			case 9:
				total = buses[i].number_of_free + buses[i].number_of_sold;
				printf("   Введите количество проданных билетов\n   ");
				scanf_s("%d", &buses[i].number_of_sold);
				number_check(buses[i].number_of_sold);
				negative_number_check(buses[i].number_of_sold);
				buses[i].number_of_free = total - buses[i].number_of_sold;
				break;
			default:
				printf("   Ошибка\n");
			}
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Такой учетной записи не существует\n");
	}
}

extern void delete_data() {
	int flag = 0;
	printf("   Введите номер рейса для поиска данных, которые хотите удалить\n   ");
	scanf_s("%d", &bus_buf.number_of_trip);
	number_check(bus_buf.number_of_trip);
	for (int i = 0; i < size_of_buses; i++) {
		if (bus_buf.number_of_trip == buses[i].number_of_trip) {
			flag++;
			for (int j = i; j < size_of_buses - 1; j++) {
				buses[j] = buses[j + 1];
			}
			buses[size_of_users - 1] = empty_bus;
			size_of_buses--;
			printf("   Данные рейса удалены\n");
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Такого рейса не существует\n");
	}
}

extern void writing_data_in_file() {
	if (fopen_s(&f2, "file2.dat", "w+") == 0)
	{
		for (int i = 0; i < size_of_buses; i++) {
			fwrite(&buses[i], sizeof(Bus), 1, f2);
		}
		fclose(f2);
		printf("   Данные записаны в файл\n");
	}
	else {
		printf("   Файл не существует\n");
	}
}

extern void buying_tickets() {
	int flag = 0, number = 0;
	printf("   Введите номер рейса, на который хотите купить билет\n   ");
	scanf_s("%d", &bus_buf.number_of_trip);
	number_check(bus_buf.number_of_trip);
	printf("   Введите количество билетов\n   ");
	scanf_s("%d", &number);
	number_check(number);
	negative_number_check(number);
	for (int i = 0; i < size_of_buses; i++) {
		if (bus_buf.number_of_trip == buses[i].number_of_trip) {
			flag++;
			if (buses[i].number_of_free >= number) {
				printf("   Билеты куплены\n");
				printf("   Общая стоимость %d\n", number* buses[i].cost_of_ticket);
				buses[i].number_of_free -= number;
				buses[i].number_of_sold += number;
			}
			else if (buses[i].number_of_free <= number) {
				printf("   Вы ввели слишком большое кол-во билетов. Свободных билетов осталось %d\n   ", buses[i].number_of_free);
			}
			else if (buses[i].number_of_free == 0) {
				printf("   Свободных мест не осталось\n");
			}
			else {
				printf("   Свободных мест всего %d\n", buses[i].number_of_free);
			}
		}
		else {
		}
	}
	if (flag == 0) {
		printf("\n   Такого рейса не существует\n");
	}
}

extern void sort_data() {
	int point = -1;
	printf("   Сортировка по _____\n");
	printf("   1.Номеру рейса\n");
	printf("   2.Дате отправления\n");
	printf("   3.Времени отправления\n");
	printf("   4.Стоимости 1 билета\n");
	printf("   5.Количеству свободных мест\n");
	printf("   0.Вернуться назад\n");
	printf("   Выберите действие\n   ");
	scanf_s("%d", &point);
	number_check(point);
	switch (point) {
	case 0:
		if (data_mode == 1) {
			administrator_menu();
		}
		else if (data_mode == 0) {
			user_menu();
		}
		break;
	case 1:
		sort_number_of_trip();
		break;
	case 2:
		sort_depature_date();
		break;
	case 3:
		sort_depature_time();
		break;
	case 4:
		sort_cost_of_trip();
		break;
	case 5:
		sort_number_of_free();
		break;
	default:
		printf("   Некорректный выбор\n");
	}
}

extern void sort_depature_date() {
	for (int i = 1; i <= size_of_buses - 1; i++)
	{
		int j = i;
		while (strcmp(buses[j - 1].depature_date, buses[j].depature_date)>0 && j >= 1)
		{
			bus_buf = buses[j];
			buses[j] = buses[j - 1];
			buses[j - 1] = bus_buf;
			j--;
		}
	}
	printf("   Сортировка выполнена успешно\n");
}

extern void sort_depature_time() {
	for (int i = 1; i <= size_of_buses - 1; i++)
	{
		int j = i;
		while (strcmp(buses[j - 1].depature_time, buses[j].depature_time) > 0 && j >= 1)
		{
			bus_buf = buses[j];
			buses[j] = buses[j - 1];
			buses[j - 1] = bus_buf;
			j--;
		}
	}
	printf("   Сортировка выполнена успешно\n");
}

extern void sort_number_of_trip() {
	for (int i = 1; i <= size_of_buses - 1; i++)
	{
		int j = i;
		while (buses[j - 1].number_of_trip > buses[j].number_of_trip && j >= 1)
		{
			bus_buf = buses[j];
			buses[j] = buses[j - 1];
			buses[j - 1] = bus_buf;
			j--;
		}
	}
	printf("   Сортировка выполнена успешно\n");
}

extern void sort_cost_of_trip() {
	for (int i = 1; i <= size_of_buses - 1; i++)
	{
		int j = i;
		while (buses[j - 1].cost_of_ticket > buses[j].cost_of_ticket && j >= 1)
		{
			bus_buf = buses[j];
			buses[j] = buses[j - 1];
			buses[j - 1] = bus_buf;
			j--;
		}
	}
	printf("   Сортировка выполнена успешно\n");
}

extern void sort_number_of_free() {
	for (int i = 1; i <= size_of_buses - 1; i++)
	{
		int j = i;
		while (buses[j - 1].number_of_free > buses[j].number_of_free && j >= 1)
		{
			bus_buf = buses[j];
			buses[j] = buses[j - 1];
			buses[j - 1] = bus_buf;
			j--;
		}
	}
	printf("   Сортировка выполнена успешно\n");
}

extern void find_data() {
	int point = -1;
	printf("   Поиск по _____\n");
	printf("   1.Номеру рейса\n");
	printf("   2.Типу автобуса\n");
	printf("   3.Пункту назначения\n");
	printf("   4.Дате отправления\n");
	printf("   5.Стоимости 1 билета\n");
	printf("   0.Вернуться назад\n");
	printf("   Выберите действие\n   ");
	scanf_s("%d", &point);
	number_check(point);
	switch (point) {
	case 0:
		if (data_mode == 1) {
			administrator_menu();
		}
		else if (data_mode == 0) {
			user_menu();
		}
		break;
	case 1:
		find_number_of_trip();
		break;
	case 2:
		find_type_of_bus();
		break;
	case 3:
		find_destination();
		break;
	case 4:
		find_depature_date();
		break;
	case 5:
		find_cost_of_ticket();
		break;
	default:
		printf("   Некорректный выбор\n");
	}
}

extern void find_number_of_trip() {
	int counter = 0;
	printf("   Введите номер рейса\n   ");
	scanf_s("%d", &bus_buf.number_of_trip);
	number_check(bus_buf.number_of_trip);
	for (int i = 0; i < size_of_buses; i++) {
		if (buses[i].number_of_trip == bus_buf.number_of_trip) {
			print_one_data(i);
		}
		else {
			counter++;
		}
	}
	if (size_of_buses == counter) {
		printf("   Автобусов с таким номером рейса не существует\n");
	}
}

extern void find_type_of_bus() {
	int counter = 0;
	printf("   Введите тип автобуса\n   ");
	scanf_s("%s", bus_buf.type_of_bus, STR_SIZE);
	for (int i = 0; i < size_of_buses; i++) {
		if (strcmp(buses[i].type_of_bus,bus_buf.type_of_bus)==0) {
			print_one_data(i);
		}
		else {
			counter++;
		}
	}
	if (size_of_buses == counter) {
		printf("   Рейсов с таким типом автобуса не существует\n");
	}
}

extern void find_destination() {
	int counter = 0;
	printf("   Введите пункт назначения\n   ");
	scanf_s("%s", bus_buf.destination, STR_SIZE);
	for (int i = 0; i < size_of_buses; i++) {
		if (strcmp(buses[i].destination, bus_buf.destination) == 0) {
			print_one_data(i);
		}
		else {
			counter++;
		}
	}
	if (size_of_buses == counter) {
		printf("   Рейсов с таким пунктом назначения не существует\n");
	}
}

extern void find_depature_date() {
	int counter = 0;
	printf("   Введите дату отправления\n   ");
	scanf_s("%s", bus_buf.depature_date, STR_SIZE);
	data_check(bus_buf.depature_date);
	for (int i = 0; i < size_of_buses; i++) {
		if (strcmp(buses[i].depature_date, bus_buf.depature_date) == 0) {
			print_one_data(i);
		}
		else {
			counter++;
		}
	}
	if (size_of_buses == counter) {
		printf("   Рейсов с такой датой отправления не существует\n");
	}
}

extern void find_cost_of_ticket() {
	int counter = 0;
	printf("   Введите стоимость билета\n   ");
	scanf_s("%d", &bus_buf.cost_of_ticket);
	number_check(bus_buf.cost_of_ticket);
	for (int i = 0; i < size_of_buses; i++) {
		if (buses[i].cost_of_ticket == bus_buf.cost_of_ticket) {
			print_one_data(i);
		}
		else {
			counter++;
		}
	}
	if (size_of_buses == counter) {
		printf("   Рейсов с такой стоимостью билета не существует\n");
	}
}

extern void create_user_without_access() {
	char c;
	int i = 0;
	size_of_users++;
	get_memory_for_users();
	do {
		printf("\n   Введите логин нового пользователя. Логин не должен повторяться!:\n   ");
		scanf_s("%s", users[size_of_users - 1].login, STR_SIZE);
	} while (verify_login() != 0);
	printf("\n   Введите пароль нового пользователя:\n   ");
	while ((c = _getch()) != '\r')
	{
		users[size_of_users - 1].password[i++] = c;
		_putch('*');
	}
	while (i < STR_SIZE - 2) {
		users[size_of_users - 1].password[i++] = NULL;
	}
	printf("\n   Выберите желаемую роль (0-пользователь, 1-администратор):\n   ");
	scanf_s("%d", &users[size_of_users - 1].role);
	number_check(users[size_of_users - 1].role);
	number_0_or_1(users[size_of_users - 1].role);
	if (users[size_of_users - 1].role == 1) {
		num_of_admins++;
	}
	users[size_of_users - 1].access = 0;
}

extern void clear_memory() {
	free(users);
	free(buses);
}

extern void data_check(char* mas) {
	int length = strlen(mas);
	int* mas_of_nums = translate_letters_to_numbers(mas);
	int date = mas_of_nums[0] * 10 + mas_of_nums[1];
	int month = mas_of_nums[3] * 10 + mas_of_nums[4];
	int year = mas_of_nums[6] * 1000 + mas_of_nums[7] * 100 + mas_of_nums[8] * 10 + mas_of_nums[9];
	if (length == 10 && mas_of_nums[2] == -1 && mas_of_nums[5] == -1 && year == 2022 && month >= 5 && month <= 12) {
		if ((month == 6 || month == 9 || month == 11) && date >= 1 && date <= 30) {
		}
		else if ((month == 7 || month == 8 || month == 10 || month == 12) && date >= 1 && date <= 31) {
		}
		else if (month == 5 && date >= 25 && date <= 31) {
		}
		else {
			printf("   Некорректное значение. Повторите попытку (ДД.ММ.ГГГГ)\n   ");
			scanf_s("%s", mas, STR_SIZE);
			data_check(mas);
		}
	}
	else {
		printf("   Некорректное значение. Повторите попытку (ДД.ММ.ГГГГ)\n   ");
		scanf_s("%s", mas, STR_SIZE);
		data_check(mas);
	}
}

extern void time_check(char* mas) {
	int length = strlen(mas);
	int* mas_of_nums = translate_letters_to_numbers(mas);
	int hours = mas_of_nums[0] * 10 + mas_of_nums[1];
	int minutes = mas_of_nums[3] * 10 + mas_of_nums[4];
	if (length == 5 && mas_of_nums[2] == -1 && hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59) {
	}
	else {
		printf("   Некорректное значение. Повторите попытку (ЧЧ.ММ)\n   ");
		scanf_s("%s", mas, STR_SIZE);
		time_check(mas);
	}
}

extern int* translate_letters_to_numbers(char* str) {
	int flag = 0;
	int len = strlen(str);
	int* mas = (int*)calloc(len, sizeof(int));
	for (int i = 0; i < len; i++) {
		switch (str[i]) {
		case '.':
			mas[i] = -1;
			break;
		case '0':
			mas[i] = 0;
			break;
		case '1':
			mas[i] = 1;
			break;
		case '2':
			mas[i] = 2;
			break;
		case '3':
			mas[i] = 3;
			break;
		case '4':
			mas[i] = 4;
			break;
		case '5':
			mas[i] = 5;
			break;
		case '6':
			mas[i] = 6;
			break;
		case '7':
			mas[i] = 7;
			break;
		case '8':
			mas[i] = 8;
			break;
		case '9':
			mas[i] = 9;
			break;
		case '\0':
			break;
		default:
			flag++;
		}
	}
	if (flag != 0) {
		printf("   Ошибка!!!\n");
	}
	return mas;
}

extern void number_check(int num) {
	if (cin.get() != '\n') {
		do {
			printf("   Некорректное значение. Повторите попытку\n   ");
			scanf_s("%d", &num);
		} while (cin.get() != '\n');
	}
}

extern void negative_number_check(int num) {
	if (num < 0) {
		do {
			printf("   Некорректное значение. Повторите попытку\n   ");
			scanf_s("%d", &num);
			number_check(num);
		} while (num < 0);
	}
}

extern void number_0_or_1(int num) {
	if (num != 0 && num != 1) {
		do {
			printf("   Некорректный выбор. Повторите попытку\n   ");
			scanf_s("%d", &num);
			number_0_or_1(num);
		} while (num != 0 && num != 1);
	}
}
