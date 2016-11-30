############################
import subprocess
import os
#dvVersion   = "v33r9"
dvVersion   = "v37r2p2"
#app = DaVinci(version=dvVersion)
filesPerJob = 20   #def = 20
maxFiles = 10000000
CPUTime     = 60*60*15
jobName     = "D11"
outputfile  = "tuple.root"
summaryfile = "summary.xml"
inputdir = '/afs/cern.ch/user/s/sblusk/Xibc/XiccMu/'
backend=Dirac()
#backend=Local()
backend.settings['CPUTime'] = CPUTime
splitter = SplitByFiles(filesPerJob=filesPerJob, maxFiles = maxFiles)


# Inputs that may change with datatype, year, etc
year = "2011"
pol = 1  # -1 is down, +1 = up
simulation = False


if simulation:
    year = "2012"

#############################################################
def getMCDataSet(pol):
        
    #DecID = "16265034"   # Omegab-->Omega_c pi

    #DecID = "15264011"   # Lb-->LcPi
    #DecID = "16265033"   # Xib->LbPi, Lb-->LcPi, sim = sim08g
    #DecID = "16265024"   # Sigmab -> LbPi, Lb-->LcPi, sim = sim08f
    
    #DecID = "16265025"    #Sigma_b --> Lb Pi
    #DecID = "15146120"   # Lb-->Jpsi p Ks pi sim08f, Digi13
    #DecID = "15144103"   # Lb-->Jpsi Lambda, Lambda-> p pi   sim08a, Digi13
    #DecID = "16145133"   # Xib- ->Jpsi Xi-, Xi- -> Lambda pi, Lambda-> p pi   sim08a, Digi13

    #DecID = "16176060"  #Xibc ->J/psi Xi_c+ (BUG in dev version)
    #DecID = "16275062"   # Xibc -> J/psi Lambda_c+   sim09a, Digi13, Reco14c
    #DecID = "16275061"   # Xibc -> J/psi Xi_c+   sim09a, Digi13, Reco14c
    #DecID = "16276060"   # Xibc -> J/psi Lambda_c+ K-  sim09a, Digi13, Reco14c
    #DecID = "16675060"   # Xibc -> Xicc++ mu nu, Xicc++ _> Xic+ pi+
    #DecID = "16677060"   # Xibc -> Xicc++ mu nu, Xicc++ _> Lc+ K+ pi- pi+
    #DecID = "16676060"   # Xibc -> Xicc+ mu nu, Xic++ _> Xic0 pi+
    #DecID = "16676061"   # Xibc -> Xicc+ mu nu, Xicc++ _> Lc+ K- pi+
    DecID = "16576061"   # Xibc -> Xicc+ mu nu, Xicc++ _> D+ p K- 
    
    sim = "Sim08f"
    vStrip = "20"
    vReco = "Reco14a"
    Gen = "Pythia8"

    if DecID == "16265034":
        sim = "Sim08h"
        vStrip = "21"
        vReco = "Reco14c"
    elif DecID == "15144103" or DecID == "16145133" :
        sim = "Sim08a"
        vStrip = "20"
        vReco = "Reco14a"
    elif DecID == "16275062" or DecID == "16275061" or DecID == "16276060":
        sim = "Sim09a"
        vStrip = "21"
        vReco = "Reco14c"
        Gen = "GenXiccPythia8"
    elif DecID == "16675060" or DecID == "16677060" or DecID == "16676060" or DecID == "16676061" or DecID == "16576061":
        sim = "Sim09a"
        vStrip = "21r0p1"
        vReco = "Reco14c"
        Gen = "GenXiccPythia8"                                
                

    dataDown = "/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-"+Gen+"/"+sim+"/Digi13/Trig0x409f0045/"+vReco+"/Stripping"+vStrip+"NoPrescalingFlagged/"
    dataUp = "/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-"+Gen+"/"+sim+"/Digi13/Trig0x409f0045/"+vReco+"/Stripping"+vStrip+"NoPrescalingFlagged/"

    if Gen == "GenXiccPythia8" :
        dataDown = "/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-GenXiccPythia8/"+sim+"/Trig0x409f0045/"+vReco+"/Stripping"+vStrip+"NoPrescalingFlagged/"
        dataUp = "/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-GenXiccPythia8/"+sim+"/Trig0x409f0045/"+vReco+"/Stripping"+vStrip+"NoPrescalingFlagged/"


    DSTFileName = "ALLSTREAMS.DST"
    if pol<0 :
        data = dataDown + DecID + "/" + DSTFileName
        name = "j"+DecID+"Dn"
    if pol>0 :
        data = dataUp + DecID + "/" + DSTFileName
        name = "j"+DecID+"Up"
    return data,name
#############################################################


#############################################################
def getDataSet(year,pol):
        
    stripVer2012 = "21r0p1a"     #re-strip #3 stripping (2012)
    stripVer2011 = "21r1p1a"     #re-strip #2 (2011)

    stream = 'SEMILEPTONIC.DST'

    #--- 2012 data (reco 14)
    data2012MagDown = 'LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping'+stripVer2012+'/90000000/'+stream
    data2012MagUp = 'LHCb/Collision12/Beam4000GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping'+stripVer2012+'/90000000/'+stream
    #--- 2011 data (reco 14)
    data2011MagDown = 'LHCb/Collision11/Beam3500GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping'+stripVer2011+'/90000000/'+stream
    data2011MagUp = 'LHCb/Collision11/Beam3500GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping'+stripVer2011+'/90000000/'+stream

    if year == "2012":
        if pol < 0:
            data = data2012MagDown
            name = "d2012Dn"
        if pol > 0:
            data = data2012MagUp
            name = "d2012Up"
    elif year == "2011":
        if pol < 0:
            data = data2011MagDown
            name = "d2011Dn"
        if pol > 0:
            data = data2011MagUp
            name = "d2011Up"

    return data,name


#############################################################

jobname = jobName
if simulation:
    data,jobname = getMCDataSet(pol)
else:
    data,jobname = getDataSet(year,pol)

InputData = BKQuery( path = data, dqflag=['ALL']).getDataset()


print "*****************************************************************************************************************************"
if simulation:
    print "*  Processing simulated data, year = ",year," ... polarity = ", pol
else:
    print "*  Processing real data, year = ", year, " data, ... polarity = ",pol
print "*  Data = ",data
print "*****************************************************************************************************************************"


j = Job(name=jobname, application=DaVinci(version=dvVersion), backend=backend, inputdata=InputData, splitter=splitter)

if simulation:
    if data.find("MagDown"):
        j.application.optsfile = [File(inputdir+'isSimulationDown.py'), File(inputdir+'Data2012.py'), File(inputdir+'DataXibc.py')]
    else:
        j.application.optsfile = [File(inputdir+'isSimulationUp.py'), File(inputdir+'Data2012.py'), File(inputdir+'DataXibc.py')]        
else:
    if year == "2011":
        j.application.optsfile = [File(inputdir+'isNotSimulationDown.py'), File(inputdir+'Data2011.py'), File(inputdir+'DataXibc.py')]
    else:
        j.application.optsfile = [File(inputdir+'isNotSimulationDown.py'), File(inputdir+'Data2012.py'), File(inputdir+'DataXibc.py')]
        
#j.outputfiles = [SandboxFile(namePattern='*.root')]
j.outputfiles = [DiracFile('tuple.root')]

#if simulation == False:
#    j.parallel_submit = True

j.do_auto_resubmit = True

j.splitter.bulksubmit = False
#j.submit()
queues.add(j.submit)

