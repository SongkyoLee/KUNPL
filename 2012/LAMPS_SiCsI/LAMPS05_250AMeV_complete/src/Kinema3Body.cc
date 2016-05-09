#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Kinema3Body.hh"
#include "Randomize.hh"

#define PI 3.141592654

Kinema3Body::Kinema3Body(double m1, double m2, double m3, double m4, double m5, double p1, double p2)
{



  double ECM, m12;
  double vx3, vy3, vz3; /* unit vector */
  double vx4, vy4, vz4; /* unit vector */
  double vx5, vy5, vz5; /* unit vector */
  double theta1, theta2; /* tmpolary; theta1 represents 1st kinematics of 
			  m1,m2,m12, and m5.
			 theta2 represents 2nd kinematics of m12, m3, and m4*/
  double phi3;         /* 2つめの運動学でのphi(CM system)*/ 
  double theta5,phi5;  /* 乱数をふったもの。log note p.43の座標系 */
  double Theta3,Phi3;  /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta4,Phi4;  /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta5,Phi5;  /* 座標系をかえてTheta,Phiをあらわしたもの */



  kin3.M_1 = m1;
  kin3.M_2 = m2;
  kin3.M_3 = m3;
  kin3.M_4 = m4;
  kin3.M_5 = m5;

  kin3.p_1_lab = p1;
  kin3.p_2_lab = p2;


  kin3.E_1_lab = p2E(kin3.p_1_lab, kin3.M_1);
  kin3.E_2_lab = p2E(kin3.p_2_lab, kin3.M_2);

  ECM = sqrt((kin3.E_1_lab+kin3.E_2_lab)*(kin3.E_1_lab+kin3.E_2_lab)
	     -(kin3.p_1_lab+kin3.p_2_lab)*(kin3.p_1_lab+kin3.p_2_lab));

  m12 = Calc_m12(m3, m4, m5, ECM);
  kin3.m34 = m12;
  //printf("m12=%f\n", m12);

  kin1 = Kinema2Body(m1, m2, m12, m5);
  kin1.SetMomentum(1, p1);
  kin1.SetMomentum(2, p2);
  kin1.SetThetaCM((double)RandSin());
  kin1.calc_kinema();
  phi5 = (360.0*(double)CLHEP::RandFlat::shoot());
  //phi5 = 360.0*(double)rand()/(RAND_MAX+1.0);

  kin3.Theta1CM = kin1.GetThetaCM();
  kin3.Phi1     = phi5;

  /* calculate m5 */
  theta5 = -kin1.GetPhiLab();
  vx5 = cos(PI*theta5/180.0);
  vy5 = sin(PI*theta5/180.0)*cos(PI*phi5/180.0);
  vz5 = -sin(deg2rad(theta5))*sin(deg2rad(phi5));
  CalcDistoribution(vx5, vy5, vz5, &Theta5, &Phi5);

  kin3.E_5_lab = kin1.GetEnergyLab(4);
  kin3.p_5_lab = kin1.GetMomentumLab(4);
  kin3.P_5_lab[0] = kin3.p_5_lab*vx5;
  kin3.P_5_lab[1] = kin3.p_5_lab*vy5;
  kin3.P_5_lab[2] = kin3.p_5_lab*vz5;
  kin3.theta5 = Theta5;
  kin3.phi5 = Phi5;

  /* calculate m3,m4 */
  kin2 = Kinema2Body(m12, 0.0, m3, m4);
  kin2.SetMomentum(1, kin1.GetMomentumLab(3));
  kin2.SetMomentum(2, 0.0);
  kin2.SetThetaCM((double)RandSin());
  kin2.calc_kinema();

  phi3 = (360.0*(double)CLHEP::RandFlat::shoot());
  //phi3 = 360.0*(double)rand()/(RAND_MAX+1.0);

  kin3.Theta2CM = kin2.GetThetaCM();
  kin3.Phi2     = phi3;

  /* m3 */
  theta1 = kin1.GetThetaLab();
  theta2 = kin2.GetThetaLab();

  vx3 = cos(deg2rad(theta2))*cos(deg2rad(theta1)) - 
      sin(deg2rad(theta1))*cos(deg2rad(phi3))*sin(deg2rad(theta2));

  vy3 = cos(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) +
     cos(deg2rad(theta1))*cos(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
        sin(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));

  vz3 = -sin(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) -
    cos(deg2rad(theta1))*sin(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
    cos(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));

  CalcDistoribution(vx3, vy3, vz3, &Theta3, &Phi3);

  kin3.E_3_lab = kin2.GetEnergyLab(3);
  kin3.p_3_lab = kin2.GetMomentumLab(3);
  kin3.P_3_lab[0] = kin3.p_3_lab*vx3;
  kin3.P_3_lab[1] = kin3.p_3_lab*vy3;
  kin3.P_3_lab[2] = kin3.p_3_lab*vz3;
  kin3.theta3 = Theta3;
  kin3.phi3 = Phi3;

  /* m4 */
  theta1 = kin1.GetThetaLab();
  theta2 = -kin2.GetPhiLab();

  vx4 = cos(deg2rad(theta2))*cos(deg2rad(theta1)) - 
      sin(deg2rad(theta1))*cos(deg2rad(phi3))*sin(deg2rad(theta2));

  vy4 = cos(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) +
     cos(deg2rad(theta1))*cos(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
        sin(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));

  vz4 = -sin(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) -
    cos(deg2rad(theta1))*sin(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
    cos(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));

  CalcDistoribution(vx4, vy4, vz4, &Theta4, &Phi4);

  kin3.E_4_lab = kin2.GetEnergyLab(4);
  kin3.p_4_lab = kin2.GetMomentumLab(4);
  kin3.P_4_lab[0] = kin3.p_4_lab*vx4;
  kin3.P_4_lab[1] = kin3.p_4_lab*vy4;
  kin3.P_4_lab[2] = kin3.p_4_lab*vz4;
  kin3.theta4 = Theta4;
  kin3.phi4 = Phi4;

  //Dump();
}

