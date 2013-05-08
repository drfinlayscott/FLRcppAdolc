HEADERS=-I../../../inst/include -I../

ADOLC_CFLAGS   = -DADOLC_INTERNAL=1
ADOLC_CXXFLAGS = -DADOLC_INTERNAL=1

TAPOBJS= tapedoc.o

%.o: %.c
	@echo CC  $<
	@${CC} -fPIC ${HEADERS} ${ADOLC_CFLAGS} -c $<

library: $(TAPOBJS)

clean:
	@-rm -f *.o







