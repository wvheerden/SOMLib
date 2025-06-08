# SccsId = "@(#)Makefile 5.1 9/25/91 MLT" 

BINDIR = "../bin"

.KEEP_STATE:

# ----------------------------------------------------------------------
# Uncomment the proper CFLAGS line for your machine.
# ----------------------------------------------------------------------

# SunOS (compiles as original distribution)
# CFLAGS = -g -D_TTYOLD -D_HAVE_LOG2 -D_USE_TIOCSTI

# SunOS (if you want to use termios rather than old-style terminal I/O)
#CFLAGS = -g -D_HAVE_LOG2 -D_USE_TIOCSTI

# Solaris - note that you will need to use the LIBS defined here, and
# comment out the LIBS line later in this file. If you forget to
# do this, then the filename completion in the CN2 interactive
# loop will produce names with the first two characters "chopped off".
# CFLAGS = -g -D_HAVE_FLOAT_H -D_USE_TIOCSTI
# LIBS = -lc -lm -ll /usr/ucblib/libucb.a

# HP-UX 
# CFLAGS = -g -D_HAVE_FLOAT_H -D_HAVE_LOG2

# IRIX 
# CFLAGS = -g -cckr -D_HAVE_FLOAT_H

# Linux
CFLAGS = -D_HAVE_FLOAT_H -D_HAVE_LOG2

LIBS = -lm

# USERS: You probably won't want to modify anything below this line.
# ----------------------------------------------------------------------
# Debugging flags: DEBUG_INPUT STATS NODE_COUNT -f68881 -g -QF_CHECK
# -a (for tcov) -pg (for gprof)
# Actually QF_CHECK is defined in quickfit.c, so you get it 
# automatically

HEADERS = cn_header.h cn_externs.h mdep.h mlt_float.h

SOURCES = cn.c cn_print_thing.c ckrl_gen.c ckrl_rules.c create.c main.c print_gen_thing.c \
          execute.c robin.c\
          test.c attribute.c att_order.c list.c names.c quickfit.c \
          interact.c interact_utils.c example.c peccles.c \
          rule_reader.c \
          heap.c specialise.c filter.c trace.c debug.c

OBJECTS = cn.o cn_print_thing.o ckrl_gen.o ckrl_rules.o create.o main.o print_gen_thing.o \
          execute.o robin.o\
          test.o attribute.c att_order.o list.o names.o quickfit.o \
          interact.o interact_utils.o example.o peccles.o \
          rule_reader.o \
          heap.o specialise.o filter.o trace.o debug.o \
          y.tab.o

cn:	$(OBJECTS)
	cc $(CFLAGS) -o cn $(OBJECTS) $(LIBS)

saber_src:    y.tab.o  $(SOURCES) $(HEADERS)
	#load $(CFLAGS) $(SOURCES) y.tab.c $(LIBS)

saber_obj:    
	#load $(CFLAGS) $(OBJECTS) $(LIBS)


cn_header.h: mlt_float.h

main.o:	cn_header.h cn_externs.h main.c

ckrl_gen.o:	cn_header.h cn_externs.h ckrl_gen.c

ckrl_rules.o:	cn_header.h cn_externs.h ckrl_rules.c

create.o:	cn_header.h cn_externs.h create.c

debug.o:	debug.c

peccles.o:	cn_header.h cn_externs.h peccles.c

execute.o:	cn_header.h cn_externs.h execute.c

robin.o:	cn_header.h cn_externs.h robin.c

rule_reader.o:	cn_header.h cn_externs.h rule_reader.c

specialise.o:	cn_header.h cn_externs.h specialise.c

heap.o:		cn_header.h cn_externs.h heap.c

attribute.o:	cn_header.h cn_externs.h attribute.c

att_order.o:	cn_header.h cn_externs.h att_order.c

list.o:		cn_header.h cn_externs.h list.c

example.o:	cn_header.h cn_externs.h example.c

filter.o:	cn_header.h cn_externs.h filter.c

trace.o:	cn_header.h cn_externs.h trace.c

interact_utils.o: cn_header.h cn_externs.h interact_utils.c

interact.o: cn_header.h cn_externs.h interact.c

logs.o:		cn_header.h cn_externs.h logs.c

test.o:		cn_header.h cn_externs.h test.c

lex.yy.c:	ingest.l
	lex ingest.l

print_gen_thing.o:	cn_header.h cn_externs.h print_gen_thing.c

cn_print_thing.o:	cn_header.h cn_externs.h cn_print_thing.c

names.o:	cn_header.h cn_externs.h names.c

quickfit.o:	cn_header.h cn_externs.h quickfit.c

cn_header.h:	qlalloc.h mdep.h

y.tab.o:	y.tab.c lex.yy.c
	cc $(CFLAGS) -c  y.tab.c 

y.tab.c:	ingest.y lex.yy.c
	yacc ingest.y

clean:
	rm -f *.o y.tab.c lex.yy.c cn