double Kinema3Body::p2E(double p,double m)
{
  return sqrt(p*p + m*m);
}

void Kinema3Body::CalcDistoribution(double unitx, double unity, double unitz, double *theta, double *phi)
{
  *theta = rag2deg(acos(unitx));

  if (unity>=0.0 && unitz>0.0) 
    *phi = rag2deg(acos(unity/sin(deg2rad(*theta))));
  else if (unity<0.0 && unitz>=0.0) 
    *phi = rag2deg(acos(unity/sin(deg2rad(*theta))));
  else if (unity<=0.0 && unitz<0.0) 
    *phi = 360.0-rag2deg(acos(unity/sin(deg2rad(*theta))));
  else if (unity>0.0 && unitz<=0.0) 
    *phi = 360.0-rag2deg(acos(unity/sin(deg2rad(*theta))));
  else {
    fprintf(stderr,
	  "Kinema3Body::CalcDistribution No such reagion unity=%f, unitz=%f\n",
	    unity, unitz);
    exit(1);
  }
  return;
}


double Kinema3Body::deg2rad(double theta) {
  return 3.141592654*theta/180.0;
}

double Kinema3Body::rag2deg(double rag)
{
  return 360.0 * rag/ (2.0 * 3.141592654);
}

double Kinema3Body::Calc_m12(double m1, double m2, double m3, double M)
{
  int success=0;
  double x, fx;
  double max;

  max = 1.2*GetMaxFunc(m1, m2, m3, M);
  do {
    x = ((M-m3)-(m1+m2))*CLHEP::RandFlat::shoot() + (m1+m2);
    //x = ((M-m3)-(m1+m2))*(double)rand()/(RAND_MAX+1.0) + (m1+m2);
    fx = ProFunction(x, m1, m2, m3, M);
    if (fx >= max*CLHEP::RandFlat::shoot())
      success = 1;
  } while (success==0);
  
  return x;
}

