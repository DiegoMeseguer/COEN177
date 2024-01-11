#!/bin/bash
echo "----------Make--------"
make; 

echo  "----------Running steps----------"
echo "Step 2"
./step2.sh

echo "Step 3"
./step3.sh

echo "Step 4"
./step4.sh

echo "Step 5"
./step5.sh

make clean;
echo
