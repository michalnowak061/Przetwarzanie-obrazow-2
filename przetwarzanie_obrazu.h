//
//  przetwarzanie_obrazu.h
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 22.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#ifndef przetwarzanie_obrazu_h
#define przetwarzanie_obrazu_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "obsluga_obrazu.h"

void negatyw(obraz *_obraz);
void progowanie(obraz *_obraz, int _prog);
void progowanie_czerni(obraz *_obraz, int _prog);
void progowanie_bieli(obraz *_obraz, int _prog);
void korekcja_gamma(obraz *_obraz, float _gamma);
void zmiana_poziomow(obraz *_obraz, int _czern, int _biel);
void konturowanie(obraz *_obraz);
void rozmywanie_poziome(obraz *_obraz);
void rozmywanie_pionowe(obraz *_obraz);
void rozciaganie_histogramu(obraz *_obraz);

#endif /* przetwarzanie_obrazu_h */
