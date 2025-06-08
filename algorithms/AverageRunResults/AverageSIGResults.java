// ===================================================================================================
// Class   : AverageRunResults
// Purpose : Calculates means and confidence intervals for data set in the following format
//           
//           TrainingError/Accuracy	GeneralizationError/Accuracy	UnlabeledCount
//           
//           READS 30 RECORDS (STOPS EARLY IF MORE IN FILE, ERROR IF LESS IN FILE)
//           EXITS IF VALUES MISSING
//           
// Usage   : java AverageLabelClassificationResults [-error/-accuracy] simFile outFile
// ===================================================================================================

import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;

public class AverageSIGResults {
	
	// ===================================================================================================
	// Method  : main(String[])
	// Purpose : Main method
	// ===================================================================================================
	
	public static void main(String args[]) {
		
		if (args.length != 3) {
			System.err.println("Invalid arguments");
			System.exit(1);
		}
		
		if (args[0].equals("-error")) {
			errorsAsInput = true;
		} else if (args[0].equals("-accuracy")) {
			errorsAsInput = false;
		} else {
			System.err.println("Invalid error specifier");
			System.exit(1);
		}
		
		try {
			readInput(args[1]);
		} catch (FileNotFoundException e) {
			System.err.println("File " + args[1] + " not found");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("IO Error reading");
			System.exit(1);
		}
		
		calcMeasures();
		writeOutput(args[1], args[2]);
	}
	
	// ===================================================================================================
	// Method  : readInput(String)
	// Purpose : Reads input based on file name (a cross validated simulation output file)
	// ===================================================================================================
	
