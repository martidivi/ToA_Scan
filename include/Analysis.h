#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include "Event.h"

class Analysis {

public:

    Analysis(const std::vector<Event>& events, const int& thr);

    void MakeHistogram(int ch1, int ch2); // coppia di canali in input

    // qua sarebbe da aggiungere una funzione che plotti gli andamenti delle sigma con le soglie
private:
    const std::vector<Event>& events;
    int thr;

};

#endif