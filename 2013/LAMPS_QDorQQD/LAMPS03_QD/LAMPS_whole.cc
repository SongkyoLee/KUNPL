// ====================================================================
//  LAMPS_whole.cc
// ====================================================================
#include "G4RunManager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "LAMPSDetectorConstruction.hh"
//#include "LAMPSPhysicsList.hh"
#include "A01PhysicsList.hh"
#include "LAMPSPrimaryGeneratorAction.hh"
#include "LAMPSRunAction.hh"
#include "LAMPSEventAction.hh"

#ifdef G4VIS_USE
#include "LAMPSVisManager.hh"
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "LAMPSAnaRoot.hh"
#include "LAMPSSteppingAction.hh"

#include <fstream>
using namespace std;
//std::ofstream ofs;
//ofstream ofs;

// ====================================================================
//     main
// ====================================================================
int main(int argc, char** argv) 
{
  // run manager
  G4RunManager* runManager= new G4RunManager;  G4cout << G4endl;

  LAMPSAnaRoot *anaRoot = new LAMPSAnaRoot();

  LAMPSDetectorConstruction* LAMPSDC = new LAMPSDetectorConstruction();
  // set mandatory user initialization classes...
  // detector setup
  runManager-> SetUserInitialization(LAMPSDC);
  // particles and physics processes
  //  runManager-> SetUserInitialization(new LAMPSPhysicsList);
  runManager-> SetUserInitialization(new A01PhysicsList);

  LAMPSPrimaryGeneratorAction* PrimaryGenerator = new LAMPSPrimaryGeneratorAction(LAMPSDC, anaRoot, runManager);
  LAMPSRunAction* RunAct = new LAMPSRunAction();
  LAMPSEventAction* EventAct = new LAMPSEventAction(anaRoot, PrimaryGenerator);
  LAMPSSteppingAction *stepAct = new LAMPSSteppingAction();

  // primary generator
  runManager -> SetUserAction(PrimaryGenerator);
  // user action classes... (optional)
  runManager -> SetUserAction(RunAct);
  runManager -> SetUserAction(EventAct);
  runManager -> SetUserAction(stepAct);

#ifdef G4VIS_USE
  // initialize visualization package
  // G4VisManager* visManager= new LAMPSVisManager;
  G4VisManager* visManager= new G4VisExecutive;
  visManager-> Initialize();
  G4cout << G4endl;
#endif

  // user session...
  runManager-> Initialize();

  G4UImanager* UImanager= G4UImanager::GetUIpointer();
    
  if(argc==1) { // interactive session, if no arguments given
/*
    // Code for the OGLIXm
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    ui -> SessionStart();
    delete ui;
*/

    // tcsh-like
    G4UItcsh* tcsh= new G4UItcsh("LAMPS(%s)[%/][%h]:");
    G4UIterminal* session= new G4UIterminal(tcsh);
    //tcsh-> SetLsColor(GREEN, CYAN);
    session-> SessionStart();
    delete session; 

  } else if (argc==2) { // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager-> ApplyCommand(command+fileName);


    G4UItcsh* tcsh= new G4UItcsh("LAMPS(%s)[%/][%h]:");
    G4UIterminal* session= new G4UIterminal(tcsh);
    session-> SessionStart();
    delete session; 
    /*
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    ui -> SessionStart();
    delete ui;
    */
  } else if (argc==3) {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager-> ApplyCommand(command+fileName);

    G4UItcsh* tcsh= new G4UItcsh("LAMPS(%s)[%/][%h]:");
    G4UIterminal* session= new G4UIterminal(tcsh);
    session-> SessionStart();
    delete session; 
	}

  // terminating...
#ifdef G4VIS_USE
  delete visManager;
#endif

	delete anaRoot;
  delete runManager;  G4cout << G4endl;
  return 0;
}

