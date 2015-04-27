# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: reco --step DIGI,L1,DIGI2RAW,HLT,RAW2DIGI,L1Reco,RECO cmsDriver.py reco --step DIGI,L1,DIGI2RAW,HLT,RAW2DIGI,L1Reco,RECO --conditions auto:mc --pileup NoPileUp --datamix NODATAMIXER --eventcontent RECOSIM --datatier GEN-SIM-RECO --filein=file:SIM.root --fileout=file:RECO.root --no_exec
import FWCore.ParameterSet.Config as cms
import sys

process = cms.Process('TTP')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
# process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
# process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
# process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
# process.load('Configuration.StandardSequences.MagneticField_38T_cff')
# process.load('Configuration.StandardSequences.Digi_cff')
# process.load('Configuration.StandardSequences.SimL1Emulator_cff')
# process.load('Configuration.StandardSequences.DigiToRaw_cff')
# process.load('HLTrigger.Configuration.HLT_GRun_cff')
# #process.load('HLTrigger.Configuration.HLT_SpecialTest_cff')
# process.load('Configuration.StandardSequences.RawToDigi_cff')
# process.load('Configuration.StandardSequences.L1Reco_cff')
# process.load('Configuration.StandardSequences.Reconstruction_cff')
# process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/c/cwohrman/CastorTriggerL1EmulationTest/ForTestMuonTriggerWithTTPDigi/CMSSW_7_3_2/src/239754_unpacked.root')
    # fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/Commissioning2015_MinimumBias_RAW_v1_000_239874_00000_22C8434B-1DDD-E411-B698-02163E013810_unpacked.root')
    # fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/Commissioning2015_MinimumBias_RAW_v1_000_239821_00000_D6B7A994-75DC-E411-92A7-02163E01354D_circbeamslumis_unpacked.root')
    #fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/m/makbiyik/public/UPC_event_Hiskim/CMSSW_5_3_20/src/ConvertStarlightToLHE/OneTrigger/1st_STEP_py_GEN_SIM_50_100.root')
    #fileNames = cms.untracked.vstring('file:/afs/cern.ch/user/c/cwohrman/public/forigor/reco_pion_E1To1000GeV_1.root')
    #fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/c/cwohrman/CastorTriggerL1EmulationTest/CMSSW_7_2_0_pre6/src/test/pion_E1To1000GeV/pg_pion_E1To1000GeV_9.root')
    #fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/c/cwohrman/CastorTriggerL1EmulationTest/CMSSW_7_2_0_pre6/src/test/RAW.root')

    # splash beam1,hv900,cms gloabl clock:
        # fileNames = cms.untracked.vstring('/afs/cern.ch/user/k/katkov/afswork/hiforest/Tmp/CMSSW_7_3_0_pre2/src/CalibCalorimetry/CastorCalib/test/239895b1_unpacked.root')
    # splash beam2,hv900, cms global clock:
        # fileNames = cms.untracked.vstring('/afs/cern.ch/user/k/katkov/afswork/hiforest/Tmp/CMSSW_7_3_0_pre2/src/CalibCalorimetry/CastorCalib/test/239895b2_unpacked.root'),
    # circulating beams last night ?, hv1800 ?, cms gloabl clock?:
        # fileNames = cms.untracked.vstring('/afs/cern.ch/user/k/katkov/afswork/hiforest/Tmp/CMSSW_7_3_0_pre2/src/CalibCalorimetry/CastorCalib/test/240070_unpacked.root')
)

# process.options = cms.untracked.PSet(

# )

# Production Info
# process.configurationMetadata = cms.untracked.PSet(
#     version = cms.untracked.string('$Revision: 1.19 $'),
#     annotation = cms.untracked.string('reco nevts:1'),
#     name = cms.untracked.string('Applications')
# )

# Output definition

# process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
#     splitLevel = cms.untracked.int32(0),
#     eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
#     # outputCommands = process.RECOSIMEventContent.outputCommands,
#     outputCommands = cms.untracked.vstring(
#         'drop *', 
#         'keep *_genParticles_*_*',
#         'keep *_generator_*_*',
#         'keep *_TriggerResults_*_*',
#         'keep *_ak5GenJets_*_*',
#         'keep *_castorreco_*_*',
#         'keep *_ak7BasicJets_*_*',
#         'keep *_ak7CastorJetID_*_*',
#         'keep *_CastorTowerReco_*_*',
#         'keep *_hltL1GtObjectMap_*_*',
#         'keep *_l1L1GtObjectMap_*_*',
#         'keep *_gtDigis_*_*',
#         'keep *_ecalTPSkim_*_*',
#         'keep *_hltScalersRawToDigi_*_*',
#         'keep *_scalersRawToDig_*_*',
#         'keep *_hltTriggerSummaryAOD_*_*',
#     ),
#     fileName = cms.untracked.string('file:reco_MC_MinBias.root'),
#     dataset = cms.untracked.PSet(
#         filterName = cms.untracked.string(''),
#         dataTier = cms.untracked.string('GEN-SIM-RECO')
#     )
# )

