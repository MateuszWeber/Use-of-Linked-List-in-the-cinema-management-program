#include "naglowki.hpp"

extern struct Film *headFilm;
extern struct Sala *headSala;
extern struct Grafik *headGrafik;

//funkcja sprawdzania czy sala jest dostepna w danych godzinach
struct Grafik *SprawdzDostepnosc (string nazwaSali, int dzien, int godzina, int minuta, int czasTrwania)//argumentami jest nazwa sali i czas wyswietlania
{
    struct Grafik *temp = headGrafik;//deklaracja wskaznika na strukture sali i ustawienie na pierwszy element (head).

    int godziny = 0;

    if(czasTrwania >= 60) for (godziny = 1; godziny*60 <= czasTrwania; godziny++);  //liczymy ile godzin trwa seans
    if(godziny>1)godziny--;

    bool zajeta = false;    //ustawiamy na poczatku, że sala jest wolna

    while( temp != NULL)    //sprawdzamy kazdy element w liscie grafikow
    {
        //tutaj sie zaczynaja warunki dostepnosci sali
        if (temp->sala.nazwaSali == nazwaSali)
        {
            if (temp->poczatekSeansu.dzien == dzien )
            {
//rozpoczecie w czasie trwania seansu
                if ( temp->poczatekSeansu.godzina < godzina)
                {
                    if(temp->koniecSeansu.godzina > godzina)
                    {
                        zajeta = true;//znaleziono ze sala jest zajeta
                        break;//konczymy petle while
                    }
                    else if (temp->koniecSeansu.godzina == (godzina))
                    {
                        if(temp->koniecSeansu.minuta >= minuta)
                        {
                            zajeta = true;//znaleziono ze sala jest zajeta
                            break;//konczymy petle while
                        }
                    }
                }
                else if ( temp->poczatekSeansu.godzina == godzina)
                {
                    if( temp->poczatekSeansu.minuta <= minuta)
                    {
                        if(temp->koniecSeansu.godzina > godzina)
                        {
                            zajeta = true;//znaleziono ze sala jest zajeta
                            break;//konczymy petle while
                        }
                        else if (temp->koniecSeansu.godzina == (godzina))
                        {
                            if(temp->koniecSeansu.minuta >= minuta)
                            {
                                zajeta = true;//znaleziono ze sala jest zajeta
                                break;//konczymy petle while
                            }
                        }
                    }
                }
//zakonczenie pomiedzy trwajacym seansem
                if ( temp->poczatekSeansu.godzina < (godzina + godziny))
                {
                    if(temp->koniecSeansu.godzina > (godzina + godziny))
                    {
                        zajeta = true;//znaleziono ze sala jest zajeta
                        break;//konczymy petle while
                    }
                    else if (temp->koniecSeansu.godzina == ((godzina + godziny)))
                    {
                        if(temp->koniecSeansu.minuta >= (czasTrwania-(60*godziny)))
                        {
                            zajeta = true;//znaleziono ze sala jest zajeta
                            break;//konczymy petle while
                        }
                    }
                }
                else if ( temp->poczatekSeansu.godzina == (godzina + godziny))
                {
                    if( temp->poczatekSeansu.minuta <= (czasTrwania-(60*godziny)))
                    {
                        if(temp->koniecSeansu.godzina > (godzina + godziny))
                        {
                            zajeta = true;//znaleziono ze sala jest zajeta
                            break;//konczymy petle while
                        }
                        else if (temp->koniecSeansu.godzina == (godzina + godziny))
                        {
                            if(temp->koniecSeansu.minuta >=  (czasTrwania-(60*godziny)))
                            {
                                zajeta = true;//znaleziono ze sala jest zajeta
                                break;//konczymy petle while
                            }
                        }
                    }
                }
            }
        }
    temp = temp->next;  //przechodzimy do nastepnego elementu listy
    }

