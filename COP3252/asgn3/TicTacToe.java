public class TicTacToe {
	public static void main(String[] args) {
		// declare important variables
		boolean gameActive = true; // true by default to enter loop
		boolean playerOneBot = false, playerTwoBot = false;
		int playerNum = 1; // default val, doesn't matter
		String str_arg = "";

		// create 2D matrix "board"
		int[][] board = new int[3][3];

		// deal with command line args
		if (args.length > 0 && args.length < 3) {
			// try to parse args, catch any failures
			try {
				// might be cheating, fix later
				// only check args[1] with parseInt
				playerNum = Integer.parseInt(args[1]);
				str_arg = args[0].trim();
				if (playerNum > 2) { throw new PlayerNumberException(); }
				if (str_arg != "-c") { throw new UnknownArgumentException(); }
			}
			// catch if player tries to input players > 2
			catch (PlayerNumberException e) {
				System.out.println("You can only be player 1 or 2.");
				System.out.println("Usage: java TicTacToe [-c [1|2]]");
				System.exit(1);
			}
			// catch if 2nd arg isn't a number
			catch (NumberFormatException e) {
        		System.err.println("Argument" + args[1] + " must be an integer.");
        		System.exit(1);
    		}
    		// catch if -c arg isn't passed, 
    		catch (ArrayIndexOutOfBoundsException e) {
    			System.err.println("Too few arguments provided.");
				System.out.println("Usage: java TicTacToe [-c [1|2]]");
				System.exit(1);
			}
			catch (UnknownArgumentException e) {
				System.err.println("Argument " + args[0] + " is unknown.");
				System.out.println("Usage: java TicTacToe [-c [1|2]]");
				System.exit(1);
			}
		}
		else if (args.length > 2) {
			System.out.println("Too many arguments provided.");
			System.out.println("Usage: java TicTacToe [-c [1|2]]");
			System.exit(1);
		}


		/*
		// gameplay loop here
		while (gameActive) {

		}
		*/

	}
}