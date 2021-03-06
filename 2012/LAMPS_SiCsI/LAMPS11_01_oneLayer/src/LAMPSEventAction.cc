// ====================================================================
//   LAMPSEventAction.cc
// ====================================================================

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "LAMPSEventAction.hh"
#include "TPCSD.hh"
#include "TPCHit.hh"
#include "DCSD.hh"
#include "DCHit.hh"
#include "ToFSD.hh"
#include "ToFHit.hh"
#include "LANDHit.hh"
#include "SiCsIHit.hh"
#include "SiCsISD.hh"

#include "LAMPSAnaRoot.hh"
#include "LAMPSPrimaryGeneratorAction.hh"

#include <fstream>

extern std::ofstream ofs;

////////////////////////////////
LAMPSEventAction::LAMPSEventAction(LAMPSAnaRoot *rootPointer, LAMPSPrimaryGeneratorAction* PGAPointer)
: anaRoot(rootPointer), LAMPSPGA(PGAPointer)
////////////////////////////////
{
}

/////////////////////////////////
LAMPSEventAction::~LAMPSEventAction()
/////////////////////////////////
{}

///////////////////////////////////////////////////////////////
void LAMPSEventAction::BeginOfEventAction(const G4Event* anEvent)
///////////////////////////////////////////////////////////////
{
  useEventFile = LAMPSPGA -> GetUseEventFile();

  G4int nVtx= anEvent-> GetNumberOfPrimaryVertex();

  for( G4int i=0; i< nVtx; i++) {
    const G4PrimaryVertex* primaryVertex= anEvent-> GetPrimaryVertex(i);
  }

//  G4SDManager *pSDManager = G4SDManager::GetSDMpointer();
}

/////////////////////////////////////////////////////////////
void LAMPSEventAction::EndOfEventAction(const G4Event* anEvent)
/////////////////////////////////////////////////////////////
{
  G4int particleNum = LAMPSPGA -> GetParticleNumber();

//  G4int eventID = anEvent-> GetEventID();
//  if(eventID % 1000 == 0){
//    G4cout << ">>> Event ID: " << eventID << G4endl;
//  }
  G4SDManager* SDManager= G4SDManager::GetSDMpointer();

  // get "Hit Collection of This Event"
  G4HCofThisEvent* HCTE = anEvent-> GetHCofThisEvent();
  if (!HCTE) return;  // no hits in this events. nothing to do!

  G4THitsCollection<TPCHit> *CHC_TPC = NULL;
  G4THitsCollection<DCHit> *CHC_DC = NULL;
  G4THitsCollection<ToFHit> *CHC_ToF = NULL;
  G4THitsCollection<LANDHit> *CHC_LAND = NULL;
  G4THitsCollection<SiCsIHit> *CHC_SiCsI = NULL;

  G4String HCname;
  hitCollectionID = SDManager -> GetCollectionID(HCname="TPCHitCollection");
  if (HCTE)	CHC_TPC = (G4THitsCollection<TPCHit> *)(HCTE -> GetHC(hitCollectionID));

  if (CHC_TPC) {
	  G4int nHits = CHC_TPC -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_TPC)[i] -> GetParentID();
			G4int pID = (*CHC_TPC)[i] -> GetParticleID();
			G4ThreeVector prePos = (*CHC_TPC)[i] -> GetPrePosition();
			G4ThreeVector postPos = (*CHC_TPC)[i] -> GetPostPosition();
			G4ThreeVector pos_voxel = (*CHC_TPC)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_TPC)[i] -> GetEDep();
			G4double ToF = (*CHC_TPC)[i] -> GetToF();

