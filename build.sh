#!/bin/bash

source ~/start/.emsdk/emsdk_env.sh

rm web/*;
find "demo/bin/"* ! -name "*.gdextension" -exec rm {} \; && 
# scons platform=web build_library=no &&
scons platform=windows build_library=no
# scons platform=linux build_library=no && godot --headless --export-debug "Web" ../web/sw.html --path ./demo/ -v