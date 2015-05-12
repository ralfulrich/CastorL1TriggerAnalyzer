import FWCore.ParameterSet.Config as cms

#run_path = '/store/group/phys_heavyions/katkov/cas_loc_2013/'
#run_number = 229479

run_number = 242871
#241423
#239821
#239754

import os
base_path = os.getenv('CMSSW_BASE', 'empty_defualt_value')
print 'CMSSW_BASE: {0}'.format(base_path) 

process = cms.Process("PEDS")
process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/854/00000/645B0043-8FF5-E411-BCBE-02163E01355D.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/847/00000/46B6AB23-85F5-E411-B567-02163E0123BB.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/786/00000/628A9296-22F5-E411-82C5-02163E012904.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/779/00000/CE644403-FAF4-E411-B74C-02163E011B13.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/740/00000/5E3EECEC-CCF4-E411-924B-02163E01395B.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/679/00000/D4B53161-5DF4-E411-BB7E-02163E011813.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/677/00000/9E94601C-52F4-E411-8C08-02163E012A6C.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/671/00000/52B6B1D9-4AF4-E411-A261-02163E012904.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/506/00000/2C884B8C-58F3-E411-8D57-02163E013750.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/244/007/00000/34C3CC4F-72F7-E411-9E65-02163E01263D.root',
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/939/00000/D27105EC-5BF6-E411-9ECF-02163E0133F2.root',

        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/243/864/00000/228CA838-99F5-E411-958A-02163E0123BB.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/243/864/00000/34B1E23D-96F5-E411-99A5-02163E0123BB.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/243/864/00000/60F7F480-97F5-E411-8958-02163E011D0B.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/243/864/00000/72712685-99F5-E411-AF71-02163E0118AF.root',

          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/0810E099-FDF2-E411-893E-02163E0134FF.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/341DC976-FEF2-E411-A4B0-02163E012387.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/34647C6A-01F3-E411-B1D5-02163E013585.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/34E65DA4-FAF2-E411-A054-02163E01390F.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/3ACC76AF-03F3-E411-80D6-02163E0118AF.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/3E85789B-FEF2-E411-91DB-02163E011873.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/4856E06E-01F3-E411-8FFB-02163E0138F3.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/5E4CA49D-FDF2-E411-92FE-02163E01274C.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/6842BCBF-FFF2-E411-9604-02163E0134FF.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/6E34E6BA-FBF2-E411-9B45-02163E013612.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/80818B6F-01F3-E411-8D45-02163E013918.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/885E6F6F-01F3-E411-8E98-02163E0133A2.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/8E6C016A-01F3-E411-931E-02163E013392.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/8E839C94-01F3-E411-AE04-02163E0133F2.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/92144A97-FDF2-E411-B0E6-02163E0126E7.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/9EE73375-01F3-E411-B16D-02163E0134EB.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/A242AABF-FFF2-E411-B8D2-02163E0134EB.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/A45BC375-01F3-E411-8243-02163E0133D9.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/B8E4FDB2-00F3-E411-8BEC-02163E011808.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/CCE01688-02F3-E411-98D5-02163E0138F3.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/D29BB0B3-03F3-E411-BE0C-02163E0134EB.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/D40000A0-FCF2-E411-AEF7-02163E0118AF.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/D6E701DB-03F3-E411-BB9D-02163E013909.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/D8348EA7-FCF2-E411-991B-02163E011A2A.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/DC5C369B-FDF2-E411-8C5A-02163E013723.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/E03435BE-FFF2-E411-912B-02163E0126E7.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/E4A30B73-01F3-E411-BB0B-02163E01367D.root',
          # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/243/479/00000/FAB75C70-01F3-E411-BC93-02163E01289B.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/754/00000/94E8E718-75DB-E411-9D0E-02163E0123CC.root'
        # 'file:/usr/users/ikatkov/hiforest/CMSSW_4_4_2_patch7/test/skim_conformal_test.root'
        # 'file:/storage/5/cbaus/RECO/PbPb_1380_eposLHC_HI44/job_N5_10.root'
    )
)

# process.source = cms.Source("HcalTBSource",
#    streams = cms.untracked.vstring('HCAL_Trigger', 
#                                    'HCAL_DCC690',
#                                    'HCAL_DCC691',
#                                    'HCAL_DCC692'),
#     # fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_242871.root')
#     # fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_242872.root')
#     # fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_242879.root')
#     fileNames = cms.untracked.vstring('file:/tmp/cwohrman/USC_244162.root')
# )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000) #10000
)

