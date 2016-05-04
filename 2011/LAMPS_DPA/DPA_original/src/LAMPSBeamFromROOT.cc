#include <TSystem.h>
#include <TFile.h>
#include <TSystem.h>
#include <TDirectory.h>

#include "LAMPSBeamFromROOT.hh"
#include "LAMPSPrimaryGeneratorAction.hh"

#include <string>
#include <sstream>

LAMPSBeamFromROOT::LAMPSBeamFromROOT(LAMPSPrimaryGeneratorAction* LAMPSPGAPointer, G4int choosenEnergy, G4int choosenModel, G4int choosenEventNum)
:LAMPSPGA(LAMPSPGAPointer), energy((Int_t)choosenEnergy), model((Int_t)choosenModel), eventNum((Int_t)choosenEventNum)
{
	openROOTFile = new TFile("/home/geniejhang/geant4/IQMDdata/IQMDdata_RandomPhi.root");

	SelectEnergyAndModel(energy, model);
	SelectEvent(eventNum);
}

LAMPSBeamFromROOT::~LAMPSBeamFromROOT()
{
	delete eventTree;
	delete selectedEnergyAndModelDir;
	delete openROOTFile;
}

void LAMPSBeamFromROOT::SelectEnergyAndModel(Int_t& choosenEnergy, Int_t& choosenModel)
{
//	if (selectedEnergyAndModelDir)	delete selectedEnergyAndModelDir;

	std::string modelName;
	if (choosenModel == 0)
		modelName = "Soft";
	else if (choosenModel == 1)
		modelName = "Hard";

	std::stringstream selectedEnergyAndModelDirName;
	selectedEnergyAndModelDirName << "IQMD_AuAu_" << choosenEnergy << "_MeV_" << modelName << "_Model";
	selectedEnergyAndModelDir = (TDirectory *) openROOTFile -> GetDirectory(selectedEnergyAndModelDirName.str().c_str());
}

void LAMPSBeamFromROOT::SelectEvent(Int_t& choosenEventNum)
{
//	if (eventTree) delete eventTree;

  std::stringstream eventTreeName;
	eventTreeName << "event_" << choosenEventNum;
	eventTree = (TTree *) selectedEnergyAndModelDir -> FindObjectAny(eventTreeName.str().c_str());
		eventTree -> SetBranchAddress("particleID", &particleID);
		eventTree -> SetBranchAddress("pX", &pX);
		eventTree -> SetBranchAddress("pY", &pY);
		eventTree -> SetBranchAddress("pZ", &pZ);

	numTracks = eventTree -> GetEntries();

	LAMPSPGA -> SetNumTracks(numTracks);
}

void LAMPSBeamFromROOT::GetBeam(Int_t& val)
{
	eventTree -> GetEntry(val);

	LAMPSPGA -> SetBeam(particleID, pX, pY, pZ);
}
