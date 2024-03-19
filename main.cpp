#include <iostream>
using namespace std;
void wypisz(int n, char znak[], int dlugosci[], int* tablica[]);
void przerob(int* tablica[], int dlugosci[], int indeks);
void przesun(int* tablica[], int dlugosc, int indeks);
void dodawanie(int* tablica[], int indeks1, int indeks2, int indeks3, int dlugosci[]);
void odejmowanie(int* tablica[], int indeks1, int indeks2, int indeks3, int dlugosci[]);
void przerobod(int* tablica[], int dlugosci[], int indeks);
int porownaj(int* tablica[], int dlugosci[], int indeks1, int indeks2);
void minimum(int* tablica[], int dlugosci[], int n, char znak[], int sameujemne, int samedodatnie, char symbol, int przekierowanie);
void maksimum(int* tablica[], int dlugosci[], int n, char znak[], int sameujemne, int samedodatnie, char symbol, int przekierowanie);
void czysame(char znaki[], int* samedodatnie, int* sameujemne, int n);
int potega(int x, int y);
int main()
{
    int n = 0;
    int indeks1 = 0;
    int indeks2 = 0;
    int indeks3 = 0;
    char* liczba;
    int samedodatnie = 1;
    int sameujemne = 1;
    int wyjscie = 0;
    char* polecenie;
    //cout << "Podaj ile liczb chcesz wprowadzic: " << endl;
    cin >> n;
    int** tablica;
    char* znak;
    znak = new char[n];

    if (znak == NULL) {
        cout << "Brak pamieci!";
        delete[] znak;
        return 0;
    }

    tablica = new int* [n];
    if (tablica == NULL) {
        cout << "Brak pamieci!";
        delete[] tablica;
        delete[] znak;
        return 0;
    }
    int* dlugosci;
    dlugosci = new int[n];

    if (dlugosci == NULL) {
        cout << "Brak pamieci!";
        delete[] tablica;
        delete[] dlugosci;
        delete[] znak;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        //cout << "Wpisz liczbe: ";
        liczba = (char*)malloc(4 * sizeof(char));

        if (liczba == NULL) {
            cout << "Brak pamieci!";
            delete[] tablica;
            delete[] dlugosci;
            delete[] znak;
            return 0;
        }

        int licznik = 0;
        int pamiecst = 2;
        while (scanf("%c", &liczba[licznik])) {
            if ((liczba[licznik] == '\n') && (licznik == 0)) licznik--;                             //pozbywanie sie niechcianego entera
            if ((liczba[licznik] == '\n') && (licznik != 0)) break;
            if (licznik >= pamiecst) {
                pamiecst = pamiecst * 2;
                char* nliczba = (char*)realloc(liczba, (pamiecst + 1) * sizeof(char));
                if (nliczba != NULL) {
                    liczba = nliczba;
                }
            }
            licznik++;
        }
        if (liczba[0] == '-') licznik--;
        dlugosci[i] = licznik;
        licznik = 0;
        tablica[i] = (int*)malloc((dlugosci[i] + 1) * sizeof(int));

        if (tablica[i] == NULL) {
            cout << "Brak pamieci!";
            return 0;

        }

        for (int j = 0; j < dlugosci[i]; j++) {
            if (liczba[0] != '-') {
                tablica[i][j] = (int)liczba[j] - 48;
                znak[i] = '+';


            }
            else {
                tablica[i][j] = (int)liczba[j + 1] - 48;
                znak[i] = '-';


            }
        }
        free(liczba);

    }
    while (wyjscie != 1) {
        polecenie = new char[20];
        int l = 0;
        while (scanf("%c", &polecenie[l])) {

            if ((polecenie[l] == '\n') && (l != 0)) break;
            l++;
        }

        if ((polecenie[0] >= 48) && (polecenie[0] <= 57)) {
            indeks3 = 0;
            indeks1 = 0;
            indeks2 = 0;
            int licznik = 0;
            int licznik2 = 0;
            int licznik3 = 0;
            while ((polecenie[licznik] >= 48) && (polecenie[licznik] <= 57)) licznik++;

            for (int i = 0; i < licznik; i++) {
                indeks3 = indeks3 + ((int)polecenie[i] - 48) * potega(10, licznik - i - 1);
            }

            licznik2 = licznik + 3;
            while ((polecenie[licznik2] >= 48) && (polecenie[licznik2] <= 57)) licznik2++;

            for (int i = licznik + 3; i < licznik2; i++) {
                indeks1 = indeks1 + ((int)polecenie[i] - 48) * potega(10, licznik2 - i - 1);
            }

            char operacja = polecenie[licznik2 + 1];
            licznik3 = licznik2 + 3;
            while ((polecenie[licznik3] >= 48) && (polecenie[licznik3] <= 57)) licznik3++;

            for (int i = licznik2 + 3; i < licznik3; i++) {
                indeks2 = indeks2 + ((int)polecenie[i] - 48) * potega(10, licznik3 - i - 1);
            }


            int ind = porownaj(tablica, dlugosci, indeks1, indeks2);                                //indeksy wiekszej i mniejszej liczby
            int ink;
            if (ind == indeks1) ink = indeks2;
            else ink = indeks1;

            if (operacja == '+') {

                if (znak[indeks1] == znak[indeks2]) {
                    dodawanie(tablica, indeks1, indeks2, indeks3, dlugosci);
                    znak[indeks3] = znak[indeks1];
                }
                else {
                    odejmowanie(tablica, ind, ink, indeks3, dlugosci);
                    znak[indeks3] = znak[ind];
                }
            }
            else if (operacja == '-') {

                if (znak[indeks1] == znak[indeks2]) {
                    odejmowanie(tablica, ind, ink, indeks3, dlugosci);
                    if (znak[indeks1] == '+') {
                        if (indeks1 == ind) znak[indeks3] = '+';
                        else znak[indeks3] = '-';
                    }

                    else if (znak[indeks1] == '-') {
                        if (indeks1 == ind) znak[indeks3] = '-';
                        else znak[indeks3] = '+';
                    }
                }
                else {
                    dodawanie(tablica, indeks1, indeks2, indeks3, dlugosci);
                    znak[indeks3] = znak[indeks1];
                }
            }
        }

        else if (polecenie[1] == 'a') {
            czysame(znak, &samedodatnie, &sameujemne, n);
            maksimum(tablica, dlugosci, n, znak, sameujemne, samedodatnie, '-', 0);
        }

        else if (polecenie[1] == 'i') {
            czysame(znak, &samedodatnie, &sameujemne, n);
            minimum(tablica, dlugosci, n, znak, sameujemne, samedodatnie, '-', 0);
        }

        else if (polecenie[0] == '?') {
            wypisz(n, znak, dlugosci, tablica);
        }

        else if (polecenie[0] == 'q') {
            wyjscie = 1;
        }
        delete[] polecenie;
    }
    delete[] tablica;
    delete[] dlugosci;
    delete[] znak;
}