//		std::ofstream outFile("edep.out", std::ios::app);
//		outFile << pos_voxel.x() << " " << pos_voxel.y() << " " << pos_voxel.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillTPC(particleNum, parentID, pID, (G4int)pos_voxel.x(), (G4int)pos_voxel.y(), (G4int)pos_voxel.z(), EDep, ToF);
//			anaRoot -> FillTPC(particleNum, parentID, pID, (G4int)pos_voxel.x(), (G4int)pos_voxel.y(), (G4int)pos_voxel.z(), EDep, ToF);
			anaRoot -> FillTPC(particleNum, parentID, pID, prePos.x(), prePos.y(), prePos.z(), postPos.x(), postPos.y(), postPos.z(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="DCHitCollection_BD");
  if (HCTE)	CHC_DC = (G4THitsCollection<DCHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_DC = NULL;

  if (CHC_DC) {
	  G4int nHits = CHC_DC -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_DC)[i] -> GetParentID();
			G4int pID = (*CHC_DC)[i] -> GetParticleID();
			G4int detID = (*CHC_DC)[i] -> GetDetID();
			G4ThreeVector pos = (*CHC_DC)[i] -> GetPosition();
			G4ThreeVector pos_voxel = (*CHC_DC)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_DC)[i] -> GetEDep();
			G4double ToF = (*CHC_DC)[i] -> GetToF();

//		std::ofstream outFile("all.out", std::ios::app);
//		outFile << pos.x() << " " << pos.y() << " " << pos.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "BD", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillDC(particleNum, "BD", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="DCHitCollection_DPA1");
  if (HCTE)	CHC_DC = (G4THitsCollection<DCHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_DC = NULL;

  if (CHC_DC) {
	  G4int nHits = CHC_DC -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_DC)[i] -> GetParentID();
			G4int pID = (*CHC_DC)[i] -> GetParticleID();
			G4int detID = (*CHC_DC)[i] -> GetDetID();
			G4ThreeVector pos = (*CHC_DC)[i] -> GetPosition();
			G4ThreeVector pos_voxel = (*CHC_DC)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_DC)[i] -> GetEDep();
			G4double ToF = (*CHC_DC)[i] -> GetToF();

//		std::ofstream outFile("all.out", std::ios::app);
//		outFile << pos.x() << " " << pos.y() << " " << pos.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="DCHitCollection_DPA2");
  if (HCTE)	CHC_DC = (G4THitsCollection<DCHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_DC = NULL;

  if (CHC_DC) {
	  G4int nHits = CHC_DC -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_DC)[i] -> GetParentID();
			G4int pID = (*CHC_DC)[i] -> GetParticleID();
			G4int detID = (*CHC_DC)[i] -> GetDetID();
			G4ThreeVector pos = (*CHC_DC)[i] -> GetPosition();
			G4ThreeVector pos_voxel = (*CHC_DC)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_DC)[i] -> GetEDep();
			G4double ToF = (*CHC_DC)[i] -> GetToF();

//		std::ofstream outFile("all.out", std::ios::app);
//		outFile << pos.x() << " " << pos.y() << " " << pos.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A2", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillDC(particleNum, "A2", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="ToFHitCollection_DPA1");
  if (HCTE)	CHC_ToF = (G4THitsCollection<ToFHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_ToF = NULL;

  if (CHC_ToF) {
	  G4int nHits = CHC_ToF -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_ToF)[i] -> GetParentID();
			G4int pID = (*CHC_ToF)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_ToF)[i] -> GetPosition();
			G4ThreeVector pos_voxel = (*CHC_ToF)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_ToF)[i] -> GetEDep();
			G4double ToF = (*CHC_ToF)[i] -> GetToF();

