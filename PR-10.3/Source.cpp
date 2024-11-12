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
    cout << "������ ������� ��� : "; cin >> N;
    char filename[100];
    Note* p = new Note[N];
    int nomer;
    string prizv;
    int found;
    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� �����" << endl;
        cout << " [4] - ������� ����� ����� �� ������� ��������" << endl;
        cout << " [5] - ����� ����� � ����" << endl;
        cout << " [6] - ���������� ����� �� �����" << endl << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
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
            cout << "������ ����� ������:" << endl;
            cout << " ����� ��������: "; cin >> nomer;
            cin.get(); // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
            cout << endl;
            if ((found = BinSearch(p, N, nomer)) != -1) {
                cout << "�������� ����� � ������� " << p[found].nomer << endl;
                cout << "������� �� ��'�:" << endl;
                cout << p[found].prizvim << " ���� ����������: ";
                cout << p[found].day << "." << p[found].month << "." << p[found].year << endl;
            }
            else
                cout << "������ ����� �� ��������" << endl;
            break;
        case 5:
            cin.get(); // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

            cout << "������ ��'� �����: "; cin.getline(filename, 99);
            SaveToFile(p, N, filename);
            break;
        case 6:
            cin.get(); // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

            cout << "������ ��'� �����: "; cin.getline(filename, 99);
            LoadFromFile(p, N, filename);
            break;

        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Note* p, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "����� � " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " ������� �� ��'�: "; getline(cin, p[i].prizvim);
        cout << " ����� ��������: "; cin >> p[i].nomer;
        cout << " ������ ���� ���������� :" << endl;
        cout << " ����: "; cin >> p[i].day;
        cout << " ̳����: "; cin >> p[i].month;
        cout << " г�: "; cin >> p[i].year;
    }
}

void Print(Note* p, const int N) {
    cout << "==================================================================================" << endl;
    cout << "| �   | ������� �� ��'�    |  ����� �������� | ����   | ̳����  | г� ����������|" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(20) << left << p[i].prizvim // ������� �� ��'�
            << "| " << setw(15) << right << p[i].nomer << " " // ����� ��������
            << "| " << setw(6) << right << p[i].day << " "    // ����
            << "| " << setw(7) << right << p[i].month << " "  // ̳����
            << "| " << setw(12) << right << p[i].year << " " << endl; // г�
    }
    cout << "==================================================================================" << endl;
}

int BinSearch(Note* p, const int N, unsigned kurs) {
    // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
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
    ofstream fout(filename, ios::binary); // ������� ������� ���� ������
    fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Note)); // �������� �������� ������
    fout.close(); // ������� ����
}

void LoadFromFile(Note*& p, int& N, const char* filename)
{
    delete[] p; // ������� �������� ���
    ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
    fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
    p = new Note[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        fin.read((char*)&p[i], sizeof(Note)); // ��������� �������� ������
    fin.close(); // ������� ����
}