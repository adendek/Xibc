void addVar()
{

  TString outdir = "/data1/sblusk/Xibc/JpsiX/JpsiLc/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"JpsiLc_MC.root";
  outfile = outdir+"JpsiLc_mc.root";
  treeName = "X2JpsiLcp/mytree";
  
  
  
  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double K_ETA, Pi_ETA, Pr_ETA;
  double K_PZ, Pi_PZ, Pr_PZ;
  double K_PT, Pi_PT, Pr_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("nTracks", &nTracks);

  oldtree->SetBranchAddress("K_PT", &K_PT);  
  oldtree->SetBranchAddress("Pi_PT", &Pi_PT);  
  oldtree->SetBranchAddress("Pr_PT", &Pr_PT);  
  oldtree->SetBranchAddress("K_PZ", &K_PZ);  
  oldtree->SetBranchAddress("Pi_PZ", &Pi_PZ);  
  oldtree->SetBranchAddress("Pr_PZ", &Pr_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("Pr_ETA", &Pr_ETA);
  newtree->Branch("K_ETA", &K_ETA);
  newtree->Branch("Pi_ETA", &Pi_ETA);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      

      // Scale up nTracks
      v = 1.3*nTracks;
      nTracks = v;

      Pr_ETA = -1.0*log(tan(0.5*Pr_PT/Pr_PZ));
      K_ETA = -1.0*log(tan(0.5*K_PT/K_PZ));
      Pi_ETA = -1.0*log(tan(0.5*Pi_PT/Pi_PZ));
      
      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
