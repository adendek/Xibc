//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct  4 17:09:05 2016 by ROOT version 5.32/00
// from TTree mytree/mytree
// found on file: all_2012_MAGUP.root
//////////////////////////////////////////////////////////

#ifndef Xic_h
#define Xic_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxXb_ENDVERTEX_COV = 1;
const Int_t kMaxXb_OWNPV_COV = 1;
const Int_t kMaxXb_TOPPV_COV = 1;
const Int_t kMaxmu_OWNPV_COV = 1;
const Int_t kMaxmu_TOPPV_COV = 1;
const Int_t kMaxmu_ORIVX_COV = 1;
const Int_t kMaxXc_ENDVERTEX_COV = 1;
const Int_t kMaxXc_OWNPV_COV = 1;
const Int_t kMaxXc_TOPPV_COV = 1;
const Int_t kMaxXc_ORIVX_COV = 1;
const Int_t kMaxpi_OWNPV_COV = 1;
const Int_t kMaxpi_TOPPV_COV = 1;
const Int_t kMaxpi_ORIVX_COV = 1;
const Int_t kMaxK_OWNPV_COV = 1;
const Int_t kMaxK_TOPPV_COV = 1;
const Int_t kMaxK_ORIVX_COV = 1;
const Int_t kMaxp_OWNPV_COV = 1;
const Int_t kMaxp_TOPPV_COV = 1;
const Int_t kMaxp_ORIVX_COV = 1;

class Xic {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        Xb_MINIP;
   Double_t        Xb_MINIPCHI2;
   Double_t        Xb_MINIPNEXTBEST;
   Double_t        Xb_MINIPCHI2NEXTBEST;
   Double_t        Xb_ENDVERTEX_X;
   Double_t        Xb_ENDVERTEX_Y;
   Double_t        Xb_ENDVERTEX_Z;
   Double_t        Xb_ENDVERTEX_XERR;
   Double_t        Xb_ENDVERTEX_YERR;
   Double_t        Xb_ENDVERTEX_ZERR;
   Double_t        Xb_ENDVERTEX_CHI2;
   Int_t           Xb_ENDVERTEX_NDOF;
   Float_t         Xb_ENDVERTEX_COV_[3][3];
   Double_t        Xb_OWNPV_X;
   Double_t        Xb_OWNPV_Y;
   Double_t        Xb_OWNPV_Z;
   Double_t        Xb_OWNPV_XERR;
   Double_t        Xb_OWNPV_YERR;
   Double_t        Xb_OWNPV_ZERR;
   Double_t        Xb_OWNPV_CHI2;
   Int_t           Xb_OWNPV_NDOF;
   Float_t         Xb_OWNPV_COV_[3][3];
   Double_t        Xb_IP_OWNPV;
   Double_t        Xb_IPCHI2_OWNPV;
   Double_t        Xb_FD_OWNPV;
   Double_t        Xb_FDCHI2_OWNPV;
   Double_t        Xb_DIRA_OWNPV;
   Double_t        Xb_TOPPV_X;
   Double_t        Xb_TOPPV_Y;
   Double_t        Xb_TOPPV_Z;
   Double_t        Xb_TOPPV_XERR;
   Double_t        Xb_TOPPV_YERR;
   Double_t        Xb_TOPPV_ZERR;
   Double_t        Xb_TOPPV_CHI2;
   Int_t           Xb_TOPPV_NDOF;
   Float_t         Xb_TOPPV_COV_[3][3];
   Double_t        Xb_IP_TOPPV;
   Double_t        Xb_IPCHI2_TOPPV;
   Double_t        Xb_FD_TOPPV;
   Double_t        Xb_FDCHI2_TOPPV;
   Double_t        Xb_DIRA_TOPPV;
   Double_t        Xb_P;
   Double_t        Xb_PT;
   Double_t        Xb_PE;
   Double_t        Xb_PX;
   Double_t        Xb_PY;
   Double_t        Xb_PZ;
   Double_t        Xb_MM;
   Double_t        Xb_MMERR;
   Double_t        Xb_M;
   Int_t           Xb_ID;
   Double_t        Xb_Nu_Parl;
   Double_t        Xb_Nu_Perp;
   Double_t        Xb_Nu_a;
   Double_t        Xb_Nu_X;
   Double_t        Xb_Nu_Y;
   Bool_t          Xb_L0Global_Dec;
   Bool_t          Xb_L0Global_TIS;
   Bool_t          Xb_L0Global_TOS;
   Bool_t          Xb_Hlt1Global_Dec;
   Bool_t          Xb_Hlt1Global_TIS;
   Bool_t          Xb_Hlt1Global_TOS;
   Bool_t          Xb_Hlt1Phys_Dec;
   Bool_t          Xb_Hlt1Phys_TIS;
   Bool_t          Xb_Hlt1Phys_TOS;
   Bool_t          Xb_Hlt2Global_Dec;
   Bool_t          Xb_Hlt2Global_TIS;
   Bool_t          Xb_Hlt2Global_TOS;
   Bool_t          Xb_Hlt2Phys_Dec;
   Bool_t          Xb_Hlt2Phys_TIS;
   Bool_t          Xb_Hlt2Phys_TOS;
   Bool_t          Xb_L0HCALDecision_Dec;
   Bool_t          Xb_L0HCALDecision_TIS;
   Bool_t          Xb_L0HCALDecision_TOS;
   Bool_t          Xb_L0MuonDecision_Dec;
   Bool_t          Xb_L0MuonDecision_TIS;
   Bool_t          Xb_L0MuonDecision_TOS;
   Bool_t          Xb_L0MuonHighDecision_Dec;
   Bool_t          Xb_L0MuonHighDecision_TIS;
   Bool_t          Xb_L0MuonHighDecision_TOS;
   Bool_t          Xb_Hlt1SingleMuonNoIPL0Decision_Dec;
   Bool_t          Xb_Hlt1SingleMuonNoIPL0Decision_TIS;
   Bool_t          Xb_Hlt1SingleMuonNoIPL0Decision_TOS;
   Bool_t          Xb_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          Xb_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          Xb_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          Xb_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          Xb_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          Xb_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          Xb_Hlt1TrackAllL0Decision_Dec;
   Bool_t          Xb_Hlt1TrackAllL0Decision_TIS;
   Bool_t          Xb_Hlt1TrackAllL0Decision_TOS;
   Bool_t          Xb_Hlt1TrackMuonDecision_Dec;
   Bool_t          Xb_Hlt1TrackMuonDecision_TIS;
   Bool_t          Xb_Hlt1TrackMuonDecision_TOS;
   Bool_t          Xb_Hlt2SingleMuonDecision_Dec;
   Bool_t          Xb_Hlt2SingleMuonDecision_TIS;
   Bool_t          Xb_Hlt2SingleMuonDecision_TOS;
   Bool_t          Xb_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          Xb_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          Xb_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          Xb_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          Xb_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          Xb_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          Xb_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          Xb_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          Xb_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          Xb_Hlt2TransparentDecision_Dec;
   Bool_t          Xb_Hlt2TransparentDecision_TIS;
   Bool_t          Xb_Hlt2TransparentDecision_TOS;
   Double_t        mu_MINIP;
   Double_t        mu_MINIPCHI2;
   Double_t        mu_MINIPNEXTBEST;
   Double_t        mu_MINIPCHI2NEXTBEST;
   Double_t        mu_OWNPV_X;
   Double_t        mu_OWNPV_Y;
   Double_t        mu_OWNPV_Z;
   Double_t        mu_OWNPV_XERR;
   Double_t        mu_OWNPV_YERR;
   Double_t        mu_OWNPV_ZERR;
   Double_t        mu_OWNPV_CHI2;
   Int_t           mu_OWNPV_NDOF;
   Float_t         mu_OWNPV_COV_[3][3];
   Double_t        mu_IP_OWNPV;
   Double_t        mu_IPCHI2_OWNPV;
   Double_t        mu_TOPPV_X;
   Double_t        mu_TOPPV_Y;
   Double_t        mu_TOPPV_Z;
   Double_t        mu_TOPPV_XERR;
   Double_t        mu_TOPPV_YERR;
   Double_t        mu_TOPPV_ZERR;
   Double_t        mu_TOPPV_CHI2;
   Int_t           mu_TOPPV_NDOF;
   Float_t         mu_TOPPV_COV_[3][3];
   Double_t        mu_IP_TOPPV;
   Double_t        mu_IPCHI2_TOPPV;
   Double_t        mu_ORIVX_X;
   Double_t        mu_ORIVX_Y;
   Double_t        mu_ORIVX_Z;
   Double_t        mu_ORIVX_XERR;
   Double_t        mu_ORIVX_YERR;
   Double_t        mu_ORIVX_ZERR;
   Double_t        mu_ORIVX_CHI2;
   Int_t           mu_ORIVX_NDOF;
   Float_t         mu_ORIVX_COV_[3][3];
   Double_t        mu_IP_ORIVX;
   Double_t        mu_IPCHI2_ORIVX;
   Double_t        mu_P;
   Double_t        mu_PT;
   Double_t        mu_PE;
   Double_t        mu_PX;
   Double_t        mu_PY;
   Double_t        mu_PZ;
   Double_t        mu_M;
   Int_t           mu_ID;
   Double_t        mu_PIDe;
   Double_t        mu_PIDmu;
   Double_t        mu_PIDK;
   Double_t        mu_PIDp;
   Double_t        mu_ProbNNe;
   Double_t        mu_ProbNNk;
   Double_t        mu_ProbNNp;
   Double_t        mu_ProbNNpi;
   Double_t        mu_ProbNNmu;
   Double_t        mu_ProbNNghost;
   Bool_t          mu_hasMuon;
   Bool_t          mu_isMuon;
   Bool_t          mu_hasRich;
   Bool_t          mu_hasCalo;
   Int_t           mu_TRACK_Type;
   Int_t           mu_TRACK_Key;
   Double_t        mu_TRACK_CHI2NDOF;
   Double_t        mu_TRACK_PCHI2;
   Double_t        mu_TRACK_MatchCHI2;
   Double_t        mu_TRACK_GhostProb;
   Double_t        mu_TRACK_CloneDist;
   Double_t        mu_TRACK_Likelihood;
   Bool_t          mu_L0Global_Dec;
   Bool_t          mu_L0Global_TIS;
   Bool_t          mu_L0Global_TOS;
   Bool_t          mu_Hlt1Global_Dec;
   Bool_t          mu_Hlt1Global_TIS;
   Bool_t          mu_Hlt1Global_TOS;
   Bool_t          mu_Hlt1Phys_Dec;
   Bool_t          mu_Hlt1Phys_TIS;
   Bool_t          mu_Hlt1Phys_TOS;
   Bool_t          mu_Hlt2Global_Dec;
   Bool_t          mu_Hlt2Global_TIS;
   Bool_t          mu_Hlt2Global_TOS;
   Bool_t          mu_Hlt2Phys_Dec;
   Bool_t          mu_Hlt2Phys_TIS;
   Bool_t          mu_Hlt2Phys_TOS;
   Bool_t          mu_L0HCALDecision_Dec;
   Bool_t          mu_L0HCALDecision_TIS;
   Bool_t          mu_L0HCALDecision_TOS;
   Bool_t          mu_L0MuonDecision_Dec;
   Bool_t          mu_L0MuonDecision_TIS;
   Bool_t          mu_L0MuonDecision_TOS;
   Bool_t          mu_L0MuonHighDecision_Dec;
   Bool_t          mu_L0MuonHighDecision_TIS;
   Bool_t          mu_L0MuonHighDecision_TOS;
   Bool_t          mu_Hlt1SingleMuonNoIPL0Decision_Dec;
   Bool_t          mu_Hlt1SingleMuonNoIPL0Decision_TIS;
   Bool_t          mu_Hlt1SingleMuonNoIPL0Decision_TOS;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_Dec;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_TIS;
   Bool_t          mu_Hlt1SingleMuonHighPTDecision_TOS;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_Dec;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_TIS;
   Bool_t          mu_Hlt1SingleMuonNoIPDecision_TOS;
   Bool_t          mu_Hlt1TrackAllL0Decision_Dec;
   Bool_t          mu_Hlt1TrackAllL0Decision_TIS;
   Bool_t          mu_Hlt1TrackAllL0Decision_TOS;
   Bool_t          mu_Hlt1TrackMuonDecision_Dec;
   Bool_t          mu_Hlt1TrackMuonDecision_TIS;
   Bool_t          mu_Hlt1TrackMuonDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonHighPTDecision_TOS;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_Dec;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_TIS;
   Bool_t          mu_Hlt2SingleMuonLowPTDecision_TOS;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo2BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo3BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2Topo4BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu2BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu3BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_Dec;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_TIS;
   Bool_t          mu_Hlt2TopoMu4BodyBBDTDecision_TOS;
   Bool_t          mu_Hlt2TransparentDecision_Dec;
   Bool_t          mu_Hlt2TransparentDecision_TIS;
   Bool_t          mu_Hlt2TransparentDecision_TOS;
   Double_t        Xc_MINIP;
   Double_t        Xc_MINIPCHI2;
   Double_t        Xc_MINIPNEXTBEST;
   Double_t        Xc_MINIPCHI2NEXTBEST;
   Double_t        Xc_ENDVERTEX_X;
   Double_t        Xc_ENDVERTEX_Y;
   Double_t        Xc_ENDVERTEX_Z;
   Double_t        Xc_ENDVERTEX_XERR;
   Double_t        Xc_ENDVERTEX_YERR;
   Double_t        Xc_ENDVERTEX_ZERR;
   Double_t        Xc_ENDVERTEX_CHI2;
   Int_t           Xc_ENDVERTEX_NDOF;
   Float_t         Xc_ENDVERTEX_COV_[3][3];
   Double_t        Xc_OWNPV_X;
   Double_t        Xc_OWNPV_Y;
   Double_t        Xc_OWNPV_Z;
   Double_t        Xc_OWNPV_XERR;
   Double_t        Xc_OWNPV_YERR;
   Double_t        Xc_OWNPV_ZERR;
   Double_t        Xc_OWNPV_CHI2;
   Int_t           Xc_OWNPV_NDOF;
   Float_t         Xc_OWNPV_COV_[3][3];
   Double_t        Xc_IP_OWNPV;
   Double_t        Xc_IPCHI2_OWNPV;
   Double_t        Xc_FD_OWNPV;
   Double_t        Xc_FDCHI2_OWNPV;
   Double_t        Xc_DIRA_OWNPV;
   Double_t        Xc_TOPPV_X;
   Double_t        Xc_TOPPV_Y;
   Double_t        Xc_TOPPV_Z;
   Double_t        Xc_TOPPV_XERR;
   Double_t        Xc_TOPPV_YERR;
   Double_t        Xc_TOPPV_ZERR;
   Double_t        Xc_TOPPV_CHI2;
   Int_t           Xc_TOPPV_NDOF;
   Float_t         Xc_TOPPV_COV_[3][3];
   Double_t        Xc_IP_TOPPV;
   Double_t        Xc_IPCHI2_TOPPV;
   Double_t        Xc_FD_TOPPV;
   Double_t        Xc_FDCHI2_TOPPV;
   Double_t        Xc_DIRA_TOPPV;
   Double_t        Xc_ORIVX_X;
   Double_t        Xc_ORIVX_Y;
   Double_t        Xc_ORIVX_Z;
   Double_t        Xc_ORIVX_XERR;
   Double_t        Xc_ORIVX_YERR;
   Double_t        Xc_ORIVX_ZERR;
   Double_t        Xc_ORIVX_CHI2;
   Int_t           Xc_ORIVX_NDOF;
   Float_t         Xc_ORIVX_COV_[3][3];
   Double_t        Xc_IP_ORIVX;
   Double_t        Xc_IPCHI2_ORIVX;
   Double_t        Xc_FD_ORIVX;
   Double_t        Xc_FDCHI2_ORIVX;
   Double_t        Xc_DIRA_ORIVX;
   Double_t        Xc_P;
   Double_t        Xc_PT;
   Double_t        Xc_PE;
   Double_t        Xc_PX;
   Double_t        Xc_PY;
   Double_t        Xc_PZ;
   Double_t        Xc_MM;
   Double_t        Xc_MMERR;
   Double_t        Xc_M;
   Int_t           Xc_ID;
   Double_t        Xc_TAU;
   Double_t        Xc_TAUERR;
   Double_t        Xc_TAUCHI2;
   Double_t        pi_MINIP;
   Double_t        pi_MINIPCHI2;
   Double_t        pi_MINIPNEXTBEST;
   Double_t        pi_MINIPCHI2NEXTBEST;
   Double_t        pi_OWNPV_X;
   Double_t        pi_OWNPV_Y;
   Double_t        pi_OWNPV_Z;
   Double_t        pi_OWNPV_XERR;
   Double_t        pi_OWNPV_YERR;
   Double_t        pi_OWNPV_ZERR;
   Double_t        pi_OWNPV_CHI2;
   Int_t           pi_OWNPV_NDOF;
   Float_t         pi_OWNPV_COV_[3][3];
   Double_t        pi_IP_OWNPV;
   Double_t        pi_IPCHI2_OWNPV;
   Double_t        pi_TOPPV_X;
   Double_t        pi_TOPPV_Y;
   Double_t        pi_TOPPV_Z;
   Double_t        pi_TOPPV_XERR;
   Double_t        pi_TOPPV_YERR;
   Double_t        pi_TOPPV_ZERR;
   Double_t        pi_TOPPV_CHI2;
   Int_t           pi_TOPPV_NDOF;
   Float_t         pi_TOPPV_COV_[3][3];
   Double_t        pi_IP_TOPPV;
   Double_t        pi_IPCHI2_TOPPV;
   Double_t        pi_ORIVX_X;
   Double_t        pi_ORIVX_Y;
   Double_t        pi_ORIVX_Z;
   Double_t        pi_ORIVX_XERR;
   Double_t        pi_ORIVX_YERR;
   Double_t        pi_ORIVX_ZERR;
   Double_t        pi_ORIVX_CHI2;
   Int_t           pi_ORIVX_NDOF;
   Float_t         pi_ORIVX_COV_[3][3];
   Double_t        pi_IP_ORIVX;
   Double_t        pi_IPCHI2_ORIVX;
   Double_t        pi_P;
   Double_t        pi_PT;
   Double_t        pi_PE;
   Double_t        pi_PX;
   Double_t        pi_PY;
   Double_t        pi_PZ;
   Double_t        pi_M;
   Int_t           pi_ID;
   Double_t        pi_PIDe;
   Double_t        pi_PIDmu;
   Double_t        pi_PIDK;
   Double_t        pi_PIDp;
   Double_t        pi_ProbNNe;
   Double_t        pi_ProbNNk;
   Double_t        pi_ProbNNp;
   Double_t        pi_ProbNNpi;
   Double_t        pi_ProbNNmu;
   Double_t        pi_ProbNNghost;
   Bool_t          pi_hasMuon;
   Bool_t          pi_isMuon;
   Bool_t          pi_hasRich;
   Bool_t          pi_hasCalo;
   Int_t           pi_TRACK_Type;
   Int_t           pi_TRACK_Key;
   Double_t        pi_TRACK_CHI2NDOF;
   Double_t        pi_TRACK_PCHI2;
   Double_t        pi_TRACK_MatchCHI2;
   Double_t        pi_TRACK_GhostProb;
   Double_t        pi_TRACK_CloneDist;
   Double_t        pi_TRACK_Likelihood;
   Double_t        K_MINIP;
   Double_t        K_MINIPCHI2;
   Double_t        K_MINIPNEXTBEST;
   Double_t        K_MINIPCHI2NEXTBEST;
   Double_t        K_OWNPV_X;
   Double_t        K_OWNPV_Y;
   Double_t        K_OWNPV_Z;
   Double_t        K_OWNPV_XERR;
   Double_t        K_OWNPV_YERR;
   Double_t        K_OWNPV_ZERR;
   Double_t        K_OWNPV_CHI2;
   Int_t           K_OWNPV_NDOF;
   Float_t         K_OWNPV_COV_[3][3];
   Double_t        K_IP_OWNPV;
   Double_t        K_IPCHI2_OWNPV;
   Double_t        K_TOPPV_X;
   Double_t        K_TOPPV_Y;
   Double_t        K_TOPPV_Z;
   Double_t        K_TOPPV_XERR;
   Double_t        K_TOPPV_YERR;
   Double_t        K_TOPPV_ZERR;
   Double_t        K_TOPPV_CHI2;
   Int_t           K_TOPPV_NDOF;
   Float_t         K_TOPPV_COV_[3][3];
   Double_t        K_IP_TOPPV;
   Double_t        K_IPCHI2_TOPPV;
   Double_t        K_ORIVX_X;
   Double_t        K_ORIVX_Y;
   Double_t        K_ORIVX_Z;
   Double_t        K_ORIVX_XERR;
   Double_t        K_ORIVX_YERR;
   Double_t        K_ORIVX_ZERR;
   Double_t        K_ORIVX_CHI2;
   Int_t           K_ORIVX_NDOF;
   Float_t         K_ORIVX_COV_[3][3];
   Double_t        K_IP_ORIVX;
   Double_t        K_IPCHI2_ORIVX;
   Double_t        K_P;
   Double_t        K_PT;
   Double_t        K_PE;
   Double_t        K_PX;
   Double_t        K_PY;
   Double_t        K_PZ;
   Double_t        K_M;
   Int_t           K_ID;
   Double_t        K_PIDe;
   Double_t        K_PIDmu;
   Double_t        K_PIDK;
   Double_t        K_PIDp;
   Double_t        K_ProbNNe;
   Double_t        K_ProbNNk;
   Double_t        K_ProbNNp;
   Double_t        K_ProbNNpi;
   Double_t        K_ProbNNmu;
   Double_t        K_ProbNNghost;
   Bool_t          K_hasMuon;
   Bool_t          K_isMuon;
   Bool_t          K_hasRich;
   Bool_t          K_hasCalo;
   Int_t           K_TRACK_Type;
   Int_t           K_TRACK_Key;
   Double_t        K_TRACK_CHI2NDOF;
   Double_t        K_TRACK_PCHI2;
   Double_t        K_TRACK_MatchCHI2;
   Double_t        K_TRACK_GhostProb;
   Double_t        K_TRACK_CloneDist;
   Double_t        K_TRACK_Likelihood;
   Double_t        p_MINIP;
   Double_t        p_MINIPCHI2;
   Double_t        p_MINIPNEXTBEST;
   Double_t        p_MINIPCHI2NEXTBEST;
   Double_t        p_OWNPV_X;
   Double_t        p_OWNPV_Y;
   Double_t        p_OWNPV_Z;
   Double_t        p_OWNPV_XERR;
   Double_t        p_OWNPV_YERR;
   Double_t        p_OWNPV_ZERR;
   Double_t        p_OWNPV_CHI2;
   Int_t           p_OWNPV_NDOF;
   Float_t         p_OWNPV_COV_[3][3];
   Double_t        p_IP_OWNPV;
   Double_t        p_IPCHI2_OWNPV;
   Double_t        p_TOPPV_X;
   Double_t        p_TOPPV_Y;
   Double_t        p_TOPPV_Z;
   Double_t        p_TOPPV_XERR;
   Double_t        p_TOPPV_YERR;
   Double_t        p_TOPPV_ZERR;
   Double_t        p_TOPPV_CHI2;
   Int_t           p_TOPPV_NDOF;
   Float_t         p_TOPPV_COV_[3][3];
   Double_t        p_IP_TOPPV;
   Double_t        p_IPCHI2_TOPPV;
   Double_t        p_ORIVX_X;
   Double_t        p_ORIVX_Y;
   Double_t        p_ORIVX_Z;
   Double_t        p_ORIVX_XERR;
   Double_t        p_ORIVX_YERR;
   Double_t        p_ORIVX_ZERR;
   Double_t        p_ORIVX_CHI2;
   Int_t           p_ORIVX_NDOF;
   Float_t         p_ORIVX_COV_[3][3];
   Double_t        p_IP_ORIVX;
   Double_t        p_IPCHI2_ORIVX;
   Double_t        p_P;
   Double_t        p_PT;
   Double_t        p_PE;
   Double_t        p_PX;
   Double_t        p_PY;
   Double_t        p_PZ;
   Double_t        p_M;
   Int_t           p_ID;
   Double_t        p_PIDe;
   Double_t        p_PIDmu;
   Double_t        p_PIDK;
   Double_t        p_PIDp;
   Double_t        p_ProbNNe;
   Double_t        p_ProbNNk;
   Double_t        p_ProbNNp;
   Double_t        p_ProbNNpi;
   Double_t        p_ProbNNmu;
   Double_t        p_ProbNNghost;
   Bool_t          p_hasMuon;
   Bool_t          p_isMuon;
   Bool_t          p_hasRich;
   Bool_t          p_hasCalo;
   Int_t           p_TRACK_Type;
   Int_t           p_TRACK_Key;
   Double_t        p_TRACK_CHI2NDOF;
   Double_t        p_TRACK_PCHI2;
   Double_t        p_TRACK_MatchCHI2;
   Double_t        p_TRACK_GhostProb;
   Double_t        p_TRACK_CloneDist;
   Double_t        p_TRACK_Likelihood;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   Double_t        nLong;
   Double_t        nTracks;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLT1TCK;
   UInt_t          HLT2TCK;
   ULong64_t       GpsTime;
   Short_t         Polarity;