process.castorDigis = cms.EDProducer("CastorRawToDigi",
   CastorFirstFED = cms.int32(690),
   FilterDataQuality = cms.bool(True),
   ExceptionEmptyData = cms.untracked.bool(True),
   InputLabel = cms.InputTag("rawDataCollector"),
   # InputLabel = cms.InputTag("source"),
   #UnpackCalib = cms.untracked.bool(False),
   # castor technical trigger processor
   UnpackTTP = cms.bool(True),
   FEDs = cms.untracked.vint32(690,691,692),
   lastSample = cms.int32(9),
   firstSample = cms.int32(0),
   CastorCtdc = cms.bool(False),
   UseNominalOrbitMessageTime = cms.bool(True),
   ExpectedOrbitMessageTime = cms.int32(-1)#,
   # Do not complain about missing FEDs
   #ComplainEmptyData = cms.untracked.bool(False),
)

process.dumpRaw = cms.EDAnalyzer( "DumpFEDRawDataProduct",

   #feds = cms.untracked.vint32( 690,691,692,693 ),
                              feds = cms.untracked.vint32(
                                  23, #BPIX
                                  32, #FPIX
                                  628, #EB+
                                  610, #EB-
                                  557, #ES+
                                  546, #ES-
                                  149, #TIBTID
                                  220, #TEC-
                                                          300, #TEC+
                                                          474, #TOB
                                                          690,691,692,693, #CASTOR-ZDC
                                                          700,#701,702,703,704,705, # HBHEa
                                                          706,#707,708,709,710,711, # HBHEb
                                                          712,#713,714,715,716,717, # HBHEc
                                                          718,  # HF
                                                          1118, #HF uTCA
                                                          724,#725,726,727,         # HO
                                                          #728,729,730,731,         # HO
                                                          735,                     # SCAL
                                                          770,#771,     # DT-
                                                          772,          # DT0
                                                          773,#774,     # DT+
                                                          790, #RPC
                                                          812,#813,745,             # TRG
                                                          841,#831,832,833,834,     # CSC+
                                                          #835,836,837,838,         # CSC+
                                                          #840,841,842,843,844,     # CSC+
                                                          #845,846,847,848,         # CSC+
                                                          851,#851,852,853,854,     # CSC-
                                                          #855,856,857,858,         # CSC-
                                                          #860,861,862,863,864,     # CSC-
                                                          #865,866,867,868,         # CSC-
                                                          760,      # CSCTF
                                                          1024                     # TCDS
                                                          ),
   #dumpPayload = cms.untracked.bool( True ),
   label = cms.untracked.string('rawDataCollector')
)

process.m = cms.EDAnalyzer("HcalDigiDump")

process.dump = cms.EDAnalyzer('HcalTBObjectDump',
                              hcalTBTriggerDataTag = cms.InputTag('tbunpack'),
                              hcalTBRunDataTag = cms.InputTag('tbunpack'),
                              hcalTBEventPositionTag = cms.InputTag('tbunpack'),
                              hcalTBTimingTag = cms.InputTag('tbunpack')
)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_P_V49::All'


#################################################################################################################################
#################################################################################################################################
process.castorl1test = cms.EDAnalyzer('CastorTTPTest',
    debugInfo = cms.bool(True),
    ShowTriggerMenu = cms.bool(False)
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
# process.MessageLogger = cms.Service("MessageLogger",
#                                     destinations   = cms.untracked.vstring('detailedInfo', 'critical', 'cerr'),
#                                     critical       = cms.untracked.PSet(threshold = cms.untracked.string('ERROR'),filename = cms.untracked.string('critical.log')),
#                                     detailedInfo   = cms.untracked.PSet(threshold = cms.untracked.string('INFO'),filename = cms.untracked.string('cinfo.log')),
#                                     cerr           = cms.untracked.PSet(threshold = cms.untracked.string('WARNING'),filename = cms.untracked.string('cerr.log'))
#                                     )
process.MessageLogger.cerr.FwkReport.reportEvery = 5000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#################################################################################################################################

process.p = cms.Path(
                     process.castorDigis*
                     process.castorl1test)

