#include "Fields.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#include "TMath.h"

#include <fstream>

const double Deg2Rad = acos(-1.)/180.;
const double Rad2Deg = 180./acos(-1.);

//define the Enge function
double EngeFunctionQ(G4double z_q);
double EngeFunctionDP(G4double z_dp);

Fields::Fields(G4double DP_X_DIM, G4double DP_Y_DIM, G4double DP_Z_DIM, G4double NEW_CENTER, G4double d_FROM_NEW_CENTER_DP, G4double ROT_DP_ANGLE, G4double DP_STRENGTH)
:
X_DIM(DP_X_DIM), Y_DIM(DP_Y_DIM), Z_DIM(DP_Z_DIM), CENTER_SHIFT(NEW_CENTER), DP_SHIFT(d_FROM_NEW_CENTER_DP), ROT_ANGLE(ROT_DP_ANGLE), F_STRENGTH(DP_STRENGTH)
{

	//open the field map for the solenoid
	std::ifstream data("./solenoid/solenoid.dat");

	G4double dummy, br, bz;
	for (G4int r = 0; r < 101; r++) {
		for (G4int z = 0; z < 201; z++) {
			data >> dummy >> dummy >> br >> bz;
			BrData[r][z] = -br; // both br and bz should have opposite sign to change the field direction!
			BzData[r][z] = -bz;
		}
	}

	G4cout << "==============================================" << G4endl;
	G4cout << "= Solenoid OPERA data file is safely loaded! =" << G4endl;
	G4cout << "==============================================" << G4endl << G4endl;
}  

