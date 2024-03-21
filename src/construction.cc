/*This is the main construction file where we assign all the attributes of the detector and the environment and the material of the detector*/

//Including the construction header file
#include "construction.hh"
#include "detector.hh"

//In the constructor function we use std::cin to take the dimensions of the environment and the detector along with the position of the detector as user input
MyDetectorConstruction::MyDetectorConstruction()
{	 
	 DefineMaterials();
	 
	 xWorld = 5.*m;
	 yWorld = 5.*m;
	 zWorld = 5.*m;
	 
	 xloc = 0.9*m;
	 
	 LogicArrangement = {HDPE,HDPE,BoratedPE,BoratedPE,Lead,Lead,HDPE,HDPE};
}

MyDetectorConstruction::MyDetectorConstruction(std::string str)
{	 
	 DefineMaterials();
	 
	 xWorld = 5.*m;
	 yWorld = 5.*m;
	 zWorld = 5.*m;
	 
	 xloc = 0.9*m;
	 
	 MatMap['H'] = HDPE;
	 MatMap['B'] = BoratedPE;
	 MatMap['L'] = Lead;
	 
	 LogicArrangement.clear();
	 
	 for (char s : str){
		 if (MatMap.find(s) != MatMap.end()){  //if the character is mapped to a material
			 LogicArrangement.push_back(MatMap[s]);
		 }
	 }
	 
	 //for (G4Material* material : LogicArrangement) {
     //    G4cout << material->GetName() << " ";
     //}
}

//The destructor function
MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
	//G4NistManager to get the required elements
	G4NistManager *nist = G4NistManager::Instance();
	
	//Here we define the material of our detector. Here we are using Aerogel as our 		detector material which is made up of a mixture of SiO2,H2O and Carbon
	worldMat =nist->FindOrBuildMaterial("G4_AIR");
	myTolueneMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	Vaccum = nist->FindOrBuildMaterial("G4_Galactic");
	
	G4double fractionmass;
	//Borated Poly-ethylene 30
	BoratedPE = new G4Material("BoratedPE",1.04*g/cm3,2);
	BoratedPE->AddMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"),fractionmass=95.*perCent);
	BoratedPE->AddElement(nist->FindOrBuildElement("B"),fractionmass=5.*perCent);
	
	HDPE = new G4Material("HDPE",0.97*g/cm3,1);
	HDPE->AddMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"),100.*perCent);
	
	Lead = new G4Material("Pb",11.4*g/cm3,1);
	Lead->AddElement(nist->FindOrBuildElement("Pb"),100.*perCent);
	Copper = new G4Material("Cu",8.96*g/cm3,1);
	Copper->AddElement(nist->FindOrBuildElement("Cu"),100.*perCent);
	Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
	
	//Defining the refractive index of the Aerogel detector and the environment so that 	  we can see the Cherenkov Light
	G4double energy[2] ={1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexWorld[2] = {1.0, 1.0};
	G4double rindexPVT[2] = {1.58, 1.58};
	
	
	
	G4double reflectivity[2] = {1.0, 1.0};
	
	G4double energy_spectrum[31] = {2.3884*eV, 2.4523*eV, 2.5240*eV, 2.5945*eV, 2.6358*eV, 2.6664*eV, 2.7058*eV, 2.7528*eV, 2.7948*eV, 2.8122*eV, 2.8337*eV, 2.8414*eV, 2.8491*eV, 2.8743*eV, 2.8995*eV, 2.9227*eV, 2.9604*eV, 2.9873*eV, 3.0093*eV, 3.0254*eV, 3.0494*eV, 3.0995*eV, 3.1235*eV, 3.1503*eV, 3.1862*eV, 3.2275*eV, 3.2700*eV, 3.3184*eV, 3.3538*eV, 3.4048*eV, 3.4474*eV};
	G4double energy_fraction[31] = {0.0225734, 0.0539278, 0.0985471, 0.171136, 0.229339, 0.296938, 0.395068, 0.489164, 0.579315, 0.641705, 0.745296, 0.82371, 0.898134, 0.971118, 0.992241, 0.972151, 0.877506, 0.761649, 0.676411, 0.56328, 0.427499, 0.249022, 0.18772, 0.146354, 0.112922, 0.0821281, 0.0659618, 0.0484438, 0.0376407, 0.0281014, 0.0279145};
	
	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX",energy, rindexWorld, 2);	
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	G4double fraction[2]= {1.0,1.0};
	G4double absorption[2] = {2.1*m,2.1*m};
	
	G4MaterialPropertiesTable *mptPVT = new G4MaterialPropertiesTable();
	mptPVT->AddProperty("RINDEX",energy, rindexPVT, 2);
	mptPVT->AddProperty("SCINTILLATIONCOMPONENT1", energy_spectrum, energy_fraction, 31);
	mptPVT->AddConstProperty("SCINTILLATIONYIELD", 11136/MeV);
	mptPVT->AddConstProperty("RESOLUTIONSCALE", 1.0);
	mptPVT->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.1*ns);
	mptPVT->AddConstProperty("SCINTILLATIONYIELD1", 1.);
	mptPVT->AddProperty("ABSLENGTH", energy, absorption,2);
	
	myTolueneMat->SetMaterialPropertiesTable(mptPVT);
	
	mirrorSurface = new G4OpticalSurface("mirrorSurface");
	
	mirrorSurface->SetType(dielectric_metal);
	mirrorSurface->SetFinish(ground);
	mirrorSurface->SetModel(unified);
	
	G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
	mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);
	mirrorSurface->SetMaterialPropertiesTable(mptMirror);

}

