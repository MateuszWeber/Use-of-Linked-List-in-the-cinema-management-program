#include "naglowki.hpp"

//extern struct Film *headFilm;
extern struct Sala *headSala;
//extern struct Grafik *headGrafik;

//Funkcja tworzaca nowa sale
void NowaSala (string nazwa)    //w argumentach przekazujemy nazwe sali, jaka chcemy usunac
{
    struct Sala *temp = headSala;   //deklaracja wskaznika na strukture sal i ustawienie na pierwszy element (head).
    struct Sala *nowy = new Sala;    //deklaracja wskaznika na strukture sal

    nowy->nazwaSali = nazwa;    //wypelniamy strukture
    nowy->next = NULL;  //dodajemy na komniec naszej listy, wiec nie ma kolejnego elementu, dlatego ustawiamy go jako null

    if (headSala == NULL)   //jezeli head jest null, to oznacza to, ze lista jest pusta, wiec ustawimy jako head nasz element
    {
        headSala = nowy;
        cout << "Utworzony nowa sale " << nazwa << "." << endl;
        return; //zakonczenie funkcji
    }

    while (temp->next != NULL) temp = temp->next;   //przechodzimy przez koeljne elementy az dojdziemy do sdtatniego
    temp->next = nowy;   //ostatni element biezacej listy musi wskazywac na element nowo utworzony

    cout << "Utworzony nowa sale " << nazwa << "." << endl;
}

//Funkcja usuwajaca sale
void UsunSale (string nazwa)
{
    struct Sala *doUsuniecia = headSala;    //deklaracja wskaznika na strukture sal i ustawienie na pierwszy element (head).
    struct Sala *poprzedni = new Sala;       //deklaracja wskaznika na strukture sal

    while ((doUsuniecia != NULL) && (doUsuniecia->nazwaSali != nazwa))  //szukamy elementu do usuniêcia sprawdzmy wszystkie elementy listy po kolei
    {
        poprzedni = doUsuniecia;    //w algotytmie usuwania musimy pamietac element poprzedzajacy ten usuwany
        doUsuniecia = doUsuniecia->next;    //przejœcie do nastepnego elementu listy
    }
//doUsuniecia przyjmuje null, jezeli nie ma sali o szukanej nazwie
    if (doUsuniecia == NULL) cout << "Nie ma takiej sali w naszym kinie." << endl;
    //algorytm usuwania elementu z listy, dobrze opisany na http://eduinf.waw.pl/inf/alg/001_search/0086.php
    else
    {
        if(doUsuniecia == headSala)
        {
            if(headSala->next!=NULL)
            {
                headSala = headSala->next;
            }
            else
            {
                headSala = NULL;
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
void EdytujSale (string nazwa)//w argumentach przekazujemy nazwe sali, ktory chcemy edytowac
{
    struct Sala *doEdycji = headSala;    //deklaracja wskaznika na strukture sal i ustawienie na pierwszy element (head).
    int wyborMenu;
    string nowaNazwa;

    while((doEdycji != NULL) && (doEdycji->nazwaSali!=nazwa) )//szukamy elementu do usuniêcia sprawdzmy wszystkie elementy listy po kolei
    {
        doEdycji = doEdycji->next;      //przejœcie do nastêpnego
    }
//doEdycji przyjmuje null, jezeli nie ma sali o szukanej nazwie
    if (doEdycji == NULL) cout << "Nie ma takiej sali w naszym kinie." << endl;
    else    //jezeli tutaj wejdziemy to wiemy, ze taki element znajduje sie na liscie
    {
        cout << "Czy chcesz zmienic nazwe sali?" << endl;
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
            cout << "Podaj nowa nazwe sali." << endl;
            cin >> nowaNazwa;   //pobieramy nawa nazwe
            doEdycji->nazwaSali = nowaNazwa;    // i zapisujemy ja w elemencie listy
        }
    }
}

//Funkcja wyswietlacaca filmy
void WyswietlSale ()
{
    struct Sala *temp = headSala;  //deklaracja wskaznika na strukture sal i ustawienie na pierwszy element (head).

    cout << "Nazwa sali:" << endl;

    while (temp != NULL)     //przechodzimy przezwszystkie elementy naszej listy i wypisujemy dane
    {
        cout << temp->nazwaSali <<  endl;
        temp = temp->next;  //przjescie do nastepnego elementu
    }
}

//Funkcja szukania sali o okreslonej nazwie
struct Sala *SzukajSali (string nazwa)//w argumentach przekazujemy nazwe sali
{
    struct Sala *temp = headSala; //deklaracja wskaznika na strukture sali i ustawienie na pierwszy element (head).

    while (temp != NULL)//przechodzimy przezwszystkie elementy naszej listy
    {
        if (temp->nazwaSali == nazwa) return temp;//jezeli znajdziemy element o takiej nazwie to konczymy dzilanie
        temp = temp->next;//funkcji zwracajac wskaznik na ta strukture, w przeciwnym wypadku przechodzimy do kolejnego elementu listy
    }
    return temp;// jezeli doszliscmy do konca listy i nie znalezliscmy szukanego elementu to zwracamy go (tu zawasze bedzie null)
}
