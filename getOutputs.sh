#! /usr/bin/env bash

ssh student@65.0.124.36 

echo "Cryptonite"
echo "hesoyamo"
echo "4"
echo "read"

while read p; do
  echo $p
  read output
  echo "c"
  echo $output >> outputs1.txt
done < inputs1.txt

while read p; do
  echo $p
  read output
  echo "c"
  echo $output >> outputs2.txt
done < inputs2.txt