#!/bin/bash

# clear

directory="./csv_files"

if [ -d "$directory" ]; then
   echo "direcory:" "$directory found"
   cd "$directory"
   touch "test.csv"
   cd ..

else
   mkdir "$directory"
   cd "$directory"
   touch "test.csv"
   cd ..

fi

if [ -d "$directory" ]; then
   cd "$directory"

   csv_files=$(ls *.csv 2>/dev/null)

   # echo "$csv_files"

# 文字列が空でないかどうか,-nは文字列が "non-zero"、
# つまり空でない場合に真（true）となる。
   if [ -n "$directory" ]; then
      # ls *.csv
      rm *.csv
      echo "$directory csv files deleted suceeded."
   else
      echo "$directory no csv files found."
   fi

else
   echo "Error. $directory directory not found."
   exit 1
fi

cd ..

directory="./ey_timestep_csvs/"

if [ -d "$directory" ]; then
   echo "directory:" "$directory found"
   cd "$directory"
   touch "test.csv"
   cd ..

else
   mkdir  "$directory"
   cd  "$directory"
   touch "test.csv"
   cd ..

fi

if [ -d "$directory" ]; then
   cd "$directory"
   csv_files=$(ls *.csv 2>/dev/null)
   # echo "$csv_files"

   if [ -n "$directory" ]; then
      # ls *.csv
      rm *.csv
      echo "$directory csv files deleted suceeded."
   else
      echo "$directory no csv files found."
   fi

else
   echo "Error. $directory directory not found."
   exit 1
fi

cd ..

cmake -B ./build -G Ninja
cd ./build
ninja -t clean
ninja
cd ..
