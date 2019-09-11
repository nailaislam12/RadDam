import FWCore.ParameterSet.Config as cms

ggNtuplizer = cms.EDAnalyzer("ggNtuplizer",

                             VtxLabel             = cms.InputTag("offlineSlimmedPrimaryVertices"),
                             rhoLabel             = cms.InputTag("fixedGridRhoFastjetAll"),
                             rhoCentralLabel      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                             electronSrc          = cms.InputTag("slimmedElectrons"),
                             calibelectronSrc     = cms.InputTag("slimmedElectrons"),
                             ebReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEBRecHits"),
                             eeReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedEERecHits"),
                             esReducedRecHitCollection = cms.InputTag("reducedEgamma", "reducedESRecHits"),
                             ak4JetSrc                 = cms.InputTag("slimmedJets"),
                             packedPFCands   = cms.InputTag("packedPFCandidates"),

)
