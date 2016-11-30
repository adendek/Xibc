#include "doComb.C"

using namespace std;
using namespace RooFit;

TString lt;


TCanvas* makeRooPlot(RooAbsPdf* pdf, RooAbsData* rdh, RooRealVar *mvar, int mode, RooRealVar* nS, TH1F *hh,
                     TString tag="def",double mlow=2420, double mhi=2520, int nbin=50){
  
  TLatex *myLatex = new TLatex();
  myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
  double xt = 0.6;
  int bw = (mhi-mlow)/nbin;

  tag = tag.ReplaceAll("#","");
  tag = tag.ReplaceAll("^{0}","z");
  tag = tag.ReplaceAll("^{+}","");
  tag = tag.ReplaceAll("^{-}","");
  tag = tag.ReplaceAll("_{c}","c");
  

  TString comps = Form("gauss%d",mode);
  TString titleY = Form("Candidates / [%d MeV/#it{c}^{2}]",bw);

  if(mode==0 || mode==2 || mode==10 || mode==12){
     TString titleX = "pK^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
  }else if(mode==1 || mode==4 || mode==11 || mode==14){
    TString titleX = "pK^{#font[122]{-}}K^{#font[122]{-}}#pi^{+} mass [MeV/#it{c}^{2}]";
  }else if(mode==3 || mode==13){
    TString titleX = "K^{#font[122]{-}}#pi^{+}#pi^{+} mass [MeV/#it{c}^{2}]";
  }
  


  TCanvas *c = new TCanvas("c_"+tag, "Mass Plot "+tag,0,0,600,600);
  c->SetRightMargin(0.05);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.11);
  RooPlot* plot2 = mvar->frame(mlow,mhi,nbin);
  plot2->SetTitle("");
  rdh->plotOn(plot2,MarkerStyle(20),MarkerSize(0.75));
  plot2->SetMinimum(0.0);
  plot2->SetMaximum(1.2*plot2->GetMaximum());
  pdf->plotOn(plot2,LineColor(kBlue),LineWidth(2),Name("Full")); 
  if(tag.Contains("Xic")) pdf->plotOn(plot2,Components(comps),LineColor(kRed),LineWidth(2),Name("Signal"));
  setFrameAtt(plot2,titleX, titleY);
  plot2->Draw();
  hh->SetLineColor(3);
  hh->Draw("same");

  float ns = nS->getVal();
  float ens = nS->getError();
  TString y = Form("N_{sig} =  %4.0f #pm %2.0f",ns,ens);
  myLatex->DrawLatex(xt,0.85,y);
  myLatex->DrawLatex(xt,0.8,lt);

  c->Print("./MassPlot_"+tag+".png");


  return c;

  
}

void setFrameAtt(RooPlot *frame, TString xtit, TString ytit)
{
  frame->SetMaximum(0.9*frame->GetMaximum());
  //frame->SetMaximum(35);
  frame->SetMinimum(0.1);    
  frame->SetLabelSize(0.045,"X");
  frame->SetLabelSize(0.045,"Y");
  frame->SetTitleSize(0.050,"X");
  frame->SetTitleSize(0.050,"Y");
  frame->SetTitleOffset(0.95,"X");
  frame->SetTitleOffset(1.25,"Y");
  frame->SetXTitle(xtit);
  frame->SetYTitle(ytit);
  frame->SetNdivisions(505,"X");
  frame->SetNdivisions(505,"Y");
  //frame->GetXaxis()->SetTitleFont(myconfigs->m_font);
  //frame->GetYaxis()->SetTitleFont(myconfigs->m_font);
}





double EstSigYield(TH1F* h,double m, double s=6){
  double bw = h->GetBinWidth(1);
  int iL = h->FindBin(m-3*s);
  int iH = h->FindBin(m+3*s);
  int iC = h->FindBin(m);
  double nS = h->Integral(iL,iH);
  double nL = h->Integral(1,iL-1);
  double nH = h->Integral(iH+1,h->GetNbinsX());
  double r = (iH-iL);
  r = r / (iL + (h->GetNbinsX()-iH));
  double Y = nS - (nL + nH)*r;
  cout << "Expected yield = " << Y << ", r = " << r << endl;
  //cout << "nL, nH, nS = " << nL << " " << nH << " " << nS << endl;
  
  return Y;  

}


TChain* getChain(TString tag,TString name){

  TChain *ch = new TChain(name,"");
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2011_MAGDN."+tag+".wMVA.test3.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2011_MAGUP."+tag+".wMVA.test3.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2012_MAGDN."+tag+".wMVA.test3.root/"+name);
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2012_MAGUP."+tag+".wMVA.test3.root/"+name);
  
  return ch;
  
    

}



