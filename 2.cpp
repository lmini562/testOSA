#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const string PATH = "F:\\qqqwe.txt";

//находим среднее значение целочисленного массива (интов)
float Avg(int* arr, int size)
{
    float avg = 0;
    //i=0
    for (int i = 0; i < size; i++)
    {
        avg += arr[i];
    }
    return avg / size;
}
//показывает сходства 2-х строк
float process(string S1, string S2)
{
    int i, x = 0;
    double K, N;

    if (strlen(S1.c_str()) >= strlen(S2.c_str()))
    {
        for (i = 0; i != strlen(S2.c_str()); i++) {
            if (S1[i] == S2[i])
                x++;
        }
    }
    else
        for (i = 0; i != strlen(S1.c_str()); i++) {
            if (S1[i] == S2[i])
                x++;
        }
    N = (strlen(S1.c_str()) + strlen(S2.c_str())) / 2;

    return ((x / N) * 100);
}
//структура студентов
struct Student
{
public:
    bool isEmpty; // no number
    string fullName; // no number
    int amountOfGrades; // 0
    int* grades;
    float averageGrade; // 1

    Student()
    {
        isEmpty = true;
        fullName = "";
        amountOfGrades = 10;
        grades = new int[10];

        for (int i = 0; i < 10; i++)
        {
            grades[i] = 0;
        }
        averageGrade = 0;
    }

