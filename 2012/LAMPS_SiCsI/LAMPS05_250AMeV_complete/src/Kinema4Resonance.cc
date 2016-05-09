#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "Kinema4Resonance.hh"
#include "Randomize.hh"
#include "G4ios.hh"

#define PI 3.141592654

Kinema4Resonance::Kinema4Resonance(double m1, double m2, double m3, double m4, double m5,  double m6,
				   double m_res1, double width1,  double m_res2, double width2,
				   double p1, double p2)
{
  double ECM;
  double vx_res1, vy_res1, vz_res1; /* unit vector */
  double vx_res2, vy_res2, vz_res2; /* unit vector */
  double vx3, vy3, vz3;             /* unit vector */
  double vx4, vy4, vz4;             /* unit vector */
  double vx5, vy5, vz5;             /* unit vector */
  double vx6, vy6, vz6;             /* unit vector */
  double theta1, theta2;            /* tmpolary; theta1 represents 1st kinematics of 
				       `m1,m2,m_res1, and m_res2.
				       theta2 represents 2nd kinematics of m3, m4, m5 and m6 */
  double phi3;                      /* 2つめの運動学でのphi(CM system)*/ 
  double phi5;                      /* 乱数をふったもの。log note p.43の座標系 */
  double theta_res1, theta_res2;    /* 乱数をふったもの。log note p.43の座標系 */
  double Theta3,Phi3;               /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta4,Phi4;               /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta5,Phi5;               /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta6,Phi6;               /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta_res1,Phi_res1;       /* 座標系をかえてTheta,Phiをあらわしたもの */
  double Theta_res2,Phi_res2;       /* 座標系をかえてTheta,Phiをあらわしたもの */


  // Get particle mass
  kin4.M_1 = m1;
  kin4.M_2 = m2;
  kin4.M_3 = m3;
  kin4.M_4 = m4;
  kin4.M_5 = m5;
  kin4.M_6 = m6;

  kin4.p_1_lab = p1;
  kin4.p_2_lab = p2;

  kin4.E_1_lab = p2E(kin4.p_1_lab, kin4.M_1);
  kin4.E_2_lab = p2E(kin4.p_2_lab, kin4.M_2);

  ECM = sqrt((kin4.E_1_lab+kin4.E_2_lab)*(kin4.E_1_lab+kin4.E_2_lab)
	     -(kin4.p_1_lab+kin4.p_2_lab)*(kin4.p_1_lab+kin4.p_2_lab));

  do {  // Generate Resonance 
    kin4.M_res1 = CLHEP::RandBreitWigner::shoot(m_res1, width1);
    kin4.M_res2 = CLHEP::RandBreitWigner::shoot(m_res2, width2);
  } while ((kin4.M_3+kin4.M_4 > kin4.M_res1 || kin4.M_res1 > ECM-kin4.M_res2)
	   || (kin4.M_5+kin4.M_6 > kin4.M_res2 || kin4.M_res2 > ECM-kin4.M_res1));

  //  kin4.M_res2 = m_res2;

  kin1 = Kinema2Body(m1, m2, kin4.M_res1, kin4.M_res2);
  kin1.SetMomentum(1, p1);
  kin1.SetMomentum(2, p2);
  kin1.SetThetaCM((double)RandSin());
  kin1.calc_kinema();
  phi5 = (360.0*(double)CLHEP::RandFlat::shoot());  // Rotation angle for reaction plane
  //  phi5 = 0.0;

  kin4.Theta1CM = kin1.GetThetaCM();
  kin4.Phi1     = phi5;

  /* calculate m_res1 */
  theta_res1 = kin1.GetThetaLab();
  vx_res1 = cos(deg2rad(theta_res1));
  vy_res1 = sin(deg2rad(theta_res1))*cos(deg2rad(phi5));
  vz_res1 = -sin(deg2rad(theta_res1))*sin(deg2rad(phi5)); // Why "-" sign ???

  CalcDistoribution(vx_res1, vy_res1, vz_res1, &Theta_res1, &Phi_res1);

  kin4.E_res1_lab = kin1.GetEnergyLab(3);
  kin4.p_res1_lab = kin1.GetMomentumLab(3);
  kin4.P_res1_lab[0] = kin4.p_res1_lab*vx_res1;
  kin4.P_res1_lab[1] = kin4.p_res1_lab*vy_res1;
  kin4.P_res1_lab[2] = kin4.p_res1_lab*vz_res1;
  kin4.theta_res1 = Theta_res1;
  kin4.phi_res1 = Phi_res1;

  //  printf("E_res1 = %f, p_res1 = %f\n",kin4.E_res1_lab, kin4.p_res1_lab);
  //  printf("theta_res1 = %f, phi_res1 = %f\n",Theta_res1, Phi_res1);
  
  /* calculate m_res2 */
  theta_res2 = -kin1.GetPhiLab();
  vx_res2 = cos(deg2rad(theta_res2));
  vy_res2 = sin(deg2rad(theta_res2))*cos(deg2rad(phi5));
  vz_res2 = -sin(deg2rad(theta_res2))*sin(deg2rad(phi5)); // Why "-" sign ???

  CalcDistoribution(vx_res2, vy_res2, vz_res2, &Theta_res2, &Phi_res2);

  kin4.E_res2_lab = kin1.GetEnergyLab(4);
  kin4.p_res2_lab = kin1.GetMomentumLab(4);
  kin4.P_res2_lab[0] = kin4.p_res2_lab*vx_res2;
  kin4.P_res2_lab[1] = kin4.p_res2_lab*vy_res2;
  kin4.P_res2_lab[2] = kin4.p_res2_lab*vz_res2;
  kin4.theta_res2 = Theta_res2;
  kin4.phi_res2 = Phi_res2;

  //  printf("E_res2 = %f, p_res2 = %f\n",kin4.E_res2_lab, kin4.p_res2_lab);
  //  printf("theta_res2 = %f, phi_res2 = %f\n",Theta_res2, Phi_res2);

  /* calculate m3,m4 */
  /* もしm_res1とm4が等しく、m3が0ならば
     resonanceの値をそのままm4にわたす。*/
  if (kin4.M_res1 == m4 && m3 == 0.0) {
    kin4.E_3_lab = 0.0;
    kin4.p_3_lab = 0.0;
    kin4.P_3_lab[0] = 0.0;
    kin4.P_3_lab[1] = 0.0;
    kin4.P_3_lab[2] = 0.0;
    kin4.theta3 = 0.0;
    kin4.phi3 = 0.0;

    kin4.E_4_lab = kin4.E_res1_lab;
    kin4.p_4_lab =  kin4.p_res1_lab;
    kin4.P_4_lab[0] = kin4.P_res1_lab[0];
    kin4.P_4_lab[1] = kin4.P_res1_lab[1];
    kin4.P_4_lab[2] = kin4.P_res1_lab[2];
    kin4.theta4 = Theta_res1;
    kin4.phi4 = Phi_res1;
  } else {
    kin2 = Kinema2Body(kin4.M_res1, 0.0, m3, m4);
    kin2.SetMomentum(1, kin1.GetMomentumLab(3));
    kin2.SetMomentum(2, 0.0);
    kin2.SetThetaCM((double)RandSin());
    kin2.calc_kinema();
    
    phi3 = (360.0*(double)CLHEP::RandFlat::shoot());
    //    phi3 = 0.0;
    
    kin4.Theta2CM = kin2.GetThetaCM();
    kin4.Phi2     = phi3;
    
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
    
    kin4.E_3_lab = kin2.GetEnergyLab(3);
    kin4.p_3_lab = kin2.GetMomentumLab(3);
    kin4.P_3_lab[0] = kin4.p_3_lab*vx3;
    kin4.P_3_lab[1] = kin4.p_3_lab*vy3;
    kin4.P_3_lab[2] = kin4.p_3_lab*vz3;
    kin4.theta3 = Theta3;
    kin4.phi3 = Phi3;
    
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
    
    kin4.E_4_lab = kin2.GetEnergyLab(4);
    kin4.p_4_lab = kin2.GetMomentumLab(4);
    kin4.P_4_lab[0] = kin4.p_4_lab*vx4;
    kin4.P_4_lab[1] = kin4.p_4_lab*vy4;
    kin4.P_4_lab[2] = kin4.p_4_lab*vz4;
    kin4.theta4 = Theta4;
    kin4.phi4 = Phi4;
  }


  /* calculate m5,m6 */
  /* もしm_res2とm6が等しく、m5が0ならば
     resonanceの値をそのままm6にわたす。*/
  if (kin4.M_res2 == m6 && m5 == 0.0) {
    kin4.E_5_lab = 0.0;
    kin4.p_5_lab = 0.0;
    kin4.P_5_lab[0] = 0.0;
    kin4.P_5_lab[1] = 0.0;
    kin4.P_5_lab[2] = 0.0;
    kin4.theta5 = 0.0;
    kin4.phi5 = 0.0;

    kin4.E_6_lab = kin4.E_res2_lab;
    kin4.p_6_lab =  kin4.p_res2_lab;
    kin4.P_6_lab[0] = kin4.P_res2_lab[0];
    kin4.P_6_lab[1] = kin4.P_res2_lab[1];
    kin4.P_6_lab[2] = kin4.P_res2_lab[2];
    kin4.theta6 = Theta_res2;
    kin4.phi6 = Phi_res2;
  } else {

    kin3 = Kinema2Body(kin4.M_res2, 0.0, m5, m6);
    kin3.SetMomentum(1, kin1.GetMomentumLab(4));
    kin3.SetMomentum(2, 0.0);
    kin3.SetThetaCM((double)RandSin());
    kin3.calc_kinema();
    
    phi3 = (360.0*(double)CLHEP::RandFlat::shoot());
    //    phi3 = 0.0;
    
    kin4.Theta3CM = kin3.GetThetaCM();
    kin4.Phi3     = phi3;
    
    /* m5 */
    theta1 = -kin1.GetPhiLab();
    theta2 = kin3.GetThetaLab();


    //    printf("phi3 = %f theta1 = %f theta2 = %f\n",phi3,theta1,theta2);
    
    vx5 = cos(deg2rad(theta2))*cos(deg2rad(theta1)) - 
      sin(deg2rad(theta1))*cos(deg2rad(phi3))*sin(deg2rad(theta2));
    
    vy5 = cos(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) +
      cos(deg2rad(theta1))*cos(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
      sin(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));
    
    vz5 = -sin(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) -
      cos(deg2rad(theta1))*sin(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
      cos(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));

    //    printf("m5\n");
    CalcDistoribution(vx5, vy5, vz5, &Theta5, &Phi5);
    
    kin4.E_5_lab = kin3.GetEnergyLab(3);
    kin4.p_5_lab = kin3.GetMomentumLab(3);
    kin4.P_5_lab[0] = kin4.p_5_lab*vx5;
    kin4.P_5_lab[1] = kin4.p_5_lab*vy5;
    kin4.P_5_lab[2] = kin4.p_5_lab*vz5;
    kin4.theta5 = Theta5;
    kin4.phi5 = Phi5;
    
    /* m6 */
    theta1 = -kin1.GetPhiLab();
    theta2 = -kin3.GetPhiLab();
    
    vx6 = cos(deg2rad(theta2))*cos(deg2rad(theta1)) - 
      sin(deg2rad(theta1))*cos(deg2rad(phi3))*sin(deg2rad(theta2));
    
    vy6 = cos(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) +
      cos(deg2rad(theta1))*cos(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
      sin(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));
    
    vz6 = -sin(deg2rad(phi5))*cos(deg2rad(theta2))*sin(deg2rad(theta1)) -
      cos(deg2rad(theta1))*sin(deg2rad(phi5))*cos(deg2rad(phi3))*sin(deg2rad(theta2)) -
    cos(deg2rad(phi5))*sin(deg2rad(phi3))*sin(deg2rad(theta2));
    //    printf("m6\n");
    CalcDistoribution(vx6, vy6, vz6, &Theta6, &Phi6);
    
    kin4.E_6_lab = kin3.GetEnergyLab(4);
    kin4.p_6_lab = kin3.GetMomentumLab(4);
    kin4.P_6_lab[0] = kin4.p_6_lab*vx6;
    kin4.P_6_lab[1] = kin4.p_6_lab*vy6;
    kin4.P_6_lab[2] = kin4.p_6_lab*vz6;
    kin4.theta6 = Theta6;
    kin4.phi6 = Phi6;
  }

  //  Dump();
}