void MyDetectorConstruction::ConstructSetup()
{	
	G4VSolid* shellMuVetoOut = ConstructShell(150.,150.,175.,4.,0.);
	G4VSolid* shellHDPEOuter = ConstructShell(142.,142.,167.,10.,0.);
	G4VSolid* shellBP = ConstructShell(122.,122.,147.,10.,0.);
	G4VSolid* shellLead = ConstructShell(102.,102.,127.,10.,0.);
	G4VSolid* shellHDPEInner = ConstructShell(82.,82.,107.,10.,0.);
	G4VSolid* shellMuVetoIn = ConstructShell(62.,62.,87.,4.,0.);
	G4VSolid* shellCuColdBox = ConstructShell(54.,54.,79.,2.,0.);
	detVol = new G4Box("Boxsensdet",25.*cm,25.*cm,37.5*cm);
	
	
	logicshellMuVetoOut = new G4LogicalVolume(shellMuVetoOut,myTolueneMat,"logicshellMuVetoOut");
	logicshellHDPEOuter = new G4LogicalVolume(shellHDPEOuter,HDPE,"logicshellHDPEOuter");
	logicshellBP 		= new G4LogicalVolume(shellBP,BoratedPE,"logicshellBP");
	logicshellLead 		= new G4LogicalVolume(shellLead,Lead,"logicshellLead");
	logicshellHDPEInner = new G4LogicalVolume(shellHDPEInner,HDPE,"logicshellHDPEInner");
	logicshellMuVetoIn 	= new G4LogicalVolume(shellMuVetoIn,myTolueneMat,"logicshellMuVetoIn");
	logicshellCuColdBox = new G4LogicalVolume(shellCuColdBox,Copper,"logicshellCuColdBox");
	logicdetVol			= new G4LogicalVolume(detVol,Vaccum,"logicdetVol");
	
	
	G4LogicalSkinSurface *skin1 = new G4LogicalSkinSurface("skin1", logicshellMuVetoOut, mirrorSurface);
	G4LogicalSkinSurface *skin2 = new G4LogicalSkinSurface("skin2", logicshellMuVetoIn, mirrorSurface);
	
	physshellMuVetoOut = new G4PVPlacement(0,G4ThreeVector(xloc,0.,4.), logicshellMuVetoOut,"physshellMuVetoOut",logicWorld,false,1,true);
	physshellHDPEOuter = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellHDPEOuter,"physshellHDPEOuter",logicWorld,false,2,true);
	physshellBP 	   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellBP,"physshellBP",logicWorld,false,3,true);
	physshellLead 	   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellLead,"physshellLead",logicWorld,false,4,true);
	physshellHDPEInner = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellHDPEInner,"physshellHDPEInner",logicWorld,false,5,true);
	physshellMuVetoIn  = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellMuVetoIn,"physshellMuVetoIn",logicWorld,false,6,true);
	physshellCuColdBox = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellCuColdBox,"physshellCuColdBox",logicWorld,false,7,true);
	physdetVol		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicdetVol,"physdetVol",logicWorld,false,0,true);
	
}

