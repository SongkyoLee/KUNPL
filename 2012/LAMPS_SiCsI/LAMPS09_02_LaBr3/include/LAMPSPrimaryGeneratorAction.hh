// ====================================================================
//   LAMPSPrimaryGeneratorAction.hh
// ====================================================================
#ifndef LAMPS_PRIMARY_GENERATOR_ACTION_H
#define LAMPS_PRIMARY_GENERATOR_ACTION_H
 
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "LAMPSDetectorConstruction.hh"

#include <fstream>

class G4ParticleGun;
class LAMPSPrimaryGeneratorMessenger;
class G4RunManager;
class LAMPSDetectorConstruction;
class LAMPSAnaRoot;
class LAMPSBeamFromROOT;

class LAMPSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
private:
  G4RunManager* runManager;
  LAMPSPrimaryGeneratorMessenger* gunMessenger;
  G4ParticleGun* particleGun;   // particle gun provided by Geant4

  LAMPSDetectorConstruction* LAMPSDC;
  LAMPSAnaRoot *anaRoot;
  LAMPSBeamFromROOT* beam;

  G4ThreeVector gun_pos;
  G4ParticleDefinition* particleName;
  G4ThreeVector p_direction;
  G4double k_energy;
  G4double given_momentum;
  G4double mField;
  G4int fileNum;
  G4bool useEventFile;
  G4int choosenEnergy;
  G4int choosenModel;

  G4int useRandom; //KYO
  G4double rndm_k_energy_max; // KYO
  G4ThreeVector rangeInfo; //KYO
  G4double rndm_k_energy; //KYO
  G4double mz; //KYO
  G4double rt; //KYO
  G4ThreeVector rndm_p_dir; //KYO

  std::ifstream openFile;
  G4int tempNumTracks;
  G4int tempParticleName;
  G4double tempPx;
  G4double tempPy;
  G4double tempPz;

  G4int eventNum;
  G4int countTrackNum;
  G4int choosenEventNum;

public:
  LAMPSPrimaryGeneratorAction(LAMPSDetectorConstruction* det, LAMPSAnaRoot* rootPointer, G4RunManager*);
  ~LAMPSPrimaryGeneratorAction();

  void PrepareBeam();

  virtual void GeneratePrimaries(G4Event* anEvent);
  void GenerateXKPi(G4Event* anEvent);
  void GenerateThetaKsP(G4Event* anEvent);        
  void GenerateLambdaStarKsPi(G4Event* anEvent); 
  void GenerateSingle(G4Event* anEvent);
  void GenerateThetaHyper(G4Event* anEvent);
  void GenerateSinglePion(G4Event* anEvent); 
  void GenerateDualPions(G4Event* anEvent);
  G4double deg2rad(double theta);
  G4double RandSin(void);

  double GetParticleMassInGeV();
  G4int    GetNumNucleon();

  void SetBeam(G4int, G4double, G4double, G4double);
  void ShowMomentum(G4double val) { given_momentum = val; };
  void SetParticle(G4ParticleDefinition* pd) { particleName = pd; };
  void SetKineticEnergy(G4double energy) { k_energy = energy; };
  void SetMomentumDirection(G4ThreeVector momentum_d) { p_direction = momentum_d; };
  void SetGunPosition(G4ThreeVector pos) { gun_pos = pos; };
  void SetUseEventFile(G4int val) { useEventFile = val; };
  void SetEnergy(G4int val) { choosenEnergy = val; };
  void SetModel(G4int val) { choosenModel = val; };
  void SetChoosenEventNum(G4int val) { choosenEventNum = val; };
  void SetNumTracks(G4int val) { tempNumTracks = val; };
  G4int GetChoosenEventEnergy() { return choosenEnergy; };
  G4int GetNumTracks()	{ return tempNumTracks; };
  void SetUseRandom(G4int val) { useRandom = val; }; //KYO
  void SetRndmKineticEnergy(G4double val) { rndm_k_energy_max = val; }; //KYO
  void SetRndm_p_direction(G4ThreeVector val) { rangeInfo = val; }; //KYO

  G4int GetParticleNumber() { return countTrackNum; };

  void AfterEndOfEventAction();
  void AfterEndOfSingleVertexEventAction();
  bool GetUseEventFile() { return useEventFile; };
	void CloseOpenFile();
};
#endif
