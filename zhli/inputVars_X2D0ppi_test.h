//=========== These variables definitely depend on mode ===========

TString topdir = "/data1/zli59/D0ppi/";
TString topdirMC = "/data1/zli59/D0ppi/";

static const int nDataFileRS = 1;
static const int nDataFileWS = 1;

//const float XcMass = 1865.0;

const static int nVars = 19;
TString vars[nVars];
TString varNames[nVars];
TString varForCuts[10];


const static int nVarForCuts = 3;
double valueForCut[nVarForCuts];
TString gtlt[nVarForCuts];

const static int nTrainSigFile = 1;
const static int nTrainBackFile = 1;

TString mode = "X2D0ppi";
TString finalState = "piKppi";

//===================================================================

TString dataFile[20];
TString dataFile[20];
TString mcFile;

TString fnameSig[nTrainSigFile];   
TString fnameBack[nTrainBackFile]; 
TString treeNameS, treeNameB;

TCut mycuts, mycutb;
TString signalWeightExpression="";
TString backWeightExpression="";

TString myMethodList = "BDTG";
TString year = "2011";


void getVars(){
  int iv = 0;
  vars[iv++] = "log(Xb_LOKI_CHI2NDOF_D0Constr)";
  vars[iv++] = "log(Xb_IPCHI2_OWNPV)";
  vars[iv++] = "log(acos(Xb_DIRA_OWNPV))";
  vars[iv++] = "log(sqrt(pow(Xb_ENDVERTEX_X-Xb_OWNPV_X,2)+pow(Xb_ENDVERTEX_Y-Xb_OWNPV_Y,2)))";
  vars[iv++] = "log(Xb_PT)";
  vars[iv++] = "log(Rp_PT)";
  vars[iv++] = "log(Rp_IPCHI2_OWNPV)";
  vars[iv++] = "log(D_IPCHI2_OWNPV)";

  vars[iv++] = "log(K_IPCHI2_OWNPV)";
  vars[iv++] = "log(Rpi_IPCHI2_OWNPV)";
  //vars[iv++] = "log(D_FDCHI2_OWNPV)";
  vars[iv++] = "log(min(K_IPCHI2_OWNPV,pi_IPCHI2_OWNPV))";
  vars[iv++] = "1-sqrt(1-Pr_V3ProbNNp)";
  vars[iv++] = "1-sqrt(1-K_V3ProbNNk)";
  vars[iv++] = "1-sqrt(1-RPi_V3ProbNNpi)";
  vars[iv++] = "1-sqrt(1-Pi_V3ProbNNpi)";
  vars[iv++] = "log(Rp_P)";
  vars[iv++] = "log(K_P)";
  vars[iv++] = "log(Rpi_P)";
  vars[iv++] = "log(pi_P)";

  TString b1 = "#Xi_{bc}^{+}";
  TString d1 = "D^{0}";
  TString d2 = "proton";
  iv = 0;
  varNames[iv++] =  b1+" log(#chi^{2}_{vtx})";
  varNames[iv++] = b1+" log(#chi^{2}_{IP})";
  varNames[iv++] = b1+" pointing angle";
  varNames[iv++] = b1+" log(radial FD)";
  varNames[iv++] = b1+" log(Rp_{T})";
  varNames[iv++] = d2+" log(#chi^{2}_{IP})";
  varNames[iv++] = d2+" log(Rp_{T})";
  varNames[iv++] = d1+" log(#chi^{2}_{IP})";
  varNames[iv++] = "K log(#chi^{2}_{IP})";
  varNames[iv++] = "Rpi log(#chi^{2}_{IP})";
  //varNames[iv++] = d1+" log(#chi^{2}_{FD})";
  varNames[iv++] = "log(Min "+d1+" #chi^{2}_{IP})";
  varNames[iv++] = "1-#sqrt{1-Rp_ProbNNp}" ;
  varNames[iv++] = "1-#sqrt{1-K_ProbNNK}";
  varNames[iv++] = "1-#sqrt{1-RPi_ProbNNpi}";
  varNames[iv++] = "1-#sqrt{1-pi_ProbNNpi}";
  varNames[iv++] = "log(Proton Mom)";
  varNames[iv++] = "log(K Mom)";
  varNames[iv++] = "log(Rpi Mom)";
  varNames[iv++] = "log(Pi Mom)";

  return;
}

void getTrainingFiles(){

  fnameSig[0] = topdirMC + "MC.tuned.piKppi.root";
  fnameBack[0] = topdir + "X2D0ppi.piKppi.ws.root";
  treeNameS = "mytree";
  treeNameB = "mytree";

  return;
}


void getTrainingCuts(){
  mycutb = Form("Pr_V3ProbNNp>0.1 && RPi_V3ProbNNpi>0.05 && K_V3ProbNNk>0.05 && Pi_V3ProbNNpi>0.01&&Xb_M>5400");
    mycuts = Form("Pr_V3ProbNNp>0.1 && RPi_V3ProbNNpi>0.05 && K_V3ProbNNk>0.05 && Pi_V3ProbNNpi>0.01 &&abs(D_M-1865)<30 &&abs(Xb_M-5620)<70");

  // Set weightes here and uncomment, if you want to weight events
  signalWeightExpression = "Xb_TRUEID!=0 && D_BKGCAT==0&&abs(Rp_TRUEID)==2212&&abs(K_TRUEID)==321&&abs(Rpi_TRUEID)>200";
  //backWeightExpression = "";
  
  return;
  
}


void getFiles(){
  dataFile[1] = "X2D0ppi.piKppi.rs";
  dataFile[11] = "X2D0ppi.piKppi.ws";
  mcFile = "MC.tuned.piKppi";
}


void getVarForCuts(){

  varForCuts[0] = "Xb_LOKI_CHI2NDOF_D0Constr";
  varForCuts[1] = "Xb_DIRA_OWNPV";
  //  varForCuts[2] = Form("abs(D_M-%5.1f)",XcMass);
  valueForCut[0] = 0;
  valueForCut[1] = 0;
  // valueForCut[2] = 25;
  
  gtlt[0] = "gt";
  gtlt[1] = "gt";
  //  gtlt[2] = "lt";
  

}

