//Autorzy: FILIP BARSZCZ (nr indeksu: 155624) oraz MAREK GÓRSKI (nr indeksu: 155647).
//Grupa D1, semestr II, rok akademicki 2022/2023, kierunek Informatyka

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int gradeQtyPerStudent = 5;
const int gradeRangeQty = 7;

struct STUDENT
{
    string im_nazwisko;
    float oceny[gradeQtyPerStudent];
    float sredniaOcen;
};

bool OpenFileRead(ifstream&, string, int&);
void DrawingRandomNumbersAndFillingArray(ifstream&, STUDENT*, int);
int HowManyStudensHaveHigherGradeThanTheAverage(STUDENT*, int);
void DisplayStudentsData(STUDENT*, int);
float TheHighestPGA(STUDENT*, int);
void ListOfStudentsWithTheHighestPGA(STUDENT*, float, int);
bool SaveToTheFile(STUDENT*, float, int, string);
bool FindString(STUDENT*, int, const string&);
void Histogram (STUDENT*, int);
void ShowMenu(STUDENT*, int);
string GradeToString (int);

int main()
{
    srand(time(0));
    for (int i=0; i<71;i++) cout << "-";
    cout << endl;
    cout << "PROJEKT ZALICZENIOWY 2_2 Z PRZEDMIOTU PODSTAWY PROGRAMOWANIA 2" << endl;
    for (int i=0; i<71;i++) cout << "-";
    cout << endl << endl;
    int N, numberOfLines;
    string fileName, searchStr;
    ifstream fileInput;
    cout << "Podaj nazwe pliku, w ktorym znajduja sie dane studentow (domyslnie to sa \"dane.txt\")" << endl;
    cout << "Nazwa pliku zrodlowego: ";
    cin >> fileName;
    if (OpenFileRead(fileInput, fileName, numberOfLines) == false)
    {
        cout << "Otwarcie pliku \"dane.txt\", zakonczone niepowodzeniem. Koniec programu." << endl;
        return 1;
    }
    cout << "Podaj ilu studentow chcesz wczytac (zliczono max. ilosc studentow: " << numberOfLines << "): ";
    cin >> N;
    do
        {
    if (N>numberOfLines) {
        cout << "Podana ilosc studentow jest wieksza niz wystepuje w pliku. Wczytano max studentow, czyli: " << numberOfLines << "." << endl;
        N = numberOfLines;
    }
    else if(N<0)
    {
            cout<<"Podano wartosc ujemna, program nie moze wyswietlic poprawnie danych. Prosze podac nowe N"<<endl;
            cin.clear();
            cout<<"Poprawiona wartosc: ";
            cin>>N;
    }
    else
    {
        cout<<"Wczytano dane"<<endl;
    }}while(N<0);

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
        for (int j = 0; j < gradeQtyPerStudent; j++)
        {
            arr[i].oceny[j] = (rand() % 7) / 2.0 + 2.0;
            sum += arr[i].oceny[j];
        }
        arr[i].sredniaOcen = sum / gradeQtyPerStudent;
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
        for (int j = 0; j < gradeQtyPerStudent; j++)
        {
            cout << setw(5) << fixed << setprecision(1) << arr[i].oceny[j] << " ";
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

void ListOfStudentsWithTheHighestPGA(STUDENT* arr, float theBestPGA, int N)
{
    int studentsNumber = 0;
    cout<<endl;
    for (int i = 0; i < N; i++)
    {
        if (arr[i].sredniaOcen == theBestPGA)
        {
            cout << " " << studentsNumber + 1 << ". " << arr[i].im_nazwisko << ", oceny: ";
            for (int j = 0; j < gradeQtyPerStudent; j++)
            {
                cout << setw(3) << fixed << setprecision(1) << arr[i].oceny[j];
                cout << ", ";
            }
            cout << "srednia ocen: " << arr[i].sredniaOcen << "." << endl;
            studentsNumber++;
        }
    }

}

bool SaveToTheFile(STUDENT* arr, float TheHighestPGA, int N, string fileSave)
{
    ofstream outputfile(fileSave, ios::out);

    if (!outputfile)
    {
        cout << "Blad podczas otwierania pliku." << endl;
        return false;
    }

    int studentsNumber = 1;
    for (int i = 0; i < N; i++)
    {
        if (arr[i].sredniaOcen == TheHighestPGA)
        {
            if (studentsNumber > 1) outputfile << endl;
            outputfile << " " << studentsNumber;
            outputfile << ". ";
            outputfile << arr[i].im_nazwisko;
            outputfile << ", oceny: ";
            for (int j = 0; j < gradeQtyPerStudent; j++)
            {
                outputfile << fixed << setprecision (1) << arr[i].oceny[j];
                outputfile << ", ";
            }
            outputfile << "srednia ocen: ";
            outputfile << arr[i].sredniaOcen;
            outputfile << ".";
            studentsNumber++;
        }
    }

    outputfile.close();
    return true;
}

bool FindString(STUDENT* arr, int N, const string& searchStr)
{
    bool found = false; // Flaga informująca, czy znaleziono wynik
    int searchStrLength = searchStr.length();

    for (int i = 0; i < N; i++)
    {
        int j=0;
        int nameLength = arr[i].im_nazwisko.length();

        for (int k=0; k <= nameLength - searchStrLength; k++) {
            if (arr[i].im_nazwisko[k] != searchStr[j]) continue;
            
            while (arr[i].im_nazwisko[k+j] == searchStr[j]) j++;
            if (j>=searchStrLength) {
                found = true;
                cout << "Student " << arr[i].im_nazwisko << " znaleziony na pozycji " << i + 1 << endl;
                cout << " " << i + 1 << ". " << arr[i].im_nazwisko << ", oceny: ";
                for (int h = 0; h < gradeQtyPerStudent; h++)
                {
                    cout << setw(3) << fixed << setprecision(1) << arr[i].oceny[h];
                    cout << ", ";
                }
                cout << "srednia ocen: " << arr[i].sredniaOcen << "." << endl << endl;
            } else {
                j=0;
            }
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
        cout << "3. Wylistuj studenta (lub studentow) z najwyzsza srednia i zapisz do pliku"<<endl;
        cout << "4. Wyszukaj studenta"<<endl;
        cout << "5. Reprezentacja graficzna ilosci przyznanych ocen - histogram" << endl;
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
                ListOfStudentsWithTheHighestPGA(arr, theHighestPGA, N);
                string fileSave;
                cout<<endl;
                char doYouWantToSaveData;
                cout << "Czy chcesz zapisac dane do pliku [t]? ";
                cin >> doYouWantToSaveData;
                if (doYouWantToSaveData == 't' || doYouWantToSaveData == 'T') {
                    cout << "Podaj nazwe pliku do zapisu: ";
                    cin >> fileSave;

                    if (SaveToTheFile(arr, theHighestPGA, N, fileSave))
                    {
                        cout << "Dane zostaly zapisane do pliku \"" << fileSave << "\"" << endl;
                    }
                    else
                    {
                        cout << "Blad podczas zapisywania do pliku." << endl;
                    }
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
                Histogram(arr, N);
                break;
            }
            case 0:
                return;
            default:
                cout << "Niepoprawna opcja. Wybierz ponownie." << endl;
        }
    }
}

void Histogram (STUDENT *arr, int N) {
    int i;
    int gradeQtyArraySize = gradeRangeQty;
    int *gradeQtyArray = new int [gradeQtyArraySize] {0};
    
    for (i=0; i<N; i++) {
        for (int j=0; j<gradeQtyPerStudent; j++) {
            int index = (int) (arr[i].oceny[j] * 2.01);
            ++gradeQtyArray[index-4];
        }
    }

    int mostPopularGrade = 0;
    string popularGrade = "2.0";
    for (i=1; i<gradeQtyArraySize; i++) {
        if (gradeQtyArray[i] > gradeQtyArray [mostPopularGrade]) {
            mostPopularGrade = i;
            popularGrade = GradeToString (i);
        } else if (gradeQtyArray[i] == gradeQtyArray [mostPopularGrade]) {
            popularGrade += ", ";
            popularGrade += GradeToString (i);
        }
    }
    cout << setw(33) << internal << "ROZKLAD OCEN - HISTOGRAM" << endl << endl;
    for (i=(gradeQtyArray[mostPopularGrade]);i>=1;i--)
	{
	    cout << setw(8) << i;
		for (int j=0;j<gradeQtyArraySize;j++)
		{
			if (gradeQtyArray[j]==i)
			{
				cout << "| * ";
				gradeQtyArray[j]--;
			}
			else
			{
				cout << "|   ";
			}
		}
		cout << "|" << endl;
	}
	cout << "--------+---+---+---+---+---+---+---+" << endl;
	cout << setw(8) << "Ocena";
    cout << "| 2 |2.5| 3 |3.5| 4 |4.5| 5 |" << endl;
    cout << endl;
    cout << "Najczesciej wystepujaca ocena: " << fixed << setprecision(1) << popularGrade << "." << endl;

    delete []gradeQtyArray;
}

string GradeToString (int given) {
    string grade = "";
    if (given == 0) grade = "2.0";
    if (given == 1) grade = "2.5";
    if (given == 2) grade = "3.0";
    if (given == 3) grade = "3.5";
    if (given == 4) grade = "4.0";
    if (given == 5) grade = "4.5";
    if (given == 6) grade = "5.0";
    return grade;
}