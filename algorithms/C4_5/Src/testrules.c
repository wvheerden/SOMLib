/*************************************************************************/
/*									 */
/*	Evaluatation of rulesets					 */
/*	------------------------					 */
/*									 */
/*************************************************************************/

#include <stdlib.h>

#include "defns.i"
#include "types.i"
#include "extern.i"
#include "rulex.i"



/*************************************************************************/
/*									 */
/*	Evaluate all rulesets						 */
/*									 */
/*************************************************************************/


    EvaluateRulesets(DeleteRules)
/*  ----------------  */
    Boolean DeleteRules;
{
    short t;
    ItemNo *Errors, Interpret();
    float AvSize=0, AvErrs=0;
    Boolean Final;

    if ( TRIALS == 1 )
    {
	/*  Evaluate current ruleset as there is no composite ruleset  */

	Interpret(0, MaxItem, DeleteRules, true, true);
	return;
    }

    Errors = (ItemNo *) malloc((TRIALS+1) * sizeof(ItemNo));

    ForEach(t, 0, TRIALS)
    {
	NRules    = PRSet[t].SNRules;
	Rule      = PRSet[t].SRule;
	RuleIndex = PRSet[t].SRuleIndex;
	DefaultClass = PRSet[t].SDefaultClass;

	if ( t < TRIALS )
	{
	    printf("\nRuleset %d:\n", t);
	}
	else
	{
	    printf("\nComposite ruleset:\n");
	}

	Final = (t == TRIALS);
	Errors[t] = Interpret(0, MaxItem, DeleteRules, Final, Final);

	AvSize += NRules;
	AvErrs += Errors[t];

	if ( DeleteRules )
	{
	    PRSet[t].SNRules = NRules;
	}
    }

    /*  Print report  */

    printf("\n");
    printf("Trial   Size      Errors\n");
    printf("-----   ----      ------\n");

    ForEach(t, 0, TRIALS)
    {
	if ( t < TRIALS )
	{
	    printf("%4d", t);
	}
	else
	{
	    printf("  **");
	}
	printf("    %4d  %3d(%4.1f%%)\n",
	      PRSet[t].SNRules, Errors[t], 100 * Errors[t] / (MaxItem+1.0));
    }

    AvSize /= TRIALS + 1;
    AvErrs /= TRIALS + 1;
    printf("\t\t\t\tAv size = %.1f,  av errors = %.1f (%.1f%%)\n",
	   AvSize, AvErrs, 100 * AvErrs / (MaxItem+1.0));
}



/*************************************************************************/
/*									 */
/*	Evaluate current ruleset					 */
/*									 */
/*************************************************************************/


float	Confidence;		/* certainty factor of fired rule */
				/* (set by BestRuleIndex) */


