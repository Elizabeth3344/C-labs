git checkout stg
git merge dev
timetag=$(date '+%H-%M-%S')
git tag $timetag
git checkout dev