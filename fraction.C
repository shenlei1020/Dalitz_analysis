#include "nll.C"
#include "fcn.C"

#include "iostream"
#include "TComplex.h"
#include "TH2D.h"
#include "TMath.h"
#include "TF2.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TComplex.h"
#include "iostream"
#include "TMinuit.h"
#include "TFitter.h"
#include "TVirtualFitter.h"
#include "TMinuitMinimizer.h"

using namespace std;

void fraction() {

 
  //////calculate the fraction.
double ampl_k1pi           = 1;
double phase_k1pi          = 0;
double ampl_k1k2           = 1.10054;
double phase_k1k2          = -155.606;
 double p[4] = {ampl_k1pi,phase_k1pi,ampl_k1k2,phase_k1k2};
 fstream phsp_truh("phsp_truth.dat",ios::in);
std::vector<int> N3;
N3.clear();
std::vector<double> z1;
z1.clear();
std::vector<double> z2;
z2.clear();
  int n3;
  double mc_m2_k1pi,mc_m2_k1k2;
while (!phsp_truh.eof()) {
    phsp_truh>>n3>>mc_m2_k1pi>>mc_m2_k1k2;
    N3.push_back(n3);
    z1.push_back(mc_m2_k1pi);
	z2.push_back(mc_m2_k1k2);
}
    N3.pop_back();
	z1.pop_back();
	z2.pop_back();
	phsp_truh.close();
	int NN3 = N3.size();
	double z[2];
	double s0 = 0.;
	double s1 = 0.;
	double s2 = 0.;
for(int i=0;i<NN3;i++) {
//

//
  z[0] = z1[i];
  z[1] = z2[i];
  s0 = ms(z,p)+s0;
  s1 = m_1(z,p)+s1;//!!!
  s2 = m_2(z,p)+s2;//!!!
 }
    s0 = s0/NN3;
	s1 = s1/NN3;
	s2 = s2/NN3;
	double frc_k1pi, frc_k1k2;
	frc_k1pi = s1/s0;
	frc_k1k2 = s2/s0;
	cout <<"frc_k1pi = "<<frc_k1pi<<endl;
	cout <<"frc_k1k2 = "<<frc_k1k2<<endl;
 
 //////
 
}