ItemNo Interpret(Fp, Lp, DeleteRules, CMInfo, Arrow)
/*     ---------  */
    ItemNo Fp, Lp;
    Boolean DeleteRules, CMInfo, Arrow;
{
    ItemNo i, Tested=0, Errors=0, *Better, *Worse, *ConfusionMat;
    Boolean FoundRule;
    ClassNo AssignedClass, AltClass;
    Attribute Att;
    RuleNo p, Bestr, ri, ri2, riDrop=0, BestRuleIndex();
    float ErrorRate, BestRuleConfidence;

    if ( CMInfo )
    {
	ConfusionMat = (ItemNo *) calloc((MaxClass+1)*(MaxClass+1), sizeof(ItemNo));
    }

    ForEach(ri, 1, NRules)
    {
	p = RuleIndex[ri];
	Rule[p].Used = Rule[p].Incorrect = 0;
    }

    Better = (ItemNo *) calloc(NRules+1, sizeof(ItemNo));
    Worse  = (ItemNo *) calloc(NRules+1, sizeof(ItemNo));

    ForEach(i, Fp, Lp)
    {
	/*  Find first choice for rule for this item  */
	/*  First choice is the rule with the highest firing strength  */

	ri = BestRuleIndex(Item[i], 1);
	Bestr = ( ri ? RuleIndex[ri] : 0 );
	FoundRule = Bestr > 0;

	if ( FoundRule )
	{
	    Rule[Bestr].Used++;
	    AssignedClass =  Rule[Bestr].Rhs;
	    BestRuleConfidence = Confidence;

	    /*  Now find second choice  */
	    /*  Second choice is the rule with the next highest firing strength, after the first choice (could be the default rule)  */

	    ri2 = BestRuleIndex(Item[i], ri+1);
	    AltClass = ( ri2 ? Rule[RuleIndex[ri2]].Rhs : DefaultClass );

	    /*  If the second choice predicted class is not the same as the first choice predicted class  */
	    /*  This means that eliminating the first choice would change the data example classification  */
	    /*  If both choices match, the removal of the first choice would not change the performance for this example, so it is ignored  */
	    if ( AltClass != AssignedClass )
	    {
		/*  If class assigned by first choice matches the data example's class, removal of the first choice causes a misclassification  */
		/*  Therefore, add one to the "better count" for this rule  */
		if ( AssignedClass == Class(Item[i]) )
		{
		    Better[ri]++;
		}
		else
		/*  If class assigned by second choice matches the data example's class, removal of the first choice causes a correct classification  */
		/*  Therefore, add one to the "worse count" for this rule  */
		if ( AltClass == Class(Item[i]) )
		{
		    Worse[ri]++;
		}
	    }
	}
	else
	{
	    /*  No rule matched the data example, so the default rule is used  */
	    AssignedClass = DefaultClass;
	}
	
	if ( CMInfo )
	{
	    ConfusionMat[Class(Item[i])*(MaxClass+1)+AssignedClass]++;
	}
	Tested++;

	if ( AssignedClass != Class(Item[i]) )
	{
	    Errors++;
	    if ( FoundRule ) Rule[Bestr].Incorrect++;

	    Verbosity(3)
	    {
	    	printf("\n");
	    	ForEach(Att, 0, MaxAtt)
	    	{
	    	    printf("\t%s: ", AttName[Att]);
	    	    if ( MaxAttVal[Att] )
	    	    {
	    		if ( DVal(Item[i],Att) )
			{
	    		    printf("%s\n", AttValName[Att][DVal(Item[i],Att)]);
			}
	    		else
			{
	    		    printf("?\n");
			}
	    	    }
	    	    else
	    	    {
	    		if ( CVal(Item[i],Att) != Unknown )
			{
	    		    printf("%g\n", CVal(Item[i],Att));
			}
	    		else
			{
	    		    printf("?\n");
			}
	    	    }
	    	}
	    	printf("\t%4d:\tGiven class %s,", i, ClassName[Class(Item[i])]);
	    	if ( FoundRule )
	    	{
	    	    printf(" rule %d [%.1f%%] gives class ",
	    		    Bestr, 100 * BestRuleConfidence);
	    	}
	    	else
		{
	    	    printf(" default class ");
		}
	    	printf("%s\n", ClassName[AssignedClass]);
	    }
	}
    }

    printf("\nRule  Size  Error  Used  Wrong\t          Advantage\n");
    printf(  "----  ----  -----  ----  -----\t          ---------\n");
    ForEach(ri, 1, NRules)
    {
	p = RuleIndex[ri];
	if ( Rule[p].Used > 0 )
	{
	    ErrorRate = Rule[p].Incorrect / (float) Rule[p].Used;

	    printf("%4d%6d%6.1f%%%6d%7d (%.1f%%)\t%6d (%d|%d) \t%s\n",
		    p, Rule[p].Size,
		    100 * Rule[p].Error, Rule[p].Used, Rule[p].Incorrect,
		    100 * ErrorRate,
		    Better[ri]-Worse[ri], Better[ri], Worse[ri],
		    ClassName[Rule[p].Rhs]);

	    /*  See whether this rule should be dropped.  Note: can only drop
		one rule at a time, because Better and Worse are affected  */
	    /*  We remove a rule if this is the first rule we're dropping (we can't drop more than one at a time),
	        and the "worse count" exceeds the "better count" (in other words, removing the rule causes more
	        correct classifications than misclassifications)  */
	    if ( DeleteRules && ! riDrop && Worse[ri] > Better[ri] )
	    {
		riDrop = ri;
	    }
	}
    }

    cfree(Better);
    cfree(Worse);

    if ( riDrop )
    {
	printf("\nDrop rule %d\n", RuleIndex[riDrop]);

	ForEach(ri, riDrop+1, NRules)
	{
	    RuleIndex[ri-1] = RuleIndex[ri];
	}
	NRules--;
    
	if ( CMInfo ) free(ConfusionMat);
	return Interpret(Fp, Lp, DeleteRules, true, Arrow);
    }
    else
    {
	printf("\nTested %d, errors %d ( %.16f %%)%s\n",
	    Tested, Errors, 100 * Errors / (float) Tested,
	    ( Arrow ? "   <<" : "" ));
    }

    if ( CMInfo )
    {
	PrintConfusionMatrix(ConfusionMat);
	free(ConfusionMat);
    }

    return Errors;
}



/*************************************************************************/
/*									 */
/*	Find the best rule for the given case, leaving probability       */
/*      in Confidence							 */
/*									 */
/*************************************************************************/


RuleNo BestRuleIndex(CaseDesc, Start)
/*     ---------------  */
    Description CaseDesc;
    RuleNo Start;
{
    RuleNo r, ri;
    float Strength();

    ForEach(ri, Start, NRules)
    {
	r = RuleIndex[ri];
	Confidence = Strength(Rule[r], CaseDesc);

	if ( Confidence > 0.1 )
	{
	    return ri;
	}
    }

    Confidence = 0.0;
    return 0;
}
