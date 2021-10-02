#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const string PATH = "F:\\qwe.txt";

//находим среднее значение целочисленного массива (интов)
float Avg(int* arr, int size)
{
    float avg = 0;

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

    int x;
    DataBase db = DataBase();
    string str;
    do {
        cout << "Что Вы хотите сделать?" << endl;
        cout << "Введите 1, чтобы вывести на экран все элементы Базы данных" << endl;
        cout << "Введите 2, чтобы ввести информацию по индексу" << endl;
        cout << "Введите 3, чтобы очистить элемент по индексуу" << endl;
        cout << "Введите 4, чтобы найти индекс первого пустой записи" << endl;
        cout << "Введите 5, чтобы вывести одну запись по её индексу" << endl;
        cout << "Введите 6, чтобы найти студента с самой близкой к заданной средней оценкой" << endl;
        cout << "Введите 7, чтобы найти студента по имени" << endl;
        cout << "Введите 8, чтобы отсортировать баззу данных по возрастанию количества оценок" 
        << "или по значению средней оценки" << endl;
        cout << "Введите 9, чтобы отсортировать баззу данных по убыванию количества оценок" 
        << "или по значению средней оценки" << endl;
        cout << "Введите 11, чтобы записать Базу данных в файл" << endl;
        cout << "Введите 11, чтобы найти размер Базы данных" << endl;
        cout << "Введите 12, чтобы загрузить Баззу данных из файла" << endl;
        cout << "Введите 13, чтобы выйти из программы" << endl;

        cin >> x;

        switch(x){
            case 1:
                db.ShowAllData();
                cout << endl;
                break;
            case 2:
                int k;
                cout << "Введите индекс элемента:" << endl;
                cin >> k;
                db.InputData(k);
                break;
            case 3:
                int k;
                cout << "Введите индекс элемента:" << endl;
                cin >> k;
                db.ClearElement(k);
                break;        
            case 4:
                cout << "Первый пустой элемент имеет индекс " << db.FindCleareElement() << endl;
                break;
            case 5:
                int k;
                cout << "Введите индекс элемента:" << endl;
                cin >> k;
                db.ShowOneData(k);
                break;
            case 6:
                float f;
                cout << "Введите значение для поиска:" << endl;
                cin >> f;
                db.FindStudentWithAverageGrade(5).Show();
                break;
            case 7:
                cout << "Введите имя для поиска:" << endl;
                cin.ignore(32767, '\n');
                getline(cin,str);
                db.FindStudentWithName(str).Show();
                break;
            case 8:
                int k;
                cout << "Введите 0 для сортировки по количеству оценок, 1 для сортировки по"
                << " средней оценке"<< endl;
                cin >> k;
                db.SortAscendDB(k);
                break;
            case 9:
            int k;
                cout << "Введите 0 для сортировки по количеству оценок, 1 для сортировки по"
                << " средней оценке"<< endl;
                cin >> k;
                db.SortDescendDB(k);
                break;
            case 10:
                db.SaveDB(PATH);
                cout << "База данных успешно записана" << endl;
                break;
            case 11:
                cout << "Размер Базы данных равен " << db.FindDBLength(PATH) << endl;
                break;
            case 12:
                db.LoadDB(PATH);
                cout << "База данных успешно прочитана" << endl;
                break;
            case 13:
                return 0;
        }
    }while(true);
    
    //1 пункт. Создание БД (по умолчанию размер 10)
    /*DataDase db = DataBase(3);*/

    //2 пункт. Показать всю БД. Вызываем метод без параметров
    /*db.ShowAllData();
    cout << endl;*/

    //3 пункт. Добавляем элементы в БД. Вызываем метод с аргументом(индексом элемента внутри БД)
    //или двумя жлементами внутри бд и самим студентом
    /*db.InputData(0, s1);
    * db.InputData(1);
    * db.ShowAllData();
    */

    //4 пункт. Очисткм элемента. Вызываем метод с одним параметром (индексом внутри БД)
    /*db.InputData(0, s1);
    * db.InputData(1);
    * db.ShowAllData();
    * cout << endl << endl;
    * db.ClearElement(0);
    * db.ShowAllData();
    */

    //5 пункт. Находим первый пустой элемент в БД. Вывовем метод, он вернет значение инта индекса
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.ClearElement(1);
    * cout << db.FindCleareElement();
    */

    //6 пункт. Показываем только один жлемент БД. Метод принимает один аргумент - индекс элемента внутри БД
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.ShowOneData(0);
    */

    //7 пункт. Находим студента со средней оценкой ближ. к какой-то. Вызываем метод, который принимает один аргумент
    //типа флоат - нужную ср оценку
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * cout << endl;
    * db.FindStudentWithAverageGrade(5).Show();
    */
    
    //8 пункт. Находим студента с именем. Метод принимает один аругмент типа стринг - нужное имя
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * cout << endl;
    * db.FindStudentWithName("Dr").Show();
    */

    //9 пункт. Сортировка БД по возрастанию оценок или значению ср. оценки. Метод принимает один параметр
    //аргумент типа инт (0-количество оценок, 1 для сортировке по ср оценке)
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * cout << endl;
    * db.SortAscendDB(1);
    * db.ShowAllData():
    */

    //10 пункт. Сортировка БД по убыванию количества оценок или зн.ср.оценки
    //метод принимает 1 параметр типа инт (0-сортировка по кол-ву оценок, 1-сортировка по ср.оценке)
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * cout << endl;
    * db.SortDescendDB(1);
    * db.ShowAllData();
    */

    //11 пункт. Сохраняем БД в файл. Вызываем метод, который
    //принимает 1 параметр - аргумент типа стринг - название тхт файла в котором все хранится
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * const strint PATH = "F:\\qwe.txt";
    * db.SaveDB(PATH);
    */

    //12 пункт. Находим размер БД. Вызываем метод, который
    //принимает один параметр - аргумент типа стринг - название тхт файла
    /*db.InputData(0, s1);
    * db.InputData(1, s2);
    * db.InputData(2, s3);
    * db.ShowAllData();
    * const strint PATH = "F:\\qwe.txt";
    * db.SaveDB(PATH);
    * cout << db.FindDBLenth(PATH);
    */

    //13 пункт. Загружаем БД из файла, вызываем метод, который принимает
    //параметр - аргумент типа стринг - название тхт файла
    /*db.InputData(0, s1);
    db.InputData(1, s2);
    db.InputData(2, s3);
    db.ShowAllData();
    cout << endl;
    cout << endl;
    //cout << db.FindCleareElement();
    cout << endl;
    db.SortDescendDB(1);
    cout << endl << endl << endl << endl;
    db.SaveDB(PATH);
    int a = db.FindDBLength(PATH);
    DataBase db1 = DataBase(a);
    db1.LoadDB(PATH);
    db1.ShowAllData();
    */


    /*int length = 3;
    DataBase db = DataBase(3);
    int g1[3] = { 4, 3, 4 };
    Student s1 = Student(false, "Harry", 3, g1);
    int g2[3] = { 5, 5, 5 };
    Student s2 = Student(false, "Drake", 3, g2);
    int g3[4] = { 5, 4, 5, 5 };
    Student s3 = Student(false, "Snape", 4, g3);
    db.InputData(0, s1);
    db.InputData(1, s2);
    db.InputData(2, s3);
    db.ShowAllData();
    cout << endl;
    cout << endl;
    //cout << db.FindCleareElement();
    cout << endl;
    db.SortDescendDB(1);
    cout << endl << endl << endl << endl;
    db.SaveDB(PATH);
    int a = db.FindDBLength(PATH);
    DataBase db1 = DataBase(a);
    db1.LoadDB(PATH);
    db1.ShowAllData();*/
}
