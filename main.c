//
//  main.cpp
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 22.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#include <string.h>

#include "obsluga_obrazu.h"
#include "przetwarzanie_obrazu.h"
#include "filtrowanie_obrazu.h"

int main(int argc, char **argv){
    
    obraz obraz;
    wyzeruj_obraz(&obraz);
    
    w_opcje opcje;
    
    printf("%d\n", przetwarzaj_opcje(argc,argv,&opcje));
    
    /* Jeśli mamy wykonac czytanie pliku wejsciowego */
    if(opcje.czytaj == 1){
        czytaj(opcje.plik_we,&obraz);
        fclose(opcje.plik_we);
    }
    
    /* Jeśli mamy wyswietlic obraz i obraz wejsciowy istnieje */
    if( (opcje.wyswietlenie == 1) && (opcje.plik_we != NULL) ) wyswietl(opcje.nazwa_pliku_we);
    
    /* Jeśli mamy wykonac negatyw */
    if(opcje.negatyw == 1) negatyw(&obraz);
    /* Jeśli mamy wykonac progowanie */
    if(opcje.progowanie == 1) progowanie(&obraz,opcje.w_progu);
    /* Jeśli mamy wykonac progowanie czerni */
    if(opcje.progowanie_czerni == 1) progowanie_czerni(&obraz,opcje.w_progu_czerni);
    /* Jeśli mamy wykonac progowanie bieli */
    if(opcje.progowanie_bieli == 1) progowanie_bieli(&obraz,opcje.w_progu_bieli);
    /* Jeśli mamy wykonac korekcje gamma */
    if(opcje.korekcja_gamma == 1) korekcja_gamma(&obraz,opcje.w_gamma);
    /* Jeśli mamy wykonac zmiane poziomow czerni i bieli */
    if(opcje.zmiana_poziomow == 1) zmiana_poziomow(&obraz,opcje.w_czerni,opcje.w_bieli);
    /* Jeśli mamy wykonac konturowanie */
    if(opcje.konturowanie == 1) konturowanie(&obraz);
    /* Jeśli mamy wykonac rozmywanie poziome */
    if(opcje.rozmywanie_poziome == 1) rozmywanie_poziome(&obraz);
    /* Jeśli mamy wykonac rozmywanie pionowe */
    if(opcje.rozmywanie_pionowe == 1) rozmywanie_pionowe(&obraz);
    /* Jeśli mamy wykonac rozciaganie histogramu */
    if(opcje.rozciaganie_histogramu == 1) rozciaganie_histogramu(&obraz);
    
    /* Jeśli mamy uzyc filtru usredniajacego */
    if(opcje.filtr_usredniajacy == 1) filtr_usredniajacy(&obraz);
    /* Jeśli mamy uzyc filtru usredniajacego ze wzmocnieniem */
    if(opcje.filtr_usredniajacy == 1) filtr_usredniajacy(&obraz);
    /* Jeśli mamy uzyc gradientu Robertsa */
    if(opcje.gradient_robertsa == 1) gradient_robertsa(&obraz);
    /* Jeśli mamy uzyc poziomej maski Prewitta */
    if(opcje.pozioma_maska_prewitta == 1) pozioma_maska_prewitta(&obraz);
    /* Jeśli mamy uzyc maski Sobela */
    if(opcje.maska_sobela == 1) maska_sobela(&obraz);
    /* Jeśli mamy uzyc maski wykrywajacej narozniki */
    if(opcje.maska_wykrywajaca_narozniki == 1) maska_wykrywajaca_narozniki(&obraz);
    /* Jeśli mamy uzyc Laplasjanu */
    if(opcje.laplasjan == 1) laplasjan(&obraz);
    
    /* Jeśli mamy wykonac zapisanie operacji wykonanych na pliku wejsciowym do pliku wyjsciowego */
    if(opcje.zapisz == 1){
        zapisz(opcje.plik_wy,&obraz);
        fclose(opcje.plik_wy);
    }
    
    /* Jeśli mamy wyswietlic obraz i obraz wyjsciowy istnieje */
    if( (opcje.wyswietlenie == 1) && (opcje.nazwa_pliku_wy != NULL) ) wyswietl(opcje.nazwa_pliku_wy);
    
    return 0;
}