void Fields::GetFieldValue(const double Point[3], double *Bfield) const
{
  const G4double r_in = 1.0*m;
  const G4double zmin = -0.7*m;
  const G4double zmax = 1.3*m;

//KYO - particle coordinates are printed regardless of the existence of the B field
//	G4cout << "Track of the particle (mm)" << G4endl;
//	G4cout << Point[0] <<" "<<Point[1]<<" "<<Point[2]<< G4endl;

	// Gradient == Bmax/radius (T/mm)
	const G4double Q1_F_GRADIENT = -(0.2830468941/200)*tesla; // unit = tesla/mm 
//	const G4double Q2_F_GRADIENT = (0.2832248357/350)*tesla; // unit = tesla/mm
	const G4double DP_FieldVal=-0.3596214951*tesla;
	G4double z_dp_ent = 0*m; // absolute distance b/w point(Point[0],[1],[2]) and line(DP EFB)
	G4double z_dp_exit = 0*m; //absolute distance b/w point(Point[0],[1],[2]) and line(DP EFB)

	// define the field regions for DP, Solenoid, Q1 and Q2
 if ( (Point[1] >= -0.2*m && Point[1] <= 0.2*m)
			&& Point[0] >= tan(65*Deg2Rad)*(Point[2] - 3.0*m)
	 		&& Point[0] <= tan(65*Deg2Rad)*(Point[2] - 3.0*m + 0.34*m/sin(25*Deg2Rad))
			&& Point[0] >= -tan(25*Deg2Rad)*Point[2] +(-0.963699*m)-(-tan(25*Deg2Rad)*(2.55602*m))
			&& Point[0] <= -tan(25*Deg2Rad)*Point[2] +(0.995759*m)-(-tan(25*Deg2Rad)*(3.46433*m))
			) {
				z_dp_ent = TMath::Abs(tan(65*Deg2Rad)*Point[2]-Point[0]-3.0*m*tan(65*Deg2Rad)) / TMath::Sqrt(TMath::Power(tan(65*Deg2Rad),2)+TMath::Power(-1,2));
				Bfield[0]= 0.*tesla;
				Bfield[1]=DP_FieldVal*EngeFunctionDP(z_dp_ent);
				Bfield[2]= 0.*tesla;
//		G4cout << "=== DP entrance outside ===" << G4endl;	
 } else if( (Point[1] >= -0.2*m && Point[1] <= 0.2*m)
			&& Point[0] <= tan(65*Deg2Rad)*(Point[2] - 3.0*m)
			&& Point[0] >= tan(85*Deg2Rad)*Point[2] +(0.995759*m)-(tan(85*Deg2Rad)*(3.46433*m))
			&& sqrt((Point[0]-1.8*m)*(Point[0]-1.8*m)+(Point[2]-3.0*m)*(Point[2]-3.0*m)) <= 2.8*m 
			) {
				z_dp_ent = TMath::Abs(tan(65*Deg2Rad)*Point[2]-Point[0]-3.0*m*tan(65*Deg2Rad)) / TMath::Sqrt(TMath::Power(tan(65*Deg2Rad),2)+TMath::Power(-1,2));
				Bfield[0]= 0.*tesla;
				Bfield[1]=DP_FieldVal*EngeFunctionDP(-z_dp_ent);
				Bfield[2]= 0.*tesla;
//		G4cout << "=== DP entrance inside (non overlapped)  ===" << G4endl;	
 } else if( (Point[1] >= -0.2*m && Point[1] <= 0.2*m)
			&& Point[0] <= tan(85*Deg2Rad)*Point[2] +(0.995759*m)-(tan(85*Deg2Rad)*(3.46433*m))
			&& Point[0] <= -tan(25*Deg2Rad)*Point[2] +(0.995759*m)-(-tan(25*Deg2Rad)*(3.46433*m))
			&& sqrt((Point[0]-1.8*m)*(Point[0]-1.8*m)+(Point[2]-3.0*m)*(Point[2]-3.0*m)) <= 2.8*m 
			) {
				z_dp_ent = TMath::Abs(tan(65*Deg2Rad)*Point[2]-Point[0]-3.0*m*tan(65*Deg2Rad)) / TMath::Sqrt(TMath::Power(tan(65*Deg2Rad),2)+TMath::Power(-1,2));
				z_dp_exit = TMath::Abs(tan(5*Deg2Rad)*Point[2]+Point[0]-3.0*m*tan(5*Deg2Rad)- (1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m ) / TMath::Sqrt(TMath::Power(tan(5*Deg2Rad),2)+TMath::Power(1,2));
				Bfield[0]= 0.*tesla;
				Bfield[1]=DP_FieldVal*EngeFunctionDP(-z_dp_ent)*EngeFunctionDP(-z_dp_exit);
				Bfield[2]= 0.*tesla;
//		G4cout << "=== DP inside (overlapped)  ===" << G4endl;	
 } else if( (Point[1] >= -0.2*m && Point[1] <= 0.2*m)
			&& Point[0] <= -tan(5*Deg2Rad)*(Point[2]-3.0*m) + ( 1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m 
			&& Point[0] >= -tan(25*Deg2Rad)*Point[2] +(0.995759*m)-(-tan(25*Deg2Rad)*(3.46433*m))
			&& sqrt((Point[0]-1.8*m)*(Point[0]-1.8*m)+(Point[2]-3.0*m)*(Point[2]-3.0*m)) <= 2.8*m 
			) {
				z_dp_exit = TMath::Abs(tan(5*Deg2Rad)*Point[2]+Point[0]-3.0*m*tan(5*Deg2Rad)- (1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m ) / TMath::Sqrt(TMath::Power(tan(5*Deg2Rad),2)+TMath::Power(1,2));
				Bfield[0]= 0.*tesla;
				Bfield[1]=DP_FieldVal*EngeFunctionDP(-z_dp_exit);
				Bfield[2]= 0.*tesla;
//		G4cout << "=== DP entrance inside (non overlapped)  ===" << G4endl;	
 } else if( (Point[1] >= -0.2*m && Point[1] <= 0.2*m)
			&& Point[0] >= -tan(5*Deg2Rad)*(Point[2]-3.0*m) + ( 1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m 
			&& Point[0] <= -tan(5*Deg2Rad)*(Point[2]-3.0*m) + ( 1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m + 0.34*m/cos(5*Deg2Rad) 
			&& Point[0] >= tan(85*Deg2Rad)*Point[2] +(0.807325*m)-(tan(85*Deg2Rad)*(5.61813*m))
			&& Point[0] <= tan(85*Deg2Rad)*Point[2] +(0.995759*m)-(tan(85*Deg2Rad)*(3.46433*m))
			) {
				z_dp_exit = TMath::Abs(tan(5*Deg2Rad)*Point[2]+Point[0]-3.0*m*tan(5*Deg2Rad)- (1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m ) / TMath::Sqrt(TMath::Power(tan(5*Deg2Rad),2)+TMath::Power(1,2));
				Bfield[0]= 0.*tesla;
				Bfield[1]=DP_FieldVal*EngeFunctionDP(z_dp_exit);
				Bfield[2]= 0.*tesla;
//		G4cout << "=== DP exit outside  ===" << G4endl;	

/*
	if ( (Point[1] >= -0.2*m && Point[1] <=0.2*m) 
			&&  Point[0] <= tan(65*Deg2Rad)*Point[2] - tan(65*Deg2Rad)*3.0*m 
			&& ( sqrt((Point[0]-1.8*m)*(Point[0]-1.8*m)+(Point[2]-3.0*m)*(Point[2]-3.0*m)) >= 0.8*m && sqrt((Point[0]-1.8*m)*(Point[0]-1.8*m)+(Point[2]-3.0*m)*(Point[2]-3.0*m)) <= 2.8*m )
			&& Point[0] <= -tan(5*Deg2Rad)*Point[2] + tan(5*Deg2Rad)*3.0*m + ( 1-cos(60*Deg2Rad)+tan(5*Deg2Rad)*sin(60*Deg2Rad) )*1.8*m  )  {
    Bfield[0]=0.*tesla;
//    Bfield[1]=F_STRENGTH;
    Bfield[1]=-0.3596214951*tesla;
    Bfield[2]=0.*tesla;
//	G4cout << "===== DP======" << G4endl;
	//G4cout << "Pointx(mm) = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
	//G4cout << "Bx(T) = " << Bfield[0]*1000 << "By = " << Bfield[1]*1000 << "Bz = " << Bfield[2]*1000 << G4endl;
	//G4cout << "              " << G4endl;
*/
  } else if (Point[2] < zmax && Point[2] > zmin && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) < r_in) {
	G4double r = sqrt(Point[0]*Point[0] + Point[1]*Point[1]);
	G4double phi = TMath::ATan2(Point[1], Point[0]);

	G4double rPos = r/10.;
	G4double zPos = (Point[2] + 700)/10.;

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
    Bfield[2] = 0.*tesla; //KYO - SLND is temporarily turned off!!!!!! 
//    Bfield[2] = 0.6*tesla; //KYO - solenoid
//
//	} else if( Point[2]<=(1750*mm+(500*mm/2)) && Point[2]>=(1750*mm-(500*mm/2)) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) <= 200*mm  ) {
//		Bfield[0] = Q1_F_GRADIENT*Point[1];
//		Bfield[1] = Q1_F_GRADIENT*Point[0];
//		Bfield[2] = 0.*tesla; // for Q1 w/o Enge function
//	G4cout << "===== Q1======" << G4endl;
	} else if( Point[2]<=(1500*mm+(500*mm/2)) && Point[2]>=(1500*mm) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) <= 200*mm  ) {
//		Bfield[0] = Q1_F_GRADIENT*Point[1]*1/(1+TMath::Exp(3.59463*((1500*mm-Point[2])/200*mm)));
//		Bfield[1] = Q1_F_GRADIENT*Point[0]*1/(1+TMath::Exp(3.59463*((1500*mm-Point[2])/200*mm)));
		Bfield[0] = Q1_F_GRADIENT*Point[1]*EngeFunctionQ(1500*mm-Point[2]);
		Bfield[1] = Q1_F_GRADIENT*Point[0]*EngeFunctionQ(1500*mm-Point[2]);
		Bfield[2] = 0.*tesla;
//		G4cout << "===Q1 entrance===" << G4endl;
//		G4cout << "Pointx(mm) = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
//		G4cout << "Bx(T) = " << Bfield[0]*1000 << "By = " << Bfield[1]*1000 << "Bz = " << Bfield[2]*1000 << G4endl;
//		G4cout << "              " << G4endl;
	} else if( Point[2]<=(2000*mm+100*mm) && Point[2]>=(2000*mm-(500*mm/2)) && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) <= 200*mm  ) {
//		Bfield[0] = Q1_F_GRADIENT*Point[1]*1/(1+TMath::Exp(3.59463*((Point[2]-2000*mm)/200*mm)));
//		Bfield[1] = Q1_F_GRADIENT*Point[0]*1/(1+TMath::Exp(3.59463*((Point[2]-2000*mm)/200*mm)));
		Bfield[0] = Q1_F_GRADIENT*Point[1]*EngeFunctionQ(Point[2]-2000*mm);
		Bfield[1] = Q1_F_GRADIENT*Point[0]*EngeFunctionQ(Point[2]-2000*mm);
		Bfield[2] = 0.*tesla;
//		G4cout << "===Q1 exit===" << G4endl;
//		G4cout << "Pointx(mm) = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
//		G4cout << "Bx(T) = " << Bfield[0]*1000 << "By = " << Bfield[1]*1000 << "Bz = " << Bfield[2]*1000 << G4endl;
//		G4cout << "              " << G4endl;
	}	else {
    Bfield[0]=0.*tesla;
    Bfield[1]=0.*tesla;
    Bfield[2]=0.*tesla; 
  }
/*
	if(Bfield[0]!=0 || Bfield[1]!=0 || Bfield[2]!=0) {
	G4cout << "              " << G4endl;
	G4cout << "=====GetFieldValue end!!=======" << G4endl;
	G4cout << "Pointx(mm) = " << Point[0] << "Pointy = " << Point[1] << "Pointz = " << Point[2] << G4endl;
	G4cout << "Bx(T) = " << Bfield[0]*1000 << "By = " << Bfield[1]*1000 << "Bz = " << Bfield[2]*1000 << G4endl;
	G4cout << "              " << G4endl;
	}
*/
}

double EngeFunctionQ(G4double z_q) {
	G4double gap_q = 200*mm;
	G4double b2=3.59463;
	return 1/(1+TMath::Exp(b2*(z_q/gap_q)));
}

double EngeFunctionDP(G4double z_dp) {
	G4double gap_dp=200*mm;
	G4double a1=0.205133;
	G4double a2=0.804972;
	G4double a3=-0.141308;
	G4double a4=0.050050;
	G4double a5=0.000076;
	G4double a6=0.005197;
	return 1/(1+TMath::Exp(a1+a2*(z_dp/gap_dp)+a3*TMath::Power(z_dp/gap_dp,2)+a4*TMath::Power(z_dp/gap_dp,3)+a5*TMath::Power(z_dp/gap_dp,4)+a6*TMath::Power(z_dp/gap_dp,5)));
}
