#!/bin/bash

maps_dir="maps"
maps=("$maps_dir"/*)


for map in "${maps[@]}"
do 
  leaks_output=$(leaks -at -- ./cub3D "$map" 2>&1)
  if [[ $leaks_output == *"0 leaks for"* ]]; then
    echo "No leaks found for $map"
  else
    echo "Leaks found for $map:"
    echo "$leaks_output"
  fi
done