#ifndef CURSCLN_MENUSRV_H
#define CURSCLN_MENUSRV_H

#include "..\Utils\stdafx.h"
#include "User.h"
#include "Company.h"

using namespace std;

class A_menu {
private:
    SOCKET sock;
public:
    //static vector<std::string> vcMainMenu = {"Логин", "Регистрация", "Выход"};
    //All_info ai;
    std::string strMenuMain = "-=-=-=-=  М е н ю  =-=-=-=-#Логин#Регистрация#Логаут#Выход";
    std::string strMenuAdmin = "\tАдминистратор#Просмотр инвестиционных проектов#Добавление#Удаление#Сохранение информации в бд#Поиск#Сортировка инвестиционных проектов#Ранжировать инвестиционные проекты#Вывести результат ранжирования ИП#Редактировать#Выход";
    std::string strMenuAdminAdd = "Вы хотите добавить: #Новые компании#Новых экспертов#Новые проекты#Назад";
    std::string strMenuAdminDel = "Вы хотите удалить: #Компанию#Экспертов#Проекты#Назад";
    std::string strMenuAdminSave = "Вы хотите сохранить информацию о:#Компании#Экспертах#Проектах#Назад";
    std::string strMenuAdminRanking = "Ранжировать инвестиционные проекты:#Осуществить попарное сравнение проектов#Найти оценки#Вычислить веса проектов#Составить порядок предпочтений#Назад";
    std::string strMenuAdminEdit = "Вы хотите редактировать данные:#Компании#Экспертов#Проектов#Назад";
    std::string strMenuCompany = "\tКомпания#Ввод данных#Редактировать данные#Добавить проект#Сохранение информации в бд#Удаление данных о проекте#Выход";
    std::string strMenuCompanyEdit = "Вы хотите редактировать данные:#Компании#Проектов#Назад";
    std::string strMenuCompanySave = "Вы хотите сохранить информацию о:#Компании#Проектах#Назад";
    std::string strMenuExpert = "\tЭксперт#Выставление оценок#Редактировать данные о себе#Просмотреть информацию об инвестиционных проектах#Выход";

    // Конструктор
    A_menu() {
        sock = NULL;
    };

    explicit A_menu(SOCKET connection) {
        sock = connection;
    }

    // Деструктор
    ~A_menu() = default;

    static int changeMenu(const std::string &str, int cntMenu, const std::string &begMenu, int back) {
        int choice = -1;
        std::string endMenu = "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        cout << endl << begMenu << endl;
        cout << str << endl;
        if (back == 0) cout << " 0 - Выход" << endl;
        else cout << " 0 - Назад" << endl;
        cout << endMenu.substr(0, begMenu.size()) << endl;
        cout << "Выберите: ";
        do {
            Checks::CheckInput(choice);
            if ((choice > cntMenu) || (choice < 0)) {
                cout << "Такого варианта нет в меню, попробуйте снова" << endl;
            }
        } while ((choice < 0) || (choice > cntMenu));
        std::cin.clear();
        return choice;
    }

    static size_t choiceMenu(size_t cntMenu, const std::string &strMenu) {
        cout << " 0 - --= ОТМЕНА =-- " << endl;
        cout << "Выберите " << strMenu << ": ";
        size_t ch = -1;
        do {
            std::cin >> ch;
            fflush(stdin);
        } while ((ch < 0) || (ch > cntMenu));
        return ch;
    }

    static bool Confirm(const std::string &msg) {
        //        int ls;
        //        cout << msg << " (Y/Д/[N/Н]): ";
        //        do {
        //            ls = cin.get();
        //        } while (((ls != 'Y') && (ls != 'y') && (ls != 'N') && (ls != 'n') && (ls != 'Д') && (ls != 'д') &&
        //                  (ls != 'Н') && (ls != '')) || (ls == 13));
        //        if ((ls == 'Y') || (ls == 'y') || (ls == 'Д') || (ls == 'д')) return true;
        //        else if ((ls == 'N') || (ls == 'n') || (ls == 'Н') || (ls == 'н') || (ls == 13)) return false;
        //        else return false;
        return true;
    }

