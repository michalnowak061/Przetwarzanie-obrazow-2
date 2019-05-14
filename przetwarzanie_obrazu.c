//
//  przetwarzanie_obrazu.c
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 22.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#include "przetwarzanie_obrazu.h"

//---------------------------------------------------------------------------------------------------------------------
void negatyw(obraz *_obraz){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for(int j = kolor; j < _obraz->piksele_x; j = j + skok){
            _obraz->piksele[i][j] = _obraz->szarosci - _obraz->piksele[i][j];
        }
    }
    
    char komentarz1[50] = " Negatyw ";
    strcat(komentarz1,data());
    dodaj_komentarz(_obraz,komentarz1);
}
//---------------------------------------------------------------------------------------------------------------------
void progowanie(obraz *_obraz,int _prog){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }
    
    assert(_prog >= 0 && _prog <= 100);
    int PROG = (_prog) * (_obraz->szarosci) / 100;
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for (int j = kolor; j < _obraz->piksele_x; j = j + skok){
            if(_obraz->piksele[i][j] <= PROG) _obraz->piksele[i][j] = 0;
            else if(_obraz->piksele[i][j] > PROG) _obraz->piksele[i][j] = _obraz->szarosci;
        }
    }
    
    char komentarz2[50] = " Progowanie ";
    strcat(komentarz2,data());
    dodaj_komentarz(_obraz,komentarz2);
}
//---------------------------------------------------------------------------------------------------------------------
void progowanie_czerni(obraz *_obraz,int _prog){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }
    
    assert(_prog >= 0 && _prog <= 100);
    int PROG = (_prog) * (_obraz->szarosci) / 100;;
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for (int j = kolor; j < _obraz->piksele_x; j = j + skok){
            if(_obraz->piksele[i][j] <= PROG) _obraz->piksele[i][j] = 0;
            else if(_obraz->piksele[i][j] > PROG) _obraz->piksele[i][j] = _obraz->piksele[i][j];
        }
    }
    
    char komentarz3[50] = " Progowanie czerni ";
    strcat(komentarz3,data());
    dodaj_komentarz(_obraz,komentarz3);
}
//---------------------------------------------------------------------------------------------------------------------
void progowanie_bieli(obraz *_obraz, int _prog){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }
    
    assert(_prog >= 0 && _prog <= 100);
    int PROG = (_prog) * (_obraz->szarosci) / 100;
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for (int j = kolor; j < _obraz->piksele_x; j = j + skok){
            if(_obraz->piksele[i][j] <= PROG) _obraz->piksele[i][j] = _obraz->piksele[i][j];
            else if(_obraz->piksele[i][j] > PROG) _obraz->piksele[i][j] = _obraz->szarosci;
        }
    }
    
    char komentarz4[50] = " Progowanie bieli ";
    strcat(komentarz4,data());
    dodaj_komentarz(_obraz,komentarz4);
}
//---------------------------------------------------------------------------------------------------------------------
void korekcja_gamma(obraz *_obraz, float _gamma){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }

    for (int i = 0; i < _obraz->piksele_y; ++i){
        for(int j = kolor; j < _obraz->piksele_x; j = j + skok){
            _obraz->piksele[i][j] = pow((float)_obraz->piksele[i][j] / (float)_obraz->szarosci,1 / _gamma) * (_obraz->szarosci);
        }
    }
    
    char komentarz5[50] = " Korekcja gamma ";
    strcat(komentarz5,data());
    dodaj_komentarz(_obraz,komentarz5);
}
//---------------------------------------------------------------------------------------------------------------------
void zmiana_poziomow(obraz *_obraz, int _czern, int _biel){
    int kolor = 0;  /* r - zaczynamy od 1 piksela i przesuwamy sie o 3 */
    int skok = 1;   /* jesli przetwarzamy wszystkie kolory przesuwamy sie o jeden piksel */
    if(_obraz->kolor[0] == 'r'){
        kolor = 0; skok = 3;
    }
    else if(_obraz->kolor[0] == 'g'){
        kolor = 1; skok = 3;
    }
    else if(_obraz->kolor[0] == 'b'){
        kolor = 2; skok = 3;
    }
    
    assert(_czern >= 0 && _czern <= 100);
    assert(_biel >= 0 && _biel <= 100);
    
    int CZERN = _obraz->szarosci - (( (1 - (float)_czern / 100) ) * (float)_obraz->szarosci ) ;
    int BIEL = _biel * _obraz->szarosci / 100;
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for(int j = kolor; j < _obraz->piksele_x; j = j + skok){
            if(_obraz->piksele[i][j] <= CZERN) _obraz->piksele[i][j] = 0;
            else if(_obraz->piksele[i][j] > CZERN && _obraz->piksele[i][j] < BIEL){
                _obraz->piksele[i][j] = (_obraz->piksele[i][j] - CZERN) * (_obraz->szarosci / (BIEL - CZERN));
            }
            else if(_obraz->piksele[i][j] >= BIEL) _obraz->piksele[i][j] = _obraz->szarosci;
        }
    }
    
    char komentarz6[50] = " Zmiana poziomow ";
    strcat(komentarz6,data());
    dodaj_komentarz(_obraz,komentarz6);
}
//---------------------------------------------------------------------------------------------------------------------
void konturowanie(obraz *_obraz){
    
    if(_obraz->magiczny_numer[1] == '3') konwersja_do_szarosci(_obraz);
    
    for(int i = 0; i < _obraz->piksele_y - 1; ++i){
        for(int j = 0; j < _obraz->piksele_x - 1; ++j){
            _obraz->piksele[i][j] = abs(_obraz->piksele[i+1][j] - _obraz->piksele[i][j])
                                  + abs(_obraz->piksele[i][j+1] - _obraz->piksele[i][j]);
        }
    }
    
    char komentarz7[50] = " Konturowanie ";
    strcat(komentarz7,data());
    dodaj_komentarz(_obraz,komentarz7);
}
//---------------------------------------------------------------------------------------------------------------------
void rozmywanie_poziome(obraz *_obraz){
    for(int i = 1; i < _obraz->piksele_y - 1; ++i){
        for(int j = 0; j < _obraz->piksele_x; ++j){
            _obraz->piksele[i][j] = (_obraz->piksele[i-1][j] + _obraz->piksele[i][j] + _obraz->piksele[i+1][j]) / 3;
        }
    }
    
    char komentarz8[50] = " Rozmywanie poziome ";
    strcat(komentarz8,data());
    dodaj_komentarz(_obraz,komentarz8);
}
//---------------------------------------------------------------------------------------------------------------------
void rozmywanie_pionowe(obraz *_obraz){
    for(int i = 0; i < _obraz->piksele_y; ++i){
        for(int j = 1; j < _obraz->piksele_x - 1; ++j){
            _obraz->piksele[i][j] = (_obraz->piksele[i][j-1] + _obraz->piksele[i][j] + _obraz->piksele[i][j+1]) / 3;
        }
    }
    
    char komentarz9[50] = " Rozmywanie pionowe ";
    strcat(komentarz9,data());
    dodaj_komentarz(_obraz,komentarz9);
}
//---------------------------------------------------------------------------------------------------------------------
void rozciaganie_histogramu(obraz *_obraz){
    int Lmin = _obraz->szarosci; int Lmax = 0;
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for (int j = 0; j < _obraz->piksele_x; ++j){
            if(_obraz->piksele[i][j] > Lmax) Lmax = _obraz->piksele[i][j];
            else if(_obraz->piksele[i][j] < Lmin) Lmin = _obraz->piksele[i][j];
        }
    }
    
    for (int i = 0; i < _obraz->piksele_y; ++i){
        for (int j = 0; j < _obraz->piksele_x; ++j){
            _obraz->piksele[i][j] = (_obraz->piksele[i][j] - Lmin) * (float)((float)_obraz->szarosci / (float)(Lmax - Lmin));
        }
    }
    
    char komentarz10[50] = " Rozciaganie histogramu ";
    strcat(komentarz10,data());
    dodaj_komentarz(_obraz,komentarz10);
}
//---------------------------------------------------------------------------------------------------------------------