   // List of branches
   TBranch        *b_Xb_MINIP;   //!
   TBranch        *b_Xb_MINIPCHI2;   //!
   TBranch        *b_Xb_MINIPNEXTBEST;   //!
   TBranch        *b_Xb_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Xb_ENDVERTEX_X;   //!
   TBranch        *b_Xb_ENDVERTEX_Y;   //!
   TBranch        *b_Xb_ENDVERTEX_Z;   //!
   TBranch        *b_Xb_ENDVERTEX_XERR;   //!
   TBranch        *b_Xb_ENDVERTEX_YERR;   //!
   TBranch        *b_Xb_ENDVERTEX_ZERR;   //!
   TBranch        *b_Xb_ENDVERTEX_CHI2;   //!
   TBranch        *b_Xb_ENDVERTEX_NDOF;   //!
   TBranch        *b_Xb_ENDVERTEX_COV_;   //!
   TBranch        *b_Xb_OWNPV_X;   //!
   TBranch        *b_Xb_OWNPV_Y;   //!
   TBranch        *b_Xb_OWNPV_Z;   //!
   TBranch        *b_Xb_OWNPV_XERR;   //!
   TBranch        *b_Xb_OWNPV_YERR;   //!
   TBranch        *b_Xb_OWNPV_ZERR;   //!
   TBranch        *b_Xb_OWNPV_CHI2;   //!
   TBranch        *b_Xb_OWNPV_NDOF;   //!
   TBranch        *b_Xb_OWNPV_COV_;   //!
   TBranch        *b_Xb_IP_OWNPV;   //!
   TBranch        *b_Xb_IPCHI2_OWNPV;   //!
   TBranch        *b_Xb_FD_OWNPV;   //!
   TBranch        *b_Xb_FDCHI2_OWNPV;   //!
   TBranch        *b_Xb_DIRA_OWNPV;   //!
   TBranch        *b_Xb_TOPPV_X;   //!
   TBranch        *b_Xb_TOPPV_Y;   //!
   TBranch        *b_Xb_TOPPV_Z;   //!
   TBranch        *b_Xb_TOPPV_XERR;   //!
   TBranch        *b_Xb_TOPPV_YERR;   //!
   TBranch        *b_Xb_TOPPV_ZERR;   //!
   TBranch        *b_Xb_TOPPV_CHI2;   //!
   TBranch        *b_Xb_TOPPV_NDOF;   //!
   TBranch        *b_Xb_TOPPV_COV_;   //!
   TBranch        *b_Xb_IP_TOPPV;   //!
   TBranch        *b_Xb_IPCHI2_TOPPV;   //!
   TBranch        *b_Xb_FD_TOPPV;   //!
   TBranch        *b_Xb_FDCHI2_TOPPV;   //!
   TBranch        *b_Xb_DIRA_TOPPV;   //!
   TBranch        *b_Xb_P;   //!
   TBranch        *b_Xb_PT;   //!
   TBranch        *b_Xb_PE;   //!
   TBranch        *b_Xb_PX;   //!
   TBranch        *b_Xb_PY;   //!
   TBranch        *b_Xb_PZ;   //!
   TBranch        *b_Xb_MM;   //!
   TBranch        *b_Xb_MMERR;   //!
   TBranch        *b_Xb_M;   //!
   TBranch        *b_Xb_ID;   //!
   TBranch        *b_Xb_Nu_Parl;   //!
   TBranch        *b_Xb_Nu_Perp;   //!
   TBranch        *b_Xb_Nu_a;   //!
   TBranch        *b_Xb_Nu_X;   //!
   TBranch        *b_Xb_Nu_Y;   //!
   TBranch        *b_Xb_L0Global_Dec;   //!
   TBranch        *b_Xb_L0Global_TIS;   //!
   TBranch        *b_Xb_L0Global_TOS;   //!
   TBranch        *b_Xb_Hlt1Global_Dec;   //!
   TBranch        *b_Xb_Hlt1Global_TIS;   //!
   TBranch        *b_Xb_Hlt1Global_TOS;   //!
   TBranch        *b_Xb_Hlt1Phys_Dec;   //!
   TBranch        *b_Xb_Hlt1Phys_TIS;   //!
   TBranch        *b_Xb_Hlt1Phys_TOS;   //!
   TBranch        *b_Xb_Hlt2Global_Dec;   //!
   TBranch        *b_Xb_Hlt2Global_TIS;   //!
   TBranch        *b_Xb_Hlt2Global_TOS;   //!
   TBranch        *b_Xb_Hlt2Phys_Dec;   //!
   TBranch        *b_Xb_Hlt2Phys_TIS;   //!
   TBranch        *b_Xb_Hlt2Phys_TOS;   //!
   TBranch        *b_Xb_L0HCALDecision_Dec;   //!
   TBranch        *b_Xb_L0HCALDecision_TIS;   //!
   TBranch        *b_Xb_L0HCALDecision_TOS;   //!
   TBranch        *b_Xb_L0MuonDecision_Dec;   //!
   TBranch        *b_Xb_L0MuonDecision_TIS;   //!
   TBranch        *b_Xb_L0MuonDecision_TOS;   //!
   TBranch        *b_Xb_L0MuonHighDecision_Dec;   //!
   TBranch        *b_Xb_L0MuonHighDecision_TIS;   //!
   TBranch        *b_Xb_L0MuonHighDecision_TOS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPL0Decision_Dec;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPL0Decision_TIS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPL0Decision_TOS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_Xb_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_Xb_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_Xb_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_Xb_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_Xb_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_Xb_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_Xb_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_Xb_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_Xb_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_Xb_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_mu_MINIP;   //!
   TBranch        *b_mu_MINIPCHI2;   //!
   TBranch        *b_mu_MINIPNEXTBEST;   //!
   TBranch        *b_mu_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_mu_OWNPV_X;   //!
   TBranch        *b_mu_OWNPV_Y;   //!
   TBranch        *b_mu_OWNPV_Z;   //!
   TBranch        *b_mu_OWNPV_XERR;   //!
   TBranch        *b_mu_OWNPV_YERR;   //!
   TBranch        *b_mu_OWNPV_ZERR;   //!
   TBranch        *b_mu_OWNPV_CHI2;   //!
   TBranch        *b_mu_OWNPV_NDOF;   //!
   TBranch        *b_mu_OWNPV_COV_;   //!
   TBranch        *b_mu_IP_OWNPV;   //!
   TBranch        *b_mu_IPCHI2_OWNPV;   //!
   TBranch        *b_mu_TOPPV_X;   //!
   TBranch        *b_mu_TOPPV_Y;   //!
   TBranch        *b_mu_TOPPV_Z;   //!
   TBranch        *b_mu_TOPPV_XERR;   //!
   TBranch        *b_mu_TOPPV_YERR;   //!
   TBranch        *b_mu_TOPPV_ZERR;   //!
   TBranch        *b_mu_TOPPV_CHI2;   //!
   TBranch        *b_mu_TOPPV_NDOF;   //!
   TBranch        *b_mu_TOPPV_COV_;   //!
   TBranch        *b_mu_IP_TOPPV;   //!
   TBranch        *b_mu_IPCHI2_TOPPV;   //!
   TBranch        *b_mu_ORIVX_X;   //!
   TBranch        *b_mu_ORIVX_Y;   //!
   TBranch        *b_mu_ORIVX_Z;   //!
   TBranch        *b_mu_ORIVX_XERR;   //!
   TBranch        *b_mu_ORIVX_YERR;   //!
   TBranch        *b_mu_ORIVX_ZERR;   //!
   TBranch        *b_mu_ORIVX_CHI2;   //!
   TBranch        *b_mu_ORIVX_NDOF;   //!
   TBranch        *b_mu_ORIVX_COV_;   //!
   TBranch        *b_mu_IP_ORIVX;   //!
   TBranch        *b_mu_IPCHI2_ORIVX;   //!
   TBranch        *b_mu_P;   //!
   TBranch        *b_mu_PT;   //!
   TBranch        *b_mu_PE;   //!
   TBranch        *b_mu_PX;   //!
   TBranch        *b_mu_PY;   //!
   TBranch        *b_mu_PZ;   //!
   TBranch        *b_mu_M;   //!
   TBranch        *b_mu_ID;   //!
   TBranch        *b_mu_PIDe;   //!
   TBranch        *b_mu_PIDmu;   //!
   TBranch        *b_mu_PIDK;   //!
   TBranch        *b_mu_PIDp;   //!
   TBranch        *b_mu_ProbNNe;   //!
   TBranch        *b_mu_ProbNNk;   //!
   TBranch        *b_mu_ProbNNp;   //!
   TBranch        *b_mu_ProbNNpi;   //!
   TBranch        *b_mu_ProbNNmu;   //!
   TBranch        *b_mu_ProbNNghost;   //!
   TBranch        *b_mu_hasMuon;   //!
   TBranch        *b_mu_isMuon;   //!
   TBranch        *b_mu_hasRich;   //!
   TBranch        *b_mu_hasCalo;   //!
   TBranch        *b_mu_TRACK_Type;   //!
   TBranch        *b_mu_TRACK_Key;   //!
   TBranch        *b_mu_TRACK_CHI2NDOF;   //!
   TBranch        *b_mu_TRACK_PCHI2;   //!
   TBranch        *b_mu_TRACK_MatchCHI2;   //!
   TBranch        *b_mu_TRACK_GhostProb;   //!
   TBranch        *b_mu_TRACK_CloneDist;   //!
   TBranch        *b_mu_TRACK_Likelihood;   //!
   TBranch        *b_mu_L0Global_Dec;   //!
   TBranch        *b_mu_L0Global_TIS;   //!
   TBranch        *b_mu_L0Global_TOS;   //!
   TBranch        *b_mu_Hlt1Global_Dec;   //!
   TBranch        *b_mu_Hlt1Global_TIS;   //!
   TBranch        *b_mu_Hlt1Global_TOS;   //!
   TBranch        *b_mu_Hlt1Phys_Dec;   //!
   TBranch        *b_mu_Hlt1Phys_TIS;   //!
   TBranch        *b_mu_Hlt1Phys_TOS;   //!
   TBranch        *b_mu_Hlt2Global_Dec;   //!
   TBranch        *b_mu_Hlt2Global_TIS;   //!
   TBranch        *b_mu_Hlt2Global_TOS;   //!
   TBranch        *b_mu_Hlt2Phys_Dec;   //!
   TBranch        *b_mu_Hlt2Phys_TIS;   //!
   TBranch        *b_mu_Hlt2Phys_TOS;   //!
   TBranch        *b_mu_L0HCALDecision_Dec;   //!
   TBranch        *b_mu_L0HCALDecision_TIS;   //!
   TBranch        *b_mu_L0HCALDecision_TOS;   //!
   TBranch        *b_mu_L0MuonDecision_Dec;   //!
   TBranch        *b_mu_L0MuonDecision_TIS;   //!
   TBranch        *b_mu_L0MuonDecision_TOS;   //!
   TBranch        *b_mu_L0MuonHighDecision_Dec;   //!
   TBranch        *b_mu_L0MuonHighDecision_TIS;   //!
   TBranch        *b_mu_L0MuonHighDecision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPL0Decision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPL0Decision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPL0Decision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_Dec;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_TIS;   //!
   TBranch        *b_mu_Hlt1SingleMuonNoIPDecision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackAllL0Decision_TOS;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_mu_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonHighPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2SingleMuonLowPTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo2BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo3BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2Topo4BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu2BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu3BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TopoMu4BodyBBDTDecision_TOS;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_Dec;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_TIS;   //!
   TBranch        *b_mu_Hlt2TransparentDecision_TOS;   //!
   TBranch        *b_Xc_MINIP;   //!
   TBranch        *b_Xc_MINIPCHI2;   //!
   TBranch        *b_Xc_MINIPNEXTBEST;   //!
   TBranch        *b_Xc_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_Xc_ENDVERTEX_X;   //!
   TBranch        *b_Xc_ENDVERTEX_Y;   //!
   TBranch        *b_Xc_ENDVERTEX_Z;   //!
   TBranch        *b_Xc_ENDVERTEX_XERR;   //!
   TBranch        *b_Xc_ENDVERTEX_YERR;   //!
   TBranch        *b_Xc_ENDVERTEX_ZERR;   //!
   TBranch        *b_Xc_ENDVERTEX_CHI2;   //!
   TBranch        *b_Xc_ENDVERTEX_NDOF;   //!
   TBranch        *b_Xc_ENDVERTEX_COV_;   //!
   TBranch        *b_Xc_OWNPV_X;   //!
   TBranch        *b_Xc_OWNPV_Y;   //!
   TBranch        *b_Xc_OWNPV_Z;   //!
   TBranch        *b_Xc_OWNPV_XERR;   //!
   TBranch        *b_Xc_OWNPV_YERR;   //!
   TBranch        *b_Xc_OWNPV_ZERR;   //!
   TBranch        *b_Xc_OWNPV_CHI2;   //!
   TBranch        *b_Xc_OWNPV_NDOF;   //!
   TBranch        *b_Xc_OWNPV_COV_;   //!
   TBranch        *b_Xc_IP_OWNPV;   //!
   TBranch        *b_Xc_IPCHI2_OWNPV;   //!
   TBranch        *b_Xc_FD_OWNPV;   //!
   TBranch        *b_Xc_FDCHI2_OWNPV;   //!
   TBranch        *b_Xc_DIRA_OWNPV;   //!
   TBranch        *b_Xc_TOPPV_X;   //!
   TBranch        *b_Xc_TOPPV_Y;   //!
   TBranch        *b_Xc_TOPPV_Z;   //!
   TBranch        *b_Xc_TOPPV_XERR;   //!
   TBranch        *b_Xc_TOPPV_YERR;   //!
   TBranch        *b_Xc_TOPPV_ZERR;   //!
   TBranch        *b_Xc_TOPPV_CHI2;   //!
   TBranch        *b_Xc_TOPPV_NDOF;   //!
   TBranch        *b_Xc_TOPPV_COV_;   //!
   TBranch        *b_Xc_IP_TOPPV;   //!
   TBranch        *b_Xc_IPCHI2_TOPPV;   //!
   TBranch        *b_Xc_FD_TOPPV;   //!
   TBranch        *b_Xc_FDCHI2_TOPPV;   //!
   TBranch        *b_Xc_DIRA_TOPPV;   //!
   TBranch        *b_Xc_ORIVX_X;   //!
   TBranch        *b_Xc_ORIVX_Y;   //!
   TBranch        *b_Xc_ORIVX_Z;   //!
   TBranch        *b_Xc_ORIVX_XERR;   //!
   TBranch        *b_Xc_ORIVX_YERR;   //!
   TBranch        *b_Xc_ORIVX_ZERR;   //!
   TBranch        *b_Xc_ORIVX_CHI2;   //!
   TBranch        *b_Xc_ORIVX_NDOF;   //!
   TBranch        *b_Xc_ORIVX_COV_;   //!
   TBranch        *b_Xc_IP_ORIVX;   //!
   TBranch        *b_Xc_IPCHI2_ORIVX;   //!
   TBranch        *b_Xc_FD_ORIVX;   //!
   TBranch        *b_Xc_FDCHI2_ORIVX;   //!
   TBranch        *b_Xc_DIRA_ORIVX;   //!
   TBranch        *b_Xc_P;   //!
   TBranch        *b_Xc_PT;   //!
   TBranch        *b_Xc_PE;   //!
   TBranch        *b_Xc_PX;   //!
   TBranch        *b_Xc_PY;   //!
   TBranch        *b_Xc_PZ;   //!
   TBranch        *b_Xc_MM;   //!
   TBranch        *b_Xc_MMERR;   //!
   TBranch        *b_Xc_M;   //!
   TBranch        *b_Xc_ID;   //!
   TBranch        *b_Xc_TAU;   //!
   TBranch        *b_Xc_TAUERR;   //!
   TBranch        *b_Xc_TAUCHI2;   //!
   TBranch        *b_pi_MINIP;   //!
   TBranch        *b_pi_MINIPCHI2;   //!
   TBranch        *b_pi_MINIPNEXTBEST;   //!
   TBranch        *b_pi_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_pi_OWNPV_X;   //!
   TBranch        *b_pi_OWNPV_Y;   //!
   TBranch        *b_pi_OWNPV_Z;   //!
   TBranch        *b_pi_OWNPV_XERR;   //!
   TBranch        *b_pi_OWNPV_YERR;   //!
   TBranch        *b_pi_OWNPV_ZERR;   //!
   TBranch        *b_pi_OWNPV_CHI2;   //!
   TBranch        *b_pi_OWNPV_NDOF;   //!
   TBranch        *b_pi_OWNPV_COV_;   //!
   TBranch        *b_pi_IP_OWNPV;   //!
   TBranch        *b_pi_IPCHI2_OWNPV;   //!
   TBranch        *b_pi_TOPPV_X;   //!
   TBranch        *b_pi_TOPPV_Y;   //!
   TBranch        *b_pi_TOPPV_Z;   //!
   TBranch        *b_pi_TOPPV_XERR;   //!
   TBranch        *b_pi_TOPPV_YERR;   //!
   TBranch        *b_pi_TOPPV_ZERR;   //!
   TBranch        *b_pi_TOPPV_CHI2;   //!
   TBranch        *b_pi_TOPPV_NDOF;   //!
   TBranch        *b_pi_TOPPV_COV_;   //!
   TBranch        *b_pi_IP_TOPPV;   //!
   TBranch        *b_pi_IPCHI2_TOPPV;   //!
   TBranch        *b_pi_ORIVX_X;   //!
   TBranch        *b_pi_ORIVX_Y;   //!
   TBranch        *b_pi_ORIVX_Z;   //!
   TBranch        *b_pi_ORIVX_XERR;   //!
   TBranch        *b_pi_ORIVX_YERR;   //!
   TBranch        *b_pi_ORIVX_ZERR;   //!
   TBranch        *b_pi_ORIVX_CHI2;   //!
   TBranch        *b_pi_ORIVX_NDOF;   //!
   TBranch        *b_pi_ORIVX_COV_;   //!
   TBranch        *b_pi_IP_ORIVX;   //!
   TBranch        *b_pi_IPCHI2_ORIVX;   //!
   TBranch        *b_pi_P;   //!
   TBranch        *b_pi_PT;   //!
   TBranch        *b_pi_PE;   //!
   TBranch        *b_pi_PX;   //!
   TBranch        *b_pi_PY;   //!
   TBranch        *b_pi_PZ;   //!
   TBranch        *b_pi_M;   //!
   TBranch        *b_pi_ID;   //!
   TBranch        *b_pi_PIDe;   //!
   TBranch        *b_pi_PIDmu;   //!
   TBranch        *b_pi_PIDK;   //!
   TBranch        *b_pi_PIDp;   //!
   TBranch        *b_pi_ProbNNe;   //!
   TBranch        *b_pi_ProbNNk;   //!
   TBranch        *b_pi_ProbNNp;   //!
   TBranch        *b_pi_ProbNNpi;   //!
   TBranch        *b_pi_ProbNNmu;   //!
   TBranch        *b_pi_ProbNNghost;   //!
   TBranch        *b_pi_hasMuon;   //!
   TBranch        *b_pi_isMuon;   //!
   TBranch        *b_pi_hasRich;   //!
   TBranch        *b_pi_hasCalo;   //!
   TBranch        *b_pi_TRACK_Type;   //!
   TBranch        *b_pi_TRACK_Key;   //!
   TBranch        *b_pi_TRACK_CHI2NDOF;   //!
   TBranch        *b_pi_TRACK_PCHI2;   //!
   TBranch        *b_pi_TRACK_MatchCHI2;   //!
   TBranch        *b_pi_TRACK_GhostProb;   //!
   TBranch        *b_pi_TRACK_CloneDist;   //!
   TBranch        *b_pi_TRACK_Likelihood;   //!
   TBranch        *b_K_MINIP;   //!
   TBranch        *b_K_MINIPCHI2;   //!
   TBranch        *b_K_MINIPNEXTBEST;   //!
   TBranch        *b_K_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_K_OWNPV_X;   //!
   TBranch        *b_K_OWNPV_Y;   //!
   TBranch        *b_K_OWNPV_Z;   //!
   TBranch        *b_K_OWNPV_XERR;   //!
   TBranch        *b_K_OWNPV_YERR;   //!
   TBranch        *b_K_OWNPV_ZERR;   //!
   TBranch        *b_K_OWNPV_CHI2;   //!
   TBranch        *b_K_OWNPV_NDOF;   //!
   TBranch        *b_K_OWNPV_COV_;   //!
   TBranch        *b_K_IP_OWNPV;   //!
   TBranch        *b_K_IPCHI2_OWNPV;   //!
   TBranch        *b_K_TOPPV_X;   //!
   TBranch        *b_K_TOPPV_Y;   //!
   TBranch        *b_K_TOPPV_Z;   //!
   TBranch        *b_K_TOPPV_XERR;   //!
   TBranch        *b_K_TOPPV_YERR;   //!
   TBranch        *b_K_TOPPV_ZERR;   //!
   TBranch        *b_K_TOPPV_CHI2;   //!
   TBranch        *b_K_TOPPV_NDOF;   //!
   TBranch        *b_K_TOPPV_COV_;   //!
   TBranch        *b_K_IP_TOPPV;   //!
   TBranch        *b_K_IPCHI2_TOPPV;   //!
   TBranch        *b_K_ORIVX_X;   //!
   TBranch        *b_K_ORIVX_Y;   //!
   TBranch        *b_K_ORIVX_Z;   //!
   TBranch        *b_K_ORIVX_XERR;   //!
   TBranch        *b_K_ORIVX_YERR;   //!
   TBranch        *b_K_ORIVX_ZERR;   //!
   TBranch        *b_K_ORIVX_CHI2;   //!
   TBranch        *b_K_ORIVX_NDOF;   //!
   TBranch        *b_K_ORIVX_COV_;   //!
   TBranch        *b_K_IP_ORIVX;   //!
   TBranch        *b_K_IPCHI2_ORIVX;   //!
   TBranch        *b_K_P;   //!
   TBranch        *b_K_PT;   //!
   TBranch        *b_K_PE;   //!
   TBranch        *b_K_PX;   //!
   TBranch        *b_K_PY;   //!
   TBranch        *b_K_PZ;   //!
   TBranch        *b_K_M;   //!
   TBranch        *b_K_ID;   //!
   TBranch        *b_K_PIDe;   //!
   TBranch        *b_K_PIDmu;   //!
   TBranch        *b_K_PIDK;   //!
   TBranch        *b_K_PIDp;   //!
   TBranch        *b_K_ProbNNe;   //!
   TBranch        *b_K_ProbNNk;   //!
   TBranch        *b_K_ProbNNp;   //!
   TBranch        *b_K_ProbNNpi;   //!
   TBranch        *b_K_ProbNNmu;   //!
   TBranch        *b_K_ProbNNghost;   //!
   TBranch        *b_K_hasMuon;   //!
   TBranch        *b_K_isMuon;   //!
   TBranch        *b_K_hasRich;   //!
   TBranch        *b_K_hasCalo;   //!
   TBranch        *b_K_TRACK_Type;   //!
   TBranch        *b_K_TRACK_Key;   //!
   TBranch        *b_K_TRACK_CHI2NDOF;   //!
   TBranch        *b_K_TRACK_PCHI2;   //!
   TBranch        *b_K_TRACK_MatchCHI2;   //!
   TBranch        *b_K_TRACK_GhostProb;   //!
   TBranch        *b_K_TRACK_CloneDist;   //!
   TBranch        *b_K_TRACK_Likelihood;   //!
   TBranch        *b_p_MINIP;   //!
   TBranch        *b_p_MINIPCHI2;   //!
   TBranch        *b_p_MINIPNEXTBEST;   //!
   TBranch        *b_p_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_p_OWNPV_X;   //!
   TBranch        *b_p_OWNPV_Y;   //!
   TBranch        *b_p_OWNPV_Z;   //!
   TBranch        *b_p_OWNPV_XERR;   //!
   TBranch        *b_p_OWNPV_YERR;   //!
   TBranch        *b_p_OWNPV_ZERR;   //!
   TBranch        *b_p_OWNPV_CHI2;   //!
   TBranch        *b_p_OWNPV_NDOF;   //!
   TBranch        *b_p_OWNPV_COV_;   //!
   TBranch        *b_p_IP_OWNPV;   //!
   TBranch        *b_p_IPCHI2_OWNPV;   //!
   TBranch        *b_p_TOPPV_X;   //!
   TBranch        *b_p_TOPPV_Y;   //!
   TBranch        *b_p_TOPPV_Z;   //!
   TBranch        *b_p_TOPPV_XERR;   //!
   TBranch        *b_p_TOPPV_YERR;   //!
   TBranch        *b_p_TOPPV_ZERR;   //!
   TBranch        *b_p_TOPPV_CHI2;   //!
   TBranch        *b_p_TOPPV_NDOF;   //!
   TBranch        *b_p_TOPPV_COV_;   //!
   TBranch        *b_p_IP_TOPPV;   //!
   TBranch        *b_p_IPCHI2_TOPPV;   //!
   TBranch        *b_p_ORIVX_X;   //!
   TBranch        *b_p_ORIVX_Y;   //!
   TBranch        *b_p_ORIVX_Z;   //!
   TBranch        *b_p_ORIVX_XERR;   //!
   TBranch        *b_p_ORIVX_YERR;   //!
   TBranch        *b_p_ORIVX_ZERR;   //!
   TBranch        *b_p_ORIVX_CHI2;   //!
   TBranch        *b_p_ORIVX_NDOF;   //!
   TBranch        *b_p_ORIVX_COV_;   //!
   TBranch        *b_p_IP_ORIVX;   //!
   TBranch        *b_p_IPCHI2_ORIVX;   //!
   TBranch        *b_p_P;   //!
   TBranch        *b_p_PT;   //!
   TBranch        *b_p_PE;   //!
   TBranch        *b_p_PX;   //!
   TBranch        *b_p_PY;   //!
   TBranch        *b_p_PZ;   //!
   TBranch        *b_p_M;   //!
   TBranch        *b_p_ID;   //!
   TBranch        *b_p_PIDe;   //!
   TBranch        *b_p_PIDmu;   //!
   TBranch        *b_p_PIDK;   //!
   TBranch        *b_p_PIDp;   //!
   TBranch        *b_p_ProbNNe;   //!
   TBranch        *b_p_ProbNNk;   //!
   TBranch        *b_p_ProbNNp;   //!
   TBranch        *b_p_ProbNNpi;   //!
   TBranch        *b_p_ProbNNmu;   //!
   TBranch        *b_p_ProbNNghost;   //!
   TBranch        *b_p_hasMuon;   //!
   TBranch        *b_p_isMuon;   //!
   TBranch        *b_p_hasRich;   //!
   TBranch        *b_p_hasCalo;   //!
   TBranch        *b_p_TRACK_Type;   //!
   TBranch        *b_p_TRACK_Key;   //!
   TBranch        *b_p_TRACK_CHI2NDOF;   //!
   TBranch        *b_p_TRACK_PCHI2;   //!
   TBranch        *b_p_TRACK_MatchCHI2;   //!
   TBranch        *b_p_TRACK_GhostProb;   //!
   TBranch        *b_p_TRACK_CloneDist;   //!
   TBranch        *b_p_TRACK_Likelihood;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_nLong;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLT1TCK;   //!
   TBranch        *b_HLT2TCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_Polarity;   //!

