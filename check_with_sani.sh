#!/bin/bash

maps_dir="maps"
maps=("$maps_dir"/*)


for map in "${maps[@]}"
do 
  leaks_output=$(./cub3D "$map" 2>&1)
done