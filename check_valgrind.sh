#!/bin/bash

maps_dir="maps"
maps=("$maps_dir"/*)


for map in "${maps[@]}"
do
  leaks_output=$(valgrind ./cub3D "$map" 2>&1)
  
  if [[ $leaks_output == *"no leaks are possible"* ]]; then
    echo "No leaks found for $map"
  else
    echo "Leaks found for $map:"
  fi
done