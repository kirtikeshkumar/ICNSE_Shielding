{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Thu Mar 21 12:01:09 2024 by ROOT version6.28/00)
//   from TTree antiNeutrinos/antiNeutrinos
//   found on file: output_neutron_4500keV_HHBLHBLH_10000000evt.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output_neutron_4500keV_HHBLHBLH_10000000evt.root");
   if (!f) {
      f = new TFile("output_neutron_4500keV_HHBLHBLH_10000000evt.root");
   }
    f->GetObject("antiNeutrinos",tree);

//Declaration of leaves types
   Int_t           fEvent;
   Int_t           fnum;
   Double_t        fEnergy;
   Double_t        fTime;

   // Set branch addresses.
   antiNeutrinos->SetBranchAddress("fEvent",&fEvent);
   antiNeutrinos->SetBranchAddress("fnum",&fnum);
   antiNeutrinos->SetBranchAddress("fEnergy",&fEnergy);
   antiNeutrinos->SetBranchAddress("fTime",&fTime);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// antiNeutrinos->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = antiNeutrinos->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += antiNeutrinos->GetEntry(i);
//   }
}
