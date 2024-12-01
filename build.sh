#!/bin/bash

source ~/start/.emsdk/emsdk_env.sh

rm /home/wheedo/start/Project7/game/godot/dino_rumble/server/src/main/resources/static/game/*
find "demo/bin/"* ! -name "*.gdextension" -exec rm {} \; && 
scons platform=web build_library=no &&
scons platform=windows build_library=no
scons platform=linux build_library=no && godot --headless --path ./demo/ -v --export-debug "Web" 