void przerob(int* tablica[], int dlugosci[], int indeks) {
    for (int i = 0; i < dlugosci[indeks]; i++) {
        if (tablica[indeks][dlugosci[indeks] - 1 - i] >= 10) {
            if (dlugosci[indeks] - 1 - i != 0) tablica[indeks][dlugosci[indeks] - 1 - i] -= 10;
            tablica[indeks][dlugosci[indeks] - 2 - i] += 1;
        }
    }
}
void przesun(int* tablica[], int dlugosc, int indeks) {
    for (int i = 0; i < dlugosc; i++) {
        if (dlugosc - 1 - i >= 0)       tablica[indeks][dlugosc - i] = tablica[indeks][dlugosc - 1 - i];
    }
}

void dodawanie(int* tablica[], int indeks1, int indeks2, int indeks3, int dlugosci[]) {
    int ile, od, dluzszy;
    if (dlugosci[indeks1] < dlugosci[indeks2]) {
        ile = dlugosci[indeks1]; od = dlugosci[indeks2]; dluzszy = indeks2;
    }
    else {
        ile = dlugosci[indeks2]; od = dlugosci[indeks1]; dluzszy = indeks1;
    }
    tablica[indeks3] = (int*)realloc(tablica[indeks3], od * sizeof(int*));

    for (int i = 0; i < ile; i++) {
        tablica[indeks3][od - i - 1] = tablica[indeks1][dlugosci[indeks1] - i - 1] + tablica[indeks2][dlugosci[indeks2] - i - 1];
    }
    for (int i = 0; i < (od - ile); i++) {
        tablica[indeks3][i] = tablica[dluzszy][i];
    }

    dlugosci[indeks3] = od;
    przerob(tablica, dlugosci, indeks3);

    if (tablica[indeks3][0] >= 10) {
        tablica[indeks3] = (int*)realloc(tablica[indeks3], (od + 1) * sizeof(int*));
        dlugosci[indeks3] = od + 1;
        przerob(tablica, dlugosci, indeks3);
        przesun(tablica, dlugosci[dluzszy], indeks3);
        tablica[indeks3][1] = tablica[indeks3][1] - 10;
        tablica[indeks3][0] = tablica[indeks3][0] / 10;
    }
}

