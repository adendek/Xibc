############################
import subprocess
import os
#dvVersion   = "v33r9"
#dvVersion   = "v37r2p2"
dvVersion = "v41r3"
#app = DaVinci(version=dvVersion)
filesPerJob = 20   #def = 20
maxFiles = 1000000
CPUTime     = 60*60*15
jobName     = "D16"
outputfile  = "tuple.root"
summaryfile = "summary.xml"
inputdir = '/afs/cern.ch/user/z/zhli/Work/Xibc/X2D0pY/'
backend=Dirac()
backend.settings['CPUTime'] = CPUTime
splitter = SplitByFiles(filesPerJob=filesPerJob, maxFiles = maxFiles, ignoremissing = True)


# Inputs that may change with datatype, year, etc
year = "2016"
pol = -1  # -1 is down, +1 = up
simulation = False


if simulation:
    year = "2016"

# main options file
python_options = 'My2016Lb0.py'


#############################################################
def getMCDataSet(pol):
    DecID =  "15204011"


    if DecID == "15204011":
        sim = "Sim09a"
        vStrip = "26"
        vReco = "Reco16"
            

    dataDown = "/MC/2016/Beam6500GeV-Summer2016-MagDown-Nu1.6-25ns-Pythia8/"+sim+"/Trig0x61321609/"+vReco+"Turbo02/Stripping"+vStrip+"NoPrescalingFlagged/"
    dataUp = "/MC/2016/Beam6500GeV-Summer2016-MagUp-Nu1.6-25ns-Pythia8/"+sim+"/Trig0x61321609/"+vReco+"Turbo02/Stripping"+vStrip+"NoPrescalingFlagged/"
       


    DSTFileName = "ALLSTREAMS.MDST"
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
        
    stream = "BHADRON.MDST"

    #--- 2016 data (reco 16)
    data2016MagDown = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/'+stream
    data2016MagUp   = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/'+stream
    #data2016MagUp   = '/lhcb/LHCb/Collision16/BHADRON.MDST/00052200/0000/00052200_00000258_1.bhadron.mdst'

    if year == "2016":
       if pol < 0:
            data = data2016MagDown
            name = "d2016Dn"
       if pol > 0:
            data = data2016MagUp
            name = "d2016Up"

    return data,name


#############################################################

jobname = jobName
if simulation:
    data,jobname = getMCDataSet(pol)
else:
    data,jobname = getDataSet(year,pol)

InputData = BKQuery( path = data, dqflag=['ALL'],type = "Path").getDataset()


print "*****************************************************************************************************************************"
if simulation:
    print "*  Processing simulated data, year = ",year," ... polarity = ", pol
else:
    print "*  Processing real data, year = ", year, " data, ... polarity = ",pol
print "*  Data = ",data
print "*****************************************************************************************************************************"


j = Job(name=jobname, application=DaVinci(version=dvVersion), backend=backend, inputdata=InputData, splitter=splitter)

if simulation:
    if data.find("MagDown")>0:
        j.application.optsfile = [File(inputdir+'isSimulationDown.py'), File(inputdir+'Data2016.py'), File(inputdir+python_options)]
    else:
        j.application.optsfile = [File(inputdir+'isSimulationUp.py'), File(inputdir+'Data2016.py'), File(inputdir+python_options)]        
else:
    if year == "2016":
        j.application.optsfile = [File(inputdir+'isNotSimulationDown.py'), File(inputdir+'Data2016.py'), File(inputdir+python_options)]
    else:
        j.application.optsfile = [File(inputdir+'isNotSimulationDown.py'), File(inputdir+'Data2012.py'), File(inputdir+python_options)]
        
#j.outputfiles = [SandboxFile(namePattern='*.root')]
j.outputfiles = [DiracFile('tuple.root')]

if simulation == False:
    j.parallel_submit = True

j.do_auto_resubmit = True

j.splitter.bulksubmit = False
#queues.add(j.submit)
j.submit()

