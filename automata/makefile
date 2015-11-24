######################################################################
#--------------------------------------------------------------------#
#---------------------------- COMMENTS ------------------------------#
#--------------------------------------------------------------------#
######################################################################

#---------------------------------------------------------------------
#
# Structure.
#
# This Makefile is split into:
# 1) Variables Section
# 	1.1) Dynamic subsection
# 	1.2) Static subsection - DO NOT MODIFY
# 2) Rules Section
# 	2.1) Static subsection - DO NOT MODIFY
# 	2.2) Dynamic subsection
# 3) Dependency Graph - DO NOT MODIFY
#
#
# As a user of this makefile You should not be modifing
# any of the static subsections.
#
#---------------------------------------------------------------------
#
# Compilers supported:
#
# 1) g++
# 2) nvcc
#
#---------------------------------------------------------------------
#
# Supports a particular project structure:
# Refer to Project Structure section to define the following folders:
#
# 1) INC: Header files of this application
# 2) LIB: Your, local Libraries to be linked with application
# 3) BLD: Build where your compiled object files are stored
# 4) SRC: Source files of this application
# 5) BIN: Binary files, executables of the application
#
#---------------------------------------------------------------------
#
# Tips:
#
# Use '\' to break new line
# Take special care of whitespaces, it might cause errors.
# $@ is the value of target
# $^ is the list of all prerequisites of the rule
# $< is just the first prerequisite
#
#---------------------------------------------------------------------
#
# TODO:
# (Lack of these features might cause bugs)
#
# Realese / Debug
# Support for gcc for .c files
# Currently only one extension per XX_EXT variable applies
# Support for unit tests
# Variable printouts
# Add usage
#
#---------------------------------------------------------------------
#
# Author:
#
# github.com/Jakub-Ciecierski
# jakub.ciecier@gmail.com
#
#---------------------------------------------------------------------
#
# For further information refer to:
# http://www.gnu.org/software/make/manual/make.html
#
#---------------------------------------------------------------------
#
# Changes log:
# 01.07.2015 - Created
# 26.10.2015 - Added Unit Test rule
# 08.11.2015 - OpenGL and CUDA libraries commented out
# 12.11.2015 - Added each module in include separately.
#	For example.
#	File:
#		./include/math/clustering/kmeans.h
#	can be included as:
#		#include "kmeans.h"
#	or:
#		#include "math/clustering/kmeans.h"
#
#---------------------------------------------------------------------


######################################################################
#--------------------------------1-----------------------------------#
#------------------------ VARIABLES SECTION -------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################


#--------------- APPLICATION NAME -------------#

APP_NAME = automaton

#--------------- FILE EXTENSIONS --------------#

# c++ extension
CPP_EXT = .cpp
# cuda extension
CUDA_EXT = .cu

#-------------- PROJECT STRUCTURE -------------#

# Your header files
INC = include
# Your local libraries to be linked with the application
LIB = lib
# Build dumper. All your object files (*.o) will be located here
OBJ = build
# Source files and only source files, subdirectories are supported.
SRC = src
# Executables of your Application
BIN = bin
# Unit tests
TST = test

#------------- EXTERNAL MAKEFILES -------------#

# Paths to the Makefiles to be ran before this Makefile.
# Default target will be executed. (TODO verify this)
# Can be used to compile your static libraries before linking.
# Surrounded the path with '...' and separate different paths
# with a space.
MAKE_EXTERNAL =

#---------------- LIBRARIES -------------------#

# Paths and names of libraries to link with
LIBS += -lpthread
# -L /opt/cuda/lib64 \
#		-L /usr/local/cuda/lib64 \
#		-lGL -lglut -lGLEW -lcudart -lcuda

#----------------- INCLUDES -------------------#

# Paths to all Includes
INCLUDES += -I /usr/local/cuda/include \
			-I /opt/cuda/include

#------------------- FLAGS --------------------#

# Use '-static' for static libraries
# Use '-shared' for shared libraries
L_FLAGS +=
C_FLAGS += -g -Wall -std=c++11
NVCC_FLAGS += -arch=sm_20


