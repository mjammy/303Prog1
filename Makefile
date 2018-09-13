# Files to compile that don't have a main() function
CFILES = team support 
CXXFILES = part2

# Files to compile that do have a main() function
TARGETS = part1a part1b

# Files to compile to .so
CSOFILES = libpart1 libpart2

# Let the programmer choose 32 or 64 bits
BITS ?= 64

# Directory names
ODIR := ./obj$(BITS)
output_folder := $(shell mkdir -p $(ODIR))

# Names of files that the compiler generates
EXEFILES  = $(patsubst %, $(ODIR)/%,    $(TARGETS))
OFILES    = $(patsubst %, $(ODIR)/%.o,  $(CFILES))
CXXOFILES = $(patsubst %, $(ODIR)/%.o,  $(CXXFILES))
SOFILES   = $(patsubst %, $(ODIR)/%.so, $(CSOFILES))
EXEOFILES = $(patsubst %, $(ODIR)/%.o,  $(TARGETS))
DEPS      = $(patsubst %, $(ODIR)/%.d,  $(CFILES) $(CXXFILES) $(CSOFILES) $(TARGETS))

# Use gcc and g++
CC = gcc
CXX = g++
CFLAGS = -MMD -O0 -m$(BITS) -ggdb -D_GNU_SOURCE
CXXFLAGS = -m$(BITS) $(CFLAGS) -std=gnu++17
SOFLAGS = -fPIC -shared
LDFLAGS = -m$(BITS) -ldl

# Best to be safe...
.DEFAULT_GOAL = all
.PRECIOUS: $(OFILES) $(EXEOFILES) $(CXXOFILES)
.PHONY: all clean

# Goal is to build all executables and shared objects
all: $(EXEFILES) $(SOFILES)

# Rules for building object files
$(ODIR)/%.o: %.c
	echo "[CC] $< --> $@"
	$(CC) $< -o $@ -c $(CFLAGS) -fPIC

$(ODIR)/%.o: %.cpp
	echo "[CXX] $< --> $@"
	$(CXX) $< -o $@ -c $(CXXFLAGS) -fPIC

# Rules for building executables
$(ODIR)/%: $(ODIR)/%.o $(OFILES)
	echo "[LD] $< --> $@"
	$(CC) $^ -o $@ $(LDFLAGS)

# Special rule for part1a, since it needs libpart1 on its library path
$(ODIR)/part1a: $(ODIR)/part1a.o $(OFILES) ${ODIR}/libpart1.so
	echo "[LD] $< --> $@"
	$(CC) $^ -o $@ $(LDFLAGS) -L$(ODIR)/ -lpart1

# Rules for building shared objects
$(ODIR)/%.so: %.c
	echo "[CC] $< --> $@"
	$(CC) $< -o $@ $(CFLAGS) $(SOFLAGS)

# Special rule for libpart2, since it needs two .o files and C++ support
$(ODIR)/libpart2.so: $(ODIR)/libpart2.o $(ODIR)/part2.o
	echo "[CXX] $^ --> $@"
	$(CXX) $^ -o $@ $(CXXFLAGS) $(SOFLAGS) -ldl

# clean by clobbering the build folder
clean:
	@echo Cleaning up...
	rm -rf $(ODIR) *.data *.enc

# submit via script
submit:
	@echo "Submitting..."
	~jloew/CSE303/submit-p1.pl

# Include dependencies
-include $(DEPS)
