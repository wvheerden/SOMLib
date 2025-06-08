#*************************************************************************#
#*									 *#
#*		Makefile for the C4.5 induction system			 *#
#*		--------------------------------------			 *#
#*									 *#
#*************************************************************************#


#	Set CFLAGS for your C compiler, e.g.
#
#	  * if you need to debug the programs (sorry about that!)
#	      CFLAGS = -g
#	    (You might also want to reactivate the lint commands that
#	    have been commented out below.)
#
#	  * if your C compiler supports higher optimization levels
#	      CFLAGS = -O3 etc


CFLAGS = -O2


#	Definitions of file sets

core = \
	getnames.o getdata.o trees.o getopt.o header.o

trees = \
	besttree.o build.o info.o discr.o contin.o subset.o prune.o\
	stats.o st-thresh.o classify.o confmat.o sort.o $(core)

rules = \
	rules.o genlogs.o genrules.o makerules.o prunerule.o\
	siftrules.o testrules.o stats.o confmat.o sort.o $(core)

#  Make everything

all:
	make c4.5
	make c4.5rules
	make consult
	make consultr
	cc -o xval-prep xval-prep.c
	cc -o average average.c -lm

#  C4.5 decision tree generator

c4.5: c4.5.o $(trees)
	cc -o c4.5 c4.5.o $(trees) -lm

#  C4.5 production rule generator

c4.5rules: c4.5rules.o $(rules)
	cc -o c4.5rules c4.5rules.o $(rules) -lm

#  C4.5 decision tree interpreter

consult: consult.o userint.o $(core)
	cc -o consult consult.o userint.o $(core)

#  C4.5 production rule interpreter

consultr: consultr.o rules.o userint.o $(core)
	cc -o consultr consultr.o rules.o userint.o $(core)

.c.o:
	cc $(CFLAGS) -c $<

clean:
	rm -f *.o c4.5 c4.5rules consult consultr average xval-prep

$(trees): defns.i types.i extern.i
$(rules): defns.i types.i extern.i
