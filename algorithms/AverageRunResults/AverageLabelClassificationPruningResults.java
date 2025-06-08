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

public class AverageLabelClassificationPruningResults {
	
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
		unlabeledNeuronCounts = new double[NUM_SIMS];
		unlabeledNeuronPercentages = new double[NUM_SIMS];
		prunedNeuronCounts = new double[NUM_SIMS];
		prunedNeuronPercentages = new double[NUM_SIMS];
		unprunedNeuronCounts = new double[NUM_SIMS];
		unprunedNeuronPercentages = new double[NUM_SIMS];
		
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
			System.err.println("Error finding training misclassification performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			trainingMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get training misclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			trainingMisclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting training misclassification performance, record " + (recordNumber + 1) + ", file " + inputFileName);
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
			System.err.println("Error finding generalization misclassification performance, record " + (recordNumber + 1) + ", file " + inputFileName);
			generalizationMisclassifiedPerformances[recordNumber] = 100.0;
			return;
		}
		
		// get generalization misclassified performance value
		String token = tokenizer.nextToken();
		
		try {
			generalizationMisclassifiedPerformances[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting generalization misclassification performance, record " + (recordNumber + 1) + ", file " + inputFileName);
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
	// Method  : void storeUnlabeledNeuronCount(String, StringTokenizer, int)
	// Purpose : Stores the unlabeled neuron counts in the appropriate array
	// ===================================================================================================
	
	private static void storeUnlabeledNeuronCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding unlabeled neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			unlabeledNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get unlabeled neuron count value
		String token = tokenizer.nextToken();
		
		try {
			unlabeledNeuronCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting unlabeled neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			unlabeledNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeUnlabeledNeuronPercentage(String, StringTokenizer, int)
	// Purpose : Stores the unlabeled neuron percentage in the appropriate array
	// ===================================================================================================
	
	private static void storeUnlabeledNeuronPercentage(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding unlabeled neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			unlabeledNeuronPercentages[recordNumber] = 100.0;
			return;
		}
		
		// get unlabeled neuron percentage value
		String token = tokenizer.nextToken();
		
		try {
			unlabeledNeuronPercentages[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting unlabeled neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			unlabeledNeuronPercentages[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storePrunedNeuronCount(String, StringTokenizer, int)
	// Purpose : Stores the pruned neuron counts in the appropriate array
	// ===================================================================================================
	
	private static void storePrunedNeuronCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding pruned neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			prunedNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get pruned neuron count value
		String token = tokenizer.nextToken();
		
		try {
			prunedNeuronCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting pruned neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			prunedNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}

	// ===================================================================================================
	// Method  : void storePrunedNeuronPercentage(String, StringTokenizer, int)
	// Purpose : Stores the pruned neuron percentage in the appropriate array
	// ===================================================================================================
	
	private static void storePrunedNeuronPercentage(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding pruned neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			prunedNeuronPercentages[recordNumber] = 100.0;
			return;
		}
		
		// get pruned neuron percentage value
		String token = tokenizer.nextToken();
		
		try {
			prunedNeuronPercentages[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting pruned neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			prunedNeuronPercentages[recordNumber] = 100.0;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeUnprunedNeuronCount(String, StringTokenizer, int)
	// Purpose : Stores the unpruned neuron counts in the appropriate array
	// ===================================================================================================
	
	private static void storeUnprunedNeuronCount(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding unpruned neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			unprunedNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
		// get unpruned neuron count value
		String token = tokenizer.nextToken();
		
		try {
			unprunedNeuronCounts[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting unpruned neuron count, record " + (recordNumber + 1) + ", file " + inputFileName);
			unprunedNeuronCounts[recordNumber] = Double.MAX_VALUE;
			return;
		}
		
	}
	
	// ===================================================================================================
	// Method  : void storeUnprunedNeuronPercentage(String, StringTokenizer, int)
	// Purpose : Stores the unpruned neuron percentage in the appropriate array
	// ===================================================================================================
	
	private static void storeUnprunedNeuronPercentage(String inputFileName, StringTokenizer tokenizer, int recordNumber) {
		
		if (tokenizer.countTokens() == 0) {
			System.err.println("Error finding unpruned neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			unprunedNeuronPercentages[recordNumber] = 100.0;
			return;
		}
		
		// get unpruned neuron percentage value
		String token = tokenizer.nextToken();
		
		try {
			unprunedNeuronPercentages[recordNumber] = Double.parseDouble(token);
		} catch (NumberFormatException e) {
			System.err.println("Error converting unpruned neuron percentage, record " + (recordNumber + 1) + ", file " + inputFileName);
			unprunedNeuronPercentages[recordNumber] = 100.0;
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
		storeUnlabeledNeuronCount(inputFileName, tokenizer, recordNumber);
		storeUnlabeledNeuronPercentage(inputFileName, tokenizer, recordNumber);
		storePrunedNeuronCount(inputFileName, tokenizer, recordNumber);
		storePrunedNeuronPercentage(inputFileName, tokenizer, recordNumber);
		storeUnprunedNeuronCount(inputFileName, tokenizer, recordNumber);
		storeUnprunedNeuronPercentage(inputFileName, tokenizer, recordNumber);
		
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
		meanUnlabeledNeuronCount = 0.0;
		meanUnlabeledNeuronPercentages = 0.0;
		meanPrunedNeuronCounts = 0.0;
		meanPrunedNeuronPercentages = 0.0;
		meanUnprunedNeuronCounts = 0.0;
		meanUnprunedNeuronPercentages = 0.0;
		
		// MEANS
		for (int i = 0; i < NUM_SIMS; i++) {
			meanTrainingPerformance += trainingPerformances[i];
			meanTrainingMisclassifiedPerformance += trainingMisclassifiedPerformances[i];
			meanTrainingUnclassifiedPerformance += trainingUnclassifiedPerformances[i];
			meanGeneralizationPerformance += generalizationPerformances[i];
			meanGeneralizationMisclassifiedPerformance += generalizationMisclassifiedPerformances[i];
			meanGeneralizationUnclassifiedPerformance += generalizationUnclassifiedPerformances[i];
			meanUnlabeledNeuronCount += unlabeledNeuronCounts[i];
			meanUnlabeledNeuronPercentages += unlabeledNeuronPercentages[i];
			meanPrunedNeuronCounts += prunedNeuronCounts[i];
			meanPrunedNeuronPercentages += prunedNeuronPercentages[i];
			meanUnprunedNeuronCounts += unprunedNeuronCounts[i];
			meanUnprunedNeuronPercentages += unprunedNeuronPercentages[i];
		}
		
		meanTrainingPerformance /= (double) NUM_SIMS;
		meanTrainingMisclassifiedPerformance /= (double) NUM_SIMS;
		meanTrainingUnclassifiedPerformance /= (double) NUM_SIMS;
		meanGeneralizationPerformance /= (double) NUM_SIMS;
		meanGeneralizationMisclassifiedPerformance /= (double) NUM_SIMS;
		meanGeneralizationUnclassifiedPerformance /= (double) NUM_SIMS;
		meanUnlabeledNeuronCount /= (double) NUM_SIMS;
		meanUnlabeledNeuronPercentages /= (double) NUM_SIMS;
		meanPrunedNeuronCounts /= (double) NUM_SIMS;
		meanPrunedNeuronPercentages /= (double) NUM_SIMS;
		meanUnprunedNeuronCounts /= (double) NUM_SIMS;
		meanUnprunedNeuronPercentages /= (double) NUM_SIMS;
		
		stdDevTrainingPerformance = 0.0;
		stdDevTrainingMisclassifiedPerformance = 0.0;
		stdDevTrainingUnclassifiedPerformance = 0.0;
		stdDevGeneralizationPerformance = 0.0;
		stdDevGeneralizationMisclassifiedPerformance = 0.0;
		stdDevGeneralizationUnclassifiedPerformance = 0.0;
		stdDevUnlabeledNeuronCount = 0.0;
		stdDevUnlabeledNeuronPercentages = 0.0;
		stdDevPrunedNeuronCounts = 0.0;
		stdDevPrunedNeuronPercentages = 0.0;
		stdDevUnprunedNeuronCounts = 0.0;
		stdDevUnprunedNeuronPercentages = 0.0;
		
		// STANDARD DEVIATIONS
		for (int i = 0; i < NUM_SIMS; i++) {
			stdDevTrainingPerformance += Math.pow(trainingPerformances[i] - meanTrainingPerformance, 2.0);
			stdDevTrainingMisclassifiedPerformance += Math.pow(trainingMisclassifiedPerformances[i] - meanTrainingMisclassifiedPerformance, 2.0);
			stdDevTrainingUnclassifiedPerformance += Math.pow(trainingUnclassifiedPerformances[i] - meanTrainingUnclassifiedPerformance, 2.0);
			stdDevGeneralizationPerformance += Math.pow(generalizationPerformances[i] - meanGeneralizationPerformance, 2.0);
			stdDevGeneralizationMisclassifiedPerformance += Math.pow(generalizationMisclassifiedPerformances[i] - meanGeneralizationMisclassifiedPerformance, 2.0);
			stdDevGeneralizationUnclassifiedPerformance += Math.pow(generalizationUnclassifiedPerformances[i] - meanGeneralizationUnclassifiedPerformance, 2.0);
			stdDevUnlabeledNeuronCount += Math.pow(unlabeledNeuronCounts[i] - meanUnlabeledNeuronCount, 2.0);
			stdDevUnlabeledNeuronPercentages += Math.pow(unlabeledNeuronPercentages[i] - meanUnlabeledNeuronPercentages, 2.0);
			stdDevPrunedNeuronCounts += Math.pow(prunedNeuronCounts[i] - meanPrunedNeuronCounts, 2.0);
			stdDevPrunedNeuronPercentages += Math.pow(prunedNeuronPercentages[i] - meanPrunedNeuronPercentages, 2.0);
			stdDevUnprunedNeuronCounts += Math.pow(unprunedNeuronCounts[i] - meanUnprunedNeuronCounts, 2.0);
			stdDevUnprunedNeuronPercentages += Math.pow(unprunedNeuronPercentages[i] - meanUnprunedNeuronPercentages, 2.0);
		}
		
		stdDevTrainingPerformance = Math.sqrt(stdDevTrainingPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevTrainingMisclassifiedPerformance = Math.sqrt(stdDevTrainingMisclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevTrainingUnclassifiedPerformance = Math.sqrt(stdDevTrainingUnclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationPerformance = Math.sqrt(stdDevGeneralizationPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationMisclassifiedPerformance = Math.sqrt(stdDevGeneralizationMisclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevGeneralizationUnclassifiedPerformance = Math.sqrt(stdDevGeneralizationUnclassifiedPerformance / (((double) NUM_SIMS) - 1.0));
		stdDevUnlabeledNeuronCount = Math.sqrt(stdDevUnlabeledNeuronCount / (((double) NUM_SIMS) - 1.0));
		stdDevUnlabeledNeuronPercentages = Math.sqrt(stdDevUnlabeledNeuronPercentages / (((double) NUM_SIMS) - 1.0));
		stdDevPrunedNeuronCounts = Math.sqrt(stdDevPrunedNeuronCounts / (((double) NUM_SIMS) - 1.0));
		stdDevPrunedNeuronPercentages = Math.sqrt(stdDevPrunedNeuronPercentages / (((double) NUM_SIMS) - 1.0));
		stdDevUnprunedNeuronCounts = Math.sqrt(stdDevUnprunedNeuronCounts / (((double) NUM_SIMS) - 1.0));
		stdDevUnprunedNeuronPercentages = Math.sqrt(stdDevUnprunedNeuronPercentages / (((double) NUM_SIMS) - 1.0));
		
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
				writer.print("simulation" + "\t" + "meanTrainingError"    + "\t" + "stdDevTrainingError"    + "\t" + "meanTrainingMisclassifiedError"    + "\t" + "stdDevTrainingMisclassifiedError"    + "\t" + "meanTrainingUnclassifiedError"    + "\t" + "stdDevTrainingUnclassifiedError"    + "\t" + "meanGeneralizationError"    + "\t" + "stdDevGeneralizationError"    + "\t" + "meanGeneralizationMisclassifiedError"    + "\t" + "stdDevGeneralizationMisclassifiedError"    + "\t" + "meanGeneralizationUnclassifiedError"    + "\t" + "stdDevGeneralizationUnclassifiedError"    + "\t" + "meanUnlabeledNeuronCount" + "\t" + "stdDevUnlabeledNeuronCount" + "\t" + "meanUnlabeledNeuronPercentages" + "\t" + "stdDevUnlabeledNeuronPercentages" + "\t" + "meanPrunedNeuronCounts" + "\t" + "stdDevPrunedNeuronCounts" + "\t" + "meanPrunedNeuronPercentages" + "\t" + "stdDevPrunedNeuronPercentages" + "\t" + "meanUnprunedNeuronCounts" + "\t" + "stdDevUnprunedNeuronCounts" + "\t" + "meanUnprunedNeuronPercentages" + "\t" + "stdDevUnprunedNeuronPercentages");
			} else {
				writer.print("simulation" + "\t" + "meanTrainingAccuracy" + "\t" + "stdDevTrainingAccuracy" + "\t" + "meanTrainingMisclassifiedAccuracy" + "\t" + "stdDevTrainingMisclassifiedAccuracy" + "\t" + "meanTrainingUnclassifiedAccuracy" + "\t" + "stdDevTrainingUnclassifiedAccuracy" + "\t" + "meanGeneralizationAccuracy" + "\t" + "stdDevGeneralizationAccuracy" + "\t" + "meanGeneralizationMisclassifiedAccuracy" + "\t" + "stdDevGeneralizationMisclassifiedAccuracy" + "\t" + "meanGeneralizationUnclassifiedAccuracy" + "\t" + "stdDevGeneralizationUnclassifiedAccuracy" + "\t" + "meanUnlabeledNeuronCount" + "\t" + "stdDevUnlabeledNeuronCount" + "\t" + "meanUnlabeledNeuronPercentages" + "\t" + "stdDevUnlabeledNeuronPercentages" + "\t" + "meanPrunedNeuronCounts" + "\t" + "stdDevPrunedNeuronCounts" + "\t" + "meanPrunedNeuronPercentages" + "\t" + "stdDevPrunedNeuronPercentages" + "\t" + "meanUnprunedNeuronCounts" + "\t" + "stdDevUnprunedNeuronCounts" + "\t" + "meanUnprunedNeuronPercentages" + "\t" + "stdDevUnprunedNeuronPercentages");
			}
		}
		
		writer.println();
		writer.print(inputFileName + "\t" + meanTrainingPerformance + "\t" + stdDevTrainingPerformance + "\t" +  meanTrainingMisclassifiedPerformance + "\t" + stdDevTrainingMisclassifiedPerformance + "\t" + meanTrainingUnclassifiedPerformance + "\t" + stdDevTrainingUnclassifiedPerformance + "\t" + meanGeneralizationPerformance + "\t" + stdDevGeneralizationPerformance + "\t" + meanGeneralizationMisclassifiedPerformance + "\t" + stdDevGeneralizationMisclassifiedPerformance + "\t" + meanGeneralizationUnclassifiedPerformance + "\t" + stdDevGeneralizationUnclassifiedPerformance + "\t" + meanUnlabeledNeuronCount + "\t" + stdDevUnlabeledNeuronCount + "\t" + meanUnlabeledNeuronPercentages + "\t" + stdDevUnlabeledNeuronPercentages + "\t" + meanPrunedNeuronCounts + "\t" + stdDevPrunedNeuronCounts + "\t" + meanPrunedNeuronPercentages + "\t" + stdDevPrunedNeuronPercentages + "\t" + meanUnprunedNeuronCounts + "\t" + stdDevUnprunedNeuronCounts + "\t" + meanUnprunedNeuronPercentages + "\t" + stdDevUnprunedNeuronPercentages);
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
	private static double[] unlabeledNeuronCounts;
	private static double[] unlabeledNeuronPercentages;
	private static double[] prunedNeuronCounts;
	private static double[] prunedNeuronPercentages;
	private static double[] unprunedNeuronCounts;
	private static double[] unprunedNeuronPercentages;
	
	// === Statistics ===
	private static double meanTrainingPerformance;
	private static double meanTrainingMisclassifiedPerformance;
	private static double meanTrainingUnclassifiedPerformance;
	private static double meanGeneralizationPerformance;
	private static double meanGeneralizationMisclassifiedPerformance;
	private static double meanGeneralizationUnclassifiedPerformance;
	private static double meanUnlabeledNeuronCount;
	private static double meanUnlabeledNeuronPercentages;
	private static double meanPrunedNeuronCounts;
	private static double meanPrunedNeuronPercentages;
	private static double meanUnprunedNeuronCounts;
	private static double meanUnprunedNeuronPercentages;
	
	private static double stdDevTrainingPerformance;
	private static double stdDevTrainingMisclassifiedPerformance;
	private static double stdDevTrainingUnclassifiedPerformance;
	private static double stdDevGeneralizationPerformance;
	private static double stdDevGeneralizationMisclassifiedPerformance;
	private static double stdDevGeneralizationUnclassifiedPerformance;
	private static double stdDevUnlabeledNeuronCount;
	private static double stdDevUnlabeledNeuronPercentages;
	private static double stdDevPrunedNeuronCounts;
	private static double stdDevPrunedNeuronPercentages;
	private static double stdDevUnprunedNeuronCounts;
	private static double stdDevUnprunedNeuronPercentages;
	
}
