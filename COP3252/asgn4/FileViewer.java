import java.io.*;
import java.util.*;
import java.nio.file.*;

/* 
Jackson McAfee, COP3252 Adv. Java Prog. Asgn 4

Did not waste a bunch of time on a file parsing function this time around.
Served me well.

I organized my program by int selections:
	1 is info, 2 is view, 3 is copy, 4 is compare

I don't know if I should've caught exceptions more specifically than just
the Exception class, but it did the job. I was having problems with 
IOException/FileNotFoundException not catching so I just defaulted to Exception. 
*/

public class FileViewer {
	public static void main(String[] args) throws Exception {

		int selection = 1; 		 
		String fileParam1 = " "; // for all use cases
		String fileParam2 = " "; // for copy and compare case

		if(args.length == 0) {
			fileParam1 = ".";
		}
		else if (args.length == 1) {
			String flag = args[0];     // makes code more readable
			if (flag.matches("-i")) {
				fileParam1 = ".";
			}
			else {
				fileParam1 = args[0]; // file passed 
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
				PrintError("");
			}
			else if (flag.matches("-d")) {
				// not enough params
				PrintError("");
			}
			else {
				PrintError("");
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
				PrintError("Invalid destination file.");
			}
		}
		else {
			PrintError("");
		}

		switch (selection) {
			case 1: {
				// "-i" or nothing was passed
				File f = new File(fileParam1);
				long size = 0;

				if (f.isFile()) {
					// prints filepath 
					System.out.printf("File Path: %s %n", f.getAbsolutePath());
					
					// prints executable status
					String executable = (f.canExecute() ? "true" : "false");
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
					PrintError("Invalid file or directory passed.");
				}
				break;
			}

			case 2: {
				// "-v" was passed
				try {
					File f = new File(fileParam1);
					// if the file passed exists and is a file
					if(f.isFile()){  
						Scanner s = new Scanner(f);
						while(s.hasNextLine())
							// outputs lines until eof
							System.out.println(s.nextLine()); 
						s.close();
					}
				}
				catch (Exception e) {
					PrintError("File not found.");
				}
				break;
			}
			
			case 3: {
				// "-c" was passed
				if (fileParam1.matches(fileParam2)) {
					PrintError("Cannot copy file to itself.");
				}

				try {
					// try to create files based on param1/param2
					File f1 = new File(fileParam1);
					File f2 = new File(fileParam2); 

					if (f2.isFile()) {
						System.out.printf("File %s already exists.", fileParam2);
						PrintError("");
					}

					// create in/out streams based on files
					FileInputStream in = new FileInputStream(f1);
					FileOutputStream out = new FileOutputStream(f2);

					int i;
					while ((i = in.read()) != -1) {
						// write each byte from instream to outstream
						out.write(i);
					}

					if (in != null) {
						in.close(); // close instream
					}
					if (out != null) {
						out.close(); // close outstream
					}
				}
				catch (Exception e) {
					// if something throws, catch here
					PrintError("File not found.");
				}	
				System.out.printf("File %s was copied to file %s successfully!", fileParam1, fileParam2);
				break;
			}

			case 4: {
			// if same file, return immediately
			if (fileParam1.matches(fileParam2)) {
				System.out.printf("The two files %s and %s are the same. %n", fileParam1, fileParam2);
				return;
			}

			// selection == 4, "-d" was passed
			try {
				// create paths from fileParams b/c Files.nBR requires path objects
				Path path1 = FileSystems.getDefault().getPath(fileParam1);
				Path path2 = FileSystems.getDefault().getPath(fileParam2);

				// create BRs from paths
				BufferedReader br1 = Files.newBufferedReader(path1);
         		BufferedReader br2 = Files.newBufferedReader(path2);

	        	String l1 = "", l2 = "";
				// get each line from each BR, compare with matches
				// if diff is found, print and return
	        	while ((l1 = br1.readLine()) != null) {
	            	l2 = br2.readLine();
	            	if (l2 == null || !l1.matches(l2)) {
	                	System.out.printf("The two files %s and %s are not the same. %n", fileParam1, fileParam2);
	                	return;
	            	}
	        	}
				// if no more lines at same time, print and return
	        	if (br2.readLine() == null) {
	               	System.out.printf("The two files %s and %s are the same. %n", fileParam1, fileParam2);
	        	}
	        	else {
	               	System.out.printf("The two files %s and %s are not the same. %n", fileParam1, fileParam2);
	        	}
        	}
        	catch (Exception e) {
        		PrintError("File not found.");
			}
			break;
			}
		}
	}
	// handles all errors as they're found
	private static void PrintError(String s) {
		System.err.println(s);
		System.err.printf("Usage: java -jar hw4.jar [-i [<file>|<directory>]|-v <file>|-c <sourceFile> <destFile>|-d <file1> <file2>]\n");
		System.exit(0);
	}
}