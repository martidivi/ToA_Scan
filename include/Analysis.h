#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include "Event.h"

class Analysis {

public:

    Analysis(const std::vector<Event>& events);

    void MakeHistograms();

private:

    const std::vector<Event>& events;

};

#endif