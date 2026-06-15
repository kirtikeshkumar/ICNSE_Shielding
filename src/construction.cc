/*This is the main construction file where we assign all the attributes of the
 * detector and the environment and the material of the detector*/

// Including the construction header file
#include "construction.hh"
#include "G4Exception.hh"
#include <G4LogicalVolume.hh>
#include <string>

// In the constructor function we use std::cin to take the dimensions of the
// environment and the detector along with the position of the detector as user
// input
MyDetectorConstruction::MyDetectorConstruction()
{
    DefineMaterials();
    std::cout << "***********************************" << std::endl;
    std::cout << "Constructor Called" << std::endl;
    // width.push_back(2.0 * cm);
    // shieldmats = "HDPE";

    // fMessenger =
    //     new G4GenericMessenger(this, "/detector/", "Shield Layer
    //     Construction");

    // fMessenger->DeclareProperty("width", wdth, "Thickness of Shield");
    // fMessenger->DeclareProperty("shieldMat", shieldmats, "Shield Material");

    // fMessenger->DeclareProperty("Configuration", ConfigNum, "Configuration of
    // Detectors");

    sdManager = G4SDManager::GetSDMpointer();

    xWorld = 10. * m;
    yWorld = 10. * m;
    zWorld = 10. * m;

    // xloc = 0.09 * m;

    // MatMap["HDPE"] = HDPE;
    // MatMap["BP"] = BoratedPE;
    // MatMap["Pb"] = Lead;
    // MatMap["Cu"] = Copper;
    // MatMap["SS"] = Steel;
}

MyDetectorConstruction::MyDetectorConstruction(std::string mat,
                                               std::string th)
{
    DefineMaterials();

    xWorld = 10. * m;
    yWorld = 10. * m;
    zWorld = 10. * m;

    // xloc = 0.09 * m;

    // MatMap["H"] = HDPE;
    // MatMap["B"] = BoratedPE;
    // MatMap["L"] = Lead;
    // MatMap["C"] = Copper;

    // shieldmats += mat;
    // for (int ijk = 0; ijk < shieldmats.length(); ijk++) {
    //   G4String key(1, shieldmats[ijk]);
    //   shieldMats.push_back(key);
    // }

    // std::istringstream iss(th);
    // std::string token;
    // netWidth = 0;
    // while (std::getline(iss, token, ' ')) {
    //   width.push_back(std::stof(token)); // convert to float
    //   netWidth += std::stof(token);
    // }
}

// The destructor function
MyDetectorConstruction::~MyDetectorConstruction() {}

