#!/bin/bash

if [ -z "$1" ]
  then
    echo "No URL specified"
fi

curl -O $1