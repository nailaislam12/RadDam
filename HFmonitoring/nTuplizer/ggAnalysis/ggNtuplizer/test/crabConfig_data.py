if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -d <work area> (to check job status)

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    config.General.workArea     = 'DataJobs'
    config.General.transferLogs = False
    config.JobType.maxMemoryMB = 5000
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.pluginName   = 'Analysis' 
    config.JobType.psetName     = 'run_data.py'
    config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       = 'LumiBased' 
    config.Data.lumiMask        = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt' # 58.83 /fb
    config.Data.unitsPerJob     = 20
    config.Data.ignoreLocality  = False
    config.Data.publication     = False
    config.Data.allowNonValidInputDataset     = True
    config.Site.storageSite     = 'T3_US_Rutgers'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    # dataset dependent configuration


    # Run2018A
    config.General.requestName = 'EGamma_Run2018A'
    config.Data.inputDataset   = '/EGamma/Run2018A-17Sep2018-v2/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/mheindl/2018HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()
    
    # Run2018B
    config.General.requestName = 'EGamma_Run2018B'
    config.Data.inputDataset   = '/EGamma/Run2018B-17Sep2018-v1/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/mheindl/2018HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

    # Run2018C
    config.General.requestName = 'EGamma_Run2018C'
    config.Data.inputDataset   = '/EGamma/Run2018C-17Sep2018-v1/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/mheindl/2018HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()
    
    # Run2018D    
    config.General.requestName = 'EGamma_Run2018D'
    config.Data.inputDataset   = '/EGamma/Run2018D-PromptReco-v2/MINIAOD'
    config.Data.outLFNDirBase  = '/store/user/mheindl/2018HF/'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()

