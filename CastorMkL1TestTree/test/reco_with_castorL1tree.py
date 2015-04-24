# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: FullReco --step DIGI,L1,DIGI2RAW,HLT:50nsGRun,RAW2DIGI,L1Reco,RECO --conditions auto:run2_mc_50ns --pileup NoPileUp --datamix NODATAMIXER --eventcontent RECOSIM --datatier GEN-SIM-RECO --filein=file:SIM.root --fileout=file:FullReco_Test_RECOSIM.root --mc --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_50ns --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT2')

#################################################################################################################################
#################################################################################################################################
# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_50nsGRun_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
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
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/c/cwohrman/CastorTriggerL1EmulationTest/ForDQM_HLT/CMSSW_7_4_0/src/test/RunIIWinter15GS_QCD_Pt-15to3000_castorJet_TuneCUETP8M1_Flat_13TeV-pythia8_GEN-SIM_castor_MCRUN2_71_V0-v1_10000_00187BAF-43D9-E411-87A6-0025904C656A.root'),
    inputCommands = cms.untracked.vstring('keep *', 
        'drop *_genParticles_*_*', 
        'drop *_genParticlesForJets_*_*', 
        'drop *_kt4GenJets_*_*', 
        'drop *_kt6GenJets_*_*', 
        'drop *_iterativeCone5GenJets_*_*', 
        'drop *_ak4GenJets_*_*', 
        'drop *_ak7GenJets_*_*', 
        'drop *_ak8GenJets_*_*', 
        'drop *_ak4GenJetsNoNu_*_*', 
        'drop *_ak8GenJetsNoNu_*_*', 
        'drop *_genCandidatesForMET_*_*', 
        'drop *_genParticlesForMETAllVisible_*_*', 
        'drop *_genMetCalo_*_*', 
        'drop *_genMetCaloAndNonPrompt_*_*', 
        'drop *_genMetTrue_*_*', 
        'drop *_genMetIC5GenJs_*_*'),
    secondaryFileNames = cms.untracked.vstring()
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.options = cms.untracked.PSet(

)
#################################################################################################################################

#################################################################################################################################
#################################################################################################################################
# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('FullReco nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
import CastorL1TriggerAnalyzer.CastorMkL1TestTree.CastorMkL1TestTree_cfi
process.castormkl1testtree = CastorL1TriggerAnalyzer.CastorMkL1TestTree.CastorMkL1TestTree_cfi.castormkl1testtree.clone()
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("MinBiasL1Tree.root"),
    closeFileFast = cms.untracked.bool(True)
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc_50ns', '')
print process.GlobalTag.globaltag
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.mktree_step = cms.EndPath(process.castormkl1testtree)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.mktree_step])
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_50ns 

#call to customisation function customisePostLS1_50ns imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1_50ns(process)

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
#################################################################################################################################
