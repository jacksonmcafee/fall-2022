/* I'm aware that having a try/catch block isn't required for this to work, nor is it
particularly necessary. I'm new to Java and thought it might be fun to throw
a few in just for a bit of practice. Might refactor entire block later. */ 

import java.util.*;

public class TicTacToe {

	// constant
	public static final String usage = "Usage: java TicTacToe [-c [1|2]]";

	public static void main(String[] args) {
		// declare variables
		int playerNum = 3;
		
		// deal with command line args
		if (args.length > 0 && args.length < 3) {			
			playerNum = parseArgs(args);
		}
		// "catch" if too many arguments are passed
		else if (args.length > 2) {
			System.err.printf("Too many arguments provided.%n%s%n", usage);
			System.exit(1);
		}

		// enter game loop here
		int winner = gameLoop(playerNum);

		switch (winner) {
			case 1:
				System.out.println("Player One wins!");
			case 2:
				System.out.println("Player Two wins!");
			default:
				System.out.println("Nobody wins! The game was a draw.");
		}
	}

	 private static int gameLoop(int playerNum) {
		int[][] board = new int[3][3]; // create 2D matrix "board"
		int[] moves = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
		boolean gameActive = true;
		int winner = 0, turn = 0, move = 0;
		int p1 = 0, p2 = 0; // if 0, player is computer, if 1, player is bot

		// evaluates players based on playerNum
		switch (playerNum) {
			case 0:
				// 2 bot players
				break;

			case 1:
				// 1 bot player, real player is p1
				p1 = 1;
				break;

			case 2:
				// 1 bot player, real player is p2
				p2 = 1;
				break;

			default:
				// 2 real players
				p1 = p2 = 1;
				break;
			}

		// central game loop
		while(gameActive) {
			printBoard(board, turn);

			// check player turn
			if (turn % 2 == 1) {
				// odd, player 1's turn 
				if (p1 == 0) {
					move = computerInput(board, moves);
				}
				else {
					move = playerInput(board, moves);
				}
			}
			else {
				// even, player 2's turn
				if (p2 == 0) {
					move = computerInput(board, moves);
				}
				else {
					move = playerInput(board, moves);
				}
			}

			printBoard(board, turn);

			// check if win condition has been met

			turn++;
			if (turn == 9) {
				gameActive = false;
			}
		}
		return winner;
	} 

	private static int playerInput(int[][] board, int[] moves) {
		// gets player move input
		
		// declare vars, new scanner
		Scanner s = new Scanner(System.in);
		int move = 0;
		boolean moveIllegal = true;

		// get input from user
		while(moveIllegal) {
			System.out.println("Input your move: ");
			move = s.nextInt();
			
			// iterate through moves, check if move is contained within
			for (int x : moves) {
				// if move is found, break out of loop and take input again
				if (x == move) {
					moveIllegal = false;
					break;
				}
				else {
					System.out.println("Invalid selection. Try again.");
					break;
				}
			}
		}
		// remove move from list of possible moves
		moves[move-1] = 0;

		// close scanner, return
		s.close();
		return move;
	}

	// unfinished
	private static int computerInput(int[][] board, int[] moves) {
		// generates computer move input
		Random r = new Random();
		int move = 0;
		boolean moveIllegal = true;

		// get input from user
		while(moveIllegal) {
			move = r.ints(1, 10).findFirst().getAsInt();

			// iterate through moves, check if move is contained within
			for (int x : moves) {
				// if move is found, break out of loop and take input again
				if (x == move) {
					moveIllegal = false;
					break;
				}
			}
		}
		// remove move from list of possible moves
		moves[move-1] = 0;

		return move;
	}

	private static void printBoard(int[][] board, int turn) {
		System.out.printf("Turn %d:%n", turn+1);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				// if "0" found, print an "X", if "1" found, print an "O"
				System.out.printf("%d ", board[i][j]);
			}
			System.out.printf("%n");
		}
	}
	
	private static int parseArgs(String[] args) {
		// try to parse args, catch any failures
			int playerNum = 3; 
			try {
				String str_arg = args[0].trim();
				playerNum = Integer.parseInt(args[1]);
				if (playerNum > 2) { throw new PlayerNumberException(); }
				if (!str_arg.matches("-c")) { throw new UnknownArgumentException(); }
			}
			// catch if player tries to input players > 2
			catch (PlayerNumberException e) {
				System.err.printf("You can only be player 1 or 2.%n%s%n", usage);
				System.exit(1);
			}
			// catch if 2nd arg isn't a number
			catch (NumberFormatException e) {
        		System.err.printf("Argument %s must be an integer.%n%s%n", args[1], usage);
        		System.exit(1);
    		}
    		// catch if only one arg passed, parseInt fails
    		catch (ArrayIndexOutOfBoundsException e) {
    			if (args[0].matches("-c")) {
    				playerNum = 0; // botNum defaults to 0, 3 means both are bots
    			}
    			else {
    			System.err.printf("Too few arguments provided.%n%s%n", usage);
				System.exit(1);
				}
			}
			// catch if flag other than -c is passed
			catch (UnknownArgumentException e) {
				System.err.printf("Argument %s is unknown.%n%s%n", args[0], usage);
				System.exit(1);
			}

			return playerNum;
		}
}	