    Student(bool empty, string name, int gradesAmount, int* inputGrades)
    {
        isEmpty = false;
        fullName = name;
        amountOfGrades = gradesAmount;
        grades = inputGrades;
        averageGrade = Avg(grades, amountOfGrades);
    }
    //метод выводит данные об этой структурированной переменной
    void Show()
    {
        cout << "Name: " << fullName << endl;
        cout << "AmountOfGrades: " << amountOfGrades << endl;
        cout << "Grades: ";

        for (int i = 0; i < amountOfGrades; i++)
        {
            cout << grades[i];
            cout << " ";
        }
        cout << endl;
        cout << "Average grade: " << averageGrade << endl;
    }
};
//класс базы данных
class DataBase
{
protected:
    Student* arr;
    int length;
public:
    DataBase() // default constructor
    {
        length = 10;
        arr = new Student[length];
    }
    DataBase(int len)  // constructor with length parametr
    {
        length = len;
        arr = new Student[length];
    }
    //метод очищает заданный элемент
    void ClearElement(int index) // making element empty
    {
        arr[index].isEmpty = true;
    }
    //метод находит 1-й пустой элемент
    int FindCleareElement()  // find first clear element
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i].isEmpty)
            {
                return i;
            }
        }
        return -1;
    }
    //метод позволяет ввести данные структурной переменной в указанную позицию
    void InputData(int index) // input data for element with index = index
    {
        if ((index < length) && (index >= 0))
        {
            cout << "Input name: ";
            string name;
            cin >> name;
            cout << endl;

            cout << endl << "Input amount of grades: ";
            int amountOfGrades;
            cin >> amountOfGrades;
            cout << endl;

            int* grades = new int[amountOfGrades];
            cout << endl << "Input Grades: ";
            for (int i = 0; i < amountOfGrades; i++)
            {
                cin >> grades[i];
                cout << " ";
            }
            cout << endl;

            arr[index] = Student(false, name, amountOfGrades, grades);
        }
        else
        {
            cout << endl << "ERROR!!!";
        }
    }
    void InputData(int index, Student student) // input data for element with index = index
    {
        arr[index] = student;
    }
    //выводит на экран значения структурной переменной
    void ShowOneData(int index) // show element with index = index
    {
        if ((index < length) && (index >= 0))
        {
            if (!arr[index].isEmpty)
            {
                cout << "Name: " << arr[index].fullName << endl;
                cout << "AmountOfGrades: " << arr[index].amountOfGrades << endl;
                cout << "Grades: ";
                for (int i = 0; i < length; i++)
                {
                    cout << arr[index].grades[i];
                    cout << " ";
                }
                cout << endl;
                cout << "Average grade: " << arr[index].averageGrade << endl;
            }
        }
        else
        {
            cout << endl << "ERROR!!!";
        }
    }
    //метод выводит все значения непустых элементов
    void ShowAllData()  // shows all not empty elements
    {
        for (int i = 0; i < length; i++)
        {
            if (!arr[i].isEmpty)
            {
                ShowOneData(i);
                cout << endl;
            }
        }

    }
    //метод возвращает структурную переменную с указанным среднем значением
    //оценок из структурной переменной Student
    Student FindStudentWithAverageGrade(float avgGrade)  // finds student with exact or more similar grade
    {
        int index = -1;
        float nearestGrade = -1000;

        for (int i = 0; i < length; i++)
        {
            Student currentStudent = arr[i];
            if (!currentStudent.isEmpty)
            {
                if (avgGrade - nearestGrade > avgGrade - currentStudent.averageGrade)
                {
                    index = i;
                    nearestGrade = currentStudent.averageGrade;
                }
            }
        }
        if (index == -1)
        {
            cout << "DB is empty!!" << endl;
            return Student();
        }
        return arr[index];
    }
    //метод находит человека с таким же или похожим именем
    Student FindStudentWithName(string name)  // finds student with exact or more similar name
    {
        float maxProximity = -1;
        int index = -1;

        for (int i = 0; i < length; i++)
        {
            if (!arr[i].isEmpty)
            {
                float currentProximity = process(name, arr[i].fullName);

                if (maxProximity <= process(name, arr[i].fullName))
                {
                    maxProximity = currentProximity;
                    index = i;
                }
            }
        }
        if (index == -1)
        {
            cout << "DB is empty!!" << endl;
            return Student();
        }
        return arr[index];
    }
    //метод находит стуркутрну. переменную с минимальных значением поля
    //которое передается в качестве аргумента
    Student FindStudentWithMin(int option) // 0 - to find minimum of amount of grades, 1 - to find minimum average grade
    {
        if (option != 1 && option != 0)
        {
            cout << "ERROR" << endl;
            return Student();
        }
        if (option == 0)
        {
            int min = 12345678;
            int index = -1;

            for (int i = 0; i < length; i++)
            {
                if (!arr[i].isEmpty)
                {
                    if (arr[i].amountOfGrades < min)
                    {
                        index = i;
                        min = arr[i].amountOfGrades;
                    }
                }
                if (index == -1)
                {
                    cout << "DB is empty!!" << endl;
                    return Student();
                }
                return arr[index];
            }
        }
        else
        {
            float min = 12345678;
            int index = -1;

            for (int i = 0; i < length; i++)
            {
                if (!arr[i].isEmpty)
                {
                    if (arr[i].averageGrade < min)
                    {
                        index = i;
                        min = arr[i].amountOfGrades;
                    }
                }
                if (index == -1)
                {
                    cout << "DB is empty!!" << endl;
                    return Student();
                }
                return arr[index];
            }
        }
    }
    //метод сортирует по возрастанию все элементы по значению поля
    //которое передается в качестве аргумента функции
    void SortAscendDB(int option)  // 0 - to sort by amount of grades, 1 - to sort by average grades (ascending)
    {
        if (option == 0)
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].amountOfGrades >= arr[i - 1].amountOfGrades)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
        else
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].averageGrade >= arr[i - 1].averageGrade)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
    }
    //метод сортирует по убывани. все элементы поля
    //которое передается в качестве аргумента функции
    void SortDescendDB(int option)  // 0 - to find sort by amount of grades, 1 - to sort by average grades (descending)
    {
        if (option == 0)
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].amountOfGrades <= arr[i - 1].amountOfGrades)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
        else
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].averageGrade <= arr[i - 1].averageGrade)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
    }
    // запись в файл массива структур
    int SaveDB(string filename)
    {
        FILE* fp, * stream;
        char* c;

        errno_t err;

        // число записываемых байтов
        int size = length * sizeof(Student);

        err = fopen_s(&fp, filename.c_str(), "wb");
        // записываем количество структур
        c = (char*)&length;
        for (int i = 0; i < sizeof(int); i++)
        {
            putc(*c++, fp);
        }
        // посимвольно записываем в файл все структуры
        c = (char*)arr;
        for (int i = 0; i < size; i++)
        {
            putc(*c, fp);
            c++;
        }
        fclose(fp);
        return 0;
    }
    int FindDBLength(string filename)
    {
        FILE* fp, * stream;
        char* c;
        int m = sizeof(int);
        int n, i;

        errno_t err;

        // выделяем память для количества данных
        int* pti = (int*)malloc(m);

        err = fopen_s(&fp, filename.c_str(), "r");

        // считываем количество структур
        c = (char*)pti;
        while (m > 0)
        {
            i = getc(fp);

            if (i == EOF)
                break;

            *c = i;
            c++;
            m--;
        }
        //получаем число элементов
        n = *pti;
        // выделяем память для считанного массива структур
        Student* ptr = (Student*)malloc(n * sizeof(Student));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }
        // перебор загруженных элементов и вывод на консоль
        printf("\n%d people in the file stored\n\n", n);

        free(pti);
        free(ptr);
        fclose(fp);

        return n;
    }
    // загрузка из файла массива структур
    int LoadDB(string filename)
    {
        FILE* fp, * stream;
        char* c;
        int m = sizeof(int);
        int n, i;

        errno_t err;

        // выделяем память для количества данных
        int* pti = (int*)malloc(m);

        err = fopen_s(&fp, filename.c_str(), "r");

        // считываем количество структур
        c = (char*)pti;

        while (m > 0)
        {
            i = getc(fp);

            if (i == EOF)
                break;
            *c = i;
            c++;
            m--;
        }
        //получаем число элементов
        n = *pti;
        // выделяем память для считанного массива структур
        Student* ptr = (Student*)malloc(n * sizeof(Student));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }

        // перебор загруженных элементов и вывод на консоль
        arr = new Student[n];

        for (int k = 0; k < n; k++)
        {
            arr[k] = Student((ptr + k)->isEmpty, (ptr + k)->fullName, (ptr + k)->amountOfGrades, (ptr + k)->grades);
        }

        free(pti);
        free(ptr);
        fclose(fp);

        return 0;
    }
};
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //////////////////////////////////////
    int length = 3;
    DataBase db = DataBase();
    int g1[3] = { 4, 3, 4 };
    Student s1 = Student(false, "Harry", 3, g1);
    int g2[3] = { 5, 5, 5 };
    Student s2 = Student(false, "Drake", 3, g2);
    int g3[4] = { 5, 4, 5, 5 };
    Student s3 = Student(false, "Snape", 4, g3);
    int a = db.FindDBLength(PATH);
    DataBase db1 = DataBase(a);
    db.InputData(0, s1);
    db.InputData(1, s2);
    db.InputData(2, s3);


    /// ////////////////////////////////

    int x, k;
    // DataBase db = DataBase();
    string str;
    do {
        cout << "Что Вы хотите сделать?" << endl;
        cout << "Введите 1, чтобы создать БД" << endl;
        cout << "Введите 2, чтобы показать всю БД" << endl;
        cout << "Введите 3, добавить элементы в БД" << endl;
        cout << "Введите 4, очистить элемент" << endl;
        cout << "Введите 5, чтобы найти 1-й пустой элемент" << endl;
        cout << "Введите 6, чтобы показать только один эелемент БД" << endl;
        cout << "Введите 7, чтобы найти студенка со ср.оценкой ближе к какой-то" << endl;
        cout << "Введите 8, чтобы найти студента по имени" << endl;
        cout << "Введите 9, чтобы отсортировать бд по возрастанию (0 - количество оценок, 1 - средний балл)" << endl;
        cout << "Введите 10, чтобы отсортировать бд по убыванию (0 - количество оценок, 1 - средний балл)" << endl;
        cout << "Введите 11, чтобы сохранить бд в файл" << endl;
        cout << "Введите 12, чтобы найти размер бд" << endl;
        cout << "Введите 13, чтобы загрузить бд" << endl;
        cout << "Введите 14, чтобы завершить" << endl;

        cin >> x;

        switch (x) {
        case 1:
            cout << "Введите размер: " << endl;
            cin >> k;
            DataBase db = DataBase(k);
            cout << endl;
            break;
        case 2:
            db.ShowAllData();
            break;
        case 3:
            cout << "Введите индекс элемента:" << endl;
            cin >> k;
            db.InputData(k);
            db.ShowAllData();
            break;
        case 4:
            cout << "Введите индекс элемента:" << endl;
            cin >> k;
            db.InputData(k, s1);
            db.ShowAllData();
            cout << endl << endl;
            db.ClearElement(k);
            db.ShowAllData();
            break;
        case 5:
            cout << "Введите индекс элемента:" << endl;
            cin >> k;
            db.ClearElement(k);
            cout << db.FindCleareElement();
            break;
        case 6:
            cout << "Введите индекс элемента:" << endl;
            cin >> k;
            db.ShowOneData(k);
            break;
        case 7:
            cout << "Введите оценку для поиска:" << endl;
            db.FindStudentWithAverageGrade(k).Show();
            break;
        case 8:
            cout << "Введите имя для поиска:" << endl;
            cin.ignore(32767, '\n');
            getline(cin, str);
            db.FindStudentWithName(str).Show();
            break;
        case 9:
            cout << "Введите 0 для сортировки по количеству оценок, 1 для сортировки по"
                << " средней оценке" << endl;
            cin >> k;
            db.SortAscendDB(k);
            db.ShowAllData();
            break;
        case 10:
            cout << "Введите 0 для сортировки по количеству оценок, 1 для сортировки по"
                << " средней оценке" << endl;
            cin >> k;
            db.SortDescendDB(k);
            db.ShowAllData();
            break;
        case 11:
            db.SaveDB(PATH);
            break;
        case 12:
            db.SaveDB(PATH);
            cout << db.FindDBLength(PATH);
            break;
        case 13:
            db.SaveDB(PATH);
            int a = db.FindDBLength(PATH);
            DataBase db1 = DataBase(a);
            db1.LoadDB(PATH);
            db1.ShowAllData();
            break;
        case 14:
            return 0;
        }
    } while (true);
}