# Additional output definition

#################################################################################################################################
#################################################################################################################################
process.castorl1test = cms.EDAnalyzer('CastorTTPTest',
    debugInfo = cms.bool(True)
    # PileUpInfo       = cms.InputTag('addPileupInfo','','HLT'),
    # GenPartColl      = cms.InputTag('genParticles'),
    # GenJetColl       = cms.InputTag('ak4GenJets'),
    # CaloTowerColl    = cms.InputTag('towerMaker'),
    # HadFwdRecHitColl = cms.InputTag('hfreco'),
    # CasRecHitColl    = cms.InputTag('castorreco'),
    # BasicJetColl     = cms.InputTag('ak7BasicJets'),
    # CastorJetID      = cms.InputTag('ak7CastorJetID'),
    # TrigResults      = cms.InputTag('TriggerResults','','HLT2'),
    # VertexColl       = cms.InputTag('offlinePrimaryVertices')
)
#################################################################################################################################



#################################################################################################################################
#################################################################################################################################
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("TestTTP.root"),
    closeFileFast = cms.untracked.bool(True)
)
#################################################################################################################################




#################################################################################################################################
#################################################################################################################################
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger",
    destinations   = cms.untracked.vstring('detailedInfo', 'critical', 'cerr'),
    categories     = cms.untracked.vstring('eventNumber'),
    critical       = cms.untracked.PSet(threshold = cms.untracked.string('ERROR')),
    detailedInfo   = cms.untracked.PSet(threshold = cms.untracked.string('INFO')),
    cerr           = cms.untracked.PSet(threshold = cms.untracked.string('WARNING'))
)
#################################################################################################################################




# #################################################################################################################################
# #################################################################################################################################
# # specify the correct database tag which contains the updated channelquality flags
# process.load("CondCore.DBCommon.CondDBSetup_cfi")
# process.CastorDbProducer = cms.ESProducer("CastorDbProducer")
# process.es_pool = cms.ESSource("PoolDBESSource",
#     process.CondDBSetup,
#     timetype = cms.string('runnumber'),
#     connect = cms.string('frontier://cmsfrontier.cern.ch:8000/FrontierProd/CMS_COND_HCAL_000'),
#     authenticationMethod = cms.untracked.uint32(0),
#     toGet = cms.VPSet(
#         cms.PSet(
#             record = cms.string('CastorGainsRcd'),
#             tag = cms.string('CastorGains_HI_v2.3_mc')
#         )
#     )
# )
# process.es_prefer_castor = cms.ESPrefer('PoolDBESSource','es_pool')
# # end of Db configuration
# #################################################################################################################################


# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_hlt_GRun', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V49::All', '')
print process.GlobalTag.globaltag

# # Path and EndPath definitions
# process.digitisation_step = cms.Path(process.pdigi)
# process.L1simulation_step = cms.Path(process.SimL1Emulator)
# process.digi2raw_step = cms.Path(process.DigiToRaw)
# process.raw2digi_step = cms.Path(process.RawToDigi)
# process.simraw2digi_step = cms.Path(process.RawToDigi)
# process.L1Reco_step = cms.Path(process.L1Reco)
# process.reconstruction_step = cms.Path(process.reconstruction)
# process.endjob_step = cms.EndPath(process.endOfProcess)
# # process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)
# process.MkL1Tree_step = cms.Path(process.castorl1test)

process.p = cms.Path(process.castorl1test)

# # Schedule definition
# process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
# #process.schedule = cms.Schedule(process.raw2digi_step,process.L1simulation_step) #,process.digi2raw_step)
# process.schedule.extend(process.HLTSchedule)
# #process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.MkL1Tree_step])
# #process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step])
# process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.MkL1Tree_step])

# # customisation of the process.

# # Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
# from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

# #call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
# process = customizeHLTforMC(process)

# # Automatic addition of the customisation function from HLTrigger.Configuration.CustomConfigs
# from HLTrigger.Configuration.CustomConfigs import L1THLT 

# #call to customisation function L1THLT imported from HLTrigger.Configuration.CustomConfigs
# process = L1THLT(process)

# # # Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
# # from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

# # #call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
# # process = customisePostLS1(process)

# # from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT#Running_the_HLT_with_CMSSW_7_AN1
# process.hltCsc2DRecHits.wireDigiTag  = cms.InputTag("simMuonCSCDigis","MuonCSCWireDigi")
# process.hltCsc2DRecHits.stripDigiTag = cms.InputTag("simMuonCSCDigis","MuonCSCStripDigi")
# # End of customisation functions

