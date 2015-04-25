#! /usr/bin/env python
#
import os
import subprocess
import shlex


#listcommand = "lcg-ls -c 500 -o 0 srm://dcache-se-cms.desy.de:8443/srm/managerv2'?'SFN=/pnfs/desy.de/cms/tier2/store/user/cwohrman/SimCastorL1StudyMkTree_RecoMkTree_QCD_15_30/"
listcommand = "lcg-ls -c 500 -o 1000 srm://dcache-se-cms.desy.de:8443/srm/managerv2'?'SFN=/pnfs/desy.de/cms/tier2/store/user/cwohrman/SimCastorL1StudyMkTree_RecoMkTree_MinBias/"

# for HF stuff
#listcommand = "lcg-ls -c 500 -o 0 srm://dcache-se-cms.desy.de:8443/srm/managerv2'?'SFN=/pnfs/desy.de/cms/tier2/store/user/cwohrman/SimCastorL1StudyMkTree_RecoMkTree_HF_MinBias/"

copycommand = "lcg-cp srm://dcache-se-cms.desy.de:8443/srm/managerv2?SFN="

# list files with inname
p = subprocess.Popen(listcommand,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
# readout standard output
stmp = p.stdout.read()
flist = sorted(shlex.split(stmp),key=str.lower)

for name in flist:
	target = "/tmp/cwohrman/" + name[name.rfind('/')+1:]
	# target = "/afs/cern.ch/work/c/cwohrman/CastorTriggerL1EmulationTest/CMSSW_7_2_0_pre6/src/docrab_Reco_And_MkTree/crab_qcd_50_80/output/" + name[name.rfind('/')+1:]
	command = copycommand + name + " " + target
 	print command
 	os.system(command)
