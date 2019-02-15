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
// #include "dalitz.h"
using namespace std;

const double m_d=1.86962;
const double m_k1=0.493677;
const double m_k2=0.493677;
const double m_pi=0.13957018;
const double m_phi=1.019455;
const double r_d=5.0;
const double r_phi=1.5, r_k0=1.5;
const double p_phi=0.126906;
const double gamma_phi=0.00426;
const double q_phi=1.18693;
const double m_k0=0.89594;
const double gamma_k0=0.0487;

double p_k1k2(double *x, double *p) {
double j=(pow((x[1]-m_k1*m_k1-m_k2*m_k2),2)-4*pow(m_k1*m_k2,2));
if (j>0) return sqrt(j)/2/sqrt(x[1]);
}


double q_k1k2(double *x,double *p) {
double j;
j=pow(x[1]-m_d*m_d-m_pi*m_pi,2)-4*pow(m_d*m_pi,2);
if (j>0) return sqrt(j)/2/sqrt(x[1]);
}




double f_phi(double *x, double *p) {
return sqrt((1+pow(r_phi*p_phi,2))/(1+pow(r_phi*p_k1k2(x,p),2)));
}


double f_d(double *x, double *p) {
double j;
j=(1+pow(r_d+q_phi,2))/(1+pow(r_d+q_k1k2(x,p),2));
if (j>0) return sqrt(j);
}

double gamma_k1k2(double *x, double *p) {
return gamma_phi*pow(p_k1k2(x,p)/p_phi,3)*(m_phi/sqrt(x[1]))*pow(f_phi(x,p),2);
}

TComplex bw(double *x, double *p){
double a=gamma_k1k2(x,p);
return 1/(m_phi*m_phi-x[1]-m_phi*a*(TComplex::I()));
}

TComplex a_2(double *x, double *p){
return f_d(x,p)*f_phi(x,p)*(2*x[0]+x[1]-m_d*m_d-m_k1*m_k1-m_k2*m_k2-m_pi*m_pi)*bw(x,p);
}


/*
double spin_1(double *x, double *p){
return 2*x[0]+x[1]-m_d*m_d-m_k1*m_k1-m_k2*m_k2-m_pi*m_pi-(m_d*m_d-m_pi*m_pi)*(m_k1*m_k1-m_k2*m_k2)/x[1];//
}

double ms_1(double *x, double *p){
return pow(f_d(x,p)*f_phi(x,p)*spin_1(x,p),2)/(pow(m_phi*m_phi-x[1],2)+pow(m_phi*gamma_k1k2(x,p),2));
}
*/
//////
double p_k1pi(double *x, double *p) {
double j;
j=pow(x[0]-m_k1*m_k1-m_pi*m_pi,2)-4*pow(m_k1*m_pi,2);
if (j>0) return sqrt(j)/2/sqrt(x[0]);
}


double q_k1pi(double *x,double *p) {
double j;
j=pow(x[0]-m_d*m_d-m_k2*m_k2,2)-4*pow(m_d*m_k2,2);
if (j>0) return sqrt(j)/2/sqrt(x[0]);
}

double p_k0(double *x, double *p) {
return sqrt(pow(m_k0*m_k0-m_k1*m_k1-m_pi*m_pi,2)-4*pow(m_k1*m_pi,2))/2/m_k0;
}

double q_k0(double *x, double *p) {
return sqrt(pow(m_k0*m_k0-m_d*m_d-m_k2*m_k2,2)-4*pow(m_d*m_k2,2))/2/m_k0;
}

double f_k0(double *x, double *p) {
double j;
j=(1+pow(r_k0*p_k0(x,p),2))/(1+pow(r_k0*p_k1pi(x,p),2));
if (j>0) return sqrt(j);
}

double f_d2(double *x, double *p) {
double j;
j=(1+pow(r_d+q_k0(x,p),2))/(1+pow(r_d+q_k1pi(x,p),2));
if (j>0) return sqrt(j);
}

double gamma_k1pi(double *x, double *p) {
return gamma_k0*pow(p_k1pi(x,p)/p_k0(x,p),3)*(m_k0/sqrt(x[0]))*pow(f_k0(x,p),2);
}

TComplex bw2(double *x, double *p) {
double b=gamma_k1pi(x,p);
return 1/(m_k0*m_k0-x[0]-b*m_k0*(TComplex::I()));
}

TComplex a_1(double *x, double *p) {
double c=2*x[1]+x[0]-m_d*m_d-m_k1*m_k1-m_pi*m_pi-m_k2*m_k2-(m_d*m_d-m_k2*m_k2)*(m_k1*m_k1-m_pi*m_pi)/x[0];//error correct
return f_d2(x,p)*f_k0(x,p)*c*bw2(x,p);//error correct
}


double m_1(double *x,double *p){
TComplex c1=TComplex(TMath::Abs(p[0]),p[1]*TMath::DegToRad(),true);
TComplex c3=c1*a_1(x,p);
return c3.Rho2();
}

double m_2(double *x, double *p) {

TComplex c2=TComplex(TMath::Abs(p[2]),p[3]*TMath::DegToRad(),true);
TComplex c3=c2*a_2(x,p);
return c3.Rho2();
}

double ms(double *x, double *p) {
TComplex c1=TComplex(TMath::Abs(p[0]),p[1]*TMath::DegToRad(),true);
TComplex c2=TComplex(TMath::Abs(p[2]),p[3]*TMath::DegToRad(),true);
TComplex c3=c1*a_1(x,p)+c2*a_2(x,p);
return c3.Rho2();
}
/*
double spin_2(double *x, double *p){
return 2*x[1]+x[0]-m_d*m_d-m_k1*m_k1-m_pi*m_pi-m_k2*m_k2-(m_d*m_d-m_pi*m_pi)*(m_k1*m_k1-m_pi*m_pi)/x[0];
}
double ms_2(double *x, double *p){
return pow(f_k0(x,p)*f_d2(x,p)*spin_2(x,p),2)/(pow(m_k0*m_k0-x[0],2)+pow(gamma_k1pi(x,p)*m_k0,2));
}

double ms(double*x,double*p){
return p[0]*ms_1(x,p)+p[1]*ms_2(x,p);
}
*/