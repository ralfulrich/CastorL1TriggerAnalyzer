import FWCore.ParameterSet.Config as cms

import os
base_path = os.getenv('CMSSW_BASE', 'empty_defualt_value')
print 'CMSSW_BASE: {0}'.format(base_path) 

process = cms.Process("PEDS")
process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
# process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/002A5A0E-7A0C-E511-A5C9-02163E011E08.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/0476711D-720C-E511-AA52-02163E01432C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/0633D51D-720C-E511-9492-02163E012665.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/06826F3D-690C-E511-B65C-02163E0140EE.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/06E76176-600C-E511-8FE8-02163E014218.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/0C910CD8-6C0C-E511-87A2-02163E0145C8.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/1466E088-6F0C-E511-8415-02163E01388B.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/14DE0CAA-630C-E511-8250-02163E012A7A.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/169495A3-6F0C-E511-ADDA-02163E0142E6.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/169F2B9E-6F0C-E511-88EC-02163E0142B7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/1E17083D-790C-E511-99C9-02163E011A81.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/1E6A2E3C-790C-E511-A1C9-02163E013942.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/1EDCAA1D-720C-E511-84BA-02163E013653.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/22A4FA07-6C0C-E511-9F7B-02163E01424D.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/22F64569-720C-E511-9B8D-02163E014374.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/245FB63D-770C-E511-B08D-02163E0145A9.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/26C89D1D-720C-E511-BE2F-02163E014467.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/2AFCBAD2-6C0C-E511-99CB-02163E0135D4.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/2C475ABB-6F0C-E511-B711-02163E012808.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/2E477B13-720C-E511-BA02-02163E011BD8.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/2E97A016-720C-E511-AD84-02163E013491.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/2EFCEEFC-640C-E511-98A7-02163E0133EB.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/381A86D6-6C0C-E511-829E-02163E012BE0.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/389CBD17-720C-E511-9F30-02163E0142E6.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/3CA2F3A2-6F0C-E511-A096-02163E013556.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/42F1EF34-690C-E511-A9C8-02163E012927.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/4450D233-720C-E511-8C15-02163E011E08.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/52AF7506-6C0C-E511-AAD9-02163E014349.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/52DF0566-6A0C-E511-B3EE-02163E011C2F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/5E81591B-720C-E511-B0E4-02163E013942.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/64AE01D7-6C0C-E511-88EB-02163E0145E7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/68831EB6-6F0C-E511-B961-02163E014240.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6A4A93C0-630C-E511-BC98-02163E0118AE.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6A4AA955-7C0C-E511-AA0D-02163E0145BA.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6A8F0D08-6C0C-E511-AB40-02163E01369F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6C0A1BC9-610C-E511-915E-02163E0144EE.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6C4B82B1-7B0C-E511-A0B1-02163E013518.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/6E3308F1-6C0C-E511-ABEC-02163E01383E.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/70277D12-720C-E511-ACC9-02163E0145C9.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/703B90A2-6F0C-E511-BDE4-02163E014349.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/725DE004-6C0C-E511-BE52-02163E01349C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/7479AA08-6C0C-E511-8C95-02163E012551.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/74D6AC1B-720C-E511-A810-02163E011C2F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/7C1B4E1E-720C-E511-84FD-02163E01437C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/7EEE3BA4-6F0C-E511-A982-02163E0145A9.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/841ED085-6E0C-E511-8746-02163E0136A3.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/84CFF6A7-6F0C-E511-8D25-02163E01369F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/86C458B4-780C-E511-87C1-02163E011D25.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/86F4A21D-720C-E511-992D-02163E014100.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/889845C3-7E0C-E511-BE0A-02163E012072.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/8A3EB737-690C-E511-BA8C-02163E01257B.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/8C98349E-6F0C-E511-9EB6-02163E0118AE.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/8E784EF3-730C-E511-A6C4-02163E014338.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/94F9ADA3-6E0C-E511-AAB2-02163E01437C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/961797A3-6F0C-E511-9EFF-02163E011C2F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/981BE33A-720C-E511-9977-02163E0144C3.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/98F1A722-720C-E511-9B13-02163E0145A9.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/9AA2B835-690C-E511-B223-02163E01364D.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/9AE63CE9-740C-E511-83DE-02163E0145E7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/9C998F11-720C-E511-B37E-02163E013556.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/9CA5F41A-750C-E511-9688-02163E0143EB.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/9CFD7E1D-720C-E511-9A32-02163E0142D7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/A2D8F7CC-630C-E511-87E2-02163E01287B.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/A47D39B0-6F0C-E511-B351-02163E0119DC.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/A6D619CE-610C-E511-A2DB-02163E0144EE.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/AE0D3179-650C-E511-81AC-02163E0140FA.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/AED10245-770C-E511-8FB8-02163E013686.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/B027EE02-6C0C-E511-8616-02163E0143EC.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/B087FAAE-670C-E511-9138-02163E011BAC.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/B64FAF63-760C-E511-BE53-02163E011A81.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/C2FAE2DD-610C-E511-A7C1-02163E0134D5.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/C40AD0B9-630C-E511-873C-02163E01184D.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/C4392C0C-720C-E511-9ECE-02163E01467C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/C602E6D7-6C0C-E511-82D8-02163E0136A7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/CA74A2AC-6F0C-E511-9962-02163E0142D7.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/CAE88016-720C-E511-8D76-02163E01364F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/CC8A28BA-5F0C-E511-B057-02163E014270.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/CCB5050E-720C-E511-B9A3-02163E014122.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/CE9DDD1E-720C-E511-AFBD-02163E012028.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/D07B30CE-6C0C-E511-8A1D-02163E014172.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/D0FDD244-720C-E511-B3EE-02163E0120CB.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/D2A8BD6B-720C-E511-ADDC-02163E014374.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/DC9FF519-720C-E511-93F4-02163E011BD8.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/E0453BDA-6C0C-E511-BC1D-02163E01432C.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/E4D8D20F-720C-E511-BCCE-02163E013727.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/E6C12EA9-6E0C-E511-BA2B-02163E01424A.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/E8EFD2B1-780C-E511-9F42-02163E011C2F.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/ECB60D1C-720C-E511-B864-02163E01442E.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/EE6F1697-6F0C-E511-BF6E-02163E01424D.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/EE94A2A4-6F0C-E511-8EF2-02163E0140E8.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/F0A8B6D7-6C0C-E511-9EEB-02163E01257B.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/F6109A6F-6A0C-E511-B3F6-02163E0145B1.root',
      '/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/266/00000/FA97C0AE-6F0C-E511-A851-02163E012A4D.root',
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
    input = cms.untracked.int32(-100) #10000
)