//		std::ofstream outFile("all.out", std::ios::app);
//		outFile << pos.x() << " " << pos.y() << " " << pos.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillToF(particleNum, (G4int)pos_voxel.x(), parentID, pID, (G4int)pos_voxel.y(), EDep, ToF);
			anaRoot -> FillToF(particleNum, (G4int)pos_voxel.x(), parentID, pID, (G4int)pos_voxel.y(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="ToFHitCollection_DPA2");
  if (HCTE)	CHC_ToF = (G4THitsCollection<ToFHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_ToF = NULL;

  if (CHC_ToF) {
	  G4int nHits = CHC_ToF -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_ToF)[i] -> GetParentID();
			G4int pID = (*CHC_ToF)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_ToF)[i] -> GetPosition();
			G4ThreeVector pos_voxel = (*CHC_ToF)[i] -> GetVoxelPosition();
			G4double EDep = (*CHC_ToF)[i] -> GetEDep();
			G4double ToF = (*CHC_ToF)[i] -> GetToF();

//		std::ofstream outFile("all.out", std::ios::app);
//		outFile << pos.x() << " " << pos.y() << " " << pos.z() << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillToF(particleNum, (G4int)pos_voxel.x(), parentID, pID, (G4int)pos_voxel.y(), EDep, ToF);
			anaRoot -> FillToF(particleNum, (G4int)pos_voxel.x(), parentID, pID, (G4int)pos_voxel.y(), EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="LANDHitCollection_VC1");
  if (HCTE)	CHC_LAND = (G4THitsCollection<LANDHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_LAND = NULL;

  if (CHC_LAND) {
	  G4int nHits = CHC_LAND -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_LAND)[i] -> GetParentID();
			G4int pID = (*CHC_LAND)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_LAND)[i] -> GetPosition();
			G4int detPos = (*CHC_LAND)[i] -> GetDetPosition();
			G4double EDep = (*CHC_LAND)[i] -> GetEDep();
			G4double ToF = (*CHC_LAND)[i] -> GetToF();

//		std::ofstream outFile("land.out", std::ios::app);
//		outFile << detPos << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillLAND(particleNum, parentID, pID, detPos, EDep, ToF);
			anaRoot -> FillLAND(particleNum, parentID, pID, detPos, EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="LANDHitCollection_SA1");
  if (HCTE)	CHC_LAND = (G4THitsCollection<LANDHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_LAND = NULL;

  if (CHC_LAND) {
	  G4int nHits = CHC_LAND -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_LAND)[i] -> GetParentID();
			G4int pID = (*CHC_LAND)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_LAND)[i] -> GetPosition();
			G4int detPos = (*CHC_LAND)[i] -> GetDetPosition();
			G4double EDep = (*CHC_LAND)[i] -> GetEDep();
			G4double ToF = (*CHC_LAND)[i] -> GetToF();

//		std::ofstream outFile("land.out", std::ios::app);
//		outFile << detPos << " " << EDep << " " << ToF << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillLAND(particleNum, parentID, pID, detPos, EDep, ToF);
			anaRoot -> FillLAND(particleNum, parentID, pID, detPos, EDep, ToF);
	  }
  }


// KYO - SiCsIHitCollection

  hitCollectionID = SDManager -> GetCollectionID(HCname="SiCsIHitCollection_SiF1");
  if (HCTE)	CHC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_SiCsI = NULL;

  if (CHC_SiCsI) {
	  G4int nHits = CHC_SiCsI -> entries();
//	G4cout << "SiCsI nHits = " << nHits << G4endl; 
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_SiCsI)[i] -> GetParentID();
			G4int pID = (*CHC_SiCsI)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_SiCsI)[i] -> GetPosition();
			G4double EDep = (*CHC_SiCsI)[i] -> GetEDep();
			G4double ToF = (*CHC_SiCsI)[i] -> GetToF();
			G4double detNum = (*CHC_SiCsI)[i] -> GetdetNum();

//		std::ofstream outFile("SiCsI.out", std::ios::app); //KYO
//		outFile << std::setw(10) << parentID
//			<< std::setw(10) << pID
//			<< std::setw(10) << Pos.x()
//			<< std::setw(10) << EDep
//			<< std::setw(10) << ToF
//			<< std::setw(10) << detNum << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillSiCsI(particleNum, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF, detNum);
	  }
  }


  hitCollectionID = SDManager -> GetCollectionID(HCname="SiCsIHitCollection_SiS1");
  if (HCTE)	CHC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_SiCsI = NULL;

  if (CHC_SiCsI) {
	  G4int nHits = CHC_SiCsI -> entries();
//	G4cout << "SiCsI nHits = " << nHits << G4endl; 
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_SiCsI)[i] -> GetParentID();
			G4int pID = (*CHC_SiCsI)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_SiCsI)[i] -> GetPosition();
			G4double EDep = (*CHC_SiCsI)[i] -> GetEDep();
			G4double ToF = (*CHC_SiCsI)[i] -> GetToF();
			G4double detNum = (*CHC_SiCsI)[i] -> GetdetNum();

