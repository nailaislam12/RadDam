if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -d <work area> (to check job status)

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    config.General.workArea     = 'MCJobs'
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 5000
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.pluginName   = 'Analysis' 
    config.JobType.psetName     = 'run_mc.py'
    config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       = 'FileBased' 
    config.Data.unitsPerJob     = 10
    config.Data.ignoreLocality  = False
    config.Data.publication     = False
    config.Site.storageSite     = 'T3_US_Rutgers'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    # dataset dependent configuration
    
    config.General.requestName = 'DYJetsToLL_M-50_Fall18'
    config.Data.inputDataset   = '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall18MiniAOD-102X_upgrade2018_realistic_v12_ext1-v1/MINIAODSIM'
    config.Data.outLFNDirBase  = '/store/user/mheindl/2018HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

    




