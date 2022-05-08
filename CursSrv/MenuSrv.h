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
    //static vector<std::string> vcMainMenu = {"�����", "�����������", "�����"};
    //All_info ai;
    std::string strMenuMain = "-=-=-=-=  � � � �  =-=-=-=-#�����#�����������#������#�����";
    std::string strMenuAdmin = "\t�������������#�������� �������������� ��������#����������#��������#���������� ���������� � ��#�����#���������� �������������� ��������#����������� �������������� �������#������� ��������� ������������ ��#�������������#�����";
    std::string strMenuAdminAdd = "�� ������ ��������: #����� ��������#����� ���������#����� �������#�����";
    std::string strMenuAdminDel = "�� ������ �������: #��������#���������#�������#�����";
    std::string strMenuAdminSave = "�� ������ ��������� ���������� �:#��������#���������#��������#�����";
    std::string strMenuAdminRanking = "����������� �������������� �������:#����������� �������� ��������� ��������#����� ������#��������� ���� ��������#��������� ������� ������������#�����";
    std::string strMenuAdminEdit = "�� ������ ������������� ������:#��������#���������#��������#�����";
    std::string strMenuCompany = "\t��������#���� ������#������������� ������#�������� ������#���������� ���������� � ��#�������� ������ � �������#�����";
    std::string strMenuCompanyEdit = "�� ������ ������������� ������:#��������#��������#�����";
    std::string strMenuCompanySave = "�� ������ ��������� ���������� �:#��������#��������#�����";
    std::string strMenuExpert = "\t�������#����������� ������#������������� ������ � ����#����������� ���������� �� �������������� ��������#�����";

    // �����������
    A_menu() {
        sock = NULL;
    };

    explicit A_menu(SOCKET connection) {
        sock = connection;
    }

    // ����������
    ~A_menu() = default;

    static int changeMenu(const std::string &str, int cntMenu, const std::string &begMenu, int back) {
        int choice = -1;
        std::string endMenu = "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        cout << endl << begMenu << endl;
        cout << str << endl;
        if (back == 0) cout << " 0 - �����" << endl;
        else cout << " 0 - �����" << endl;
        cout << endMenu.substr(0, begMenu.size()) << endl;
        cout << "��������: ";
        do {
            Checks::CheckInput(choice);
            if ((choice > cntMenu) || (choice < 0)) {
                cout << "������ �������� ��� � ����, ���������� �����" << endl;
            }
        } while ((choice < 0) || (choice > cntMenu));
        std::cin.clear();
        return choice;
    }

    static size_t choiceMenu(size_t cntMenu, const std::string &strMenu) {
        cout << " 0 - --= ������ =-- " << endl;
        cout << "�������� " << strMenu << ": ";
        size_t ch = -1;
        do {
            std::cin >> ch;
            fflush(stdin);
        } while ((ch < 0) || (ch > cntMenu));
        return ch;
    }

    static bool Confirm(const std::string &msg) {
        //        int ls;
        //        cout << msg << " (Y/�/[N/�]): ";
        //        do {
        //            ls = cin.get();
        //        } while (((ls != 'Y') && (ls != 'y') && (ls != 'N') && (ls != 'n') && (ls != '�') && (ls != '�') &&
        //                  (ls != '�') && (ls != '')) || (ls == 13));
        //        if ((ls == 'Y') || (ls == 'y') || (ls == '�') || (ls == '�')) return true;
        //        else if ((ls == 'N') || (ls == 'n') || (ls == '�') || (ls == '�') || (ls == 13)) return false;
        //        else return false;
        return true;
    }

    static int menuMain() {
        std::string strMenu = " 1 - �����\n 2 - �����������";
        return changeMenu(strMenu, 6, "-=-=-=-=  � � � �  =-=-=-=-", 0);
        //        return vcChoice("-=-=-=-=  � � � �  =-=-=-=-", vcMainMenu, 0)
    }

    void menuAdmin() {
        sendString(sock, "menu");
        sendString(sock, strMenuAdmin);
        //sendMenu(sock, split(strMenuAdmin));
        char p[200];
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (int c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
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
        char p[200], com[200];//�������� ����� � �������
        char curU[20];
        curU[0] = '\0';
        com[0] = '\0';
        p[0] = '\0';
        std::cout << "���������� �����������." << std::endl;
        char *message = new char[100];
        strcat(p, "Server connected...\n");
        //send((SOCKET)newS, p, sizeof(p), 0);//�������� ����������� ��� ����������
        std::string strMenu = "-=-=-=-=  � � � �  =-=-=-=-#�����#�����������#������#�����";
        sendString(sock, "Server connected...\n");
        sendString(sock, "menu");
        sendString(sock, strMenu);
        strcpy(p, "");
        p[0] = '\0';
        std::string command;
        while (c = recv(sock, p, sizeof(p), 0) != 0) { //���� ����������� �������
            command = p;
            //std::cout << "<- " << com << std::endl;
            int i = atoi(command.c_str());
            if (command == "1") {//����������� ������������
//                tUser user{};
//                sendString(sock, "data");
//                sendString(sock, "������� �����: ");
//                user.login = takeString(sock);
//                // ���� ������������ � ����
//                // ���� �������
//                sendString(sock, "������� ������: ");
//                user.pass = takeString(sock);
//                sendString(sock, "end");
//                std::cout << "login: " << user.login << " - " << user.pass << endl;
                //if user = Admin
                //menuAdmin();
                menuCompany();
            }
            if (command == "2") {//����������� ������������
//                tUser user{};
//                sendString(sock, "data");
//                sendString(sock, "������� �����: ");
//                user.login = takeString(sock);
//                // ���� ������������ � ����
//                // ���� �������
//                sendString(sock, "������� ������: ");
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
            if (command == "3") {//���������� ������������
                //cout << "User " << curU << " logout" << endl;
                sendString(sock, "exit");
                closesocket(sock);//��������� �����
                return;
            }
            if (command == "4") {//�����
                sendString(sock, "exit");
                closesocket(sock);//��������� �����
                exit(EXIT_SUCCESS);
            }
        }
    }

    //    // �������� ���������� (case 1)
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
    //                    std::cout << "������� ��������� ������ � ����... ��������!" << endl;
    //                    ofstream fout;
    //                    fout.exceptions(ofstream::badbit);
    //                    try {
    //                        fout.open("lab5.txt");
    //                        //else fout.open("lab5.txt", ios::app | ios_base::in);
    //                        ai.printHos(fout);
    //                        cout << "������ ��������� �������!" << endl;
    //                    }
    //                    catch (const ofstream::failure &e) {
    //                        cout << "������ �������� ����� (lab5.txt)!" << endl;
    //                    }
    //                    fout.close();
    //                    system("pause");
    //                    break;
    //                }
    //                case 0:
    //                    return;
    //                default:
    //                    cout << "������ �������� ���. ������� ������ �����.\n";
    //                    break;
    //            }
    //        }
    //    }
    //
    //    // ���������� ���������� (case 2)
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
    //    // �������������� ���������� (case 3)
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
    //    // �������� ���������� (case 4)
    //    void delete_info() {
    //        int v;
    //        while (true) {
    //            system("cls");
    //            v = menuDelete();
    //            switch (v) {
    //                case 1: {  //������� ������
    //                    system("cls");
    //                    ai.deleteMedic();
    //                    system("pause");
    //                    break;
    //                }
    //                case 2: {   //������� ���������
    //                    system("cls");
    //                    std::string vv = menuEdit();
    //                    if (vv.length() != 0) {
    //                        auto nameDepart = ai.Hospital.find(vv); // ������� ������
    //                        ai.Hospital.erase(nameDepart);
    //                    }
    //                    break;
    //                }
    //                case 3: {   //������� ����
    //                    system("cls");
    //                    ai.Hospital.clear();
    //                    break;
    //                }
    //                case 0:
    //                    return;
    //                default:
    //                    cout << "������ �������� ���. ������� ������ �����.\n";
    //                    break;
    //            }
    //        }
    //    }
    //
    //    // ����� ���������� (case 5)
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
    //                    std::cout << "������� ������� ���.���������: ";
    //                    std::cin >> _n;
    //                    return _n;
    //                };
    //                std::string strFind = getSurname();
    //                result = ai.searchByName(strFind);
    //                std::cout << "���� ���.���������: " << strFind << "." << endl;
    //                if (result.empty()) {
    //                    std::cout << "���������� �� �������\n";
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
    //                    int ch = vcChoice("���������", Posts);
    //                    if (ch != 0) {
    //                        position = Posts[ch - 1];
    //                    } else {
    //                        position = "";
    //                    }
    //                    return position;
    //                };
    //                std::string strFind = getPost();
    //                result = ai.searchByPost(strFind);
    //                std::cout << "���� ���������: " << strFind << "." << endl;
    //                if (result.empty()) {
    //                    std::cout << "���������� �� �������\n";
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
    //                    int ch = vcChoice("���������", Departs);
    //                    if (ch != 0) {
    //                        key = Departs[ch - 1];
    //                    } else {
    //                        key = "";
    //                    }
    //                    return key;
    //                };
    //                std::string strFind = getKey();
    //                std::cout << "���� ���������: " << strFind << "." << endl;
    //                auto it = ai.Hospital.find(strFind);
    //                if (it != ai.Hospital.end()) {
    //                    All_info::printHead();
    //                    All_info::printList(it->second);
    //                } else {
    //                    std::cout << "���������� �� �������\n";
    //                }
    //                system("pause");
    //                break;
    //            }
    //            default:
    //                std::cout << "������������ �����. ��������� �������\n";
    //                system("pause");
    //                break;
    //        }
    //    }
    //
    //    // ���������� ���������� (case 6)
    //    void sorting(size_t mode) {
    //        system("cls");
    //        if (ai.Hospital.empty()) {
    //            cout << "������ ����.\n";
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
