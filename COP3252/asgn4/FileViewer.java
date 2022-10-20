import java.util.Scanner;
import java.util.Arrays;
import java.util.Date;
import java.io.*;

public class FileViewer {
	public static void main(String[] args) throws FileNotFoundException, IOException {

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
				PrintError(0);
			}
		}
		else {
			PrintError(0);
		}

		if (selection == 1) {
			File f = new File(fileParam1);
			long size = 0;

			if (f.isFile()) {
				System.out.println("File Path: "+ f.getAbsolutePath());
				System.out.print("Is executable? ");
				if(f.canExecute())
					System.out.println("True");
				else
					System.out.println("False");
				System.out.println("Size: " + f.length());
				System.out.print("Last modified date: ");
				long time = 0;
				time = f.lastModified();
				Date date = new Date(time);
				System.out.println(date);
			}
			else if (f.isDirectory()) {
				System.out.println("Size        Filename");
				File[] files = f.listFiles();

				for (File x : files) {
					size = f.length();
					if (f.isDirectory()) {
						System.out.print("*    ");
					}
					else {
						System.out.print(size + "       ");
					}
					System.out.println(f.getName());
				}
			}
			else {
				// not valid file, not valid directory, 
				PrintError(1);
			}


		}
		else if (selection == 2) {

		}
		else if (selection == 3) {

		}
		else {
			// selection == 4;
		}

	}
	private static void PrintError(int code) {
		switch (code) {
			case 1:
				System.err.println("Invalid filepath.");
				System.exit(1);

			case 2:
				System.err.println("Invalid destination file.");
				System.exit(2);

			default:
				System.err.printf("Usage: java -jar hw4.jar [-i [<file>|<directory>]|-v <file>|-c <sourceFile> <destFile>|-d <file1> <file2>]\n");
				System.exit(0);
		}
	}
}