double Kinema3Body::GetMaxFunc( double m1, double m2, double m3, double M)
{
  double x;
  double delta;
  double val;
  double max=0.0;

  delta = ((M-m3)-(m1+m2))/1000.0;
  
  for (x=(m1+m2); x<=(M-m3); x=x+delta) {
    val = ProFunction(x, m1, m2, m3, M);
    if (val >= max)
      max = val;
  }
  return max;
}
  
double Kinema3Body::ProFunction(double m12, double m1, double m2, double m3, double M)
{
  double p1_star, p3;
  if (m12 >= m1+m2 && m12 <= M-m3) {
    p1_star = sqrt((m12*m12 - (m1+m2)*(m1+m2))*(m12*m12 - (m1-m2)*(m1-m2)))/(2.0*m12);
    p3 = sqrt((M*M - (m12+m3)*(m12+m3))*(M*M - (m12-m3)*(m12-m3)))/(2.0*M);
    
    return p1_star*p3;
  } else {
    fprintf(stderr, "Kinema3Body::ProFunction Not m1+m2 <= m12 <= M-m3\n");
    fprintf(stderr, "             m1=%f, m2=%f, m3=%f, M=%f, m12=%f\n",
	    m1,m2,m3,M,m12);
    exit(1);
  }
}
    
double Kinema3Body::RandSin(void)
{
  int success=0;
  double x,fx;

  do {
    x = 180.0 * (double)CLHEP::RandFlat::shoot();
    //x = 180.0 * (double)rand()/(RAND_MAX+1.0);
    fx = sin(deg2rad(x));
    if (fx >= (double)CLHEP::RandFlat::shoot())
      success = 1;
  } while (success==0);

  return x;
}

