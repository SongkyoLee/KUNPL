#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Kinema2Body.hh"

Kinema2Body::Kinema2Body(void)
{
}

Kinema2Body::Kinema2Body(double m1, double m2, double m3, double m4)
{
  kin.M_1 = m1;
  kin.M_2 = m2;
  kin.M_3 = m3;
  kin.M_4 = m4;
}

void Kinema2Body::SetMass(double *mass)
{
  kin.M_1 = mass[0];
  kin.M_2 = mass[1];
  kin.M_3 = mass[2];
  kin.M_4 = mass[3];
}
  
void Kinema2Body::SetMass(int i, double mass)
{
  switch (i) {
  case 1:
    kin.M_1 = mass;
    break;
  case 2:
    kin.M_2 = mass;
    break;
  case 3:
    kin.M_3 = mass;
    break;
  case 4:
    kin.M_4 = mass;
    break;
  default:
    fprintf(stderr,"Kinema2Body::SetMass No such particle:%d\n",i);
  }
  return;
}

void Kinema2Body::SetMomentum(int i,double mom)
{
  switch (i) {
  case 1:
    kin.p_1_lab = mom;
    break;
  case 2:
    kin.p_2_lab = mom;
    break;
  case 3:
    kin.p_3_lab = mom;
    break;
  case 4:
    kin.p_4_lab = mom;
    break;
  default:
    fprintf(stderr,"Kinema2Body::SetMomentum No such particle:%d\n",i);
  }
  return;
}

void Kinema2Body::SetThetaCM(double theta_cm)
{
  kin.theta_cm = theta_cm;
  
  return;
}

int Kinema2Body::calc_kinema(void)
{

  kin.E_1_lab = p2E(kin.p_1_lab,kin.M_1);
  kin.E_2_lab = p2E(kin.p_2_lab,kin.M_2);

  kin.beta_cm = pE2beta(kin.p_1_lab,kin.E_1_lab,kin.M_2);
  kin.gamma_cm = beta2gamma(kin.beta_cm);


  //calculate of Kinematics in CM system
  kin.E_1_cm = kin.gamma_cm * kin.E_1_lab - kin.beta_cm * kin.gamma_cm * kin.p_1_lab;

  kin.E_2_cm = kin.gamma_cm * kin.M_2;

  kin.p_12_cm = E2p(kin.E_1_cm,kin.M_1);

  kin.E_3_cm = (pow(kin.M_3,2.0) + pow(kin.E_1_cm + kin.E_2_cm,2.0) - pow(kin.M_4,2.0))/(2.0*(kin.E_1_cm + kin.E_2_cm));

  kin.E_4_cm = (pow(kin.E_1_cm + kin.E_2_cm,2.0) + pow(kin.M_4,2.0) - pow(kin.M_3,2.0))/(2.0*(kin.E_1_cm + kin.E_2_cm));

  kin.p_34_cm = sqrt((pow((kin.M_3 + kin.E_1_cm + kin.E_2_cm),2.0)-pow(kin.M_4,2.0))*(pow((kin.M_3 - (kin.E_1_cm + kin.E_2_cm)),2.0)-pow(kin.M_4,2.0))/(4.0*pow(kin.E_1_cm + kin.E_2_cm,2.0)));

  //calculate theta,phi of LAB system form CM system
  kin.theta_lab = theta_cm2theta_lab(kin.theta_cm,kin.p_34_cm,kin.E_3_cm,kin.gamma_cm,kin.beta_cm);

  kin.phi_lab = theta_cm2phi_lab(kin.theta_cm,kin.p_34_cm,kin.E_4_cm,kin.gamma_cm,kin.beta_cm);
  
  //calculate pormentum ,energy of LAB system
  double p_lab_z,p_lab_xy;

  p_lab_z = kin.beta_cm * kin.gamma_cm * kin.E_3_cm + kin.gamma_cm * kin.p_34_cm * cos(deg2rad(kin.theta_cm));

  p_lab_xy = kin.p_34_cm * sin(deg2rad(kin.theta_cm));

  kin.p_3_lab = sqrt(pow(p_lab_z,2.0) + pow(p_lab_xy,2.0));

  p_lab_z = kin.beta_cm * kin.gamma_cm * kin.E_4_cm - kin.gamma_cm * kin.p_34_cm * cos(deg2rad(kin.theta_cm));

  kin.p_4_lab = sqrt(pow(p_lab_z,2.0) + pow(p_lab_xy,2.0));

  kin.E_3_lab = p2E(kin.p_3_lab,kin.M_3);
  kin.E_4_lab = p2E(kin.p_4_lab,kin.M_4);

  return 0;
}

double Kinema2Body::p2E(double p,double m)
{
  return sqrt(p*p + m*m);
}

double Kinema2Body::E2p(double E,double m)
{
  if (E*E - m*m<0.000000001)
    return 0.0;
  else
    return sqrt(E*E - m*m);
}

double Kinema2Body::pE2beta(double p,double E,double m_2)
{
  return p/(E + m_2);
}

double Kinema2Body::pE2beta(double p1,double E1,double p2, double E2)
{
  return (p1+p2)/(E1 + E2);
}

