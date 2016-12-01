void addVar()
{

  TString outdir = "/data1/sblusk/Xibc/JpsiX/Lb2JpsipK/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"Lb2JpsipK_MC.root";
  outfile = outdir+"Lb2JpsipK_mc.root";
  treeName = "X2JpsipK/mytree";
  
  
  
  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double k_ETA, p_ETA;
  double k_PZ, p_PZ;
  double k_PT, p_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("nTracks", &nTracks);

  oldtree->SetBranchAddress("k_PT", &k_PT);  
  oldtree->SetBranchAddress("p_PT", &p_PT);  
  oldtree->SetBranchAddress("k_PZ", &k_PZ);  
  oldtree->SetBranchAddress("p_PZ", &p_PZ);  

  TFile *newfile = new TFile(outfile,"RECREATE");
  TTree* newtree = (TTree*) oldtree->CloneTree(0);

  //newtree->Branch("lab0_LOKI_CONE1PTASY", &lab0_LOKI_CONE1PTASY);
  newtree->Branch("p_ETA", &p_ETA);
  newtree->Branch("k_ETA", &k_ETA);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      

      // Scale up nTracks
      v = 1.2*nTracks;
      nTracks = v;

      p_ETA = -1.0*log(tan(0.5*p_PT/p_PZ));
      k_ETA = -1.0*log(tan(0.5*k_PT/k_PZ));
      
      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
