/* I'm aware that having a try/catch block isn't required for this to work, nor is it
particularly necessary. I'm new to Java and thought it might be fun to throw
a few in just for a bit of practice. Might refactor entire block later. */ 

public class TicTacToe {

	// constant
	public static final String usage = "Usage: java TicTacToe [-c [1|2]]";

	public static void main(String[] args) {

		/*
		playerNum == 0, 2 bots
		playerNum == 1, p1 = human, p2 = bot
		playerNum == 2, p1 = bot, p2 = human
		playerNum == 3, 2 humans
		*/
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

		int winner = gameLoop();

	}

	 private static int gameLoop() {
		int[][] board = new int[3][3]; // create 2D matrix "board"
		boolean gameActive = true;
		int winner = 0, turn = 0;

		while(gameActive) {
			printBoard(board, turn);

			

			turn++;
			if (turn == 9) {
				gameActive = false;
			}
		}
		return winner;
	} 

	private static void printBoard(int[][] board, int turn) {
		System.out.printf("Turn %d:%n", turn+1);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
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