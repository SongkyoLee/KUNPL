#ifndef exampleDetectorConstruction_h
#define exampleDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4Element.hh"
#include "G4Material.hh"

class G4VPhysicalVolume;

class exampleDetectorConstruction: public G4VUserDetectorConstruction
{
public:
    exampleDetectorConstruction();
    virtual ~exampleDetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
    
private:
    
    
    void DefineDimensions();
    
    void ConstructMaterials();
    void DestructMaterials();
    
    G4Element *elHe;
    G4Element *elSi;
    G4Element *elCs;
    G4Element *elI;
    
    G4Material *Helium;
    G4Material *Silicon;
    G4Material *CsI;
    G4Material *Vacuum;
    
    G4double labX, labY, labZ, distS, coverage, angle1, angle2;
    G4double detS, detC, target;
    G4int pad, i;
};
#endif
