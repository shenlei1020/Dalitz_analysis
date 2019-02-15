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
#include <TMath.h>
#include <TComplex.h>
#include <iostream>

using namespace std;

double nll(Int_t &npar, Double_t *gin, Double_t &nln, Double_t *p, Int_t iflag) //it should be a specific kind of formation.
{
//double p[2] = {1.0.7};
//std::string str1 = "phsp_kkpi.dat";//input char which is accepted by C, converted into usable stream.
fstream phsp_kkpi("phsp_kkpi.dat",ios::in);//"phsp_kkpi.dat"  str1.c_str()
std::vector<int> N1;
N1.clear();
std::vector<double> x1;
x1.clear();
std::vector<double> x2;
x2.clear();
  int n1;
  double kkpi_k1pi,kkpi_k1k2;
while (!phsp_kkpi.eof()) {
    phsp_kkpi>>n1>>kkpi_k1pi>>kkpi_k1k2;
    N1.push_back(n1);
    x1.push_back(kkpi_k1pi);
	x2.push_back(kkpi_k1k2);
}
//why are there one more line? Got it.
    N1.pop_back();
	x1.pop_back();
	x2.pop_back();
	
	phsp_kkpi.close();
  int NN1 = N1.size();
  double x[2];
  double S = 0;
 for(int i=0;i<NN1;i++) {
  x[0] = x1[i];
  x[1] = x2[i];
  S = ms(x,p)+S;
 }
    S = S/NN1;
	
///////

//std::string str2 = "sig.dat";//str2.c_str()
fstream sig("sig.dat",ios::in);//input  "sig.dat"  str2.c_str()
std::vector<int> N2;
N2.clear();
std::vector<double> y1;
y1.clear();
std::vector<double> y2;
y2.clear();
  int n2;
  double sig_k1pi,sig_k1k2;
while (!sig.eof()) {
    sig>>n2>>sig_k1pi>>sig_k1k2;
    N2.push_back(n2);
    y1.push_back(sig_k1pi);
	y2.push_back(sig_k1k2);
}
    N2.pop_back();
	y1.pop_back();
	y2.pop_back();
	sig.close();
  int NN2 = N2.size();
  double y[2];
  double nln = 0;
 for(int i=0;i<NN2;i++) {
  y[0] = y1[i];
  y[1] = y2[i];
  nln = nln - TMath::Log(ms(y,p)/S);
 }

}