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

##process.source = cms.Source("PoolSource",
##    fileNames = cms.untracked.vstring(
##'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/754/00000/94E8E718-75DB-E411-9D0E-02163E0123CC.root'
#        #'file:/usr/users/ikatkov/hiforest/CMSSW_4_4_2_patch7/test/skim_conformal_test.root'
#        'file:/storage/5/cbaus/RECO/PbPb_1380_eposLHC_HI44/job_N5_10.root'
##    )
##)

process.source = cms.Source("HcalTBSource",
   streams = cms.untracked.vstring('HCAL_Trigger', 
                                   'HCAL_DCC690',
                                   'HCAL_DCC691',
                                   'HCAL_DCC692'),
    fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_242871.root')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1) #10000
)

process.castorDigis = cms.EDProducer("CastorRawToDigi",
   CastorFirstFED = cms.int32(690),
   FilterDataQuality = cms.bool(True),
   ExceptionEmptyData = cms.untracked.bool(True),
   # InputLabel = cms.InputTag("rawDataCollector"), #source #rawDataCollector
   InputLabel = cms.InputTag("source"), #source #rawDataCollector
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
    ShowTriggerMenu = cms.bool(True)
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
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#################################################################################################################################

process.p = cms.Path(
                     process.castorDigis*
                     process.castorl1test)

