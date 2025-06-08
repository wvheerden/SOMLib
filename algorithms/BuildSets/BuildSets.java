// java BuildSets iris.txt , 30 5 -normalise

import java.util.ArrayList;
import java.io.FileNotFoundException;
import java.io.IOException;

public class BuildSets {

	public static void main(String args[]) {
	
		int numSims = 0;
		
		// check for correct number of arguments
		if ((args.length < 3) || (args.length > 5)) {
			System.err.println("Invalid arguments");
			System.err.println("java BuildSets <filename> <separator> <numSims> [noisePercentage] [-normalise]");
			System.exit(1);
		}
		
		// get number of simulations from parameter list
		try {
			numSims = Integer.parseInt(args[2]);
		} catch (NumberFormatException e) {
			System.err.println("Invalid number for simulation count");
			System.exit(1);
		}
		
		// test and set separator from parameter list
		if ((!args[1].equals("t")) && !args[1].equals(",")) {
			System.err.println("Invalid record separator");
			System.exit(1);
		}
		
		String separator = args[1];
		
		// set default normalisation and noise injection parameters
		boolean normalise = false;
		boolean addNoise = false;
		int noisePercentage = 0;
		
		// set parameter normalisation and noise injection parameters
		if (args.length >= 4) {
			if ((args.length == 4) && (args[3].equals("-normalise"))) {
				normalise = true;
			} else {
				addNoise = true;
				try {
					noisePercentage = Integer.parseInt(args[3]);
				} catch (NumberFormatException e) {
					System.err.println("Invalid number for noise percentage");
					System.exit(0);
				}
				if ((noisePercentage < 0) || (noisePercentage > 100)) {
					System.err.println("Noise percentage out of range");
					System.exit(0);
				}
				if (args.length == 5) {
					if (args[4].equals("-normalise")) {
						normalise = true;
					} else {
						System.err.println("Invalid option");
						System.exit(1);
					}
				}
			}
		}
		
		// create a new file reader using parameter file name and separator
		DataFileReader reader = null;
		
		try {
			reader = new DataFileReader(args[0], separator);
		} catch (FileNotFoundException e) {
			System.err.println("File " + args[0] + " not found");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("IO error reading file " + args[0]);
		}
		
		if (separator == "\t") {
			System.out.println("File " + args[0] + " read... [separator: \"\\t\"]");
		} else {
			System.out.println("File " + args[0] + " read... [separator: \"" + separator + "\"]");
		}
		
		// create new set builder using read data set
		DataSetBuilder builder = new DataSetBuilder(reader, numSims, addNoise, noisePercentage, normalise);
		
		// output stats for this run
		System.out.println();
		System.out.println("Simulations         : " + numSims);
		System.out.println("Records             : " + reader.getRecordCount());
		System.out.println("Validation set size : " + builder.getValidationSetSize());
		System.out.print("Training set size   : " + builder.getTrainingSetSize());
		if (builder.getUnusedForValidationCount() != 0) {
			System.out.print(" [" + builder.getUnusedForValidationCount() + " records unused for validation]");
		}
		System.out.print("\n");
		
		if (addNoise) {
			System.out.println("Training set noise  : " + noisePercentage + "% [" + builder.getNumberTrainingFlipped() + " training records]");
		}
		
		if (normalise) {
			System.out.print("Normalising using   : ");
			for (int i = 0; i < reader.getMinValues().length; i++) {
				System.out.print("[" + (reader.getMinValues())[i] + ", " + (reader.getMaxValues())[i] + "] ");
			}
			System.out.println();
		}
		
		int i = 0;
		
		do {
			ArrayList trainingSet = builder.getTrainingSet();
			ArrayList validationSet = builder.getValidationSet();
			
			// strip extraneous directory information from args[0] to get only output file root
			int stripIndex = args[0].lastIndexOf(System.getProperty("file.separator"));
			if (stripIndex != -1) {
				args[0] = args[0].substring(stripIndex + 1, args[0].length());
			}
			
			// create new set writer using reader and parameter separator
			DataFileWriter writer = new DataFileWriter(reader, separator);
			
			try {
				writer.writeFile(trainingSet, args[0] + ".raw." + i + ".train");
				writer.writeFile(validationSet, args[0] + ".raw." + i + ".test");
			} catch (IOException e) {
				System.err.println("IO error " + e.getMessage());
				System.exit(1);
			}
			i++;
		} while (builder.nextSet());
	}
	
}
