#!/usr/bin/python
from subprocess import call
import sys, os, time, tarfile

def main():

#FIXME Update these
    email = "cameronc@jlab.org"

    #configuration = "prexI"
    #configuration = "crex5"
    configuration = "prexII"
    #configuration = "moller"
    #configuration = "happex2"

    stage = "hallRad"
    varied = "off_thickness"
    geo = raw_input("Please enter the can geometry (sph or cyl): ")
    offset = raw_input("Please enter the offset in mm (integers up to 360): ")
    thickness = raw_input("Please enter the thickness in mm (integers up to 15): ")
    identifier = "SAMs_"+geo+"_"+offset+varied#raw_input("Please enter the identifier: ")

    #sourceDir = "/work/halla/parity/disk1/ciprian/prexSim"
    sourceDir = "/work/halla/parity/disk1/moller12gev/cameronc/masterPrexSim"
    sourceMasterDir = "/work/halla/parity/disk1/moller12gev/cameronc/masterPrexSim"
    outputDir = "/lustre/expphy/volatile/halla/parity/cameronc/prexSim/output/SAM_"+stage+"_tests"
    nrEv=900000

    jobName=configuration + '_' + identifier + '_' + thickness + 'mm' + '_%03dkEv'%(nrEv/1000)
    listName='list_' + identifier + '_' + thickness + 'mm'

    if not os.path.exists(outputDir+"/"+jobName+"/log"):
        os.makedirs(outputDir+"/"+jobName+"/log")
    createXMLfile(sourceDir,outputDir,jobName,identifier,listName,thickness,email)

    call(["cp",sourceDir+"/output/ls_mod.sh",
              outputDir+"/"+jobName+"/ls_mod.sh"])
    call(["cp",sourceMasterDir+"/build/hallRad",
              outputDir+"/"+jobName+"/hallRad"])
    print "All done for configuration ",configuration,"_",identifier,"for",thickness

def createXMLfile(source,writeDir,idRoot,name,listname,number,email):

    if not os.path.exists(source+"/output/jobs"):
        os.makedirs(source+"/output/jobs")

    f=open(source+"/output/jobs/"+idRoot+"_hallRad.xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"prex\"/>\n")

    f.write("  <Track name=\"debug\"/>\n")
#    f.write("  <Track name=\"analysis\"/>\n")

    f.write("  <Name name=\""+idRoot+"_hallRad\"/>\n")
    f.write("  <OS name=\"centos7\"/>\n")
    f.write("  <Memory space=\"3500\" unit=\"MB\"/>\n")

    f.write("  <Command><![CDATA[\n")
    f.write("    pwd\n")
    f.write("    ./ls_mod.sh "+name+" "+number+"\n")
    
    f.write("  ]]></Command>\n")

    idName= writeDir+"/"+idRoot
    f.write("  <Job>\n")
    f.write("    <Input src=\""+idName+"/hallRad\" dest=\"hallRad\"/>\n")
    f.write("    <Input src=\""+idName+"/ls_mod.sh\" dest=\"ls_mod.sh\"/>\n")
    #f.write("    <Input src=\""+idName+"/"+listname+".txt\" dest=\""+listname+".txt\"/>\n")
    f.write("    <Output src=\""+listname+".txt\" dest=\""+idName+"/"+listname+".txt\"/>\n")
    f.write("    <Output src=\""+listname+"_hallRad.root\" dest=\""+idName+"/"+listname+"_hallRad.root\"/>\n")

    f.write("    <Stdout dest=\""+idName+"/log/log.out\"/>\n")
    f.write("    <Stderr dest=\""+idName+"/log/log.err\"/>\n")
    f.write("  </Job>\n\n")

    f.write("</Request>\n")
    f.close()
    return 0

if __name__ == '__main__':
    main()
