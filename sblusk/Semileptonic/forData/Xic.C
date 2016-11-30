#define Xic_cxx
#include "Xic.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>

void Xic::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L Xic.C
//      Root > Xic t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   TFile *fout = new TFile("out.root","RECREATE");

   TH1F *h1 = new TH1F("h1","Mass",50,2420,2520);
   TH1F *h2 = new TH1F("h2","Corr Mass",1000,0,8000);
   TH1F *h3 = new TH1F("h3","Mass",50,2420,2520);
   TH1F *h4 = new TH1F("h4","Mass",50,2420,2520);
   
   cout << "Number of entries = " << nentries << endl;
   
   //nentries = 200000;
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      bool keep = p_ProbNNp>0.3&&K_ProbNNk>0.15&&pi_ProbNNpi>0.15&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<10;
      /*
      keep = keep && (abs(sqrt((sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2)+K_PE)**2-((p_PX+K_PX)**2+(p_PY+K_PY)**2+(p_PZ+K_PZ)**2))-1020)>8 || p_PIDp-p_PIDK>8);
      keep = keep && (abs(sqrt((K_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2))**2-((K_PX+p_PX+pi_PX)**2+(K_PY+p_PY+pi_PY)**2+(K_PZ+p_PZ+pi_PZ)**2))-1968)>15 || p_PIDp-p_PIDK>7);
      keep = keep && (abs(sqrt((K_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2))**2-((K_PX+p_PX+pi_PX)**2+(K_PY+p_PY+pi_PY)**2+(K_PZ+p_PZ+pi_PZ)**2))-1869)>15 || p_PIDp-p_PIDK>5);
      keep = keep && sqrt((K_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((K_PX+p_PX+pi_PX)**2+(K_PY+p_PY+pi_PY)**2+(K_PZ+p_PZ+pi_PZ)**2))-sqrt((K_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((K_PX+p_PX)**2+(K_PY+p_PY)**2+(K_PZ+p_PZ)**2))>152 || (p_PIDp>25)
      keep = keep && abs(sqrt((K_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((K_PX+p_PX+pi_PX)**2+(K_PY+p_PY+pi_PY)**2+(K_PZ+p_PZ+pi_PZ)**2))-1869)>20 || (p_PIDp>20);
      */

      if(!keep) continue;
      h1->Fill(Xc_M);
      
      
      // Compute corrected mass
      //double Xb_ETA = -log(tan(0.5*Xb_PT/Xb_PZ));

      TVector3 dir;
      TVector3 mom;
      //mom.SetPtEtaPhi(Xb_PT,Xb_ETA,Xb_PHI);
      dir.SetXYZ(Xb_ENDVERTEX_X-Xb_OWNPV_X,Xb_ENDVERTEX_Y-Xb_OWNPV_Y,Xb_ENDVERTEX_Z-Xb_OWNPV_Z);
      mom.SetXYZ(Xb_PX,Xb_PY,Xb_PZ);

      double dmag2 = dir.Mag2();
      double ptprime = 0;
      if ( 0 == dmag2 ) ptprime = mom.Mag();
      else ptprime = (mom - dir * ( mom.Dot( dir ) / dmag2 )).Mag() ;
      double Xb_CorrM = sqrt(Xb_M*Xb_M + ptprime*ptprime) + ptprime;
      h2->Fill(Xb_CorrM);
      if(Xb_CorrM>4500&Xb_CorrM<7200) {
        h3->Fill(Xc_M);
      }else{
        h4->Fill(Xc_M);
      }
      
      
      // if (Cut(ientry) < 0) continue;
   }

   h1->SetMinimum(0);
   h3->SetLineColor(2);
   h4->SetLineColor(4);
   

   TCanvas *c = new TCanvas("c","plots",1000,500);
   c->Divide(2,1);
   c->cd(1);
   h1->Draw();
   h3->Draw("same");
   h4->Draw("same");
   c->cd(2);
   h2->Draw();
   
}