    if (zajeta) //napisy jesli sala jest zajeta
    {
        cout << "Sala " << temp->sala.nazwaSali << " jest zajeta." << endl;
        cout << "Projekcja " << temp->film.nazwaFilmu << " trwa od" << endl;
        cout << temp->poczatekSeansu.dzien << " " ;
        cout << " godz: " << temp->poczatekSeansu.godzina << " : " << temp->poczatekSeansu.minuta;
        //cout << " do: " << temp->koniecSeansu.dzien << " " << temp->koniecSeansu.miesiac << " " << temp->koniecSeansu.rok;
        cout << " do godz: " << temp->koniecSeansu.godzina << " : " << temp->koniecSeansu.minuta << endl;

        return temp;    //zwracamy wskaznik na kolidujacy grafik
    }
    temp = NULL;
    return temp;    //zwracamy wskaznik na grafik null
}

//SZUKANIE NJAMNIEJSZEGO WOLNEGO ID
int SprawdzId()
{
	struct Grafik *temp = headGrafik;       //inicjujemy zmienną strukturalną i ustawienie wskaźnika na pierwszą strukturę naszej listy
	int id = 1,i=0;
	if(temp == NULL) return 1;                      //Jeżeli lista jest pusta

        for(id = 1; i == 0; id++,temp = headGrafik)           //szukanie najmniejszego wolnego numeru id
        {
            i=1;
            while(temp != NULL)         //Przejście przez wszysktie elementu listy
            {
                if(id == (temp->ID))
                {
                    i=0;                //jeśli program tu wejdzie wykona się następna pętla for
                }
                temp = temp->next;      //przejście do następnego elementu
            }
        }
    id--;   //pętla for przy wyjściu zwiększyła id o 1. Msimy to odjąć
    return id;  //Zwracamy znelzione najmniejsze id
}

//funkcja tworzaca nowy grafik z przekazanych argumentow
void NowyRepertuar(string nazwaFilmu, string sala, int dzien, int godz, int minuta, int czasTrwania)
{
    //najpierw sprawdzimy, czy ten grafik nie koliduje z innym
    if(SprawdzDostepnosc(sala, dzien, godz, minuta, czasTrwania) != NULL)
    {
        return; //jezeli koliduje to konczymy dzialanie funkcji
    }
    cout << "sprawdzono dostepnosc" << endl;
    struct Grafik *temp = headGrafik;     //inicjujemy zmienną strukturalną i ustawienie wskaźnika na pierwszą strukturę naszej listy
    struct Grafik *nowy = new Grafik;     //inicjujemy zmienną strukturalną

    int iD = SprawdzId();   //szukamy najmniejszego wolnego id dla grafiku

    //wypelniamy strukture grafiku
    nowy->film.nazwaFilmu = nazwaFilmu;
    nowy->film.czasTrwania = czasTrwania;
    nowy->sala.nazwaSali = sala;

    nowy->poczatekSeansu.dzien = dzien;
    nowy->poczatekSeansu.godzina = godz;
    nowy->poczatekSeansu.minuta = minuta;
    nowy->ID = iD;

    //liczymy ilosc godzin
    int ileGodzin = 0;
    if(nowy->film.czasTrwania >= 60) for (ileGodzin = 1; ileGodzin*60 <= nowy->film.czasTrwania; ileGodzin++);
    if(ileGodzin>1)ileGodzin--;

    nowy->koniecSeansu.godzina = nowy->poczatekSeansu.godzina + ileGodzin;

    nowy->koniecSeansu.minuta = nowy->poczatekSeansu.minuta + (nowy->film.czasTrwania - 60*ileGodzin);

    nowy->next = NULL;  //nie ma kolejnego elementu na liscie, dlatego ustawiamy ten wskaznik na null

    if (headGrafik == NULL) //tak jak poprzednio jezeli lista pusta...
    {
        headGrafik = nowy;
        cout << "Utworzony nowy grafik." << endl;
        return;
    }

    while (temp->next != NULL) temp = temp->next;   //przechodzimy do statniego elementu na liscie
    temp->next = nowy;  //ustawiamy wskaznik ostatniego elementu na nasz nowy element

    cout << "Utworzony nowy grafik." << endl;
}

