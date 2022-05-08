#ifndef CURSSRV_USER_H
#define CURSSRV_USER_H

#include "../Utils/stdafx.h"

using namespace std;
using namespace Checks;

vector<string> Roles = {"Администратор", "Представитель компании", "Эксперт"};

class User {
    std::string name;       // Имя
    std::string surname;    // Фамилия
    std::string login;      // Логин
    std::string pass;       // Телефон
    std::string role;       // Роль
public:
    friend ostream &operator<<(ostream &out, User &obj) {
        out << "Фамилия: " << obj.getSurname() << endl;
        out << "Имя: " << obj.getName() << endl;
        out << "Логин: " << obj.getLogin() << endl;
        out << "Пароль: " << obj.getPass() << endl;
        out << "Роль: " << obj.getRole() << endl;
        return out;
    }

    User() {};

    User(string _name, string _surname, string _login, string _pass,
         string _role) : name(std::move(_name)), surname(std::move(_surname)),
                         login(std::move(_login)),
                         pass(std::move(_pass)),
                         role(std::move(_role)) {}

    virtual ~User() = default;

    const string &getName() const {
        return name;
    }

    const string &getSurname() const {
        return surname;
    }

    const string &getLogin() const {
        return login;
    }

    string getFio() const {
        return surname + " " + name;
    }

    const string &getPass() const {
        return pass;
    }

    const string &getRole() const {
        return role;
    }

    void setName(const string &_name) {
        User::name = _name;
    }

    void setSurname(const string &_surname) {
        User::surname = _surname;
    }

    void setLogin(const string &_login) {
        User::login = _login;
    }

    void setPass(const string &_pass) {
        User::pass = _pass;
    }

    void setRole(const string &_role) {
        User::role = _role;
    }

    void setUser(string _name, string _surname, string _login, string _pass, string _role) {
        this->name = std::move(_name);
        this->surname = std::move(_surname);
        this->login = std::move(_login);
        this->pass = std::move(_pass);
        this->role = std::move(_role);
        //return *this;
    }

    void setUser(const User &rhs) {
        this->name = rhs.name;
        this->surname = rhs.surname;
        this->login = rhs.login;
        this->pass = rhs.pass;
        this->role = rhs.role;
        //return *this;
    }

    // Функция для просмотра сотрудника администратором
    void printUser(bool one = false, ostream &fout = std::cout) const {
        if (one) {
            fout << "+-------------------------------------+------------------------+--------+-------------+----------+"
                 << endl;
        }
        fout << "|" << setw(37) << left << this->getFio() << "|"
             << setw(24) << left << this->getLogin() << "|"
             << setw(13) << this->getPass() << "|"
             << setw(13) << this->getRole() << "|" << endl;
        fout << "+-------------------------------------+------------------------+--------+-------------+----------+"
             << endl;
    }

    static void enterUser(User &tmp) {
        string _name, _surname, _login, _pass, _role;
        //ФИО
        cout << "Введите ФИО сотрудника:\n";
        do {
            cout << "Фамилия: ";
            cin >> _surname;
            if (Checks::checkNoNumbers(_surname)) {
                break;
            } else
                cout << "Некорректный ввод. Повторите попытку.\n";
        } while (true);
        do {
            cout << "Имя: ";
            cin >> _name;
            if (Checks::checkNoNumbers(_name)) {
                break;
            } else
                cout << "Некорректный ввод. Повторите попытку.\n";
        } while (true);
        do {
            cout << "Отчество: ";
            cin >> _login;
            if (Checks::checkNoNumbers(_login)) {
                break;
            } else
                cout << "Некорректный ввод. Повторите попытку.\n";
        } while (true);
        //Номер телефона
        do {
            cout << "Введите номер телефона:\n";
            cin >> _pass;
            if (Checks::checkNoLetters(_pass)) {
                break;
            } else
                cout << "Некорректный ввод. Повторите попытку.\n";
        } while (true);
        //Роль
        size_t ch = vcChoice("Роль", Roles);
        if (ch > 0) _role = Roles[ch - 1];
        else return;
        tmp.setUser(_name, _surname, _login, _pass, _role);
    }

    bool operator==(const User &rhs) const {
        return name == rhs.name &&
               surname == rhs.surname &&
               login == rhs.login &&
               pass == rhs.pass &&
               role == rhs.role;
    }

    bool operator!=(const User &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const User &rhs) const {
        if (surname < rhs.surname)
            return true;
        if (name < rhs.name)
            return true;
        return (rhs.name < name);
    }

    bool operator>(const User &rhs) const {

        return rhs < *this;
    }

    bool operator<=(const User &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const User &rhs) const {
        return !(*this < rhs);
    }
};

// Сравнение по фамилии
bool compareSurname(const User &obj1, const User &obj2) {
    if (strcmp(obj1.getSurname().c_str(), obj2.getSurname().c_str()) < 0)
        return true;
    else
        return false;
}

class UserSock : public User {
private:
    //SOCKET sock;
public:
    SOCKET sock;

    UserSock(SOCKET _sock) {
        this->sock = _sock;
    }

    void enterUser() {
        //UserSock tmp;
        string _name, _surname, _login, _pass, _role;
        sendString(sock, "data");
        //ФИО
        sendString(sock, "Фамилия: ");
        do {
            _surname = takeString(sock);
            if (Checks::checkNoNumbers(_surname)) {
                break;
            } else
                sendString(sock, "Некорректный ввод. Повторите попытку.\nФамилия: ");
        } while (true);
        sendString(sock, "Имя: ");
        do {
            _name = takeString(sock);
            if (Checks::checkNoNumbers(_name)) {
                break;
            } else
                sendString(sock, "Некорректный ввод. Повторите попытку.\nИмя: ");
        } while (true);
        sendString(sock, "Логин: ");
        do {
            _login = takeString(sock);
            if (Checks::checkNoNumbers(_login)) {
                break;
            } else
                sendString(sock, "Некорректный ввод. Повторите попытку.\nЛогин: ");
        } while (true);
        //Пароль
        sendString(sock, "Пароль: ");
        do {
            _pass = takeString(sock);
            if (Checks::checkNoLetters(_pass)) {
                break;
            } else
                sendString(sock, "Некорректный ввод. Повторите попытку.\nПароль: ");
        } while (true);
        //Роль
        //size_t ch = vcChoice("Роль", Roles);
        size_t ch;
        sendString(sock, "end");
        sendString(sock, "menu");
        sendString(sock, toString(Roles));
        ch = takeInt(sock);
        if (ch > 0) _role = Roles[ch - 1];
        else return;
        //sendString(sock, "end");
        setUser(_name, _surname, _login, _pass, _role);
        //tmp.setUser(_name, _surname, _login, _pass, _role);
    }
};

#endif //CURSSRV_USER_H
