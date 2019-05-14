//
//  obsluga_obrazu.c
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 22.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#include "obsluga_obrazu.h"

//--------------------------------------------------------------------------------------------------
void wyzeruj_obraz(obraz *_obraz) {
    _obraz->wymx = 0;
    _obraz->wymy = 0;
    _obraz->szarosci = 0;
    _obraz->piksele = NULL;
    _obraz->piksele_x = 0;
    _obraz->piksele_y = 0;
}
//--------------------------------------------------------------------------------------------------
int czytaj(FILE *_plik,obraz *_obraz){
    char buf[DL_LINII];     /* <- bufor pomocniczy do czytania naglowka i komentarzy */
    int znak = '#';         /* <- zmienna pomocnicza do czytania komentarzy */
    int koniec = 0;         /* <- czy napotkano koniec danych w pliku */
                             
    /* Sprawdzenie czy podano prawidłowy uchwyt pliku */
    if (_plik==NULL) {
        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
        return 0;
    }
    
    /* Sprawdzenie "numeru magicznego" - powinien być P2 */
    if (fgets(buf,DL_LINII,_plik)==NULL)       /* Wczytanie pierwszej linii pliku do bufora */
        koniec = 1;                              /* Nie udalo sie? Koniec danych! */
    
    if ( (buf[0] != 'P') || ( buf[1] != '2' && buf[1] != '3') || koniec) {  /* Czy jest magiczne "P2" lub "P3"? */
        fprintf(stderr,"Blad: To nie jest plik PGM ani PPM\n");
        return 0;
    }
    
    /* zapisanie numeru magicznego do struktury przechowujacej info o obrazie */
    _obraz->magiczny_numer[0] = buf[0];
    _obraz->magiczny_numer[1] = buf[1];
    
    /* Pominiecie komentarzy */
    int i = 0;
    do{
        if((znak = fgetc(_plik)) == '#') {
            if (fgets(buf,DL_LINII,_plik)==NULL){
                koniec=1;
            }
            //przekopiowanie komentarzy do tablicy komentarzy
            for (int j = 0; j < strlen(buf); ++j){
                _obraz->komentarze[i][j] = buf[j];
            }
            ++i;
            
        }else ungetc(znak,_plik);
    }while (znak=='#' && !koniec);
    
    /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
    if (fscanf(_plik,"%d %d %d",&(_obraz->wymx),&(_obraz->wymy),&(_obraz->szarosci))!=3) {
        fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
        return 0;
    }
    
    /* Jesli jest to obraz PGM */
    if(_obraz->magiczny_numer[1] == '2'){
        _obraz->piksele_x = _obraz->wymx; /* tyle samo pikseli w rzedzie */
        _obraz->piksele_y = _obraz->wymy;
    }
    
    /* Jesli jest to obraz PPM */
    if(_obraz->magiczny_numer[1] == '3'){
        _obraz->piksele_x = _obraz->wymx * 3; /* trzy razy wiecej pikseli w rzedzie */
        _obraz->piksele_y = _obraz->wymy;
    }
    
    /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
   
    /* Przydzielamy pamięć dla każdej kolumny */
    _obraz->piksele = malloc(_obraz->piksele_y * sizeof( int * ) );
    
    /* Przydzielamy pamięć dla każdego wiersza */
    for ( i = 0; i < _obraz->piksele_y; i++ ){
        _obraz->piksele[i] = malloc( _obraz->piksele_x * sizeof( int ) );
    }
    
    for (int i = 0; i < _obraz->piksele_y; i++) {
        for (int j = 0; j < _obraz->piksele_x; j++) {
            if (fscanf(_plik,"%d",&(_obraz->piksele[i][j]))!=1) {
                fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
                return 0;
            }
        }
    }
    
    return 1;   /* Czytanie zakonczone sukcesem */
}
//--------------------------------------------------------------------------------------------------
void wyswietl(char *_nazwa_pliku) {
    
    char polecenie[DL_LINII];
    
    strcpy(polecenie,"open ");
    strcat(polecenie,_nazwa_pliku);
    
    printf("%s\n",polecenie);
    system(polecenie);
}
//--------------------------------------------------------------------------------------------------
int zapisz(FILE *_plik,obraz *_obraz){
    /* wpisanie na poczatek pliku "numeru magicznego" */
    fprintf(_plik,"%c", _obraz->magiczny_numer[0]);
    fprintf(_plik,"%c\n", _obraz->magiczny_numer[1]);
    
    /* wpisanie do pliku komentarzy */
    for(int i = 0; i < DL_LINII; ++i){
        fprintf(_plik,"#");
        for(int j = 0; j < DL_LINII; ++j){
            fprintf(_plik,"%c",_obraz->komentarze[i][j]);
            if(_obraz->komentarze[i][j] == '\n') break;
        }
        if(_obraz->komentarze[i+1][0] == 0) break;
    }
    
    /* wpisanie do pliku wymiarow obrazu */
    fprintf(_plik,"%d %d \n",_obraz->wymx,_obraz->wymy);

    /* wpisanie do pliku maksymalnego stopnia szarosci */
    fprintf(_plik,"%d \n",_obraz->szarosci);
    
    /* wpisanie do pliku pikseli */
    for(int i = 0; i < _obraz->piksele_y; i++) {
        for(int j = 0; j < _obraz->piksele_x; j++) {
            fprintf(_plik,"%d ",_obraz->piksele[i][j]);
        }
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------
void dodaj_komentarz(obraz *_obraz,char *_komentarz){
    
    /* dodanie na koniec tablicy komentarzy nowego komentarza */
    for(int i = 0; i < DL_LINII; ++i){
        if(_obraz->komentarze[i][0] == '\0'){
            for (int j = 0; j < strlen(_komentarz); ++j) {
                _obraz->komentarze[i][j] = _komentarz[j];
            }
            break;
        }
    }
}
//--------------------------------------------------------------------------------------------------
char *data(void){
    time_t czas;
    struct tm * ptr;
    time( & czas );
    ptr = localtime( & czas );
    char * data = asctime( ptr );
    
    return data;
}
//--------------------------------------------------------------------------------------------------
void konwersja_do_szarosci(obraz *_obraz){
   
    if(_obraz->magiczny_numer[1] == '3'){
        for(int i = 0, k = 0; i < _obraz->piksele_y; i++, k++) {
            for(int j = 0, l = 0; j < _obraz->piksele_x; j = j + 3, l++) {
                _obraz->piksele[k][l] = (_obraz->piksele[i][j] + _obraz->piksele[i][j+1] + _obraz->piksele[i][j+2]) / 3;
            }
        }
    }else printf("To nie jest obraz kolorowy !");
    
    _obraz->magiczny_numer[1] = '2';
    _obraz->piksele_x = _obraz->wymx;
    
}
//--------------------------------------------------------------------------------------------------
void wybierz_kolor(obraz *_obraz,char *_kolor){
    assert(_kolor[0] == 'r' || _kolor[0] == 'g' || _kolor[0] == 'b');
    if(_obraz->magiczny_numer[1] == '3'){
        _obraz->kolor[0] = *_kolor;
    }else printf("To nie jest obraz kolorowy !");
}
//--------------------------------------------------------------------------------------------------
void wyzeruj_opcje(w_opcje * wybor) {
    wybor->plik_we = NULL;
    wybor->plik_wy = NULL;
    wybor->negatyw = 0;
    wybor->konturowanie = 0;
    wybor->progowanie = 0;
    wybor->wyswietlenie = 0;
    wybor->zapisz = 0;
    wybor->czytaj = 0;
}
//--------------------------------------------------------------------------------------------------
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor) {
    wyzeruj_opcje(wybor);
    wybor->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */
    
    for(int i = 1; i < argc; i++){
        if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
            return B_NIEPOPRAWNAOPCJA;
        switch (argv[i][1]) {
            case 'i':                 /* opcja z nazwa pliku wejsciowego */
                if (++i < argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
                    wybor->nazwa_pliku_we=argv[i];
                    if (strcmp(wybor->nazwa_pliku_we,"-")==0)   /* gdy nazwa jest "-"        */
                        wybor->plik_we=stdin;            /* ustwiamy wejscie na stdin */
                    else{                                 /* otwieramy wskazany plik   */
                        wybor->plik_we = fopen(wybor->nazwa_pliku_we,"r");
                        wybor->czytaj = 1;
                    }
                } else
                    return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
                break;
            
            case 'o':                 /* opcja z nazwa pliku wyjsciowego */
                if (++i<argc) {         /* wczytujemy kolejny argument jako nazwe pliku */
                    wybor->nazwa_pliku_wy=argv[i];
                    if (strcmp(wybor->nazwa_pliku_wy,"-")==0)/* gdy nazwa jest "-"         */
                        wybor->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
                    else{                               /* otwieramy wskazany plik    */
                        wybor->plik_wy = fopen(wybor->nazwa_pliku_wy,"w");
                        wybor->zapisz = 1;
                    }
                } else
                    return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
                break;
            
            case 'p':
                if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%d",&wybor->w_progu) == 1) {
                        wybor->progowanie = 1;
                    }else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
            
            case 'n':                  /* mamy wykonac negatyw */
                wybor->negatyw = 1;
                break;
            
            case 'k':                  /* mamy wykonac konturowanie */
                wybor->konturowanie = 1;
                break;
            
            case 'd':                  /* mamy wyswietlic obraz */
                wybor->wyswietlenie = 1;
                break;
                
            case 'c':
                if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%d",&wybor->w_progu_czerni) == 1) {
                        wybor->progowanie_czerni = 1;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
                
            case 'b':            
                if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%d",&wybor->w_progu_bieli) == 1) {
                        wybor->progowanie_bieli = 1;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
                
            case 'g':
                if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%f",&wybor->w_gamma) == 1) {
                        wybor->korekcja_gamma = 1;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
                
            case 'z':
                if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%d",&wybor->w_czerni) != 1) {
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                    }
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%d",&wybor->w_bieli) == 1) {
                        wybor->zmiana_poziomow = 1;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
                
            case 'x':
                wybor->rozmywanie_poziome = 1;
                break;
                
            case 'y':
                wybor->rozmywanie_pionowe = 1;
                break;
                
            case 'h':
                wybor->rozciaganie_histogramu = 1;
                break;
                
            case 's':
                if (++i < argc) { /* wczytujemy kolejny argument jako wartosc progu */
                    if(sscanf(argv[i],"%s",&wybor->filtr) == 1) {
                        if(wybor->filtr == 'u') wybor->filtr_usredniajacy = 1;
                        if(wybor->filtr == 'w') wybor->filtr_usredniajacy_ze_wzmocnieniem = 1;
                        if(wybor->filtr == 'r') wybor->gradient_robertsa = 1;
                        if(wybor->filtr == 'p') wybor->pozioma_maska_prewitta = 1;
                        if(wybor->filtr == 's') wybor->maska_sobela = 1;
                        if(wybor->filtr == 'n') wybor->maska_wykrywajaca_narozniki = 1;
                        if(wybor->filtr == 'l') wybor->laplasjan = 1;
                    } else
                        return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
                } else
                    return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
                break;
            
            default:                    /* nierozpoznana opcja */
                return B_NIEPOPRAWNAOPCJA;
        } /*koniec switch */
    } /* koniec for */
    
    if (wybor->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
        return W_OK;
    else
        return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}
//--------------------------------------------------------------------------------------------------
