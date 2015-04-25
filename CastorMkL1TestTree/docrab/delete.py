#! /usr/bin/env python
#
import os
import subprocess
import shlex

#listcommand = "lcg-ls -c 500 -o 0 srm://dcache-se-cms.desy.de:8443/srm/managerv2'?'SFN=/pnfs/desy.de/cms/tier2/store/user/cwohrman/SimCastorL1StudyMkTree_RecoMkTree_QCD_30_50/"
listcommand = "lcg-ls -c 500 -o 0 srm://dcache-se-cms.desy.de:8443/srm/managerv2'?'SFN=/pnfs/desy.de/cms/tier2/store/user/cwohrman/SimCastorL1StudyMkTree_RecoMkTree_MinBias/"
deletcommand = "lcg-del -b -v -l -D srmv2 srm://dcache-se-cms.desy.de:8443/srm/managerv2?SFN="

# list files with inname
p = subprocess.Popen(listcommand,shell=True,stdin=subprocess.PIPE,stdout=subprocess.PIPE)
# readout standard output
stmp = p.stdout.read()

for name in shlex.split(stmp):
	command = deletcommand + name
	print command
	os.system(command)

