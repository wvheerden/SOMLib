import java.util.ArrayList;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class DataFileReader {

	public DataFileReader(String aFileName, String aRecordSeparator) throws FileNotFoundException, IOException {
		
		// initialize fields
		fileName = aFileName;
		recordSeparator = aRecordSeparator;
		valueCount = 0;
		recordSet = new ArrayList<ArrayList<String>>();
		uniqueClasses = new ArrayList<String>();
		
		// read and process file body
		BufferedReader inputReader = new BufferedReader(new FileReader(fileName));
		String readLine = inputReader.readLine();
		
		while (readLine != null) {
			tokenizeRecord(readLine);
			readLine = inputReader.readLine();
		}
		
	}
	
	// ===========================================================================
	// Instance Method : void tokenizeRecord(String)
	// Purpose         : Tokenizes record string (based on recordSeparator), and
	//                   adds records and classes to appropriate lists
	// ===========================================================================
	
	private void tokenizeRecord(String record) {
		
		// create required tokenizer for the record
		StringTokenizer recordTokenizer = new StringTokenizer(record, recordSeparator);
		
		// if this is the first record, set number of values per record
		if (recordSet.size() == 0) {
			valueCount = recordTokenizer.countTokens() - 1;
		// if this is a subsequent record, check for valid number of values in record
		} else if ((recordTokenizer.countTokens() - 1) != valueCount) {
			System.err.println();
			System.err.println("Error: Invalid number of records in " + fileName);
			System.err.println("Line: " + (recordSet.size() + 1));
			System.exit(1);
		}
		
		// initialize minValues if necessary
		if (minValues == null) {
			minValues = new double[valueCount];
			for (int i = 0; i < valueCount; ++i) {
				minValues[i] = Double.MAX_VALUE;
			}
		}
		
		// initialize maxValues if necessary
		if (maxValues == null) {
			maxValues = new double[valueCount];
			for (int i = 0; i < valueCount; ++i) {
				maxValues[i] = -Double.MAX_VALUE;
			}
		}
		
		addRecord(recordTokenizer);
		
	}
	
	// ===========================================================================
	// Instance Method : addRecord(StringTokenizer)
	// Purpose         : Add record values from supplied tokenizer to record set
	// ===========================================================================
	
	private void addRecord(StringTokenizer recordTokenizer) {
		
		// store current token for update of minValue and maxValue arrays
		int tokenIndex = 0;
		
		// List for new record values
		ArrayList<String> recordList = new ArrayList<String>();
		
		while (recordTokenizer.hasMoreTokens()) {
			// get next value and add to record
			String nextToken = recordTokenizer.nextToken();
			recordList.add(nextToken);
			// if not the class record, test for minimum or maximum
			if (recordTokenizer.countTokens() != 0) {
				double currentValue = Double.parseDouble(nextToken);
				if (currentValue < minValues[tokenIndex]) {
					minValues[tokenIndex] = currentValue;
				}
				if (currentValue > maxValues[tokenIndex]) {
					maxValues[tokenIndex] = currentValue;
				}
			} else {
				evaluateRecordLabel(nextToken);
			}
			// advance token index
			tokenIndex++;
		}
		
		recordSet.add(recordList);
		
	}
	
	// ===========================================================================
	// Instance Method : evaluateRecordLabel(String)
	// Purpose         : Evaluate record label from supplied string to record set
	// ===========================================================================
	
	private void evaluateRecordLabel(String recordLabel) {
		
		if (!uniqueClasses.contains(recordLabel)) {
			uniqueClasses.add(recordLabel);
		}
		
	}
	
	// ===========================================================================
	// Instance Method : int getRecordCount()
	// Purpose         : Returns the number of records read by this reader
	// ===========================================================================
	
	public int getRecordCount() {
		return recordSet.size();
	}
	
	// ===========================================================================
	// Instance Method : ArrayList getRecordSet()
	// Purpose         : Returns a copy of the recordSet this object stores
	// ===========================================================================
	
	public ArrayList<ArrayList<String>> getRecordSet() {
		
		ArrayList<ArrayList<String>> returnRecordSet = new ArrayList<ArrayList<String>>();
		
		for (int i = 0; i < recordSet.size(); ++i) {
			// contained record stores only immutable String objects which do not need to be cloned
			ArrayList<String> recordCopy = new ArrayList<String>();
			
			for (int j = 0; j < recordSet.get(i).size(); ++j) {
				recordCopy.add(recordSet.get(i).get(j));
			}
			
			returnRecordSet.add(recordCopy);
		}
		
		return returnRecordSet;
		
	}
	
	// ===========================================================================
	// Instance Method : ArrayList getUniqueClasses()
	// Purpose         : Returns a copy of the uniqueClasses list this object stores
	// ===========================================================================

	public ArrayList<String> getUniqueClasses() {
		
		// contains only immutable String objects which do not need to be cloned
		ArrayList<String> returnUniqueClasses = new ArrayList<String>();
		
		for (int i = 0; i < uniqueClasses.size(); ++i) {
			returnUniqueClasses.add(uniqueClasses.get(i));
		}
		
		return returnUniqueClasses;
	}
	
	// ===========================================================================
	// Instance Method : double[] getMinValues()
	// Purpose         : Returns a copy of the minValues list this object stores
	// ===========================================================================
	
	public double[] getMinValues() {
		// contains only basic type double values which do not need to be cloned
		return minValues.clone();
	}
	
	// ===========================================================================
	// Instance Method : double[] getMaxValues()
	// Purpose         : Returns a copy of the maxValues list this object stores
	// ===========================================================================
	
	public double[] getMaxValues() {
		// contains only basic type double values which do not need to be cloned
		return maxValues.clone();
	}
	
	private String fileName;
	private String recordSeparator;
	private int valueCount;
	private double[] minValues;
	private double[] maxValues;
	private ArrayList<ArrayList<String>> recordSet;
	private ArrayList<String> uniqueClasses;

}
