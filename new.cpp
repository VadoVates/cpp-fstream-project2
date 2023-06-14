#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int gradeQty = 5;

struct STUDENT
{
    string im_nazwisko;
    float oceny[gradeQty];
    float sredniaOcen;
};

bool OpenFileRead(ifstream&, string, int&);
void DrawingRandomNumbersAndFillingArray(ifstream&, STUDENT*, int);
int HowManyStudensHaveHigherGradeThanTheAverage(STUDENT*, int);
void DisplayStudentsData(STUDENT*, int);
float TheHighestPGA(STUDENT*, int);
int ListOfStudentsWithTheHighestPGA(STUDENT*, float, int);
bool SaveToTheFile(STUDENT*, float, int, string);
bool FindString(STUDENT*, int, const string&);
int Partition(int[], int, int);
void QuickSort(int[], int, int);
void GradeRepresentation (STUDENT*, int);
void ShowMenu(STUDENT*, int);

int main()
{
    srand(time(0));
    cout << "PROGRAM ODCZYTUJACY DANE STUDENTOW Z PLIKU" << endl;
    int N, numberOfLines;
    string fileName, searchStr;
    ifstream fileInput;
    cout << "Podaj nazwe pliku, w ktorym znajduja sie dane studentow (domyslnie to sa \"dane.txt\")" << endl;
    cin >> fileName;
    if (OpenFileRead(fileInput, fileName, numberOfLines) == false)
    {
        cout << "Otwarcie pliku \"dane.txt\", zakonczone niepowodzeniem. Koniec programu." << endl;
        return 1;
    }
    cout << "Podaj ilu jest studentow: ";
    cin >> N;
    if (N>numberOfLines) {
        cout << "Podana ilosc studentow jest wieksza niz wystepuje w pliku. Wczytano max studentow, czyli: " << numberOfLines << endl;
        N = numberOfLines;
    }
    STUDENT* arr = new STUDENT[N];
    DrawingRandomNumbersAndFillingArray(fileInput, arr, N);
    ShowMenu(arr, N);

    fileInput.close();
    delete[] arr;
    return 0;
}

bool OpenFileRead(ifstream& myFile, string fileName, int &numberOfLines)
{
    
    myFile.open(fileName, ios::in);

    if (!myFile.is_open())
    {
        return false;
    }

    numberOfLines = count (istreambuf_iterator<char>(myFile),istreambuf_iterator<char>(), '\n') + 1;
    myFile.clear();
    myFile.seekg (0, ios::beg);

    return true;
}

void DrawingRandomNumbersAndFillingArray(ifstream& myFile, STUDENT* arr, int arraySize)
{
    float sum;
    for (int i = 0; i < arraySize; i++)
    {
        sum = 0.0;
        if (!getline(myFile, arr[i].im_nazwisko))
        {
            cout << "Blad odczytu danych z pliku. Program zakonczy dzialanie" << endl;
            myFile.close();
            exit(1);
        }
        for (int j = 0; j < gradeQty; j++)
        {
            arr[i].oceny[j] = (rand() % 7) / 2.0 + 2.0;
            sum += arr[i].oceny[j];
        }
        arr[i].sredniaOcen = sum / gradeQty;
    }
}

int HowManyStudensHaveHigherGradeThanTheAverage(STUDENT* arr, int arraySize)
{
    int studentsWhoHaveHigherGradeThanTheAverage = 0;
    float sum = 0.0;
    for (int i = 0; i < arraySize; i++)
    {
        sum += arr[i].sredniaOcen;
    }
    sum = sum / arraySize;

    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i].sredniaOcen > sum)
            ++studentsWhoHaveHigherGradeThanTheAverage;
    }

    return studentsWhoHaveHigherGradeThanTheAverage;
}

void DisplayStudentsData(STUDENT* arr, int N)
{
    cout << endl;
    cout << setw(20) << left << "Imie i nazwisko";
    cout << " | ";
    cout << setw(10) << "Oceny";
    cout << setw(20) << left << "";
    cout << " | ";
    cout << setw(20) << left << "Srednia" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << setw(20) << left << arr[i].im_nazwisko;
        cout << " | ";
        for (int j = 0; j < gradeQty; j++)
        {
            cout << setw(5) << fixed << setprecision(2) << arr[i].oceny[j] << " ";
        }
        cout << " | " << setw(7) << fixed << setprecision(2) << arr[i].sredniaOcen << endl;
    }
}

float TheHighestPGA(STUDENT* arr, int N)
{
    float theHighestPGA = 0;

    for (int i = 0; i < N; i++)
    {
        if (theHighestPGA < arr[i].sredniaOcen)
        {
            theHighestPGA = arr[i].sredniaOcen;
        }
    }
    return theHighestPGA;
}

int ListOfStudentsWithTheHighestPGA(STUDENT* arr, float theBestPGA, int N)
{
    int studentsNumber = 0;
    cout<<endl;
    for (int i = 0; i < N; i++)
    {
        if (arr[i].sredniaOcen == theBestPGA)
        {
            cout << " " << studentsNumber + 1 << ". " << arr[i].im_nazwisko << " ";
            for (int j = 0; j < gradeQty; j++)
            {
                cout << setw(5) << fixed << setprecision(2) << arr[i].oceny[j] << " ";
            }
            cout << arr[i].sredniaOcen << endl;
            studentsNumber++;
        }
    }
    return studentsNumber;
}

