import java.util.Arrays;
import java.util.ArrayList;
import java.util.NoSuchElementException;
import java.text.DecimalFormatSymbols;
import java.text.DecimalFormat;
import java.math.RoundingMode;
import java.util.Collections;
import net.sourceforge.cilib.Random.MersenneTwister;

public class DataSetBuilder {

	// ===========================================================================
	// Constructor : DataSetBuilder(DataFileReader, int, boolean, int, boolean)
	// Purpose     : Construct new DataSetBuilder with specified data file reader,
	//               noise percentage (if required), and normalisation flag
	// ===========================================================================
	
	public DataSetBuilder(DataFileReader reader, int aNumSims, boolean anAddNoise, int noisePercentage, boolean aNormalise) {
		
		// get copies of required data from reader
		recordSet = reader.getRecordSet();
		minValues = reader.getMinValues();
		maxValues = reader.getMaxValues();
		uniqueClasses = reader.getUniqueClasses();
		
		// set additional information
		numSims = aNumSims;
		nextSet = 0;
		validationSetSize = recordSet.size() / numSims;
		validationSetStart = 0;
		addNoise = anAddNoise;
		
		// calculate number of records to flip (for noise injection)
		if (addNoise) {
			numTrainingToFlip = (int) Math.floor(((double) noisePercentage / 100.0) * getTrainingSetSize());
		} else {
			numTrainingToFlip = 0;
		}
		
		normalise = aNormalise;
		
		// random number generators (fixed seeds to ensure same sequence of values for subsequent t-tests)
		flipListShuffleGenerator = new MersenneTwister(-1652585779);
		flipClassGenerator = new MersenneTwister(1578433329);
		
		// get first training and test sets
		nextSet();
		
	}
	
	// ===========================================================================
	// Instance Method : boolean nextSet()
	// Purpose         : Generates a new set with constructor-specified properties
	// Return          : true if next set generated, false otherwise
	// ===========================================================================
	
	public boolean nextSet() throws NoSuchElementException {
		//System.out.println("Calling nextSet");
		
		//if ((validationSetStart + validationSetSize) > recordSet.size()) {
		if (nextSet >= numSims) {
			return false;
		}
		
		trainingSet = new ArrayList<ArrayList<String>>();
		validationSet = new ArrayList<ArrayList<String>>();
		
		// copy leading training set
		for (int i = 0; i < validationSetStart; i++) {
			ArrayList<String> copyFromRecord = recordSet.get(i);
			ArrayList<String> copyToRecord = new ArrayList<String>();
			for (int j = 0; j < copyFromRecord.size(); j++) {
				copyToRecord.add(copyFromRecord.get(j));
			}
			trainingSet.add(copyToRecord);
		}
		
		// copy validation set
		for (int i = validationSetStart; i < (validationSetStart + validationSetSize); i++) {
			//System.out.println(i);
			ArrayList<String> copyFromRecord = recordSet.get(i);
			ArrayList<String> copyToRecord = new ArrayList<String>();
			for (int j = 0; j < copyFromRecord.size(); j++) {
				copyToRecord.add(copyFromRecord.get(j));
			}
			validationSet.add(copyToRecord);
		}
		
		// copy trailing training set
		for (int i = (validationSetStart + validationSetSize); i < recordSet.size(); i++) {
			ArrayList<String> copyFromRecord = recordSet.get(i);
			ArrayList<String> copyToRecord = new ArrayList<String>();
			for (int j = 0; j < copyFromRecord.size(); j++) {
				copyToRecord.add(copyFromRecord.get(j));
			}
			trainingSet.add(copyToRecord);
		}
		
		// add noise to training set (if required)
		if (addNoise) {
			
			// create a flip indices array containing the ordered indices of the training data array
			ArrayList<Integer> flipIndices = new ArrayList<Integer>();
			
			for (int i = 0; i < trainingSet.size(); ++i) {
				flipIndices.add(new Integer(i));
			}
			
			// perform a Fisher-Yates shuffle (unbiased) on the flip indices array
			Collections.shuffle(flipIndices, flipListShuffleGenerator);
			
			// flip required indices
			for (int i = 0; i < numTrainingToFlip; ++i) {
				
				ArrayList<String> flipRecord = trainingSet.get(flipIndices.get(i));
				String flipRecordClass = flipRecord.get(flipRecord.size() - 1);
				
				// flip the selected record's class randomly (using a Fisher-Yates unbiased shuffle on the classes we could flip to)
				ArrayList<Integer> flipToClasses = new ArrayList<Integer>();
				
				for (int j = 0; j < uniqueClasses.size(); ++j) {
					if (!flipRecordClass.equals(uniqueClasses.get(j))) {
						flipToClasses.add(new Integer(j));
					}
				}
				
				Collections.shuffle(flipToClasses, flipClassGenerator);
				flipRecord.set(flipRecord.size() - 1, uniqueClasses.get(flipToClasses.get(0)));
			}
			
		}
		
		// scale input values to [newMin..newMax] (if required)
		DecimalFormatSymbols symbols = new DecimalFormatSymbols();
		symbols.setDecimalSeparator('.');
		DecimalFormat formatter = new DecimalFormat("", symbols);
		formatter.setGroupingUsed(false);
		formatter.setMinimumFractionDigits(15);
		formatter.setMinimumIntegerDigits(1);
		
		if (normalise) {
			for (int i = 0; i < trainingSet.size(); i++) {
				ArrayList<String> currentList = trainingSet.get(i);
				for (int j = 0; j < (currentList.size() - 1); j++) {
					
					double currentValue = 0.0;
					
					try {
						currentValue = Double.parseDouble(currentList.get(j));
					} catch (NumberFormatException e) {
						System.err.println("Data value is not a floating point number");
						System.exit(1);
					}
					
					double newValue = 0.0;
					
					if (minValues[j] == maxValues[j]) {
						newValue = minValues[j];
					} else {
						newValue = ((currentValue - minValues[j]) / (maxValues[j] - minValues[j])) * (newMax - newMin) + newMin;
					}
					
					currentList.set(j, formatter.format(newValue));
				}
			}
			
			for (int i = 0; i < validationSet.size(); i++) {
				ArrayList<String> currentList = validationSet.get(i);
				for (int j = 0; j < (currentList.size() - 1); j++) {
					
					double currentValue = 0.0;
					
					try {
						currentValue = Double.parseDouble(currentList.get(j));
					} catch (NumberFormatException e) {
						System.err.println("Data value is not a floating point number");
						System.exit(1);
					}
					
					double newValue = 0.0;
					
					if (minValues[j] == maxValues[j]) {
						newValue = minValues[j];
					} else {
						newValue = ((currentValue - minValues[j]) / (maxValues[j] - minValues[j])) * (newMax - newMin) + newMin;
					}
					
					currentList.set(j, formatter.format(newValue));
				}
			}
		}
		
		// update validation set start
		validationSetStart += validationSetSize;
		
		// update current sim counter
		++nextSet;
		
		return true;
	}
	
