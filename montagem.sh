#!/bin/sh
saidaVids=/DCIM/Motion

for filename in /sdcard/DCIM/Camera/*.jpg; do
    #./MyProgram.exe "$filename" "Logs/$(basename "$filename" .txt)_Log$i.txt"
    opath="/sdcard/DCIM/Motion/$(basename $filename .jpg).mp4"
    if [ ! -f "$opath" ]
    then
      ./vids "$filename" "$opath"
    fi
done

## Check to see if a pipe exists on stdin.
#if [ -p /dev/stdin ]; then
        #echo "Data was piped to this script!"
        ## If we want to read the input line by line
        #while IFS= read line; do
                #echo "./vids ${line} /sdcard$saidaVids/$(basename ${line} .js).mp4"
        #done
        ## Or if we want to simply grab all the data, we can simply use cat instead
        ## cat
#else
        #echo "No input was found on stdin, skipping!"
        ## Checking to ensure a filename was specified and that it exists
        #if [ -f "$1" ]; then
                #echo "Filename specified: ${1}"
                #echo "Doing things now.."
        #else
                #echo "No input given!"
        #fi
#fi