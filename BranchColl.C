{
  //////////////////////////////////////////////////////////
  //   This file has been automatically generated
  //     (Tue Sep  1 16:44:47 2026 by ROOT version6.28/10)
  //   from TTree BranchColl/BranchColl
  //   found on file: output1.root
  //////////////////////////////////////////////////////////

  // Reset ROOT and connect tree file
  gROOT->Reset();
  // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("output1.root");
  // if (!f) {
  //    f = new TFile("output1.root");
  // }
  //  f->GetObject("BranchColl",tree);
  std::string fname = "output1.root";
  TFile *f = new TFile(fname.c_str(), "READ");

  if (!f || f->IsZombie()) {
    std::cerr << "Error: Unable to open file " << fname << std::endl;
    return; // Exit or handle the error appropriately
  }

  TTree *BranchColl = (TTree *)f->Get("BranchColl");
  // Declaration of leaves types
  Int_t EvNo;
  Int_t Copy;
  Char_t DetectorMat[4];
  Double_t EnergyDep;
  Char_t Branch[21];
  Double_t EDepTime;
  Double_t DecayTime;
  Double_t OrigDecayTime;
  Char_t OrigDecayParticle[15];

  // Set branch addresses.
  BranchColl->SetBranchAddress("EvNo", &EvNo);
  BranchColl->SetBranchAddress("Copy", &Copy);
  BranchColl->SetBranchAddress("DetectorMat", DetectorMat);
  BranchColl->SetBranchAddress("EnergyDep", &EnergyDep);
  BranchColl->SetBranchAddress("Branch", Branch);
  BranchColl->SetBranchAddress("EDepTime", &EDepTime);
  BranchColl->SetBranchAddress("DecayTime", &DecayTime);
  BranchColl->SetBranchAddress("OrigDecayTime", &OrigDecayTime);
  BranchColl->SetBranchAddress("OrigDecayParticle", OrigDecayParticle);

  //     This is the loop skeleton
  //       To read only selected branches, Insert statements like:
  // BranchColl->SetBranchStatus("*",0);  // disable all branches
  // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

  Long64_t nentries = BranchColl->GetEntries();
  std::cout << "Now sorting: " << nentries << " entries in order of timestamp"
            << std::endl;

  BranchColl->BuildIndex("EvNo");
  TTreeIndex *index = (TTreeIndex *)BranchColl->GetTreeIndex();
  if (!index) {
    std::cerr << "Error creating tree index!" << std::endl;
    gROOT->ProcessLine(".q");
    return;
  }
  Long64_t *indices = index->GetIndex();
  if (!indices) {
    std::cerr << "Error retrieving index array!" << std::endl;
    gROOT->ProcessLine(".q");
    return;
  }

  std::cout << "sorting done" << std::endl;
  Long64_t nbytes = 0;

  int currEvt = -1;
  double currTime = 0;
  double edep = 0;
  double sig;
  TH1 *hSpec = new TH1F("hSpec", "EnergySpectra", 20000, 0, 2000);
  for (Long64_t i = 0; i < nentries; i++) {
    nbytes += BranchColl->GetEntry(indices[i]);
    if (EvNo == currEvt) {
      if (Copy == 120) {
        if (strncmp(Branch, "e+ ", 3) == 0 ||
            strncmp(Branch, "gam", 3) == 0) { //
          if (fabs(EDepTime - currTime) < 100) {
            edep += EnergyDep;
          } else
            edep = 0;
        }
      }
    } else {
      sig = 1.975962E-8 * edep * edep - 8.47571E-5 * edep + 0.123;
      sig = sig * edep / 2.35;
      if (edep > 0)
        hSpec->Fill(gRandom->Gaus(edep, sig));
      currEvt = EvNo;
      edep = 0;
      if (Copy == 120) {
        if (strncmp(Branch, "e+ ", 3) == 0 ||
            strncmp(Branch, "gam", 3) == 0) { //
          edep += EnergyDep;
          currTime = EDepTime;
        }
      }
    }
  }

  //   TCanvas c1 = new TCanvas();
  hSpec->Draw("Hist");
}