void MyDetectorConstruction::ConstructSetupMod()
{	
	G4VSolid* shellMuVetoOut = ConstructShell(150.,150.,175.,4.,0.);
	G4VSolid* shell0		 = ConstructShell(142.,142.,167.,5.,0.);
	G4VSolid* shell1		 = ConstructShell(132.,132.,157.,5.,0.);
	G4VSolid* shell2		 = ConstructShell(122.,122.,147.,5.,0.);
	G4VSolid* shell3		 = ConstructShell(112.,112.,137.,5.,0.);
	G4VSolid* shell4		 = ConstructShell(102.,102.,127.,5.,0.);
	G4VSolid* shell5		 = ConstructShell(92.,92.,117.,5.,0.);
	G4VSolid* shell6		 = ConstructShell(82.,82.,107.,5.,0.);
	G4VSolid* shell7		 = ConstructShell(72.,72.,97.,5.,0.);
	G4VSolid* shellMuVetoIn  = ConstructShell(62.,62.,87.,4.,0.);
	G4VSolid* shellCuColdBox = ConstructShell(54.,54.,79.,2.,0.);
	detVol = new G4Box("Boxsensdet",25.*cm,25.*cm,37.5*cm);
	
	std::vector<G4Material*> LogicArrangement = {HDPE,HDPE,BoratedPE,Lead,HDPE,BoratedPE,Lead,HDPE};
	//std::vector<G4Material*> LogicArrangement = {HDPE,HDPE,BoratedPE,BoratedPE,Lead,Lead,HDPE,HDPE};
	
	logicshellMuVetoOut = new G4LogicalVolume(shellMuVetoOut,myTolueneMat,"logicshellMuVetoOut");
	logicshell0		    = new G4LogicalVolume(shell0,LogicArrangement[0],"logicshell0");
	logicshell1		    = new G4LogicalVolume(shell1,LogicArrangement[1],"logicshell1");
	logicshell2		    = new G4LogicalVolume(shell2,LogicArrangement[2],"logicshell2");
	logicshell3		    = new G4LogicalVolume(shell3,LogicArrangement[3],"logicshell3");
	logicshell4		    = new G4LogicalVolume(shell4,LogicArrangement[4],"logicshell4");
	logicshell5		    = new G4LogicalVolume(shell5,LogicArrangement[5],"logicshell5");
	logicshell6		    = new G4LogicalVolume(shell6,LogicArrangement[6],"logicshell6");
	logicshell7		    = new G4LogicalVolume(shell7,LogicArrangement[7],"logicshell7");
	logicshellMuVetoIn 	= new G4LogicalVolume(shellMuVetoIn,myTolueneMat,"logicshellMuVetoIn");
	logicshellCuColdBox = new G4LogicalVolume(shellCuColdBox,Copper,"logicshellCuColdBox");
	logicdetVol			= new G4LogicalVolume(detVol,Vaccum,"logicdetVol");
	
	G4LogicalSkinSurface *skin1 = new G4LogicalSkinSurface("skin1", logicshellMuVetoOut, mirrorSurface);
	G4LogicalSkinSurface *skin2 = new G4LogicalSkinSurface("skin2", logicshellMuVetoIn, mirrorSurface);
	
	physshellMuVetoOut = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellMuVetoOut,"physshellMuVetoOut",logicWorld,false,1,true);
	physshell0 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell0,"physshell0",logicWorld,false,2,true);
	physshell1 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell1,"physshell1",logicWorld,false,3,true);
	physshell2		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell2,"physshell2",logicWorld,false,4,true);
	physshell3 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell3,"physshell3",logicWorld,false,5,true);
	physshell4    	   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell4,"physshell4",logicWorld,false,6,true);
	physshell5 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell5,"physshell5",logicWorld,false,7,true);
	physshell6 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell6,"physshell6",logicWorld,false,8,true);
	physshell7 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell7,"physshell7",logicWorld,false,9,true);
	physshellMuVetoIn  = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellMuVetoIn,"physshellMuVetoIn",logicWorld,false,10,true);
	physshellCuColdBox = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellCuColdBox,"physshellCuColdBox",logicWorld,false,11,true);
	physdetVol		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicdetVol,"physdetVol",logicWorld,false,0,true);
}