void odejmowanie(int* tablica[], int indeks1, int indeks2, int indeks3, int dlugosci[]) {
    int ile, od, dluzszy;
    if (dlugosci[indeks1] < dlugosci[indeks2]) {
        ile = dlugosci[indeks1]; od = dlugosci[indeks2]; dluzszy = indeks2;
    }
    else {
        ile = dlugosci[indeks2]; od = dlugosci[indeks1]; dluzszy = indeks1;
    }
    tablica[indeks3] = (int*)realloc(tablica[indeks3], od * sizeof(int*));
    for (int i = 0; i < ile; i++) {
        tablica[indeks3][od - i - 1] = tablica[indeks1][dlugosci[indeks1] - i - 1] - tablica[indeks2][dlugosci[indeks2] - i - 1];
    }
    for (int i = 0; i < (od - ile); i++) {
        tablica[indeks3][i] = tablica[dluzszy][i];
    }

    dlugosci[indeks3] = od;
    przerobod(tablica, dlugosci, indeks3);

}

void przerobod(int* tablica[], int dlugosci[], int indeks) {

    for (int i = 0; i < dlugosci[indeks]; i++) {

        if (tablica[indeks][dlugosci[indeks] - 1 - i] < 0) {

            tablica[indeks][dlugosci[indeks] - 1 - i] += 10;
            tablica[indeks][dlugosci[indeks] - 2 - i] -= 1;
        }
    }

    int licznikzer = 0;

    while (tablica[indeks][licznikzer] == 0) {
        licznikzer++;
    }
    for (int i = 0; i < dlugosci[indeks] - licznikzer; i++) {

        tablica[indeks][i] = tablica[indeks][licznikzer + i];
    }
    dlugosci[indeks] -= licznikzer;
    if (dlugosci[indeks] == 0) {
        dlugosci[indeks] = 1;
    }
}

int porownaj(int* tablica[], int dlugosci[], int indeks1, int indeks2) {

    if (dlugosci[indeks1] > dlugosci[indeks2]) {
        return indeks1;


    }
    else if (dlugosci[indeks2] > dlugosci[indeks1]) return indeks2;

    else {

        for (int i = 0; i < dlugosci[indeks1]; i++) {
            if (tablica[indeks1][i] > tablica[indeks2][i]) return indeks1;
            else if (tablica[indeks2][i] > tablica[indeks1][i]) return indeks2;
        }
        return indeks1;
    }
}

void maksimum(int* tablica[], int dlugosci[], int n, char znak[], int sameujemne, int samedodatnie, char symbol, int przekierowanie) {


    if ((sameujemne == 0) || (przekierowanie == 1)) {
        int maxdlugosc = 0;
        int max = 0;
        int indeks = 0;
        int** maksymalne;

        for (int i = 0; i < n; i++) {
            if ((dlugosci[i] > maxdlugosc) && (znak[i] != symbol)) maxdlugosc = dlugosci[i];
        }

        for (int i = 0; i < n; i++) {
            if ((dlugosci[i] == maxdlugosc) && (znak[i] != symbol)) {
                max++;
                indeks = i;
            }
        }
        if (max == 1) {
            if (symbol == '+') cout << "-";
            for (int i = 0; i < dlugosci[indeks]; i++) {
                cout << tablica[indeks][i];
            }
            cout << "\n";
        }
        else {
            maksymalne = (int**)malloc(max * sizeof(int*));
            int licznik = 0;
            int indeksmax = 0;
            for (int i = 0; i < n; i++) {

                if ((dlugosci[i] == maxdlugosc) && (znak[i] != symbol)) {
                    maksymalne[licznik] = (int*)malloc(dlugosci[i] * sizeof(int));
                    for (int j = 0; j < dlugosci[i]; j++) {
                        maksymalne[licznik][j] = tablica[i][j];
                    }
                    licznik++;
                }
            }

            for (int i = 0; i < maxdlugosc; i++) {
                int wystapienia = 0;
                int m = -9;
                for (int j = 0; j < max; j++) {
                    if (maksymalne[j][i] > m) m = maksymalne[j][i];


                }

                for (int u = 0; u < max; u++) {
                    if (maksymalne[u][i] < m) {
                        for (int l = 0; l < maxdlugosc; l++) {
                            maksymalne[u][l] = -1;
                        }
                    }
                }

                for (int j = 0; j < max; j++) {
                    if (maksymalne[j][i] == m) {
                        wystapienia++;
                        indeksmax = j;
                    }
                }
                if (wystapienia == 1) {



                    if (symbol == '+') cout << "-";
                    for (int k = 0; k < maxdlugosc; k++) {
                        cout << maksymalne[indeksmax][k];

                    }
                    cout << "\n";
                    free(maksymalne);
                    break;
                }
            }
        }
    }
    else {
        minimum(tablica, dlugosci, n, znak, sameujemne, samedodatnie, '+', 1);
    }
}

