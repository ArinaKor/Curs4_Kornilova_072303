#include "Server.h"
#include <iostream>
#include <process.h> /* _beginthread, _endthread */
#include <Windows.h>
#include <fstream>
#include "MenuSrv.h"


// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma warning (disable: 4996)

using namespace std;

int registerUser(char* user, char* password) {
	try {
		fstream f("password", ios::out | ios::app);//открываем файл для записи в конец файла
		if (!f.is_open()) return 0;
		f << user << " " << password << endl;
		f.close();
		return 1;
	}
	catch (...) {//если исключение:
		cerr << "Cannot open password file. Try again\n" << endl;
		return 0;
	}
}

int loginUser(char* user, char* password) {
	char* log = new char[20];
	char* oldPass = new char[20];
	try {
		ifstream f("password", ios::in);//открываем файл для чтения
		if (!f.is_open()) return 0;
		char* str = new char[255];
		int i = 0, j = 0, n = 0;
		while (!f.eof()) {
			f.getline(str, 255, '\n');//читаем
			for (int i = 0; str[i] != ' '; i++) {//откуда:
				log[j] = str[i];
				j++;
			}
			log[j] = '\0';
			if (!strcmp(user, log)) {
				for (int i = j + 1; ((str[i] != ' ') && (str[i] != '\0')); i++) {//откуда:
					oldPass[n] = str[i];
					n++;
				}
				oldPass[n] = '\0';
				if (!strcmp(password, oldPass)) {
					f.close();
					return 2;
				}
				else {
					f.close();
					return 1;
				}
			}
			log[0] = '\0';
			j = 0;
			cout << str << endl;
		}
		f.close();
	}
	catch (...) {//если исключение:
		cerr << "Cannot open password file. Try again\n" << endl;
		return 0;
	}
	return 0;
}

void login_menu() {}

void register_menu() {}

void Work(void* newS) {//поток обслуживания
	A_menu menu((SOCKET)newS);
	menu.start();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);//первая цифра версии находится в младшем байте, вторая - в старшем.
	int err = WSAStartup(wVersionRequested, &wsaData);//инициализируем работу с WinSock dll
	if (err != 0) return err;

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);//создаем TCP-сокет с интернет-адресацией
	struct sockaddr_in local;//адресная структура
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);//порт соединения
	local.sin_addr.s_addr = htonl(INADDR_ANY);//посылать или принимать данные через любой IP-адрес данного компьютера
	bind(s, (struct sockaddr*)&local, sizeof(local));//связываем адрес с сокетом
	listen(s, 5);//установка в прослушивание с 5-ти кратными попытками соединения
	while (true) {//цикл извлечения запросов на подключение из очереди
		sockaddr_in remote;//адрес клиента(заполняется системой)
		int j = sizeof(remote);//адрес клиента(заполняется системой)
		SOCKET newS = accept(s, (struct sockaddr*)&remote, &j);//подключение
		std::cout << remoteIP(remote) << std::endl;
		_beginthread(Work, 0, (void*)newS);//запускаем поток для обслуживания клиента
	}
	WSACleanup();
	return 0;
};