void plotXicc(){

   TLatex *myLatex = new TLatex();
   myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
   double xt = 0.6;

  TCanvas *c = new TCanvas("c","Plot",800,800);
  
  TChain *l = new TChain("LumiTuple","");
  l->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2011_MAGDN.root/GetIntegratedLuminosity/LumiTuple");
  l->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2011_MAGUP.root/GetIntegratedLuminosity/LumiTuple");
  l->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2012_MAGDN.root/GetIntegratedLuminosity/LumiTuple");
  l->Add("/data1/sblusk/Xibc/Semileptonic/data/All_2012_MAGUP.root/GetIntegratedLuminosity/LumiTuple");
  //TFile *f = new TFile("/data1/sblusk/Xibc/Semileptonic/data/All_2012_MAGUP.root");
  //TTree* treeXic = (TTree*)f->Get("XicMu/mytree");
  //TTree* l = (TTree*)f->Get("GetIntegratedLuminosity/LumiTuple");
  TH1F *lum = new TH1F("lum","Lumi",5,0,5);
  l->Draw("0.5>>lum","IntegratedLuminosity");
  float lumi = lum->GetBinContent(1);    
  lt = Form("Lum =  %4.0f pb^{-1}",lumi);
  TChain *tree[20];
  TChain *treeX[10];
  

  int iMode = 0;
  //tree[0] = (TTree*)f->Get("XicMu/mytree");
  treeX[0] = getChain("X2XiccMu.XicPi","mytree");
  treeX[1] = getChain("X2XiccMu.Xiczpi","mytree");
  treeX[2] = getChain("X2XiccMu.LcKpi","mytree");
  treeX[3] = getChain("X2XiccMu.DpK","mytree");


  //return;
  

  int nSL = 5;

  TString ScutsWS;
  TCut cuts[20];
  TCut cutsX[10];
  cuts[0] = "BDTG>0.0";
  cuts[1] = "BDTG>0.0";
  cuts[2] = "BDTG>0.0";
  cuts[3] = "BDTG>0.0";
  //cuts[1] = "p_ProbNNp>0.1&&k1_ProbNNk>0.1&&k2_ProbNNk>0.1&&pi_ProbNNpi>0.05&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  //cuts[2] = "p_ProbNNp>0.3&&k_ProbNNk>0.2&&pi_ProbNNpi>0.2&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  //cuts[3] = "k_ProbNNk>0.1&&pi1_ProbNNk>0.05&&pi2_ProbNNpi>0.05&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  cuts[4] = "p_ProbNNp>0.5&&k1_ProbNNk>0.3&&k2_ProbNNk>0.3&&pi_ProbNNpi>0.05&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<3";  

  for(int i=0;i<nSL;i++){cuts[i+10] = cuts[i];}
  

  TCut vetos[20];
  vetos[0] = "(abs(sqrt((sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2)+k_PE)**2-((p_PX+k_PX)**2+(p_PY+k_PY)**2+(p_PZ+k_PZ)**2))-1020)>8 || p_PIDp-p_PIDK>8)"; // phi -> KK
  vetos[0] = vetos[0] && "(abs(sqrt((k_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2))**2-((k_PX+p_PX+pi_PX)**2+(k_PY+p_PY+pi_PY)**2+(k_PZ+p_PZ+pi_PZ)**2))-1968)>15 || p_PIDp-p_PIDK>7)";
  vetos[0] = vetos[0] && "(abs(sqrt((k_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2))**2-((k_PX+p_PX+pi_PX)**2+(k_PY+p_PY+pi_PY)**2+(k_PZ+p_PZ+pi_PZ)**2))-1869)>15 || p_PIDp-p_PIDK>5)";
  vetos[0] = vetos[0] && "sqrt((k_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((k_PX+p_PX+pi_PX)**2+(k_PY+p_PY+pi_PY)**2+(k_PZ+p_PZ+pi_PZ)**2))-sqrt((k_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((k_PX+p_PX)**2+(k_PY+p_PY)**2+(k_PZ+p_PZ)**2))>152 || (p_PIDp>25)";
  vetos[0] = vetos[0] && "abs(sqrt((k_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((k_PX+p_PX+pi_PX)**2+(k_PY+p_PY+pi_PY)**2+(k_PZ+p_PZ+pi_PZ)**2))-1869)>20 || (p_PIDp>20)";

  vetos[1] = "(abs(sqrt((sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2)+k1_PE)**2-((p_PX+k1_PX)**2+(p_PY+k1_PY)**2+(p_PZ+k1_PZ)**2))-1020)>8 || p_PIDp-p_PIDK>4)"; // phi -> KK
  vetos[1] = vetos[1] && "(abs(sqrt((sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2)+k2_PE)**2-((p_PX+k2_PX)**2+(p_PY+k2_PY)**2+(p_PZ+k2_PZ)**2))-1020)>8 || p_PIDp-p_PIDK>4)"; // phi -> KK
  vetos[1] = vetos[1] && "(abs(sqrt((sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 493.67**2)+k2_PE+k1_PE+pi_PE)**2-((p_PX+k2_PX+k1_PX+pi_PX)**2+(p_PY+k2_PY+k1_PY+pi_PY)**2+(p_PZ+k2_PZ+k1_PZ+pi_PZ)**2))-1865)>15 || p_PIDp-p_PIDK>5)"; // D0->KKKpi
  vetos[2] = vetos[0];
  vetos[3] = "Xb_M>0";
  vetos[4] = "Xb_M>0";

  for(int i=0; i<nSL;i++){ vetos[i+10] = vetos[i]; }

  bool doVeto = true;  
  if(doVeto){
    for(int i=0; i<8; i++){
      //cuts[i] = cuts[i] && "Xb_TAU<0.0015";
      //cuts[i] = cuts[i] && vetos[i];
      //cuts[i] = cuts[i] && "p_IPCHI2_OWNPV>9&&pi_IPCHI2_OWNPV>9";
      //if(i==0 || i==3 || i==6) cuts[i] = cuts[i] && "k_IPCHI2_OWNPV>9";
      //if(i!=0 && i!=3 && i!=6) cuts[i] = cuts[i] && "(k1_IPCHI2_OWNPV>9||k2_IPCHI2_OWNPV>9)";      
    }
  }
  //ScutsWS = cuts[4];
  //ScutsWS.ReplaceAll("k1","K1");
  //ScutsWS.ReplaceAll("k2","K2");
  //TCut cutsWS = ScutsWS;
  

  TH1F *hc = new TH1F("hc","m",1000,0,1000);
  //tree[0]->Draw("sqrt((k_PE+pi_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((k_PX+p_PX+pi_PX)**2+(k_PY+p_PY+pi_PY)**2+(k_PZ+p_PZ+pi_PZ)**2))-sqrt((k_PE+sqrt(p_PX**2 + p_PY**2 + p_PZ**2 + 139.57**2))**2-((k_PX+p_PX)**2+(k_PY+p_PY)**2+(k_PZ+p_PZ)**2))>>hc",cuts[0]);

  //tree[0]->Draw("Xc_PT",cuts[0]&&"Xc_PT<10000");
  //return;

  //doComb("XicMu",tree[2],cuts[2],"Xc_M");
  //return;

  
  float masses[20] = {2469, 2472, 2288, 1871, 2696, 0,0,0,0,0, 2469, 2472, 2288, 1871, 2696, 0,0,0,0,0 };  
  double mlow[20] = {2420, 2420, 2240, 1820, 2645, 0,0,0,0,0, 2420, 2420, 2240, 1820,2645, 0,0,0,0,0 };
  double mhi[20]  = {2520, 2520, 2330, 1920, 2745, 0,0,0,0,0, 2520, 2520, 2330, 1920, 2745, 0,0,0,0,0};  
  double bw[20] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,};
  int nbins[20];
  for(int i=0; i<20; i++){nbins[i] = (mhi[i]-mlow[i])/bw[i];}
  TH1F *h[20];
  

  double sy[20], by[20];

  
  RooRealVar* mvar[20];
  RooRealVar* mg[20];
  RooRealVar* fr[20];
  RooRealVar* sg[20];
  RooRealVar* sg2[20];
  RooRealVar* b1[20];
  RooGaussian* gaussA[20];
  RooGaussian* gaussB[20];
  RooAbsPdf* gauss[20];
  RooExponential* comb[20];
  RooRealVar* nsig[20];
  RooRealVar* ncomb[20];
  RooAbsPdf* pdf[20];
  RooDataHist *rdh[20];
  TString modes[20] = {"#Xi_{c}^{+}", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}",  
                      "", "","","","",
                      "#Xi_{c}^{+}", "#Xi_{c}^{0}", "#Lambda_{c}^{+}", "D^{+}", "#Omega_{c}^{0}", 
                      "", "","","",""};
  
  TString dmExp[4] = {"Xcc_M-Xc_M+2471", "Xcc_M-Xc_M+2470", "Xcc_M-Xc_M+2286", "Xcc_M-Xc_M+1869"};
  

  TFile *fout = new TFile("temp.root","RECREATE");
  

  TCanvas *ccc = new TCanvas("ccc","Xic",1200,600);
  //treeX[0]->Draw("Xcc_M-Xc_M-PI_M",cutsX[0]);
  
  //return;

  for(int i=0;i<4;i++){cutsX[i] = cuts[i];}
  
  TCut extraCuts[4];
  extraCuts[0] = "Xcc_FDCHI2_ORIVX>2&&PI_ProbNNpi>0.05&&PI_PT>500&&PI_IPCHI2_OWNPV>4&&Xcc_ENDVERTEX_CHI2/Xcc_ENDVERTEX_NDOF<3&&Xcc_PT>2000";
  extraCuts[1] = "Xcc_FDCHI2_ORIVX>2&&PI_ProbNNpi>0.05&&PI_PT>400&&PI_IPCHI2_OWNPV>4&&Xcc_ENDVERTEX_CHI2/Xcc_ENDVERTEX_NDOF<3&&Xcc_PT>2000";
  extraCuts[2] = "Xcc_FDCHI2_ORIVX>2&&K_ProbNNk>0.3&&K_PT>400&&PI_ProbNNpi>0.2&&PI_PT>300&&Xcc_ENDVERTEX_CHI2/Xcc_ENDVERTEX_NDOF<3&&Xcc_PT>2000";  
  extraCuts[3] = "P_ProbNNp>0.2&&K_ProbNNk>0.1&&Xcc_ENDVERTEX_CHI2/Xcc_ENDVERTEX_NDOF<4&&Xcc_PT>2000";
  float dmCut[4] = {15, 10, 15, 15};
  float sbMass1[4] = {2440, 2440, 2250, 1830 };
  float sbMass2[4] = {2500, 2500, 2320, 1910};
  

  TCut addVeto = "abs(sqrt((p_PE+k_PE+PI_PE)**2-((k_PX+p_PX+PI_PX)**2+(k_PY+p_PY+PI_PY)**2+(k_PZ+p_PZ+PI_PZ)**2))-2286)>15";
  addVeto = addVeto && "abs(sqrt((pi_PE+k_PE+PI_PE)**2-((k_PX+pi_PX+PI_PX)**2+(k_PY+pi_PY+PI_PY)**2+(k_PZ+pi_PZ+PI_PZ)**2))-1870)>20";
  
  TCut mPiPiCut = "abs(sqrt((pi_PE+PI_PE)**2-((pi_PX+PI_PX)**2+(pi_PY+PI_PY)**2+(pi_PZ+PI_PZ)**2)))>300";
  extraCuts[0] = extraCuts[0] && addVeto && mPiPiCut;
  

  ccc->Divide(4,2);
  TH1F *hm[10];
  TH1F *dm[10];
  TH1F *dmb[10];
  for(int i=0;i<4;i++){
    cout << "i = " << i << endl;
    TString hist = Form("%d",i);
    hm[i] = new TH1F("hm_"+hist,"mass",nbins[i],mlow[i],mhi[i]);
    dm[i] = new TH1F("dm_"+hist,"#Deltam",200,2500,4500);
    dmb[i] = new TH1F("dmb_"+hist,"#Deltam",200,2500,4500);
    dmb[i]->SetLineColor(2);
    hm[i]->SetMinimum(0);
    TString cut = Form("abs(Xc_M-%4.0f)<%2.0f",masses[i],dmCut[i]);
    TString sbMass = Form("(abs(Xc_M-%4.0f)<%2.0f)||(abs(Xc_M-%4.0f)<%2.0f)",sbMass1[i],dmCut[i]/2,sbMass2[i],dmCut[i]/2);
    TCut allCut = cutsX[i];//&&cut&&extraCuts[i];
    TCut allCutB = cutsX[i];//&&sbMass&&extraCuts[i];
    ccc->cd(i+1);
    treeX[i]->Draw("Xc_M>>hm_"+hist,cutsX[i]);
    ccc->cd(i+5);
    //treeX[i]->Draw(dmExp[i]+">>"+hist2,cutsX[i]); 
    allCut.Print();
    TString histProj = dmExp[i]+">>+dm_"+hist;
    TString histProj2 = dmExp[i]+">>+dmb_"+hist;
    //TString histProj = "Xcc_M-Xc_M-PI_M>>+dm_"+hist;
    cout << histProj << endl;
    treeX[i]->Draw(histProj,allCut); 
    treeX[i]->Draw(histProj2,allCutB); 
    dm[i]->Draw();
    dmb[i]->Draw("same");

    TCut allCut2 = allCut && "Xcc_M-Xc_M+2471<2660";
    //doComb("XiccMu",treeX[0],allCut2,"Xcc_M");  

  }

  //TCanvas *c4 = new TCanvas("c4","2D",800,800);
  //treeX[0]->Draw("Xcc_M-Xc_M+2471:Xc_M",allCut,"box");

  TH1F *hXic = dm[0]->Clone("hXic");
  hXic->Add(dm[1]);
  hXic->Add(dm[2]);
  hXic->Add(dm[3]);

  TCanvas *c = new TCanvas("c","Mass",800,800);
  hXic->Draw();
  
    

  return;



  
}


