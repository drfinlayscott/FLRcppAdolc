HEADERS=-I../../../inst/include -I../

# Taken from Makefile.am
ADOLC_CFLAGS = -DADOLC_INTERNAL=1

DRVOBJS =drivers.o driversf.o odedrivers.o odedriversf.o taylor.o 
#DRVOBJS := $(DRVSRCS:.c=.o)

%.o: %.c
	@echo CC  $<
	@${CC} -fPIC ${HEADERS} ${ADOLC_CFLAGS} -c $<

library: $(DRVOBJS)

clean:
	@-rm -f *.o
