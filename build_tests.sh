#!/bin/bash

#https://stackoverflow.com/questions/8512462/looping-through-all-files-in-a-directory
format=./tests/*.c
for file in $format;
do
    if [ "$file" != "$format" ]
    then
        # this is janky and breaks easily; can probably fix by compiling source
        # files and linking in separate steps, making sure NOT to include main.c,
        # since it interferes with Criterion's main function
        #
        # I should definitely just use a Makefile lol
        gcc -Wall -Wextra -Werror -O0 -std=c99 -ggdb -D_DEFAULT_SOURCE -lcriterion ./src/$(basename "$file" _test.c).c $file -o ./tests/$(basename "$file" .c)
    else
        echo "No tests to build!"
    fi
done
