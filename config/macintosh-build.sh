#!/bin/bash
source_dir=${BASH_SOURCE[0]}
while [ -L "$source_dir" ]; do # resolve $source_dir until the file is no longer a symlink
  file_dir=$( cd -P "$( dirname "$source_dir" )" >/dev/null 2>&1 && pwd )
  source_dir=$(readlink "$source_dir")
  [[ $source_dir != /* ]] && source_dir=$file_dir/$source_dir # if $source was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
file_dir=$( cd -P "$( dirname "$source_dir" )" >/dev/null 2>&1 && pwd )

for param in "$@"
do
    if [ "$next_build_command" == "set-version" ]; then
        next_build_command="";
        build_version="$param";
    fi
    if [ "$next_build_command" == "set-repo" ]; then
        next_build_command="";
        build_repo="$param";
    fi
    if [ "$param" == "--version" ]; then
        next_build_command="set-version";
    fi
    if [ "$param" == "--repo" ]; then
        next_build_command="set-repo";
    fi
done

build_dir=$file_dir/../build/build-system
if [ -d $build_dir ]; then
    echo Build System: Fetching...;
    cd $build_dir && git checkout $build_version && git pull origin;
else
    echo Build System: Cloning...;
    git clone --branch=$build_version $build_repo $build_dir;
fi
echo Build System: Fetching...;
