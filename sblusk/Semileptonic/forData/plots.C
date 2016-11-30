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


TChain* getChain(TString name){

  TChain *ch = new TChain(name,"");
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/2011/all_2011_MAGDN.root/"+name+"/mytree");
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/2011/all_2011_MAGUP.root/"+name+"/mytree");
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/2012/all_2012_MAGDN.root/"+name+"/mytree");
  ch->Add("/data1/sblusk/Xibc/Semileptonic/data/2012/all_2012_MAGUP.root/"+name+"/mytree");
  
  return ch;
  
    

}



void plots(){

   TLatex *myLatex = new TLatex();
   myLatex->SetTextFont(42); myLatex->SetTextColor(1); myLatex->SetTextAlign(12); myLatex->SetNDC(kTRUE); myLatex->SetTextSize(0.045);
   double xt = 0.6;

  TCanvas *c = new TCanvas("c","Plot",800,800);

  TFile *f = new TFile("/data1/sblusk/Xibc/Semileptonic/data/2012/all_2012_MAGUP.root");
  //TTree* treeXic = (TTree*)f->Get("XicMu/mytree");
  TTree* l = (TTree*)f->Get("GetIntegratedLuminosity/LumiTuple");
  TH1F *lum = new TH1F("lum","Lumi",5,0,5);
  l->Draw("0.5>>lum","IntegratedLuminosity");
  float lumi = lum->GetBinContent(1);    
  lt = Form("Lum =  %4.0f pb^{-1}",lumi);
  TChain *tree[20];
  TChain *treeX[10];
  

  int iMode = 0;
  //tree[0] = (TTree*)f->Get("XicMu/mytree");
  tree[0] = getChain("XicMu");
  tree[1] = getChain("XiczMu");
  tree[2] = getChain("LcMu");
  tree[3] = getChain("DMu");
  tree[4] = getChain("OmczMu");
  tree[10] = getChain("wsXicMu");
  tree[11] = getChain("wsXiczMu");
  tree[12] = getChain("wsLcMu");
  tree[13] = getChain("wsDMu");
  tree[14] = getChain("wsOmczMu");

  treeX[0] = getChain("XiccppMu");
  treeX[1] = getChain("XiccpMu");
  treeX[2] = getChain("XiccpMu1");
  treeX[3] = getChain("XiccpMu2");


  //return;
  

  int nSL = 5;

  TString ScutsWS;
  TCut cuts[20];
  TCut cutsX[10];
  cuts[0] = "p_ProbNNp>0.3&&k_ProbNNk>0.2&&pi_ProbNNpi>0.2&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  cuts[1] = "p_ProbNNp>0.1&&k1_ProbNNk>0.1&&k2_ProbNNk>0.1&&pi_ProbNNpi>0.05&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  cuts[2] = "p_ProbNNp>0.3&&k_ProbNNk>0.2&&pi_ProbNNpi>0.2&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
  cuts[3] = "k_ProbNNk>0.1&&pi1_ProbNNk>0.05&&pi2_ProbNNpi>0.05&&Xc_ENDVERTEX_CHI2/Xc_ENDVERTEX_NDOF<5";
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
      cuts[i] = cuts[i] && vetos[i];
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
  
  /*
  ccc->Divide(4,2);
  TH1F *hm[10];
  TH1F *dm[10];
  TH1F *dmb[10];
  for(int i=0;i<4;i++){
    cout << "i = " << i << endl;
    TString hist = Form("%d",i);
    hm[i] = new TH1F("hm_"+hist,"mass",nbins[i],mlow[i],mhi[i]);
    dm[i] = new TH1F("dm_"+hist,"#Deltam",140,2600,4000);
    dmb[i] = new TH1F("dmb_"+hist,"#Deltam",140,2600,4000);
    dmb[i]->SetLineColor(2);
    hm[i]->SetMinimum(0);
    TString cut = Form("abs(Xc_M-%4.0f)<%2.0f",masses[i],dmCut[i]);
    TString sbMass = Form("(abs(Xc_M-%4.0f)<%2.0f)||(abs(Xc_M-%4.0f)<%2.0f)",sbMass1[i],dmCut[i]/2,sbMass2[i],dmCut[i]/2);
    TCut allCut = cutsX[i]&&cut&&extraCuts[i];
    TCut allCutB = cutsX[i]&&sbMass&&extraCuts[i];
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


  return;

  */

  
  TCanvas *cc[20];
  
  TCut theCuts;
  double sigma[20]; for(int j=0;j<20;j++){sigma[j] = 6.0;}
  int i;
  for(int j=1; j>=0; j--){  
    for(int k=0; k<nSL;k++){
      i = 10*j + k;
      theCuts = cuts[i];
      //if(modes[i].Contains("Omega") && j==1) theCuts = cutsWS;
      cout << "Mode = " << modes[i] << endl;
      
      mvar[i] = new RooRealVar(Form("mvar%d",i),"lab0_M",mlow[i],mhi[i]);
      h[i] = new TH1F(Form("h%d",i),"Mass",nbins[i],mlow[i],mhi[i]);
      TString histExp = Form("Xc_M>>h%d",i);
      tree[i]->Draw(histExp,theCuts);
      //h[i]->Draw();
      //return;
      
      mg[i] = new RooRealVar(Form("mg%d",i),"mean",masses[i],masses[i]-10,masses[i]+10);
      sg[i] = new RooRealVar(Form("sg%d",i),"width",sigma[i],2,15);
      sg2[i] = new RooRealVar(Form("sg2%d",i),"width",8,4,15);
      fr[i] = new RooRealVar(Form("fr%d",i),"fraction",0.9,0.5,1.0);
      if(i==4){
        fr[4]->setVal(fr[1]->getVal());
        fr[4]->setConstant();
      }
      
      gaussA[i] = new RooGaussian(Form("gaussA%d",i),"Signal",*mvar[i],*mg[i],*sg[i]);
      gaussB[i] = new RooGaussian(Form("gaussB%d",i),"Signal",*mvar[i],*mg[i],*sg2[i]);
      gauss[i] = new RooAddPdf(Form("gauss%d",i),"Signal",RooArgList(*gaussA[i],*gaussB[i]),RooArgList(*fr[i]));
      b1[i]  = new RooRealVar(Form("b%d",i), "b1", -0.003,-0.05,0.05);//0.002,-0.005,0.000001);
      comb[i] = new RooExponential(Form("comb%d",i),"f_{back}",*mvar[i],*b1[i]);
      sy[i] = EstSigYield(h[i], masses[i], sigma[i]);
      by[i] = h[i]->GetEntries()-sy[i];
      nsig[i] = new RooRealVar("n_{sig}^{"+modes[i]+"}","",sy[i],0,300000);
      ncomb[i] = new RooRealVar("n_{comb}^{"+modes[i]+"}","",by[i],0,300000);
      rdh[i] = new RooDataHist(Form("rdh%d",i),"", *mvar[i], h[i]);
      pdf[i] = new RooAddPdf(Form("pdf%d",i),"",RooArgList(*gauss[i],*comb[i]),RooArgList(*nsig[i],*ncomb[i]));  
      //if(i < 10){
      //  pdf[i]->fitTo(*rdh[i]);
      //  cc[i] = makeRooPlot(pdf[i],rdh[i],mvar[i],i,nsig[i],h[i+10],modes[i],mlow[i],mhi[i],nbins[i]);
      //}
      
    }
  }
  
  //return;

  pdf[iMode]->fitTo(*rdh[iMode]);
  cc[iMode] = makeRooPlot(pdf[iMode],rdh[iMode],mvar[iMode],iMode,nsig[iMode],h[iMode+10],modes[iMode],mlow[iMode],mhi[iMode],nbins[iMode]);
  

  iMode++;
  pdf[iMode]->fitTo(*rdh[iMode]);
  cc[iMode] = makeRooPlot(pdf[iMode],rdh[iMode],mvar[iMode],iMode,nsig[iMode],h[iMode+10],modes[iMode],mlow[iMode],mhi[iMode],nbins[iMode]);

  iMode++;
  pdf[iMode]->fitTo(*rdh[iMode]);
  cc[iMode] = makeRooPlot(pdf[iMode],rdh[iMode],mvar[iMode],iMode,nsig[iMode],h[iMode+10],modes[iMode],mlow[iMode],mhi[iMode],nbins[iMode]);

  iMode++;
  pdf[iMode]->fitTo(*rdh[iMode]);
  cc[iMode] = makeRooPlot(pdf[iMode],rdh[iMode],mvar[iMode],iMode,nsig[iMode],h[iMode+10],modes[iMode],mlow[iMode],mhi[iMode],nbins[iMode]);

  iMode++;
  
  pdf[iMode]->fitTo(*rdh[iMode]);
  cc[iMode] = makeRooPlot(pdf[iMode],rdh[iMode],mvar[iMode],iMode,nsig[iMode],h[iMode+10],modes[iMode],mlow[iMode],mhi[iMode],nbins[iMode]);

  return;
  
  
}


