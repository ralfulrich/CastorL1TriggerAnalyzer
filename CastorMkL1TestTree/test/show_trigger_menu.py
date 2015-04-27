# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: FullReco --step DIGI,L1,DIGI2RAW,HLT:50nsGRun,RAW2DIGI,L1Reco,RECO --conditions auto:run2_mc_50ns --pileup NoPileUp --datamix NODATAMIXER --eventcontent RECOSIM --datatier GEN-SIM-RECO --filein=file:SIM.root --fileout=file:FullReco_Test_RECOSIM.root --mc --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_50ns --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

#################################################################################################################################
#################################################################################################################################
# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Input source
process.source = cms.Source("PoolSource",
    # fileNames = cms.untracked.vstring('root://xrootd-cms.infn.it//store/hidata/HIRun2013A/MinimumBias/RAW/v1/000/209/649/54F188C3-3C5C-E211-A125-001D09F253C0.root'),
    fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_raw_2015/241423_ls179to266_likelyLHCclock_castimequasifin10ts_1800V_B0T_BeamsInLHC_unpacked.root'),
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.options = cms.untracked.PSet(

)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
import CastorL1TriggerAnalyzer.CastorMkL1TestTree.CastorMkL1TestTree_cfi
process.castormkl1testtree = CastorL1TriggerAnalyzer.CastorMkL1TestTree.CastorMkL1TestTree_cfi.castormkl1testtree.clone()
process.castormkl1testtree.ShowDebugInfo    = cms.bool(True)
process.castormkl1testtree.OnlyCheckTrigger = cms.bool(True)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("ShowTriggerMenu.root"),
    closeFileFast = cms.untracked.bool(True)
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V50', '')
print process.GlobalTag.globaltag
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Path and EndPath definitions
process.mktree_step = cms.EndPath(process.castormkl1testtree)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Schedule definition
process.schedule = cms.Schedule(process.mktree_step)
#################################################################################################################################
