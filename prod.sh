#!/bin/bash

git checkout prd
git merge stg
timetag=$(date '+%H-%M-%S')
git tag $timetag
git checkout dev