void Kinema3Body::Dump(void)
{
  printf("======Kinema3Body Dump======\n");
  printf("--Particle1--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin3.M_1, kin3.p_1_lab, kin3.E_1_lab);
  printf("--Particle2--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin3.M_2, kin3.p_2_lab, kin3.E_2_lab);
  printf("--Particle3--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin3.M_3, kin3.p_3_lab, kin3.E_3_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin3.P_3_lab[0], kin3.P_3_lab[1], kin3.P_3_lab[2],
	 kin3.theta3, kin3.phi3);
  printf("--Particle4--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin3.M_4, kin3.p_4_lab, kin3.E_4_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin3.P_4_lab[0], kin3.P_4_lab[1], kin3.P_4_lab[2],
	 kin3.theta4, kin3.phi4);
  printf("--Particle5--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin3.M_5, kin3.p_5_lab, kin3.E_5_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin3.P_5_lab[0], kin3.P_5_lab[1], kin3.P_5_lab[2],
	 kin3.theta5, kin3.phi5);

  printf("Energy:E1+E2=%f, E1+E2+E3=%f\n", kin3.E_1_lab+kin3.E_2_lab,
	 kin3.E_3_lab+kin3.E_4_lab+kin3.E_5_lab);
  printf("Momentum: x-> p1+p2=%f, p3+p4+p5=%f\n", kin3.p_1_lab+kin3.p_2_lab,
	 kin3.P_3_lab[0]+kin3.P_4_lab[0]+kin3.P_5_lab[0]);
  printf("          y-> p3+p4+p5=%f\n",
	 kin3.P_3_lab[1]+kin3.P_4_lab[1]+kin3.P_5_lab[1]);
  printf("          z-> p3+p4+p5=%f\n",
	 kin3.P_3_lab[2]+kin3.P_4_lab[2]+kin3.P_5_lab[2]);

  return;
}

double Kinema3Body::GetEnergy(int i)
{
  switch (i) {
  case 1:
    return kin3.E_1_lab;
    break;
  case 2:
    return kin3.E_2_lab;
    break;
  case 3:
    return kin3.E_3_lab;
    break;
  case 4:
    return kin3.E_4_lab;
    break;
  case 5:
    return kin3.E_5_lab;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetEnergy No such particle %d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetMomentum(int i)
{
  switch (i) {
  case 1:
    return kin3.p_1_lab;
    break;
  case 2:
    return kin3.p_2_lab;
    break;
  case 3:
    return kin3.p_3_lab;
    break;
  case 4:
    return kin3.p_4_lab;
    break;
  case 5:
    return kin3.p_5_lab;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetMomentum No such particle %d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetMomentum(int i, double *mom)
{
  switch (i) {
  case 1:
    mom[0] = kin3.p_1_lab;
    mom[1] = 0.0;
    mom[2] = 0.0;
    break;
  case 2:
    mom[0] = kin3.p_2_lab;
    mom[1] = 0.0;
    mom[2] = 0.0;
    break;
  case 3:
    mom[0] = kin3.P_3_lab[0];
    mom[1] = kin3.P_3_lab[1];
    mom[2] = kin3.P_3_lab[2];
    break;
  case 4:
    mom[0] = kin3.P_4_lab[0];
    mom[1] = kin3.P_4_lab[1];
    mom[2] = kin3.P_4_lab[2];
    break;
  case 5:
    mom[0] = kin3.P_5_lab[0];
    mom[1] = kin3.P_5_lab[1];
    mom[2] = kin3.P_5_lab[2];
    return kin3.p_5_lab;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetMomentum No such particle %d\n", i);
    exit(1);
  }
  return 0.0;
}

double Kinema3Body::GetTheta(int i)
{
  switch (i) {
  case 1:
    return 0.0;
    break;
  case 2:
    return 0.0;
    break;
  case 3:
    return kin3.theta3;
    break;
  case 4:
    return kin3.theta4;
    break;
  case 5:
    return kin3.theta5;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetTheta No such particle %d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetPhi(int i)
{
  switch (i) {
  case 1:
    return 0.0;
    break;
  case 2:
    return 0.0;
    break;
  case 3:
    return kin3.phi3;
    break;
  case 4:
    return kin3.phi4;
    break;
  case 5:
    return kin3.phi5;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetPhi No such particle %d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetThetaCM(int i)
{
  switch (i) {
  case 1:
    return kin3.Theta1CM;
    break;
  case 2:
    return kin3.Theta2CM;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetThetaCM index should be 1 or 2 ->%d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetPhiCM(int i)
{
  switch (i) {
  case 1:
    return kin3.Phi1;
    break;
  case 2:
    return kin3.Phi2;
    break;
  default:
    fprintf(stderr, "Kinema3Body::GetPhiCM index should be 1 or 2 ->%d\n", i);
    exit(1);
  }
}

double Kinema3Body::GetM34(void)
{
  return kin3.m34;
}

void Kinema3Body::RotateMom(int i, double deg, double *mom)
{
  double Sin,Cos;

  Sin=sin(deg2rad(deg));
  Cos=cos(deg2rad(deg));
  switch (i) {
  case 3:
    mom[0] = Cos*kin3.P_3_lab[0] - Sin*kin3.P_3_lab[1];
    mom[1] = Sin*kin3.P_3_lab[0] + Cos*kin3.P_3_lab[1];
    mom[2] = kin3.P_3_lab[2];
    break;
  case 4:
    mom[0] = Cos*kin3.P_4_lab[0] - Sin*kin3.P_4_lab[1];
    mom[1] = Sin*kin3.P_4_lab[0] + Cos*kin3.P_4_lab[1];
    mom[2] = kin3.P_4_lab[2];
    break;
  case 5:
    mom[0] = Cos*kin3.P_5_lab[0] - Sin*kin3.P_5_lab[1];
    mom[1] = Sin*kin3.P_5_lab[0] + Cos*kin3.P_5_lab[1];
    mom[2] = kin3.P_5_lab[2];
    break;
  default:
    fprintf(stderr, "Kinema3Body::RotateMom should be 3,4,5 ->%d\n",i);
    exit(1);
  }

}
