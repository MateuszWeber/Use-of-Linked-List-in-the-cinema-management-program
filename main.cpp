#include "naglowki.hpp"

struct Film *headFilm = NULL;
struct Sala *headSala = NULL;
struct Grafik *headGrafik = NULL;

int main ()
{
    int wyborMenu;
    bool petla = true;

    while (petla)   //dopóki zmienna logiczna "petla" bedzie prawdziwa wykonujemy ta petle.
    {
        string nazwa;
        int czas;

        system ( "cls" );       //czyszczenie ekranu konsoli
        menuGlowne();           //wywolanie funkcji z menu glównym

        while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 6)//pobranie liczby
        {
            cout << "Wprowadz numer menu." << endl;
            cin.clear(); //kasowanie flagi b³êdu strumienia
            cin.sync(); //kasowanie zbêdnych znaków z bufora
        }

        switch (wyborMenu)              //wiadomo - instrukcja switch - case, standard w menu
        {
//Podmenu filmu
            case 1:
                system( "cls" );        //czyszczenie ekranu konsoli
                menuFilmy();          //wywo³anie funkcji z menu filmu
                while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 5 )//pobranie liczby
                {
                    cout << "Wprowadz numer menu." << endl;
                    cin.clear(); //kasowanie flagi b³êdu strumienia
                    cin.sync(); //kasowanie zbêdnych znaków z bufora
                }
                switch (wyborMenu)      //wiadomo - instrukcja switch - case, standard w menu
                {
                    case 1:
                        cout << "Wybrales dodanie nowego filmu." << endl;
                        cout << "Podaj nazwe filmu." << endl;

                        cin >> nazwa;

                        cout << "Podaj czas trwania filmu w minutach." << endl;

                        while ( !(cin >> czas) || czas < 1 || czas > 500 )//pobranie liczby
                        {
                            cout << "Wprowadz czas trwania filmu w minutach (1 - 500)." << endl;
                            cin.clear(); //kasowanie flagi bledu strumienia
                            cin.sync(); //kasowanie zbêdnych znaków z bufora
                        }

                        NowyFilm(nazwa, czas);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;

                        getch();
                    break;

                    case 2:
                        cout << "Wybrales usuniecie filmu z naszej bazy." << endl;

                        WyswietlFilmy();

                        cout << "Podaj nazwe filmu." << endl;

                        cin >> nazwa;

                        UsunFilm (nazwa);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;

                        getch();
                    break;

                    case 3:
                        cout << "Wybrales edycje filmu w naszej bazie." << endl;

                        WyswietlFilmy();

                        cout << "Podaj nazwe filmu." << endl;

                        cin >> nazwa;

                        EdytujFilm (nazwa);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 4:
                        cout << "Wybrales wyswietlenie filmow z naszej bazy." << endl;

                        WyswietlFilmy();

                        cout << "Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 5:
                        system( "cls" );        //powrót do menu g³ównego i wyczyszczenie ekranu konsoli
                    break;
                }
            break;
//podmenu sale
            case 2:
                system( "cls" );
                menuSale();
                while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 5 )//pobranie liczby
                {
                    cout << "Wprowadz numer menu." << endl;
                    cin.clear(); //kasowanie flagi bledu strumienia
                    cin.sync(); //kasowanie zbêdnych znaków z bufora
                }
                switch (wyborMenu)
                {
                    case 1:
                        cout << "Wybrales dodanie nowej sali." << endl;
                        cout << "Podaj nazwe sali." << endl;

                        cin >> nazwa;

                        NowaSala(nazwa);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 2:
                        cout << "Wybrales usuniecie sali z naszego kina." << endl;

                        WyswietlSale();

                        cout << "Podaj nazwe sali." << endl;

                        cin >> nazwa;

                        UsunSale (nazwa);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;

                        getch();
                    break;

                    case 3:
                        cout << "Wybrales edycje sali w naszym kinie." << endl;

                        WyswietlSale();

                        cout << "Podaj nazwe sali." << endl;

                        cin >> nazwa;

                        EdytujSale (nazwa);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 4:
                        cout << "Wybrales wyswietlenie naszych sal." << endl;

                        WyswietlSale();

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 5:
                        system( "cls" );
                    break;
                }
            break;
//podmenu repertuar
            case 3:
                system( "cls" );
                menuRepertuar();
                while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 5 )//pobranie liczby
                {
                    cout << "Wprowadz numer menu." << endl;
                    cin.clear(); //kasowanie flagi b³êdu strumienia
                    cin.sync(); //kasowanie zbêdnych znaków z bufora
                }
                switch (wyborMenu)
                {
                    case 1:
                        cout << "Wybrales dodanie nowego repertuaru." << endl;

                        InputNowyRepertuar();

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 2:

                        cout << "Wybrales usuniecie repertuaru." << endl;

                        UsunRepertuar();

                        cout << "Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 3:
                        cout << "Wybrales edycje repertuaru." << endl;

                        EdytujRepertuar();

                        cout << "Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 4:
                        cout << "Wybrales wyswietlenie repertuaru." << endl;

                        WyswietlRepertuar();

                        cout << "Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 5:
                        system( "cls" );
                    break;
                }
            break;
//podmenu pliki
            case 4:
                system( "cls" );
                menuPliki();
                while ( !(cin >> wyborMenu) || wyborMenu < 1 || wyborMenu > 7 )//pobranie liczby
                {
                    cout << "Wprowadz numer menu." << endl;
                    cin.clear(); //kasowanie flagi b³êdu strumienia
                    cin.sync(); //kasowanie zbêdnych znaków z bufora
                }
                switch(wyborMenu)
               {
                    case 1:
                        cout << "Wybrales zapisanie bazy filmow do pliku." << endl;

                        DoPliku (true);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 2:
                        cout << "Wybrales zapisanie bazy sal do pliku." << endl;

                        DoPliku (false);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 3:
                        cout << "Wybrales zapisanie repertuaru do pliku." << endl;

                        ZapisRepertuaru();

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 4:
                        cout << "Wybrales wczytanie bazy filmow z pliku." << endl;

                        ZPliku(true);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 5:
                        cout << "Wybrales wczytanie bazy sal z pliku." << endl;

                        ZPliku(false);

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 6:
                        cout << "Wybrales wczytanie grafiku z pliku." << endl;

                        OdczytRepertuaru();

                        cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;
                        getch();
                    break;

                    case 7:
                        system( "cls" );
                    break;
               }

            break;

            case 5:
                system( "cls" );

                cout << "Wybrales zarzadzenie seansami." << endl;

                WyswietlFilmy();

                cout << "Podaj nazwe filmu, ktory chcesz sprawdzic." << endl;
                cin >> nazwa;

                Seanse (nazwa);

                cout<<"Wcisnij dowolny przycisk, aby kontynuowac."<<endl;

                getch();

            break;

            case 6:
                system( "cls" );
                cout<<"Konczenie pracy"<<endl;
                petla = false;
            break;
        }
    }
    return 0;
}
