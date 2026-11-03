#include "Analysis.h"
#include "Constants.h"

#include "TStyle.h" // per mostrare i risultati del fit sul plot
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFitResult.h" // per ottenere il risultato del fit (la sigma da salvare)
#include <iostream> // check
#include <fstream> // per scrivere in file .txt

// Costruttore
Analysis::Analysis(const std::vector<Event>& events, const int& thr)
    : events(events), thr(thr)
{
}

// Funzione che crea gli istogrammi, li plotta in file .png che salva, e crea un file .txt con le sigma
void Analysis::MakeHistogram(int ch1, int ch2)
{
    // check
    std::cout << "thr=" << thr << " ch1=" << ch1 << " ch2=" << ch2 << std::endl;

    // Creiamo un istogramma per il ToA
    TH1D d_t(
        "d_t",
        "Distribuzione Delta_t;Delta_t [ns];Count",
        150, -50, 50
    );



    d_t.SetDirectory(nullptr);

    double get_val1, get_val2;

    // Scorriamo tutti gli eventi
    for (const Event& ev : events) {
 
    get_val1=0;
    get_val2=0;    
    int a=0;
    int b=0;


        // Scorriamo tutti i valori ToA dell'evento
        //for (size_t i = 0; i < ev.toa.size(); i++) {

        double value = ev.toa;
        uint8_t channel = ev.channel;
        uint8_t edge = ev.edge;


        if((value>305)||(value<260)||(edge==1)){continue;}

        if((channel==ch1)&&(a==0)){

            get_val1=value;
            a=1;
        }
        
        if((channel==ch2)&&(b==0)){

           get_val2=value;
           b=1;
        }

        if((a==1)&&(b==1)){

            d_t.Fill(get_val1-get_val2);
            break;
        }
            

        
    }

    // Disegniamo e salviamo l'istogramma
    TCanvas canvas("canvas", "Distribuzione dt", 800, 600);

    canvas.SetLogy();  // Scala logaritmica sull'asse Y
    gStyle->SetOptFit(1111);

    TFitResultPtr fit = d_t.Fit("gaus", "S", "", -3, 3);
    // prendo la sigma del fit e l'errore associato
    double sigma = fit->Parameter(2);
    double sigma_err = fit->ParError(2);

    d_t.Draw();

    std::string filename = "dt_" + std::to_string(thr) + "mV" + 
                           "_ch" + std::to_string(ch1) + 
                           "_ch" + std::to_string(ch2) + ".png";
    canvas.SaveAs(filename.c_str());

    // check
    std::cout << "sigma= " << sigma << " +/- " << sigma_err << " ns"<< std::endl;


    // salvare su file (questo sarebbe da mettere in funzione a parte che così è un troiaio (?) però non sono sicura)
    std::ofstream file_output("../data/sigma.txt", std::ios_base::app); // l'ultima opzione serve ad aggiungere una riga dopo l'altra

    if (file_output.is_open()) {
        // Scrivo dati sul file
        file_output << thr << " " << ch1 << " " << ch2 << " " << sigma << " " << sigma_err << std::endl;
    
        file_output.close();
    } 
    else {
        std::cerr << "Non apre il file :(" << std::endl;
    }

}
