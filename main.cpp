#include <iostream>
#include <fstream>

using namespace std;

void fillArray(int arr1[], int arrLength) { //funckja ktora wypelni tymczasowa tablice wartosciami 1,2,3,4 ... 10000
    for (int i = 0; i < arrLength; i++) {
        arr1[i] = i + 1; //+1 aby przypisywac wartosci od 1 do 10000
    }
}

void luckyNumbersGenerator(int inputArrLength,
                           int luckyNumbers[]) { // funkcja generujaca dla nas wszystkie szczesliwe liczby i ktore zapisze do tablicy luckyNumbers[]

    luckyNumbers[0] = 1; // przypisujemy domyslna liczbe szczesliwa jako pierwsza do tablicy

    bool flag = false, isNextLucky; // zmienne typu bool ktore beda flagami w programie beda sluzyc za bramki dla algorytmu
    int counter, arrCounter = 1, luckyNumber = 2, *arr, *arr1; // liczniki oraz luckyNumber = 2 ktora bedzie miala za zadanie przefiltrowac podczas 1 przejscia wszystkie parzyste liczby
    // oraz 2 tymczasowe tablice bedziemy z jednej do drugiej przepisywac przefiltrowane dane

    arr1 = new int[inputArrLength]; // deklarujemy tablice o dlugosci inputArrLength domyslne w zadaniu jest to 10 000

    fillArray(arr1,
              inputArrLength); // wypelniamy ja wartosciami od 1 do 10 000 zeby pozniej moc usuwac poszczegolne przefiltrowane liczby i uzyskiwac szczesliwe liczby


    while (luckyNumber <
           inputArrLength) { // petla bedzie szukac liczb szczesliwych dopoki beda mniejsze od podanej max wartosci w zadaniu czyli 10 000

        isNextLucky = false; // domyslna wartosc flagi ktorej bedziemy uzywac w 48-56 linijce
        counter = 0; // zerujemy counter aby w 36 lub 40 linijce przypisywac w tablicy wartosci od 0

        arr = new int[inputArrLength]; //za kazdym razem kiedy znajdziemy liczbe szczesliwa bedziemy tworzyc nowa tablice zeby wpisac tam przesiane wartosci

        for (int i = 0; i <
                        inputArrLength; i++) {  //petla ktora przesiewa wartosci czyli usuwa wartosci indeksow dzielacych sie bez reszty przez liczbe szczesliwa

            if ((i + 1) % luckyNumber != 0 &&
                flag) { //flaga sluzy tutaj po to zeby za pierwszym razem domyslne przefiltrowalo tablice przez 2

                arr[counter] = arr1[i];
                counter++;
            } else if (i % luckyNumber == 0 &&
                       !flag) { // tutaj jest warunek ktory tylko zadziala za pierwszym razem i bedzie on filtrowal przez 2

                arr[counter] = arr1[i];
                counter++;
            }
        }

        flag = true; // domyslna wartosc dla flagi zeby tylko za 1 razem przefiltrowalo przez 2
        counter = 0; // zerujemy counter aby ponownie go uzyc przy przeszukiwaniu tablicy

        while (!isNextLucky) { // petla bedzie szukac az znajdzie 1 wartosc w przefiltrowanej tablicy wieksza od poprzedniej liczby szczesliwej i bedzie sie wykonywac dopoki taka znajdzie
            if (luckyNumber < arr[counter]) {
                luckyNumber = arr[counter];
                isNextLucky = true; // jezeli znajdzie wartosc wieksza zmieniamy flage i konczymy pętle
                luckyNumbers[arrCounter] = luckyNumber; // tutaj dodajemy do tablicy ktora utworzylismy w mainie wszystkie liczby szczesliwe
                arrCounter++;
            }
            counter++;
        }
        arr1 = arr; // zamieniamy tablice nieprzefiltrowana przez nowa szczesliwa liczbe na przefiltrowana liczbe
    }
}

bool isLucky(int inputValue,
             int luckyNumbers[]) { // funkcja ktora bedzie sprawdac czy podana liczba znajduje sie w wczesniej wygenerowanej tablicy szczesliwych liczb
    for (int i = 0; i < 10000; i++) {
        if (luckyNumbers[i] == inputValue) return true;
        if (luckyNumbers[i] > inputValue) return false;
    }
}

bool isPrime(int inputValue) { // funkcja typu bool zwraca true albo false

    if (inputValue <= 2)
        return false; // sprawdzamy czy liczba nie jest mniejsza od 2 wtedy z definicji mozemy odrazu odrzucic taka liczbe

    for (int i = 2; i <=
                    sqrt(inputValue); i++) { // sprawdzamy dzielniki od 2 do sqrt(n) aby program byl wydajniejszy dalszych i wczesniejszych dzielnikow nie musimy sprawdzac

        if (inputValue % i == 0)
            return false; // jezeli znajdzie sie jakis dzielnik to z definicji odrazu mozemy odrzucic taka liczbe
    }

    return true; // jezeli nie znajdziemy zadnych dzielnikow uznajemy taka liczbe za liczbe pierwsza
}

int main() {
    int *luckyNumbers; // tworzymy miejsce w pamieci dla naszych liczb szczesliwych ktore bedziemy do tej tablicy zapisywac
    luckyNumbers = new int[10000];

    fstream read;

    int inputValue, counter4_1 = 0, counter4_2 = 1, counter4_3 = 0, maxTrain4_2 = 1, firstInTrain, tempFirstInTrain;
    bool previousLucky = false; // flaga do zadania 4_2 ktora bedzie mowic czy poprzednia wartosc byla liczba szczesliwa czy nie

    luckyNumbersGenerator(10000, luckyNumbers); // generujemy najpierw wszystkie liczby szczesliwe mniejsze od  10 000

    read.open("dane.txt", ios::in); // otwieramy plik do odczytu
    while (!read.eof()) { // petla bedzie sie wykonywac dopoki bedzie jakas wartosc w pliku
        read >> inputValue; // sciagamy 1 wartosc z pliku

        if (isLucky(inputValue, luckyNumbers)) { // sprawdzamy czy jest szczesliwa
            counter4_1++; // jezeli jest to do zadania 4_1 naliczamy


            if (previousLucky) { // jezeli poprzednia jest szczesliwa to liczymy ciag
                counter4_2++;
            }
            if (counter4_2 == 1) {
                tempFirstInTrain = inputValue;
            }

            if (isPrime(
                    inputValue)) { // zadanie 4_3 sprawdzamy czy dana liczba jest rowniez liczba pierwsza jezeli jest naliczamy
                counter4_3++;
            }

            if (counter4_2 > maxTrain4_2) { // jezeli dany ciag bedzie wiekszy od obecnego najdluzszego zapisujemy wynik
                maxTrain4_2 = counter4_2;
                firstInTrain = tempFirstInTrain;
            }

            previousLucky = true; // flaga zeby w nastepnym obejsciu zlapalo warunek ze poprzednia byla szczesliwa
        } else {
            previousLucky = false; // jezeli liczba nie jest szczesliwa ustawiamy flage na false i zerujemy licznik do domyslnej wartosci 1
            counter4_2 = 1;
        }
    }
    read.close();

    cout << "4.1 ->" << counter4_1 << endl; // wynik 4_1 -> 307
    cout << "4.2 ->" << maxTrain4_2 << " pierwsza liczba w ciagu -> " << firstInTrain << endl; // wynik 4_2 -> 27, 1749
    cout << "4.3 ->" << counter4_3 << endl;  // wynik 4_3 -> 56

    return 0;
}
