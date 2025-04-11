#!/bin/bash

#https://stackoverflow.com/questions/8512462/looping-through-all-files-in-a-directory
format=./tests/*_test
for file in $format;
do
    if [ "$file" != "$format" ]
    then
        echo "Running $(basename $file)..."
        $file
    else 
        echo "No tests have been built!"
    fi
done