double Kinema4Resonance::p2E(double p,double m)
{
  return sqrt(p*p + m*m);
}

void Kinema4Resonance::CalcDistoribution(double unitx, double unity, double unitz, double *theta, double *phi)
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
	  "Kinema4Resonance::CalcDistribution No such reagion unity=%f, unitz=%f\n",
	    unity, unitz);
    Dump();
    exit(1);
  }
  return;
}


double Kinema4Resonance::deg2rad(double theta) {
  return 3.141592654*theta/180.0;
}

double Kinema4Resonance::rag2deg(double rag)
{
  return 360.0 * rag/ (2.0 * 3.141592654);
}

    
double Kinema4Resonance::RandSin(void)
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

void Kinema4Resonance::Dump(void)
{
  printf("======Kinema4Resonance Dump======\n");
  printf("--Particle1--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_1, kin4.p_1_lab, kin4.E_1_lab);
  printf("--Particle2--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_2, kin4.p_2_lab, kin4.E_2_lab);
  printf("--Resonance1--\n");
  printf("mass=%f\n",kin4.M_res1);
  printf("--Resonance2--\n");
  printf("mass=%f\n",kin4.M_res2);
  printf("--Particle3--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_3, kin4.p_3_lab, kin4.E_3_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin4.P_3_lab[0], kin4.P_3_lab[1], kin4.P_3_lab[2],
	 kin4.theta3, kin4.phi3);
  printf("--Particle4--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_4, kin4.p_4_lab, kin4.E_4_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin4.P_4_lab[0], kin4.P_4_lab[1], kin4.P_4_lab[2],
	 kin4.theta4, kin4.phi4);
  printf("--Particle5--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_5, kin4.p_5_lab, kin4.E_5_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin4.P_5_lab[0], kin4.P_5_lab[1], kin4.P_5_lab[2],
	 kin4.theta5, kin4.phi5);
  printf("--Particle6--\n");
  printf("mass=%f, p_lab=%f, E_lab=%f\n",kin4.M_6, kin4.p_6_lab, kin4.E_6_lab);
  printf("momentum=(%f, %f, %f), (theta, phi)=(%f, %f)\n",
	 kin4.P_6_lab[0], kin4.P_6_lab[1], kin4.P_6_lab[2],
	 kin4.theta6, kin4.phi6);

  printf("Energy:E1+E2=%f, E1+E2+E3=%f\n", kin4.E_1_lab+kin4.E_2_lab,
	 kin4.E_3_lab+kin4.E_4_lab+kin4.E_5_lab);
  printf("Momentum: x-> p1+p2=%f, p3+p4+p5=%f\n", kin4.p_1_lab+kin4.p_2_lab,
	 kin4.P_3_lab[0]+kin4.P_4_lab[0]+kin4.P_5_lab[0]);
  printf("          y-> p3+p4+p5=%f\n",
	 kin4.P_3_lab[1]+kin4.P_4_lab[1]+kin4.P_5_lab[1]);
  printf("          z-> p3+p4+p5=%f\n",
	 kin4.P_3_lab[2]+kin4.P_4_lab[2]+kin4.P_5_lab[2]);

  return;
}

double Kinema4Resonance::GetEnergy(int i)
{
  switch (i) {
  case 1:
    return kin4.E_1_lab;
    break;
  case 2:
    return kin4.E_2_lab;
    break;
  case 3:
    return kin4.E_3_lab;
    break;
  case 4:
    return kin4.E_4_lab;
    break;
  case 5:
    return kin4.E_5_lab;
    break;
  case 6:
    return kin4.E_6_lab;
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetEnergy No such particle %d\n", i);
    exit(1);
  }
}

double Kinema4Resonance::GetMomentum(int i)
{
  switch (i) {
  case 1:
    return kin4.p_1_lab;
    break;
  case 2:
    return kin4.p_2_lab;
    break;
  case 3:
    return kin4.p_3_lab;
    break;
  case 4:
    return kin4.p_4_lab;
    break;
  case 5:
    return kin4.p_5_lab;
    break;
  case 6:
    return kin4.p_6_lab;
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetMomentum No such particle %d\n", i);
    exit(1);
  }
}

void Kinema4Resonance::GetMomentum(int i, double *mom)
{
  switch (i) {
  case 1:
    mom[0] = kin4.p_1_lab;
    mom[1] = 0.0;
    mom[2] = 0.0;
    break;
  case 2:
    mom[0] = kin4.p_2_lab;
    mom[1] = 0.0;
    mom[2] = 0.0;
    break;
  case 3:
    mom[0] = kin4.P_3_lab[0];
    mom[1] = kin4.P_3_lab[1];
    mom[2] = kin4.P_3_lab[2];
    break;
  case 4:
    mom[0] = kin4.P_4_lab[0];
    mom[1] = kin4.P_4_lab[1];
    mom[2] = kin4.P_4_lab[2];
    break;
  case 5:
    mom[0] = kin4.P_5_lab[0];
    mom[1] = kin4.P_5_lab[1];
    mom[2] = kin4.P_5_lab[2];
    break;
  case 6:
    mom[0] = kin4.P_6_lab[0];
    mom[1] = kin4.P_6_lab[1];
    mom[2] = kin4.P_6_lab[2];
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetMomentum No such particle %d\n", i);
    exit(1);
  }
}

double Kinema4Resonance::GetTheta(int i)
{
  switch (i) {
  case 1:
    return 0.0;
    break;
  case 2:
    return 0.0;
    break;
  case 3:
    return kin4.theta3;
    break;
  case 4:
    return kin4.theta4;
    break;
  case 5:
    return kin4.theta5;
    break;
  case 6:
    return kin4.theta6;
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetTheta No such particle %d\n", i);
    exit(1);
  }
}

double Kinema4Resonance::GetPhi(int i)
{
  switch (i) {
  case 1:
    return 0.0;
    break;
  case 2:
    return 0.0;
    break;
  case 3:
    return kin4.phi3;
    break;
  case 4:
    return kin4.phi4;
    break;
  case 5:
    return kin4.phi5;
    break;
  case 6:
    return kin4.phi6;
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetPhi No such particle %d\n", i);
    exit(1);
  }
}

double Kinema4Resonance::GetThetaCM(int i)
{
  switch (i) {
  case 1:
    return kin4.Theta1CM;
    break;
  case 2:
    return kin4.Theta2CM;
    break;
  case 3:
    return kin4.Theta3CM;
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::GetThetaCM index should be 1 or 2 ->%d\n", i);
    exit(1);
  }
}

double Kinema4Resonance::GetPhiCM(int i)
{
  switch (i) {
  case 1:
    return kin4.Phi1;
    break;
  case 2:
    return kin4.Phi2;
    break;
  case 3:
    return kin4.Phi3;
    break;
  default:
    fprintf(stderr, "Kinema3Resonance::GetPhiCM index should be 1 or 2 ->%d\n", i);
    exit(1);
  }
}


void Kinema4Resonance::RotateMom(int i, double deg, double *mom)
{
  double Sin,Cos;

  Sin=sin(deg2rad(deg));
  Cos=cos(deg2rad(deg));
  switch (i) {
  case 3:
    mom[0] = Cos*kin4.P_3_lab[0] - Sin*kin4.P_3_lab[1];
    mom[1] = Sin*kin4.P_3_lab[0] + Cos*kin4.P_3_lab[1];
    mom[2] = kin4.P_3_lab[2];
    break;
  case 4:
    mom[0] = Cos*kin4.P_4_lab[0] - Sin*kin4.P_4_lab[1];
    mom[1] = Sin*kin4.P_4_lab[0] + Cos*kin4.P_4_lab[1];
    mom[2] = kin4.P_4_lab[2];
    break;
  case 5:
    mom[0] = Cos*kin4.P_5_lab[0] - Sin*kin4.P_5_lab[1];
    mom[1] = Sin*kin4.P_5_lab[0] + Cos*kin4.P_5_lab[1];
    mom[2] = kin4.P_5_lab[2];
    break;
  default:
    fprintf(stderr, "Kinema4Resonance::RotateMom should be 3,4,5 ->%d\n",i);
    exit(1);
  }

}

double Kinema4Resonance::GetResMass(void)
{
  return kin4.M_res1;
}
