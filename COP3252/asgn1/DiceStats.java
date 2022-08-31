/*
DiceStats.java for COP3252 Fall2022 Asgn1
Jackson McAfee, 30 Aug. 2022
*/

import java.util.Scanner;
import java.util.Random;

public class DiceStats {
	public static void main(String[] args) {
		// declare scanner & random obj
		Scanner s = new Scanner(System.in);
		Random r = new Random();

		// get user input
		System.out.print("How many dice will constitute one roll? ");
		float dice_per_turn = s.nextFloat();
		System.out.print("How many rolls? ");
		float num_of_rolls = s.nextFloat();

		// used to calculate array size
		int min_roll = (int)dice_per_turn;
		int max_roll = (int)dice_per_turn * 6;
		int size = max_roll - min_roll;

		// declare array and assign memory
		int[] dice_stats;
		dice_stats = new int[size+1];

		// random value generation loops
		for (int i = 0; i < (int)num_of_rolls; i++) {
			int dice_sum = 0;
			for (int j = (int)dice_per_turn; j > 0; j--) {
				// nextInt is bounded [0, int) so in order to get proper
				// values, each int needs to be adjusted before adding to total
				dice_sum += r.nextInt(6) + 1;
			}
			dice_stats[dice_sum-min_roll]++;
		}

		// printing function
		System.out.printf("%-4s %-10s %-16s %n", "Sum", "# of Times", "Percentage");
		for (int i = 0; i < dice_stats.length; i++) {
			System.out.printf("%-4d %-11d%.2f %c %n", min_roll+i, 
												 dice_stats[i],
												 ((float)dice_stats[i]/(num_of_rolls))*100,
												 '%');
		}
	}
}