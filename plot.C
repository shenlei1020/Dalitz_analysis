//#include "nll.C"
#include "fcn.C"

#include "TRandom.h"
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

using namespace std;

void plot() {
gStyle->SetOptFit();
gStyle->SetOptStat(kFALSE);

//input parameter
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
double fmax = 0;
//double fmax =79125.6;
double z[2];
double h[NN3];

for(int i=0;i<NN3;i++) {
z[0] = z1[i];
z[1] = z2[i];
h[i]=ms(z,p);
if (fmax < h[i]) {
fmax = h[i];
}
}
cout << " fmax = " << fmax <<endl;

///
double xmax=2.2;
double xmin=0.3;
int nxbin=50;
double ymax=3.2;
double ymin=0.8;
int nybin=80;
double ran;
double x[2];
TH2D *h1 = new TH2D("h1","select",nxbin,xmin,xmax,nybin,ymin,ymax);
TH1F *h2=new TH1F("h2","PDF and data;m^{2}_{k1pi} (GeV^{2}/c^{4});Events/(GeV^{2}/c^{4})",nxbin,xmin,xmax);
TH1F *h2y=new TH1F("h2y","PDF and data;m^{2}_{k1k2} (GeV^{2}/c^{4});Events/(GeV^{2}/c^{4})",nybin,ymin,ymax);
for (int j=0;j<80;j++){
  for(int i=0;i<NN3;i++) {
   ran = gRandom->Uniform(0.,fmax);
    if (ran <h[i] ) {
  h1->Fill(z1[i],z2[i]);
  h2->Fill(z1[i]);
  h2y->Fill(z2[i]);
   }
  }
}

//TCanvas *c1 = new TCanvas("c1","sig_lego");
//h1->Draw("lego");
//TCanvas *c2 = new TCanvas("c2","sig_scat");
//h1->Draw("scat");
//TCanvas *c3 = new TCanvas("c3","projection");
//h2->Draw("c");


//data point
TH1F *h3=new TH1F("PDF&data","data;x;y",nxbin,xmin,xmax);
TH1F *h3y=new TH1F("PDF&data","data;x;y",nybin,ymin,ymax);
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
 
 for(int i=0;i<NN2;i++) {
  y[0] = y1[i];
  y[1] = y2[i];
h3->Fill(y1[i]);
h3y->Fill(y2[i]);
 }
// TCanvas *c4 = new TCanvas("c4","dataprojection");
// h3->SetLineWidth(4);  
//h3->Draw("e");

//k1kpi
TCanvas *c5 = new TCanvas("c5","PDF&data");
//gStyle->SetEndErrorSize(5);
float norm=1000;
h2->Scale(norm/h2->Integral());
h3->Scale(norm/h3->Integral());

h2->SetLineWidth(2);
h2->Draw("c");

h3->SetLineColor(kRed);
h3->SetMarkerStyle(21);
//h3->GetXaxis()->SetTitle("X axis title");
h3->Draw("esame");

//residuals
TCanvas *c6 = new TCanvas("c6","residual");
TH1F *h4=new TH1F("Residuals","Residuals;m^{2}_{kpi} (GeV^{2}/c^{4});Events/(GeV^{2}/c^{4})",nxbin,xmin,xmax);
h4->Add(h2,h3,-1,1);
h4->SetLineColor(kRed);
h4->SetMarkerStyle(21);
h4->Draw("e");

//k1k2
TCanvas *c5y = new TCanvas("c5y","PDF&data");
//gStyle->SetEndErrorSize(5);
float norm=1000;
h2y->Scale(norm/h2y->Integral());
h3y->Scale(norm/h3y->Integral());

h2y->SetLineWidth(2);
h2y->Draw("c");

h3y->SetLineColor(kRed);
h3y->SetMarkerStyle(21);
//h3->GetXaxis()->SetTitle("X axis title");
h3y->Draw("esame");

//residuals
TCanvas *c6y = new TCanvas("c6y","residuals");
TH1F *h4y=new TH1F("Residuals","Residuals;m^{2}_{k1k2} (GeV^{2}/c^{4});Events/(GeV^{2}/c^{4})",nybin,ymin,ymax);
h4y->Add(h2y,h3y,-1,1);
h4y->SetLineColor(kRed);
h4y->SetMarkerStyle(21);
h4y->Draw("e");


}
