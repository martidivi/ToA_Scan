#include <iostream>
#include <exception>

#include "Reader.h"
#include "Analysis.h"
#include "Constants.h"

int main()
{
    try {

        for (size_t i = 0; i < thresholds.size(); i++){
            // 1. Creiamo il Reader
            Reader reader(thresholds[i]);

            // 2. Leggiamo tutti gli eventi
            std::vector<Event> events = reader.Read();

            std::cout << "Eventi caricati: "
                      << events.size() << std::endl;

            // 3. Creiamo l'oggetto Analysis
            Analysis analysis(events, thresholds[i]);

            // 4. Eseguiamo l'analisi
            for (size_t j = 0; j < chan_combos.size(); j++){
                // definisco i canali (primo e secondo)
                int ch1 = chan_combos[j].first, ch2 = chan_combos[j].second;

                analysis.MakeHistogram(ch1, ch2);
            }
        }
    }   
    catch (const std::exception& e) {

        std::cerr << "Errore: " << e.what() << std::endl;
        return 1;

    }

    return 0;
}