#ifndef __KINEMA2BODY_HH__
#define __KINEMA2BODY_HH__

#include "kinema_cm2lab.h"

class Kinema2Body {
private:
  KINEMA_CM2LAB kin;
  double Phi;

public:
  Kinema2Body(void);
  Kinema2Body(double m1, double m2, double m3, double m4);
  void SetMass(double *mass);
  void SetMass(int i, double mass);
  void SetMomentum(int i,double mom);
  void SetThetaCM(double theta_cm);
  int calc_kinema(void);
  double p2E(double p,double m);
  double E2p(double E,double m);
  double pE2beta(double p,double E,double m_2);
  double pE2beta(double p1,double E1,double p2, double E2);
  double beta2gamma(double beta);
  double theta2theta_cm(double theta,double p,double E,double kin_gamma,double beta);
  double theta_cm2theta_lab(double theta,double p,double E,double gamma_cm,double beta_cm);
  double theta_cm2phi_lab(double theta,double p,double E,double gamma_cm,double beta_cm);
  double deg2rad(double theta);
  double rag2deg(double rag);
  void Dump(void);
  double GetMomentumLab(int i);
  double GetEnergyLab(int i);
  double GetMomentumCM(int i);
  double GetEnergyCM(int i);
  double GetThetaLab(void);
  double GetPhiLab(void);
  double GetThetaCM(void);
  double GetMass(int i); 
};
#endif
