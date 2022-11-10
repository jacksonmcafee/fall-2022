// Texas Hold'em Poker, main project file
// Very liberal use of ArrayList in this project...

import java.util.ArrayList;
import java.util.Collections;

public class Solitaire {
    // declare variables
    private Board board;
    private Deck deck;
    private Card dummy;

    // piles on the main table
    private ArrayList<Pile> piles;
    private Pile hand;
    private Pile waste;
    private ArrayList<Pile> foundations;

    public Solitaire() {
        // create deck and board
        deck = new Deck();

        // create card piles
        piles = new ArrayList<Pile>();
        hand = new Pile();
        waste = new Pile();
        foundations = new ArrayList<Pile>();

        // add 7 piles to piles and 4 to foundations
        // initializer
        SetPiles();

        // distribute cards from deck into piles
        DealCards();
        PopulateHand();

        // set vis of cards that are not the top card of a pile to false
        SetVisibility(); 

        board = new Board();
    }

    private void SetPiles() {
        for (int i = 0; i < 7; ++i) {
            Pile pile = new Pile();
            piles.add(pile);
        }
        for (int i = 0; i < 4; ++i) {
            Pile pile = new Pile();
            foundations.add(pile);
        }
    }

    // deals cards from deck into each tableau
    private void DealCards() {
        for (int i = 0; i < 7; ++i) {
            Pile pile = piles.get(i);
            // for each tableau, deal some number of cards
            for (int j = i + 1; j != 0; --j) {
                System.out.println("Card pulled!");
                // populate pile i with a pulled card
                // pile[-1] == top of the pile
                pile.Add(deck.Pull());
            }
        }
    }

    // take the remainder of the deck and push it to the hand
    private void PopulateHand() {
        for (int i = 0; i < deck.size(); ++i) {
            hand.Add(deck.Pull());
        }
    }

    // adjusts visibility for each card as needed
    // only needed during setup 
    private void SetVisibility() {
        for (int i = 0; i < 7; ++i) {
            Pile pile = piles.get(i);
            for (int j = 0; j < 13; ++j)
            {
                Card card = pile.Get(j);
                // gross, but if card c == pile top card, set visibility to true
                if (card == pile.Get(pile.Size() - 1)) {
                    card.setVisible(true);
                }
            }
        }
    }

    // used to take hand cards and throw them into the waste pile
    private void Trash() {
        waste.Add(hand.Get(0));
        hand.Remove(0);
    }

    private static void RunGame() {
        Solitaire game = new Solitaire();

    }

    public static void main(String[] args) {
        // to make main as simple as possible,
        // RunGame holds the main body of the game
        RunGame();
    }
}
