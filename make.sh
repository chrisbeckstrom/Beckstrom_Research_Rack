#!/bin/bash

# make and move to plugins folder
echo "making..."

make
	echo "removing existing folder in plugins..."
	rm -R ~/Documents/Rack/plugins/BeckstromResearch
	echo "copying compiled stuff to plugins folder..."
	cp -R ~/source_files/Rack/plugins/BeckstromResearch ~/Documents/Rack/plugins/
	echo "the end"
