#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

class Spravocnik {
private:
    string firma;
    string owner;
    string phone;
    string address;
    string work;

public:
    Spravocnik(const string& name, const string& owner, const string& phone,
        const string& address, const string& work) : firma(name), owner(owner),
        phone(phone), address(address), work(work)
    {}

    void showInfo() const
    {
        cout << "Название: " << firma << "\n";
        cout << "Владелец: " << owner << "\n";
        cout << "Телефон: " << phone << "\n";
        cout << "Адрес: " << address << "\n";
        cout << "Род деятельности: " << work << "\n";
        cout << "-------------------------\n";
    }

    void Save(ofstream& файл) const
    {
        файл << firma << ";" << owner << ";" << phone << ";" << address << ";" << work << "\n";
    }

    string getName() const { return firma; }
    string getOwner() const { return owner; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }
    string getWork() const { return work; }
};

void search(const vector<shared_ptr<Spravocnik>>& spravocnik, const string& str, int value) {
    for (const auto& firm : spravocnik)
    {
        string val;
        switch (value)
        {
        case 1:
            val = firm->getName();
            break;
        case 2:
            val = firm->getOwner();
            break;
        case 3:
            val = firm->getPhone();
            break;
        case 4:
            val = firm->getWork();
            break;
        default:
            break;
        }

        if (val.find(str) != string::npos)
        {
            firm->showInfo();
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    vector<shared_ptr<Spravocnik>> spr;

    ifstream file("справочник.txt");
    if (file.is_open())
    {
        string str;
        while (getline(file, str))
        {
            string name, owner, phone, address, work;
            size_t pos = 0;
            for (int i = 0; i < 4; ++i)
            {
                pos = str.find(';', pos);
                if (pos == string::npos)
                {
                    break;
                }

                switch (i)
                {
                case 0:
                    name = str.substr(0, pos);
                    break;
                case 1:
                    owner = str.substr(pos + 1, str.find(';', pos + 1) - pos - 1);
                    break;
                case 2:
                    phone = str.substr(pos + 1, str.find(';', pos + 1) - pos - 1);
                    break;
                case 3:
                    address = str.substr(pos + 1, str.find(';', pos + 1) - pos - 1);
                    work = str.substr(str.find(';', pos + 1) + 1);
                    break;
                default:
                    break;
                }
                pos++;
            }
            spr.push_back(make_shared<Spravocnik>(name, owner, phone, address, work));
        }
        file.close();
    }

    int value;
    do {
        cout << "Выберите действие:\n";
        cout << "1. Поиск по названию\n";
        cout << "2. Поиск по владельцу\n";
        cout << "3. Поиск по номеру телефона\n";
        cout << "4. Поиск по роду деятельности\n";
        cout << "5. Показать все записи\n";
        cout << "6. Добавить новую запись\n";
        cout << "0. Выйти\n";
        cin >> value;

        switch (value)
        {
        case 1:
        {
            string sFirm;
            cout << "Введите название фирмы для поиска: ";
            cin.ignore();
            getline(cin, sFirm);
            search(spr, sFirm, 1);
            break;
        }
        case 2:
        {
            string owner;
            cout << "Введите владельца для поиска: ";
            cin.ignore();
            getline(cin, owner);
            search(spr, owner, 2);
            break;
        }
        case 3:
        {
            string phone;
            cout << "Введите номер телефона для поиска: ";
            cin.ignore();
            getline(cin, phone);
            search(spr, phone, 3);
            break;
        }
        case 4:
        {
            string work;
            cout << "Введите род деятельности для поиска: ";
            cin.ignore();
            getline(cin, work);
            search(spr, work, 4);
            break;
        }
        case 5:
            for (const auto& firm : spr)
            {
                firm->showInfo();
            }
            break;
        case 6: {
            string name, owner, phone, address, work;
            cout << "Введите данные для новой записи:\n";
            cout << "Название: ";
            cin.ignore();
            getline(cin, name);
            cout << "Владелец: ";
            getline(cin, owner);
            cout << "Телефон: ";
            getline(cin, phone);
            cout << "Адрес: ";
            getline(cin, address);
            cout << "Род деятельности: ";
            getline(cin, work);

            spr.push_back(make_shared<Spravocnik>(name, owner, phone, address, work));

            ofstream Fin("справочник.txt", ios::app);
            if (Fin.is_open()) {
                spr.back()->Save(Fin);
                Fin.close();
                cout << "Запись успешно добавлена!\n";
            }
            else {
                cerr << "Ошибка открытия файла для дозаписи!\n";
            }
            break;
        }
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    } while (value != 0);
}
