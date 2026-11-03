#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

#include "Event.h"

class Reader {

public:

    Reader(const std::string& filename);

    std::vector<Event> Read();

private:

    std::string filename;

};

#endif