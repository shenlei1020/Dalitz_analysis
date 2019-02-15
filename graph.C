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
#include <math.h>

using namespace std;
void graph(){
 
 fstream PAR("PAR.dat",ios::in);
std::vector<int> nop;
nop.clear();
std::vector<double> par;
par.clear();
  double Par;
while (!PAR.eof()) {
    PAR>>Par;
    par.push_back(Par);
	}
par.pop_back();
PAR.close();
double p[4];
p[0]=par[0];
p[1]=par[1];
p[2]=par[2];
p[3]=par[3];

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
	const int NN3 = N3.size();
	const int Np = 1500;
	double x[Np];
	double y[Np];
	double z[Np];
	double xy[2];
	TRandom *r = new TRandom();
for(int j=0;j<Np;j++) {
int i=(r->Uniform(NN3));
 xy[0] = z1[i];
 xy[1] = z2[i];
  x[j] = z1[i];
  y[j] = z2[i];
  z[j] = ms(xy,p);
 }
  TGraph2D *gr = new TGraph2D (Np,x,y,z);
  gr->SetTitle("PDF");
  gr->Draw("surf1");
  }