bool SaveToTheFile(STUDENT* arr, float TheHighestPGA, int N, string fileName)
{
    ofstream outputfile(fileName, ios::out);

    if (!outputfile)
    {
        cout << "Blad podczas otwierania pliku." << endl;
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        if (arr[i].sredniaOcen == TheHighestPGA)
        {
            outputfile << arr[i].im_nazwisko << " ";
            for (int j = 0; j < gradeQty; j++)
            {
                outputfile << arr[i].oceny[j] << " ";
            }
            outputfile << arr[i].sredniaOcen << endl;
        }
    }
    outputfile.close();
    return true;
}

bool FindString(STUDENT* arr, int N, const string& searchStr)
{
    bool found = false; // Flaga informująca, czy znaleziono wynik

    for (int i = 0; i < N; i++)
    {
        if (arr[i].im_nazwisko == searchStr)
        {
            if (!found)
            {
                cout << "Znaleziono wynik dla frazy: \"" << searchStr << "\"" << endl;
                found = true;
            }
            cout<<endl;
            cout << "Student " << arr[i].im_nazwisko << " znaleziony na pozycji " << i + 1 << endl;
            cout<<endl;
            cout << " " << i + 1 << ". " << arr[i].im_nazwisko << " ";
            for (int j = 0; j < gradeQty; j++)
            {
                cout << setw(5) << fixed << setprecision(2) << arr[i].oceny[j] << " ";
            }
            cout << arr[i].sredniaOcen << endl;
        }
    }

    if (!found)
    {
        cout << "Nie znaleziono wyniku dla frazy: \"" << searchStr << "\"" << endl;
    }

    return found;
}

void ShowMenu(STUDENT* arr, int N)
{
    int choice;
    string searchStr;

    while (true)
    {
        cout << endl;
        cout << "======= MENU =======\n";
        cout << "1. Wyswietl dane wszystkich studentow"<<endl;
        cout << "2. Ilu studentow posiada srednia ocen powyzej sredniej wszystkich studentow "<<endl;
        cout << "3. Wylistuj studentow z najwyzsza srednia i zapisz do pliku"<<endl;
        cout << "4. Wyszukaj studenta"<<endl;
        cout << "5. Reprezentacja statystyczna przyznanych ocen" << endl;
        cout << "0. Wyjscie"<<endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                DisplayStudentsData(arr,N);
                break;
            }
            case 2:
            {
                cout<<endl;
                cout << "Ciekawe jak wiele studentow ma srednia ocen wyzsza niz srednia reszty?" << endl;
                cout << "A, tutaj mam akurat odpowiedz: " << HowManyStudensHaveHigherGradeThanTheAverage(arr, N) << endl;
                break;
            }
            case 3:
            {
                float theHighestPGA = TheHighestPGA(arr, N);
                int numberOfStudents = ListOfStudentsWithTheHighestPGA(arr, theHighestPGA, N);
                string fileName;
                cout<<endl;
                cout << "Podaj nazwe pliku do zapisu: ";
                cin >> fileName;

                if (SaveToTheFile(arr, theHighestPGA, numberOfStudents, fileName))
                {
                    cout << "Dane zostaly zapisane do pliku \"" << fileName << "\"" << endl;
                }
                else
                {
                    cout << "Blad podczas zapisywania do pliku." << endl;
                }
                break;
            }
            case 4:
            {
                cout<<endl;
                cout << "Podaj fraze do wyszukania: ";
                cin.ignore();
                getline(cin, searchStr);
                FindString(arr, N, searchStr);
                break;
            }
            case 5:
            {
                cout << endl;
                GradeRepresentation(arr, N);
            }
            case 0:
                return;
            default:
                cout << "Niepoprawna opcja. Wybierz ponownie." << endl;
        }
    }
}

int Partition(int array[], int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = array[pivotIndex];
    int i = left, j = right;
    int temp;
    while(i <= j) {
        while(array[i] < pivotValue) {
            i++;
        }
        while(array[j] > pivotValue) {
            j--;
        }
        if(i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void QuickSort(int array[], int left, int right) {
    if(left < right) {
        int pivotIndex = Partition (array, left, right);
        QuickSort(array, left, pivotIndex - 1);
        QuickSort(array, pivotIndex, right);
    }
}

void GradeRepresentation (STUDENT *arr, int N) {
    int gradeArraySize = N*gradeQty;
    int *gradeArray = new int [gradeArraySize];
    
    for (int i=0; i<N; i++) {
        int rowNumber = i*gradeQty;
        for (int j=0; j<gradeQty; j++) {
            gradeArray[rowNumber+j] = (int) (arr[i].oceny[j] * 2);
        }
    }

    QuickSort (gradeArray, 0, gradeArraySize-1);

    for (int i=0; i<gradeArraySize; i++) {
        cout << gradeArray [i] << " ";
    }

    delete []gradeArray;
}