#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <windows.h>

using namespace std;

// Линейный поиск
// Поиск с барьером
// Бинарный поиск

struct Student
{
    int num_book;
    int num_group;
    string name;
};

void inputKeyboard(vector <Student> &arr)
{
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    cout << "Введите данные студентов: номер зачетной книжки, номер группы, ФИО" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Данные " << i + 1 << " студента";
        Student per;
        cout << "\nНомер зачетной книжки: ";
        cin >> per.num_book;
        cout << "Номер группы: ";
        cin >> per.num_group;
        cin.clear();
        cin.ignore();
        cout << "ФИО: ";
        getline(cin, per.name);
        arr.push_back(per);
    }
}

void inputFile(vector <Student>& arr)
{
    ifstream file;
    file.open("students.txt");
    if (!file.is_open())
    {
        cout << "Ошибка открытия файла!";
        exit(0);
    }
    else
    {
        while (!file.eof())
        {
            Student per;
            file >> per.num_book >> per.num_group;
            string temp;
            getline(file, temp);
            per.name = temp.substr(1);
            arr.push_back(per);
        }
    }
    file.close();
}

void output(vector <Student> arr)
{
    cout << "Таблица данных о студентах" << endl;
    cout << "Номер зачетной книжки" << "     Номер группы" << "     ФИО" << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        if (i == arr.size() - 1) cout << left << setw(26) << arr[i].num_book << setw(17) << arr[i].num_group << arr[i].name;
        else cout << left << setw(26) << arr[i].num_book << setw(17) << arr[i].num_group << arr[i].name << endl;
    }
}

void linearSearch(vector <Student> arr, int num)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i].num_book == num)
        {
            cout << "Данные студента с " << arr[i].num_book << " номером зачетной книжки:" << endl;
            cout << "Номер группы: " << arr[i].num_group << "\nФИО: " << arr[i].name;
            return;
        }
    }
    cout << "Студента с введенным номером зачетной книжки нет в таблице данных!";
}

void barrierSearch(vector <Student> arr, int num)
{
    Student last;
    last.num_book = arr[arr.size() - 1].num_book;
    arr[arr.size() - 1].num_book = num;
    int i = 0;
    for (i; arr[i].num_book!=num; i++){}
    arr[arr.size() - 1].num_book = last.num_book;
    if (i != arr.size() - 1 || num == last.num_book)
    {
        cout << "Данные студента с " << arr[i].num_book << " номером зачетной книжки:" << endl;
        cout << "Номер группы: " << arr[i].num_group << "\nФИО: " << arr[i].name;
        return;
    }
    cout << "Студента с введенным номером зачетной книжки нет в таблице данных!";
}

bool operator<(const Student& a, const Student& b)
{
    return a.num_book < b.num_book;
}

void binarySearch(vector <Student> arr, int num)
{
    sort(arr.begin(), arr.end());
    int i = 0, j = arr.size() - 1;
    Student left = arr[i];
    Student mid = arr[(i + j) / 2];
    Student right = arr[j];
    if (right.num_book < num || left.num_book > num)
    {
        cout << "Студента с введенным номером зачетной книжки нет в таблице данных!";
        return;
    }
    while (mid.num_book != num || mid.num_book != right.num_book || mid.num_book != left.num_book)
    {
        if (left.num_book == num)
        {
            cout << "Данные студента с " << left.num_book << " номером зачетной книжки:" << endl;
            cout << "Номер группы: " << left.num_group << "\nФИО: " << left.name;
            return;
        }
        else if (right.num_book == num)
        {
            cout << "Данные студента с " << right.num_book << " номером зачетной книжки:" << endl;
            cout << "Номер группы: " << right.num_group << "\nФИО: " << right.name;
            return;
        }

        if (num > mid.num_book)
        {
            i = (i + j) / 2 + 1;
            left = arr[i];
        }
        else
        {
            j = (i + j) / 2 - 1;
            right = arr[j];
        }
        mid = arr[(i + j) / 2];
    }
    if (mid.num_book == num)
    {
        cout << "Данные студента с " << mid.num_book << " номером зачетной книжки:" << endl;
        cout << "Номер группы: " << mid.num_group << "\nФИО: " << mid.name;
    }
    else cout << "Студента с введенным номером зачетной книжки нет в таблице данных!";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");
    vector <Student> arr;
    inputFile(arr);
    output(arr);
    string answer;
    cout << "\nВы хотите получить данные какого то студента? Если да - введите +, иначе введите -" << endl;
    cin >> answer;
    while (answer != "-" && answer != "+")
    {
        cout << "Вы ввели не то, что требовалось, попробуйте снова!" << endl;
        cout << "Вы хотите получить данные какого то студента? Если да - введите +, иначе введите -" << endl;
        cin >> answer;
    }
    while (answer != "-")
    {
        int num;
        cout << "Введите номер зачетной книжки того студента, данные которого вы хотите узнать: ";
        cin >> num;
        binarySearch(arr, num);
        cout << "\nВы хотите получить данные какого то студента? Если да - введите +, иначе введите -" << endl;
        cin >> answer;
        while (answer != "-" && answer != "+")
        {
            cout << "Вы ввели не то, что требовалось, попробуйте снова!" << endl;
            cout << "Вы хотите получить данные какого то студента? Если да - введите +, иначе введите -" << endl;
            cin >> answer;
        }
    }
    return 0;
}