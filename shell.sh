#!/bin/bash
if [ "$#" -lt "2" ];
then
  echo "Usage : ./shell.sh src time-limit [classpath]"
  exit 1
fi

if [ -z $JAVA_HOME ];
then
  echo "Need to set JAVA_HOME"
  exit 1
fi

if [ -z $RANDOOP_JAR ];
then
  echo "Need to set environmental variable RANDOOP_JAR"
  export RANDOOP_JAR=./jar/randoop-all-4.1.0.jar
fi

`g++ Traversal.cpp -o Traversal`
`mkdir classdir 2>/dev/null`
javac $1/*.java -d classdir
./Traversal ./classdir > class.txt
src=$1
dest=${src%src*}
dest=$dest"src/test"
`mkdir $dest 2>/dev/null`
dest=$dest"/java"
`mkdir $dest 2>/dev/null`
java -classpath $PWD/classdir:$RANDOOP_JAR:$3 randoop.main.Main gentests --classlist=class.txt --time-limit=$2 --junit-output-dir=$dest
rm Traversal
rm class.txt
rm -rf classdir

