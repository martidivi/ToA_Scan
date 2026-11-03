#include <iostream>
#include <exception>

#include "Reader.h"
#include "Analysis.h"

int main()
{
    try {

        // 1. Creiamo il Reader
        Reader reader("../data/Signal_15mV.root");

        // 2. Leggiamo tutti gli eventi
        std::vector<Event> events = reader.Read();

        std::cout << "Eventi caricati: "
                  << events.size() << std::endl;

        // 3. Creiamo l'oggetto Analysis
        Analysis analysis(events);

        // 4. Eseguiamo l'analisi
        analysis.MakeHistograms();

    }
    catch (const std::exception& e) {

        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;

    }

    return 0;
}