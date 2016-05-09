// ====================================================================
//   LAMPSPrimaryGeneratorAction.cc
// ====================================================================
#include "LAMPSPrimaryGeneratorAction.hh"
#include "LAMPSPrimaryGeneratorMessenger.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "common.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"
#include "TMath.h"//KYO

#include "LAMPSAnaRoot.hh"
#include "LAMPSBeamFromROOT.hh"
 
#include <iostream>
#include <iomanip>
#include <fstream>

LAMPSPrimaryGeneratorAction::LAMPSPrimaryGeneratorAction(LAMPSDetectorConstruction* det, LAMPSAnaRoot *rootPointer, G4RunManager* runPointer)
  :runManager(runPointer), LAMPSDC(det), anaRoot(rootPointer), beam(0), gun_pos(G4ThreeVector()), p_direction(G4ThreeVector(0, 0, 1)), k_energy(100.*MeV), given_momentum(0), mField(0), fileNum(0), useEventFile(0), choosenEnergy(150), choosenModel(1), eventNum(0), choosenEventNum(0) 
{
  gunMessenger = new LAMPSPrimaryGeneratorMessenger(this, runManager);
  particleGun = new G4ParticleGun;
  PrepareBeam();
}

LAMPSPrimaryGeneratorAction::~LAMPSPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

void LAMPSPrimaryGeneratorAction::PrepareBeam()
{
//	if (beam)	delete beam;

	beam = new LAMPSBeamFromROOT(this, choosenEnergy, choosenModel, choosenEventNum);

  countTrackNum = 0;
}

void LAMPSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //  GenerateXKPi(anEvent);          // p(gamma, K-pi+)Theta+
  //  GenerateThetaKsP(anEvent);          // p(gamma, K-pi+)Theta+ ->KsP invm
  //  GenerateLambdaStarKsPi(anEvent);    // p(gamma, Kspi+)Lambda(1405)
  GenerateSingle(anEvent);          // Single track
  //  GenerateThetaHyper(anEvent);         // alpha(gamma,pK-)tTheta+
  //  GenerateSinglePion(anEvent);            // Single pion
  //GenerateDualPions(anEvent);            // Pi+ Pi-
}


double LAMPSPrimaryGeneratorAction::deg2rad(double theta) {
  return 3.141592654*theta/180.0;
}

double LAMPSPrimaryGeneratorAction::RandSin(void)
{
  int success=0;
  double x,fx;

  do {
    x = 180.0 * (double)CLHEP::RandFlat::shoot();
    fx = sin(deg2rad(x));
    if (fx >= (double)CLHEP::RandFlat::shoot())
      success = 1;
  } while (success==0);

  return x;
}

double LAMPSPrimaryGeneratorAction::GetParticleMassInGeV()
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	if ( particleName == NULL )	particleName = particleTable -> FindParticle("proton");

	return particleName -> GetPDGMass()/GeV;
}

int LAMPSPrimaryGeneratorAction::GetNumNucleon()
{
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	if ( particleName == NULL )	particleName = particleTable -> FindParticle("proton");

	return particleName -> GetAtomicMass();
}