# This version is intended for unpacking standard production data
process.castorDigis = cms.EDProducer("CastorRawToDigi",
    # Optional filter to remove any digi with "data valid" off, "error" on, 
    # or capids not rotating
    FilterDataQuality = cms.bool(True),
    # Number of the first CASTOR FED.  If this is not specified, the
    # default from FEDNumbering is used.
    CastorFirstFED = cms.int32(690),
    # FED numbers to unpack.  If this is not specified, all FEDs from
    # FEDNumbering will be unpacked.
    FEDs = cms.untracked.vint32( 690, 691, 692 ),
    # Do not complain about missing FEDs
    ExceptionEmptyData = cms.untracked.bool(False),
    # Do not complain about missing FEDs
    ComplainEmptyData = cms.untracked.bool(False),
    # At most ten samples can be put into a digi, if there are more
    # than ten, firstSample and lastSample select which samples
    # will be copied to the digi
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    # castor technical trigger processor
    UnpackTTP = cms.bool(True),
    # report errors
    silent = cms.untracked.bool(False),
    #
    InputLabel = cms.InputTag("rawDataCollector"),
    # InputLabel = cms.InputTag("hltEcalCalibrationRaw"),
    # InputLabel = cms.InputTag("source"),
    CastorCtdc = cms.bool(False),
    UseNominalOrbitMessageTime = cms.bool(True),
    ExpectedOrbitMessageTime = cms.int32(-1)
)



process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# process.GlobalTag.globaltag = 'GR_P_V49::All'
process.GlobalTag.globaltag = 'GR_E_V47::All'


#################################################################################################################################
#################################################################################################################################
process.castorl1test = cms.EDAnalyzer('CastorTTPTest',
    debugInfo = cms.bool(False),
    ShowTriggerMenu = cms.bool(False),

    # Alan changed it on 6.June see also http://cmsonline.cern.ch/cms-elog/858046
    NewTTPinputCoding = cms.bool(True)
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


#################################################################################################################################
#################################################################################################################################
#Trigger Selection
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltMinBiasHF = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBiasHF.HLTPaths = ["HLT_Random_v2"]
#process.hltMinBiasHF.HLTPaths = ["HLT_PAMinBiasHF_v1"]
#################################################################################################################################

process.p = cms.Path(
                     # process.hltMinBiasHF*
                     process.castorDigis*
                     process.castorl1test)

