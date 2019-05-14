//
//  filtrowanie_obrazu.h
//  Przetwarzanie_obrazów_2
//
//  Created by Michał on 23.06.2018.
//  Copyright © 2018 Michał. All rights reserved.
//

#ifndef filtrowanie_obrazu_h
#define filtrowanie_obrazu_h

#include <stdio.h>
#include "przetwarzanie_obrazu.h"

void splot(obraz *_obraz, int _maska[3][3]);

void filtr_usredniajacy(obraz *_obraz);
void filtr_usredniajacy_ze_wzmocnieniem(obraz *_obraz);
void gradient_robertsa(obraz *_obraz);
void pozioma_maska_prewitta(obraz *_obraz);
void maska_sobela(obraz *_obraz);
void maska_wykrywajaca_narozniki(obraz *_obraz);
void laplasjan(obraz *_obraz);

#endif /* filtrowanie_obrazu_h */
