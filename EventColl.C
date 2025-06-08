//////////////////////////////////////////////////////////
//   This file has been automatically generated
//     (Sun Jun  8 10:18:57 2025 by ROOT version6.32.02)
//   from TTree EventColl/EventColl
//   found on file: output_DetEff_gamma_3600keV_10000000evt.root
//////////////////////////////////////////////////////////
#include <stdio.h>
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TTreeIndex.h"
#include <filesystem>
#include "TH1.h"

int EventColl()
{

   /*if (argc < 2)
   {
      std::cerr << "Usage: " << argv[0] << " <folder_path>" << std::endl;
      return 1;
   }

   std::string folderPath = argv[1];

   for (const auto &entry : fs::directory_iterator(folderPath))
   {
      if (!entry.is_regular_file())
         continue;

      std::string filename = entry.path().filename().string();
      if (filename.size() < 5 || filename.substr(filename.size() - 5) != ".root")
         continue;
   }*/

   // Reset ROOT and connect tree file
   gROOT->Reset();
   std::string filename = "outputs/DetEff/gamma/output_DetEff_gamma_3600keV_10000000evt.root";
   TFile *f = new TFile(filename.c_str(), "r");
   TTree *tr = (TTree *)f->Get("EventColl");

   std::smatch match;
   std::regex energy_pattern("gamma_(\\d+)keV");
   if (!std::regex_search(filename, match, energy_pattern))
   {
      std::cerr << "Filename doesn't match energy pattern: " << filename << std::endl;
      return 1;
   }

   int gammaEnergy = std::stoi(match[1]);
   std::cout << "Gamma Energy: " << gammaEnergy << std::endl;

   // Declaration of leaves types
   Int_t EvNo;
   Int_t Copy;
   Char_t DetectorMat[4];
   Double_t EnergyDep;
   Int_t NumHitPrimary;

   // Set branch addresses.
   tr->SetBranchAddress("EvNo", &EvNo);
   tr->SetBranchAddress("Copy", &Copy);
   tr->SetBranchAddress("DetectorMat", DetectorMat);
   tr->SetBranchAddress("EnergyDep", &EnergyDep);
   tr->SetBranchAddress("NumHitPrimary", &NumHitPrimary);

   //     This is the loop skeleton
   //       To read only selected branches, Insert statements like:
   // tr->SetBranchStatus("*",0);  // disable all branches
   // TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = tr->GetEntries();

   TH1F *hEDep = new TH1F("hEDep", "EnergyDep", gammaEnergy + 101, 0, gammaEnergy + 100);
   tr->Project("hEDep", "EnergyDep", "DetectorMat==\"Ge\"");

   unsigned int numIncident = hEDep->GetEntries();
   std::cout << "Efficiency/HPGe: " << numIncident / 4.0 / 1.0E7 * 100 << " %" << std::endl;
   double xlowPeak = gammaEnergy - 2.0;
   double xhiPeak = gammaEnergy + 2.0;

   int binlowPeak = hEDep->FindBin(xlowPeak);
   int binhiPeak = hEDep->FindBin(xhiPeak);
   int bin10keV = hEDep->FindBin(10.0);
   int bin1keV = hEDep->FindBin(1.0);

   unsigned int peakCount = hEDep->Integral(binlowPeak, binhiPeak);
   unsigned int comptonCount = hEDep->Integral(1, binlowPeak);
   unsigned int count10keV = hEDep->Integral(1, bin10keV);
   unsigned int count1keV = hEDep->Integral(1, bin1keV);

   std::cout << "Peak to Incident ratio: " << peakCount * 1.0 / numIncident << std::endl;
   std::cout << "Compton to Peak ratio: " << comptonCount * 1.0 / peakCount << std::endl;
   std::cout << "10keV to Peak ratio: " << count10keV * 1.0 / peakCount << std::endl;
   std::cout << "10keV to Compton ratio: " << count10keV * 1.0 / comptonCount << std::endl;
   std::cout << "10keV to Incident: " << count10keV * 1.0 / numIncident << std::endl;
   std::cout << "1keV to Incident: " << count1keV * 1.0 / numIncident << std::endl;

   //////////////////////////////////////////////////////////////////////////////
   /// SORTING
   //////////////////////////////////////////////////////////////////////////////

   std::cout << "Now sorting: " << nentries << " entries in order of EventNum"
             << std::endl;

   tr->BuildIndex("EvNo");
   TTreeIndex *index = (TTreeIndex *)tr->GetTreeIndex();
   if (!index)
   {
      std::cerr << "Error creating tree index!" << std::endl;
      gROOT->ProcessLine(".q");
      return 1;
   }
   Long64_t *indices = index->GetIndex();
   if (!indices)
   {
      std::cerr << "Error retrieving index array!" << std::endl;
      gROOT->ProcessLine(".q");
      return 1;
   }

   std::cout << "sorting done" << std::endl;

   Long64_t nbytes = 0;
   int Event = 0;
   TH1F *hEDepAC = new TH1F("hEDepAntiCompton", "EnergyDepAntiCompton", 650, 0, 650);
   std::map<std::string, double> Energy_Deposition;
   for (Long64_t i = 0; i < nentries; i++)
   {
      nbytes += tr->GetEntry(indices[i]);
      // std::cout << i << "," << indices[i] << "," << EvNo << "," << Event << std::endl;
      if (EvNo == Event)
      {
         if (strcmp(DetectorMat, "Ge") == 0 and EnergyDep >= 0.21 and EnergyDep < 600.0)
         {
            Energy_Deposition["Ge"] = EnergyDep;
         }
         if (strcmp(DetectorMat, "NaI") == 0 and EnergyDep >= 20)
         {
            Energy_Deposition["NaI"] = EnergyDep;
         }
      }
      else
      {
         // for (const auto &entry : Energy_Deposition)
         // {
         //    std::cout << Event << ": " << entry.first << " => " << entry.second << std::endl;
         // }

         if (Energy_Deposition.size() == 1 and Energy_Deposition.begin()->first == "Ge")
         {
            // for (const auto &entry : Energy_Deposition)
            // {
            //    std::cout << Event << ": " << entry.first << " => " << Energy_Deposition.begin()->second << std::endl;
            // }
            hEDepAC->Fill(Energy_Deposition.begin()->second);
         }

         Event = EvNo;
         Energy_Deposition.clear();
         if (strcmp(DetectorMat, "Ge") == 0 and EnergyDep >= 0.21 and EnergyDep < 600.0)
         {
            Energy_Deposition["Ge"] = EnergyDep;
         }
         if (strcmp(DetectorMat, "NaI") == 0 and EnergyDep >= 20)
         {
            Energy_Deposition["NaI"] = EnergyDep;
         }
      }
   }
   TFile outFile("output_histograms_600keVcut.root", "RECREATE");
   hEDep->Write();
   hEDepAC->Write();
   outFile.Close();
   return 0;
}
