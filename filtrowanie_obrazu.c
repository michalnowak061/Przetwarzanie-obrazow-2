//
//  filtrowanie_obrazu.c
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 23.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#include "filtrowanie_obrazu.h"

//--------------------------------------------------------------------------------------------------
void splot(obraz *_obraz, int _maska[3][3]){
    int bitmapa[_obraz->piksele_y][_obraz->piksele_x]; // <- tymczasowa bitmapa do przechowania pikseli po splocie
    
    //wykonanie splotu maski z obrazem
    for(int i = 1; i < _obraz->piksele_y - 1; ++i){
        for(int j = 1; j < _obraz->piksele_x - 1; ++j){
            bitmapa[i][j] = (_maska[0][0] * _obraz->piksele[i-1][j-1])
                          + (_maska[0][1] * _obraz->piksele[i-1][j])
                          + (_maska[0][2] * _obraz->piksele[i-1][j+1])
                          + (_maska[1][0] * _obraz->piksele[i][j-1])
                          + (_maska[1][1] * _obraz->piksele[i][j])
                          + (_maska[1][2] * _obraz->piksele[i][j+1])
                          + (_maska[2][0] * _obraz->piksele[i+1][j-1])
                          + (_maska[2][1] * _obraz->piksele[i+1][j])
                          + (_maska[2][2] * _obraz->piksele[i+1][j+1]);
        }
    }
    //przekopiowanie zawartosci bitmapy do obrazu
    for(int i = 1; i < _obraz->piksele_y - 1; ++i){
        for(int j = 1; j < _obraz->piksele_x - 1; ++j){
            _obraz->piksele[i][j] = bitmapa[i][j];
        }
    }
    //sprawdzenie czy wszystkie wspolczynniki maski sa dodatnie
    int dodatnie = 1;
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(_maska[i][j] < 0){
                dodatnie = 0; break;
            }
        }
    }
    //normalizacja
    int Lmin = 255; int Lmax = 0;
    
    switch(dodatnie){
        //normalizacja dla dodatnich i ujemnych wspolczynnikow maski
        case 0:
            for (int i = 1; i < _obraz->piksele_y - 1; ++i){
                for (int j = 1; j < _obraz->piksele_x - 1; ++j){
                    if(_obraz->piksele[i][j] > Lmax) Lmax = _obraz->piksele[i][j];
                    else if(_obraz->piksele[i][j] < Lmin) Lmin = _obraz->piksele[i][j];
                }
            }
            
            for(int i = 1; i < _obraz->piksele_y - 1; ++i){
                for(int j = 1; j < _obraz->piksele_x - 1; ++j){
                    _obraz->piksele[i][j] = ( (float)(_obraz->piksele[i][j] - Lmin) / (float)(Lmax - Lmin) ) * 255;
                }
            }
            break;
        //normalizacja dla dodatnich wspolczynnikow maski
        case 1:
            for(int i = 1; i < _obraz->piksele_y - 1; ++i){
                for(int j = 1; j < _obraz->piksele_x - 1; ++j){
                    _obraz->piksele[i][j] = _obraz->piksele[i][j] / (_maska[0][0] + _maska[0][1] + _maska[0][2]
                                                                    +_maska[1][0] + _maska[1][1] + _maska[1][2]
                                                                    +_maska[2][0] + _maska[2][1] + _maska[2][2]);
                }
            }
            break;
    }
}
//--------------------------------------------------------------------------------------------------
void filtr_usredniajacy(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = 1; W[0][1] = 1; W[0][2] = 1;
    W[1][0] = 1; W[1][1] = 1; W[1][2] = 1;
    W[2][0] = 1; W[2][1] = 1; W[2][2] = 1;
    
    splot(_obraz,W);
    
    char komentarz11[50] = " Filtr usredniajacy ";
    strcat(komentarz11,data());
    dodaj_komentarz(_obraz,komentarz11);
}
//--------------------------------------------------------------------------------------------------
void filtr_usredniajacy_ze_wzmocnieniem(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = 1; W[0][1] = 1; W[0][2] = 1;
    W[1][0] = 1; W[1][1] = 2; W[1][2] = 1;
    W[2][0] = 1; W[2][1] = 1; W[2][2] = 1;
    
    splot(_obraz,W);
    
    char komentarz12[100] = " Filtr usredniajacy ze wzmocnieniem ";
    strcat(komentarz12,data());
    dodaj_komentarz(_obraz,komentarz12);
}
//--------------------------------------------------------------------------------------------------
void gradient_robertsa(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = 0;  W[0][1] = 0; W[0][2] = 0;
    W[1][0] = -1; W[1][1] = 0; W[1][2] = 0;
    W[2][0] = 0;  W[2][1] = 1; W[2][2] = 0;
    
    if(_obraz->magiczny_numer[1] == '3') konwersja_do_szarosci(_obraz);
    
    splot(_obraz,W);
    
    char komentarz13[50] = " Gradient Robertsa ";
    strcat(komentarz13,data());
    dodaj_komentarz(_obraz,komentarz13);
}
//--------------------------------------------------------------------------------------------------
void pozioma_maska_prewitta(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = -1;  W[0][1] = -1; W[0][2] = -1;
    W[1][0] = 0;   W[1][1] = 0;  W[1][2] = 0;
    W[2][0] = 1;   W[2][1] = 1;  W[2][2] = 1;
    
    splot(_obraz,W);
    
    char komentarz14[50] = " Pozioma maska Prewitta ";
    strcat(komentarz14,data());
    dodaj_komentarz(_obraz,komentarz14);
}
//--------------------------------------------------------------------------------------------------
void maska_sobela(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = -1;  W[0][1] = -2; W[0][2] = -1;
    W[1][0] = 0;   W[1][1] = 0;  W[1][2] = 0;
    W[2][0] = 1;   W[2][1] = 2;  W[2][2] = 1;
    
    splot(_obraz,W);
    
    char komentarz15[50] = " Maska Sobela ";
    strcat(komentarz15,data());
    dodaj_komentarz(_obraz,komentarz15);
}
//--------------------------------------------------------------------------------------------------
void maska_wykrywajaca_narozniki(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = 1;  W[0][1] = 1;  W[0][2] = 1;
    W[1][0] = -1; W[1][1] = -2; W[1][2] = 1;
    W[2][0] = -1; W[2][1] = -1; W[2][2] = 1;
    
    if(_obraz->magiczny_numer[1] == '3') konwersja_do_szarosci(_obraz);
    
    splot(_obraz,W);
    
    char komentarz16[100] = " Maska wykrywajaca narozniki ";
    strcat(komentarz16,data());
    dodaj_komentarz(_obraz,komentarz16);
}
//--------------------------------------------------------------------------------------------------
void laplasjan(obraz *_obraz){
    int W[3][3];
    
    W[0][0] = -1; W[0][1] = -1; W[0][2] = -1;
    W[1][0] = -1; W[1][1] = -8; W[1][2] = -1;
    W[2][0] = -1; W[2][1] = -1; W[2][2] = -1;
    
    if(_obraz->magiczny_numer[1] == '3') konwersja_do_szarosci(_obraz);
    
    splot(_obraz,W);
    
    char komentarz17[50] = " Laplasjan ";
    strcat(komentarz17,data());
    dodaj_komentarz(_obraz,komentarz17);
}
//--------------------------------------------------------------------------------------------------