double Kinema2Body::beta2gamma(double beta)
{
  return 1.0/sqrt(1.0 - pow(beta,2.0));
}

double Kinema2Body::theta2theta_cm(double theta,double p,double E,double kin_gamma,double beta)
{
  double value;

  value = atan(p*sin(deg2rad(theta))/(-kin_gamma*beta*E + kin_gamma*p*cos(deg2rad(theta))))*180.0/3.14;

  if ( value < 0.0 )
    value = value + 180.0;

  return value;
}

double Kinema2Body::theta_cm2theta_lab(double theta,double p,double E,double gamma_cm,double beta_cm)
{
  double value;

  value = atan(p*sin(deg2rad(theta))/(beta_cm*gamma_cm*E + gamma_cm*p*cos(deg2rad(theta))))*180.0/3.14;

  if (value < 0.0)
    value = value + 180.0;

  return value;
}

double Kinema2Body::theta_cm2phi_lab(double theta,double p,double E,double gamma_cm,double beta_cm)
{
  double value;

  value = atan(p*sin(deg2rad(theta))/(beta_cm*gamma_cm*E - gamma_cm*p*cos(deg2rad(theta))))*180.0/3.14;

  if (value < 0.0)
    value = value + 180.0;

  return value;
}

double Kinema2Body::deg2rad(double theta) {
  return 3.141592654*theta/180.0;
}

double Kinema2Body::rag2deg(double rag)
{
  return 360.0 * rag/ (2.0 * 3.141592654);
}

void Kinema2Body::Dump(void)
{
  printf("===theta_cm:%f===\n",kin.theta_cm);
  printf("E_1_cm:%f p_1_cm:%f\n",kin.E_1_cm,kin.p_12_cm);
  printf("E_2_cm:%f p_2_cm:%f\n",kin.E_2_cm,kin.p_12_cm);
  printf("E_3_cm:%f p_3_cm:%f\n",kin.E_3_cm,kin.p_34_cm);
  printf("E_4_cm:%f p_4_cm:%f\n",kin.E_4_cm,kin.p_34_cm);
  printf("\n");
  printf("***LAB SYSTEM***\n");
  printf("E_1_lab:%f p_1_lab:%f\n",kin.E_1_lab,kin.p_1_lab);
  printf("E_2_lab:%f\n",kin.M_2);
  printf("E_3_lab:%f p_3_lab:%f\n",kin.E_3_lab,kin.p_3_lab);
  printf("E_4_lab:%f p_4_lab:%f\n",kin.E_4_lab,kin.p_4_lab);
  printf("theta_lab:%f phi_lab:%f",kin.theta_lab,kin.phi_lab);
  printf("\n\n");

}

double Kinema2Body::GetMomentumLab(int i)
{
  switch (i) {
  case 1:
    return kin.p_1_lab;
    break;
  case 2:
    return kin.p_2_lab;
    break;
  case 3:
    return kin.p_3_lab;
    break;
  case 4:
    return kin.p_4_lab;
    break;
  default:
    fprintf(stderr,"Kinema2Body::GetMomLab No such particle:%d\n",i);
    exit(1);
  }

}

double Kinema2Body::GetEnergyLab(int i)
{
  switch (i) {
  case 1:
    return kin.E_1_lab;
    break;
  case 2:
    return kin.E_2_lab;
    break;
  case 3:
    return kin.E_3_lab;
    break;
  case 4:
    return kin.E_4_lab;
    break;
  default:
    fprintf(stderr,"Kinema2Body::GetEnergyLab No such particle:%d\n",i);
    exit(1);
  }

}

double Kinema2Body::GetMomentumCM(int i)
{
  switch (i) {
  case 1:
    return kin.p_12_cm;
    break;
  case 2:
    return -kin.p_12_cm;
    break;
  case 3:
    return kin.p_34_cm;
    break;
  case 4:
    return -kin.p_34_cm;
    break;
  default:
    fprintf(stderr,"Kinema2Body::GetMomCm No such particle:%d\n",i);
    exit(1);
  }

}

double Kinema2Body::GetEnergyCM(int i)
{
  switch (i) {
  case 1:
    return kin.E_1_cm;
    break;
  case 2:
    return kin.E_2_cm;
    break;
  case 3:
    return kin.E_3_cm;
    break;
  case 4:
    return kin.E_4_cm;
    break;
  default:
    fprintf(stderr,"Kinema2Body::GetEnergyCM No such particle:%d\n",i);
    exit(1);
  }

}

double Kinema2Body::GetThetaLab(void)
{
  return kin.theta_lab;
}

double Kinema2Body::GetPhiLab(void)
{
  return kin.phi_lab;
}

double Kinema2Body::GetThetaCM(void)
{
  return kin.theta_cm;
}

double Kinema2Body::GetMass(int i) 
{
  switch (i) {
  case 1:
    return kin.M_1;
    break;
  case 2:
    return kin.M_2;
    break;
  case 3:
    return kin.M_3;
    break;
  case 4:
    return kin.M_4;
    break;
  default:
    fprintf(stderr,"Kinema2Body::GetMass No such particle:%d\n",i);
    exit(1);
  }

}