//		std::ofstream outFile("SiCsI.out", std::ios::app); //KYO
//		outFile << std::setw(10) << parentID
//			<< std::setw(10) << pID
//			<< std::setw(10) << Pos.x()
//			<< std::setw(10) << EDep
//			<< std::setw(10) << ToF
//			<< std::setw(10) << detNum << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillSiCsI(particleNum, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF, detNum);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="SiCsIHitCollection_SiT1");
  if (HCTE)	CHC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_SiCsI = NULL;

  if (CHC_SiCsI) {
	  G4int nHits = CHC_SiCsI -> entries();
//	G4cout << "SiCsI nHits = " << nHits << G4endl; 
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_SiCsI)[i] -> GetParentID();
			G4int pID = (*CHC_SiCsI)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_SiCsI)[i] -> GetPosition();
			G4double EDep = (*CHC_SiCsI)[i] -> GetEDep();
			G4double ToF = (*CHC_SiCsI)[i] -> GetToF();
			G4double detNum = (*CHC_SiCsI)[i] -> GetdetNum();

//		std::ofstream outFile("SiCsI.out", std::ios::app); //KYO
//		outFile << std::setw(10) << parentID
//			<< std::setw(10) << pID
//			<< std::setw(10) << Pos.x()
//			<< std::setw(10) << EDep
//			<< std::setw(10) << ToF
//			<< std::setw(10) << detNum << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillSiCsI(particleNum, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF, detNum);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="SiCsIHitCollection_CsI1");
  if (HCTE)	CHC_SiCsI = (G4THitsCollection<SiCsIHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_SiCsI = NULL;

  if (CHC_SiCsI) {
	  G4int nHits = CHC_SiCsI -> entries();
//	G4cout << "SiCsI nHits = " << nHits << G4endl; 
	  
	  for (G4int i = 0; i != nHits; i++) {
			G4int parentID = (*CHC_SiCsI)[i] -> GetParentID();
			G4int pID = (*CHC_SiCsI)[i] -> GetParticleID();
			G4ThreeVector pos = (*CHC_SiCsI)[i] -> GetPosition();
			G4double EDep = (*CHC_SiCsI)[i] -> GetEDep();
			G4double ToF = (*CHC_SiCsI)[i] -> GetToF();
			G4double detNum = (*CHC_SiCsI)[i] -> GetdetNum();

//		std::ofstream outFile("SiCsI.out", std::ios::app); //KYO
//		outFile << std::setw(10) << parentID
//			<< std::setw(10) << pID
//			<< std::setw(10) << Pos.x()
//			<< std::setw(10) << EDep
//			<< std::setw(10) << ToF
//			<< std::setw(10) << detNum << G4endl;

//		if (useEventFile == 1)	anaRoot -> FillDC(particleNum, "A1", detID, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF);
			anaRoot -> FillSiCsI(particleNum, parentID, pID, pos.x(), pos.y(), pos.z(), EDep, ToF, detNum);
	  }
  }

/*
  hitCollectionID = SDManager -> GetCollectionID(HCname="LANDHitCollection_VC2");
  if (HCTE)	CHC_LAND = (G4THitsCollection<LANDHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_LAND = NULL;

  if (CHC_LAND) {
	  G4int nHits = CHC_LAND -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
		G4int pID = (*CHC_LAND)[i] -> GetParticleID();
		G4ThreeVector pos = (*CHC_LAND)[i] -> GetPosition();
		G4int detPos = (*CHC_LAND)[i] -> GetDetPosition();
		G4double EDep = (*CHC_LAND)[i] -> GetEDep();
		G4double ToF = (*CHC_LAND)[i] -> GetToF();

//		std::ofstream outFile("land.out", std::ios::app);
//		outFile << detPos << " " << EDep << " " << ToF << G4endl;

		if (useEventFile == 1)	anaRoot -> FillLAND(particleNum, pID, detPos, EDep, ToF);
	  }
  }

  hitCollectionID = SDManager -> GetCollectionID(HCname="LANDHitCollection_SA2");
  if (HCTE)	CHC_LAND = (G4THitsCollection<LANDHit> *)(HCTE -> GetHC(hitCollectionID));
  else		CHC_LAND = NULL;

  if (CHC_LAND) {
	  G4int nHits = CHC_LAND -> entries();
	  
	  for (G4int i = 0; i != nHits; i++) {
		G4int pID = (*CHC_LAND)[i] -> GetParticleID();
		G4ThreeVector pos = (*CHC_LAND)[i] -> GetPosition();
		G4int detPos = (*CHC_LAND)[i] -> GetDetPosition();
		G4double EDep = (*CHC_LAND)[i] -> GetEDep();
		G4double ToF = (*CHC_LAND)[i] -> GetToF();

//		std::ofstream outFile("land.out", std::ios::app);
//		outFile << detPos << " " << EDep << " " << ToF << G4endl;

		if (useEventFile == 1)	anaRoot -> FillLAND(particleNum, pID, detPos, EDep, ToF);
	  }
  }
*/

/* Genie
  static G4int idcounter= -1;
  if(idcounter<0) idcounter= SDManager-> GetCollectionID("TPC/hit");
  G4THitsCollection<TPCPadHit>* padHC = 0;
  padHC = (G4THitsCollection<TPCPadHit>*)HCTE-> GetHC(idcounter);

  if(padHC){

    G4int nhits = padHC -> entries();

    for(G4int i=0; i< nhits; i++) {
      G4ThreeVector xyz = (*padHC)[i] -> GetPosition();
      G4ThreeVector mom = (*padHC)[i] -> GetMomentum();
      G4double tof= (*padHC)[i] -> GetTOF();
      G4int tid = (*padHC)[i] -> GetTrackID();
      G4int pid = (*padHC)[i] -> GetParticleID();
      G4int ilay = (*padHC)[i] -> GetPadLay();
      G4int irow = (*padHC)[i] -> GetPadRow();
      G4double beta = (*padHC)[i] -> GetBeta();
      G4double edep = (*padHC)[i] -> GetEdep();
    }
  }

  static G4int idscint = -1;
  if(idscint < 0) idscint = SDManager-> GetCollectionID("SCINT/hit");
  G4THitsCollection<TPCScintHit>* scintHC = 0;
  scintHC = (G4THitsCollection<TPCScintHit>*)HCTE-> GetHC(idscint);


  if(scintHC){

    G4int nhits= scintHC -> entries();

    for(G4int i=0; i< nhits; i++) {
      G4ThreeVector xyz = (*scintHC)[i]-> GetPosition();
      G4ThreeVector mom = (*scintHC)[i]-> GetMomentum();
      G4double tof= (*scintHC)[i]-> GetTOF();
      G4int tid = (*scintHC)[i]-> GetTrackID();
      G4int pid = (*scintHC)[i]-> GetParticleID();
      G4int did = (*scintHC)[i]-> GetDetectorID();
      //      printf("didsc : %d \n", did);
    }
  }


  static G4int idfdc = -1;
  if(idfdc < 0) idfdc = SDManager-> GetCollectionID("FDC/hit");
  G4THitsCollection<TPCFDCHit>* fdcHC = 0;
  fdcHC = (G4THitsCollection<TPCFDCHit>*)HCTE-> GetHC(idfdc);

  if(fdcHC){

    G4int nhits= fdcHC -> entries();

    for(G4int i=0; i< nhits; i++) {
      G4ThreeVector xyz = (*fdcHC)[i]-> GetPosition();
      G4ThreeVector mom = (*fdcHC)[i]-> GetMomentum();
      G4double tof= (*fdcHC)[i]-> GetTOF();
      G4int tid = (*fdcHC)[i]-> GetTrackID();
      G4int pid = (*fdcHC)[i]-> GetParticleID();
      G4int did = (*fdcHC)[i]-> GetDetectorID();

      //      printf("didfdc : %d \n", did);

    }

  }
*/

  if (useEventFile == 1 )	LAMPSPGA -> AfterEndOfEventAction();
	else	LAMPSPGA -> AfterEndOfSingleVertexEventAction();
}
