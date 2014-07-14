#!/bin/bash

if [ -z "$1" ]
  then
    echo "No build number specified"
fi

sed -i "7s/.*/#define PONYTERRA_BUILD $1/" src/VersionNumber.h
