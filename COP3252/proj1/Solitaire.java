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
    private ArrayList<Pile> piles;
    private Pile hand;
    private Pile waste;

    Solitaire() {
        // create deck and board
        deck = new Deck();
        board = new Board();

        // create card piles
        piles = new ArrayList<Pile>(7);
        hand = new Pile();
        waste = new Pile();

        // distribute cards from deck into piles
        DealCards();
    }

    private void DealCards() {
        for (int i = 0; i < 7; ++i) {
            // for each tableau, deal some number of cards
            for (int j = 1; j < 7 - i; ++j) {
                piles.get(i).add(deck.Pull());
            }
        }
    }

    public static void main(String[] args) {
        Solitaire game = new Solitaire();
    }
}
