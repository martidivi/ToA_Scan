#ifndef CONSTANTS_H
#define CONSTANTS_H

// file in cui definisco il vettore dei voltaggi di soglia e le coppie da confrontare
// questo file viene "condiviso" al file di analisi (lo includo in Analysis.cpp)
// per sicurezza i vettori sono definiti inline, in modo da poterli "includere" in tanti file diversi senza che ci siano problemi di tante "ridefinizioni" (e const perché tanto non devono cambiare)

#include <vector>
#include <utility> // header per std::pair

// Creare le coppie: uso un vettore di coppie (per le coppie uso std::pair), lungo 6 (tutte le possibili combinazioni)
// canali nei quali voglio vedere la differenza temporale
//inline const std::vector<std::pair<int,int>> chan_combos = {{2,4}, {2,6}, {2,8}, {4,6}, {4,8}, {6,8}};
inline const std::vector<std::pair<int,int>> chan_combos = {{3,4}};

// vettore per i voltaggi di soglia (in mV)
//inline const std::vector<int> thresholds = {15, 20, 25, 30, 40, 45, 50};
inline const std::vector<int> thresholds = {0};

#endif