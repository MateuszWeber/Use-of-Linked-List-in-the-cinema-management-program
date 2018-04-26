#ifndef NAGLOWKI_HPP_INCLUDED
#define NAGLOWKI_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Data         //STRUKTURA DO DATY
{
    int dzien;
    int godzina;
    int minuta;
    /*int miesiac;
    int rok;
    */
};

struct Film //struktura filmu
{
    string nazwaFilmu;
    int czasTrwania;
    struct Film *next;  //wskaŸnik na nastepny element listy filomow
};

struct Sala //struktura sali
{
    string nazwaSali;
    struct Sala *next;  //wskaŸnik na nastepny element listy sal
};

struct Grafik   //struktura grafiku
{
    int ID;
    struct Data poczatekSeansu;
    struct Data koniecSeansu;
    struct Film film;
    struct Sala sala;
    struct Grafik *next;    //wskaŸnik na nastepny element listy gafikow
};

void NowyFilm (string nazwa, int dlugosc);
void UsunFilm (string nazwa);
void EdytujFilm (string nazwa);
void WyswietlFilmy();
struct Film *SzukajFilmu (string nazwa);

void NowaSala (string nazwa);
void UsunSale (string nazwa);
void EdytujSale (string nazwa);
void WyswietlSale ();
struct Sala *SzukajSali (string nazwa);

struct Grafik *SprawdzDostepnosc (string nazwaSali, int dzien, int godzina, int minuta, int czasTrwania);
int SprawdzId();
void NowyRepertuar(string nazwaFilmu, string sala, int dzien, int godz, int minuta, int czasTrwania);
void InputNowyRepertuar();
void WyswietlRepertuar ();
void EdytujRepertuar();
void UsunRepertuar();

void ZPliku(bool filmsala);
void DoPliku (bool filmsala);
void OdczytRepertuaru();
void ZapisRepertuaru();
void menuGlowne ();
void menuFilmy ();
void menuSale ();
void menuRepertuar ();
void menuPliki ();
void Seanse (string nazwaFilmu);

#endif // NAGLOWKI_HPP_INCLUDED
