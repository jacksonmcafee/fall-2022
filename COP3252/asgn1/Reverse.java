// Pi.java for COP3252 Fall2022 Asgn1
// Jackson McAfee, 30 Aug. 2022

import java.util.Scanner;

public class Reverse {
	public static void main(String[] args) {
		// create scanner obj. to get input from Sys.in
		Scanner s = new Scanner(System.in);

		long user_input = 1;
		String reverse_str = "";

		// main loop body
		while (true) {
			System.out.print("Please enter a long integer (0 to quit): ");
			user_input = s.nextLong();

			if (user_input == 0) {
				System.out.println("Goodbye!");
				break;
			}

			reverse_str = reverseDigits(user_input);
			System.out.printf("The number reversed is: %s \n", reverse_str);
			reverse_str = "";
		}
	}
	public static String reverseDigits(long user_input) {
		String forward_str = Long.toString(user_input);
		String reverse_str = "";

		for (int i = forward_str.length(); i != 0; i--) {
				reverse_str += forward_str.charAt(i-1);
		}
	
		while (reverse_str.charAt(0) == '0') {
			// remove 0 from front of string
				reverse_str = reverse_str.substring(1);
		}

		return reverse_str;
	}
} 