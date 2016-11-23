import os, sys

#run like this: 
#> ganga get_dirac_data.py 34 dirac_job_tuple.root outfilename 
#                                                         (outfilename w/o .root)
#
# run this from the /tmp/adendek/ area
#

jid = int(sys.argv[1])
print "Job = ", jid


diracname = sys.argv[2]
oname = sys.argv[3]
j = jobs(jid)
for js in j.subjobs:
    #if js.id != 1: continue
    print js.id, js.status, js.backend.status
    #if js.id==61: continue
    if js.status=='completed' and os.path.exists(str(js.id)+"_"+oname + "." + diracname.split('.')[-1])==False:
        print "downloading........................"
        ds = js.backend.getOutputDataLFNs()
        f = ds
        if len(f)==0:
            print "no output files: " + repr(f)
            print "some problem"
            continue
        try:
            DiracFile(lfn=f[0],localDir='/tmp/adendek').get()
            #f[0].download()
        except:
            print "unexpected error", sys.exc_info()[0]
            #js.resubmit()
            continue
        
        name = str(js.id) + "_" + oname + "." + diracname.split('.')[-1]
        print name, diracname
        #name = "./new/" + name
        os.rename(diracname, name)
        print "renaming %s --> %s"%(diracname, name)
    elif js.status=='completed' and os.path.exists(oname+"_"+str(js.id)+".root")==True:
        print "....................is already downloaded"