   Xic(TTree *tree=0);
   virtual ~Xic();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Xic_cxx
Xic::Xic(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = new TFile("all_2012_MAGUP.root");
     tree = (TTree*)f->Get("XicMu/mytree");
   }

   cout << "tree = " << tree << endl;
   
   Init(tree);
}

Xic::~Xic()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Xic::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Xic::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Xic::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Xb_MINIP", &Xb_MINIP, &b_Xb_MINIP);
   fChain->SetBranchAddress("Xb_MINIPCHI2", &Xb_MINIPCHI2, &b_Xb_MINIPCHI2);
   fChain->SetBranchAddress("Xb_MINIPNEXTBEST", &Xb_MINIPNEXTBEST, &b_Xb_MINIPNEXTBEST);
   fChain->SetBranchAddress("Xb_MINIPCHI2NEXTBEST", &Xb_MINIPCHI2NEXTBEST, &b_Xb_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Xb_ENDVERTEX_X", &Xb_ENDVERTEX_X, &b_Xb_ENDVERTEX_X);
   fChain->SetBranchAddress("Xb_ENDVERTEX_Y", &Xb_ENDVERTEX_Y, &b_Xb_ENDVERTEX_Y);
   fChain->SetBranchAddress("Xb_ENDVERTEX_Z", &Xb_ENDVERTEX_Z, &b_Xb_ENDVERTEX_Z);
   fChain->SetBranchAddress("Xb_ENDVERTEX_XERR", &Xb_ENDVERTEX_XERR, &b_Xb_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Xb_ENDVERTEX_YERR", &Xb_ENDVERTEX_YERR, &b_Xb_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Xb_ENDVERTEX_ZERR", &Xb_ENDVERTEX_ZERR, &b_Xb_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Xb_ENDVERTEX_CHI2", &Xb_ENDVERTEX_CHI2, &b_Xb_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Xb_ENDVERTEX_NDOF", &Xb_ENDVERTEX_NDOF, &b_Xb_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Xb_ENDVERTEX_COV_", Xb_ENDVERTEX_COV_, &b_Xb_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Xb_OWNPV_X", &Xb_OWNPV_X, &b_Xb_OWNPV_X);
   fChain->SetBranchAddress("Xb_OWNPV_Y", &Xb_OWNPV_Y, &b_Xb_OWNPV_Y);
   fChain->SetBranchAddress("Xb_OWNPV_Z", &Xb_OWNPV_Z, &b_Xb_OWNPV_Z);
   fChain->SetBranchAddress("Xb_OWNPV_XERR", &Xb_OWNPV_XERR, &b_Xb_OWNPV_XERR);
   fChain->SetBranchAddress("Xb_OWNPV_YERR", &Xb_OWNPV_YERR, &b_Xb_OWNPV_YERR);
   fChain->SetBranchAddress("Xb_OWNPV_ZERR", &Xb_OWNPV_ZERR, &b_Xb_OWNPV_ZERR);
   fChain->SetBranchAddress("Xb_OWNPV_CHI2", &Xb_OWNPV_CHI2, &b_Xb_OWNPV_CHI2);
   fChain->SetBranchAddress("Xb_OWNPV_NDOF", &Xb_OWNPV_NDOF, &b_Xb_OWNPV_NDOF);
   fChain->SetBranchAddress("Xb_OWNPV_COV_", Xb_OWNPV_COV_, &b_Xb_OWNPV_COV_);
   fChain->SetBranchAddress("Xb_IP_OWNPV", &Xb_IP_OWNPV, &b_Xb_IP_OWNPV);
   fChain->SetBranchAddress("Xb_IPCHI2_OWNPV", &Xb_IPCHI2_OWNPV, &b_Xb_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Xb_FD_OWNPV", &Xb_FD_OWNPV, &b_Xb_FD_OWNPV);
   fChain->SetBranchAddress("Xb_FDCHI2_OWNPV", &Xb_FDCHI2_OWNPV, &b_Xb_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Xb_DIRA_OWNPV", &Xb_DIRA_OWNPV, &b_Xb_DIRA_OWNPV);
   fChain->SetBranchAddress("Xb_TOPPV_X", &Xb_TOPPV_X, &b_Xb_TOPPV_X);
   fChain->SetBranchAddress("Xb_TOPPV_Y", &Xb_TOPPV_Y, &b_Xb_TOPPV_Y);
   fChain->SetBranchAddress("Xb_TOPPV_Z", &Xb_TOPPV_Z, &b_Xb_TOPPV_Z);
   fChain->SetBranchAddress("Xb_TOPPV_XERR", &Xb_TOPPV_XERR, &b_Xb_TOPPV_XERR);
   fChain->SetBranchAddress("Xb_TOPPV_YERR", &Xb_TOPPV_YERR, &b_Xb_TOPPV_YERR);
   fChain->SetBranchAddress("Xb_TOPPV_ZERR", &Xb_TOPPV_ZERR, &b_Xb_TOPPV_ZERR);
   fChain->SetBranchAddress("Xb_TOPPV_CHI2", &Xb_TOPPV_CHI2, &b_Xb_TOPPV_CHI2);
   fChain->SetBranchAddress("Xb_TOPPV_NDOF", &Xb_TOPPV_NDOF, &b_Xb_TOPPV_NDOF);
   fChain->SetBranchAddress("Xb_TOPPV_COV_", Xb_TOPPV_COV_, &b_Xb_TOPPV_COV_);
   fChain->SetBranchAddress("Xb_IP_TOPPV", &Xb_IP_TOPPV, &b_Xb_IP_TOPPV);
   fChain->SetBranchAddress("Xb_IPCHI2_TOPPV", &Xb_IPCHI2_TOPPV, &b_Xb_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Xb_FD_TOPPV", &Xb_FD_TOPPV, &b_Xb_FD_TOPPV);
   fChain->SetBranchAddress("Xb_FDCHI2_TOPPV", &Xb_FDCHI2_TOPPV, &b_Xb_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Xb_DIRA_TOPPV", &Xb_DIRA_TOPPV, &b_Xb_DIRA_TOPPV);
   fChain->SetBranchAddress("Xb_P", &Xb_P, &b_Xb_P);
   fChain->SetBranchAddress("Xb_PT", &Xb_PT, &b_Xb_PT);
   fChain->SetBranchAddress("Xb_PE", &Xb_PE, &b_Xb_PE);
   fChain->SetBranchAddress("Xb_PX", &Xb_PX, &b_Xb_PX);
   fChain->SetBranchAddress("Xb_PY", &Xb_PY, &b_Xb_PY);
   fChain->SetBranchAddress("Xb_PZ", &Xb_PZ, &b_Xb_PZ);
   fChain->SetBranchAddress("Xb_MM", &Xb_MM, &b_Xb_MM);
   fChain->SetBranchAddress("Xb_MMERR", &Xb_MMERR, &b_Xb_MMERR);
   fChain->SetBranchAddress("Xb_M", &Xb_M, &b_Xb_M);
   fChain->SetBranchAddress("Xb_ID", &Xb_ID, &b_Xb_ID);
   fChain->SetBranchAddress("Xb_Nu_Parl", &Xb_Nu_Parl, &b_Xb_Nu_Parl);
   fChain->SetBranchAddress("Xb_Nu_Perp", &Xb_Nu_Perp, &b_Xb_Nu_Perp);
   fChain->SetBranchAddress("Xb_Nu_a", &Xb_Nu_a, &b_Xb_Nu_a);
   fChain->SetBranchAddress("Xb_Nu_X", &Xb_Nu_X, &b_Xb_Nu_X);
   fChain->SetBranchAddress("Xb_Nu_Y", &Xb_Nu_Y, &b_Xb_Nu_Y);
   fChain->SetBranchAddress("Xb_L0Global_Dec", &Xb_L0Global_Dec, &b_Xb_L0Global_Dec);
   fChain->SetBranchAddress("Xb_L0Global_TIS", &Xb_L0Global_TIS, &b_Xb_L0Global_TIS);
   fChain->SetBranchAddress("Xb_L0Global_TOS", &Xb_L0Global_TOS, &b_Xb_L0Global_TOS);
   fChain->SetBranchAddress("Xb_Hlt1Global_Dec", &Xb_Hlt1Global_Dec, &b_Xb_Hlt1Global_Dec);
   fChain->SetBranchAddress("Xb_Hlt1Global_TIS", &Xb_Hlt1Global_TIS, &b_Xb_Hlt1Global_TIS);
   fChain->SetBranchAddress("Xb_Hlt1Global_TOS", &Xb_Hlt1Global_TOS, &b_Xb_Hlt1Global_TOS);
   fChain->SetBranchAddress("Xb_Hlt1Phys_Dec", &Xb_Hlt1Phys_Dec, &b_Xb_Hlt1Phys_Dec);
   fChain->SetBranchAddress("Xb_Hlt1Phys_TIS", &Xb_Hlt1Phys_TIS, &b_Xb_Hlt1Phys_TIS);
   fChain->SetBranchAddress("Xb_Hlt1Phys_TOS", &Xb_Hlt1Phys_TOS, &b_Xb_Hlt1Phys_TOS);
   fChain->SetBranchAddress("Xb_Hlt2Global_Dec", &Xb_Hlt2Global_Dec, &b_Xb_Hlt2Global_Dec);
   fChain->SetBranchAddress("Xb_Hlt2Global_TIS", &Xb_Hlt2Global_TIS, &b_Xb_Hlt2Global_TIS);
   fChain->SetBranchAddress("Xb_Hlt2Global_TOS", &Xb_Hlt2Global_TOS, &b_Xb_Hlt2Global_TOS);
   fChain->SetBranchAddress("Xb_Hlt2Phys_Dec", &Xb_Hlt2Phys_Dec, &b_Xb_Hlt2Phys_Dec);
   fChain->SetBranchAddress("Xb_Hlt2Phys_TIS", &Xb_Hlt2Phys_TIS, &b_Xb_Hlt2Phys_TIS);
   fChain->SetBranchAddress("Xb_Hlt2Phys_TOS", &Xb_Hlt2Phys_TOS, &b_Xb_Hlt2Phys_TOS);
   fChain->SetBranchAddress("Xb_L0HCALDecision_Dec", &Xb_L0HCALDecision_Dec, &b_Xb_L0HCALDecision_Dec);
   fChain->SetBranchAddress("Xb_L0HCALDecision_TIS", &Xb_L0HCALDecision_TIS, &b_Xb_L0HCALDecision_TIS);
   fChain->SetBranchAddress("Xb_L0HCALDecision_TOS", &Xb_L0HCALDecision_TOS, &b_Xb_L0HCALDecision_TOS);
   fChain->SetBranchAddress("Xb_L0MuonDecision_Dec", &Xb_L0MuonDecision_Dec, &b_Xb_L0MuonDecision_Dec);
   fChain->SetBranchAddress("Xb_L0MuonDecision_TIS", &Xb_L0MuonDecision_TIS, &b_Xb_L0MuonDecision_TIS);
   fChain->SetBranchAddress("Xb_L0MuonDecision_TOS", &Xb_L0MuonDecision_TOS, &b_Xb_L0MuonDecision_TOS);
   fChain->SetBranchAddress("Xb_L0MuonHighDecision_Dec", &Xb_L0MuonHighDecision_Dec, &b_Xb_L0MuonHighDecision_Dec);
   fChain->SetBranchAddress("Xb_L0MuonHighDecision_TIS", &Xb_L0MuonHighDecision_TIS, &b_Xb_L0MuonHighDecision_TIS);
   fChain->SetBranchAddress("Xb_L0MuonHighDecision_TOS", &Xb_L0MuonHighDecision_TOS, &b_Xb_L0MuonHighDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPL0Decision_Dec", &Xb_Hlt1SingleMuonNoIPL0Decision_Dec, &b_Xb_Hlt1SingleMuonNoIPL0Decision_Dec);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPL0Decision_TIS", &Xb_Hlt1SingleMuonNoIPL0Decision_TIS, &b_Xb_Hlt1SingleMuonNoIPL0Decision_TIS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPL0Decision_TOS", &Xb_Hlt1SingleMuonNoIPL0Decision_TOS, &b_Xb_Hlt1SingleMuonNoIPL0Decision_TOS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonHighPTDecision_Dec", &Xb_Hlt1SingleMuonHighPTDecision_Dec, &b_Xb_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonHighPTDecision_TIS", &Xb_Hlt1SingleMuonHighPTDecision_TIS, &b_Xb_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonHighPTDecision_TOS", &Xb_Hlt1SingleMuonHighPTDecision_TOS, &b_Xb_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPDecision_Dec", &Xb_Hlt1SingleMuonNoIPDecision_Dec, &b_Xb_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPDecision_TIS", &Xb_Hlt1SingleMuonNoIPDecision_TIS, &b_Xb_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt1SingleMuonNoIPDecision_TOS", &Xb_Hlt1SingleMuonNoIPDecision_TOS, &b_Xb_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt1TrackAllL0Decision_Dec", &Xb_Hlt1TrackAllL0Decision_Dec, &b_Xb_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("Xb_Hlt1TrackAllL0Decision_TIS", &Xb_Hlt1TrackAllL0Decision_TIS, &b_Xb_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("Xb_Hlt1TrackAllL0Decision_TOS", &Xb_Hlt1TrackAllL0Decision_TOS, &b_Xb_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("Xb_Hlt1TrackMuonDecision_Dec", &Xb_Hlt1TrackMuonDecision_Dec, &b_Xb_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt1TrackMuonDecision_TIS", &Xb_Hlt1TrackMuonDecision_TIS, &b_Xb_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt1TrackMuonDecision_TOS", &Xb_Hlt1TrackMuonDecision_TOS, &b_Xb_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonDecision_Dec", &Xb_Hlt2SingleMuonDecision_Dec, &b_Xb_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonDecision_TIS", &Xb_Hlt2SingleMuonDecision_TIS, &b_Xb_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonDecision_TOS", &Xb_Hlt2SingleMuonDecision_TOS, &b_Xb_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonHighPTDecision_Dec", &Xb_Hlt2SingleMuonHighPTDecision_Dec, &b_Xb_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonHighPTDecision_TIS", &Xb_Hlt2SingleMuonHighPTDecision_TIS, &b_Xb_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonHighPTDecision_TOS", &Xb_Hlt2SingleMuonHighPTDecision_TOS, &b_Xb_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonLowPTDecision_Dec", &Xb_Hlt2SingleMuonLowPTDecision_Dec, &b_Xb_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonLowPTDecision_TIS", &Xb_Hlt2SingleMuonLowPTDecision_TIS, &b_Xb_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2SingleMuonLowPTDecision_TOS", &Xb_Hlt2SingleMuonLowPTDecision_TOS, &b_Xb_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2Topo2BodyBBDTDecision_Dec", &Xb_Hlt2Topo2BodyBBDTDecision_Dec, &b_Xb_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2Topo2BodyBBDTDecision_TIS", &Xb_Hlt2Topo2BodyBBDTDecision_TIS, &b_Xb_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2Topo2BodyBBDTDecision_TOS", &Xb_Hlt2Topo2BodyBBDTDecision_TOS, &b_Xb_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2Topo3BodyBBDTDecision_Dec", &Xb_Hlt2Topo3BodyBBDTDecision_Dec, &b_Xb_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2Topo3BodyBBDTDecision_TIS", &Xb_Hlt2Topo3BodyBBDTDecision_TIS, &b_Xb_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2Topo3BodyBBDTDecision_TOS", &Xb_Hlt2Topo3BodyBBDTDecision_TOS, &b_Xb_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2Topo4BodyBBDTDecision_Dec", &Xb_Hlt2Topo4BodyBBDTDecision_Dec, &b_Xb_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2Topo4BodyBBDTDecision_TIS", &Xb_Hlt2Topo4BodyBBDTDecision_TIS, &b_Xb_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2Topo4BodyBBDTDecision_TOS", &Xb_Hlt2Topo4BodyBBDTDecision_TOS, &b_Xb_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu2BodyBBDTDecision_Dec", &Xb_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_Xb_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu2BodyBBDTDecision_TIS", &Xb_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_Xb_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu2BodyBBDTDecision_TOS", &Xb_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_Xb_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu3BodyBBDTDecision_Dec", &Xb_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_Xb_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu3BodyBBDTDecision_TIS", &Xb_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_Xb_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu3BodyBBDTDecision_TOS", &Xb_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_Xb_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu4BodyBBDTDecision_Dec", &Xb_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_Xb_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu4BodyBBDTDecision_TIS", &Xb_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_Xb_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2TopoMu4BodyBBDTDecision_TOS", &Xb_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_Xb_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("Xb_Hlt2TransparentDecision_Dec", &Xb_Hlt2TransparentDecision_Dec, &b_Xb_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("Xb_Hlt2TransparentDecision_TIS", &Xb_Hlt2TransparentDecision_TIS, &b_Xb_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("Xb_Hlt2TransparentDecision_TOS", &Xb_Hlt2TransparentDecision_TOS, &b_Xb_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("mu_MINIP", &mu_MINIP, &b_mu_MINIP);
   fChain->SetBranchAddress("mu_MINIPCHI2", &mu_MINIPCHI2, &b_mu_MINIPCHI2);
   fChain->SetBranchAddress("mu_MINIPNEXTBEST", &mu_MINIPNEXTBEST, &b_mu_MINIPNEXTBEST);
   fChain->SetBranchAddress("mu_MINIPCHI2NEXTBEST", &mu_MINIPCHI2NEXTBEST, &b_mu_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("mu_OWNPV_X", &mu_OWNPV_X, &b_mu_OWNPV_X);
   fChain->SetBranchAddress("mu_OWNPV_Y", &mu_OWNPV_Y, &b_mu_OWNPV_Y);
   fChain->SetBranchAddress("mu_OWNPV_Z", &mu_OWNPV_Z, &b_mu_OWNPV_Z);
   fChain->SetBranchAddress("mu_OWNPV_XERR", &mu_OWNPV_XERR, &b_mu_OWNPV_XERR);
   fChain->SetBranchAddress("mu_OWNPV_YERR", &mu_OWNPV_YERR, &b_mu_OWNPV_YERR);
   fChain->SetBranchAddress("mu_OWNPV_ZERR", &mu_OWNPV_ZERR, &b_mu_OWNPV_ZERR);
   fChain->SetBranchAddress("mu_OWNPV_CHI2", &mu_OWNPV_CHI2, &b_mu_OWNPV_CHI2);
   fChain->SetBranchAddress("mu_OWNPV_NDOF", &mu_OWNPV_NDOF, &b_mu_OWNPV_NDOF);
   fChain->SetBranchAddress("mu_OWNPV_COV_", mu_OWNPV_COV_, &b_mu_OWNPV_COV_);
   fChain->SetBranchAddress("mu_IP_OWNPV", &mu_IP_OWNPV, &b_mu_IP_OWNPV);
   fChain->SetBranchAddress("mu_IPCHI2_OWNPV", &mu_IPCHI2_OWNPV, &b_mu_IPCHI2_OWNPV);
   fChain->SetBranchAddress("mu_TOPPV_X", &mu_TOPPV_X, &b_mu_TOPPV_X);
   fChain->SetBranchAddress("mu_TOPPV_Y", &mu_TOPPV_Y, &b_mu_TOPPV_Y);
   fChain->SetBranchAddress("mu_TOPPV_Z", &mu_TOPPV_Z, &b_mu_TOPPV_Z);
   fChain->SetBranchAddress("mu_TOPPV_XERR", &mu_TOPPV_XERR, &b_mu_TOPPV_XERR);
   fChain->SetBranchAddress("mu_TOPPV_YERR", &mu_TOPPV_YERR, &b_mu_TOPPV_YERR);
   fChain->SetBranchAddress("mu_TOPPV_ZERR", &mu_TOPPV_ZERR, &b_mu_TOPPV_ZERR);
   fChain->SetBranchAddress("mu_TOPPV_CHI2", &mu_TOPPV_CHI2, &b_mu_TOPPV_CHI2);
   fChain->SetBranchAddress("mu_TOPPV_NDOF", &mu_TOPPV_NDOF, &b_mu_TOPPV_NDOF);
   fChain->SetBranchAddress("mu_TOPPV_COV_", mu_TOPPV_COV_, &b_mu_TOPPV_COV_);
   fChain->SetBranchAddress("mu_IP_TOPPV", &mu_IP_TOPPV, &b_mu_IP_TOPPV);
   fChain->SetBranchAddress("mu_IPCHI2_TOPPV", &mu_IPCHI2_TOPPV, &b_mu_IPCHI2_TOPPV);
   fChain->SetBranchAddress("mu_ORIVX_X", &mu_ORIVX_X, &b_mu_ORIVX_X);
   fChain->SetBranchAddress("mu_ORIVX_Y", &mu_ORIVX_Y, &b_mu_ORIVX_Y);
   fChain->SetBranchAddress("mu_ORIVX_Z", &mu_ORIVX_Z, &b_mu_ORIVX_Z);
   fChain->SetBranchAddress("mu_ORIVX_XERR", &mu_ORIVX_XERR, &b_mu_ORIVX_XERR);
   fChain->SetBranchAddress("mu_ORIVX_YERR", &mu_ORIVX_YERR, &b_mu_ORIVX_YERR);
   fChain->SetBranchAddress("mu_ORIVX_ZERR", &mu_ORIVX_ZERR, &b_mu_ORIVX_ZERR);
   fChain->SetBranchAddress("mu_ORIVX_CHI2", &mu_ORIVX_CHI2, &b_mu_ORIVX_CHI2);
   fChain->SetBranchAddress("mu_ORIVX_NDOF", &mu_ORIVX_NDOF, &b_mu_ORIVX_NDOF);
   fChain->SetBranchAddress("mu_ORIVX_COV_", mu_ORIVX_COV_, &b_mu_ORIVX_COV_);
   fChain->SetBranchAddress("mu_IP_ORIVX", &mu_IP_ORIVX, &b_mu_IP_ORIVX);
   fChain->SetBranchAddress("mu_IPCHI2_ORIVX", &mu_IPCHI2_ORIVX, &b_mu_IPCHI2_ORIVX);
   fChain->SetBranchAddress("mu_P", &mu_P, &b_mu_P);
   fChain->SetBranchAddress("mu_PT", &mu_PT, &b_mu_PT);
   fChain->SetBranchAddress("mu_PE", &mu_PE, &b_mu_PE);
   fChain->SetBranchAddress("mu_PX", &mu_PX, &b_mu_PX);
   fChain->SetBranchAddress("mu_PY", &mu_PY, &b_mu_PY);
   fChain->SetBranchAddress("mu_PZ", &mu_PZ, &b_mu_PZ);
   fChain->SetBranchAddress("mu_M", &mu_M, &b_mu_M);
   fChain->SetBranchAddress("mu_ID", &mu_ID, &b_mu_ID);
   fChain->SetBranchAddress("mu_PIDe", &mu_PIDe, &b_mu_PIDe);
   fChain->SetBranchAddress("mu_PIDmu", &mu_PIDmu, &b_mu_PIDmu);
   fChain->SetBranchAddress("mu_PIDK", &mu_PIDK, &b_mu_PIDK);
   fChain->SetBranchAddress("mu_PIDp", &mu_PIDp, &b_mu_PIDp);
   fChain->SetBranchAddress("mu_ProbNNe", &mu_ProbNNe, &b_mu_ProbNNe);
   fChain->SetBranchAddress("mu_ProbNNk", &mu_ProbNNk, &b_mu_ProbNNk);
   fChain->SetBranchAddress("mu_ProbNNp", &mu_ProbNNp, &b_mu_ProbNNp);
   fChain->SetBranchAddress("mu_ProbNNpi", &mu_ProbNNpi, &b_mu_ProbNNpi);
   fChain->SetBranchAddress("mu_ProbNNmu", &mu_ProbNNmu, &b_mu_ProbNNmu);
   fChain->SetBranchAddress("mu_ProbNNghost", &mu_ProbNNghost, &b_mu_ProbNNghost);
   fChain->SetBranchAddress("mu_hasMuon", &mu_hasMuon, &b_mu_hasMuon);
   fChain->SetBranchAddress("mu_isMuon", &mu_isMuon, &b_mu_isMuon);
   fChain->SetBranchAddress("mu_hasRich", &mu_hasRich, &b_mu_hasRich);
   fChain->SetBranchAddress("mu_hasCalo", &mu_hasCalo, &b_mu_hasCalo);
   fChain->SetBranchAddress("mu_TRACK_Type", &mu_TRACK_Type, &b_mu_TRACK_Type);
   fChain->SetBranchAddress("mu_TRACK_Key", &mu_TRACK_Key, &b_mu_TRACK_Key);
   fChain->SetBranchAddress("mu_TRACK_CHI2NDOF", &mu_TRACK_CHI2NDOF, &b_mu_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("mu_TRACK_PCHI2", &mu_TRACK_PCHI2, &b_mu_TRACK_PCHI2);
   fChain->SetBranchAddress("mu_TRACK_MatchCHI2", &mu_TRACK_MatchCHI2, &b_mu_TRACK_MatchCHI2);
   fChain->SetBranchAddress("mu_TRACK_GhostProb", &mu_TRACK_GhostProb, &b_mu_TRACK_GhostProb);
   fChain->SetBranchAddress("mu_TRACK_CloneDist", &mu_TRACK_CloneDist, &b_mu_TRACK_CloneDist);
   fChain->SetBranchAddress("mu_TRACK_Likelihood", &mu_TRACK_Likelihood, &b_mu_TRACK_Likelihood);
   fChain->SetBranchAddress("mu_L0Global_Dec", &mu_L0Global_Dec, &b_mu_L0Global_Dec);
   fChain->SetBranchAddress("mu_L0Global_TIS", &mu_L0Global_TIS, &b_mu_L0Global_TIS);
   fChain->SetBranchAddress("mu_L0Global_TOS", &mu_L0Global_TOS, &b_mu_L0Global_TOS);
   fChain->SetBranchAddress("mu_Hlt1Global_Dec", &mu_Hlt1Global_Dec, &b_mu_Hlt1Global_Dec);
   fChain->SetBranchAddress("mu_Hlt1Global_TIS", &mu_Hlt1Global_TIS, &b_mu_Hlt1Global_TIS);
   fChain->SetBranchAddress("mu_Hlt1Global_TOS", &mu_Hlt1Global_TOS, &b_mu_Hlt1Global_TOS);
   fChain->SetBranchAddress("mu_Hlt1Phys_Dec", &mu_Hlt1Phys_Dec, &b_mu_Hlt1Phys_Dec);
   fChain->SetBranchAddress("mu_Hlt1Phys_TIS", &mu_Hlt1Phys_TIS, &b_mu_Hlt1Phys_TIS);
   fChain->SetBranchAddress("mu_Hlt1Phys_TOS", &mu_Hlt1Phys_TOS, &b_mu_Hlt1Phys_TOS);
   fChain->SetBranchAddress("mu_Hlt2Global_Dec", &mu_Hlt2Global_Dec, &b_mu_Hlt2Global_Dec);
   fChain->SetBranchAddress("mu_Hlt2Global_TIS", &mu_Hlt2Global_TIS, &b_mu_Hlt2Global_TIS);
   fChain->SetBranchAddress("mu_Hlt2Global_TOS", &mu_Hlt2Global_TOS, &b_mu_Hlt2Global_TOS);
   fChain->SetBranchAddress("mu_Hlt2Phys_Dec", &mu_Hlt2Phys_Dec, &b_mu_Hlt2Phys_Dec);
   fChain->SetBranchAddress("mu_Hlt2Phys_TIS", &mu_Hlt2Phys_TIS, &b_mu_Hlt2Phys_TIS);
   fChain->SetBranchAddress("mu_Hlt2Phys_TOS", &mu_Hlt2Phys_TOS, &b_mu_Hlt2Phys_TOS);
   fChain->SetBranchAddress("mu_L0HCALDecision_Dec", &mu_L0HCALDecision_Dec, &b_mu_L0HCALDecision_Dec);
   fChain->SetBranchAddress("mu_L0HCALDecision_TIS", &mu_L0HCALDecision_TIS, &b_mu_L0HCALDecision_TIS);
   fChain->SetBranchAddress("mu_L0HCALDecision_TOS", &mu_L0HCALDecision_TOS, &b_mu_L0HCALDecision_TOS);
   fChain->SetBranchAddress("mu_L0MuonDecision_Dec", &mu_L0MuonDecision_Dec, &b_mu_L0MuonDecision_Dec);
   fChain->SetBranchAddress("mu_L0MuonDecision_TIS", &mu_L0MuonDecision_TIS, &b_mu_L0MuonDecision_TIS);
   fChain->SetBranchAddress("mu_L0MuonDecision_TOS", &mu_L0MuonDecision_TOS, &b_mu_L0MuonDecision_TOS);
   fChain->SetBranchAddress("mu_L0MuonHighDecision_Dec", &mu_L0MuonHighDecision_Dec, &b_mu_L0MuonHighDecision_Dec);
   fChain->SetBranchAddress("mu_L0MuonHighDecision_TIS", &mu_L0MuonHighDecision_TIS, &b_mu_L0MuonHighDecision_TIS);
   fChain->SetBranchAddress("mu_L0MuonHighDecision_TOS", &mu_L0MuonHighDecision_TOS, &b_mu_L0MuonHighDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPL0Decision_Dec", &mu_Hlt1SingleMuonNoIPL0Decision_Dec, &b_mu_Hlt1SingleMuonNoIPL0Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPL0Decision_TIS", &mu_Hlt1SingleMuonNoIPL0Decision_TIS, &b_mu_Hlt1SingleMuonNoIPL0Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPL0Decision_TOS", &mu_Hlt1SingleMuonNoIPL0Decision_TOS, &b_mu_Hlt1SingleMuonNoIPL0Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_Dec", &mu_Hlt1SingleMuonHighPTDecision_Dec, &b_mu_Hlt1SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_TIS", &mu_Hlt1SingleMuonHighPTDecision_TIS, &b_mu_Hlt1SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonHighPTDecision_TOS", &mu_Hlt1SingleMuonHighPTDecision_TOS, &b_mu_Hlt1SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_Dec", &mu_Hlt1SingleMuonNoIPDecision_Dec, &b_mu_Hlt1SingleMuonNoIPDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_TIS", &mu_Hlt1SingleMuonNoIPDecision_TIS, &b_mu_Hlt1SingleMuonNoIPDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1SingleMuonNoIPDecision_TOS", &mu_Hlt1SingleMuonNoIPDecision_TOS, &b_mu_Hlt1SingleMuonNoIPDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_Dec", &mu_Hlt1TrackAllL0Decision_Dec, &b_mu_Hlt1TrackAllL0Decision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_TIS", &mu_Hlt1TrackAllL0Decision_TIS, &b_mu_Hlt1TrackAllL0Decision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackAllL0Decision_TOS", &mu_Hlt1TrackAllL0Decision_TOS, &b_mu_Hlt1TrackAllL0Decision_TOS);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_Dec", &mu_Hlt1TrackMuonDecision_Dec, &b_mu_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_TIS", &mu_Hlt1TrackMuonDecision_TIS, &b_mu_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt1TrackMuonDecision_TOS", &mu_Hlt1TrackMuonDecision_TOS, &b_mu_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_Dec", &mu_Hlt2SingleMuonDecision_Dec, &b_mu_Hlt2SingleMuonDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_TIS", &mu_Hlt2SingleMuonDecision_TIS, &b_mu_Hlt2SingleMuonDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonDecision_TOS", &mu_Hlt2SingleMuonDecision_TOS, &b_mu_Hlt2SingleMuonDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_Dec", &mu_Hlt2SingleMuonHighPTDecision_Dec, &b_mu_Hlt2SingleMuonHighPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_TIS", &mu_Hlt2SingleMuonHighPTDecision_TIS, &b_mu_Hlt2SingleMuonHighPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonHighPTDecision_TOS", &mu_Hlt2SingleMuonHighPTDecision_TOS, &b_mu_Hlt2SingleMuonHighPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_Dec", &mu_Hlt2SingleMuonLowPTDecision_Dec, &b_mu_Hlt2SingleMuonLowPTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_TIS", &mu_Hlt2SingleMuonLowPTDecision_TIS, &b_mu_Hlt2SingleMuonLowPTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2SingleMuonLowPTDecision_TOS", &mu_Hlt2SingleMuonLowPTDecision_TOS, &b_mu_Hlt2SingleMuonLowPTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_Dec", &mu_Hlt2Topo2BodyBBDTDecision_Dec, &b_mu_Hlt2Topo2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_TIS", &mu_Hlt2Topo2BodyBBDTDecision_TIS, &b_mu_Hlt2Topo2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo2BodyBBDTDecision_TOS", &mu_Hlt2Topo2BodyBBDTDecision_TOS, &b_mu_Hlt2Topo2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_Dec", &mu_Hlt2Topo3BodyBBDTDecision_Dec, &b_mu_Hlt2Topo3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_TIS", &mu_Hlt2Topo3BodyBBDTDecision_TIS, &b_mu_Hlt2Topo3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo3BodyBBDTDecision_TOS", &mu_Hlt2Topo3BodyBBDTDecision_TOS, &b_mu_Hlt2Topo3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_Dec", &mu_Hlt2Topo4BodyBBDTDecision_Dec, &b_mu_Hlt2Topo4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_TIS", &mu_Hlt2Topo4BodyBBDTDecision_TIS, &b_mu_Hlt2Topo4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2Topo4BodyBBDTDecision_TOS", &mu_Hlt2Topo4BodyBBDTDecision_TOS, &b_mu_Hlt2Topo4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_Dec", &mu_Hlt2TopoMu2BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu2BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_TIS", &mu_Hlt2TopoMu2BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu2BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu2BodyBBDTDecision_TOS", &mu_Hlt2TopoMu2BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu2BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_Dec", &mu_Hlt2TopoMu3BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu3BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_TIS", &mu_Hlt2TopoMu3BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu3BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu3BodyBBDTDecision_TOS", &mu_Hlt2TopoMu3BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu3BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_Dec", &mu_Hlt2TopoMu4BodyBBDTDecision_Dec, &b_mu_Hlt2TopoMu4BodyBBDTDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_TIS", &mu_Hlt2TopoMu4BodyBBDTDecision_TIS, &b_mu_Hlt2TopoMu4BodyBBDTDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TopoMu4BodyBBDTDecision_TOS", &mu_Hlt2TopoMu4BodyBBDTDecision_TOS, &b_mu_Hlt2TopoMu4BodyBBDTDecision_TOS);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_Dec", &mu_Hlt2TransparentDecision_Dec, &b_mu_Hlt2TransparentDecision_Dec);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_TIS", &mu_Hlt2TransparentDecision_TIS, &b_mu_Hlt2TransparentDecision_TIS);
   fChain->SetBranchAddress("mu_Hlt2TransparentDecision_TOS", &mu_Hlt2TransparentDecision_TOS, &b_mu_Hlt2TransparentDecision_TOS);
   fChain->SetBranchAddress("Xc_MINIP", &Xc_MINIP, &b_Xc_MINIP);
   fChain->SetBranchAddress("Xc_MINIPCHI2", &Xc_MINIPCHI2, &b_Xc_MINIPCHI2);
   fChain->SetBranchAddress("Xc_MINIPNEXTBEST", &Xc_MINIPNEXTBEST, &b_Xc_MINIPNEXTBEST);
   fChain->SetBranchAddress("Xc_MINIPCHI2NEXTBEST", &Xc_MINIPCHI2NEXTBEST, &b_Xc_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("Xc_ENDVERTEX_X", &Xc_ENDVERTEX_X, &b_Xc_ENDVERTEX_X);
   fChain->SetBranchAddress("Xc_ENDVERTEX_Y", &Xc_ENDVERTEX_Y, &b_Xc_ENDVERTEX_Y);
   fChain->SetBranchAddress("Xc_ENDVERTEX_Z", &Xc_ENDVERTEX_Z, &b_Xc_ENDVERTEX_Z);
   fChain->SetBranchAddress("Xc_ENDVERTEX_XERR", &Xc_ENDVERTEX_XERR, &b_Xc_ENDVERTEX_XERR);
   fChain->SetBranchAddress("Xc_ENDVERTEX_YERR", &Xc_ENDVERTEX_YERR, &b_Xc_ENDVERTEX_YERR);
   fChain->SetBranchAddress("Xc_ENDVERTEX_ZERR", &Xc_ENDVERTEX_ZERR, &b_Xc_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("Xc_ENDVERTEX_CHI2", &Xc_ENDVERTEX_CHI2, &b_Xc_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("Xc_ENDVERTEX_NDOF", &Xc_ENDVERTEX_NDOF, &b_Xc_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("Xc_ENDVERTEX_COV_", Xc_ENDVERTEX_COV_, &b_Xc_ENDVERTEX_COV_);
   fChain->SetBranchAddress("Xc_OWNPV_X", &Xc_OWNPV_X, &b_Xc_OWNPV_X);
   fChain->SetBranchAddress("Xc_OWNPV_Y", &Xc_OWNPV_Y, &b_Xc_OWNPV_Y);
   fChain->SetBranchAddress("Xc_OWNPV_Z", &Xc_OWNPV_Z, &b_Xc_OWNPV_Z);
   fChain->SetBranchAddress("Xc_OWNPV_XERR", &Xc_OWNPV_XERR, &b_Xc_OWNPV_XERR);
   fChain->SetBranchAddress("Xc_OWNPV_YERR", &Xc_OWNPV_YERR, &b_Xc_OWNPV_YERR);
   fChain->SetBranchAddress("Xc_OWNPV_ZERR", &Xc_OWNPV_ZERR, &b_Xc_OWNPV_ZERR);
   fChain->SetBranchAddress("Xc_OWNPV_CHI2", &Xc_OWNPV_CHI2, &b_Xc_OWNPV_CHI2);
   fChain->SetBranchAddress("Xc_OWNPV_NDOF", &Xc_OWNPV_NDOF, &b_Xc_OWNPV_NDOF);
   fChain->SetBranchAddress("Xc_OWNPV_COV_", Xc_OWNPV_COV_, &b_Xc_OWNPV_COV_);
   fChain->SetBranchAddress("Xc_IP_OWNPV", &Xc_IP_OWNPV, &b_Xc_IP_OWNPV);
   fChain->SetBranchAddress("Xc_IPCHI2_OWNPV", &Xc_IPCHI2_OWNPV, &b_Xc_IPCHI2_OWNPV);
   fChain->SetBranchAddress("Xc_FD_OWNPV", &Xc_FD_OWNPV, &b_Xc_FD_OWNPV);
   fChain->SetBranchAddress("Xc_FDCHI2_OWNPV", &Xc_FDCHI2_OWNPV, &b_Xc_FDCHI2_OWNPV);
   fChain->SetBranchAddress("Xc_DIRA_OWNPV", &Xc_DIRA_OWNPV, &b_Xc_DIRA_OWNPV);
   fChain->SetBranchAddress("Xc_TOPPV_X", &Xc_TOPPV_X, &b_Xc_TOPPV_X);
   fChain->SetBranchAddress("Xc_TOPPV_Y", &Xc_TOPPV_Y, &b_Xc_TOPPV_Y);
   fChain->SetBranchAddress("Xc_TOPPV_Z", &Xc_TOPPV_Z, &b_Xc_TOPPV_Z);
   fChain->SetBranchAddress("Xc_TOPPV_XERR", &Xc_TOPPV_XERR, &b_Xc_TOPPV_XERR);
   fChain->SetBranchAddress("Xc_TOPPV_YERR", &Xc_TOPPV_YERR, &b_Xc_TOPPV_YERR);
   fChain->SetBranchAddress("Xc_TOPPV_ZERR", &Xc_TOPPV_ZERR, &b_Xc_TOPPV_ZERR);
   fChain->SetBranchAddress("Xc_TOPPV_CHI2", &Xc_TOPPV_CHI2, &b_Xc_TOPPV_CHI2);
   fChain->SetBranchAddress("Xc_TOPPV_NDOF", &Xc_TOPPV_NDOF, &b_Xc_TOPPV_NDOF);
   fChain->SetBranchAddress("Xc_TOPPV_COV_", Xc_TOPPV_COV_, &b_Xc_TOPPV_COV_);
   fChain->SetBranchAddress("Xc_IP_TOPPV", &Xc_IP_TOPPV, &b_Xc_IP_TOPPV);
   fChain->SetBranchAddress("Xc_IPCHI2_TOPPV", &Xc_IPCHI2_TOPPV, &b_Xc_IPCHI2_TOPPV);
   fChain->SetBranchAddress("Xc_FD_TOPPV", &Xc_FD_TOPPV, &b_Xc_FD_TOPPV);
   fChain->SetBranchAddress("Xc_FDCHI2_TOPPV", &Xc_FDCHI2_TOPPV, &b_Xc_FDCHI2_TOPPV);
   fChain->SetBranchAddress("Xc_DIRA_TOPPV", &Xc_DIRA_TOPPV, &b_Xc_DIRA_TOPPV);
   fChain->SetBranchAddress("Xc_ORIVX_X", &Xc_ORIVX_X, &b_Xc_ORIVX_X);
   fChain->SetBranchAddress("Xc_ORIVX_Y", &Xc_ORIVX_Y, &b_Xc_ORIVX_Y);
   fChain->SetBranchAddress("Xc_ORIVX_Z", &Xc_ORIVX_Z, &b_Xc_ORIVX_Z);
   fChain->SetBranchAddress("Xc_ORIVX_XERR", &Xc_ORIVX_XERR, &b_Xc_ORIVX_XERR);
   fChain->SetBranchAddress("Xc_ORIVX_YERR", &Xc_ORIVX_YERR, &b_Xc_ORIVX_YERR);
   fChain->SetBranchAddress("Xc_ORIVX_ZERR", &Xc_ORIVX_ZERR, &b_Xc_ORIVX_ZERR);
   fChain->SetBranchAddress("Xc_ORIVX_CHI2", &Xc_ORIVX_CHI2, &b_Xc_ORIVX_CHI2);
   fChain->SetBranchAddress("Xc_ORIVX_NDOF", &Xc_ORIVX_NDOF, &b_Xc_ORIVX_NDOF);
   fChain->SetBranchAddress("Xc_ORIVX_COV_", Xc_ORIVX_COV_, &b_Xc_ORIVX_COV_);
   fChain->SetBranchAddress("Xc_IP_ORIVX", &Xc_IP_ORIVX, &b_Xc_IP_ORIVX);
   fChain->SetBranchAddress("Xc_IPCHI2_ORIVX", &Xc_IPCHI2_ORIVX, &b_Xc_IPCHI2_ORIVX);
   fChain->SetBranchAddress("Xc_FD_ORIVX", &Xc_FD_ORIVX, &b_Xc_FD_ORIVX);
   fChain->SetBranchAddress("Xc_FDCHI2_ORIVX", &Xc_FDCHI2_ORIVX, &b_Xc_FDCHI2_ORIVX);
   fChain->SetBranchAddress("Xc_DIRA_ORIVX", &Xc_DIRA_ORIVX, &b_Xc_DIRA_ORIVX);
   fChain->SetBranchAddress("Xc_P", &Xc_P, &b_Xc_P);
   fChain->SetBranchAddress("Xc_PT", &Xc_PT, &b_Xc_PT);
   fChain->SetBranchAddress("Xc_PE", &Xc_PE, &b_Xc_PE);
   fChain->SetBranchAddress("Xc_PX", &Xc_PX, &b_Xc_PX);
   fChain->SetBranchAddress("Xc_PY", &Xc_PY, &b_Xc_PY);
   fChain->SetBranchAddress("Xc_PZ", &Xc_PZ, &b_Xc_PZ);
   fChain->SetBranchAddress("Xc_MM", &Xc_MM, &b_Xc_MM);
   fChain->SetBranchAddress("Xc_MMERR", &Xc_MMERR, &b_Xc_MMERR);
   fChain->SetBranchAddress("Xc_M", &Xc_M, &b_Xc_M);
   fChain->SetBranchAddress("Xc_ID", &Xc_ID, &b_Xc_ID);
   fChain->SetBranchAddress("Xc_TAU", &Xc_TAU, &b_Xc_TAU);
   fChain->SetBranchAddress("Xc_TAUERR", &Xc_TAUERR, &b_Xc_TAUERR);
   fChain->SetBranchAddress("Xc_TAUCHI2", &Xc_TAUCHI2, &b_Xc_TAUCHI2);
   fChain->SetBranchAddress("pi_MINIP", &pi_MINIP, &b_pi_MINIP);
   fChain->SetBranchAddress("pi_MINIPCHI2", &pi_MINIPCHI2, &b_pi_MINIPCHI2);
   fChain->SetBranchAddress("pi_MINIPNEXTBEST", &pi_MINIPNEXTBEST, &b_pi_MINIPNEXTBEST);
   fChain->SetBranchAddress("pi_MINIPCHI2NEXTBEST", &pi_MINIPCHI2NEXTBEST, &b_pi_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("pi_OWNPV_X", &pi_OWNPV_X, &b_pi_OWNPV_X);
   fChain->SetBranchAddress("pi_OWNPV_Y", &pi_OWNPV_Y, &b_pi_OWNPV_Y);
   fChain->SetBranchAddress("pi_OWNPV_Z", &pi_OWNPV_Z, &b_pi_OWNPV_Z);
   fChain->SetBranchAddress("pi_OWNPV_XERR", &pi_OWNPV_XERR, &b_pi_OWNPV_XERR);
   fChain->SetBranchAddress("pi_OWNPV_YERR", &pi_OWNPV_YERR, &b_pi_OWNPV_YERR);
   fChain->SetBranchAddress("pi_OWNPV_ZERR", &pi_OWNPV_ZERR, &b_pi_OWNPV_ZERR);
   fChain->SetBranchAddress("pi_OWNPV_CHI2", &pi_OWNPV_CHI2, &b_pi_OWNPV_CHI2);
   fChain->SetBranchAddress("pi_OWNPV_NDOF", &pi_OWNPV_NDOF, &b_pi_OWNPV_NDOF);
   fChain->SetBranchAddress("pi_OWNPV_COV_", pi_OWNPV_COV_, &b_pi_OWNPV_COV_);
   fChain->SetBranchAddress("pi_IP_OWNPV", &pi_IP_OWNPV, &b_pi_IP_OWNPV);
   fChain->SetBranchAddress("pi_IPCHI2_OWNPV", &pi_IPCHI2_OWNPV, &b_pi_IPCHI2_OWNPV);
   fChain->SetBranchAddress("pi_TOPPV_X", &pi_TOPPV_X, &b_pi_TOPPV_X);
   fChain->SetBranchAddress("pi_TOPPV_Y", &pi_TOPPV_Y, &b_pi_TOPPV_Y);
   fChain->SetBranchAddress("pi_TOPPV_Z", &pi_TOPPV_Z, &b_pi_TOPPV_Z);
   fChain->SetBranchAddress("pi_TOPPV_XERR", &pi_TOPPV_XERR, &b_pi_TOPPV_XERR);
   fChain->SetBranchAddress("pi_TOPPV_YERR", &pi_TOPPV_YERR, &b_pi_TOPPV_YERR);
   fChain->SetBranchAddress("pi_TOPPV_ZERR", &pi_TOPPV_ZERR, &b_pi_TOPPV_ZERR);
   fChain->SetBranchAddress("pi_TOPPV_CHI2", &pi_TOPPV_CHI2, &b_pi_TOPPV_CHI2);
   fChain->SetBranchAddress("pi_TOPPV_NDOF", &pi_TOPPV_NDOF, &b_pi_TOPPV_NDOF);
   fChain->SetBranchAddress("pi_TOPPV_COV_", pi_TOPPV_COV_, &b_pi_TOPPV_COV_);
   fChain->SetBranchAddress("pi_IP_TOPPV", &pi_IP_TOPPV, &b_pi_IP_TOPPV);
   fChain->SetBranchAddress("pi_IPCHI2_TOPPV", &pi_IPCHI2_TOPPV, &b_pi_IPCHI2_TOPPV);
   fChain->SetBranchAddress("pi_ORIVX_X", &pi_ORIVX_X, &b_pi_ORIVX_X);
   fChain->SetBranchAddress("pi_ORIVX_Y", &pi_ORIVX_Y, &b_pi_ORIVX_Y);
   fChain->SetBranchAddress("pi_ORIVX_Z", &pi_ORIVX_Z, &b_pi_ORIVX_Z);
   fChain->SetBranchAddress("pi_ORIVX_XERR", &pi_ORIVX_XERR, &b_pi_ORIVX_XERR);
   fChain->SetBranchAddress("pi_ORIVX_YERR", &pi_ORIVX_YERR, &b_pi_ORIVX_YERR);
   fChain->SetBranchAddress("pi_ORIVX_ZERR", &pi_ORIVX_ZERR, &b_pi_ORIVX_ZERR);
   fChain->SetBranchAddress("pi_ORIVX_CHI2", &pi_ORIVX_CHI2, &b_pi_ORIVX_CHI2);
   fChain->SetBranchAddress("pi_ORIVX_NDOF", &pi_ORIVX_NDOF, &b_pi_ORIVX_NDOF);
   fChain->SetBranchAddress("pi_ORIVX_COV_", pi_ORIVX_COV_, &b_pi_ORIVX_COV_);
   fChain->SetBranchAddress("pi_IP_ORIVX", &pi_IP_ORIVX, &b_pi_IP_ORIVX);
   fChain->SetBranchAddress("pi_IPCHI2_ORIVX", &pi_IPCHI2_ORIVX, &b_pi_IPCHI2_ORIVX);
   fChain->SetBranchAddress("pi_P", &pi_P, &b_pi_P);
   fChain->SetBranchAddress("pi_PT", &pi_PT, &b_pi_PT);
   fChain->SetBranchAddress("pi_PE", &pi_PE, &b_pi_PE);
   fChain->SetBranchAddress("pi_PX", &pi_PX, &b_pi_PX);
   fChain->SetBranchAddress("pi_PY", &pi_PY, &b_pi_PY);
   fChain->SetBranchAddress("pi_PZ", &pi_PZ, &b_pi_PZ);
   fChain->SetBranchAddress("pi_M", &pi_M, &b_pi_M);
   fChain->SetBranchAddress("pi_ID", &pi_ID, &b_pi_ID);
   fChain->SetBranchAddress("pi_PIDe", &pi_PIDe, &b_pi_PIDe);
   fChain->SetBranchAddress("pi_PIDmu", &pi_PIDmu, &b_pi_PIDmu);
   fChain->SetBranchAddress("pi_PIDK", &pi_PIDK, &b_pi_PIDK);
   fChain->SetBranchAddress("pi_PIDp", &pi_PIDp, &b_pi_PIDp);
   fChain->SetBranchAddress("pi_ProbNNe", &pi_ProbNNe, &b_pi_ProbNNe);
   fChain->SetBranchAddress("pi_ProbNNk", &pi_ProbNNk, &b_pi_ProbNNk);
   fChain->SetBranchAddress("pi_ProbNNp", &pi_ProbNNp, &b_pi_ProbNNp);
   fChain->SetBranchAddress("pi_ProbNNpi", &pi_ProbNNpi, &b_pi_ProbNNpi);
   fChain->SetBranchAddress("pi_ProbNNmu", &pi_ProbNNmu, &b_pi_ProbNNmu);
   fChain->SetBranchAddress("pi_ProbNNghost", &pi_ProbNNghost, &b_pi_ProbNNghost);
   fChain->SetBranchAddress("pi_hasMuon", &pi_hasMuon, &b_pi_hasMuon);
   fChain->SetBranchAddress("pi_isMuon", &pi_isMuon, &b_pi_isMuon);
   fChain->SetBranchAddress("pi_hasRich", &pi_hasRich, &b_pi_hasRich);
   fChain->SetBranchAddress("pi_hasCalo", &pi_hasCalo, &b_pi_hasCalo);
   fChain->SetBranchAddress("pi_TRACK_Type", &pi_TRACK_Type, &b_pi_TRACK_Type);
   fChain->SetBranchAddress("pi_TRACK_Key", &pi_TRACK_Key, &b_pi_TRACK_Key);
   fChain->SetBranchAddress("pi_TRACK_CHI2NDOF", &pi_TRACK_CHI2NDOF, &b_pi_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("pi_TRACK_PCHI2", &pi_TRACK_PCHI2, &b_pi_TRACK_PCHI2);
   fChain->SetBranchAddress("pi_TRACK_MatchCHI2", &pi_TRACK_MatchCHI2, &b_pi_TRACK_MatchCHI2);
   fChain->SetBranchAddress("pi_TRACK_GhostProb", &pi_TRACK_GhostProb, &b_pi_TRACK_GhostProb);
   fChain->SetBranchAddress("pi_TRACK_CloneDist", &pi_TRACK_CloneDist, &b_pi_TRACK_CloneDist);
   fChain->SetBranchAddress("pi_TRACK_Likelihood", &pi_TRACK_Likelihood, &b_pi_TRACK_Likelihood);
   fChain->SetBranchAddress("K_MINIP", &K_MINIP, &b_K_MINIP);
   fChain->SetBranchAddress("K_MINIPCHI2", &K_MINIPCHI2, &b_K_MINIPCHI2);
   fChain->SetBranchAddress("K_MINIPNEXTBEST", &K_MINIPNEXTBEST, &b_K_MINIPNEXTBEST);
   fChain->SetBranchAddress("K_MINIPCHI2NEXTBEST", &K_MINIPCHI2NEXTBEST, &b_K_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("K_OWNPV_X", &K_OWNPV_X, &b_K_OWNPV_X);
   fChain->SetBranchAddress("K_OWNPV_Y", &K_OWNPV_Y, &b_K_OWNPV_Y);
   fChain->SetBranchAddress("K_OWNPV_Z", &K_OWNPV_Z, &b_K_OWNPV_Z);
   fChain->SetBranchAddress("K_OWNPV_XERR", &K_OWNPV_XERR, &b_K_OWNPV_XERR);
   fChain->SetBranchAddress("K_OWNPV_YERR", &K_OWNPV_YERR, &b_K_OWNPV_YERR);
   fChain->SetBranchAddress("K_OWNPV_ZERR", &K_OWNPV_ZERR, &b_K_OWNPV_ZERR);
   fChain->SetBranchAddress("K_OWNPV_CHI2", &K_OWNPV_CHI2, &b_K_OWNPV_CHI2);
   fChain->SetBranchAddress("K_OWNPV_NDOF", &K_OWNPV_NDOF, &b_K_OWNPV_NDOF);
   fChain->SetBranchAddress("K_OWNPV_COV_", K_OWNPV_COV_, &b_K_OWNPV_COV_);
   fChain->SetBranchAddress("K_IP_OWNPV", &K_IP_OWNPV, &b_K_IP_OWNPV);
   fChain->SetBranchAddress("K_IPCHI2_OWNPV", &K_IPCHI2_OWNPV, &b_K_IPCHI2_OWNPV);
   fChain->SetBranchAddress("K_TOPPV_X", &K_TOPPV_X, &b_K_TOPPV_X);
   fChain->SetBranchAddress("K_TOPPV_Y", &K_TOPPV_Y, &b_K_TOPPV_Y);
   fChain->SetBranchAddress("K_TOPPV_Z", &K_TOPPV_Z, &b_K_TOPPV_Z);
   fChain->SetBranchAddress("K_TOPPV_XERR", &K_TOPPV_XERR, &b_K_TOPPV_XERR);
   fChain->SetBranchAddress("K_TOPPV_YERR", &K_TOPPV_YERR, &b_K_TOPPV_YERR);
   fChain->SetBranchAddress("K_TOPPV_ZERR", &K_TOPPV_ZERR, &b_K_TOPPV_ZERR);
   fChain->SetBranchAddress("K_TOPPV_CHI2", &K_TOPPV_CHI2, &b_K_TOPPV_CHI2);
   fChain->SetBranchAddress("K_TOPPV_NDOF", &K_TOPPV_NDOF, &b_K_TOPPV_NDOF);
   fChain->SetBranchAddress("K_TOPPV_COV_", K_TOPPV_COV_, &b_K_TOPPV_COV_);
   fChain->SetBranchAddress("K_IP_TOPPV", &K_IP_TOPPV, &b_K_IP_TOPPV);
   fChain->SetBranchAddress("K_IPCHI2_TOPPV", &K_IPCHI2_TOPPV, &b_K_IPCHI2_TOPPV);
   fChain->SetBranchAddress("K_ORIVX_X", &K_ORIVX_X, &b_K_ORIVX_X);
   fChain->SetBranchAddress("K_ORIVX_Y", &K_ORIVX_Y, &b_K_ORIVX_Y);
   fChain->SetBranchAddress("K_ORIVX_Z", &K_ORIVX_Z, &b_K_ORIVX_Z);
   fChain->SetBranchAddress("K_ORIVX_XERR", &K_ORIVX_XERR, &b_K_ORIVX_XERR);
   fChain->SetBranchAddress("K_ORIVX_YERR", &K_ORIVX_YERR, &b_K_ORIVX_YERR);
   fChain->SetBranchAddress("K_ORIVX_ZERR", &K_ORIVX_ZERR, &b_K_ORIVX_ZERR);
   fChain->SetBranchAddress("K_ORIVX_CHI2", &K_ORIVX_CHI2, &b_K_ORIVX_CHI2);
   fChain->SetBranchAddress("K_ORIVX_NDOF", &K_ORIVX_NDOF, &b_K_ORIVX_NDOF);
   fChain->SetBranchAddress("K_ORIVX_COV_", K_ORIVX_COV_, &b_K_ORIVX_COV_);
   fChain->SetBranchAddress("K_IP_ORIVX", &K_IP_ORIVX, &b_K_IP_ORIVX);
   fChain->SetBranchAddress("K_IPCHI2_ORIVX", &K_IPCHI2_ORIVX, &b_K_IPCHI2_ORIVX);
   fChain->SetBranchAddress("K_P", &K_P, &b_K_P);
   fChain->SetBranchAddress("K_PT", &K_PT, &b_K_PT);
   fChain->SetBranchAddress("K_PE", &K_PE, &b_K_PE);
   fChain->SetBranchAddress("K_PX", &K_PX, &b_K_PX);
   fChain->SetBranchAddress("K_PY", &K_PY, &b_K_PY);
   fChain->SetBranchAddress("K_PZ", &K_PZ, &b_K_PZ);
   fChain->SetBranchAddress("K_M", &K_M, &b_K_M);
   fChain->SetBranchAddress("K_ID", &K_ID, &b_K_ID);
   fChain->SetBranchAddress("K_PIDe", &K_PIDe, &b_K_PIDe);
   fChain->SetBranchAddress("K_PIDmu", &K_PIDmu, &b_K_PIDmu);
   fChain->SetBranchAddress("K_PIDK", &K_PIDK, &b_K_PIDK);
   fChain->SetBranchAddress("K_PIDp", &K_PIDp, &b_K_PIDp);
   fChain->SetBranchAddress("K_ProbNNe", &K_ProbNNe, &b_K_ProbNNe);
   fChain->SetBranchAddress("K_ProbNNk", &K_ProbNNk, &b_K_ProbNNk);
   fChain->SetBranchAddress("K_ProbNNp", &K_ProbNNp, &b_K_ProbNNp);
   fChain->SetBranchAddress("K_ProbNNpi", &K_ProbNNpi, &b_K_ProbNNpi);
   fChain->SetBranchAddress("K_ProbNNmu", &K_ProbNNmu, &b_K_ProbNNmu);
   fChain->SetBranchAddress("K_ProbNNghost", &K_ProbNNghost, &b_K_ProbNNghost);
   fChain->SetBranchAddress("K_hasMuon", &K_hasMuon, &b_K_hasMuon);
   fChain->SetBranchAddress("K_isMuon", &K_isMuon, &b_K_isMuon);
   fChain->SetBranchAddress("K_hasRich", &K_hasRich, &b_K_hasRich);
   fChain->SetBranchAddress("K_hasCalo", &K_hasCalo, &b_K_hasCalo);
   fChain->SetBranchAddress("K_TRACK_Type", &K_TRACK_Type, &b_K_TRACK_Type);
   fChain->SetBranchAddress("K_TRACK_Key", &K_TRACK_Key, &b_K_TRACK_Key);
   fChain->SetBranchAddress("K_TRACK_CHI2NDOF", &K_TRACK_CHI2NDOF, &b_K_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("K_TRACK_PCHI2", &K_TRACK_PCHI2, &b_K_TRACK_PCHI2);
   fChain->SetBranchAddress("K_TRACK_MatchCHI2", &K_TRACK_MatchCHI2, &b_K_TRACK_MatchCHI2);
   fChain->SetBranchAddress("K_TRACK_GhostProb", &K_TRACK_GhostProb, &b_K_TRACK_GhostProb);
   fChain->SetBranchAddress("K_TRACK_CloneDist", &K_TRACK_CloneDist, &b_K_TRACK_CloneDist);
   fChain->SetBranchAddress("K_TRACK_Likelihood", &K_TRACK_Likelihood, &b_K_TRACK_Likelihood);
   fChain->SetBranchAddress("p_MINIP", &p_MINIP, &b_p_MINIP);
   fChain->SetBranchAddress("p_MINIPCHI2", &p_MINIPCHI2, &b_p_MINIPCHI2);
   fChain->SetBranchAddress("p_MINIPNEXTBEST", &p_MINIPNEXTBEST, &b_p_MINIPNEXTBEST);
   fChain->SetBranchAddress("p_MINIPCHI2NEXTBEST", &p_MINIPCHI2NEXTBEST, &b_p_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("p_OWNPV_X", &p_OWNPV_X, &b_p_OWNPV_X);
   fChain->SetBranchAddress("p_OWNPV_Y", &p_OWNPV_Y, &b_p_OWNPV_Y);
   fChain->SetBranchAddress("p_OWNPV_Z", &p_OWNPV_Z, &b_p_OWNPV_Z);
   fChain->SetBranchAddress("p_OWNPV_XERR", &p_OWNPV_XERR, &b_p_OWNPV_XERR);
   fChain->SetBranchAddress("p_OWNPV_YERR", &p_OWNPV_YERR, &b_p_OWNPV_YERR);
   fChain->SetBranchAddress("p_OWNPV_ZERR", &p_OWNPV_ZERR, &b_p_OWNPV_ZERR);
   fChain->SetBranchAddress("p_OWNPV_CHI2", &p_OWNPV_CHI2, &b_p_OWNPV_CHI2);
   fChain->SetBranchAddress("p_OWNPV_NDOF", &p_OWNPV_NDOF, &b_p_OWNPV_NDOF);
   fChain->SetBranchAddress("p_OWNPV_COV_", p_OWNPV_COV_, &b_p_OWNPV_COV_);
   fChain->SetBranchAddress("p_IP_OWNPV", &p_IP_OWNPV, &b_p_IP_OWNPV);
   fChain->SetBranchAddress("p_IPCHI2_OWNPV", &p_IPCHI2_OWNPV, &b_p_IPCHI2_OWNPV);
   fChain->SetBranchAddress("p_TOPPV_X", &p_TOPPV_X, &b_p_TOPPV_X);
   fChain->SetBranchAddress("p_TOPPV_Y", &p_TOPPV_Y, &b_p_TOPPV_Y);
   fChain->SetBranchAddress("p_TOPPV_Z", &p_TOPPV_Z, &b_p_TOPPV_Z);
   fChain->SetBranchAddress("p_TOPPV_XERR", &p_TOPPV_XERR, &b_p_TOPPV_XERR);
   fChain->SetBranchAddress("p_TOPPV_YERR", &p_TOPPV_YERR, &b_p_TOPPV_YERR);
   fChain->SetBranchAddress("p_TOPPV_ZERR", &p_TOPPV_ZERR, &b_p_TOPPV_ZERR);
   fChain->SetBranchAddress("p_TOPPV_CHI2", &p_TOPPV_CHI2, &b_p_TOPPV_CHI2);
   fChain->SetBranchAddress("p_TOPPV_NDOF", &p_TOPPV_NDOF, &b_p_TOPPV_NDOF);
   fChain->SetBranchAddress("p_TOPPV_COV_", p_TOPPV_COV_, &b_p_TOPPV_COV_);
   fChain->SetBranchAddress("p_IP_TOPPV", &p_IP_TOPPV, &b_p_IP_TOPPV);
   fChain->SetBranchAddress("p_IPCHI2_TOPPV", &p_IPCHI2_TOPPV, &b_p_IPCHI2_TOPPV);
   fChain->SetBranchAddress("p_ORIVX_X", &p_ORIVX_X, &b_p_ORIVX_X);
   fChain->SetBranchAddress("p_ORIVX_Y", &p_ORIVX_Y, &b_p_ORIVX_Y);
   fChain->SetBranchAddress("p_ORIVX_Z", &p_ORIVX_Z, &b_p_ORIVX_Z);
   fChain->SetBranchAddress("p_ORIVX_XERR", &p_ORIVX_XERR, &b_p_ORIVX_XERR);
   fChain->SetBranchAddress("p_ORIVX_YERR", &p_ORIVX_YERR, &b_p_ORIVX_YERR);
   fChain->SetBranchAddress("p_ORIVX_ZERR", &p_ORIVX_ZERR, &b_p_ORIVX_ZERR);
   fChain->SetBranchAddress("p_ORIVX_CHI2", &p_ORIVX_CHI2, &b_p_ORIVX_CHI2);
   fChain->SetBranchAddress("p_ORIVX_NDOF", &p_ORIVX_NDOF, &b_p_ORIVX_NDOF);
   fChain->SetBranchAddress("p_ORIVX_COV_", p_ORIVX_COV_, &b_p_ORIVX_COV_);
   fChain->SetBranchAddress("p_IP_ORIVX", &p_IP_ORIVX, &b_p_IP_ORIVX);
   fChain->SetBranchAddress("p_IPCHI2_ORIVX", &p_IPCHI2_ORIVX, &b_p_IPCHI2_ORIVX);
   fChain->SetBranchAddress("p_P", &p_P, &b_p_P);
   fChain->SetBranchAddress("p_PT", &p_PT, &b_p_PT);
   fChain->SetBranchAddress("p_PE", &p_PE, &b_p_PE);
   fChain->SetBranchAddress("p_PX", &p_PX, &b_p_PX);
   fChain->SetBranchAddress("p_PY", &p_PY, &b_p_PY);
   fChain->SetBranchAddress("p_PZ", &p_PZ, &b_p_PZ);
   fChain->SetBranchAddress("p_M", &p_M, &b_p_M);
   fChain->SetBranchAddress("p_ID", &p_ID, &b_p_ID);
   fChain->SetBranchAddress("p_PIDe", &p_PIDe, &b_p_PIDe);
   fChain->SetBranchAddress("p_PIDmu", &p_PIDmu, &b_p_PIDmu);
   fChain->SetBranchAddress("p_PIDK", &p_PIDK, &b_p_PIDK);
   fChain->SetBranchAddress("p_PIDp", &p_PIDp, &b_p_PIDp);
   fChain->SetBranchAddress("p_ProbNNe", &p_ProbNNe, &b_p_ProbNNe);
   fChain->SetBranchAddress("p_ProbNNk", &p_ProbNNk, &b_p_ProbNNk);
   fChain->SetBranchAddress("p_ProbNNp", &p_ProbNNp, &b_p_ProbNNp);
   fChain->SetBranchAddress("p_ProbNNpi", &p_ProbNNpi, &b_p_ProbNNpi);
   fChain->SetBranchAddress("p_ProbNNmu", &p_ProbNNmu, &b_p_ProbNNmu);
   fChain->SetBranchAddress("p_ProbNNghost", &p_ProbNNghost, &b_p_ProbNNghost);
   fChain->SetBranchAddress("p_hasMuon", &p_hasMuon, &b_p_hasMuon);
   fChain->SetBranchAddress("p_isMuon", &p_isMuon, &b_p_isMuon);
   fChain->SetBranchAddress("p_hasRich", &p_hasRich, &b_p_hasRich);
   fChain->SetBranchAddress("p_hasCalo", &p_hasCalo, &b_p_hasCalo);
   fChain->SetBranchAddress("p_TRACK_Type", &p_TRACK_Type, &b_p_TRACK_Type);
   fChain->SetBranchAddress("p_TRACK_Key", &p_TRACK_Key, &b_p_TRACK_Key);
   fChain->SetBranchAddress("p_TRACK_CHI2NDOF", &p_TRACK_CHI2NDOF, &b_p_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("p_TRACK_PCHI2", &p_TRACK_PCHI2, &b_p_TRACK_PCHI2);
   fChain->SetBranchAddress("p_TRACK_MatchCHI2", &p_TRACK_MatchCHI2, &b_p_TRACK_MatchCHI2);
   fChain->SetBranchAddress("p_TRACK_GhostProb", &p_TRACK_GhostProb, &b_p_TRACK_GhostProb);
   fChain->SetBranchAddress("p_TRACK_CloneDist", &p_TRACK_CloneDist, &b_p_TRACK_CloneDist);
   fChain->SetBranchAddress("p_TRACK_Likelihood", &p_TRACK_Likelihood, &b_p_TRACK_Likelihood);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("nLong", &nLong, &b_nLong);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLT1TCK", &HLT1TCK, &b_HLT1TCK);
   fChain->SetBranchAddress("HLT2TCK", &HLT2TCK, &b_HLT2TCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   Notify();
}

Bool_t Xic::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Xic::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Xic::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Xic_cxx
