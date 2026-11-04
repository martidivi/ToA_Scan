//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov  3 23:52:58 2026 by ROOT version 6.38.04
// from TTree Event/Event
// found on file: Signal_0mV.root
//////////////////////////////////////////////////////////

#ifndef RunAnalysis_h
#define RunAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class RunAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        FD00_fine_tstamp;
   ULong64_t       FD00_trgID;
   UInt_t          FD00_nhits;
   UChar_t         FD00_channel[2];   //[FD00_nhits]
   UInt_t          FD00_ToA[2];   //[FD00_nhits]
   UShort_t        FD00_ToT[2];   //[FD00_nhits]
   Double_t        FD01_tstamp_us;
   ULong64_t       FD01_trigger_id;
   UInt_t          FD01_nhits;
   UChar_t         FD01_channel[39];   //[FD01_nhits]
   UChar_t         FD01_edge[39];   //[FD01_nhits]
   Double_t        FD01_ToA[39];   //[FD01_nhits]
   UShort_t        FD01_ToT[39];   //[FD01_nhits]

   // List of branches
   TBranch        *b_FD00_fine_tstamp;   //!
   TBranch        *b_FD00_trgID;   //!
   TBranch        *b_FD00_nhits;   //!
   TBranch        *b_FD00_channel;   //!
   TBranch        *b_FD00_ToA;   //!
   TBranch        *b_FD00_ToT;   //!
   TBranch        *b_FD01_tstamp_us;   //!
   TBranch        *b_FD01_trigger_id;   //!
   TBranch        *b_FD01_nhits;   //!
   TBranch        *b_FD01_channel;   //!
   TBranch        *b_FD01_edge;   //!
   TBranch        *b_FD01_ToA;   //!
   TBranch        *b_FD01_ToT;   //!

   RunAnalysis(TTree *tree=0);
   virtual ~RunAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual bool     Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RunAnalysis_cxx
RunAnalysis::RunAnalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Signal_0mV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Signal_0mV.root");
      }
      f->GetObject("Event",tree);

   }
   Init(tree);
}

RunAnalysis::~RunAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t RunAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t RunAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void RunAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("FD00_fine_tstamp", &FD00_fine_tstamp, &b_FD00_fine_tstamp);
   fChain->SetBranchAddress("FD00_trgID", &FD00_trgID, &b_FD00_trgID);
   fChain->SetBranchAddress("FD00_nhits", &FD00_nhits, &b_FD00_nhits);
   fChain->SetBranchAddress("FD00_channel", FD00_channel, &b_FD00_channel);
   fChain->SetBranchAddress("FD00_ToA", FD00_ToA, &b_FD00_ToA);
   fChain->SetBranchAddress("FD00_ToT", FD00_ToT, &b_FD00_ToT);
   fChain->SetBranchAddress("FD01_tstamp_us", &FD01_tstamp_us, &b_FD01_tstamp_us);
   fChain->SetBranchAddress("FD01_trigger_id", &FD01_trigger_id, &b_FD01_trigger_id);
   fChain->SetBranchAddress("FD01_nhits", &FD01_nhits, &b_FD01_nhits);
   fChain->SetBranchAddress("FD01_channel", FD01_channel, &b_FD01_channel);
   fChain->SetBranchAddress("FD01_edge", FD01_edge, &b_FD01_edge);
   fChain->SetBranchAddress("FD01_ToA", FD01_ToA, &b_FD01_ToA);
   fChain->SetBranchAddress("FD01_ToT", FD01_ToT, &b_FD01_ToT);
   Notify();
}

bool RunAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be for a new TTree in a TChain. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return true;
}

void RunAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t RunAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef RunAnalysis_cxx
