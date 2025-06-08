import java.util.ArrayList;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class DataFileWriter {

	// ===========================================================================
	// Constructor : DataFileWriter(DataFileReader, String)
	// Purpose     : Construct new DataFileWriter using specified DataFileReader
	//               and record separator
	// ===========================================================================
	
	public DataFileWriter(DataFileReader reader, String aRecordSeparator) {
		recordSeparator = aRecordSeparator;
	}
	
	// ===========================================================================
	// Instance Method : writeFile(ArrayList, String)
	// Purpose         : Writes specified dataset to specified file name
	// ===========================================================================
	
	public void writeFile(ArrayList dataSet, String fileName) throws IOException {
		BufferedWriter outputWriter = null;
		
		try {
			outputWriter = new BufferedWriter(new FileWriter(fileName));
		} catch (IOException e) {
			throw new IOException("creating " + fileName);
		}
		
		try {
			
			// write records to file
			for (int i = 0; i < dataSet.size(); i++) {
				ArrayList record = (ArrayList) dataSet.get(i);
				for (int j = 0; j < record.size(); j++) {
					outputWriter.write((String) record.get(j));
					if (j != record.size() - 1) {
						outputWriter.write(recordSeparator);
					}
				}
				if (i != dataSet.size() - 1) {
					outputWriter.write("\n");
				}
			}
			outputWriter.close();
			
		} catch (IOException e) {
			throw new IOException("writing to " + fileName);
		}
	}
	
	private String recordSeparator;
}
