#!/bin/bash

if [ -z "$1" ]
  then
    echo "No file specified"
fi

unzip $1