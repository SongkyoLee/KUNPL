#ifndef __KINEMA4RESONANCE_HH__
#define __KINEMA4RESONANCE_HH__

#include "Kinema2Body.hh"
struct KINEMA_4RESONANCE{
  double E_1_lab;
  double p_1_lab;
  double M_1;

  double E_2_lab;
  double p_2_lab;
  double M_2;

  double E_3_lab;
  double p_3_lab;
  double M_3;
  double P_3_lab[3];
  double theta3, phi3;

  double E_4_lab;
  double p_4_lab;
  double M_4;
  double P_4_lab[3];
  double theta4, phi4;

  double E_5_lab;
  double p_5_lab;
  double M_5;
  double P_5_lab[3];
  double theta5, phi5;

  double E_6_lab;
  double p_6_lab;
  double M_6;
  double P_6_lab[3];
  double theta6, phi6;

  double E_res1_lab;
  double p_res1_lab;
  double M_res1;
  double P_res1_lab[3];
  double theta_res1, phi_res1;

  double E_res2_lab;
  double p_res2_lab;
  double M_res2;
  double P_res2_lab[3];
  double theta_res2, phi_res2;

  double Theta1CM, Theta2CM,Theta3CM;
  double Phi1,Phi2,Phi3;
};

class Kinema4Resonance {
private:
  Kinema2Body kin1;
  Kinema2Body kin2;
  Kinema2Body kin3;
  KINEMA_4RESONANCE kin4;

public:
  Kinema4Resonance(double m1, double m2, double m3, double m4, double m5, double m6,
		   double m_res1, double width1, double m_res2, double width2, double p1, double p2);
  double p2E(double p,double m);
  void CalcDistoribution(double unitx, double unity, double unitz, double *theta, double *phi);
  double deg2rad(double theta);
  double rag2deg(double rag);
  double RandSin(void);
  void Dump(void);
  double GetEnergy(int i);
  double GetMomentum(int i);
  void GetMomentum(int i, double *mom);
  double GetTheta(int i);
  double GetPhi(int i);
  double GetThetaCM(int i);
  double GetPhiCM(int i);
  void  RotateMom(int i, double deg, double *mom);
  double GetResMass(void);
};

#endif
