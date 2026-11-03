#ifndef EVENT_H
#define EVENT_H

#include <cstdint>
#include <vector>

struct Event {

    uint8_t board;
    double timestamp;
    uint64_t triggerID;
    uint64_t numHits;

    std::vector<uint8_t> channel;
    std::vector<uint8_t> edge;
    std::vector<uint16_t> hitNumber;

    std::vector<double> toa;
    std::vector<double> tot;

};

#endif