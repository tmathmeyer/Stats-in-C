# See LICENSE file for copyright and license details.

include config.mk

all: libncbi

libncbi: http.o ncbi_translation.o

.c.o: config.mk
	@echo CC -c $<
	@${CC} -c $< ${CFLAGS}

libncbi libncbi_path:
	@echo CC -o $@
	@${CC} -o $@ $+ ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f libncbi *.o

update: clean all
