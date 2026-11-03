#include "Reader.h"

#include <iostream>
#include <stdexcept>

#include "TFile.h"
#include "TTree.h"

// Costruttore
Reader::Reader(const std::string& filename)
    : filename(filename)
{
}

// Funzione che legge il file ROOT
std::vector<Event> Reader::Read()
{
    // 1. Creiamo il contenitore in cui salveremo gli eventi
    std::vector<Event> events;

    // 2. Apriamo il file ROOT
    TFile file(filename.c_str(), "READ");

    if (file.IsZombie()) {
        throw std::runtime_error("Errore nell'apertura del file ROOT");
    }

    // 3. Recuperiamo il TTree
    TTree* tree = dynamic_cast<TTree*>(file.Get("data_tree"));

    if (!tree) {
        throw std::runtime_error("TTree non trovato!");
    }

    // 4. Definiamo le variabili collegate ai branch
    uint8_t ev_board;
    double ev_timestamp;
    uint64_t trg_id;
    uint64_t num_hits;

    std::vector<uint8_t>* of_Channel = nullptr;
    std::vector<uint8_t>* of_Edge = nullptr;
    std::vector<uint16_t>* of_HitNumber = nullptr;

    std::vector<double>* of_ToA = nullptr;
    std::vector<double>* of_ToT = nullptr;

    // 5. Colleghiamo i branch alle variabili
    tree->SetBranchAddress("Board", &ev_board);
    tree->SetBranchAddress("Timestamp", &ev_timestamp);
    tree->SetBranchAddress("TriggerID", &trg_id);
    tree->SetBranchAddress("NumberofHits", &num_hits);

    tree->SetBranchAddress("Hit_Channel", &of_Channel);
    tree->SetBranchAddress("Edge", &of_Edge);
    tree->SetBranchAddress("HitNumber", &of_HitNumber);

    tree->SetBranchAddress("ToA", &of_ToA);
    tree->SetBranchAddress("ToT", &of_ToT);

    // 6. Scopriamo quanti eventi contiene il TTree
    Long64_t nEntries = tree->GetEntries();

    std::cout << "Numero di eventi: " << nEntries << std::endl;

    // 7. Leggiamo gli eventi uno alla volta
    for (Long64_t i = 0; i < nEntries; i++) {

        tree->GetEntry(i);

        // Controlliamo che i vettori siano disponibili
        if (!of_Channel || !of_Edge || !of_HitNumber ||
            !of_ToA || !of_ToT) {
            throw std::runtime_error("Errore nella lettura dei branch vettoriali");
        }

        // Creiamo un nuovo evento
        Event ev;

        ev.board = ev_board;
        ev.timestamp = ev_timestamp;
        ev.triggerID = trg_id;
        ev.numHits = num_hits;

        ev.channel = *of_Channel;
        ev.edge = *of_Edge;
        ev.hitNumber = *of_HitNumber;

        ev.toa = *of_ToA;
        ev.tot = *of_ToT;

        // Aggiungiamo l'evento al vettore
        events.push_back(ev);
    }

    // 8. Restituiamo tutti gli eventi letti
    return events;
}