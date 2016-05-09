#include "Fields.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

const double Deg2Rad = acos(-1.)/180.;
const double Rad2Deg = 180./acos(-1.);

Fields::Fields(G4double DP_X_DIM, G4double DP_Y_DIM, G4double DP_Z_DIM, G4double NEW_CENTER, G4double d_FROM_NEW_CENTER_DP, G4double ROT_DP_ANGLE, G4double DP_STRENGTH)
:
X_DIM(DP_X_DIM), Y_DIM(DP_Y_DIM), Z_DIM(DP_Z_DIM), CENTER_SHIFT(NEW_CENTER), DP_SHIFT(d_FROM_NEW_CENTER_DP), ROT_ANGLE(ROT_DP_ANGLE), F_STRENGTH(DP_STRENGTH)
{
}  

void Fields::GetFieldValue(const double Point[3], double *Bfield) const
{
  const G4double r_in = 0.9*m;
  const G4double zmin = -0.7*m;
  const G4double zmax = 1.3*m;

  if ( (Point[1] >= -Y_DIM/2 && Point[1] <= Y_DIM/2)
       && (Point[0] >= tan(ROT_ANGLE + 90*Deg2Rad)*(Point[2] - CENTER_SHIFT) + X_DIM/2/cos(ROT_ANGLE + 90*Deg2Rad) &&
           Point[0] <= tan(ROT_ANGLE + 90*Deg2Rad)*(Point[2] - CENTER_SHIFT) - X_DIM/2/cos(ROT_ANGLE + 90*Deg2Rad))
       && (Point[0] <= tan(ROT_ANGLE)*(Point[2] - CENTER_SHIFT) + (Z_DIM/2 + DP_SHIFT)/cos(ROT_ANGLE) &&
           Point[0] >= tan(ROT_ANGLE)*(Point[2] - CENTER_SHIFT) - (Z_DIM/2 - DP_SHIFT)/cos(ROT_ANGLE)) ) {
    Bfield[0]=0.*tesla;
    Bfield[1]=F_STRENGTH;
    Bfield[2]=0.*tesla;
  } else if (Point[2] < zmax && Point[2] > zmin && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) < r_in) {
    Bfield[0] = 0.; 
    Bfield[1] = 0.; 
    Bfield[2] = 0.6*tesla; //KYO - solenoid 
  } else {
    Bfield[0]=0.*tesla;
    Bfield[1]=0.*tesla;
    Bfield[2]=0.*tesla;
  }
}
