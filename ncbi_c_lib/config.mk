VERSION = 4.2.1

# includes and libs
LIBS = -lpthread

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\"
CFLAGS   = -std=c11 -pedantic -rdynamic -Wextra -Wall ${CPPFLAGS} -g
LDFLAGS  = ${LIBS}

# compiler and linker
CC = gcc