    static int menuMain() {
        std::string strMenu = " 1 - Логин\n 2 - Регистрация";
        return changeMenu(strMenu, 6, "-=-=-=-=  М е н ю  =-=-=-=-", 0);
        //        return vcChoice("-=-=-=-=  М е н ю  =-=-=-=-", vcMainMenu, 0)
    }

    void menuAdmin() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdmin);
        //sendMenu(sock, split(strMenuAdmin));
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            size_t i = atoi(p);
            std::cout << "<- " << split(strMenuAdmin)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    menuAdminAdd();
                    break;
                case 3:
                    menuAdminDel();
                    break;
                case 4:
                    menuAdminSave();
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    menuAdminRanking();
                    break;
                case 8:
                    break;
                case 9:
                    menuAdminEdit();
                    break;
                case 10:
                    sendString(sock, "menu");
                    sendString(sock, strMenuMain);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdmin);
        }
    }

    void menuAdminAdd() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdminAdd);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuAdminAdd)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    sendString(sock, "menu");
                    sendString(sock, strMenuAdmin);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdminAdd);
        }
    }

    void menuAdminDel() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdminDel);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuAdminDel)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    sendString(sock, "menu");
                    sendString(sock, strMenuAdmin);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdminDel);
        }
    }

    void menuAdminSave() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdminSave);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuAdminSave)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    sendString(sock, "menu");
                    sendString(sock, strMenuAdmin);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdminSave);
        }
    }

    void menuAdminRanking() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdminRanking);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuAdminRanking)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    sendString(sock, "menu");
                    sendString(sock, strMenuAdmin);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdminRanking);
        }
    }

    void menuAdminEdit() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdminEdit);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuAdminEdit)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    sendString(sock, "menu");
                    sendString(sock, strMenuAdmin);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuAdminEdit);
        }
    }

    void menuCompany() {
        sendString(sock, "menu");
        sendString(sock, strMenuCompany);
        //sendMenu(sock, split(strMenuAdmin));
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        int c = -1;
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuCompany)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    menuCompanyEdit();
                    break;
                case 3:
                    //menuCompanyEdit();
                    break;
                case 4:
                    menuCompanySave();
                    break;
                case 5:
                    break;
                case 6:
                    sendString(sock, "menu");
                    sendString(sock, strMenuMain);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuCompany);
        }
    }

    void menuCompanyEdit() {
        sendString(sock, "menu");
        sendString(sock, strMenuCompanyEdit);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuCompanyEdit)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    sendString(sock, "menu");
                    sendString(sock, strMenuCompany);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuCompanyEdit);
        }
    }

    void menuCompanySave() {
        sendString(sock, "menu");
        sendString(sock, strMenuCompanySave);
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuCompanySave)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    sendString(sock, "menu");
                    sendString(sock, strMenuCompany);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuCompanySave);
        }
    }

    void menuExpert() {
        sendString(sock, "menu");
        sendString(sock, strMenuExpert);
        //sendMenu(sock, split(strMenuExpert));
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        int c = -1;
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            int i = atoi(p);
            std::cout << "<- " << split(strMenuExpert)[i] << endl;
            switch (i) {
                case 1:
                    break;
                case 2:
                    //menuAdminAdd();
                    break;
                case 3:
                    //menuCompanyEdit();
                    break;
                case 4:
                    sendString(sock, "menu");
                    sendString(sock, strMenuMain);
                    return;
            }
            sendString(sock, "menu");
            sendString(sock, strMenuExpert);
        }
    }

    void start() {
        int c;
        char p[200], com[200];//основной буфер и команда
        char curU[20];
        curU[0] = '\0';
        com[0] = '\0';
        p[0] = '\0';
        std::cout << "Соединение установлено." << std::endl;
        char *message = new char[100];
        strcat(p, "Server connected...\n");
        //send((SOCKET)newS, p, sizeof(p), 0);//посылаем приветствие при соединении
        std::string strMenu = "-=-=-=-=  М е н ю  =-=-=-=-#Логин#Регистрация#Логаут#Выход";
        sendString(sock, "Server connected...\n");
        sendString(sock, "menu");
        sendString(sock, strMenu);
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //пока принимаются команды
            command = p;
            //std::cout << "<- " << com << std::endl;
            int i = atoi(command.c_str());
            if (command == "1") {//подключение пользователя
//                tUser user{};
//                sendString(sock, "data");
//                sendString(sock, "Введите логин: ");
//                user.login = takeString(sock);
//                // ищем пользователя в базе
//                // если находим
//                sendString(sock, "Введите пароль: ");
//                user.pass = takeString(sock);
//                sendString(sock, "end");
//                std::cout << "login: " << user.login << " - " << user.pass << endl;
                //if user = Admin
                //menuAdmin();
                menuCompany();
            }
            if (command == "2") {//подключение пользователя
//                tUser user{};
//                sendString(sock, "data");
//                sendString(sock, "Введите логин: ");
//                user.login = takeString(sock);
//                // ищем пользователя в базе
//                // если находим
//                sendString(sock, "Введите пароль: ");
//                user.pass = takeString(sock);
//                sendString(sock, "end");
//                std::cout << "register: " << user.login << " - " << user.pass << endl;
//
//                menuExpert();
                UserSock user(sock);
                user.enterUser();
                std::cout << user;
                menuAdmin();
            }
            if (command == "3") {//отключение пользователя
                //cout << "User " << curU << " logout" << endl;
                sendString(sock, "exit");
                closesocket(sock);//закрываем сокет
                return;
            }
            if (command == "4") {//выход
                sendString(sock, "exit");
                closesocket(sock);//закрываем сокет
                exit(EXIT_SUCCESS);
            }
        }
    }

    //    // Просмотр информации (case 1)
    //    void view_info() {
    //        int v;
    //        while (true) {
    //            system("cls");
    //            v = menuView();
    //            switch (v) {
    //                case 1: {
    //                    system("cls");
    //                    ai.printHos();
    //                    system("pause");
    //                    break;
    //                }
    //                case 2: {
    //                    system("cls");
    //                    std::cout << "Попытка сохранить данные в файл... Ожидайте!" << endl;
    //                    ofstream fout;
    //                    fout.exceptions(ofstream::badbit);
    //                    try {
    //                        fout.open("lab5.txt");
    //                        //else fout.open("lab5.txt", ios::app | ios_base::in);
    //                        ai.printHos(fout);
    //                        cout << "Данные сохранены успешно!" << endl;
    //                    }
    //                    catch (const ofstream::failure &e) {
    //                        cout << "Ошибка открытия файла (lab5.txt)!" << endl;
    //                    }
    //                    fout.close();
    //                    system("pause");
    //                    break;
    //                }
    //                case 0:
    //                    return;
    //                default:
    //                    cout << "Такого действия нет. Введите другой выбор.\n";
    //                    break;
    //            }
    //        }
    //    }
    //
    //    // Добавление информации (case 2)
    //    void add_info() {
    //        int v;
    //        while (true) {
    //            system("cls");
    //            v = menuAdd();
    //            if (v != 0) {
    //                ai.addMedic(Departs[v - 1]);
    //            }
    //            break;
    //        }
    //    }
    //
    //    // Редактирование информации (case 3)
    //    void edit_info() {
    //        std::string v;
    //        while (true) {
    //            system("cls");
    //            v = menuEdit();
    //            if (v.length() != 0) {
    //                ai.editMedic(v);
    //            }
    //            break;
    //        }
    //    }
    //
    //    // Удаление информации (case 4)
    //    void delete_info() {
    //        int v;
    //        while (true) {
    //            system("cls");
    //            v = menuDelete();
    //            switch (v) {
    //                case 1: {  //Удалить одного
    //                    system("cls");
    //                    ai.deleteMedic();
    //                    system("pause");
    //                    break;
    //                }
    //                case 2: {   //Удалить отделение
    //                    system("cls");
    //                    std::string vv = menuEdit();
    //                    if (vv.length() != 0) {
    //                        auto nameDepart = ai.Hospital.find(vv); // находим ячейку
    //                        ai.Hospital.erase(nameDepart);
    //                    }
    //                    break;
    //                }
    //                case 3: {   //Удалить всех
    //                    system("cls");
    //                    ai.Hospital.clear();
    //                    break;
    //                }
    //                case 0:
    //                    return;
    //                default:
    //                    cout << "Такого действия нет. Введите другой выбор.\n";
    //                    break;
    //            }
    //        }
    //    }
    //
    //    // Поиск информации (case 5)
    //    void search_info() {
    //        while (true) {
    //            int sw = menuSearch();
    //            if (sw == 0) return;
    //            else {
    //                system("cls");
    //                medicSearchMenu(sw);
    //            }
    //        }
    //    }
    //
    //    void medicSearchMenu(size_t menuChoice) {
    //        switch (menuChoice) {
    //            case 1: {
    //                system("cls");
    //                list <Medic> result;
    //                auto getSurname = []() -> string {
    //                    std::string _n;
    //                    std::cout << "Введите фамилию мед.работника: ";
    //                    std::cin >> _n;
    //                    return _n;
    //                };
    //                std::string strFind = getSurname();
    //                result = ai.searchByName(strFind);
    //                std::cout << "Ищем мед.работника: " << strFind << "." << endl;
    //                if (result.empty()) {
    //                    std::cout << "Совпадений не найдено\n";
    //                } else {
    //                    All_info::printHead();
    //                    All_info::printList(result);
    //                }
    //                system("pause");
    //                break;
    //            }
    //            case 2: {
    //                system("cls");
    //                list <Medic> result;
    //                auto getPost = []() -> string {
    //                    std::string position;
    //                    int ch = vcChoice("должность", Posts);
    //                    if (ch != 0) {
    //                        position = Posts[ch - 1];
    //                    } else {
    //                        position = "";
    //                    }
    //                    return position;
    //                };
    //                std::string strFind = getPost();
    //                result = ai.searchByPost(strFind);
    //                std::cout << "Ищем должность: " << strFind << "." << endl;
    //                if (result.empty()) {
    //                    std::cout << "Совпадений не найдено\n";
    //                } else {
    //                    All_info::printHead();
    //                    All_info::printList(result);
    //                }
    //                system("pause");
    //                break;
    //            }
    //            case 3: {
    //                system("cls");
    //                list <Medic> result;
    //                auto getKey = []() -> string {
    //                    std::string key;
    //                    int ch = vcChoice("отделение", Departs);
    //                    if (ch != 0) {
    //                        key = Departs[ch - 1];
    //                    } else {
    //                        key = "";
    //                    }
    //                    return key;
    //                };
    //                std::string strFind = getKey();
    //                std::cout << "Ищем отделение: " << strFind << "." << endl;
    //                auto it = ai.Hospital.find(strFind);
    //                if (it != ai.Hospital.end()) {
    //                    All_info::printHead();
    //                    All_info::printList(it->second);
    //                } else {
    //                    std::cout << "Совпадений не найдено\n";
    //                }
    //                system("pause");
    //                break;
    //            }
    //            default:
    //                std::cout << "Некорректный выбор. Повторите попытку\n";
    //                system("pause");
    //                break;
    //        }
    //    }
    //
    //    // Сортировка информации (case 6)
    //    void sorting(size_t mode) {
    //        system("cls");
    //        if (ai.Hospital.empty()) {
    //            cout << "Список пуст.\n";
    //            return;
    //        }
    //        for (auto &it: ai.Hospital) {
    //            switch (mode) {
    //                case 1:
    //                    it.second.sort(compareSurname);
    //                    break;
    //                case 2:
    //                    it.second.sort(compareSalary);
    //                    break;
    //                default:
    //                    break;
    //            }
    //        }
    //        ai.printHos();
    //        system("pause");
    //    }
};

#endif //CURSCLN_MENUSRV_H
