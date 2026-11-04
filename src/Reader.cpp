#include "Reader.h"

#include <iostream>
#include <stdexcept>

#include "TFile.h"
#include "TTree.h"

// Costruttore
Reader::Reader(const int& thr)
    : thr(thr)
{
}

// Funzione che legge il file ROOT
std::vector<Event> Reader::Read()
{
    // 1. Creiamo il contenitore in cui salveremo gli eventi
    std::vector<Event> events;

    // 2. Creiamo il filename e apriamo il file ROOT
    std::string filename = getfilename();
    TFile file(filename.c_str(), "READ");

    if (file.IsZombie()) {
        throw std::runtime_error("Errore nell'apertura del file ROOT");
    }

    // 3. Recuperiamo il TTree
    //TTree* tree = dynamic_cast<TTree*>(file.Get("data_tree"));
    TTree* tree = dynamic_cast<TTree*>(file.Get("Event"));

    if (!tree) {
        throw std::runtime_error("TTree non trovato!");
    }

    // 4. Definiamo le variabili collegate ai branch
    uint8_t ev_board;
    double ev_timestamp;
    uint64_t trg_id;
    UInt_t num_hits;

    std::vector<uint8_t>* of_Channel = nullptr;
    std::vector<uint8_t>* of_Edge = nullptr;
    std::vector<uint16_t>* of_HitNumber = nullptr;

    std::vector<double>* of_ToA = nullptr;
    std::vector<double>* of_ToT = nullptr;

    // Modifica per il run
    UChar_t* raw_Channel = nullptr;
    UChar_t* raw_Edge = nullptr;
    UInt_t* raw_HitNumber = nullptr;

    Double_t* raw_ToA = nullptr;
    UShort_t* raw_ToT = nullptr; 

    // 5. Colleghiamo i branch alle variabili
    /*tree->SetBranchAddress("Board", &ev_board);
    tree->SetBranchAddress("Timestamp", &ev_timestamp);
    tree->SetBranchAddress("TriggerID", &trg_id);
*/
    tree->SetBranchAddress("FD01_nhits", &num_hits);
    tree->SetBranchAddress("FD01_channel", &raw_Channel);
    tree->SetBranchAddress("FD01_edge", &raw_Edge);
    //tree->SetBranchAddress("HitNumber", &of_HitNumber);

    tree->SetBranchAddress("FD01_ToA", &raw_ToA);
    tree->SetBranchAddress("FD01_ToT", &raw_ToT);

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

        // Creiamo un vettore temporaneo usando i dati appena letti da ROOT
        std::vector<double> temp_ToA(raw_ToA, raw_ToA + num_hits);
        // Facciamo puntare il puntatore originale a questo vettore
        of_ToA = &temp_ToA;

        // ... e così per tutti i vettori
        // Creiamo un vettore temporaneo usando i dati appena letti da ROOT
        std::vector<uint8_t> temp_Channel(raw_Channel, raw_Channel + num_hits);
        // Facciamo puntare il puntatore originale a questo vettore
        of_Channel = &temp_Channel;

        // Creiamo un vettore temporaneo usando i dati appena letti da ROOT
        std::vector<uint8_t> temp_Edge(raw_Edge, raw_Edge + num_hits);
        // Facciamo puntare il puntatore originale a questo vettore
        of_Edge = &temp_Edge;

        std::vector<double> temp_ToT(raw_ToT, raw_ToT + num_hits);
        // Facciamo puntare il puntatore originale a questo vettore
        of_ToT = &temp_ToT;


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