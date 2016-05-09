// ====================================================================
//   LAMPSField.hh
// ====================================================================

#include "LAMPSField.hh"
#include <fstream>
#include <iostream>


LAMPSField::LAMPSField(char* fname)
{

  std::ifstream ifs(fname);

  printf("reading TOSCA file \n");

  for(int ix = 0;ix<MAX_DIM_X_TOSCA;ix++){
    for(int iy = 0;iy<MAX_DIM_Y_TOSCA;iy++){
      for(int iz = 0;iz<MAX_DIM_Z_TOSCA;iz++){
	ifs >> xTosca[ix] >> yTosca[iy] >> zTosca[iz] >>
	  bTosca[0][ix][iy][iz] >> bTosca[1][ix][iy][iz] >> bTosca[2][ix][iy][iz];

	bTosca[0][ix][iy][iz] *= tesla;
	bTosca[1][ix][iy][iz] *= tesla;
	bTosca[2][ix][iy][iz] *= tesla;
	//	bTosca[1][ix][iy][iz] += 0.05*tesla;
	//	printf("%f %f %f\n",bTosca[0][ix][iy][iz],bTosca[2][ix][iy][iz],bTosca[2][ix][iy][iz]);
	zTosca[iz] += solenoidOffset;     // Center of Solenoid
      }
    }
  }
  //  printf("tesla = %f\n",tesla);
  //  printf("deg = %f\n",deg);
  //  printf("mm = %f\n",mm);
  //  printf("GeV = %f\n",GeV);
  printf("Finish reading TOSCA file \n");

}
/////////////////////////////////////////////////////////////////////////////
void LAMPSField::GetFieldValue(const G4double Point[3], G4double Bfield[3]) const
/////////////////////////////////////////////////////////////////////////////
{
  //  const G4double Bz= 2.6*tesla;

  //  const G4double Bz= 2.0*tesla;
  //  const G4double xmax = 300.0*mm;
  //  const G4double ymax = 300.0*mm;
  //  const G4double zmax = 498.5*mm;
  //  const G4double zmin = -501.5*mm;
  //  const G4double xmax = 280.0*mm;
  //  const G4double ymax = 280.0*mm;
  //  const G4double zmax = 478.5*mm;
  //  const G4double zmin = -481.5*mm;
  int iX,iY,iZ;

  const G4double r_in = 0.9*m;
  const G4double zmin = -1.0*m;
  const G4double zmax = 1.0*m;

  const G4double xmin = 0.9*m;
  const G4double xmax = 1.4*m;
  const G4double ymin = 0.9*m;
  const G4double ymax = 1.3*m;

  if (Point[2] < zmax && Point[2] > zmin && sqrt(Point[0]*Point[0] + Point[1]*Point[1]) < r_in) {
    Bfield[0] = 0.;
    Bfield[1] = 0.;
    Bfield[2] = 1.0*tesla; 
  } else { 
    Bfield[0] = 0.;
    Bfield[1] = 0.;
    Bfield[2] = 0.; 
  }
  return;

  iX = (int) ((Point[0]-xTosca[0])/BFIELD_GRID_X);
  iY = (int) ((Point[1]-yTosca[0])/BFIELD_GRID_Y);
  iZ = (int) ((Point[2]-zTosca[0])/BFIELD_GRID_Z);
  
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  

  if(Point[2]<zmax && Point[2]>zmin && abs(Point[0])<xmax && abs(Point[1])<ymax) {


    double s,t,u;
    double sp, tp, up;

    /*
     *    bTosca[0] : BX
     *    bTosca[1] : BY
     *    bTosca[2] : BZ
     *    bOut[0]   : Bx (at interior point)
     *    bOut[1]   : By (at interior point)
     *    bOut[2]   : Bz (at interior point)
     */

    s = (Point[0] - xTosca[iX]) / BFIELD_GRID_X;
    t = (Point[1] - yTosca[iY]) / BFIELD_GRID_Y;
    u = (Point[2] - zTosca[iZ]) / BFIELD_GRID_Z;

    G4cout << "---------------------------------------------------------------------" << BFIELD_GRID_X << "   " << BFIELD_GRID_Y << "   " << BFIELD_GRID_Z << G4endl;

    sp = 1.0-s; tp = 1.0-t;  up = 1.0-u; 

    for (int i=0; i<3; i++){
      double b[8]= {
	bTosca[i][iX][iY][iZ],       bTosca[i][iX+1][iY][iZ],
	bTosca[i][iX+1][iY][iZ+1],   bTosca[i][iX][iY][iZ+1],
	bTosca[i][iX][iY+1][iZ],     bTosca[i][iX+1][iY+1][iZ],
	bTosca[i][iX+1][iY+1][iZ+1], bTosca[i][iX][iY+1][iZ+1] };

      double bTmp  = up*b[0] + u*b[3]; // up*(iX,  iY,  iZ) + u*(iX,  iY,  iZ+1) 
      double bTmp1 = up*b[1] + u*b[2]; // up*(iX+1,iY,  iZ) + u*(iX+1,iY,  iZ+1) 
      double bTmp2 = up*b[4] + u*b[7]; // up*(iX,  iY+1,iZ) + u*(iX,  iY+1,iZ+1) 
      double bTmp3 = up*b[5] + u*b[6]; // up*(iX+1,iY+1,iZ) + u*(iX+1,iY+1,iZ+1) 

      Bfield[i] =  sp * (tp * bTmp + t * bTmp2) + s * (tp * bTmp1 + t * bTmp3) ;
     
    }

    
    //    Bfield[0] = 0.;
    //    Bfield[1] = 0.;
    //    Bfield[2] = 2.0*tesla; 

  } else { 
    Bfield[0] = 0.;
    Bfield[1] = 0.;
    Bfield[2] = 0.; 
  }
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  //  printf("P(x,y,z) %f %f %f\n",Point[0],Point[1],Point[2]);
  //  printf("B(x,y,z) %f %f %f\n",Bfield[0],Bfield[1],Bfield[2]);
}
