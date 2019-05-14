//
//  obsluga_obrazu.h
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 22.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#ifndef obsluga_obrazu_h
#define obsluga_obrazu_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

typedef struct{
    char magiczny_numer[2];                 // <- informacje o typie obrazu
    char komentarze[DL_LINII][DL_LINII];    // <- komentarze
    int wymx, wymy;                         // <- wymiary obrazu
    int szarosci;                           // <- maksymalny odcien szarosci
    int piksele_x, piksele_y;               // <- wymiary tablicy przechowujacej piksele
    int **piksele;                          // <- tablica zawierajaca piksele
    char kolor[1];                          // <- jaki kolor ma byc przetwarzany
}obraz;

void wyzeruj_obraz(obraz *_obraz);

int czytaj(FILE *_plik,obraz *_obraz);
void wyswietl(char *_nazwa_pliku);
int zapisz(FILE *_plik,obraz *_obraz);
void dodaj_komentarz(obraz *_obraz,char *_komentarz);
char *data(void);
void konwersja_do_szarosci(obraz *_obraz);
void wybierz_kolor(obraz *_obraz,char *_kolor);

/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2013 ZPCiR */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/

#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

/* strukura do zapamietywania opcji podanych w wywolaniu programu */
typedef struct {
    /* uchwyty do pliku wej. i wyj. */
    FILE *plik_we, *plik_wy;
    char *nazwa_pliku_we, *nazwa_pliku_wy;
    /* opcje */
    int negatyw,progowanie,progowanie_czerni,progowanie_bieli,
        korekcja_gamma,zmiana_poziomow,konturowanie,rozmywanie_poziome,
        rozmywanie_pionowe,rozciaganie_histogramu,wyswietlenie,zapisz,czytaj,
        filtr_usredniajacy,filtr_usredniajacy_ze_wzmocnieniem,gradient_robertsa,
        pozioma_maska_prewitta,maska_sobela,maska_wykrywajaca_narozniki,laplasjan;
    /* argumenty opcji */
    int w_progu,w_progu_czerni,w_progu_bieli,w_czerni,w_bieli;
    float w_gamma;
    char filtr;
} w_opcje;

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/

void wyzeruj_opcje(w_opcje * wybor);

/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*    poprawnie wystapily w linii wywolania programu,                   */
/*    pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;       */
/*    zwraca wartosc W_OK, gdy wywolanie bylo poprawne                  */
/*    lub kod bledu zdefiniowany stalymi B_* (<0)                       */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor);

#endif /* obsluga_obrazu_h */
