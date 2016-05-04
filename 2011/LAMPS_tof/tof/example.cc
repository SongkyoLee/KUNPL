#include "G4RunManager.hh"
#include "A01PhysicsList.hh"
#include "exampleDetectorConstruction.hh"
#include "examplePrimaryGeneratorAction.hh"
#include "exampleEventAction.hh"

#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"

#include "G4VisExecutive.hh"

int main(int argc, char **argv)
{
  G4RunManager *runManager = new G4RunManager();

  exampleDetectorConstruction* exampleDC = new exampleDetectorConstruction();
  runManager -> SetUserInitialization(exampleDC);

  A01PhysicsList* PhysicsList = new A01PhysicsList();
  runManager -> SetUserInitialization(PhysicsList);

  examplePrimaryGeneratorAction* examplePGA = new examplePrimaryGeneratorAction();
  runManager -> SetUserAction(examplePGA);

  exampleEventAction* exampleEA = new exampleEventAction();
  runManager -> SetUserAction(exampleEA);

  runManager->Initialize();

  G4VisManager* visManager = new G4VisExecutive();
  visManager -> Initialize();

  if (argc = 1) // Batch mode : when there is no macro file
  {
    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  else // Interactive mode : when there is a marco file
  {
    G4String command = "/control/execute";
    G4String fileName = argv [1];

    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI -> ApplyCommand(command + fileName);

    G4UIsession* session = new G4UIterminal(new	G4UItcsh);
    session -> SessionStart();
    delete session;
  }

  delete runManager;

  return 0;
}
