/*
Reverse.java for COP3252 Fall2022 Asgn1
Jackson McAfee, 30 Aug. 2022

I'm aware that my reverseDigits function doesn't return a long int, but because
there was not an explicit type defined in the assignment, I decided to save
myself from an extra cast.
*/

import java.util.Scanner;

public class Reverse {
	public static void main(String[] args) {
		// declare scanner obj
		Scanner s = new Scanner(System.in);

		// main loop body
		while (true) {
			System.out.print("Please enter a long integer (0 to quit): ");
			long user_input = s.nextLong();

			// checks if exit is needed
			if (user_input == 0) {
				System.out.println("Goodbye!");
				break;
			}

			// assign reverse_str to the reverseDigits call & print
			String reverse_str = reverseDigits(user_input);
			System.out.printf("The number reversed is: %s \n", reverse_str);
		}
	}

	public static String reverseDigits(long user_input) {
		String forward_str = Long.toString(user_input);
		String reverse_str = "";

		// builds reverse_str by iterating through forward_str backwards
		for (int i = forward_str.length(); i != 0; i--) {
				reverse_str += forward_str.charAt(i-1);
		}

		// remove all 0s from front of string
		while (reverse_str.charAt(0) == '0') {
			reverse_str = reverse_str.substring(1);
		}

		return reverse_str;
	}
} 