void MyDetectorConstruction::ConstructSetupV1()
{	
	G4ThreeVector shellMuVetoOutSz = G4ThreeVector(150.,150.,175.);
	G4ThreeVector shell0Sz = G4ThreeVector(142.,142.,167.);
	G4ThreeVector shell1Sz = G4ThreeVector(132.,132.,157.);
	G4ThreeVector shell2Sz = G4ThreeVector(122.,122.,147.);
	G4ThreeVector shell3Sz = G4ThreeVector(112.,112.,137.);
	G4ThreeVector shell4Sz = G4ThreeVector(102.,102.,127.);
	G4ThreeVector shell5Sz = G4ThreeVector(92.,92.,117.);
	G4ThreeVector shell6Sz = G4ThreeVector(82.,82.,107.);
	G4ThreeVector shell7Sz = G4ThreeVector(72.,72.,97.);
	G4ThreeVector shellMuVetoInSz  = G4ThreeVector(62.,62.,87.);
	G4ThreeVector shellCuColdBoxSz = G4ThreeVector(54.,54.,79.);
	G4ThreeVector SteelPlateSz     = G4ThreeVector(250.0, 200.0, 2.5);
	G4ThreeVector UnderSideBPSz    = G4ThreeVector(150.0, 150.0, 10.0);
	G4ThreeVector UnderSideHDPESz  = G4ThreeVector(150.0, 150.0, 10.0);
	
	
	//SubBoxSz is size of the box to be subtracted. the  x and y are to ensure complete subtraction, z is since 4cm of muveto, and 10cm each of HDPE and BP to be removed
	G4ThreeVector SubBoxSz = G4ThreeVector(151.,151.,24.);
	double zoffsetSubBox = -0.5*(shellMuVetoOutSz.z()-SubBoxSz.z());
	//zoffset determines the position the steel table is compared to center of table top part.
	//there is 0.5*shellMuVetoOutSz.z() extent of shellMuVetoOutSz below its center
	//from this SubBoxSz.z() is removed
	//the steelplate center is 0.5*SteelPlateSz below its surface hence the following formula
	double zoffset = 0.5*shellMuVetoOutSz.z() - SubBoxSz.z() + 0.5*SteelPlateSz.z(); 
	G4ThreeVector offsetSubBox = G4ThreeVector(0., 0., zoffsetSubBox*cm); 
	
	
	G4VSolid* shellMuVetoOut = SubtractBoxfrmShell(shellMuVetoOutSz, 4.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell0		 = SubtractBoxfrmShell(shell0Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell1		 = SubtractBoxfrmShell(shell1Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell2		 = SubtractBoxfrmShell(shell2Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell3		 = SubtractBoxfrmShell(shell3Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell4		 = SubtractBoxfrmShell(shell4Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell5		 = SubtractBoxfrmShell(shell5Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell6		 = SubtractBoxfrmShell(shell6Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shell7		 = SubtractBoxfrmShell(shell7Sz, 5.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shellMuVetoIn  = SubtractBoxfrmShell(shellMuVetoInSz, 4.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* shellCuColdBox = SubtractBoxfrmShell(shellCuColdBoxSz, 2.0, 0.0, SubBoxSz, offsetSubBox);
	G4VSolid* SteelPlate     = new G4Box("SteelPlate", 0.5*SteelPlateSz.x()*cm, 0.5*SteelPlateSz.y()*cm, 0.5*SteelPlateSz.z()*cm);
	G4VSolid* UnderSideBP    = new G4Box("UnderSideBP", 0.5*UnderSideBPSz.x()*cm, 0.5*UnderSideBPSz.y()*cm, 0.5*UnderSideBPSz.z()*cm);
	G4VSolid* UnderSideHDPE    = new G4Box("UnderSideHDPE", 0.5*UnderSideHDPESz.x()*cm, 0.5*UnderSideHDPESz.y()*cm, 0.5*UnderSideHDPESz.z()*cm);
	detVol = new G4Box("Boxsensdet", 25.*cm, 25.*cm, 37.5*cm);
	
	logicshellMuVetoOut = new G4LogicalVolume(shellMuVetoOut,myTolueneMat,"logicshellMuVetoOut");
	logicshell0		    = new G4LogicalVolume(shell0,LogicArrangement[0],"logicshell0");
	logicshell1		    = new G4LogicalVolume(shell1,LogicArrangement[1],"logicshell1");
	logicshell2		    = new G4LogicalVolume(shell2,LogicArrangement[2],"logicshell2");
	logicshell3		    = new G4LogicalVolume(shell3,LogicArrangement[3],"logicshell3");
	logicshell4		    = new G4LogicalVolume(shell4,LogicArrangement[4],"logicshell4");
	logicshell5		    = new G4LogicalVolume(shell5,LogicArrangement[5],"logicshell5");
	logicshell6		    = new G4LogicalVolume(shell6,LogicArrangement[6],"logicshell6");
	logicshell7		    = new G4LogicalVolume(shell7,LogicArrangement[7],"logicshell7");
	logicshellMuVetoIn 	= new G4LogicalVolume(shellMuVetoIn,myTolueneMat,"logicshellMuVetoIn");
	logicshellCuColdBox = new G4LogicalVolume(shellCuColdBox,Copper,"logicshellCuColdBox");
	logicSteelPlate		= new G4LogicalVolume(SteelPlate,Steel,"logicSteelPlate");
	logicUnderSideBP    = new G4LogicalVolume(UnderSideBP,BoratedPE,"logicUnderSideBP");
	logicUnderSideHDPE  = new G4LogicalVolume(UnderSideHDPE,HDPE,"logicUnderSideHDPE");
	logicdetVol			= new G4LogicalVolume(detVol,Vaccum,"logicdetVol");
	
	G4LogicalSkinSurface *skin1 = new G4LogicalSkinSurface("skin1", logicshellMuVetoOut, mirrorSurface);
	G4LogicalSkinSurface *skin2 = new G4LogicalSkinSurface("skin2", logicshellMuVetoIn, mirrorSurface);
	
	//when subtracting 2 boxes, the origin of the parent box from which subtraction is done is retained in the resultant box
	//thus all the boxes above table are kept at (x,0,0)
	physshellMuVetoOut = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellMuVetoOut,"physshellMuVetoOut",logicWorld,false,1,true);
	physshell0 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell0,"physshell0",logicWorld,false,2,true);
	physshell1 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell1,"physshell1",logicWorld,false,3,true);
	physshell2		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell2,"physshell2",logicWorld,false,4,true);
	physshell3 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell3,"physshell3",logicWorld,false,5,true);
	physshell4    	   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell4,"physshell4",logicWorld,false,6,true);
	physshell5 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell5,"physshell5",logicWorld,false,7,true);
	physshell6 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell6,"physshell6",logicWorld,false,8,true);
	physshell7 		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshell7,"physshell7",logicWorld,false,9,true);
	physshellMuVetoIn  = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellMuVetoIn,"physshellMuVetoIn",logicWorld,false,10,true);
	physshellCuColdBox = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicshellCuColdBox,"physshellCuColdBox",logicWorld,false,11,true);
	physSteelPlate     = new G4PVPlacement(0,G4ThreeVector(xloc,0.,-1.0*zoffset*cm), logicSteelPlate,"physSteelPlate",logicWorld,false,12,true);
	physUnderSideBP	   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,-1.0*(zoffset+6.25)*cm), logicUnderSideBP,"physUnderSideBP",logicWorld,false,13,true);
	physUnderSideHDPE  = new G4PVPlacement(0,G4ThreeVector(xloc,0.,-1.0*(zoffset+16.25)*cm), logicUnderSideHDPE,"physUnderSideHDPE",logicWorld,false,14,true);
	physdetVol		   = new G4PVPlacement(0,G4ThreeVector(xloc,0.,0.), logicdetVol,"physdetVol",logicWorld,false,0,true);
}

