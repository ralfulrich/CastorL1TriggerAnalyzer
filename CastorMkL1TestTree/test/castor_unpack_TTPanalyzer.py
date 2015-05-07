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
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/390/00000/A0445EE2-B8EA-E411-B6D7-02163E011D0F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/00936F84-BFEB-E411-97E8-02163E013397.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/02875666-B5EB-E411-91F4-02163E0128C4.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/02977D6A-ACEB-E411-93E8-02163E011878.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/04AD22E3-80EB-E411-8E92-02163E0139C4.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/04EA22B7-BAEB-E411-8D6A-02163E013421.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/088E9637-9CEB-E411-B916-02163E01350E.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/08E604F9-8CEB-E411-93A9-02163E01280E.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/0E5CA151-85EB-E411-820F-02163E01347C.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/0EAAE23C-83EB-E411-BD7F-02163E011D1F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/10941FB3-93EB-E411-A92A-02163E011D77.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/109CF99C-A4EB-E411-B084-02163E0137C9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/122602F2-7EEB-E411-BF28-02163E011C19.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/126FA934-83EB-E411-B16A-02163E0135BE.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/12D69DED-8CEB-E411-AAE1-02163E0124A9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/140E135F-ADEB-E411-A44B-02163E0134AC.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/167B238D-73EB-E411-AE8F-02163E0127E5.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/1A57F528-B2EB-E411-88A1-02163E0121EE.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/1C302B4C-A1EB-E411-92D0-02163E011CF9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/1E243A8A-9FEB-E411-92DE-02163E0138A9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/1E7D49D6-90EB-E411-B78F-02163E011D10.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/22ADE7BA-70EB-E411-BD78-02163E0133D6.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/24415FE4-7AEB-E411-B4FE-02163E01188F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2455925B-ADEB-E411-94FB-02163E01206B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2456D8E6-8FEB-E411-B16C-02163E01244F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/24E3B870-ACEB-E411-B8C8-02163E011EAB.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/26882701-75EB-E411-A1AB-02163E011869.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/28454C39-9AEB-E411-A940-02163E013684.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2C89919D-94EB-E411-8D78-02163E0129C4.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2CC8B1B4-BEEB-E411-8882-02163E011D20.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2E10A23C-A2EB-E411-B9E7-02163E01351F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2E205066-B0EB-E411-A493-02163E012811.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/2E797B80-A3EB-E411-8011-02163E012400.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/304A39C3-7FEB-E411-84C0-02163E01358D.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/3098BA9B-82EB-E411-95F6-02163E01348A.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/30FD7B2E-83EB-E411-8B1B-02163E0121C3.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/3207206C-77EB-E411-9813-02163E01395A.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/3427A399-8BEB-E411-85D6-02163E012A08.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/34814240-AAEB-E411-B861-02163E011878.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/34B4E6C7-A5EB-E411-9025-02163E0138EF.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/36E13E3A-A2EB-E411-AA34-02163E013421.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/38346F4F-85EB-E411-A3E3-02163E012701.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/3AB51705-7CEB-E411-8A3D-02163E0133E0.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/3C8E1076-AFEB-E411-823F-02163E01257B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/400380E0-A7EB-E411-A55A-02163E01350B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/401A2F3C-BDEB-E411-8DCC-02163E012749.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/42E03698-AFEB-E411-8ECC-02163E01206B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/44571C74-70EB-E411-89B7-02163E0139DD.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/4469AD80-B6EB-E411-9933-02163E0139C4.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/4647FF25-8AEB-E411-AAAB-02163E012493.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/465DCBC1-7FEB-E411-B917-02163E01389A.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/4ADE6423-9BEB-E411-9AF6-02163E012013.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/4C2D9A7A-77EB-E411-AA5F-02163E013575.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/4E1460F3-7CEB-E411-88FB-02163E01271E.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/56FD775D-A0EB-E411-8B4C-02163E0136B0.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/5877BC89-9FEB-E411-B296-02163E0122F7.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/58CEDCC0-87EB-E411-869A-02163E01348A.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/5C6DE4EF-8FEB-E411-B423-02163E0138A9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/5CC506CE-A5EB-E411-9CC4-02163E011DDF.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/241/422/00000/5E5E8432-ABEB-E411-A59D-02163E0135CD.root',
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
#     fileNames = cms.untracked.vstring('/store/group/phys_heavyions/katkov/cas_loc_2013/USC_242879.root')
# )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000) #10000
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

