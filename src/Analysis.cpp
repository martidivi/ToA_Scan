#include "Analysis.h"
#include "TStyle.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"


// Costruttore
Analysis::Analysis(const std::vector<Event>& events)
    : events(events)
{
}

// Funzione che crea gli istogrammi
void Analysis::MakeHistograms()
{
    // Creiamo un istogramma per il ToT
    TH1D d_t(
        "d_t",
        "Distribuzione Delta_t;Delta_t;Count",
        150, -50, 50
    );





    int chan[2]={2,6}; //canali nei quali voglio vedere la differenza temporale (in ordine di grandezza)





    d_t.SetDirectory(nullptr);

    double get_val1, get_val2;

    // Scorriamo tutti gli eventi
    for (const Event& ev : events) {
 
    get_val1=0;
    get_val2=0;    
    int a=0;
    int b=0;


        // Scorriamo tutti i valori ToT dell'evento
        for (size_t i = 0; i < ev.toa.size(); i++) {

        double value = ev.toa[i];
        uint8_t channel = ev.channel[i];
        uint8_t edge = ev.edge[i];


        if((value>305)||(value<260)||(edge==1)){continue;}

        if((channel==chan[0])&&(a==0)){

            get_val1=value;
            a=1;
        }
        
        if((channel==chan[1])&&(b==0)){

           get_val2=value;
           b=1;
        }

        if((a==1)&&(b==1)){

            d_t.Fill(get_val1-get_val2);
            break;
        }
            

        }
    }

    // Disegniamo e salviamo l'istogramma
    TCanvas canvas("canvas", "Distribuzione dt", 800, 600);

    canvas.SetLogy();  // Scala logaritmica sull'asse Y
    gStyle->SetOptFit(1111);
    d_t.Fit("gaus", "", "", -3, 3);
    d_t.Draw();

    canvas.SaveAs("dt.png");





}