void MyDetectorConstruction::DefineMaterials()
{
    // G4NistManager to get the required elements
    G4NistManager *nist = G4NistManager::Instance();

    // Here we define the material of our detector. Here we are using Aerogel as
    // our 		detector material which is made up of a mixture of
    // SiO2,H2O and Carbon
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    myTolueneMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    Vaccum = nist->FindOrBuildMaterial("G4_Galactic");

    G4double fractionmass;
    // Borated Poly-ethylene 30
    BoratedPE = new G4Material("BoratedPE", 1.04 * g / cm3, 2);
    BoratedPE->AddMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"),
                           fractionmass = 95. * perCent);
    BoratedPE->AddElement(nist->FindOrBuildElement("B"),
                          fractionmass = 5. * perCent);

    HDPE = new G4Material("HDPE", 0.97 * g / cm3, 1);
    HDPE->AddMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"),
                      100. * perCent);
    NaI = new G4Material("NaI", 3.667 * g / cm3, 1);
    NaI->AddMaterial(nist->FindOrBuildMaterial("G4_SODIUM_IODIDE"),
                     100. * perCent);

    Lead = new G4Material("Pb", 11.4 * g / cm3, 1);
    Lead->AddElement(nist->FindOrBuildElement("Pb"), 100. * perCent);
    //   G4Isotope *Pb210 = new G4Isotope("Pb210", 82, 210, 209.984 * g / mole);
    //   G4Element *elPb210 = new G4Element("Lead210", "Pb210", 1);
    //   elPb210->AddIsotope(Pb210, 100. * perCent);
    //   Lead->AddElement(elPb210, 10. * perCent);

    Copper = new G4Material("Cu", 8.96 * g / cm3, 1);
    Copper->AddMaterial(nist->FindOrBuildMaterial("G4_Cu"), 100. * perCent);
    Mat_Ge = new G4Material("Ge", 5.323 * g / cm3, 1);
    Mat_Ge->AddMaterial(nist->FindOrBuildMaterial("G4_Ge"), 100. * perCent);
    Mat_Al = new G4Material("Al", 2.7 * g / cm3, 1);
    Mat_Al->AddMaterial(nist->FindOrBuildMaterial("G4_Al"), 100. * perCent);
    Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    // Defining the refractive index of the Aerogel detector and the environment
    // so that 	  we can see the Cherenkov Light
    G4double energy[2] = {1.239841939 * eV / 0.9, 1.239841939 * eV / 0.2};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double rindexPVT[2] = {1.58, 1.58};

    G4double reflectivity[2] = {1.0, 1.0};

    G4double energy_spectrum[31] = {
        2.3884 * eV, 2.4523 * eV, 2.5240 * eV, 2.5945 * eV, 2.6358 * eV,
        2.6664 * eV, 2.7058 * eV, 2.7528 * eV, 2.7948 * eV, 2.8122 * eV,
        2.8337 * eV, 2.8414 * eV, 2.8491 * eV, 2.8743 * eV, 2.8995 * eV,
        2.9227 * eV, 2.9604 * eV, 2.9873 * eV, 3.0093 * eV, 3.0254 * eV,
        3.0494 * eV, 3.0995 * eV, 3.1235 * eV, 3.1503 * eV, 3.1862 * eV,
        3.2275 * eV, 3.2700 * eV, 3.3184 * eV, 3.3538 * eV, 3.4048 * eV,
        3.4474 * eV};
    G4double energy_fraction[31] = {
        0.0225734, 0.0539278, 0.0985471, 0.171136, 0.229339, 0.296938,
        0.395068, 0.489164, 0.579315, 0.641705, 0.745296, 0.82371,
        0.898134, 0.971118, 0.992241, 0.972151, 0.877506, 0.761649,
        0.676411, 0.56328, 0.427499, 0.249022, 0.18772, 0.146354,
        0.112922, 0.0821281, 0.0659618, 0.0484438, 0.0376407, 0.0281014,
        0.0279145};

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4double fraction[2] = {1.0, 1.0};
    G4double absorption[2] = {2.1 * m, 2.1 * m};

    G4MaterialPropertiesTable *mptPVT = new G4MaterialPropertiesTable();
    mptPVT->AddProperty("RINDEX", energy, rindexPVT, 2);
    mptPVT->AddProperty("SCINTILLATIONCOMPONENT1", energy_spectrum,
                        energy_fraction, 31);
    mptPVT->AddConstProperty("SCINTILLATIONYIELD", 11136 / MeV);
    mptPVT->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptPVT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1 * ns);
    mptPVT->AddConstProperty("SCINTILLATIONYIELD1", 1.);
    mptPVT->AddProperty("ABSLENGTH", energy, absorption, 2);

    myTolueneMat->SetMaterialPropertiesTable(mptPVT);

    mirrorSurface = new G4OpticalSurface("mirrorSurface");

    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
    mirrorSurface->SetMaterialPropertiesTable(mptMirror);
}

