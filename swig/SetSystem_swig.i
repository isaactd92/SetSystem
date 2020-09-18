/* -*- c++ -*- */

#define SETSYSTEM_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "SetSystem_swig_doc.i"

%{
#include "SetSystem/SetSystem.h"
%}


%include "SetSystem/SetSystem.h"
GR_SWIG_BLOCK_MAGIC2(SetSystem, SetSystem);
