import FWCore.ParameterSet.Config as cms

#run_path = '/store/group/phys_heavyions/katkov/cas_loc_2013/'
#run_number = 229479

run_number = 241423
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

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/821/00000/D6B7A994-75DC-E411-92A7-02163E01354D.root',
#'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/895/00000/5246DFEF-92DD-E411-8012-02163E011DF0.root'
#########'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/240/070/00000/1846A2AE-21DF-E411-BB73-02163E011C32.root'
'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/241/423/00000/DE8BBB61-FBEB-E411-A601-02163E0133B6.root' #Lumi: [179, 266]
#    '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/754/00000/94E8E718-75DB-E411-9D0E-02163E0123CC.root', 
#'/store/data/Commissioning2015/MinimumBias/RAW/v1/000/239/754/00000/94E8E718-75DB-E411-9D0E-02163E0123CC.root',
#        #'file:/usr/users/ikatkov/hiforest/CMSSW_4_4_2_patch7/test/skim_conformal_test.root'
#        'file:/storage/5/cbaus/RECO/PbPb_1380_eposLHC_HI44/job_N5_10.root'
    )
#   ,eventsToProcess = cms.untracked.VEventRange('239754:71:128-239754:71:128')  ####################################################
#    ,lumisToProcess = cms.untracked.VLuminosityBlockRange('239821:1-239821:43','239821:76-239821:172','239821:204-239821:248','239821:295-239821:355') #b1&b2
#    ,lumisToProcess = cms.untracked.VLuminosityBlockRange('239821:274-239821:276')#,'239821:282-239821:286') #eg-spike b1 = '239821:275-239821:275' b2 = '239821:284-239821:284'
#     ,lumisToProcess = cms.untracked.VLuminosityBlockRange('239821:282-239821:286')
#      ,lumisToProcess = cms.untracked.VLuminosityBlockRange('239895:620-239895:681')
#      ,lumisToProcess = cms.untracked.VLuminosityBlockRange('239895:770-239895:841')
)

#process.source = cms.Source("HcalTBSource",
#    streams = cms.untracked.vstring('HCAL_Trigger', 
#        'HCAL_DCC690','HCAL_DCC691','HCAL_DCC692', 
#),
    #fileNames = cms.untracked.vstring('/store/caft2/user/campbell/castor_localruns/USC_119814.root')
##    fileNames = cms.untracked.vstring('{0}/USC_{1}.root'.format(run_path,run_number))
    #fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_229479.root')
#)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000) #10000
)

process.castorDigis = cms.EDProducer("CastorRawToDigi",
   CastorFirstFED = cms.int32(690),
   FilterDataQuality = cms.bool(True),
   ExceptionEmptyData = cms.untracked.bool(True),
   InputLabel = cms.InputTag("rawDataCollector"), #source #rawDataCollector
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

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('{0}_unpacked.root'.format(run_number))
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

process.dumpECA = cms.EDAnalyzer("EventContentAnalyzer")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'GR_P_V49::All'
#'GR_P_V50::All' ---> causes crash on raw data of run 239754
#'GR_R_53_LV6::All'#'GR_P_V43D::All'

#####process.CastorDbProducer = cms.ESProducer("CastorDbProducer")

#process.es_hardcode = cms.ESSource("CastorHardcodeCalibrations",
    #toGet = cms.untracked.vstring('Gains', 
        #'Pedestals', 
        #'PedestalWidths', 
        #'GainWidths', 
        #'QIEShape', 
        #'QIEData', 
        #'ChannelQuality', 
        #'RespCorrs', 
        #'ZSThresholds')
#)

#process.es_ascii = cms.ESSource("CastorTextCalibrations",
   #input = cms.VPSet(cms.PSet(
       #object = cms.string('ElectronicsMap'),
       #file = cms.FileInPath('cmssw_emap_3dcc_v1.txt')
   #))
#)

# use this when it works
#   connect = cms.string('frontier://cmsfrontier.cern.ch:8000/FrontierProd/CMS_COND_31X_HCAL'),

#####process.es_pool = cms.ESSource(
#####   "PoolDBESSource",
#####   process.CondDBSetup,
#####   timetype = cms.string('runnumber'),
#####   connect = cms.string('frontier://cmsfrontier.cern.ch:8000/FrontierPrep/CMS_COND_30X_HCAL'),
#####   authenticationMethod = cms.untracked.uint32(0),
#####   toGet = cms.VPSet(
#####       cms.PSet(
#####           record = cms.string('CastorPedestalsRcd'),
#####           tag = cms.string('castor_pedestals_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorPedestalWidthsRcd'),
#####           tag = cms.string('castor_pedestalwidths_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorGainsRcd'),
#####           tag = cms.string('castor_gains_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorGainWidthsRcd'),
#####           tag = cms.string('castor_gainwidths_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorQIEDataRcd'),
#####           tag = cms.string('castor_qie_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorChannelQualityRcd'),
#####           tag = cms.string('castor_channelquality_v1.0_test')
#####           ),
#####       cms.PSet(
#####           record = cms.string('CastorElectronicsMapRcd'),
#####           tag = cms.string('castor_emap_dcc_v1.0_test')
#####           )
#####   )
#####)

process.castorpedestalsanalysis = cms.EDAnalyzer("CastorPedestalsAnalysis",
    hiSaveFlag  = cms.untracked.bool( False ),
    verboseflag = cms.untracked.bool( True ),
    firstTS = cms.untracked.int32(0),
    lastTS = cms.untracked.int32(9),
    castorDigiCollectionTag = cms.InputTag('castorDigis')
)


process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.destinations = ['detailedInfo.txt']
process.MessageLogger = cms.Service("MessageLogger",
                                    destinations   = cms.untracked.vstring('detailedInfo', 'critical', 'cerr'),
                                    critical       = cms.untracked.PSet(threshold = cms.untracked.string('ERROR'),filename = cms.untracked.string('critical.log')),
                                    detailedInfo   = cms.untracked.PSet(threshold = cms.untracked.string('INFO'),filename = cms.untracked.string('cinfo.log')),
                                    cerr           = cms.untracked.PSet(threshold = cms.untracked.string('WARNING'),filename = cms.untracked.string('cerr.log'))
                                    )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.p = cms.Path(#process.castorDigis*
                     #process.dumpECA* #Digis*process.m* #process.dumpRaw --> shows BCN-counters
                     process.RawToDigi*
                     process.L1Reco)
#process.p = cms.Path(process.dumpRaw*process.castorDigis*process.dump*process.m*process.dumpECA)
#process.p = cms.Path(process.castorDigis*process.castorpedestalsanalysis)
process.ep = cms.EndPath(process.out)