	private static void readInput(String inputFileName) throws FileNotFoundException, IOException {
		
		BufferedReader inputReader;
		inputReader = new BufferedReader(new FileReader(inputFileName));
		
		trainingPerformances = new double[NUM_SIMS];
		trainingMisclassifiedPerformances = new double[NUM_SIMS];
		trainingUnclassifiedPerformances = new double[NUM_SIMS];
		generalizationPerformances = new double[NUM_SIMS];
		generalizationMisclassifiedPerformances = new double[NUM_SIMS];
		generalizationUnclassifiedPerformances = new double[NUM_SIMS];
		totalConditionCounts = new double[NUM_SIMS];
		ruleCounts = new double[NUM_SIMS];
		averageConditionsPerRule = new double[NUM_SIMS];
		totalConjunctiveConditionCounts = new double[NUM_SIMS];
		conjunctiveRuleCounts = new double[NUM_SIMS];
		averageConditionsPerConjunctiveRule = new double[NUM_SIMS];
		
		int recordNumber = 0;
		String readLine = inputReader.readLine();
		
		while ((readLine != null) && (recordNumber != NUM_SIMS)) {
			storeInput(inputFileName, readLine, recordNumber);
			readLine = inputReader.readLine();
			++recordNumber;
		}
		
		if (recordNumber != NUM_SIMS) {
			System.err.println("Too few lines read");
			System.exit(1);
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeTrainingPerformance(String, StringTokenizer, int)
	// Purpose : Stores the training performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeTrainingPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		String token = tokenizer.nextToken();
		
		try {
			trainingPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting training performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeTrainingMisclassifiedPerformance(String, StringTokenizer, int)
	// Purpose : Stores the training misclassified performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeTrainingMisclassifiedPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding training misclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get training misclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			trainingMisclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting training misclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeTrainingUnclassifiedPerformance(String, StringTokenizer, int)
	// Purpose : Stores the training unclassified performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeTrainingUnclassifiedPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding training unclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingUnclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get training unclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			trainingUnclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting training unclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingUnclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeGeneralizationPerformance(String, StringTokenizer, int)
	// Purpose : Stores the generalization performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeGeneralizationPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding generalization performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get generalization performance value
		String token = tokenizer.nextToken();
		
		try {
			generalizationPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting generalization performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeGeneralizationMisclassifiedPerformance(String, StringTokenizer, int)
	// Purpose : Stores the generalization misclassified performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeGeneralizationMisclassifiedPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding generalization misclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get generalization misclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			generalizationMisclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting generalization misclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeGeneralizationUnclassifiedPerformance(String, StringTokenizer, int)
	// Purpose : Stores the generalization unclassified performance measures (either error or accuracy) in the appropriate array
	// ===================================================================================================
	
	private static void storeGeneralizationUnclassifiedPerformance(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding generalization unclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationUnclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get generalization unclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			generalizationUnclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting generalization unclassified performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationUnclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeTotalConditionCount(String, StringTokenizer, int)
	// Purpose : Stores the rule set condition counts in the appropriate array
	// ===================================================================================================
	
	private static void storeTotalConditionCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding rule set condition count, record " + (recordNumber + 1) + ", file " + inputFileName);
			totalConditionCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get rule set condition count value
		String token = tokenizer.nextToken();
		
		try {
			totalConditionCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting rule set condition count, record " + (recordNumber + 1) + ", file " + inputFileName);
			totalConditionCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeRuleCount(String, StringTokenizer, int)
	// Purpose : Stores the rule counts in the appropriate array
	// ===================================================================================================
	
	private static void storeRuleCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			ruleCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get rule count value
		String token = tokenizer.nextToken();
		
		try {
			ruleCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			ruleCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeAverageConditionsPerRule(String, StringTokenizer, int)
	// Purpose : Stores the average conditions per rule counts in the appropriate array
	// ===================================================================================================
	
	private static void storeAverageConditionsPerRule(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding average conditions per rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			averageConditionsPerRule[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get average conditions per rule count value
		String token = tokenizer.nextToken();
		
		try {
			averageConditionsPerRule[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting average conditions per rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			averageConditionsPerRule[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeRuleSetConjunctiveConditionCount(String, StringTokenizer, int)
	// Purpose : Stores the rule set conjunctive condition counts in the appropriate array
	// ===================================================================================================
	
	private static void storeTotalConjunctiveConditionCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding total conjunctive condition count, record " + (recordNumber + 1) + ", file " + inputFileName);
			totalConjunctiveConditionCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get rule set condition count value
		String token = tokenizer.nextToken();
		
		try {
			totalConjunctiveConditionCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting total conjunctive condition count, record " + (recordNumber + 1) + ", file " + inputFileName);
			totalConjunctiveConditionCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeConjunctiveRuleCount(String, StringTokenizer, int)
	// Purpose : Stores the conjunctive rule counts in the appropriate array
	// ===================================================================================================
	
	private static void storeConjunctiveRuleCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding conjunctive rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			conjunctiveRuleCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get rule count value
		String token = tokenizer.nextToken();
		
		try {
			conjunctiveRuleCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting conjunctive rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			conjunctiveRuleCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeAverageConditionsPerConjunctiveRule(String, StringTokenizer, int)
	// Purpose : Stores the average conditions per conjunctive rule counts in the appropriate array
	// ===================================================================================================
	
	private static void storeAverageConditionsPerConjunctiveRule(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding average conditions per conjunctive rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			averageConditionsPerConjunctiveRule[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get average conditions per rule count value
		String token = tokenizer.nextToken();
		
		try {
			averageConditionsPerConjunctiveRule[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting average conditions per conjunctive rule count, record " + (recordNumber + 1) + ", file " + inputFileName);
			averageConditionsPerConjunctiveRule[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : storeInput(String, String, int)
	// Purpose : Tokenizes a single read line, extracts values, and stores them
	// ===================================================================================================
	
	private static void storeInput(String inputFileName, String readLine, int recordNumber) {
		
		StringTokenizer tokenizer = new StringTokenizer(readLine, "\t");
		
		// ignore empty lines
		if (readLine.equals("")) {
			return;
		} else {
			
			if (tokenizer.countTokens() > 12) {
				System.err.print((tokenizer.countTokens() - 12) + " extra values found, record " + (recordNumber + 1));
				System.err.println(", ignoring them");
			}
			
		}
		
		storeTrainingPerformance(inputFileName, tokenizer, recordNumber);
		storeTrainingMisclassifiedPerformance(inputFileName, tokenizer, recordNumber);
		storeTrainingUnclassifiedPerformance(inputFileName, tokenizer, recordNumber);
		storeGeneralizationPerformance(inputFileName, tokenizer, recordNumber);
		storeGeneralizationMisclassifiedPerformance(inputFileName, tokenizer, recordNumber);
		storeGeneralizationUnclassifiedPerformance(inputFileName, tokenizer, recordNumber);
		storeTotalConditionCount(inputFileName, tokenizer, recordNumber);
		storeRuleCount(inputFileName, tokenizer, recordNumber);
		storeAverageConditionsPerRule(inputFileName, tokenizer, recordNumber);
		storeTotalConjunctiveConditionCount(inputFileName, tokenizer, recordNumber);
		storeConjunctiveRuleCount(inputFileName, tokenizer, recordNumber);
		storeAverageConditionsPerConjunctiveRule(inputFileName, tokenizer, recordNumber);
		
	}
	
	// ===================================================================================================
	// Method  : calcMeasures(String)
	// Purpose : Calculates the mean and standard deviation statistics for the stored values
	// ===================================================================================================
	
	private static void calcMeasures() {
		
		meanTrainingPerformance = 0.0;
		meanTrainingMisclassifiedPerformance = 0.0;
		meanTrainingUnclassifiedPerformance = 0.0;
		meanGeneralizationPerformance = 0.0;
		meanGeneralizationMisclassifiedPerformance = 0.0;
		meanGeneralizationUnclassifiedPerformance = 0.0;
		meanTotalConditionCount = 0.0;
		meanRuleCount = 0.0;
		meanAverageConditionsPerRule = 0.0;
		meanTotalConjunctiveConditionCount = 0.0;
		meanConjunctiveRuleCount = 0.0;
		meanAverageConditionsPerConjunctiveRule = 0.0;
		
		// MEANS
		for (int i = 0; i < NUM_SIMS; i++) {
			meanTrainingPerformance += trainingPerformances[i];
			meanTrainingMisclassifiedPerformance += trainingMisclassifiedPerformances[i];
			meanTrainingUnclassifiedPerformance += trainingUnclassifiedPerformances[i];
			meanGeneralizationPerformance += generalizationPerformances[i];
			meanGeneralizationMisclassifiedPerformance += generalizationMisclassifiedPerformances[i];
			meanGeneralizationUnclassifiedPerformance += generalizationUnclassifiedPerformances[i];
			meanTotalConditionCount += totalConditionCounts[i];
			meanRuleCount += ruleCounts[i];
			meanAverageConditionsPerRule += averageConditionsPerRule[i];
			meanTotalConjunctiveConditionCount += totalConjunctiveConditionCounts[i];
			meanConjunctiveRuleCount += conjunctiveRuleCounts[i];
			meanAverageConditionsPerConjunctiveRule += averageConditionsPerConjunctiveRule[i];
		}
		
		meanTrainingPerformance /= (double) NUM_SIMS;
		meanTrainingMisclassifiedPerformance /= (double) NUM_SIMS;
		meanTrainingUnclassifiedPerformance /= (double) NUM_SIMS;
		meanGeneralizationPerformance /= (double) NUM_SIMS;
		meanGeneralizationMisclassifiedPerformance /= (double) NUM_SIMS;
		meanGeneralizationUnclassifiedPerformance /= (double) NUM_SIMS;
		meanTotalConditionCount /= (double) NUM_SIMS;
		meanRuleCount /= (double) NUM_SIMS;
		meanAverageConditionsPerRule /= (double) NUM_SIMS;
		meanTotalConjunctiveConditionCount /= (double) NUM_SIMS;
		meanConjunctiveRuleCount /= (double) NUM_SIMS;
		meanAverageConditionsPerConjunctiveRule /= (double) NUM_SIMS;
		
		stdDevTrainingPerformance = 0.0;
		stdDevTrainingMisclassifiedPerformance = 0.0;
		stdDevTrainingUnclassifiedPerformance = 0.0;
		stdDevGeneralizationPerformance = 0.0;
		stdDevGeneralizationMisclassifiedPerformance = 0.0;
		stdDevGeneralizationUnclassifiedPerformance = 0.0;
		stdDevTotalConditionCount = 0.0;
		stdDevRuleCount = 0.0;
		stdDevAverageConditionsPerRule = 0.0;
		stdDevTotalConjunctiveConditionCount = 0.0;
		stdDevConjunctiveRuleCount = 0.0;
		stdDevAverageConditionsPerConjunctiveRule = 0.0;
		
		// STANDARD DEVIATIONS
		for (int i = 0; i < NUM_SIMS; i++) {
			stdDevTrainingPerformance += Math.pow(trainingPerformances[i] - meanTrainingPerformance, 2.0);
			stdDevTrainingMisclassifiedPerformance += Math.pow(trainingMisclassifiedPerformances[i] - meanTrainingMisclassifiedPerformance, 2.0);
			stdDevTrainingUnclassifiedPerformance += Math.pow(trainingUnclassifiedPerformances[i] - meanTrainingUnclassifiedPerformance, 2.0);
			stdDevGeneralizationPerformance += Math.pow(generalizationPerformances[i] - meanGeneralizationPerformance, 2.0);
			stdDevGeneralizationMisclassifiedPerformance += Math.pow(generalizationMisclassifiedPerformances[i] - meanGeneralizationMisclassifiedPerformance, 2.0);
			stdDevGeneralizationUnclassifiedPerformance += Math.pow(generalizationUnclassifiedPerformances[i] - meanGeneralizationUnclassifiedPerformance, 2.0);
			stdDevTotalConditionCount += Math.pow(totalConditionCounts[i] - meanTotalConditionCount, 2.0);
			stdDevRuleCount += Math.pow(ruleCounts[i] - meanRuleCount, 2.0);
			stdDevAverageConditionsPerRule += Math.pow(averageConditionsPerRule[i] - meanAverageConditionsPerRule, 2.0);
			stdDevTotalConjunctiveConditionCount += Math.pow(totalConjunctiveConditionCounts[i] - meanTotalConjunctiveConditionCount, 2.0);
			stdDevConjunctiveRuleCount += Math.pow(conjunctiveRuleCounts[i] - meanConjunctiveRuleCount, 2.0);
			stdDevAverageConditionsPerConjunctiveRule += Math.pow(averageConditionsPerConjunctiveRule[i] - meanAverageConditionsPerConjunctiveRule, 2.0);
		}
		
		stdDevTrainingPerformance = Math.sqrt(stdDevTrainingPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevTrainingMisclassifiedPerformance = Math.sqrt(stdDevTrainingMisclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevTrainingUnclassifiedPerformance = Math.sqrt(stdDevTrainingUnclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationPerformance = Math.sqrt(stdDevGeneralizationPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationMisclassifiedPerformance = Math.sqrt(stdDevGeneralizationMisclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationUnclassifiedPerformance = Math.sqrt(stdDevGeneralizationUnclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevTotalConditionCount = Math.sqrt(stdDevTotalConditionCount / (((double) NUM_SIMS) - 1.0));
		stdDevRuleCount = Math.sqrt(stdDevRuleCount / (((double) NUM_SIMS) - 1.0));
		stdDevAverageConditionsPerRule = Math.sqrt(stdDevAverageConditionsPerRule / (((double) NUM_SIMS) - 1.0));
		stdDevTotalConjunctiveConditionCount = Math.sqrt(stdDevTotalConjunctiveConditionCount / (((double) NUM_SIMS) - 1.0));
		stdDevConjunctiveRuleCount = Math.sqrt(stdDevConjunctiveRuleCount / (((double) NUM_SIMS) - 1.0));
		stdDevAverageConditionsPerConjunctiveRule = Math.sqrt(stdDevAverageConditionsPerConjunctiveRule / (((double) NUM_SIMS) - 1.0));
		
	}
	
	// ===================================================================================================
	// Method  : writeOutput(String, String)
	// Purpose : Prints output to a file [results.average], adds header if this is the first output
	// ===================================================================================================
	
	private static void writeOutput(String inputFileName, String outputFileName) {
		PrintWriter writer = null;
		boolean exists = (new File(outputFileName)).exists();
		
		try {
			// open writer for appending
			writer = new PrintWriter(new FileWriter(outputFileName, true));
		} catch (IOException e) {
			System.err.println("IO Error creating file " + outputFileName);
			System.exit(1);
		}
		
		if (!exists) {
			if (errorsAsInput) {
				writer.print("simulation" + "\t" + "meanTrainingError" + "\t" + "stdDevTrainingError" + "\t" + "meanTrainingMisclassifiedError" + "\t" + "stdDevTrainingMisclassifiedError" + "\t" + "meanTrainingUnclassifiedError" + "\t" + "stdDevTrainingUnclassifiedError" + "\t" + "meanGeneralizationError" + "\t" + "stdDevGeneralizationError" + "\t" + "meanGeneralizationMisclassifiedError" + "\t" + "stdDevGeneralizationMisclassifiedError" + "\t" + "meanGeneralizationUnclassifiedError" + "\t" + "stdDevGeneralizationUnclassifiedError" + "\t" + "meanTotalConditionCount" + "\t" + "stdDevTotalConditionCount" + "\t" + "meanRuleCount" + "\t" + "stdDevRuleCount" + "\t" + "meanAverageConditionsPerRule" + "\t" + "stdDevAverageConditionsPerRule" + "\t" + "meanTotalConjunctiveConditionCount" + "\t" + "stdDevTotalConjunctiveConditionCount" + "\t" + "meanConjunctiveRuleCount" + "\t" + "stdDevConjunctiveRuleCount" + "\t" + "meanAverageConditionsPerConjunctiveRule" + "\t" + "stdDevAverageConditionsPerConjunctiveRule");
			} else {
				writer.print("simulation" + "\t" + "meanTrainingAccuracy" + "\t" + "stdDevTrainingAccuracy" + "\t" + "meanTrainingMisclassifiedAccuracy" + "\t" + "stdDevTrainingMisclassifiedAccuracy" + "\t" + "meanTrainingUnclassifiedAccuracy" + "\t" + "stdDevTrainingUnclassifiedAccuracy" + "\t" + "meanGeneralizationAccuracy" + "\t" + "stdDevGeneralizationAccuracy" + "\t" + "meanGeneralizationMisclassifiedAccuracy" + "\t" + "stdDevGeneralizationMisclassifiedAccuracy" + "\t" + "meanGeneralizationUnclassifiedAccuracy" + "\t" + "stdDevGeneralizationUnclassifiedAccuracy" + "\t" + "meanTotalConditionCount" + "\t" + "stdDevTotalConditionCount" + "\t" + "meanRuleCount" + "\t" + "stdDevRuleCount" + "\t" + "meanAverageConditionsPerRule" + "\t" + "stdDevAverageConditionsPerRule" + "\t" + "meanTotalConjunctiveConditionCount" + "\t" + "stdDevTotalConjunctiveConditionCount" + "\t" + "meanConjunctiveRuleCount" + "\t" + "stdDevConjunctiveRuleCount" + "\t" + "meanAverageConditionsPerConjunctiveRule" + "\t" + "stdDevAverageConditionsPerConjunctiveRule");
			}
		}
		
		writer.println();
		writer.print(inputFileName + "\t" + meanTrainingPerformance + "\t" + stdDevTrainingPerformance + "\t" + meanTrainingMisclassifiedPerformance + "\t" + stdDevTrainingMisclassifiedPerformance + "\t" + meanTrainingUnclassifiedPerformance + "\t" + stdDevTrainingUnclassifiedPerformance + "\t" + meanGeneralizationPerformance + "\t" + stdDevGeneralizationPerformance + "\t" + meanGeneralizationMisclassifiedPerformance + "\t" + stdDevGeneralizationMisclassifiedPerformance + "\t" + meanGeneralizationUnclassifiedPerformance + "\t" + stdDevGeneralizationUnclassifiedPerformance + "\t" + meanTotalConditionCount + "\t" + stdDevTotalConditionCount + "\t" + meanRuleCount + "\t" + stdDevRuleCount + "\t" + meanAverageConditionsPerRule + "\t" + stdDevAverageConditionsPerRule+ "\t" + meanTotalConjunctiveConditionCount + "\t" + stdDevTotalConjunctiveConditionCount + "\t" + meanConjunctiveRuleCount + "\t" + stdDevConjunctiveRuleCount + "\t" + meanAverageConditionsPerConjunctiveRule + "\t" + stdDevAverageConditionsPerConjunctiveRule);
		writer.close();
		
	}
	
	// ===================================================================================================
	
	// === Constants ===
	private static final int NUM_SIMS = 30;
	
	// === Flags ===
	private static boolean errorsAsInput;
	
	// === Measurements ===
	private static double[] trainingPerformances;
	private static double[] trainingMisclassifiedPerformances;
	private static double[] trainingUnclassifiedPerformances;
	private static double[] generalizationPerformances;
	private static double[] generalizationMisclassifiedPerformances;
	private static double[] generalizationUnclassifiedPerformances;
	private static double[] totalConditionCounts;
	private static double[] ruleCounts;
	private static double[] averageConditionsPerRule;
	private static double[] totalConjunctiveConditionCounts;
	private static double[] conjunctiveRuleCounts;
	private static double[] averageConditionsPerConjunctiveRule;
	
	// === Statistics ===
	private static double meanTrainingPerformance;
	private static double meanTrainingMisclassifiedPerformance;
	private static double meanTrainingUnclassifiedPerformance;
	private static double meanGeneralizationPerformance;
	private static double meanGeneralizationMisclassifiedPerformance;
	private static double meanGeneralizationUnclassifiedPerformance;
	private static double meanTotalConditionCount;
	private static double meanRuleCount;
	private static double meanAverageConditionsPerRule;
	private static double meanTotalConjunctiveConditionCount;
	private static double meanConjunctiveRuleCount;
	private static double meanAverageConditionsPerConjunctiveRule;
	
	private static double stdDevTrainingPerformance;
	private static double stdDevTrainingMisclassifiedPerformance;
	private static double stdDevTrainingUnclassifiedPerformance;
	private static double stdDevGeneralizationPerformance;
	private static double stdDevGeneralizationMisclassifiedPerformance;
	private static double stdDevGeneralizationUnclassifiedPerformance;
	private static double stdDevTotalConditionCount;
	private static double stdDevRuleCount;
	private static double stdDevAverageConditionsPerRule;
	private static double stdDevTotalConjunctiveConditionCount;
	private static double stdDevConjunctiveRuleCount;
	private static double stdDevAverageConditionsPerConjunctiveRule;
	
}