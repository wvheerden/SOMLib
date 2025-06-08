// ===================================================================================================
// Class   : DataSetShuffler
// Purpose : Shuffles data set
// Usage   : java DataSetShuffler dataFile
//           ASSUMES ONE RECORD PER LINE, NO HEADER IN DATA FILE (NO OTHER REQUIREMENTS)
// ===================================================================================================

import net.sourceforge.cilib.Random.MersenneTwister;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.Collections;
import java.util.ArrayList;

public class DataSetShuffler {
	
	// ===================================================================================================
	// Method  : main(String[])
	// Purpose : Main method
	// ===================================================================================================
	
	public static void main(String args[]) {
		
		if (args.length != 1) {
			System.err.println("Invalid arguments");
			System.exit(1);
		}
		
		dataRecords = new ArrayList<Object>();
		
		try {
			readInput(args[0]);
		} catch (FileNotFoundException e) {
			System.err.println("File " + args[0] + " not found");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("IO Error reading");
			System.exit(1);
		}
		
	}
	
	// ===================================================================================================
	// Method  : readInput(String)
	// Purpose : Reads input based on file name (a data file that must be shuffled), outputs to stdout
	// ===================================================================================================
	
	private static void readInput(String fileName) throws FileNotFoundException, IOException {
		
		BufferedReader inputReader = new BufferedReader(new FileReader(fileName));
		
		String readLine = inputReader.readLine();
		while (readLine != null) {
			dataRecords.add(readLine);
			readLine = inputReader.readLine();
		}
		
		// Fisher-Yates shuffle, with Mersenne Twister
		MersenneTwister randomizer = new MersenneTwister();
		Collections.shuffle(dataRecords, randomizer);
		
		for (int i = 0; i < dataRecords.size(); ++i) {
			System.out.print(dataRecords.get(i));
			if (i != dataRecords.size() - 1) {
				System.out.println();
			}
		}
		
	}
	
	// === Static Fields ===
	
	private static ArrayList<Object> dataRecords;
	
}
