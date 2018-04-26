#include "naglowki.hpp"

extern struct Film *headFilm;
extern struct Sala *headSala;
extern struct Grafik *headGrafik;

//Funkcja tworzaca nowy film
void NowyFilm (string nazwa, int dlugosc)   //w argumentach przekazujemy nazwe filmu i czas twrania
{
    struct Film *temp = headFilm;   //deklaracja wskaznika na strukture Filmu i ustawienie na pierwszy element (head).
    struct Film *nowy = new Film;   //deklaracja wskaznika na strukture Filmu

    nowy->nazwaFilmu = nazwa;   //wypelniamy strukture filmu
    nowy->czasTrwania = dlugosc;     //wypelniamy strukture filmu
    nowy->next = NULL;   //dodajemy na komniec naszej listy, wiec nie ma kolejnego elementu, dlatego ustawiamy go jako null

    if (headFilm == NULL)   //jezeli head jest null, to oznacza to, ze lista jest pusta, wiec ustawimy jako head nasz element
    {
        headFilm = nowy;
        cout << "Utworzony nowy film " << nazwa << ". Czas projekcji filmu wynosi: " << dlugosc << "min." << endl;
        return; //zakonczenie funkcji
    }

    while (temp->next != NULL) temp = temp->next;   //przechodzimy przez koeljne elementy az dojdziemy do sdtatniego
    temp->next = nowy;  //ostatni element biezacej listy musi wskazywac na element nowo utworzony

    cout << "Utworzony nowy film " << nazwa << ". Czas projekcji filmu wynosi: " << dlugosc << "min." << endl;
}

//Funkcja usuwajaca film
void UsunFilm (string nazwa)     //w argumentach przekazujemy nazwe filmu, ktory chcemy usunac
{
    struct Film *doUsuniecia = headFilm;    //deklaracja wskaznika na strukture Filmu i ustawienie na pierwszy element (head).
    struct Film *poprzedni = new Film;      //deklaracja wskaznika na strukture Filmu

    while ((doUsuniecia != NULL) && (doUsuniecia->nazwaFilmu != nazwa)) //szukamy elementu do usuniêcia sprawdzmy wszystkie elementy listy po kolei
    {
        poprzedni = doUsuniecia;    //w algotytmie usuwania musimy pamietac element poprzedzajacy ten usuwany
        doUsuniecia = doUsuniecia->next;    //przejœcie do nastepnego elementu listy
    }
//doUsuniecia przyjmuje null, jezeli nie ma filmu o szukanym tytule
    if (doUsuniecia == NULL) cout << "Nie ma takiego filmu w naszej bazie danych." << endl;

    //algorytm usuwania elementu z listy, dobrze opisany na http://eduinf.waw.pl/inf/alg/001_search/0086.php
    else
    {
        if(doUsuniecia == headFilm)
        {
            if(headFilm->next!=NULL)
            {
                headFilm = headFilm->next;
            }
            else
            {
                headFilm = NULL;
            }

            free(doUsuniecia);
        }
        else if(doUsuniecia->next == NULL)
		{
		    poprzedni->next=NULL;

		    free(doUsuniecia);//zwolnienie pamiêci
		}
        else if(doUsuniecia != NULL)
        {
            poprzedni->next = doUsuniecia->next;
            free(doUsuniecia);  //zwolnienie pamiêci usuniêtego audiobooka
        }

        cout<<"Usunieto film "<<nazwa<<"."<<endl;

    }
}

//Funkcja usuwajaca film
void EdytujFilm (string nazwa)//w argumentach przekazujemy nazwe filmu, ktory chcemy usunac
{
    struct Film *doEdycji = headFilm;   //deklaracja wskaznika na strukture Filmu i ustawienie na pierwszy element (head).

    int wyborMenu;
    string nowaNazwa;
    int nowyCzas;

    while((doEdycji != NULL) && (doEdycji->nazwaFilmu!=nazwa) )//szukamy elementu do usuniêcia sprawdzmy wszystkie elementy listy po kolei
    {
        doEdycji = doEdycji->next;      //przejœcie do nastêpnego
    }
//doEdycji przyjmuje null, jezeli nie ma filmu o szukanym tytule
    if (doEdycji == NULL) cout << "Nie ma takiego filmu w naszej bazie danych." << endl;
    else
    {
        cout << "Czy chcesz zmienic tytul filmu?" << endl;
        cout << "1: Tak." << endl;
        cout << "2: Nie." << endl;

        while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 2)//pobranie liczby
        {
            cout << "Wprowadz numer menu." << endl;
            cin.clear(); //kasowanie flagi b³êdu strumienia
            cin.sync(); //kasowanie zbêdnych znaków z bufora
        }

        if (wyborMenu == 1)
        {
            cout << "Podaj nowa nazwe filmu." << endl;
            cin >> nowaNazwa;
            doEdycji->nazwaFilmu = nowaNazwa;   //pobieramy nowa nazwe i zapisujemy ja w naszym elemencie listy
        }

        cout << "Czy chcesz zmienic czas trwania filmu?" << endl;
        cout << "1: Tak." << endl;
        cout << "2: Nie." << endl;

        while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 2)//pobranie liczby
        {
            cout << "Wprowadz numer menu." << endl;
            cin.clear(); //kasowanie flagi b³êdu strumienia
            cin.sync(); //kasowanie zbêdnych znaków z bufora
        }

        if (wyborMenu == 1)
        {
            cout << "Podaj nowy czas trwania filmu w minutach." << endl;
            while ( !(cin >> nowyCzas) || nowyCzas < 1 )//pobranie liczby
            {
                cout << "Wprowadz czas trwania filmu w minutach." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }
            doEdycji->czasTrwania = nowyCzas;   //pobieramy nowy czas i zapisujemy w naszym elemencie listy
        }
    }
}

//Funkcja wyswietlacaca filmy
void WyswietlFilmy()
{
    struct Film *temp = headFilm;   //deklaracja wskaznika na strukture Filmu i ustawienie na pierwszy element (head).

    cout << "Nazwa filmu:\t" << "Czas trwania filmu:" << endl;

    while (temp != NULL)     //przechodzimy przezwszystkie elementy naszej listy i wypisujemy dane
    {
        cout << temp->nazwaFilmu << "\t" << temp->czasTrwania << endl;
        temp = temp->next;  //przjescie do nastepnego elementu
    }
}

//Funkcja szukania filmu o okreslonej nazwie
struct Film *SzukajFilmu (string nazwa)//w argumentach przekazujemy nazwe filmu
{
    struct Film *temp = headFilm;    //deklaracja wskaznika na strukture filmu i ustawienie na pierwszy element (head).

    while (temp != NULL)//przechodzimy przezwszystkie elementy naszej listy
    {
        if (temp->nazwaFilmu == nazwa) return temp; //jezeli znajdziemy element o takiej nazwie to konczymy dzilanie
        temp = temp->next;  //funkcji zwracajac wskaznik na ta strukture, w przeciwnym wypadku przechodzimy do kolejnego elementu listy
    }
    return temp;    // jezeli doszliscmy do konca listy i nie znalezliscmy szukanego elementu to zwracamy go (tu zawasze bedzie null)
}

