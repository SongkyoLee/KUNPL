// ====================================================================
//   LAMPSVisManager.hh
// ====================================================================
#ifndef LAMPS_VIS_MANAGER_H
#define LAMPS_VIS_MANAGER_H

#include "G4VisManager.hh"

class LAMPSVisManager : public G4VisManager {
public:
  LAMPSVisManager();
  virtual ~LAMPSVisManager();
  
private:
  virtual void RegisterGraphicsSystems();

};

#endif
