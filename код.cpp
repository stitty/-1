#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <clocale>


using namespace std;

const int MAX_PASSWORDS = 20;

string generateStrongPassword(int length) {
    string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+<>?";
    string password = "";
    for (int i = 0; i < length; i++) {
        password += charset[rand() % charset.length()];
    }
    return password;
}

int evaluatePasswordStrength(const string& password) {
    int score = 0;
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    string specialChars = "!@#$%^&*()-_=+<>?";

    for (char ch : password) {
        if (islower(ch)) hasLower = true;
        if (isupper(ch)) hasUpper = true;
        if (isdigit(ch)) hasDigit = true;
        if (specialChars.find(ch) != string::npos) hasSpecial = true;
    }

    if (hasLower) score++;
    if (hasUpper) score++;
    if (hasDigit) score++;
    if (hasSpecial) score++;
    if (password.length() >= 12) score++;

    return score;
}

void clearSavedPasswords(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (file) {
        cout << "Все сохраненные пароли удалены." << endl;
    }
    else {
        cerr << "Ошибка при очистке файла!" << endl;
    }
}

void showMenu() { 
    cout << "               @@@@@@@@               " << endl;
    cout << "            @@@@@    @@@@@            " << endl;
    cout << "          @@@@          @@@@          " << endl;
    cout << "         @@@              @@@         " << endl;
    cout << "        @@@                @@@        " << endl;
    cout << "        @@@                @@@        " << endl;
    cout << "        @@@                @@@        " << endl;
    cout << "        @@@                @@@        " << endl;
    cout << "        @@@                @@@        " << endl;
    cout << "        @@@@@@@@@@@@@@@@@@@@@@        " << endl;
    cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@     " << endl;
    cout << "     @@@@@@@@@@@@@  @@@@@@@@@@@@@     " << endl;
    cout << "     @@@@@@@@@@@      @@@@@@@@@@@     " << endl;
    cout << "     @@@@@@@@@@@@    @@@@@@@@@@@#     " << endl;
    cout << "     @@@@@@@@@@@@    @@@@@@@@@@@@     " << endl;
    cout << "     @@@@@@@@@@@@    @@@@@@@@@@@#     " << endl;
    cout << "     @@@@@@@@@@@      @@@@@@@@@@@     " << endl;
    cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@     " << endl;
    cout << "     =@@@@@@@@@@@@@@@@@@@@@@@@@@      " << endl;
    cout << "            =@@@@@@@@@@@@+             " << endl;
    cout << endl << "===== Главное меню =====" << endl;
    cout << "1. Сгенерировать сложный пароль" << endl;
    cout << "2. Просмотреть сохраненные пароли" << endl;
    cout << "3. Оценить сложность пароля" << endl;
    cout << "4. Очистить сохраненные пароли" << endl;
    cout << "5. Выход" << endl;
    cout << "Введите номер пункта: " << endl;
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(0));

    int choice;
    string filename = "passwords.txt";
    string passwords[MAX_PASSWORDS];
    int passwordCount = 0;

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            system("cls");
            int length;
            cout << "Введите длину пароля (не менее 8 символов): " << endl;
            cin >> length;
            length = max(8, length);

            if (passwordCount < MAX_PASSWORDS) {
                passwords[passwordCount] = generateStrongPassword(length);
                cout << "Сгенерированный пароль: " << passwords[passwordCount] << endl;
                passwordCount++;
            }
            else {
                cout << "Достигнуто максимальное количество паролей." << endl;
            }

            ofstream file(filename, ios::app);
            if (file) {
                for (int i = 0; i < passwordCount; i++) file << passwords[i] << endl;
                file.close();
                cout << "Пароль сохранен в " << filename << endl;
            }
            else cerr << "Ошибка записи в файл!" << endl;
        }
        else if (choice == 2) {
            system("cls");
            ifstream file(filename);
            if (file) {
                string line;
                cout << "Сохраненные пароли:" << endl;
                while (getline(file, line)) cout << line << endl;
                file.close();
            }
            else cerr << "Ошибка открытия файла!" << endl;
        }
        else if (choice == 3) {
            system("cls");
            string password;
            cout << "Введите пароль для оценки: " << endl;
            cin >> password;
            int strength = evaluatePasswordStrength(password);
            cout << "Оценка сложности пароля (0-5): " << strength << endl;
        }
        else if (choice == 4) {
            system("cls");
            clearSavedPasswords(filename);
        }
        else if (choice == 5) {
            system("cls");
            cout << "Завершение работы..." << endl;
            break;
        }
        else {
            system("cls");
            cout << "Ошибка: неверный ввод. Попробуйте снова." << endl;
        }
    }
    return 0;
}