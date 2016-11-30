void tune2012MC()
{

  int iDecay = 1;   // 1 = Xib-, 2 = Xib0

  TString outdir = "/data1/sblusk/Xibc/JpsiX/mc/";
  
  TString infile, outfile,treeName;
  TString topdir = outdir;
  infile = topdir+"JpsiXic_mc.root";
  outfile = outdir+"JpsiXic_mc.tuned.root";
  treeName = "X2JpsiXicp/mytree";
  
  
  
  cout << " -------------------------------------------------------------------------" << endl;
  //cout << "Running tuning of input MC variables, Decay.= " << decay << endl;
  cout << "Input File: " << infile << endl;
  cout << "Output file: " << outfile << endl; 
  cout << "----> Tree: " << treeName << endl;
  cout << " -------------------------------------------------------------------------" << endl;

  TFile *f = new TFile(infile);
  
  TTree *oldtree = (TTree*)f->Get(treeName);

  double p_IPCHI2_OWNPV;
  double K_IPCHI2_OWNPV;
  double Xb_IPCHI2_OWNPV;
  double Xb_FDCHI2_OWNPV;

  double Xc_IPCHI2_OWNPV;
  double Pi_IPCHI2_OWNPV;
  double Pr_IPCHI2_OWNPV;
  double K_IPCHI2_OWNPV;

  int Xb_BKGCAT;
  double Xb_LOKI_DTF_CHI2NDOF_massConstr;
  double Xc_M, Xb_M;

  double Xb_PT, Xc_PT;
  double Xc_PT;
  double K_PT;
  double Pi_PT;
  double Pr_PT;

  double K_ETA, Pi_ETA, Pr_ETA;
  double K_PZ, Pi_PZ, Pr_PZ;
  double K_PT, Pi_PT, Pr_PT;

  double nTracks;
  int nTracksI;
  

  oldtree->SetBranchAddress("Xb_IPCHI2_OWNPV", &Xb_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xc_IPCHI2_OWNPV", &Xc_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("K_IPCHI2_OWNPV", &K_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Pi_IPCHI2_OWNPV", &Pi_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Pr_IPCHI2_OWNPV", &Pr_IPCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_FDCHI2_OWNPV", &Xb_FDCHI2_OWNPV);
  oldtree->SetBranchAddress("Xb_M", &Xb_M);
  oldtree->SetBranchAddress("Xb_LOKI_DTF_CHI2NDOF_massConstr", &Xb_LOKI_DTF_CHI2NDOF_massConstr);
  oldtree->SetBranchAddress("Xc_M", &Xc_M);
  oldtree->SetBranchAddress("nTracks", &nTracks);
  oldtree->SetBranchAddress("Xc_PT", &Xc_PT);

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
  newtree->Branch("nTracksI", &nTracksI);

  Long64_t nentries = oldtree->GetEntriesFast();
  cout << "Looping over " << nentries << " entries" << endl;
   
   //nentries = 1000;
   
   double v;
   for (Long64_t i=0;i<nentries; i++) {
      oldtree->GetEntry(i);
      if(i%10000 == 0) cout << "At entry = " << i << endl;
      
      double voff = 0.08; 
      if(Xb_LOKI_DTF_CHI2NDOF_massConstr>=0){
        v = exp(log(Xb_LOKI_DTF_CHI2NDOF_massConstr)+voff);
        Xb_LOKI_DTF_CHI2NDOF_massConstr = v;
      }
      
      if(Xb_IPCHI2_OWNPV<0){
        cout << "Negative IPCHI2, skipping this ... " << Xb_IPCHI2_OWNPV << endl;
      }else{
        v = exp(log(Xb_IPCHI2_OWNPV)+0.05);
        Xb_IPCHI2_OWNPV = v;
      }
      
      

      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(K_IPCHI2_OWNPV)+voff);
      K_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(Pi_IPCHI2_OWNPV)+voff);
      Pi_IPCHI2_OWNPV = v;
      voff = 0.15*(1.0+0.05*gRandom->Gaus());
      v = exp(log(Pr_IPCHI2_OWNPV)+voff);
      Pr_IPCHI2_OWNPV = v;

      v = exp(log(Xc_IPCHI2_OWNPV)+0.15);
      Xc_IPCHI2_OWNPV = v;


      // In sim08, the pT asymmetry looks fine as is..
      //lab0_LOKI_CONE1PTASY = lab0_LOKI_CONE1PTASY - 0.04;
      // lab0_LOKI_CONE1PTASY =  lab0_ptasy_1_50 - 0.08;


      // Scale up nTracks
      v = 1.3*nTracks;
      nTracks = v;


      Pr_ETA = -1.0*log(tan(0.5*Pr_PT/Pr_PZ));
      K_ETA = -1.0*log(tan(0.5*K_PT/K_PZ));
      Pi_ETA = -1.0*log(tan(0.5*Pi_PT/Pi_PZ));
      
      nTracksI = nTracks;

      newtree->Fill();
      
      //event->Clear();
   }
   //newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

}
