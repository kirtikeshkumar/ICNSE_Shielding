//////////////////////////////////////////////////////////
//   This file has been automatically generated
//     (Sun Jun  8 10:18:57 2025 by ROOT version6.32.02)
//   from TTree EventColl/EventColl
//   found on file: output_DetEff_gamma_3600keV_10000000evt.root
//////////////////////////////////////////////////////////
#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "TTree.h"
#include "TTreeIndex.h"
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>

namespace fs = std::filesystem;

struct EventEDep {
  std::string Material;
  int copy;
  double EDep;
};

int extractEnergy(const std::string &filename) {
  std::smatch match;
  std::regex pattern(R"(.*_gamma_(\d+)keV_.*\.root)");
  if (std::regex_match(filename, match, pattern)) {
    return std::stoi(match[1]);
  }
  return -1; // Invalid or not matched
}

int EventColl(const char *folderPath = "outputs/DetEff/gamma") {

  std::vector<double> gamEnergy, GeTotal, GeEff, GePeakToIncident,
      GePeakToCompton, Ge10keVToTotalIncident, Ge1keVToTotalIncident,
      Ge10keVToTotal, Ge1keVToTotal;
  std::vector<double> Ge10keV_AC_13NaI, Ge10keV_AC_1NaI, Ge10keV_AC_4NaI,
      Ge10keV_AC_5NaI, Ge10keV_AC_8NaI, Ge10keV_AC_9NaI;
  std::vector<double> Ge1keV_AC_13NaI, Ge1keV_AC_1NaI, Ge1keV_AC_4NaI,
      Ge1keV_AC_5NaI, Ge1keV_AC_8NaI, Ge1keV_AC_9NaI;

  std::vector<std::string> rootFiles;
  for (const auto &entry : fs::directory_iterator(folderPath)) {
    if (!entry.is_regular_file())
      continue;

    std::string fullPath = entry.path().string();
    std::string filename = entry.path().filename().string();
    if (filename.size() >= 5 &&
        filename.substr(filename.size() - 5) == ".root") {
      rootFiles.push_back(entry.path().string()); // Full path
    }
  }

  // Step 2: Sort the filenames in increasing energy
  std::sort(rootFiles.begin(), rootFiles.end(),
            [](const std::string &a, const std::string &b) {
              return extractEnergy(a) < extractEnergy(b);
            });

  for (const auto &filename : rootFiles) {
    std::cout << "opening file: " << filename << std::endl;
    // Reset ROOT and connect tree file
    gROOT->Reset();

    TFile *f = new TFile(filename.c_str(), "r");
    TTree *tr = (TTree *)f->Get("EventColl");

    std::smatch match;
    std::regex numRuns_pattern("_(\\d+)evt");
    if (!std::regex_search(filename, match, numRuns_pattern)) {
      std::cerr << "Filename doesn't match numRuns pattern: " << filename
                << std::endl;
      return 1;
    }

    int numRuns = std::stoi(match[1]);
    // std::cout << "numRuns: " << numRuns << std::endl;

    std::regex energy_pattern("gamma_(\\d+)keV");
    if (!std::regex_search(filename, match, energy_pattern)) {
      std::cerr << "Filename doesn't match energy pattern: " << filename
                << std::endl;
      return 1;
    }

    int gammaEnergy = std::stoi(match[1]);
    // std::cout << "Gamma Energy: " << gammaEnergy << std::endl;
    gamEnergy.push_back(gammaEnergy);

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

    TH1F *hEDep =
        new TH1F("hEDep", "EnergyDep", gammaEnergy + 101, 0, gammaEnergy + 100);
    tr->Project("hEDep", "EnergyDep", "DetectorMat==\"Ge\"");

    unsigned int numIncident = hEDep->GetEntries();
    // std::cout << "Efficiency/HPGe: " << numIncident / 4.0 / 1.0E7 * 100 << "
    // %"  << std::endl;
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
    int count10keV_1NaI_AC, count10keV_4NaI_AC, count10keV_5NaI_AC,
        count10keV_8NaI_AC, count10keV_9NaI_AC, count10keV_13NaI_AC;
    int count1keV_1NaI_AC, count1keV_4NaI_AC, count1keV_5NaI_AC,
        count1keV_8NaI_AC, count1keV_9NaI_AC, count1keV_13NaI_AC;

    // std::cout << "Peak to Incident ratio: " << peakCount * 1.0 / numIncident
    //           << std::endl;
    // std::cout << "Compton to Peak ratio: " << comptonCount * 1.0 / peakCount
    //           << std::endl;
    // std::cout << "10keV to Peak ratio: " << count10keV * 1.0 / peakCount
    //           << std::endl;
    // std::cout << "10keV to Compton ratio: " << count10keV * 1.0 /
    // comptonCount
    //           << std::endl;
    // std::cout << "10keV to Incident: " << count10keV * 1.0 / numIncident
    //           << std::endl;
    // std::cout << "1keV to Incident: " << count1keV * 1.0 / numIncident
    //           << std::endl;

    GeTotal.push_back(numIncident);
    GeEff.push_back(numIncident / 4.0 / numRuns * 100);
    Ge10keVToTotal.push_back(count10keV * 1.0 / numRuns);
    Ge1keVToTotal.push_back(count1keV * 1.0 / numRuns);
    if (numIncident != 0) {
      GePeakToIncident.push_back(peakCount * 1.0 / numIncident);
      GePeakToCompton.push_back(comptonCount * 1.0 / peakCount);
      Ge10keVToTotalIncident.push_back(count10keV * 1.0 / numIncident);
      Ge1keVToTotalIncident.push_back(count1keV * 1.0 / numIncident);
    } else {
      GePeakToIncident.push_back(0.);
      GePeakToCompton.push_back(0.);
      Ge10keVToTotalIncident.push_back(0.);
      Ge1keVToTotalIncident.push_back(0.);
    }

    //////////////////////////////////////////////////////////////////////////////
    /// SORTING
    //////////////////////////////////////////////////////////////////////////////

    // std::cout << "Now sorting: " << nentries << " entries in order of
    // EventNum" << std::endl;

    tr->BuildIndex("EvNo");
    TTreeIndex *index = (TTreeIndex *)tr->GetTreeIndex();
    if (!index) {
      std::cerr << "Error creating tree index!" << std::endl;
      gROOT->ProcessLine(".q");
      return 1;
    }
    Long64_t *indices = index->GetIndex();
    if (!indices) {
      std::cerr << "Error retrieving index array!" << std::endl;
      gROOT->ProcessLine(".q");
      return 1;
    }

    // std::cout << "sorting done" << std::endl;

    Long64_t nbytes = 0;
    int Event = 0;
    TH1F *hEDepAC_1NaI = new TH1F("hEDepAntiCompton_1NaI",
                                  "EnergyDepAntiCompton_1NaI", 650, 0, 650);
    TH1F *hEDepAC_4NaI = new TH1F("hEDepAntiCompton_4NaI",
                                  "EnergyDepAntiCompton_4NaI", 650, 0, 650);
    TH1F *hEDepAC_5NaI = new TH1F("hEDepAntiCompton_5NaI",
                                  "EnergyDepAntiCompton_5NaI", 650, 0, 650);
    TH1F *hEDepAC_8NaI = new TH1F("hEDepAntiCompton_8NaI",
                                  "EnergyDepAntiCompton_8NaI", 650, 0, 650);
    TH1F *hEDepAC_9NaI = new TH1F("hEDepAntiCompton_9NaI",
                                  "EnergyDepAntiCompton_9NaI", 650, 0, 650);
    TH1F *hEDepAC_13NaI = new TH1F("hEDepAntiCompton_13NaI",
                                   "EnergyDepAntiCompton_13NaI", 650, 0, 650);
    std::list<EventEDep> Energy_Deposition;
    for (Long64_t i = 0; i < nentries; i++) {
      nbytes += tr->GetEntry(indices[i]);
      // std::cout << i << "," << indices[i] << "," << EvNo << "," << Event <<
      // std::endl;
      if (EvNo == Event) {
        if (strcmp(DetectorMat, "Ge") == 0 and EnergyDep >= 0.21 and
            EnergyDep < 600.0) {
          Energy_Deposition.push_back({DetectorMat, Copy, EnergyDep});
        }
        if (strcmp(DetectorMat, "NaI") == 0 and EnergyDep >= 20) {
          Energy_Deposition.push_back({DetectorMat, Copy, EnergyDep});
        }
      } else {

        if (Energy_Deposition.size() == 1 and
            Energy_Deposition.front().Material == "Ge") {
          hEDepAC_13NaI->Fill(Energy_Deposition.front().EDep);
          hEDepAC_1NaI->Fill(Energy_Deposition.front().EDep);
          hEDepAC_4NaI->Fill(Energy_Deposition.front().EDep);
          hEDepAC_5NaI->Fill(Energy_Deposition.front().EDep);
          hEDepAC_8NaI->Fill(Energy_Deposition.front().EDep);
          hEDepAC_9NaI->Fill(Energy_Deposition.front().EDep);
          // for (const auto &entry : Energy_Deposition) {
          //   std::cout << Event << ": " << entry.Material << "[" << entry.copy
          //             << "] => " << entry.EDep << std::endl;
          // }
        } else if (Energy_Deposition.size() != 1) {
          //   for (const auto &entry : Energy_Deposition) {
          //     std::cout << Event << ": " << entry.Material << "[" <<
          //     entry.copy
          //               << "] => " << entry.EDep << std::endl;
          //   }
          int geCount = 0;
          double edepGe;
          bool otherCopy_1NaI = true, otherCopy_4NaI = true,
               otherCopy_5NaI = true, otherCopy_8NaI = true,
               otherCopy_9NaI = true;
          for (const auto &entry : Energy_Deposition) {
            if (entry.Material == "Ge") {
              ++geCount;
              edepGe = entry.EDep;
            } else {
              if (entry.copy == 120) {
                otherCopy_1NaI = false;
              }
              if (entry.copy >= 129) {
                otherCopy_4NaI = false;
              }
              if (entry.copy >= 129 or entry.copy == 120) {
                otherCopy_5NaI = false;
              }
              if (entry.copy < 129 and entry.copy > 120) {
                otherCopy_8NaI = false;
              }
              if (entry.copy < 129 and entry.copy >= 120) {
                otherCopy_9NaI = false;
              }
            }
          }
          if (geCount == 1 and otherCopy_1NaI) {
            hEDepAC_1NaI->Fill(edepGe);
          }
          if (geCount == 1 and otherCopy_4NaI) {
            hEDepAC_4NaI->Fill(edepGe);
          }
          if (geCount == 1 and otherCopy_5NaI) {
            hEDepAC_5NaI->Fill(edepGe);
          }
          if (geCount == 1 and otherCopy_8NaI) {
            hEDepAC_8NaI->Fill(edepGe);
          }
          if (geCount == 1 and otherCopy_9NaI) {
            hEDepAC_9NaI->Fill(edepGe);
          }
        }

        Event = EvNo;
        Energy_Deposition.clear();
        if (strcmp(DetectorMat, "Ge") == 0 and EnergyDep >= 0.21 and
            EnergyDep < 600.0) {
          Energy_Deposition.push_back({DetectorMat, Copy, EnergyDep});
        }
        if (strcmp(DetectorMat, "NaI") == 0 and EnergyDep >= 20) {
          Energy_Deposition.push_back({DetectorMat, Copy, EnergyDep});
        }
      }
    }

    count10keV_1NaI_AC = hEDepAC_1NaI->Integral(1, hEDepAC_1NaI->FindBin(10.));
    count10keV_4NaI_AC = hEDepAC_4NaI->Integral(1, hEDepAC_4NaI->FindBin(10.));
    count10keV_5NaI_AC = hEDepAC_5NaI->Integral(1, hEDepAC_5NaI->FindBin(10.));
    count10keV_8NaI_AC = hEDepAC_8NaI->Integral(1, hEDepAC_8NaI->FindBin(10.));
    count10keV_9NaI_AC = hEDepAC_9NaI->Integral(1, hEDepAC_9NaI->FindBin(10.));
    count10keV_13NaI_AC =
        hEDepAC_13NaI->Integral(1, hEDepAC_13NaI->FindBin(10.));

    count1keV_1NaI_AC = hEDepAC_1NaI->Integral(1, hEDepAC_1NaI->FindBin(1.));
    count1keV_4NaI_AC = hEDepAC_4NaI->Integral(1, hEDepAC_4NaI->FindBin(1.));
    count1keV_5NaI_AC = hEDepAC_5NaI->Integral(1, hEDepAC_5NaI->FindBin(1.));
    count1keV_8NaI_AC = hEDepAC_8NaI->Integral(1, hEDepAC_8NaI->FindBin(1.));
    count1keV_9NaI_AC = hEDepAC_9NaI->Integral(1, hEDepAC_9NaI->FindBin(1.));
    count1keV_13NaI_AC = hEDepAC_13NaI->Integral(1, hEDepAC_13NaI->FindBin(1.));

    // std::cout << "1NaI: " << count1keV_1NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_1NaI_AC * 1.0 / count10keV << std::endl;
    // std::cout << "4NaI: " << count1keV_4NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_4NaI_AC * 1.0 / count10keV << std::endl;
    // std::cout << "5NaI: " << count1keV_5NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_5NaI_AC * 1.0 / count10keV << std::endl;
    // std::cout << "8NaI: " << count1keV_8NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_8NaI_AC * 1.0 / count10keV << std::endl;
    // std::cout << "9NaI: " << count1keV_9NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_9NaI_AC * 1.0 / count10keV << std::endl;
    // std::cout << "13NaI: " << count1keV_13NaI_AC * 1.0 / count1keV << " : "
    //           << count10keV_13NaI_AC * 1.0 / count10keV << std::endl;

    if (count10keV) {
      Ge10keV_AC_13NaI.push_back(count10keV_13NaI_AC * 1.0 / count10keV);
      Ge10keV_AC_1NaI.push_back(count10keV_1NaI_AC * 1.0 / count10keV);
      Ge10keV_AC_4NaI.push_back(count10keV_4NaI_AC * 1.0 / count10keV);
      Ge10keV_AC_5NaI.push_back(count10keV_5NaI_AC * 1.0 / count10keV);
      Ge10keV_AC_8NaI.push_back(count10keV_8NaI_AC * 1.0 / count10keV);
      Ge10keV_AC_9NaI.push_back(count10keV_9NaI_AC * 1.0 / count10keV);
    } else {
      Ge10keV_AC_13NaI.push_back(0.);
      Ge10keV_AC_1NaI.push_back(0.);
      Ge10keV_AC_4NaI.push_back(0.);
      Ge10keV_AC_5NaI.push_back(0.);
      Ge10keV_AC_8NaI.push_back(0.);
      Ge10keV_AC_9NaI.push_back(0.);
    }
    if (count1keV) {
      Ge1keV_AC_13NaI.push_back(count1keV_13NaI_AC * 1.0 / count1keV);
      Ge1keV_AC_1NaI.push_back(count1keV_1NaI_AC * 1.0 / count1keV);
      Ge1keV_AC_4NaI.push_back(count1keV_4NaI_AC * 1.0 / count1keV);
      Ge1keV_AC_5NaI.push_back(count1keV_5NaI_AC * 1.0 / count1keV);
      Ge1keV_AC_8NaI.push_back(count1keV_8NaI_AC * 1.0 / count1keV);
      Ge1keV_AC_9NaI.push_back(count1keV_9NaI_AC * 1.0 / count1keV);
    } else {
      Ge1keV_AC_13NaI.push_back(0.);
      Ge1keV_AC_1NaI.push_back(0.);
      Ge1keV_AC_4NaI.push_back(0.);
      Ge1keV_AC_5NaI.push_back(0.);
      Ge1keV_AC_8NaI.push_back(0.);
      Ge1keV_AC_9NaI.push_back(0.);
    }

    std::string outfilename =
        "outputs/DetEff/gamma/hists/output_histograms_600keVcut_gamma_" +
        std::to_string(gammaEnergy) + ".root";
    TFile outFile(outfilename.c_str(), "RECREATE");
    hEDep->Write();
    hEDepAC_13NaI->Write();
    hEDepAC_1NaI->Write();
    hEDepAC_4NaI->Write();
    hEDepAC_5NaI->Write();
    hEDepAC_8NaI->Write();
    hEDepAC_9NaI->Write();
    outFile.Close();
    f->Close();
  }

  TGraph *graphTotalIncident =
      new TGraph(gamEnergy.size(), gamEnergy.data(), GeTotal.data());
  TGraph *graphEfficiency =
      new TGraph(gamEnergy.size(), gamEnergy.data(), GeEff.data());
  TGraph *graphPeakToIncident =
      new TGraph(gamEnergy.size(), gamEnergy.data(), GePeakToIncident.data());
  TGraph *graphPeakToCompton =
      new TGraph(gamEnergy.size(), gamEnergy.data(), GePeakToCompton.data());
  TGraph *graph10keVToIncident = new TGraph(gamEnergy.size(), gamEnergy.data(),
                                            Ge10keVToTotalIncident.data());
  TGraph *graph1keVToIncident = new TGraph(gamEnergy.size(), gamEnergy.data(),
                                           Ge1keVToTotalIncident.data());
  TGraph *graph10keVToTotal =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keVToTotal.data());
  TGraph *graph1keVToTotal =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keVToTotal.data());

  TSpline3 *splineTotalIncident =
      new TSpline3("splineTotalIncident", graphTotalIncident);
  TSpline3 *splineEfficiency =
      new TSpline3("splineEfficiency", graphEfficiency);
  TSpline3 *splinePeakToIncident =
      new TSpline3("splinePeakToIncident", graphPeakToIncident);
  TSpline3 *splinePeakToCompton =
      new TSpline3("splinePeakToCompton", graphPeakToCompton);
  TSpline3 *spline10keVToIncident =
      new TSpline3("spline10keVToIncident", graph10keVToIncident);
  TSpline3 *spline1keVToIncident =
      new TSpline3("spline1keVToIncident", graph1keVToIncident);
  TSpline3 *spline10keVToTotal =
      new TSpline3("spline10keVToTotal", graph10keVToTotal);
  TSpline3 *spline1keVToTotal =
      new TSpline3("spline1keVToTotal", graph1keVToTotal);

  TGraph *graph10keV_AC_13NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_13NaI.data());
  TGraph *graph10keV_AC_1NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_1NaI.data());
  TGraph *graph10keV_AC_4NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_4NaI.data());
  TGraph *graph10keV_AC_5NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_5NaI.data());
  TGraph *graph10keV_AC_8NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_8NaI.data());
  TGraph *graph10keV_AC_9NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge10keV_AC_9NaI.data());

  TSpline3 *spline10keV_AC_13NaI =
      new TSpline3("spline10keV_AC_13NaI", graph10keV_AC_13NaI);
  TSpline3 *spline10keV_AC_1NaI =
      new TSpline3("spline10keV_AC_1NaI", graph10keV_AC_1NaI);
  TSpline3 *spline10keV_AC_4NaI =
      new TSpline3("spline10keV_AC_4NaI", graph10keV_AC_4NaI);
  TSpline3 *spline10keV_AC_5NaI =
      new TSpline3("spline10keV_AC_5NaI", graph10keV_AC_5NaI);
  TSpline3 *spline10keV_AC_8NaI =
      new TSpline3("spline10keV_AC_8NaI", graph10keV_AC_8NaI);
  TSpline3 *spline10keV_AC_9NaI =
      new TSpline3("spline10keV_AC_9NaI", graph10keV_AC_9NaI);

  TGraph *graph1keV_AC_13NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_13NaI.data());
  TGraph *graph1keV_AC_1NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_1NaI.data());
  TGraph *graph1keV_AC_4NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_4NaI.data());
  TGraph *graph1keV_AC_5NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_5NaI.data());
  TGraph *graph1keV_AC_8NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_8NaI.data());
  TGraph *graph1keV_AC_9NaI =
      new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_9NaI.data());

  TSpline3 *spline1keV_AC_13NaI =
      new TSpline3("spline1keV_AC_13NaI", graph1keV_AC_13NaI);
  TSpline3 *spline1keV_AC_1NaI =
      new TSpline3("spline1keV_AC_1NaI", graph1keV_AC_1NaI);
  TSpline3 *spline1keV_AC_4NaI =
      new TSpline3("spline1keV_AC_4NaI", graph1keV_AC_4NaI);
  TSpline3 *spline1keV_AC_5NaI =
      new TSpline3("spline1keV_AC_5NaI", graph1keV_AC_5NaI);
  TSpline3 *spline1keV_AC_8NaI =
      new TSpline3("spline1keV_AC_8NaI", graph1keV_AC_8NaI);
  TSpline3 *spline1keV_AC_9NaI =
      new TSpline3("spline1keV_AC_9NaI", graph1keV_AC_9NaI);

  // TGraph *graph1keV_AC_13NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_13NaI.data());
  // TGraph *graph1keV_AC_1NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_1NaI.data());
  // TGraph *graph1keV_AC_4NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_4NaI.data());
  // TGraph *graph1keV_AC_5NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_5NaI.data());
  // TGraph *graph1keV_AC_8NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_8NaI.data());
  // TGraph *graph1keV_AC_9NaI =
  //     new TGraph(gamEnergy.size(), gamEnergy.data(), Ge1keV_AC_9NaI.data());

  std::string splineFileName =
      std::string(folderPath) + "/Results/splines.root";

  TFile *fileSplines = new TFile(splineFileName.c_str(), "RECREATE");

  splineTotalIncident->Write("splineTotalIncident");
  splineEfficiency->Write("splineEfficiency");
  splinePeakToIncident->Write("splinePeakToIncident");
  splinePeakToCompton->Write("splinePeakToCompton");
  spline10keVToIncident->Write("spline10keVToIncident");
  spline1keVToIncident->Write("spline1keVToIncident");
  spline10keVToTotal->Write("spline10keVToTotal");
  spline1keVToTotal->Write("spline1keVToTotal");

  spline10keV_AC_13NaI->Write("spline10keV_AC_13NaI");
  spline10keV_AC_1NaI->Write("spline10keV_AC_1NaI");
  spline10keV_AC_4NaI->Write("spline10keV_AC_4NaI");
  spline10keV_AC_5NaI->Write("spline10keV_AC_5NaI");
  spline10keV_AC_8NaI->Write("spline10keV_AC_8NaI");
  spline10keV_AC_9NaI->Write("spline10keV_AC_9NaI");

  spline1keV_AC_13NaI->Write("spline1keV_AC_13NaI");
  spline1keV_AC_1NaI->Write("spline1keV_AC_1NaI");
  spline1keV_AC_4NaI->Write("spline1keV_AC_4NaI");
  spline1keV_AC_5NaI->Write("spline1keV_AC_5NaI");
  spline1keV_AC_8NaI->Write("spline1keV_AC_8NaI");
  spline1keV_AC_9NaI->Write("spline1keV_AC_9NaI");

  fileSplines->Close();

  std::string graphFileName = std::string(folderPath) + "/Results/graphs.root";

  TFile *filegraphs = new TFile(graphFileName.c_str(), "RECREATE");
  graphTotalIncident->Write("graphTotalIncident");
  graphEfficiency->Write("graphEfficiency");
  graphPeakToIncident->Write("graphPeakToIncident");
  graphPeakToCompton->Write("graphPeakToCompton");
  graph10keVToIncident->Write("graph10keVToIncident");
  graph1keVToIncident->Write("graph1keVToIncident");
  graph10keVToTotal->Write("graph10keVToTotal");
  graph1keVToTotal->Write("graph1keVToTotal");

  graph10keV_AC_13NaI->Write("graph10keV_AC_13NaI");
  graph10keV_AC_1NaI->Write("graph10keV_AC_1NaI");
  graph10keV_AC_4NaI->Write("graph10keV_AC_4NaI");
  graph10keV_AC_5NaI->Write("graph10keV_AC_5NaI");
  graph10keV_AC_8NaI->Write("graph10keV_AC_8NaI");
  graph10keV_AC_9NaI->Write("graph10keV_AC_9NaI");

  graph1keV_AC_13NaI->Write("graph1keV_AC_13NaI");
  graph1keV_AC_1NaI->Write("graph1keV_AC_1NaI");
  graph1keV_AC_4NaI->Write("graph1keV_AC_4NaI");
  graph1keV_AC_5NaI->Write("graph1keV_AC_5NaI");
  graph1keV_AC_8NaI->Write("graph1keV_AC_8NaI");
  graph1keV_AC_9NaI->Write("graph1keV_AC_9NaI");

  filegraphs->Close();

  return 0;
}
