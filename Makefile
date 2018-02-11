SLUG = BeckstromResearch
VERSION = 0.5.0

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine.
LDFLAGS +=

# Add .cpp and .c files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin is automatically added.
DISTRIBUTABLES += $(wildcard LICENSE*) res

# Include the VCV plugin Makefile framework
include ../../plugin.mk

# do stuff
install: all
	echo "removing existing folder in plugins..."
	rm -R ~/Documents/Rack/plugins/BeckstromResearch
	echo "copying compiled stuff to plugins folder..."
	cp -R ~/source_files/Rack/plugins/BeckstromResearch ~/Documents/Rack/plugins/
	echo "the end"