void MyDetectorConstruction::ConstructSingleSheet()
{

    //   Define the region where I want to measure the escaping particles as a box
    //   surrounding the sheet
    //
    //   detVol = ConstructShell(netWidth + 5, 155., 155, 2.5, 2.5);
    //   logicdetVol = new G4LogicalVolume(detVol, Vaccum, "logicdetVol");
    //   physdetVol = new G4PVPlacement(
    //       0, G4ThreeVector(xloc + 0.5 * (netWidth + 5) * cm, 0., 0.),
    //       logicdetVol, "physdetVol", logicWorld, false, 0, true);

    // Define the sheet

    for (int ij = 0; ij < shieldMats.size(); ij++)
    {
        // std::cout << std::endl << "xloc: " << xloc / cm << std::endl;
        float layerWidth = width[ij] * cm;
        xloc = xloc + 0.5 * layerWidth;
        // std::cout << "xloc: " << xloc / cm << ", layerWidth: " << layerWidth / cm
        //           << std::endl;
        G4Box *solid = new G4Box("solidSheet", 0.5 * layerWidth, 75 * cm, 75 * cm);
        solidSheet.push_back(solid);
        logic = new G4LogicalVolume(solidSheet[ij], MatMap[shieldMats[ij]],
                                    "logicSheet");
        logicSheet.push_back(logic);
        phys = new G4PVPlacement(0, G4ThreeVector(xloc, 0., 0.), logicSheet[ij],
                                 "physSheet", logicWorld, true, ij + 1, true);
        physSheet.push_back(phys);
        xloc = xloc + 0.5 * layerWidth;
        // std::cout << "xloc: " << xloc / cm << std::endl << std::endl;
    }

    //   Define the region where I want to measure the escaping particles as a box
    detVol = new G4Box("solidSheet", 0.1 * cm, 80 * cm, 80 * cm);
    logicdetVol = new G4LogicalVolume(detVol, Vaccum, "logicdetVol");
    physdetVol =
        new G4PVPlacement(0, G4ThreeVector(xloc + 0.1 * cm, 0., 0.), logicdetVol,
                          "physdetVol", logicWorld, false, 0, true);
}

G4VSolid *MyDetectorConstruction::ClosedHollowCylinder(double rin,
                                                       double thickness,
                                                       double halfHtIn)
{
    double rout = rin + thickness;
    G4VSolid *cylinder = new G4Tubs("Cylinder", rin * cm, rout * cm,
                                    halfHtIn * cm, 0 * deg, 360 * deg);
    G4VSolid *TopCap = new G4Tubs("TopCap", 0 * cm, rout * cm,
                                  (thickness / 2.0) * cm, 0 * deg, 360 * deg);
    G4VSolid *BotCap = new G4Tubs("BotCap", 0 * cm, rout * cm,
                                  (thickness / 2.0) * cm, 0 * deg, 360 * deg);
    G4VSolid *UnionTopCap = new G4UnionSolid(
        "UnionTopCap", cylinder, TopCap, 0,
        G4ThreeVector(0., 0., (halfHtIn + thickness / 2.0) * cm));
    G4VSolid *ClosedCyl = new G4UnionSolid(
        "ClosedCyl", UnionTopCap, BotCap, 0,
        G4ThreeVector(0., 0., -1.0 * (halfHtIn + thickness / 2.0) * cm));
    return ClosedCyl;
}

G4LogicalVolume *MyDetectorConstruction::ConstructNaI()
{
    solidNaI = new G4Tubs("NaICrystal", 0 * cm, 3.75 * cm, 3.75 * cm, 0 * deg,
                          360 * deg);
    G4LogicalVolume *logicNaI = new G4LogicalVolume(solidNaI, NaI, "logicNaI");
    return logicNaI;
}

