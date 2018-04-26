#include "naglowki.hpp"

extern struct Film *headFilm;
extern struct Sala *headSala;
extern struct Grafik *headGrafik;

//odczytujemy dane grafiku z pliku
void OdczytRepertuaru()
{
    string buf;
    string nazwaFilmu,sala;
    int dzien, godzina, minuta, czasTrwania;

    fstream plik;

    plik.open( "repertuar_in.txt", ios::in);  //otwarcie pliku

    if( plik.good() == true )//sprawdzenie, cczy plik zostal otwarty
    {
        cout << "Odczytuje dane z pliku repertuar_in.txt!" <<endl;
        plik>>buf>>buf>>buf>>buf>>buf>>buf;       //odczyt pierwszej linii z pliku
        while(plik.good())      //dopoki sa dane w pliku
        {
            plik>>nazwaFilmu>>sala>>dzien>>godzina>>minuta>>czasTrwania;   //odczytanie danych i zapis do zmiennych pomocniczych
            NowyRepertuar(nazwaFilmu, sala, dzien, godzina, minuta, czasTrwania);       //wtwolanie funkcji tworzacej
        }
        cout<<"Odczytano wszystkie dane."<<endl;
        plik.close();
    }
    else cout << "Nie moge otworzyc pliku repertuar_in.txt do odczytu!" <<endl;
}

//odczytujemy dane dla sali i filmu z pliku
void ZPliku(bool filmsala)  //zakladamy, ze argument dla filmu jest true, a dla sali false
{
    string buf;
    string nazwa;

    int dlugoscFilmu;

    fstream plik;

    if(filmsala) plik.open( "filmy_dane_wejsciowe.txt", ios::in);  //otwarcie pliku
    else plik.open( "sale_dane_wejsciowe.txt", ios::in);

    if( plik.good() == true )//sprawdzenie, cczy plik zostal otwarty
    {
        cout << "Odczytuje dane z pliku filmy_dane_wejsciowe.txt!" << endl;

        if(filmsala) plik>>buf>>buf;       //odczyt pierwszej linii z pliku
        else plik>>buf;

        while(plik.good())      //dopoki sa dane w pliku
        {
            if(filmsala)
            {
                plik >> nazwa >> dlugoscFilmu;       //odczytanie danych i zapis do zmiennych pomocniczych
                NowyFilm (nazwa, dlugoscFilmu);       //wtwolanie funkcji tworzacej film
            }
            else
            {
                plik >> nazwa;
                NowaSala (nazwa);
            }

        }

        cout<<"Odczytano wszystkie dane." << endl;
        plik.close();
    }
    else cout << "Nie moge otworzyc pliku do odczytu!" << endl;
}

//zapisujemy dane dla sali i filmu do pliku
void DoPliku (bool filmsala)     //zakladamy, ze argument dla filmu jest true, a dla sali false
{
    struct Film *tempFilm = headFilm;
    struct Sala *tempSala = headSala;

    fstream plik;

    if(filmsala) plik.open( "filmy_dane_wyjsciowe.txt", ios::out);  //otwarcie pliku
    else plik.open( "sale_dane_wyjsciowe.txt", ios::out);

    if( plik.good() == true )   //sprawdzenie, cczy plik zostal otwarty
    {
        cout << "Zapisuje dane do pliku." << endl;

        if(filmsala) plik << "Tytul:\tCzas trwania:" << endl;       //zapianie pierwszej linii w pliku
        else plik << "Nazwa:" << endl;

        if(filmsala)
        {
            while(tempFilm != NULL) //przejscie przez wszystkie elementy listy
            {
                plik << tempFilm->nazwaFilmu << " \t " << tempFilm->czasTrwania << endl;       //zapianie pierwszej linii w pliku
                tempFilm = tempFilm->next;  //nastepny element
            }
        }
        else
        {
            while(tempSala != NULL) //przejscie przez wszystkie elementy listy
            {
                plik << tempSala->nazwaSali << endl;
                tempSala = tempSala->next;  //nastepny element
            }
        }
        cout<<"Zapisano wszystkie dane." << endl;
        plik.close();
    }
    else cout << "Nie moge otworzyc pliku do zapisu!" <<endl;
}

//zapisujemy repertuaru do pliku
void ZapisRepertuaru()
{
    struct Grafik *temp = headGrafik;

    fstream plik;

    plik.open( "repertuar_out.txt", ios::out);

    if( plik.good() == true )
    {
        cout << "Zapisuje dane do pliku repertuar_out.txt!" <<endl;

        plik << "Film: \t sala: \t dzien:\t godzina:  minuta:  czas trwania:" <<  endl;

        while(temp != NULL)
        {
            plik<<temp->film.nazwaFilmu<<"\t"<<temp->sala.nazwaSali<<"\t"<<temp->poczatekSeansu.dzien<<"\t"<<temp->poczatekSeansu.godzina;
            plik <<"\t"<<temp->poczatekSeansu.minuta << "\t" <<temp->film.czasTrwania << endl;
            temp = temp->next;
        }
        cout<<"Zapisano wszystkie dane." << endl;
        plik.close();
    }
    else cout << "Nie moge otworzyc pliku repertuar_out.txt do zapisu!" <<endl;
}

