/*************************************************************************/
/*									 */
/*  Main routine for constructing sets of production rules from trees	 */
/*  -----------------------------------------------------------------	 */
/*									 */
/*************************************************************************/

#include <stdlib.h>

#include "defns.i"
#include "types.i"

	/*  External data.  Note: uncommented variables have the same meaning
	    as for decision trees  */

short		MaxAtt, MaxClass, MaxDiscrVal;

ItemNo		MaxItem;

Description	*Item;

DiscrValue	*MaxAttVal;

char		*SpecialStatus;

String		*ClassName,
		*AttName,
		**AttValName,
		FileName = "DF";

short		VERBOSITY = 0,
		TRIALS;

Boolean		UNSEENS	  = false,
		UNSEENTRAIN = false,
		SIGTEST	  = false,	/* use significance test in rule pruning */
		SIMANNEAL = false;	/* use simulated annealing */

float		SIGTHRESH   = 0.05,
		CF	    = 0.25,
		REDUNDANCY  = 1.0;	/* factor that guesstimates the
					   amount of redundancy and
					   irrelevance in the attributes */

PR		*Rule;			/* current rules */

RuleNo		NRules = 0,		/* number of current rules */
		*RuleIndex;		/* rule index */

short		RuleSpace = 0;		/* space allocated for rules */

ClassNo		DefaultClass;		/* current default class */

RuleSet		*PRSet;			/* sets of rulesets */

float		AttTestBits,		/* bits to encode tested att */
		*BranchBits;		/* ditto attribute value */



    main(Argc, Argv)
/*  ----  */
    int Argc;
    char *Argv[];
{
    int o;
    extern char *optarg;
    extern int optind;
    Boolean FirstTime=true;

    PrintHeader("rule generator");

    /*  Process options  */

    while ( (o = getopt(Argc, Argv, "f:utv:c:r:F:a")) != EOF )
    {
	if ( FirstTime )
	{
	    printf("\n    Options:\n");
	    FirstTime = false;
	}

	switch (o)
	{
	    case 'f':	FileName = optarg;
			printf("\tFile stem <%s>\n", FileName);
			break;
	    case 'u':	UNSEENS = true;
			printf("\tRulesets evaluated on unseen test cases\n");
			break;
	    case 't':	UNSEENTRAIN = true;
			printf("\tRulesets evaluated on unseen training cases\n");
			break;
	    case 'v':	VERBOSITY = atoi(optarg);
			printf("\tVerbosity level %d\n", VERBOSITY);
			break;
	    case 'c':	CF = atof(optarg);
			printf("\tPruning confidence level %g%%\n", CF);
			Check(CF, 0, 100);
			CF /= 100;
			break;
	    case 'r':	REDUNDANCY = atof(optarg);
			printf("\tRedundancy factor %g\n", REDUNDANCY);
			Check(REDUNDANCY, 0, 10000);
			break;
	    case 'F':	SIGTHRESH = atof(optarg);
			printf("\tSignificance test in rule pruning, ");
			printf("threshold %g%%\n", SIGTHRESH);
			Check(SIGTHRESH, 0, 100);
		 	SIGTHRESH /= 100;
			SIGTEST = true;
			break;
	    case 'a':	SIMANNEAL = true;
			printf("\tSimulated annealing for selecting rules\n");
			break;
	    case '?':	printf("unrecognised option\n");
			exit(1);
	}
    }

    /*  Initialise  */

    GetNames();
    GetData(".data");
    printf("\nRead %d cases (%d attributes) from %s\n",
	   MaxItem+1, MaxAtt+1, FileName);

    GenerateLogs();

    /*  Construct rules  */

    GenerateRules();

    /*  Evaluations  */

    /*  And THIS is where the final pruning of rules occurs, based on overall classification errors  */
    printf("\n\nEvaluation on training data (%d items):\n", MaxItem+1);
    EvaluateRulesets(true);

    /*  Save current ruleset  */

    SaveRules();

    if ( UNSEENTRAIN )
    {
	GetData(".train");
	printf("\nEvaluation on unseen training data (%d items):\n", MaxItem+1);
	EvaluateRulesets(false);
    }

    if ( UNSEENS )
    {
	GetData(".test");
	printf("\nEvaluation on unseen test data (%d items):\n", MaxItem+1);
	EvaluateRulesets(false);
    }

    exit(0);
}