void MyDetectorConstruction::ConstructDetectorSetup()
{
    // logicHPGe = ConstructHPGe();
    solidNaIClad = ClosedHollowCylinder(3.85, 0.15, 3.85);
    logicNaI = ConstructNaI();
    logicNaIClad = new G4LogicalVolume(solidNaIClad, Mat_Al, "logicNaIClad");

    physNaI.push_back(new G4PVPlacement(0, G4ThreeVector(0., -40. * cm, -15.5 * cm), logicNaI,
                                        "physNaI_0", logicWorld, true, 120,
                                        true));
    physNaI.push_back(
        new G4PVPlacement(0, G4ThreeVector(0., -20. * cm, -15.5 * cm), logicNaI,
                          "physNaI_1", logicWorld, true, 121, true));

    for (int iter = 0; iter < physNaI.size(); iter++)
    {
        int copy = 140 + iter;
        G4ThreeVector pos = physNaI[iter]->GetTranslation();
        std::string name = "physNaI_Clad_" + std::to_string(iter);
        physNaIClad.push_back(
            new G4PVPlacement(0, G4ThreeVector(pos.x(), pos.y(), pos.z()),
                              logicNaIClad, name, logicWorld, true, copy, true));
    }

    G4VSolid *boxout =
        new G4Box("Boxout", 0.5 * 50. * cm, 0.5 * 70. * cm, 0.5 * 45. * cm);
    G4VSolid *boxin =
        new G4Box("Boxin", 0.5 * 25. * cm, 0.5 * 50. * cm, 0.5 * 40. * cm);
    G4VSolid *Pb1 = new G4SubtractionSolid("physPb1", boxout, boxin, 0,
                                           G4ThreeVector(0., 0., 2.5 * cm));
    logicPb = new G4LogicalVolume(Pb1, Lead, "logicPb1");
    physPb1 = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicPb, "physPb1", logicWorld, false, 0, true);

    G4VSolid *boxout2 =
        new G4Box("Boxout2", 0.5 * 25. * cm, 0.5 * 50. * cm, 0.5 * 40. * cm);
    G4VSolid *boxin2 =
        new G4Box("Boxin2", 0.5 * 24.9 * cm, 0.5 * 49.9 * cm, 0.5 * 39.05 * cm);
    G4VSolid *Cu = new G4SubtractionSolid("physCu", boxout2, boxin2, 0,
                                          G4ThreeVector(0., 0., 0.25 * mm));
    logicCu = new G4LogicalVolume(Cu, Copper, "logicCu");
    physCu = new G4PVPlacement(0, G4ThreeVector(0., 0., 2.5), logicCu, "physCu", logicWorld, false, 0, true);
}

G4VSolid *MyDetectorConstruction::ConstructShell(double xsz, double ysz,
                                                 double zsz, double thickness,
                                                 double offset = 0.0)
{
    G4VSolid *boxout =
        new G4Box("Boxout", 0.5 * xsz * cm, 0.5 * ysz * cm, 0.5 * zsz * cm);
    G4VSolid *boxin =
        new G4Box("Boxin", (0.5 * xsz - thickness) * cm,
                  (0.5 * ysz - thickness) * cm, (0.5 * zsz - thickness) * cm);
    G4VSolid *shell =
        new G4SubtractionSolid("BoxOut-BoxIn", boxout, boxin, 0,
                               G4ThreeVector(-1.0 * offset * cm, 0., 0.));
    return shell;
}

// The Construct function where we define the material of the detector and
// define the physical and logical volume of the environment and detector.
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

    // The following part is for parsing the run.mac to get material and
    // thickness for singleSheets
    //
    // std::istringstream iss(wdth);
    // std::string token;
    // netWidth = 0;
    // width.clear();
    // shieldMats.clear();
    // while (std::getline(iss, token, '_')) {
    //   width.push_back(std::stof(token)); // convert to float
    //   netWidth += std::stof(token);
    // }
    // std::istringstream ist(shieldmats);
    // while (std::getline(ist, token, '_')) {
    //   shieldMats.push_back(token);
    // }
    // if (shieldMats.size() != width.size()) {
    //   G4Exception("MyDetectorConstruction::Construct()", "ConstructionError",
    //               FatalException,
    //               "Size of Material List and Widhts not same. Aborting.");
    // }

    // Defining the world environment
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    // logicWorld= new G4LogicalVolume(solidWorld,Vaccum,"logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld,
                                  "physWorld", 0, false, 100, true);

    // ConstructSingleSheet();
    ConstructDetectorSetup();

    // Finally we return the physWorld as output
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    sdManager->AddNewDetector(sensDet);
    logicNaI->SetSensitiveDetector(sensDet);
}
