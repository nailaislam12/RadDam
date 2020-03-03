//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 30 11:17:06 2017 by ROOT version 6.08/07
// from TTree miniTree/miniTree
// found on file: /afs/cern.ch/work/m/mheindl/HF_calibration/Untuplize/test92X_mc.root
//////////////////////////////////////////////////////////

#ifndef Analysis18_h
#define Analysis18_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class Analysis18 {
public :
//   TTree          *fChain;   //!pointer to the analyzed TTree or TChain //use this one if you are going to use a TTree
   TChain           *fChain; //use this one if you are going to use a TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           nvtx;
   Int_t           nele;
   vector<float>   *ele_pt;
   vector<float>   *ele_eta;
   vector<float>   *ele_phi;
   vector<int>     *ele_mediumID;
   Int_t           nhf;
   vector<float>   *hf_en;
   vector<float>   *hf_pt;
   vector<float>   *hf_eta;
   vector<float>   *hf_phi;
   vector<float>   *hf_iso;
   vector<float>   *hf_ecal;
   vector<float>   *hf_hcal;
   // vector<int>     *hf_type;
   // vector<int>     *hf_match;
   // Int_t           nmc;
   // vector<float>   *mc_pt;
   // vector<float>   *mc_eta;
   // vector<float>   *mc_phi;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_nele;   //!
   TBranch        *b_ele_pt;   //!
   TBranch        *b_ele_eta;   //!
   TBranch        *b_ele_phi;   //!
   TBranch        *b_ele_mediumID;   //!
   TBranch        *b_nhf;   //!
   TBranch        *b_hf_en;   //!
   TBranch        *b_hf_pt;   //!
   TBranch        *b_hf_eta;   //!
   TBranch        *b_hf_phi;   //!
   TBranch        *b_hf_iso;   //!
   TBranch        *b_hf_ecal;   //!
   TBranch        *b_hf_hcal;   //!
   // TBranch        *b_hf_type;   //!
   // TBranch        *b_hf_match;   //!
   // TBranch        *b_nmc;   //!
   // TBranch        *b_mc_pt;   //!
   // TBranch        *b_mc_eta;   //!
   // TBranch        *b_mc_phi;   //!

   Analysis18(TChain *tree=0); //change this to TTree if you are doing the TTree
   virtual ~Analysis18();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analysis18_cxx
Analysis18::Analysis18(TChain *tree) : fChain(0) //change this to TTree if you are using the TTree
{

    TChain *myChain = new TChain("miniTree"); //must initialize this before doing the if tree == 0 stuff, need to make it a pointer so that it can deal with trees //comment this out if doing a TTree
// if parameter tree is not specified (or zero), connect the file 
// used to generate this class and read the Tree.
   if (tree == 0) // {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/user/m/mhadley/output_from_HCAL_HF_RadDam_Initial_Tests/output_mc.root");
// //      std::cout << f;
//       if (!f || !f->IsOpen()) {
//          f = new TFile("/eos/user/m/mhadley/output_from_HCAL_HF_RadDam_Initial_Tests/output_mc.root");
//       }
//       f->GetObject("miniTree",tree);
// 
//    } //comment this in if doing a TTree, out if doing a TChain

                { 
                   
                    
           //         myChain->Add("output_data_UL17B_0000.root/miniTree");
//                    myChain->Add("output_data_UL17B_0001.root/miniTree");
//                    
//                    myChain->Add("output_data_UL17C_0000.root/miniTree");
//                    myChain->Add("output_data_UL17C_0001.root/miniTree");
//                    myChain->Add("output_data_UL17C_0002.root/miniTree");
//                     
//                    myChain->Add("output_data_UL17D_0000.root/miniTree");
//                    myChain->Add("output_data_UL17D_0001.root/miniTree");
//                     
//                    myChain->Add("output_data_UL17E_0000.root/miniTree");
//                    myChain->Add("output_data_UL17E_0001.root/miniTree");
//                    myChain->Add("output_data_UL17E_0002.root/miniTree");
//                     
//                    myChain->Add("output_data_UL17F_0000.root/miniTree");
//                    myChain->Add("output_data_UL17F_0001.root/miniTree");
//                    myChain->Add("output_data_UL17F_0002.root/miniTree");
//                     
                 myChain->Add("output_mc.root/miniTree");

}
   //Init(tree); //use this if doing a TTree
   Init(myChain); //use this if doing a TChain
}

Analysis18::~Analysis18()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analysis18::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analysis18::LoadTree(Long64_t entry)
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

void Analysis18::Init(TChain *tree) //change this to TTree *tree if you are using a TTree
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   ele_pt = 0;
   ele_eta = 0;
   ele_phi = 0;
   ele_mediumID = 0;
   hf_en = 0;
   hf_pt = 0;
   hf_eta = 0;
   hf_phi = 0;
   hf_iso = 0;
   hf_ecal = 0;
   hf_hcal = 0;
   // hf_type = 0;
   // hf_match = 0;
   // mc_pt = 0;
   // mc_eta = 0;
   // mc_phi = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("nele", &nele, &b_nele);
   fChain->SetBranchAddress("ele_pt", &ele_pt, &b_ele_pt);
   fChain->SetBranchAddress("ele_eta", &ele_eta, &b_ele_eta);
   fChain->SetBranchAddress("ele_phi", &ele_phi, &b_ele_phi);
   fChain->SetBranchAddress("ele_mediumID", &ele_mediumID, &b_ele_mediumID);
   fChain->SetBranchAddress("nhf", &nhf, &b_nhf);
   fChain->SetBranchAddress("hf_en", &hf_en, &b_hf_en);
   fChain->SetBranchAddress("hf_pt", &hf_pt, &b_hf_pt);
   fChain->SetBranchAddress("hf_eta", &hf_eta, &b_hf_eta);
   fChain->SetBranchAddress("hf_phi", &hf_phi, &b_hf_phi);
   fChain->SetBranchAddress("hf_iso", &hf_iso, &b_hf_iso);
   fChain->SetBranchAddress("hf_ecal", &hf_ecal, &b_hf_ecal);
   fChain->SetBranchAddress("hf_hcal", &hf_hcal, &b_hf_hcal);
   // fChain->SetBranchAddress("hf_type", &hf_type, &b_hf_type);
   // fChain->SetBranchAddress("hf_match", &hf_match, &b_hf_match);
   // fChain->SetBranchAddress("nmc", &nmc, &b_nmc);
   // fChain->SetBranchAddress("mc_pt", &mc_pt, &b_mc_pt);
   // fChain->SetBranchAddress("mc_eta", &mc_eta, &b_mc_eta);
   // fChain->SetBranchAddress("mc_phi", &mc_phi, &b_mc_phi);
   Notify();
}

Bool_t Analysis18::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analysis18::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analysis18::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analysis18_cxx
