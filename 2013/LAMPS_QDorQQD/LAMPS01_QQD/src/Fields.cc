#include "Fields.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#include "TMath.h"

#include <fstream>

const double Deg2Rad = acos(-1.)/180.;
const double Rad2Deg = 180./acos(-1.);

Fields::Fields(G4double DP_X_DIM, G4double DP_Y_DIM, G4double DP_Z_DIM, G4double NEW_CENTER, G4double d_FROM_NEW_CENTER_DP, G4double ROT_DP_ANGLE, G4double DP_STRENGTH)
:
X_DIM(DP_X_DIM), Y_DIM(DP_Y_DIM), Z_DIM(DP_Z_DIM), CENTER_SHIFT(NEW_CENTER), DP_SHIFT(d_FROM_NEW_CENTER_DP), ROT_ANGLE(ROT_DP_ANGLE), F_STRENGTH(DP_STRENGTH)
{
	std::ifstream data("./solenoid/solenoid.dat");

	G4double dummy, br, bz;
	for (G4int r = 0; r < 101; r++) {
		for (G4int z = 0; z < 201; z++) {
			data >> dummy >> dummy >> br >> bz;
			BrData[r][z] = br; 
			BzData[r][z] = bz;
		}
	}

	G4cout << "==============================================" << G4endl;
	G4cout << "= Solenoid OPERA data file is safely loaded! =" << G4endl;
	G4cout << "==============================================" << G4endl << G4endl;
}  

void Fields::GetFieldValue(const double Point[3], double *Bfield) const
{
  const G4double r_in = 0.9*m;
  const G4double zmin = -0.7*m;
  const G4double zmax = 1.3*m;

//	G4cout << "              " << G4endl;
//	G4cout << "              " << G4endl;
//	G4cout << "=====GetFieldValue start!!=======" << G4endl;

	const G4double Q1_F_GRADIENT = -(0.6042618714/300)*tesla;
	const G4double Q2_F_GRADIENT = (0.5465580404/400)*tesla;

//	const G4double Q1_F_GRADIENT = -(0.6285044814/300)*tesla;
//	const G4double Q2_F_GRADIENT = (0.5574894733/400)*tesla;

/*
  if ( (Point[1] >= -Y_DIM/2 && Point[1] <= Y_DIM/2)
       && (Point[0] >= tan(ROT_ANGLE + 90*Deg2Rad)*(Point[2] - CENTER_SHIFT) + X_DIM/2/cos(ROT_ANGLE + 90*Deg2Rad) &&
           Point[0] <= tan(ROT_ANGLE + 90*Deg2Rad)*(Point[2] - CENTER_SHIFT) - X_DIM/2/cos(ROT_ANGLE + 90*Deg2Rad))
       && (Point[0] <= tan(ROT_ANGLE)*(Point[2] - CENTER_SHIFT) + (Z_DIM/2 + DP_SHIFT)/cos(ROT_ANGLE) &&
           Point[0] >= tan(ROT_ANGLE)*(Point[2] - CENTER_SHIFT) - (Z_DIM/2 - DP_SHIFT)/cos(ROT_ANGLE)) ) {
*/
	if ( (Point[1] >= -0.2*m && Point[1] <=0.2*m) 
			&&  Point[2]>=2.9*m 
			&& ( sqrt((Point[0]-2.2*m)*(Point[0]-2.2*m)+(Point[2]-2.9*m)*(Point[2]-2.9*m)) >= 1.0*m && sqrt((Point[0]-2.2*m)*(Point[0]-2.2*m)+(Point[2]-2.9*m)*(Point[2]-2.9*m)) <= 3.2*m )
//			&& Point[0] < -tan(35*Deg2Rad)*Point[2]+tan(35*Deg2Rad)*2.9*m+2.2*m )  {
			&& Point[0] < -tan(25*Deg2Rad)*Point[2] + tan(25*Deg2Rad)*2.9*m + ( 1-cos(55*Deg2Rad)+tan(25*Deg2Rad)*sin(55*Deg2Rad) )*2.2*m  )  {
    Bfield[0]=0.*tesla;
//    Bfield[1]=F_STRENGTH;
    Bfield[1]=-0.2942359687*tesla;
    Bfield[2]=0.*tesla;
//	G4cout << "===== DP======" << G4endl;
	//G4cout << "Pointx = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
	//G4cout << "Bx = " << Bfield[0] << "By = " << Bfield[1] << "Bz = " << Bfield[2] << G4endl;
	//G4cout << "              " << G4endl;

  } else if (Point[2] < zmax && Point[2] > zmin && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) < r_in) {
	G4double r = sqrt(Point[0]*Point[0] + Point[1]*Point[1]);
	G4double phi = TMath::ATan2(Point[1], Point[0]);

	G4double rPos = r/10.;
	G4double zPos = (Point[3] + 300)/10.;

	G4int rIndex = (G4int)rPos;
	G4int zIndex = (G4int)zPos;

	G4double rRatio = rPos - rIndex;
	G4double zRatio = zPos - zIndex;

	G4double Br = BrData[rIndex][zIndex]*rRatio + BrData[rIndex + 1][zIndex]*(1 - rRatio);
	G4double Bz = BzData[rIndex][zIndex]*zRatio + BzData[rIndex][zIndex + 1]*(1 - zRatio);

//	Bfield[0] = Br*TMath::Cos(phi)*tesla;
//	Bfield[1] = Br*TMath::Sin(phi)*tesla;
//	Bfield[2] = Bz*tesla;
//	G4cout << "===== SLND======" << G4endl;

    Bfield[0] = 0.; 
    Bfield[1] = 0.; 
    Bfield[2] = 0.*tesla; //KYO - temp 
//    Bfield[2] = 0.6*tesla; //KYO - solenoid 
	} else if( Point[2]<=(1750*mm+(500*mm/2)) && Point[2]>=(1750*mm-(500*mm/2)) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) <= 300*mm  ) {
		Bfield[0] = Q1_F_GRADIENT*Point[1];
		Bfield[1] = Q1_F_GRADIENT*Point[0];
		Bfield[2] = 0.*tesla; // for Q1
//	G4cout << "===== Q1======" << G4endl;

	} else if(Point[2]<=(2450*mm+(500*mm/2)) && Point[2]>=(2450*mm-(500*mm/2)) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) <= 400*mm ) {
//	} else if(Point[2]<=(Q2_SHIFT+(Q2_Z_DIM/2)) && Point[2]>=(Q2_SHIFT-(500*mm/2)) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) < 400*mm ) {
		Bfield[0] = Q2_F_GRADIENT*Point[1];
		Bfield[1] = Q2_F_GRADIENT*Point[0];
		Bfield[2] = 0.*tesla; //for Q2
//	G4cout << "===== Q2======" << G4endl;
  } else {
    Bfield[0]=0.*tesla;
    Bfield[1]=0.*tesla;
    Bfield[2]=0.*tesla; 
  }
/*
	if(Bfield[0]!=0 || Bfield[1]!=0 || Bfield[2]!=0) {
	G4cout << "              " << G4endl;
	G4cout << "=====GetFieldValue end!!=======" << G4endl;
	G4cout << "Pointx = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
	G4cout << "Bx = " << Bfield[0] << "By = " << Bfield[1] << "Bz = " << Bfield[2] << G4endl;
	G4cout << "=====GetFieldValue end!!=======" << G4endl;
	}

	G4cout << "              " << G4endl;
	G4cout << "              " << G4endl;
*/
}
