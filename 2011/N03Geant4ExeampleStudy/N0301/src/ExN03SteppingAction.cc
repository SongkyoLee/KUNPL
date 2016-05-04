//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN03SteppingAction.cc,v 1.15 2006/06/29 17:49:13 gunter Exp $
// GEANT4 tag $Name: geant4-09-03-patch-01 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN03SteppingAction.hh"

#include "ExN03DetectorConstruction.hh"
#include "ExN03EventAction.hh"

#include "G4Step.hh"
#include <fstream>
////#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN03SteppingAction::ExN03SteppingAction(ExN03DetectorConstruction* det,
                                         ExN03EventAction* evt)
:detector(det), eventaction(evt)					 
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN03SteppingAction::~ExN03SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN03SteppingAction::UserSteppingAction(const G4Step* aStep)
{

 
 // get volume of the current step
  G4VPhysicalVolume* volume 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // collect energy and track length step by step
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  G4double stepl = 0.;
  if (aStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    stepl = aStep->GetStepLength();   


//KYO : get layerNum, edep, globalTime and make <data.txt> file ------------------
  if (volume == detector->GetAbsorber())
{
 G4int layerNum 
  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
 G4double globalTime
  = aStep->GetPreStepPoint()->GetGlobalTime();

 std::ofstream G4fout("data.txt", std::ios::out | std::ios::app);
 G4cout<< "\t" << layerNum << "\t \t" << edep << "\t  \t" << globalTime << G4endl;
 if ( G4fout.is_open())
 G4fout << " " << layerNum << " " << edep << " " << globalTime << G4endl;

 eventaction->AddAbs(edep,stepl);
}
 // if (volume == detector->GetGap())      eventaction->AddGap(edep,stepl);
 
  //example of saving random number seed of this event, under condition
  //// if (condition) G4RunManager::GetRunManager()->rndmSaveThisEvent(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
