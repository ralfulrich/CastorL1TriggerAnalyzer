import FWCore.ParameterSet.Config as cms

castormkl1testtree = cms.EDAnalyzer('CastorMkL1TestTree',
    ShowDebugInfo    = cms.bool(False),
    ShowTriggerMenu  = cms.bool(False),

    PileUpInfo       = cms.InputTag('addPileupInfo'),
    GenPartColl      = cms.InputTag('genParticles'),
    GenJetColl       = cms.InputTag('ak5GenJets'),
    CaloTowerColl    = cms.InputTag('towerMaker'),
    HadFwdRecHitColl = cms.InputTag('hfreco'),
    CasRecHitColl    = cms.InputTag('castorreco'),
    BasicJetColl     = cms.InputTag('ak5CastorJets'),
    CastorJetID      = cms.InputTag('ak5CastorJetID'),
    TrigResults      = cms.InputTag('TriggerResults'),
    VertexColl       = cms.InputTag('offlinePrimaryVertices'),

    HLTpaths         = cms.vstring()
)
