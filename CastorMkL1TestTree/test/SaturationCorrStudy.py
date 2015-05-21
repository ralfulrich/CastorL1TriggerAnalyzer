import FWCore.ParameterSet.Config as cms

process = cms.Process("PEDS")

#################################################################################################################################
#################################################################################################################################
process.load('Configuration.StandardSequences.Services_cff')
#process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
#process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.EventContent.EventContent_cff')
#################################################################################################################################


#################################################################################################################################
#################################################################################################################################
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/0C7358DF-94FF-E411-8EB8-02163E012324.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/0ECA3BCD-97FF-E411-A8C7-02163E01432C.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/10A14B1A-94FF-E411-AFCF-02163E013809.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/10AC2C86-9BFF-E411-AC8A-02163E012927.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/10FD326B-9BFF-E411-82F5-02163E012011.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/12BC4169-9BFF-E411-9946-02163E01432C.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/12DD0A11-96FF-E411-89EC-02163E012927.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/1A2813BE-97FF-E411-90E1-02163E01369F.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/1EAD2677-9CFF-E411-AE63-02163E011DE2.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/24559B8C-9BFF-E411-B96D-02163E01262E.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/24E5766C-9BFF-E411-9A84-02163E0133D9.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/285AD4CB-97FF-E411-867A-02163E014652.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/2ADAFD2F-97FF-E411-AB60-02163E0142E6.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/2C0CE7CB-97FF-E411-B69A-02163E0142B3.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/2E8C82CC-97FF-E411-B0C0-02163E013476.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/30C3D0B8-97FF-E411-8E52-02163E01289B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/32F2C17E-9BFF-E411-A0FF-02163E0133F2.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3834DE17-94FF-E411-AEC8-02163E0138F8.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3864932C-95FF-E411-AB83-02163E0143AD.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3A76A0C7-97FF-E411-B83D-02163E0142DF.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3C0E6AEE-99FF-E411-96CB-02163E012011.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3C11AA0A-9AFF-E411-A2D7-02163E01391B.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3C337869-9BFF-E411-BFE8-02163E011D70.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/3C8DA6A8-9CFF-E411-ABB9-02163E014274.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/40ACAE7E-9BFF-E411-9805-02163E011DE2.root',
        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/194/00000/40FF2A69-9BFF-E411-ABC1-02163E0142B3.root',

        '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/192/00000/12D20F51-8EFF-E411-AA4E-02163E012324.root',
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-10) #10000
)
#################################################################################################################################




#################################################################################################################################
#################################################################################################################################
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger = cms.Service("MessageLogger",
    destinations   = cms.untracked.vstring('detailedInfo', 'warning', 'cerr'),
    statistics     = cms.untracked.vstring('detailedInfo', 'warning', 'cerr'),
    detailedInfo   = cms.untracked.PSet(threshold = cms.untracked.string('INFO')),
    warning        = cms.untracked.PSet(threshold = cms.untracked.string('WARNING')),
    cerr           = cms.untracked.PSet(threshold = cms.untracked.string('ERROR'))
)
#################################################################################################################################




#################################################################################################################################
##################################################################################################################################
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.prefer("GlobalTag")
#process.GlobalTag.globaltag = 'GR_R_39X_V6::All'
#process.GlobalTag.globaltag = 'GR_R_311_V4::All' 
#process.GlobalTag.globaltag = 'GR_R_44_V15::All' 
#process.GlobalTag.globaltag = 'GR_R_42_V25::All'
process.GlobalTag.globaltag = 'GR_E_V33::All'
##################################################################################################################################




#################################################################################################################################
#################################################################################################################################
#process.load("EventFilter.CastorRawToDigi.CastorRawToDigi_cfi")
#process.castorDigis = cms.EDProducer("CastorRawToDigi", ###EDProducer/EDFilter
#   CastorFirstFED     = cms.untracked.int32(690),
#   FilterDataQuality  = cms.bool(True),
#   ExceptionEmptyData = cms.untracked.bool(True),
#   InputLabel         = cms.InputTag("source"),  #"source" #"rawDataRepacker"
#   UnpackCalib        = cms.untracked.bool(False),
#   FEDs               = cms.untracked.vint32(690,691,692),
#   lastSample         = cms.int32(9), #9
#   firstSample        = cms.int32(0)
#) 
#################################################################################################################################




#################################################################################################################################
#################################################################################################################################
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
#################################################################################################################################


# #################################################################################################################################
# #################################################################################################################################
# process.load("RecoLocalCalo.CastorReco.CastorSimpleReconstructor_cfi")
# process.NewCastorReco = cms.EDProducer("CastorSimpleReconstructor",
#     correctionPhaseNS          = cms.double(0.0),
#     digiLabel                  = cms.InputTag("castorDigis"),
#     samplesToAdd               = cms.int32(2),
#     Subdetector                = cms.string('CASTOR'),
#     firstSample                = cms.int32(4),
#     correctForPhaseContainment = cms.bool(False),
#     correctForTimeslew         = cms.bool(False),
#     tsFromDB                   = cms.bool(True),
#     setSaturationFlag          = cms.bool(True),
#     maxADCvalue                = cms.int32(127),
#     doSaturationCorr           = cms.bool(True)
# )
# #################################################################################################################################




#################################################################################################################################
#################################################################################################################################
process.saturationcorrstudy = cms.EDAnalyzer('SaturationCorrStudy',
    CastorDigiColl      = cms.InputTag('castorDigis'),
    NewCastorRecHitColl = cms.InputTag('NewCastorReco'),

    PrintInfo   = cms.bool(True),
    InvestMod   = cms.int32(1),
    InvestSec   = cms.int32(13)
)
#################################################################################################################################



# #################################################################################################################################
# #################################################################################################################################
# process.noscraping = cms.EDFilter("FilterOutScraping",
#     applyfilter = cms.untracked.bool(True),
#     debugOn = cms.untracked.bool(False),
#     numtrack = cms.untracked.uint32(10),
#     thresh = cms.untracked.double(0.25),
# )
# #################################################################################################################################




# #################################################################################################################################
# #################################################################################################################################
# process.primaryVertexFilter = cms.EDFilter("VertexSelector",
#     src = cms.InputTag("offlinePrimaryVertices"),
#     cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
#     filter = cms.bool(True), # otherwise it won't filter the events, just produce an empty vertex collection.
# )
# #################################################################################################################################




#################################################################################################################################
#################################################################################################################################
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('SaturationCorrStudy.root')
)
#################################################################################################################################


#process.p = cms.Path(process.RawToDigi*process.L1Reco*process.reconstruction*process.NewCastorReco*
#                     process.noscraping*process.primaryVertexFilter*process.testcastorsimplereco_norecodata)
process.p = cms.Path(process.castorDigis*
                     process.saturationcorrstudy)
