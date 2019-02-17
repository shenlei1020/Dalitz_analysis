#include "fstream"

void create() {
TFile *fphsp = new TFile("kkpi_2_PHSP_truth.root");//!!!
TFile *fsig = new TFile("kkpi_2_SigMc.root");//!!!

ofstream phsp_kkpi("phsp_kkpi.dat",ios::out);
ofstream phsp_truth("phsp_truth.dat",ios::out);
ofstream sig("sig.dat",ios::out);//create with one line at first
//ofstream sig1("sig1.dat",ios::out);

TTree *tphsp_truth = (TTree *)fphsp->Get("truth");
TTree *tphsp_kkpi = (TTree *)fphsp->Get("kkpi");
TTree *tsig = (TTree *)fsig->Get("kkpi");

int entry_truth=tphsp_truth->GetEntries();
int entry_kkpi=tphsp_kkpi->GetEntries();
int entry_sig=tsig->GetEntries();

double m2_k1pi,m2_k1k2,mc_m2_k1pi,mc_m2_k1k2;

tphsp_truth->SetBranchAddress("mc_m2_k1pi",&mc_m2_k1pi);
tphsp_truth->SetBranchAddress("mc_m2_k1k2",&mc_m2_k1k2);
tphsp_kkpi->SetBranchAddress("m2_k1pi",&m2_k1pi);
tphsp_kkpi->SetBranchAddress("m2_k1k2",&m2_k1k2);
tsig->SetBranchAddress("m2_k1pi",&m2_k1pi);
tsig->SetBranchAddress("m2_k1k2",&m2_k1k2);

for(int i=0;i<entry_truth;i++) {
tphsp_truth->GetEntry(i);
phsp_truth<<i<<" "<<mc_m2_k1pi<<" "<<mc_m2_k1k2<<" "<<endl;
}

for(int i=0;i<entry_kkpi;i++) {
tphsp_kkpi->GetEntry(i);
phsp_kkpi<<i<<" "<<m2_k1pi<<" "<<m2_k1k2<<" "<<endl;
}

for(int i=0;i<entry_sig;i++) {
tsig->GetEntry(i);
sig<<i<<" "<<m2_k1pi<<" "<<m2_k1k2<<" "<<endl;
}
phsp_truth.close();
phsp_kkpi.close();
sig.close();
}