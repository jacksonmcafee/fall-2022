// Pi.java for COP3252 Fall2022 Asgn1
// Jackson McAfee, 29 Aug. 2022

import java.util.Scanner;

public class Pi {
	public static void main(String args[]) {
		// create scanner obj. to get input from Sys.in
		Scanner s = new Scanner(System.in);

		// get user input from scanner 
		System.out.printf("Compute to how many terms of the series? ");
		int N_terms = s.nextInt();

		System.out.printf("terms | PI approximation \n");
		
		// for loop to print
		float value = 4;
		for (float i = 1; i < N_terms + 1; i++) {
			if ( i == 1 ) {
				value += 0;
			}
			else if ( i % 2 == 0 ) {
				value += (-4)/(2*i-1);
			}
			else {
				value += (4)/(2*i-1);
			}
	   		System.out.printf("%d      %f\n", Math.round(i), value);
 		}
	}
}