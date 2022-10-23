#pragma once

//функции для работы с учетными записями
extern void input_login_and_password();             //ввод логина и пароля
extern int verify_login();                          //проверка логина на уникальность
extern void find_user(char* login, char* password); //поиск учетной записи
extern void writing_1_user_in_file();            //добавление первого администратора
extern void writing_users_to_array();            //запись пользователей в массив
extern void print_list_of_users();               //вывод списка учетных записей
extern void add_user();                          //добавление учетной записи администратором
extern void change_user();                       //изменение учетной записи
extern void delete_user();                       //удаление учетной записи
extern void check_users();                       //проверка неподтвержденных записей
extern void get_memory_for_users();              //выделение памяти для массива пользователей
extern void writing_users_in_file();             //запись пользователей в файл       
extern void create_user_without_access();        //создание учетной записи без входа в аккаунт

//функции вывода меню
extern void administrator_menu();                //меню администратора
extern void user_menu();                         //меню пользователя

//функции для работы с данными
extern void writing_data_to_array();             //запись данных в массив
extern void print_data();                        //вывод данных о всех рейсах
extern void print_one_data(int);                 //вывод данных об 1 рейсе
extern void add_data();                          //добавление данных
extern void change_data();                       //изменение данных
extern void delete_data();                       //удаление данных
extern void get_memory_for_data();               //выделение памяти для массива данных
extern void writing_data_in_file();              //запись данных в файл

//индивидуальное задание
extern void buying_tickets();                    //покупка билетов в нужном количестве

//функции сортировки
extern void sort_data();                         //функция сортировки
extern void sort_number_of_trip();               //функция сортировки по номеру рейса
extern void sort_cost_of_trip();                 //функция сортировки по стоимости 1 билета
extern void sort_number_of_free();               //функция сортировки по кол-ву свободных мест
extern void sort_depature_date();
extern void sort_depature_time();
extern void quick_sort_depature_date(int, int);  //функция сортировки по дате отправления
extern void quick_sort_depature_time(int, int);  //функция сортировки по времени отправления

//функции поиска
extern void find_data();             //функция поиска данных
extern void find_number_of_trip();   //поиск по номеру рейса
extern void find_type_of_bus();      //поиск по типу автобуса
extern void find_destination();      //поиск по пунку назначения
extern void find_depature_date();    //поиск по дате отправления
extern void find_cost_of_ticket();   //поиск по стоимости 1 билета

//функция очистки памяти динамическихх массивов
extern void clear_memory();

//проверка на ввод числа
extern void number_check(int);          //проверка на ввод только чисел
extern void negative_number_check(int); //проверка отрицательного числа
extern void number_0_or_1(int);         //проверка на ввод только 0 или 1
extern void data_check(char*);          //проверка на ввод даты
extern void time_check(char*);          //проверка на ввод времени
extern int* translate_letters_to_numbers(char*); //перевод массива символов в числа

extern int data_mode; //режим работы с данными в текущий момент
extern int choise; //выбор пользователя в меню