	// ===========================================================================
	// Instance Method : ArrayList getTrainingSet()
	// Purpose         : Returns a copy of the current training set
	// ===========================================================================
	
	public ArrayList getTrainingSet() {
		return trainingSet;
	}
	
	// ===========================================================================
	// Instance Method : int getTrainingSetSize()
	// Purpose         : Returns current size of training set
	// ===========================================================================
	
	public int getTrainingSetSize() {
		return (recordSet.size() - validationSetSize);
	}
	
	// ===========================================================================
	// Instance Method : ArrayList getValidationSet()
	// Purpose         : Returns a copy of the current validation set
	// ===========================================================================
	
	public ArrayList getValidationSet() {
		return validationSet;
	}
	
	// ===========================================================================
	// Instance Method : int getValidationSetSize()
	// Purpose         : Returns current size of validation set
	// ===========================================================================
	
	public int getValidationSetSize() {
		return validationSetSize;
	}
	
	// ===========================================================================
	// Instance Method : int getUnusedForValidationCount()
	// Purpose         : Returns number of records that will be unused for validation
	// ===========================================================================
	
	public int getUnusedForValidationCount() {
		return (recordSet.size() % numSims);
	}
	
	// ===========================================================================
	// Instance Method : int getNumberTrainingFlipped()
	// Purpose         : Returns number of records to have their class flipped
	// ===========================================================================
	
	public int getNumberTrainingFlipped() {
		return numTrainingToFlip;
	}
	
	// *** Instance Fields ***
	
	private ArrayList<ArrayList<String>> recordSet;
	private double[] minValues;
	private double[] maxValues;  
	private ArrayList<String> uniqueClasses;
	private int numSims;
	private int nextSet;
	private int validationSetSize;
	private ArrayList<ArrayList<String>> trainingSet;
	private ArrayList<ArrayList<String>> validationSet;
	private int validationSetStart;
	private boolean addNoise;
	private int numTrainingToFlip;
	private boolean normalise;
	private MersenneTwister flipListShuffleGenerator;
	private MersenneTwister flipClassGenerator;
	
	// ** Constants **
	
	private static double newMin = 0;
	private static double newMax = 1;
	
}