void LAMPSPrimaryGeneratorAction::GenerateSingle(G4Event* anEvent)
{

  double mom_pp;
  double mom1[3];
  double mom2[3];
  double mom3[3];
  double mom4[3];
  double theta;
  double phi;
  double mass;
  double energy;
  const double pi = 3.141592653;
  double Egamma,pg_x,pg_y,pg_z;

  G4ParticleDefinition* gamma;
  G4ParticleDefinition* proton;
  G4ParticleDefinition* d2;
  G4ParticleDefinition* alpha;
  G4ParticleDefinition* triton;
  G4ParticleDefinition* c12;
  G4ParticleDefinition* kaonPlus;
  G4ParticleDefinition* piPlus;
  G4ParticleDefinition* neutron;
  G4ParticleDefinition* kaonMinus;
  G4ParticleDefinition* kaonShort;
  G4ParticleDefinition* lambda;

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //  G4IonTable* ionTable;
  //  G4ParticleDefinition* d2 = ionTable->GetIon(1,2,0.);

  // GetIon(atomicNumber, atomicMass, excitationEnergy)
  gamma = particleTable->FindParticle("gamma");
  proton = particleTable->FindParticle("proton");
  d2 = particleTable->FindParticle("deuteron");
  c12 = particleTable->GetIon(6,12,0.);
  alpha = particleTable->FindParticle("alpha");
  triton = particleTable->FindParticle("triton");
  neutron = particleTable->FindParticle("neutron");
  kaonPlus = particleTable->FindParticle("kaon+");
  kaonMinus = particleTable->FindParticle("kaon-");
  piPlus = particleTable->FindParticle("pi+");
  kaonShort = particleTable->FindParticle("kaon0S");
  lambda = particleTable->FindParticle("lambda");

  G4ParticleDefinition* he3 = particleTable -> GetIon(2, 3, 0);
  G4ParticleDefinition* li6 = particleTable -> GetIon(3, 6, 0);
  G4ParticleDefinition* li7 = particleTable -> GetIon(3, 7, 0);


  Egamma = 2.0;       // Incident gamma energy (GeV)
  pg_x = 0.0;
  pg_y = 0.0;
  pg_z = Egamma;

  double checkx;
  double checky;
  int checkk=0;
  //  do {
    //  phi=CLHEP::RandFlat::shoot(0.*deg, 360.*deg);
    //  theta=CLHEP::RandFlat::shoot(0.*deg, 45.*deg);  //shhwang
    //  checkx=1333.*tan(theta)*cos(phi);
    //  checky=1333.*tan(theta)*sin(phi);
    //  if(abs(checkx)<=580.){
    //    if(abs(checky)<=300.){
    //      checkk=1;
    //    }
  //  }
  //  } while (checkk==0);

//  particleGun->SetParticleDefinition(proton);
//  particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
//  particleGun->SetParticlePosition(G4ThreeVector(0, 0, 0));
//  particleGun->SetParticleEnergy(200*MeV);

  if ( useEventFile == 0 )
  {
		anaRoot -> BeginOfEvent(eventNum);

	  if ( particleName == NULL )	particleName = proton;
	  G4double val1 = particleGun -> GetParticleEnergy();
	  G4double val2 = (particleName -> GetPDGMass())/GeV;
	  if ( given_momentum == 0)	given_momentum = sqrt( (val1/GeV + val2)*(val1/GeV + val2) - val2*val2 );

	  G4int numNucleon = particleName -> GetAtomicMass();

	  particleGun->SetParticlePosition(gun_pos);
	  particleGun->SetParticleDefinition(particleName);

	if ( useRandom == 0 )
	{
	  particleGun->SetParticleMomentumDirection(p_direction);
	  particleGun->SetParticleEnergy(k_energy);

	  G4cout << G4endl;
	  G4cout << "========================= Settings =========================" << G4endl;
	  G4cout << std::setw(30) << "Particle: " << particleGun -> GetParticleDefinition() -> GetParticleName() << G4endl;
	  G4cout << std::setw(30) << "Number of Nucleons: " << particleName -> GetAtomicMass() << G4endl;
	  G4cout << std::setw(30) << "Mass: " << G4BestUnit(val2*GeV, "Energy") << "/c2" << G4endl;
	  G4cout << std::setw(30) << "Momentum: " << G4BestUnit(given_momentum*GeV, "Energy") << "/c" << G4endl;
	  G4cout << std::setw(30) << "Momentum Per Nucleon: " << G4BestUnit(given_momentum*GeV/numNucleon, "Energy") << "/c/u" << G4endl;
	  G4cout << std::setw(30) << "Kinetic Energy: " << G4BestUnit(particleGun -> GetParticleEnergy(), "Energy") << G4endl;
	  G4cout << std::setw(30) << "Kinetic Energy Per Nucleon: " << G4BestUnit((particleGun -> GetParticleEnergy())/numNucleon, "Energy") << "/u" << G4endl;
	  G4cout << std::setw(30) << "Dipole Magnetic Field: " << (LAMPSDC -> GetDPField())*1000 << " T" << G4endl;
	  G4cout << std::setw(30) << "Momentum Direction: " << particleGun -> GetParticleMomentumDirection() << G4endl;
	  G4cout << std::setw(30) << "Particle Gun Position: " << particleGun -> GetParticlePosition() << G4endl;
	  G4cout << "============================================================" << G4endl;
	  G4cout << G4endl;
	}

	else if ( useRandom == 1 ) //KYO
	{
		G4double rand1 = G4UniformRand();
		G4double rand2 = G4UniformRand();
		G4double rand3 = G4UniformRand();

		rndm_k_energy = rand1*rndm_k_energy_max*MeV;
		mz = TMath::Tan( ( rangeInfo.x()+ (rangeInfo.y()-rangeInfo.x())*rand2 ) *degree );
		rt = rand3*rangeInfo.z();
		rndm_p_dir = G4ThreeVector(0, mz, 1).rotateZ(rt*degree);
		particleGun->SetParticleMomentumDirection(rndm_p_dir);
		particleGun->SetParticleEnergy(rndm_k_energy);

	  G4cout << G4endl;
	  G4cout << "**********  use Random beam  **********" << G4endl;
	  G4cout << "========================= Settings =========================" << G4endl;
	  G4cout << std::setw(30) << "Particle: " << particleGun -> GetParticleDefinition() -> GetParticleName() << G4endl;
	  G4cout << std::setw(30) << "Number of Nucleons: " << particleName -> GetAtomicMass() << G4endl;
	  G4cout << std::setw(30) << "Mass: " << G4BestUnit(val2*GeV, "Energy") << "/c2" << G4endl;
	  G4cout << std::setw(30) << "the Momentum: " << G4BestUnit(given_momentum*GeV, "Energy") << "/c" << G4endl;
	  G4cout << std::setw(30) << "Momentum Per Nucleon: " << G4BestUnit(given_momentum*GeV/numNucleon, "Energy") << "/c/u" << G4endl;
	  G4cout << std::setw(30) << "Kinetic Energy: " << G4BestUnit(particleGun -> GetParticleEnergy(), "Energy") << G4endl;
	  G4cout << std::setw(30) << "Kinetic Energy Per Nucleon: " << G4BestUnit((particleGun -> GetParticleEnergy())/numNucleon, "Energy") << "/u" << G4endl;
	  G4cout << std::setw(30) << "Dipole Magnetic Field: " << (LAMPSDC -> GetDPField())*1000 << " T" << G4endl;
	  G4cout << std::setw(30) << "Momentum Direction (Random): " << particleGun -> GetParticleMomentumDirection() << G4endl;
	  G4cout << std::setw(30) << "Particle Gun Position: " << particleGun -> GetParticlePosition() << G4endl;
	  G4cout << "============================================================" << G4endl;
	  G4cout << G4endl;
	}

		G4double pX = given_momentum*GeV*(particleGun -> GetParticleMomentumDirection()).x();
		G4double pY = given_momentum*GeV*(particleGun -> GetParticleMomentumDirection()).y();
		G4double pZ = given_momentum*GeV*(particleGun -> GetParticleMomentumDirection()).z();

	  anaRoot -> FillPrimaryVertex( 0,
					particleGun -> GetParticleDefinition() -> GetPDGEncoding(),
					particleGun -> GetParticleEnergy(),
					particleName -> GetPDGMass(),
					pX,
					pY,
					pZ);

	  particleGun->GeneratePrimaryVertex(anEvent);

  }
  else if ( useEventFile == 1 )
  {
	  if (openFile)
	  {
		  if (countTrackNum == 0) anaRoot -> BeginOfEvent(eventNum);

			beam -> GetBeam(countTrackNum);
//		  G4cout << tempTrackNum << tempParticleName << tempMass << tempPx << tempPy << tempPz << G4endl;
//		  if ( openFile.eof() ) break;
		  G4ThreeVector momentum(tempPx*GeV, tempPy*GeV, tempPz*GeV);
		  given_momentum = sqrt( momentum.x()*momentum.x() + momentum.y()*momentum.y() + momentum.z()*momentum.z() );
		  G4ThreeVector momentumDirection(momentum.x()/given_momentum, momentum.y()/given_momentum, momentum.z()/given_momentum);
		  G4ParticleDefinition *beamParticle = particleTable -> FindParticle(tempParticleName);
		  G4double particleMass = beamParticle -> GetPDGMass();
		  G4int numNucleon = beamParticle -> GetAtomicMass();
		  G4double k_energy = sqrt( given_momentum*given_momentum + particleMass*particleMass ) - particleMass;
//		  G4cout << G4BestUnit(k_energy, "Energy") << G4endl;

		  particleGun->SetParticlePosition(gun_pos);
		  particleGun->SetParticleDefinition(beamParticle);
//		  particleGun->SetParticleMomentum(momentum);
		  particleGun->SetParticleMomentumDirection(momentumDirection);
		  particleGun->SetParticleEnergy(k_energy);

/*
		  G4cout << G4endl;
		  G4cout << "========================= Settings =========================" << G4endl;
		  G4cout << std::setw(30) << "Particle: " << particleGun -> GetParticleDefinition() -> GetParticleName() << G4endl;
		  G4cout << std::setw(30) << "Number of Nucleons: " << beamParticle -> GetAtomicMass() << G4endl;
		  G4cout << std::setw(30) << "Mass: " << G4BestUnit(particleMass, "Energy") << "/c2" << G4endl;
		  G4cout << std::setw(30) << "Momentum: " << G4BestUnit(given_momentum, "Energy") << "/c" << G4endl;
		  G4cout << std::setw(30) << "Momentum Per Nucleon: " << ( numNucleon != 0 ? G4BestUnit(given_momentum/numNucleon, "Energy") : G4BestUnit(given_momentum, "Energy") ) << "/c/u" << G4endl;
		  G4cout << std::setw(30) << "Kinetic Energy: " << G4BestUnit(particleGun -> GetParticleEnergy(), "Energy") << G4endl;
		  G4cout << std::setw(30) << "Kinetic Energy Per Nucleon: " << ( numNucleon != 0 ? G4BestUnit((particleGun -> GetParticleEnergy())/numNucleon, "Energy") : G4BestUnit(particleGun -> GetParticleEnergy(), "Energy") ) << "/u" << G4endl;
		  G4cout << std::setw(30) << "Dipole Magnetic Field: " << (LAMPSDC -> GetDPField())*1000 << " T" << G4endl;
		  G4cout << std::setw(30) << "Momentum Direction: " << particleGun -> GetParticleMomentumDirection() << G4endl;
		  G4cout << std::setw(30) << "Particle Gun Position: " << particleGun -> GetParticlePosition() << G4endl;
		  G4cout << "============================================================" << G4endl;
		  G4cout << G4endl;
*/
		  
		  anaRoot -> FillPrimaryVertex( countTrackNum,
																		particleGun -> GetParticleDefinition() -> GetPDGEncoding(),
																		particleGun -> GetParticleEnergy(),
																		particleMass,
																		momentum.x(),
																		momentum.y(),
																		momentum.z() );

		  particleGun -> GeneratePrimaryVertex(anEvent);

/*
		  countTrackNum++;
		  if (countTrackNum == tempTrackNum) {
			countTrackNum = 0;
		  	eventNum++;
			if (eventNum%10 == 0) G4cout << eventNum << " events are completed!!!!" << G4endl;
			if (eventNum == 50) {
				eventNum = 0;
				fileNum++;
				anaRoot -> EndOfRun();
				anaRoot -> BeginOfRun(fileNum);
			}
		  }
*/
//		  if (tempTrackNum == NULL ) G4cout << "File ended." << G4endl;
	  }
  }

/* Genie
  mom_pp = 3.0; // GeV/c
  theta=-10.*deg;
  phi=0.*deg;
  mom1[0] = mom_pp*sin(theta)*cos(phi);
  mom1[1] = mom_pp*sin(theta)*sin(phi);
  mom1[2] = mom_pp*cos(theta);
  mass = li3->GetPDGMass()/GeV; // mass (GeV)
  energy = sqrt(mom_pp*mom_pp + mass * mass)- mass; // kinetic energy (GeV)


  particleGun->SetParticleDefinition(li3);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(mom1[0],mom1[1],mom1[2]));
  particleGun->SetParticleEnergy(energy*GeV);
				 //  particleGun->SetParticlePosition(G4ThreeVector(vtx,vty,vtz));
  particleGun->GeneratePrimaryVertex(anEvent);

				 ///////////////////////////////////////////////
  mom_pp = 3.0; // GeV/c

  mom2[0] = mom_pp*sin(theta)*cos(phi);
  mom2[1] = mom_pp*sin(theta)*sin(phi);
  mom2[2] = mom_pp*cos(theta);
  mass = c6->GetPDGMass()/GeV; // mass (GeV)
  energy = sqrt(mom_pp*mom_pp + mass * mass)- mass; // kinetic energy (GeV)

  particleGun->SetParticleDefinition(c6);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(mom2[0],mom2[1],mom2[2]));
  particleGun->SetParticleEnergy(energy*GeV);
				 //  particleGun->SetParticlePosition(G4ThreeVector(vtx,vty,vtz));
  particleGun->GeneratePrimaryVertex(anEvent);

				 ///////////////////////////////////////////////
*/
  /*
  mom_pp = 4.; // GeV/c

  mom3[0] = mom_pp*sin(theta)*cos(phi);
  mom3[1] = mom_pp*sin(theta)*sin(phi);
  mom3[2] = mom_pp*cos(theta);
  mass = c6->GetPDGMass()/GeV; // mass (GeV)
  energy = sqrt(mom_pp*mom_pp + mass * mass)- mass; // kinetic energy (GeV)

  particleGun->SetParticleDefinition(c6);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(mom3[0],mom3[1],mom3[2]));
  particleGun->SetParticleEnergy(energy*GeV);
				 //  particleGun->SetParticlePosition(G4ThreeVector(vtx,vty,vtz));
  particleGun->GeneratePrimaryVertex(anEvent);


				 ///////////////////////////////////////////////
  mom_pp = 1.5; // GeV/c

  mom3[0] = mom_pp*sin(theta)*cos(phi);
  mom3[1] = mom_pp*sin(theta)*sin(phi);
  mom3[2] = mom_pp*cos(theta);
  mass = li3->GetPDGMass()/GeV; // mass (GeV)
  energy = sqrt(mom_pp*mom_pp + mass * mass)- mass; // kinetic energy (GeV)

  particleGun->SetParticleDefinition(li3);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(mom3[0],mom3[1],mom3[2]));
  particleGun->SetParticleEnergy(energy*GeV);
				 //  particleGun->SetParticlePosition(G4ThreeVector(vtx,vty,vtz));
  particleGun->GeneratePrimaryVertex(anEvent);

  */
}

//		  G4cout << tempTrackNum << tempParticleName << tempMass << tempPx << tempPy << tempPz << G4endl;
void LAMPSPrimaryGeneratorAction::SetBeam(G4int particleID, G4double pX, G4double pY, G4double pZ)
{
	tempParticleName = particleID;
	tempPx = pX;
	tempPy = pY;
	tempPz = pZ;
}

void LAMPSPrimaryGeneratorAction::AfterEndOfEventAction()
{
  countTrackNum++;
  if (countTrackNum == tempNumTracks) {
		countTrackNum = 0;
  	eventNum++;
//	if (eventNum%10 == 0) G4cout << eventNum << " events are completed!!!!" << G4endl;
//		if (eventNum == 50) {
//			eventNum = 0;
//			G4cout << "   rawData_" << fileNum << ".root is created!!!!" << G4endl;
//			fileNum++;
//		}
  }
}

void LAMPSPrimaryGeneratorAction::AfterEndOfSingleVertexEventAction()
{
	eventNum++;
}

void LAMPSPrimaryGeneratorAction::CloseOpenFile()
{
	delete beam;
}
