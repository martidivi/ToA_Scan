#ifndef EVENT_H
#define EVENT_H

#include <cstdint>
#include <vector>

struct Event {

    uint8_t board;
    double timestamp;
    uint64_t triggerID;
    uint64_t numHits;

    uint8_t channel;
    uint8_t edge;
    std::vector<uint16_t> hitNumber;

    uint8_t toa;
    std::vector<double> tot;

};

#endif