//pobieranie danych wejsciowych z klawiatury, potrzebnych do utwoerzenia nowego grafiku
void InputNowyRepertuar()
{
    string nazwaFilmu, sala;

    struct Film *wybranyFilm = new Film;    //inicjujemy zmienną strukturalną filmu
    struct Sala *wybranaSala = new Sala;    //inicjujemy zmienną strukturalną sali

    int dzien, godz, minuta;

    cout << "Dodawanie grafiku." << endl;
    cout << "Dostepne filmy w naszym kinie:" << endl;

    WyswietlFilmy();    //pokazujemy filmy

    cout << "Najpierw wybierz film." << endl;
    cin >> nazwaFilmu;

    wybranyFilm = SzukajFilmu(nazwaFilmu);  //szuakmy takiego filmu

    if (wybranyFilm == NULL)    //jezeli funkcja zwrocila null
    {
        cout << "Nie mamy takiego filmu w naszych zasobach." << endl;
        return; //konczymy funkcje
    }
    cout << "Wybrany film to: " << wybranyFilm->nazwaFilmu << "Czas trwania: " << wybranyFilm->czasTrwania << endl;

    cout << "Dostepne sale w naszym kinie:" << endl;
    WyswietlSale();//wyswietlamy sale
    cout << "Podaj sale, na ktorej odbedzie sie projekcja filmu." << endl;

    cin >> sala;

    wybranaSala = SzukajSali(sala); //szukamy takiej sali

    if (wybranaSala == NULL)//jezeli funkcja zwrocila null
    {
        cout << "Nie mamy takiej sali w naszych kinach." << endl;
        return;//konczymy funkcje
    }

    cout << "Wybrana sala to: " << wybranaSala->nazwaSali << endl;

    cout << "Podaj date wyswietlania filmu:" << endl;
    /*cout << "Najpierw podaj rok:" << endl;

    while ( !(cin >> rok) || rok < 1500 || rok > 2500)//pobranie liczby
    {
        cout << "Wprowadz normalny rok (1500 - 2500)." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    cout << "Podaj miesiac:" << endl;
    while ( !(cin >> mies) || mies < 1 || mies > 12)//pobranie liczby
    {
        cout << "Wprowadz normalny miesiac (1 - 12)." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }
*/
    cout << "Podaj dzien:" << endl;
    while ( !(cin >> dzien) || dzien < 1 || dzien > 7)//pobranie liczby
    {
        cout << "Wprowadz normalny dzien (1 - 7)." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    cout << "Podaj godzine rozpoczecia seansu:" << endl;
    while ( !(cin >> godz) || godz < 0 || godz > 23)//pobranie liczby
    {
        cout << "Wprowadz normalna godzine (0 - 23)." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    cout << "Podaj minute rozpoczecia seansu:" << endl;
    while ( !(cin >> minuta) || minuta < 0 || minuta > 59)//pobranie liczby
    {
        cout << "Wprowadz normalna minute (0 - 59)." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    NowyRepertuar(nazwaFilmu, sala, dzien, godz, minuta, wybranyFilm->czasTrwania);//wywolujemy funkcje tworzaca nowy grafik z pobranymi argumentami
}

//funkcja wyswietlajaca grafik
void WyswietlRepertuar ()
{
    struct Grafik *temp = headGrafik;   //inicjujemy zmienną strukturalną grafiku i ustawimy ja na head

    cout << "ID: Film: \t sala: \t dzien:\tgodzina:  minuta:  czas trwania:" <<  endl;

    while (temp != NULL)//przechodzimy przez wszystkie elementu listy
    {
        cout << temp->ID << " ";
        cout << temp->film.nazwaFilmu << " \t " << temp->sala.nazwaSali;
        cout << " \t " << temp->poczatekSeansu.dzien << " \t " << temp->poczatekSeansu.godzina << " \t " << temp->poczatekSeansu.minuta;
        cout << " \t " << temp->film.czasTrwania << endl;
        temp = temp->next;
    }
}

void EdytujRepertuar()
{
    struct Grafik *doEdycji = headGrafik;   //inicjujemy zmienną strukturalną grafiku i ustawimy ja na head
    struct Grafik *temp = new Grafik;   //inicjujemy zmienną strukturalną grafiku
    string nazwaFilmu;
    struct Film *wybranyFilm = new Film;    //inicjujemy zmienną strukturalną filmu
    string sala;
    struct Sala *wybranaSala = new Sala;    //inicjujemy zmienną strukturalną sali
    int iD;
    int dzien, godz, minuta;

    cout << "Oto obecny repertuar." << endl;

    WyswietlRepertuar();

    cout << "Podaj numer ID do edycji." << endl;
    while ( !(cin >> iD) || iD < 1 )//pobranie liczby
    {
        cout << "Wprowadz numer ID." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    while ((doEdycji != NULL) && (doEdycji->ID != iD))  //szukamu wybranego id edycji
    {
        doEdycji = doEdycji->next;
    }

    if (doEdycji == NULL)   //nie znaleziono
    {
        cout << "Nie ma takiej edycji." << endl;
        return;
    }
    else//tutaj wchodzimy, jezeli podano wlasciwy numer id do edycji
    {
        int numerMenu;
//mini - menu
        cout << "Co chcesz zmienic?" << endl;

        cout << "1. Zmien film." << endl;
        cout << "2. Zmien sale." << endl;
        cout << "3. Zmien czas projekcji." << endl;
        cout << "4. Anuluj." << endl;

        while ( !(cin >> numerMenu) || numerMenu < 1 || numerMenu > 4)//pobranie liczby
        {
            cout << "Wprowadz numer menu (1 - 4)." << endl;
            cin.clear(); //kasowanie flagi b³êdu strumienia
            cin.sync(); //kasowanie zbêdnych znaków z bufora
        }

        switch (numerMenu)
        {
        case 1:
            cout << "Dostepne filmy w naszym kinie:" << endl;

            WyswietlFilmy();

            cout << "Najpierw wybierz film." << endl;
            cin >> nazwaFilmu;

            wybranyFilm = SzukajFilmu(nazwaFilmu);  //szukanie wybranego filmu czy iistnieje

            if (wybranyFilm == NULL)    //standardowo, tak jak wczesniej, spraedzamu, czy wprowadzono poprawna nazwe
            {
                cout << "Nie mamy takiego filmu w naszych zasobach." << endl;
                return;
            }

            cout << "Wybrany film to: " << wybranyFilm->nazwaFilmu << endl;

            doEdycji->film.nazwaFilmu = wybranyFilm->nazwaFilmu;//zmieniamy nazwe
            break;

        case 2:
            cout << "Dostepne sale w naszym kinie:" << endl;
            WyswietlSale();
            cout << "Podaj sale, na ktorej odbedzie sie projekcja filmu." << endl;

            cin >> sala;

            wybranaSala = SzukajSali(sala);//szukanie wybranej sali czy iistnieje

            if (wybranaSala == NULL) //standardowo, tak jak wczesniej, spraedzamu, czy wprowadzono poprawna nazwe
            {
                cout << "Nie mamy takiej sali w naszych kinach." << endl;
                return;
            }

            cout << "Wybrana sala to: " << wybranaSala->nazwaSali << endl;

            if(wybranaSala->nazwaSali == doEdycji->sala.nazwaSali)//jezeli wprowadzono to samo
            {
                cout << "Nic nie zmieniles." << endl;
            }
            else
            {
                if(SprawdzDostepnosc(wybranaSala->nazwaSali, doEdycji->poczatekSeansu.dzien, doEdycji->poczatekSeansu.godzina, doEdycji->poczatekSeansu.minuta, doEdycji->film.czasTrwania) != NULL)//sprawdzmy dostepnosc sali w tym terminie
                {
                    return;//brak wolnych terminow - koniec
                }
                doEdycji->sala.nazwaSali = wybranaSala->nazwaSali;  //zmieniamy nazwe
            }
            break;

        case 3:

            cout << "Podaj nowy czas wyswietlania filmu:" << endl;
            /*cout << "Najpierw podaj rok:" << endl;

            while ( !(cin >> rok) || rok < 1500 || rok > 2500)//pobranie liczby
            {
                cout << "Wprowadz normalny rok (1500 - 2500)." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }

            cout << "Podaj miesiac:" << endl;
            while ( !(cin >> mies) || mies < 1 || mies > 12)//pobranie liczby
            {
                cout << "Wprowadz normalny miesiac (1 - 12)." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }
*/
            cout << "Podaj dzien:" << endl;
            while ( !(cin >> dzien) || dzien < 1 || dzien > 7)//pobranie liczby
            {
                cout << "Wprowadz normalny dzien (1 - 7)." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }

            cout << "Podaj godzine rozpoczecia seansu:" << endl;
            while ( !(cin >> godz) || godz < 0 || godz > 23)//pobranie liczby
            {
                cout << "Wprowadz normalna godzine (0 - 23)." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }

            cout << "Podaj minute rozpoczecia seansu:" << endl;
            while ( !(cin >> minuta) || minuta < 0 || minuta > 59)//pobranie liczby
            {
                cout << "Wprowadz normalna minute (0 - 59)." << endl;
                cin.clear(); //kasowanie flagi b³êdu strumienia
                cin.sync(); //kasowanie zbêdnych znaków z bufora
            }
//patrzymy czy w tym czasie sala jest wolna
            temp = SprawdzDostepnosc(doEdycji->sala.nazwaSali, dzien, godz, minuta, doEdycji->film.czasTrwania);
//musimy jeszcze sprawdzic czy nasz obecny film sie nie pokrywa, jezeli to jest to samo to zmieniamy czas
            if((temp == NULL) || (temp->film.nazwaFilmu == doEdycji->film.nazwaFilmu))
            {

                doEdycji->poczatekSeansu.dzien = dzien;
                doEdycji->poczatekSeansu.godzina = godz;
                doEdycji->poczatekSeansu.minuta = minuta;
                int ileGodzin = 0;
                if(doEdycji->film.czasTrwania >= 60) for (ileGodzin = 1; ileGodzin*60 <= doEdycji->film.czasTrwania; ileGodzin++);

                doEdycji->koniecSeansu.godzina = doEdycji->poczatekSeansu.godzina + ileGodzin;
                doEdycji->koniecSeansu.minuta = doEdycji->poczatekSeansu.minuta + (doEdycji->film.czasTrwania - 60*ileGodzin);

            }

            break;
        }
    }
}

void UsunRepertuar()
{
    struct Grafik *doUsuniecia = headGrafik;    //inicjujemy zmienną strukturalną grafiku i ustawimy ja na head
    struct Grafik *poprzedni = new Grafik;  //inicjujemy zmienną strukturalną grafiku
    int iD;

    cout << "Oto obecny repertuar." << endl;
    WyswietlRepertuar();                            //pokazujemy repertuar
    cout << "Podaj numer ID do usuniecia." << endl;
    while ( !(cin >> iD) || iD < 1 )//pobranie liczby
    {
        cout << "Wprowadz numer ID." << endl;
        cin.clear(); //kasowanie flagi b³êdu strumienia
        cin.sync(); //kasowanie zbêdnych znaków z bufora
    }

    while ((doUsuniecia != NULL) && (doUsuniecia->ID != iD))    //szukamu wybranego id
    {
        poprzedni = doUsuniecia;
        doUsuniecia = doUsuniecia->next;
    }

    if (doUsuniecia == NULL)//nie ma taakiego id
    {
        cout << "Nie ma takiego usuwania." << endl;
        return;
    }
    //algorytm usuwania elementu z listy, dobrze opisany na http://eduinf.waw.pl/inf/alg/001_search/0086.php
    else//znaleziono takie id
    {
        if(doUsuniecia == headGrafik)
        {
            if(headGrafik->next!=NULL)
            {
                headGrafik = headGrafik->next;
            }
            else
            {
                headGrafik = NULL;
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

        cout<<"Usunieto grafik " <<"."<<endl;
    }
}

//funkcja wyswietlania seansow wybranego filmu
void Seanse (string nazwaFilmu)
{
    struct Grafik *temp = headGrafik;   //bedziemy szukali w grafikach

    bool istnieje = false;

    cout << "Film " << nazwaFilmu << " jest na nastepujacych seansach:" << endl;

    cout << "Sala: \t dzien: \t godzina: \t minuta: \t czas trwania:" << endl;

    while (temp != NULL)    //sprawdzamy hazdy grafik
    {
        if (temp->film.nazwaFilmu == nazwaFilmu)//jezli w grafiku znajdziemy nazwe filmu do wyswietlamy dane tego grafiku
        {
cout << temp->sala.nazwaSali << "\t" << temp->poczatekSeansu.dzien << "\t" << temp->poczatekSeansu.godzina << "\t" << temp->poczatekSeansu.minuta << "\t" << temp->film.czasTrwania << endl;

        istnieje = true;
        }
        temp = temp->next;
    }

    if (!istnieje) cout << "Nie ma takiego filmu w naszej bazie." << endl;
}
