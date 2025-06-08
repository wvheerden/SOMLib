// Usage: java GetRuleSetConditionCount ruleFile

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.Vector;

public class GetRuleSetConditionCountC4_5 {
	
	// =======================================================
	// Method: main(String[])
	// =======================================================
	
	public static void main(String[] args) {
		
		if (args.length != 1) {
			System.err.println("Invalid arguments");
			System.exit(1);
		}
		
		ruleCount = 0;
		conditionCount = 0;
		averageConditionsPerRule = 0.0;
		
		try {
			readInput(args[0]);
		} catch (FileNotFoundException e) {
			System.err.println("File not found");
			System.exit(1);
		} catch (IOException e) {
			System.err.println("IO Error reading");
			System.exit(1);
		}
		
		// print total condition count (+1 for default rule)
		System.out.print(conditionCount + 1);
		System.out.print("\t");
		
		// print total rule count (+1 for default rule)
		System.out.print(ruleCount + 1);
		System.out.print("\t");
		
		// print average condition count per rule (consider the default rule to be a separate rule with 1 condition)
		System.out.print(((double) (conditionCount + 1)) / ((double) (ruleCount + 1)));
		
	}
	
	// =======================================================
	// Method: readInput(String)
	// =======================================================
	
	private static void readInput(String fileName) throws FileNotFoundException, IOException {
		
		BufferedReader inputReader = new BufferedReader(new FileReader(fileName));
		String readLine = inputReader.readLine();
		
		while (readLine != null) {
			
			if (readLine.startsWith("Rule ")) {
				if (readLine.endsWith(":")) {
					++ruleCount;
					readRuleValues(inputReader);
				}
			}
			
			readLine = inputReader.readLine();
			
		}
		
	}
	
	// =======================================================
	// Method: readRuleValues(BufferedReader)
	// =======================================================
	
	private static int readRuleValues(BufferedReader inputReader) throws IOException {
		
		String readLine = inputReader.readLine();
		
		while (!readLine.trim().startsWith("->")) {
			++conditionCount;
			readLine = inputReader.readLine();
		}
		
		return conditionCount;
		
	}
	
	private static int ruleCount;
	private static int conditionCount;
	private static double averageConditionsPerRule;
	
}