#----------------- PRINT OUTS -----------------#

# The separator will be printed between compiling objects
INFO_SEPARATOR = "|-------------------------------------------------------------------|"
INFO_FILLER = "  <<  "


######################################################################
#------------------ STATIC SUBSECTION - DO NOT MODIFY ---------------#
######################################################################

# Adds each modules in include separately.
INC_MODULES =  $(addprefix -I , $(shell find ${INC} -type d 2>/dev/null))

LIBS += -L ${LIB}
INCLUDES += ${INC_MODULES}

CC = g++
NVCC = nvcc

L_FLAGS += ${LIBS}
C_FLAGS += ${INCLUDES} -MMD
NVCC_FLAGS +=

# All source files
# [2>/dev/null] is added to supresss the 'file not found'
# message when inititing project structure for the first time
# (src file does not exist at the beginning)
CPP_SOURCES = $(shell find ${SRC} -name *${CPP_EXT} 2>/dev/null)
CUDA_SOURCES = $(shell find ${SRC} -name *${CUDA_EXT} 2>/dev/null)

# List of all subdirectories in source directory
MODULES = $(shell find ${SRC} -type d 2>/dev/null)

# All objects to be compiled
OBJECTS += $(addprefix ${OBJ}/,$(notdir $(CPP_SOURCES:${CPP_EXT}=.o)))
OBJECTS += $(addprefix ${OBJ}/,$(notdir $(CUDA_SOURCES:${CUDA_EXT}=.o)))

# Add modules to vpath
VPATH = ${MODULES}

######################################################################
#---------------------------------2----------------------------------#
#------------------------------ RULES -------------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ STATIC SUBSECTION - DO NOT MODIFY ---------------#
######################################################################

#------------------ DEFAULT -------------------#

# All
all: rel utest

# Release rule
rel: $(MAKE_EXTERNAL) info_prefix init ${APP_NAME} info_suffix

# Debug rule
debug:
	@echo 'Debug TODO'

# Unit Test rule, assumes that $(TST) has a makefile inside
utest:
	@$(MAKE) -C $(TST)

#------------------ LINKER --------------------#

${APP_NAME}: ${OBJECTS}
	@$(CC) -o ${BIN}/${APP_NAME} $^ $(L_FLAGS)

#----------------- COMPILERS ------------------#

# cpp compiler
$(OBJ)/%.o: %${CPP_EXT}
	@echo ${INFO_SEPARATOR}
	@echo 'COMPILING: ' $<
	@echo
	@$(CC) $(C_FLAGS) -c -o $@ $<

# cuda compiler
${OBJ}/%.o: %${CUDA_EXT}
	@echo ${INFO_SEPARATOR}
	@echo 'COMPILING: ' $<
	@echo
	@$(NVCC) $(NVCC_FLAGS) -c -o $@ $<

#------------------ EXTERNALS -----------------#

# Make external makefiles
$(MAKE_EXTERNAL):
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External: $@'
	@echo ${INFO_SEPARATOR}
	@$(MAKE) -C $@
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External $@ Finished'
	@echo

#---------------- UTILITY RULES ---------------#

# Creates all the directories of the project
init:
	@mkdir -p ${OBJ} ${BIN} ${SRC} ${LIB} ${INC} ${TST}

clean:
	@$(RM) *.o *~ ${OBJ}/*.o ${OBJ}/*.d ${OBJ}/*~ ${BIN}/*
	@$(MAKE) -C $(TST) clean


.PHONY: $(SUBDIRS) clean

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################

#----------------- PRINT RULES ----------------#

info_prefix:
	@echo
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER}"MAKING:" ${APP_NAME}
	@echo
	@echo

info_suffix:
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER}"LINKING SUCCESSFULL"
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo

######################################################################
#---------------------------------3----------------------------------#
#---------------- DEPENDENCY GRAPH - DO NOT MODIFY ------------------#
#--------------------------------------------------------------------#
######################################################################

#--------------- DEPENDENCY GRAPH -------------#

# Automatic dependency graph generation
# Must be inserted at the end of the makefile
-include $(OBJECTS:.o=.d)
