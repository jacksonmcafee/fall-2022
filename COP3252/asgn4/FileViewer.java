import java.util.Scanner;
import java.util.Arrays;
import java.util.Date;
import java.io.*;

// I am a huge fan of the ternary operator and might have overused it here. Oops!

public class FileViewer {
	public static void main(String[] args) throws Exception {

		int selection = 1; 		 // 1 is info, 2 is view, 3 is copy, 4 is compare
		String fileParam1 = " "; // for all use cases
		String fileParam2 = " "; // for copy and compare case
		boolean maybeDirectory = false;

		if(args.length == 0) {
			fileParam1 = ".";
		}
		else if (args.length == 1) {
			String flag = args[0];     // makes code more readable
			if (flag.matches("-i")) {
				fileParam1 = ".";
				maybeDirectory = true;
			}
		}
		else if (args.length == 2) {
			String flag = args[0];
			if (flag.matches("-i")) {
				fileParam1 = args[1];
			}
			else if (flag.matches("-v")) {
				selection = 2;
				fileParam1 = args[1];
			}
			else if (flag.matches("-c")) {
				// not enough params
				PrintError(0);
			}
			else if (flag.matches("-d")) {
				// not enough params
				PrintError(0);
			}
			else {
				PrintError(0);
			}
		}
		else if (args.length == 3) {
			String flag = args[0];
			if (flag.matches("-c")) {
				selection = 3;
				fileParam1 = args[1];
				fileParam2 = args[2];
			}
			else if (flag.matches("-d")) {
				selection = 4;
				fileParam1 = args[1];
				fileParam2 = args[2];
			}
			else {
				PrintError(2);
			}
		}
		else {
			PrintError(0);
		}

		try {
			System.out.println("Trying something!");

			File f = new File(fileParam1);
		}
		catch (Exception e) {
			System.out.println("This block handles all exception types");

			PrintError(1);
		}

		if (selection == 1) {
			// "-i" or nothing was passed
			File f = new File(fileParam1);
			long size = 0;

			if (f.isFile()) {
				// prints filepath 
				System.out.printf("File Path: %s %n", f.getAbsolutePath());
				
				// prints executable status
				String executable = (f.canExecute() ? "True" : "False");
				System.out.printf("Is executable?: %s %n", executable);

				// prints size of file
				System.out.printf("Size: %d bytes %n", f.length());
				
				// prints out date and time 
				Date date = new Date(f.lastModified());
				System.out.printf("Last Modified Date: %tc %n", date);
			}
			else if (f.isDirectory()) {
				System.out.printf("%-10s %s %n", "Size", "Filename");
				File[] files = f.listFiles();

				for (File x : files) {
					// get filesize, if directory, set to *
					size = x.length();
					String name = (x.isDirectory() ? x.getName() + "*" : x.getName());

					System.out.printf("%-10d %s %n", size, name);
				}
			}
			else {
				// not valid file, not valid directory, 
				PrintError(1);
			}
		}
		else if (selection == 2) {
			// "-v" was passed
			File f = new File(fileParam1);
			if(f.isFile()){  // if the file passed exists and is a file, 
				Scanner s = new Scanner(f);
				while(s.hasNextLine())
					System.out.println(s.nextLine()); // prints out each line while there are still lines to print
				s.close();
			}	
		}
		else if (selection == 3) {
			// "-c" was passed
			System.out.println("C was passed!");

		}
		else {
			// selection == 4, "-d" was passed
			System.out.println("D was passed!");
		}

	}
	private static void PrintError(int code) {
		switch (code) {
			case 1:
				System.err.println("Invalid filepath.");
				break;

			case 2:
				System.err.println("Invalid destination file.");
				break;
			
			default:
				break;

		}
		
		System.err.printf("Usage: java -jar hw4.jar [-i [<file>|<directory>]|-v <file>|-c <sourceFile> <destFile>|-d <file1> <file2>]\n");
		System.exit(0);
	}
}