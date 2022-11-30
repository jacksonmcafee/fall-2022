import java.util.ArrayList;
import projectPack.*;

public class Player {
    private ArrayList<Card> hand;
    public int balance;
    
    Player() {
        // every player starts with $10,000
        balance = 10000;
        hand = new ArrayList<Card>();
    }

    public void AddCard(Card c) {
        hand.add(c);
    }

    // whenever a bet occurs OR a win occurs, update player balances
    public void ChangeBalance(int val) {
        balance += val;
    }

    // at the end of each round, reset all player hands
    public void ResetHand() {
        hand.clear();
    }

    public OptionEnum getOption() {
        if (true) {
            return Raise;
        }
        else if (true) {
            return Bet;
        }
        else if (true) {
            return Check;
        }
        else {
            return Fold;
        }
    }
}
