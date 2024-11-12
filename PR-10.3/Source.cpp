#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

struct Note {
    string prizvim;
    unsigned nomer;
    struct {
        int day;
        int month;
        int year;
    };
};

void Create(Note* p, const int N);
void Print(Note* p, const int N);
int BinSearch(Note* p, const int N, unsigned kurs);
void SaveToFile(Note* p, const int N, const char* filename);
void LoadFromFile(Note*& p, int& N, const char* filename);
void Sort(Note* p, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int k = 0;
    int N;
    cout << "Введіть кількість осіб : "; cin >> N;
    char filename[100];
    Note* p = new Note[N];
    int nomer;
    string prizv;
    int found;
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - бінарний пошук особи за номером телефону" << endl;
        cout << " [5] - запис даних у файл" << endl;
        cout << " [6] - зчитування даних із файлу" << endl << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
        cout << endl << endl << endl;
        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            break;
        case 4:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " Номер телефону: "; cin >> nomer;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            cout << endl;
            if ((found = BinSearch(p, N, nomer)) != -1) {
                cout << "Знайдено особу з номером " << p[found].nomer << endl;
                cout << "Прізвище та ім'я:" << endl;
                cout << p[found].prizvim << " Дата народження: ";
                cout << p[found].day << "." << p[found].month << "." << p[found].year << endl;
            }
            else
                cout << "Шукану особу не знайдено" << endl;
            break;
        case 5:
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

            cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
            SaveToFile(p, N, filename);
            break;
        case 6:
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

            cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
            LoadFromFile(p, N, filename);
            break;

        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Note* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Особа № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " Прізвище та Ім'я: "; getline(cin, p[i].prizvim);
        cout << " Номер телефону: "; cin >> p[i].nomer;
        cout << " Введіть дату народження :" << endl;
        cout << " День: "; cin >> p[i].day;
        cout << " Місяць: "; cin >> p[i].month;
        cout << " Рік: "; cin >> p[i].year;
    }
}

void Print(Note* p, const int N) {
    cout << "==================================================================================" << endl;
    cout << "| №   | Прізвище та ім'я    |  Номер телефону | День   | Місяць  | Рік народження|" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(20) << left << p[i].prizvim // Прізвище та ім'я
            << "| " << setw(15) << right << p[i].nomer << " " // Номер телефону
            << "| " << setw(6) << right << p[i].day << " "    // День
            << "| " << setw(7) << right << p[i].month << " "  // Місяць
            << "| " << setw(12) << right << p[i].year << " " << endl; // Рік
    }
    cout << "==================================================================================" << endl;
}

int BinSearch(Note* p, const int N, unsigned kurs) {
    // Повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m =  (L +R)/ 2;  
        if (p[m].nomer == kurs)
            return m;
        if (p[m].nomer > kurs) {
            R = m - 1; 
        }
        else {
            L = m + 1;  
        }
    }
    return -1;  
}

void Sort(Note* p, const int N) {
    Note tmp;
    for (int i0 = 0; i0 < N - 1; i0++) 
    for (int i1 = 0; i1 < N - i0 - 1; i1++) 
        {
            if ((p[i1].year < p[i1 + 1].year) ||
                (p[i1].year == p[i1 + 1].year && p[i1].month < p[i1 + 1].month) ||
                (p[i1].year == p[i1 + 1].year && p[i1].month == p[i1 + 1].month && p[i1].day < p[i1 + 1].day))
            {
                tmp = p[i1 + 1];
                p[i1 + 1] = p[i1];
                p[i1] = tmp;
            }
        }
}

void SaveToFile(Note* p, const int N, const char* filename) {
    ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
    fout.write((char*)&N, sizeof(N)); // записали кількість елементів
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Note)); // записали елементи масиву
    fout.close(); // закрили файл
}

void LoadFromFile(Note*& p, int& N, const char* filename)
{
    delete[] p; // знищили попередні дані
    ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
    fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
    p = new Note[N]; // створили динамічний масив
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Note)); // прочитали елементи масиву
    fin.close(); // закрили файл
}