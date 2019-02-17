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

void main() {

const int npar=4;
   TMinuit *gMinuit = new TMinuit(npar); 
   gMinuit->SetFCN(nll);

   Double_t arglist[10];
   Int_t ierflg = 0;
   /*
   arglist[0] = 0.1;
   gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
   */
// Set starting values and step sizes for parameters
  // Double_t vstart[npar] = {1.,0.0,0.7,-10.0};
 // Double_t vstart[npar]={1,0.0,0.53,0.0};
    Double_t vstart[npar]={1,0.0,1.5,0.0};
   Double_t step[npar] = {0.0,0.0,0.2,0.0};//step[0] is 0, and vstart is const.
   gMinuit->mnparm(0, "ampl_k1pi", vstart[0], step[0], 0,2,ierflg);//!!!
   gMinuit->mnparm(1, "phase_k1pi", vstart[1], step[1], -180,180,ierflg);
   gMinuit->mnparm(2, "ampl_k1k2", vstart[2], step[2], 0,2,ierflg);//!!!
   gMinuit->mnparm(3, "phase_k1k2", vstart[3], step[3], -180,180,ierflg);//?range?

// Now ready for minimization step
   arglist[0] = 500;
   arglist[1] = 1.;
   gMinuit->mnexcm("MIGRAD", arglist ,4,ierflg);
 //  gMinuit->mnexcm("HESSE", arglist ,2,ierflg);
 //  gMinuit->mnexcm("MINOS", arglist ,2,ierflg);

   Double_t ampl_k1pi,ampl_k1pi_err,phase_k1pi,phase_k1pi_err,ampl_k1k2,ampl_k1k2_err,phase_k1k2,phase_k1k2_err;//error correct
   gMinuit->GetParameter(0, ampl_k1pi,ampl_k1pi_err );
   gMinuit->GetParameter(1, phase_k1pi,phase_k1pi_err );
   gMinuit->GetParameter(2, ampl_k1k2,ampl_k1k2_err );
   gMinuit->GetParameter(3, phase_k1k2,phase_k1k2_err );
   cout <<"ampl_k1pi           = "<<ampl_k1pi<<" +/- "<<ampl_k1pi_err<<endl;
   cout <<"phase_k1pi          = "<<phase_k1pi<<" +/- "<<phase_k1pi_err<<endl;
   cout <<"ampl_k1k2           = "<<ampl_k1k2<<" +/- "<<ampl_k1k2_err<<endl;
   cout <<"phase_k1k2          = "<<phase_k1k2<<" +/- "<<phase_k1k2_err<<endl;
 
  fstream PAR;
PAR.open("PAR.dat",ios::out);
PAR<<ampl_k1pi<<" "<<endl;
PAR<<phase_k1pi<<" "<<endl;
PAR<<ampl_k1k2<<" "<<endl;
PAR<<phase_k1k2<<" "<<endl;
PAR.close();  
 
 
 
 //////calculate the fraction.
 
 
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
 

}
