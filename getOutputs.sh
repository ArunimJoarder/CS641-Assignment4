#! /usr/bin/expect -f

spawn ssh student@65.0.124.36 

send "Cryptonite"
send "hesoyamo"
send "4"
send "read"

> outputs1.txt
while read p; do
  echo $p
  read output
  echo "c"
  echo $output >> outputs1.txt
done < inputs1.txt

> outputs2.txt
while read p; do
  echo $p
  read output
  echo "c"
  echo $output >> outputs2.txt
done < inputs2.txt
