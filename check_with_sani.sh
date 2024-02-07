#!/bin/bash

maps_dir="maps"
maps=("$maps_dir"/*)


for map in "${maps[@]}"
do 
  leaks_output=$(./cub3D_bonus "$map" 2>&1)
  echo $leaks_output
done