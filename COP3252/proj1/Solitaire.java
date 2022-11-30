// Texas Hold'em Poker, main project file
// Very liberal use of ArrayList in this project...

import java.util.ArrayList;
import java.util.Collections;
import projectPack.*;

public class Solitaire {
    // declare variables
    private Board board;
    private Deck deck;

    // piles on the main table
    private ArrayList<ArrayList<Card>> piles;
    private ArrayList<Card> hand;
    private ArrayList<Card> waste;
    private ArrayList<ArrayList<Card>> foundations;

    public Solitaire() {
        // create deck and board
        deck = new Deck();

        // create card piles
        piles = new ArrayList<ArrayList<Card>>();
        hand = new ArrayList<Card>();
        waste = new ArrayList<Card>();
        foundations = new ArrayList<ArrayList<Card>>();

        // distribute cards from deck into piles
        DealCards();
        PopulateHand();

        // set vis of cards that are not the top card of a pile to false
        SetVisibility(); 

        board = new Board();
    }

    // deals cards from deck into each tableau
    private void DealCards() {
        for (int i = 1; i < 8; ++i) {
            // for each tableau, deal some number of cards
            for (int j = i; j != 0; --j) {
                // populate pile (i-0) with a pulled card
                // pile[-1] == top of the pile
                piles.get(i-1).add(deck.Pull());
            }
        }
    }

    // take the remainder of the deck and push it to the hand
    private void PopulateHand() {
        for (int i = 0; i < deck.size(); ++i) {
            hand.add(deck.Pull());
        }
    }

    // adjusts visibility for each card as needed
    // only needed during setup 
    private void SetVisibility() {
        for (int i = 0; i < 7; ++i) {
            for (Card card : piles.get(i)) {
                // gross, but if card c == pile top card, set visibility to true
                if (card == piles.get(i).get(piles.get(i).size())) {
                    card.setVisible(true);
                }
            }
        }
    }

    // used to take hand cards and throw them into the waste pile
    private void Trash() {
        waste.add(hand.get(0));
        hand.remove(0);
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