G4VSolid* MyDetectorConstruction::ConstructShell(double xsz, double ysz, double zsz, double thickness, double offset=0.0){
	G4VSolid* boxout = new G4Box("Boxout",0.5*xsz*cm,0.5*ysz*cm,0.5*zsz*cm);
	G4VSolid* boxin  = new G4Box("Boxin",(0.5*xsz-thickness)*cm,(0.5*ysz-thickness)*cm,(0.5*zsz-thickness)*cm);
	G4VSolid* shell  = new G4SubtractionSolid("BoxOut-BoxIn", boxout, boxin, 0, G4ThreeVector(0.,0.,-1.0*offset*cm));
	return shell;
}

G4VSolid* MyDetectorConstruction::SubtractBox(G4VSolid* sol, G4ThreeVector Boxsz, G4ThreeVector relPosSubVol){
	G4VSolid* box = new G4Box("Box",0.5*Boxsz.x()*cm,0.5*Boxsz.y()*cm,0.5*Boxsz.z()*cm);
	G4VSolid* subbox  = new G4SubtractionSolid("sol-box", sol, box, 0, relPosSubVol);
	return subbox;
}

G4VSolid* MyDetectorConstruction::SubtractBoxfrmShell(G4ThreeVector shellsz, double thickness, double offset, G4ThreeVector Boxsz, G4ThreeVector relPosSubVol){
	G4VSolid* shell = ConstructShell(shellsz.x(),shellsz.y(),shellsz.z(),thickness,offset);
	G4VSolid* box = new G4Box("Box",0.5*Boxsz.x()*cm,0.5*Boxsz.y()*cm,0.5*Boxsz.z()*cm);
	G4VSolid* subboxfrmshell  = new G4SubtractionSolid("shell-box", shell, box, 0, relPosSubVol);
	return subboxfrmshell;
}

