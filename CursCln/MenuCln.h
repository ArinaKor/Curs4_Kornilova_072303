#ifndef CURSCLN_MENUCLN_H
#define CURSCLN_MENUCLN_H

#include "..\Utils\stdafx.h"

using namespace std;

int vcChoiceOld(std::vector<std::string> vc, const std::string& strMenu = "", bool back = false) {
	std::cout << "Выберите " + strMenu + ": " << std::endl;
	for (size_t i = 0; i < vc.size(); ++i) {
		std::cout << std::setw(2) << i + 1 << ". " << vc[i] << std::endl;
	}
	if (back) std::cout << "0. -= ОТМЕНА =- " << std::endl;
	int ch = -1;
	do {
		std::cin >> ch;
		fflush(stdin);
	} while ((ch < 0) || (ch > vc.size()));
	return ch;
}
int vcChoice(std::vector<std::string> vc) {
	std::cout << vc[0] << std::endl;
	for (size_t i = 1; i < vc.size(); ++i) {
		std::cout << std::setw(2) << i << ". " << vc[i] << std::endl;
	}
	std::cout << "Выберите: ";
	int ch = -1;
	do {
		std::cin >> ch;
		fflush(stdin);
	} while ((ch < 1) || (ch > vc.size() - 1));
	return ch;
}

class A_menu {
private:
	SOCKET cn;
public:
	std::vector<std::string> vcMenu;
	//All_info ai;

	// Конструктор
	A_menu() {
		cn = NULL;
	};

	A_menu(SOCKET connection) {
		cn = connection;
	}

	// Деструктор
	~A_menu() = default;

	static int changeMenu(const std::string& str, int cntMenu, const std::string& begMenu, int back) {
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

	static size_t choiceMenu(size_t cntMenu, const std::string& strMenu) {
		cout << " 0 - --= ОТМЕНА =-- " << endl;
		cout << "Выберите " << strMenu << ": ";
		size_t ch = -1;
		do {
			std::cin >> ch;
			fflush(stdin);
		} while ((ch < 0) || (ch > cntMenu));
		return ch;
	}

	static bool Confirm(const std::string& msg) {
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
	//
	//    static int menuView() {
	//        std::string strMenu = " 1 - Вывод на экран\n 2 - Сохранение в файл";
	//        return changeMenu(strMenu, 2, "-=-=-=-= Просмотр работников =-=-=-=-", 1);
	//    }
	//
	//    static int menuAdd() {
	//        return vcChoice("отделение", Departs);
	//    }
	//
	//    std::string menuEdit() const {
	//        return All_info::mpChoice("отделение", ai.Hospital);
	//    }
	//
	//    static int menuDelete() {
	//        std::string strMenu = " 1 - Мед.работника\n 2 - Отделение\n 3 - Всех подряд";
	//        return changeMenu(strMenu, 3, "-=-=-=-= Удаление работников =-=-=-=-", 1);
	//    }
	//
	//    static int menuSearch() {
	//        std::string strMenu = " 1 - Фамилии\n 2 - Должности\n 3 - Отделению";
	//        return changeMenu(strMenu, 3, "-=-=-=-= Поиск работников =-=-=-=-", 1);
	//    }
	//
	//    static int menuSort() {
	//        std::string strMenu = " 1 - Фамилии\n 2 - Зарплате";
	//        return changeMenu(strMenu, 2, "-=-=-=-= Сортировка работников =-=-=-=-", 1);
	//    }

	void start() {
		int v;
		std::string str;
		while (true) {
			//system("cls");
			//v = menuMain();
			str = takeString(cn);
			if (str == "menu") {
				if (!vcMenu.empty()) {
					vcMenu.clear();
				}
				vcMenu = takeMenu(cn);
				sendInt(cn, vcChoice(vcMenu));
			}
			if (str == "data") {
				// получение и отправка данных
				str = takeString(cn);
				while (str != "end") {
					std::cout << str;
					std::cin >> str;
					sendString(cn, str);
					str = takeString(cn);
				}
			}
			if (str == "exit") {
				return;
			}
			//switch (v) {
			//case 1: {
			//	sendString(cn, "login");
			//	std::cout << takeString(cn);
			//	std::cin >> str;
			//	sendString(cn, str);
			//	std::cout << takeString(cn);
			//	std::cin >> str;
			//	sendString(cn, str);
			//	//system("cls");
			//	//                    view_info();
			//	break;
			//}
			//
			//case 0:
			//	sendString(cn, "quit");
			//	return;
			//default:
			//	std::cout << "Выберите другой пункт меню.\n";
			//	break;
			//}
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

#endif //CURSCLN_MENUCLN_H