void minimum(int* tablica[], int dlugosci[], int n, char znak[], int sameujemne, int samedodatnie, char symbol, int przekierowanie) {
    if ((samedodatnie == 1) || (przekierowanie == 1)) {
        int mindlugosc = dlugosci[0];
        int min = 0;
        int indeks = 0;
        int** minimalne;
        for (int i = 0; i < n; i++) {
            if ((dlugosci[i] < mindlugosc) && (znak[i] != symbol)) mindlugosc = dlugosci[i];
        }
        for (int i = 0; i < n; i++) {
            if ((dlugosci[i] == mindlugosc) && (znak[i] != symbol)) {
                min++;
                indeks = i;
            }
        }
        if (min == 1) {
            if (symbol == '+') cout << "-";
            for (int i = 0; i < dlugosci[indeks]; i++) {
                cout << tablica[indeks][i];
            }
            cout << "\n";
        }
        else {
            minimalne = (int**)malloc(min * sizeof(int*));
            int indeksmin = 0;
            int licznik = 0;
            for (int i = 0; i < n; i++) {

                if ((dlugosci[i] == mindlugosc)) {
                    minimalne[licznik] = (int*)malloc(dlugosci[i] * sizeof(int));
                    for (int j = 0; j < dlugosci[i]; j++) {
                        minimalne[licznik][j] = tablica[i][j];
                    }
                    licznik++;
                }
            }
            for (int i = 0; i < mindlugosc; i++) {
                int wystapienia = 0;
                int m = 10;
                for (int j = 0; j < min; j++) {
                    if (minimalne[j][i] < m) m = minimalne[j][i];

                }
                for (int u = 0; u < min; u++) {
                    if (minimalne[u][i] > m) {
                        for (int l = 0; l < mindlugosc; l++) {
                            minimalne[u][l] = 10;
                        }
                    }
                }
                for (int j = 0; j < min; j++) {
                    if (minimalne[j][i] == m) {
                        wystapienia++;
                        indeksmin = j;
                    }
                }
                if (wystapienia == 1) {
                    if (symbol == '+') cout << "-";
                    for (int k = 0; k < mindlugosc; k++) {
                        cout << minimalne[indeksmin][k];
                    }
                    free(minimalne);
                    cout << "\n";
                    break;
                }
            }
        }
    }
    else {
        maksimum(tablica, dlugosci, n, znak, sameujemne, samedodatnie, '+', 1);
    }
}

void czysame(char znaki[], int* samedodatnie, int* sameujemne, int n) {
    for (int i = 0; i < n; i++) {
        if (znaki[i] == '+') {
            *sameujemne = 0;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (znaki[i] == '-') {
            *samedodatnie = 0;
            break;
        }
    }
}

void wypisz(int n, char znak[], int dlugosci[], int* tablica[]) {

    for (int i = 0; i < n; i++) {
        if (znak[i] == '-') cout << "-";
        for (int j = 0; j < dlugosci[i]; j++) {
            printf("%d", tablica[i][j]);
        }
        cout << "\n";
    }
}

int potega(int x, int y) {
    int wynik = 1;
    for (int i = 0; i < y; i++) {
        wynik = wynik * x;
    }
    return wynik;
}