G4VSolid* MyDetectorConstruction::SubtractBoxfrmShell(G4ThreeVector shellsz, double thickness, double offset, G4ThreeVector Boxsz){
	G4ThreeVector relPosSubVol = G4ThreeVector(0,0,-0.5*(shellsz.z()-Boxsz.z())*cm);
	G4VSolid* shell = ConstructShell(shellsz.x(),shellsz.y(),shellsz.z(),thickness,offset);
	G4VSolid* box = new G4Box("Box",0.5*Boxsz.x()*cm,0.5*Boxsz.y()*cm,0.5*Boxsz.z()*cm);
	G4VSolid* subboxfrmshell  = new G4SubtractionSolid("shell-box", shell, box, 0, relPosSubVol);
	return subboxfrmshell;
}

//The Construct function where we define the material of the detector and define the physical and logical volume of the environment and detector.
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	//Defining the dimenstions of the world environment	
	solidWorld = new G4Box("solidWorld",xWorld,yWorld,zWorld);

	//Setiing Logical volume where we integrate the material to the world box	
	 logicWorld= new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
	 //logicWorld= new G4LogicalVolume(solidWorld,Vaccum,"logicWorld");
	//Integrating the position of the world to the logical volume to create our final Physical Volume	
	 physWorld = new G4PVPlacement(0,G4ThreeVector(0., 0., 0.),logicWorld,"physWorld",0,false,100,true);
	 
	 //ConstructSetupMod();
	 ConstructSetupV1();
	

//Finally we return the physWorld as output	
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField(){
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	
	/*logicshellMuVetoOut->SetSensitiveDetector(sensDet);
	logicshellHDPEOuter->SetSensitiveDetector(sensDet);
	logicshellBP->SetSensitiveDetector(sensDet);
	logicshellLead->SetSensitiveDetector(sensDet);
	logicshellHDPEInner->SetSensitiveDetector(sensDet);
	logicshellMuVetoIn->SetSensitiveDetector(sensDet);
	logicshellCuColdBox->SetSensitiveDetector(sensDet);*/
	logicdetVol->SetSensitiveDetector(sensDet);
}
