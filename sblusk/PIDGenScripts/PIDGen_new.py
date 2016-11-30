import argparse, sys, os

sys.path.append("../expert/")
os.environ["ROOT_INCLUDE_PATH"] = os.pathsep + "../../Meerkat/inc/"

from ROOT import gROOT, TNtuple, TFile, TH1F, TH2F, TCanvas, TMath, TRandom3, gStyle, gSystem, RooRealVar

gSystem.Load("../../Meerkat/lib/libMeerkat.so")

from ROOT import OneDimPhaseSpace, CombinedPhaseSpace, BinnedDensity

from Config import *

parser = argparse.ArgumentParser(description='PIDGen')
parser.add_argument('-i', type=str, default = None, 
                    help='Input file name')
parser.add_argument('-t', type=str, default = "tree", 
                    help='Input tree name')
parser.add_argument('-o', type=str, default = "output.root", 
                    help='Output file name')
parser.add_argument('-p', type=str, default = "PID_gen", 
                    help='PID variable')
parser.add_argument('-m', type=str, default = "Pt", 
                    help='Pt variable')
parser.add_argument('-e', type=str, default = "Eta", 
                    help='Eta variable')
parser.add_argument('-n', type=str, default = "nTracks", 
                    help='Ntracks variable')
parser.add_argument('-l', type=str, default = None, 
                    help='Lower PID value to generate')
parser.add_argument('-c', type=str, default = "p_V3ProbNNp", 
                    help='PID response to sample')
parser.add_argument('-d', type=str, default = "MagDown_2011", 
                    help='Dataset (polarity_year)')
parser.add_argument('-v', type=str, default = "default", 
                    help='Variation (default, syst_N, stat_N etc.)')

parser.print_help()
args = parser.parse_args()

print args

infilename = args.i
intree = args.t
outfilename = args.o
pidvar = args.p
ptvar = args.m
etavar = args.e
ntrvar = args.n
minpid = args.l
config = args.c
dataset = args.d
variant = args.v

if not infilename : 
  print "Usage: PIDGen.py [options]"
  print "  For the usage example, look at batch.sh file"
  print "  Available PID configs are: "
  for i in sorted(configs.keys()) : 
    print "    ", i
  quit()

if variant == "default" : variant = "distrib"  # to do: change this name in CreatePIDPdf

calibfilename = eosrootdir + "/" + config + "/" + "%s_%s.root" % (dataset, variant)
  
transform_forward = configs[config]['transform_forward']
transform_backward = configs[config]['transform_backward']

print "Calib File name: ",calibfilename

from math import sqrt

pidmin = 0.
pidmax = 1.
if 'limits' in configs[config] : 
  pidmin = configs[config]['limits'][0]
  pidmax = configs[config]['limits'][1]
if minpid == None : 
  minpid = pidmin
else :
  minpid = float(minpid)
  if minpid<pidmin : minpid = pidmin

# Calculate the minimum PID variable to generate (after transformation)
x = pidmin
pidmin = eval(transform_forward)
x = pidmax
pidmax = eval(transform_forward)
x = minpid
minpid = eval(transform_forward)

pid_phsp = OneDimPhaseSpace("PIDPhsp", pidmin , pidmax )
mom_phsp = OneDimPhaseSpace("MomPhsp", 5.5, 9.5)
eta_phsp = OneDimPhaseSpace("EtaPhsp", 1.5, 5.5)
ntr_phsp = OneDimPhaseSpace("NtrPhsp", 3.0, 6.5)
pidmom_phsp = CombinedPhaseSpace("PIDMomPhsp", pid_phsp, mom_phsp) 
pidmometa_phsp = CombinedPhaseSpace("PIDMomEtaPhsp", pidmom_phsp, eta_phsp) 
phsp = CombinedPhaseSpace("FullPhsp", pidmometa_phsp, ntr_phsp) 

infile = TFile.Open(infilename)
tree = infile.Get(intree) 
if not tree :  
  print "Ntuple not found!"
  quit()

kde = BinnedDensity("KDEPDF", phsp, calibfilename)
nentries = tree.GetEntries()

gROOT.ProcessLine("struct MyStruct { \
  Double_t newpid; \
}")
from ROOT import MyStruct, AddressOf

s = MyStruct()

outfile = TFile.Open(outfilename, "RECREATE")
newtree = tree.CloneTree(0)
newtree.Branch(pidvar, AddressOf(s, "newpid"), pidvar + "/D")
infile.cd() 

h = TH1F("h", "h", 100, minpid, pidmax) 
rnd = TRandom3()

from ROOT import std, Double
from math import log

#x_code = compile("i.%s" % pidvar, '<string>', 'eval')
pid_code = compile(transform_backward, '<string>', 'eval')
pt_code = compile("log(i.%s)" % ptvar, '<string>', 'eval')
eta_code = compile("i.%s" % etavar, '<string>', 'eval')
ntracks_code = compile("log(i.%s)" % ntrvar, '<string>', 'eval')

n = 0
for i in tree : 
  point = std.vector(Double)(4) 
  point[0] = (pidmin + pidmax)/2.
  point[1] = eval(pt_code)
  point[2] = eval(eta_code)
  point[3] = eval(ntracks_code) 

  h.Reset() 
  kde.slice(point, 0, h, False) 

  if h.Integral() > 0 : 
    x = h.GetRandom()
  else : 
    x = minpid + (pidmax-minpid)*rnd.Rndm()

  s.newpid = eval(pid_code)
  
  newtree.Fill() 

  if (n % 1000 == 0) : 
    print "Event %d/%d : Pt=%f, Eta=%f, Ntr=%d, PIDGen=%f" % \
       (n, nentries, point[1], point[2], point[3], \
        s.newpid)

  n += 1

outfile.cd() 
newtree.Write() 
infile.Close() 
outfile.Close() 
