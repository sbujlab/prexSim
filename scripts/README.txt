Cameron + Ciprian

https://kk-router.physics.sunysb.edu/Radiation,+Shielding,+and+Configuration+Simulations/28

To create a workflow on swif run
  swif create -workflow WorkFlowName (where WorkFlowName is an identifier you give to it to monitor its progress)
To monitor the workflow run
  swif status -workflow Name
To delete a workflow run
  swif cancel -workflow Name
  swif cancel -delete -workflow Name
To add a job run
  swif add-jsub -workflow Name -script jobScript.xml
  swif run -workflow Name
To create a script .xml file for running jobs see the description of its function and the python wrapper code included in Ciprian's prexSim code (https://github.com/cipriangal/prexSim)
