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
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/24555EC9-C30E-E511-852C-02163E0143CF.root',
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/421B22C1-C40E-E511-BD47-02163E014150.root',
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/72D5B9B9-C20E-E511-96BD-02163E011A5D.root',
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/7A6EC6D0-C60E-E511-BE96-02163E0133AF.root',
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/9A83EA43-C30E-E511-9A35-02163E012698.root',
'/store/express/Run2015A/ExpressPhysics/FEVT/Express-v1/000/247/571/00000/FE6767FA-C40E-E511-AB74-02163E014384.root',
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

