//   WITHIN ROOT
//
//  .L addVar.C
//  addVar(iDecayNumber) to just do a single one
//  doAll() to do all data samples
//  doRS() to do only RS data samples
//  doWS() to do only WS data samples
//
// 1 = 2011 - RS MAGDN          11 = 2011 - WS MAGDN
// 2 = 2011 - RS MAGUP          12 = 2011 - WS MAGUP
// 3 = 2012 - RS MAGDN          13 = 2012 - WS MAGDN              
// 4 = 2012 - RS MAGUP          14 = 2012 - WS MAGUP             
//
void doAll(){
  for(int i=1; i<=4; i++){  addVar(i); }    // Right sign
  for(int i=11; i<=14; i++){  addVar(i); }   // Wrong sign
}

void doRS(){
  for(int i=1; i<=4; i++){  addVar(i); }    // Right sign
}

void doWS(){
  for(int i=11; i<=14; i++){  addVar(i); }   // Wrong sign
}

void do2011(){
  for(int i=1; i<=2; i++){  addVar(i); }   // RS
  for(int i=11; i<=12; i++){  addVar(i); }   // RS
}

void do2012(){
  for(int i=3; i<=4; i++){  addVar(i); }   // RS
  for(int i=13; i<=14; i++){  addVar(i); }   // RS
}



void addVar(int iDecay){


  TString infile, outfile,treeName;
  treeName = "X2JpsipK/mytree";

  TString run  = "2011";
  TString mag = "MAGDN";
  TString sign = "rs";
  if((iDecay >= 3 && iDecay<=4) || iDecay>=13) run = "2012";
  if(iDecay==2 || iDecay==4 || iDecay==12 || iDecay==14) mag = "MAGUP";
  if(iDecay > 10) {
    sign = "ws";
    treeName = sign+treeName;
  }

  TString outdir = "/data1/sblusk/Xibc/JpsiX/data/";
  TString topdir = outdir;
  infile = topdir+"All_"+run+"_"+mag+".root";
  outfile = topdir+"Lb2JpsipK/data/All_"+run+"_"+mag+".pkpi."+sign+".root";   

  
  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double k_MC12TuneV3_ProbNNk;
  double p_MC12TuneV3_ProbNNp;  
  double p_V3ProbNNp, k_V3ProbNNk;

  oldtree->SetBranchAddress("k_MC12TuneV3_ProbNNk", &k_MC12TuneV3_ProbNNk);  
  oldtree->SetBranchAddress("p_MC12TuneV3_ProbNNp", &p_MC12TuneV3_ProbNNp);  

  
  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);


  newtree->Branch("k_V3ProbNNk", &k_V3ProbNNk);
  newtree->Branch("p_V3ProbNNp", &p_V3ProbNNp);

  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;


  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      k_V3ProbNNk = k_MC12TuneV3_ProbNNk;
      p_V3ProbNNp = p_MC12TuneV3_ProbNNp;
      newtree->Fill();      
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
