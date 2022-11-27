import java.io.*;

public class FileIO {
    public static void main (String[] args) throws IOException {
		// Create input stream
      	FileReader fr = new FileReader("test.txt");
      	BufferedReader in = new BufferedReader(fr);

      	// Create output stream
      	FileWriter fw = new FileWriter("out.txt");
      	BufferedWriter out = new BufferedWriter(fw);

      	boolean eof = false;
      	int inChar;
      	do {
        	inChar = in.read();
        	if (inChar != -1) {
          		char outChar = Character.toUpperCase((char) inChar);
          		out.write(outChar);
        	} else
          		eof = true;
      		} while (!eof);
      			in.close();
      			out.close();
        }       
    }