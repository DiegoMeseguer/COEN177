# Name: Diego Meseguer
# Date: 06/03/2023
# Title: Lab8 - Step 1
# Description: This creates creates 5 files of different sizes filled with
# random characters

#!/bin/bash
for file in file1.txt file2.txt file3.txt file4.txt 
do
	echo "Step2 $file"
	time ./step2 $file
	echo " "
done

