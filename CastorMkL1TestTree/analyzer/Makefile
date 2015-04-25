SHELL:=/bin/sh

CXX:=g++

CXXFLAGS:=-std=c++11 -o2 -Wall
#CXXFLAGS:=-o2 -Wall
CXXFLAGS+=$(shell root-config --cflags)

LDFLAGS:=-lboost_program_options
LDFLAGS+=$(shell root-config --libs)

all: CastorL1MkTreeAnalyzer

CastorL1MkTreeAnalyzer: CastorL1MkTreeAnalyzer.cc
	$(CXX) $(CXXFLAGS) CastorL1MkTreeAnalyzer.cc $(LDFLAGS) -o CastorL1MkTreeAnalyzer