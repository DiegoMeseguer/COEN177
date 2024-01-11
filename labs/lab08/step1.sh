# Name: Diego Meseguer
# Date: 06/03/2023
# Title: Lab8 - Step 1
# Description: This creates creates 5 files of different sizes filled with
# random characters

#!/bin/bash
#cat /dev/random | head -c <bytecount>

cat /dev/random | head -c 100000 > file1.txt
cat /dev/random | head -c 1000000 > file2.txt
cat /dev/random | head -c 10000000 > file3.txt
cat /dev/random | head -c 100000000 > file4.txt
cat /dev/random | head -c 10000000000 > file5.txt
