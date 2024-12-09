#!/bin/bash

TARGET_PATH="day$1"
pushd "$TARGET_PATH" > /dev/null || { echo "Failed to change directory to $TARGET_PATH"; exit 1; }
./main
popd > /dev/null
