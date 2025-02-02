# 📜 Вики по программе генерации паролей

## 1. Подключение заголовочных файлов
```cpp
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <clocale>
```
### Что делают эти библиотеки?
- **`#include <iostream>`** — используется для работы с вводом (`cin`) и выводом (`cout`) в консоли.
- **`#include <fstream>`** — позволяет работать с файлами (сохранение и чтение паролей).
- **`#include <ctime>`** — предоставляет функции работы со временем (`time(0)`) для генерации случайных чисел.
- **`#include <cstdlib>`** — содержит функции `rand()` и `srand()` для генерации случайных чисел.
- **`#include <string>`** — необходима для работы с `string`, удобным типом данных для работы с текстом.
- **`#include <vector>`** — позволяет использовать динамические массивы (`vector`).
- **`#include <clocale>`** — устанавливает локаль, чтобы корректно отображать русский текст в консоли.

---

## 2. Глобальные переменные и константы
```cpp
const int MAX_PASSWORDS = 20;
```
- **`MAX_PASSWORDS`** — ограничение на количество паролей, которые можно сохранить.

---

## 3. Функция генерации сложного пароля
```cpp
string generateStrongPassword(int length) {
    string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+<>?";
    string password = "";
    for (int i = 0; i < length; i++) {
        password += charset[rand() % charset.length()];
    }
    return password;
}
```
### Как это работает?
1. `charset` содержит все возможные символы для пароля.
2. Цикл выбирает случайные символы из `charset` и добавляет их в `password`.
3. Итоговый пароль возвращается.

---

## 4. Функция оценки сложности пароля
```cpp
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
```
### Как это работает?
1. Проверяет, есть ли в пароле:
   - Прописные буквы
   - Заглавные буквы
   - Цифры
   - Специальные символы
2. Начисляет баллы за каждое из этих условий.
3. Дополнительный балл за длину пароля ≥ 12 символов.

---

## 5. Функция очистки сохраненных паролей
```cpp
void clearSavedPasswords(const string& filename) {
    ofstream file(filename, ios::trunc);
    if (file) {
        cout << "Все сохраненные пароли удалены." << endl;
    }
    else {
        cerr << "Ошибка при очистке файла!" << endl;
    }
}
```
### Как это работает?
- `ios::trunc` очищает файл перед записью, удаляя все прошлые пароли.

---

## 6. Основной цикл программы
```cpp
while (true) {
    showMenu();
    cin >> choice;
    
    if (choice == 1) {
        // Генерация пароля
    } else if (choice == 2) {
        // Просмотр паролей
    } else if (choice == 3) {
        // Оценка сложности
    } else if (choice == 4) {
        // Очистка списка
    } else if (choice == 5) {
        break; // Выход
    } else {
        cout << "Ошибка: неверный ввод. Попробуйте снова." << endl;
    }
}
```
### Как это работает?
- `while (true)` создаёт бесконечный цикл, пока не выбрано `5` (выход).
- `cin >> choice;` получает ввод пользователя.
- `if-else` проверяет введённую команду и выполняет соответствующую операцию.

---

## 7. Выход из программы
```cpp
else if (choice == 5) {
    system("cls");
    cout << "Завершение работы..." << endl;
    break;
}
```
- Очищает консоль (`system("cls")` для Windows).
- Выводит сообщение перед завершением.

