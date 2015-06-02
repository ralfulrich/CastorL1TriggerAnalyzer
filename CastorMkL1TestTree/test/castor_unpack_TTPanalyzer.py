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
        '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/246/599/00000/94FE5E48-FE08-E511-A048-02163E011911.root'

        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/246/310/00000/1832742A-C506-E511-B3B2-02163E0139D8.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/246/339/00000/D8016108-F706-E511-841F-02163E0119D0.root',

        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/246/442/00000/081D8E53-4108-E511-A365-02163E011C9E.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/246/442/00000/128AD7C0-4A08-E511-9DFC-02163E013780.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/246/442/00000/1C432E0E-4308-E511-A2BF-02163E011BA1.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/246/442/00000/1C7FD82C-4308-E511-B7B6-02163E014470.root',

        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/357/00000/44B81F5D-AE00-E511-A2F3-02163E012011.root',
        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/357/00000/7E8B1889-AE00-E511-8B1A-02163E0123BB.root',
        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/357/00000/B25344F0-B000-E511-B8EB-02163E012B0F.root',
        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/357/00000/D21A7BD2-B000-E511-8A81-02163E01219E.root',

        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/245/258/00000/7A0527F5-4F00-E511-B481-02163E0142D7.root',

        # '/store/express/Commissioning2015/ExpressPhysics/FEVT/Express-v1/000/245/192/00000/12D20F51-8EFF-E411-AA4E-02163E012324.root',

        # 'file:/tmp/katkov/HIRun2013A_PAMinBiasUPC_RAW_v1_000_210_983_A850DF19-7F69-E211-8DDE-001D09F2447F.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/244/734/00000/14A1F9EB-FEFC-E411-9214-02163E011DA1.root',

        # '/store/data/Commissioning2015/TestEnablesEcalHcal/RAW/v1/000/244/456/00000/1831154B-34FA-E411-9D4D-02163E0122E1.root',

        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/244/259/00000/065D1CC2-29F9-E411-BACB-02163E012A7A.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/244/245/00000/1A93B236-E9F8-E411-A8D2-02163E0137B0.root',
        # '/store/express/Commissioning2015/ExpressCosmics/FEVT/Express-v1/000/244/244/00000/000C0A27-E8F8-E411-85CD-02163E0144F1.root',

        # '/store/data/Commissioning2015/Cosmics/RAW/v1/000/243/902/00000/8EBB8E97-08F6-E411-8411-02163E0135AD.root',

        # famous run with castor muon trigger
        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/864/00000/2A232EE6-94F5-E411-B649-02163E0118AF.root',

        # '/store/data/Commissioning2015/MinimumBias/RAW/v1/000/243/854/00000/645B0043-8FF5-E411-BCBE-02163E01355D.root',
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
process.MessageLogger.cerr.FwkReport.reportEvery = 5000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
#################################################################################################################################

process.p = cms.Path(
                     process.castorDigis*
                     process.castorl1test)

