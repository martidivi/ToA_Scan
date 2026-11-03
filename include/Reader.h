#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

#include "Event.h"

class Reader {

public:

    Reader(const int& thr);

    std::vector<Event> Read();
    
    // getter per costruire il filename partendo dalla threshold (devo renderla stringa per concatenare)
    std::string getfilename() const {
        return "../data/Signal_" + std::to_string(thr) + "mV.root";
    }

private:

    int thr; // soglia

};

#endif