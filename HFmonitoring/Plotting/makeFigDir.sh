
#!/bin/bash
# quick script to create a figures directory...

NEWDIR=${1}

if [[ ! -d ${NEWDIR} ]]; then
    echo "mkdir ${NEWDIR}"
    mkdir ${NEWDIR}
else
    echo "Directory ${NEWDIR} already exists... will not overwrite"
fi

for i in Eta EtaBin EtaPhiFit PU Phi; do 
    if [[ ! -d ${NEWDIR}/${i} ]]; then 
	mkdir ${NEWDIR}/${i}; 
    else
	echo "Directory ${NEWDIR}/${i} already exists, will not overwrite"
    fi
done
