HEADERS=-I../../inst/include -I../adolc

# FROM ADOLC 2-4.0 Makefile.am
# No Sparse as no ColPack
#AM_CFLAGS            = @ac_adolc_cflags@ -DADOLC_INTERNAL=1 -std=gnu99
#AM_CXXFLAGS          = @ac_adolc_cxxflags@ -DADOLC_INTERNAL=1
# What are these @ac_adolc_cflags@ etc?
# After grepping, looks like standard flags like -O2 -g -Wall -ansi etc
#AM_CPPFLAGS          = -I$(top_srcdir)/ADOL-C/include -I$(top_srcdir)/ADOL-C/src
#
#
#libadolc_la_SOURCES  = adalloc.c malloc.c adouble.cpp \
#                       convolut.c fortutils.c\
#                       interfaces.cpp interfacesf.c \
#                       taping.c tape_handling.cpp \
#                       zos_forward.c fos_forward.c fov_forward.c \
#                       hos_forward.c hov_forward.c hov_wk_forward.c \
#                       fos_reverse.c fov_reverse.c \
#                       hos_reverse.c hos_ov_reverse.c hov_reverse.c \
#                       forward_partx.c \
#                       externfcts.cpp checkpointing.cpp \
#                       fixpoint.cpp fov_offset_forward.c revolve.c advector.cpp
#
#libadolc_la_LIBADD   = drivers/libdrivers.la tapedoc/libtapedoc.la

# Need to define many other flags - e.g. are we using malloc and so on
# Many of these are defined in the config.h file - so why isn't that being used?
#ADOLC_CXXFLAGS= -DADOLC_INTERNAL=1 -DADOLC_VERSION=2 -DADOLC_SUBVERSION=4 -DADOLC_PATCHLEVEL=0 -DADOLC_USE_CALLOC=1
#ADOLC_CFLAGS= -DADOLC_INTERNAL=1 -std=gnu99 -DADOLC_VERSION=2 -DADOLC_SUBVERSION=4 -DADOLC_PATCHLEVEL=0 -DADOLC_USE_CALLOC=1

# Need to set the HAVE_CONFIG_H flag
# This makes the compilation use the config.h file to set all the flags
# Problem is, this config.h file is particular to each distribution and set up
# e.g. Windows one will be different to Linux
# Also sets Open_MP flags and so on
# How to get round this? Use the ADOLC configure command and put inside package?
ADOLC_CXXFLAGS= -DADOLC_INTERNAL=1 -DHAVE_CONFIG_H
ADOLC_CFLAGS= -DADOLC_INTERNAL=1 -std=gnu99 -DHAVE_CONFIG_H 

ADCSRCS  = adalloc.c malloc.c adouble.cpp \
                       convolut.c fortutils.c\
                       interfaces.cpp interfacesf.c \
                       taping.c tape_handling.cpp \
                       zos_forward.c fos_forward.c fov_forward.c \
                       hos_forward.c hov_forward.c hov_wk_forward.c \
                       fos_reverse.c fov_reverse.c \
                       hos_reverse.c hos_ov_reverse.c hov_reverse.c \
                       forward_partx.c \
                       externfcts.cpp checkpointing.cpp \
                       fixpoint.cpp fov_offset_forward.c revolve.c advector.cpp
ADCOBJS := $(ADCSRCS:.c=.o)
ADCOBJS := $(ADCOBJS:.cpp=.o)


# These are repeated in their own folders - not very neat
DRVOBJS = drivers/drivers.o drivers/driversf.o drivers/odedrivers.o drivers/odedriversf.o drivers/taylor.o 
TAPOBJS= tapedoc/tapedoc.o
#SPAOBJS=sparse/int_forward_s.o sparse/int_forward_t.o \
#	sparse/int_reverse_s.o sparse/int_reverse_t.o \
#	sparse/jacutils.o sparse/sparse.o sparse/sparsedrivers.o \
#	sparse/graph_hess.o sparse/graph_jac.o sparse/hessutils.o
#


#ADCSRCS := $(wildcard *.c) $(wildcard *.cpp)
#ADCOBJS := $(ADCSRCS:.c=.o)
#ADCOBJS := $(ADCOBJS:.cpp=.o)


library: lib

# What is this -fPIC thing?
%.o: %.c
	@echo CC  $<
	@${CC} ${HEADERS} ${ADOLC_CFLAGS} -fPIC -c $<

%.o: %.cpp
	@echo CXX $<
	@${CXX} ${HEADERS} ${ADOLC_CXXFLAGS} -fPIC -c $<

# ALso named in root directory - not very robust
LIB = ../adolc.a

lib: $(LIB)

#$(LIB): $(ADCOBJS)
#	@make -C drivers -f Makefile library
#	@make -C sparse -f Makefile library
#	@make -C tapedoc -f Makefile library
#	@${AR} -rucs $(LIB) ${ADCOBJS} ${DRVOBJS} ${SPAOBJS} ${TAPOBJS}

# -rucs?
# No sparse folder as no ColPack
$(LIB): $(ADCOBJS)
	@make -C drivers -f Makefile library
	@make -C tapedoc -f Makefile library
	@${AR} -rucs $(LIB) ${ADCOBJS} ${DRVOBJS} ${TAPOBJS}

clean:
		@-rm -f $(LIB)
		@-rm -f $(ADCOBJS)
		@make -C drivers -f Makefile clean
		@make -C tapedoc -f Makefile clean
