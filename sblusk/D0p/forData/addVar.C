void addVar(TString sign = "rs"){

  TString infile, outfile,treeName;
  TString outdir = "/data1/sblusk/Xibc/D0p/data/";
  TString topdir = outdir;

  infile = topdir+"X2D0p.root";
  outfile = outdir+"X2D0p.pkpi."+sign+".root";
   
  treeName = sign+"Xibc2D0p/mytree";

  
  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);


  double p_ProbNNp, K_ProbNNk, pi_ProbNNpi;
  double Pr_V3ProbNNp, K_V3ProbNNk, Pi_V3ProbNNpi;

  oldtree->SetBranchAddress("p_ProbNNp", &p_ProbNNp);  
  oldtree->SetBranchAddress("K_ProbNNk", &K_ProbNNk);  
  oldtree->SetBranchAddress("pi_ProbNNpi", &pi_ProbNNpi);  

  
  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);


  newtree->Branch("K_V3ProbNNk", &K_V3ProbNNk);
  newtree->Branch("Pi_V3ProbNNpi", &Pi_V3ProbNNpi);
  newtree->Branch("Pr_V3ProbNNp", &Pr_V3ProbNNp);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      Pi_V3ProbNNpi = pi_ProbNNpi;
      K_V3ProbNNk = K_ProbNNk;
      Pr_V3ProbNNp = p_ProbNNp;
      newtree->Fill();      
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
