import javax.swing.JLayeredPane;

import java.io.IOException;
import java.awt.Graphics;

import java.util.Vector;
import java.util.Arrays;
import java.util.Collections;
import projPack.*;

/*
Deck is implements a Vector of cards because cards must be able to be moved singly and 
as a unit (moving a pile). 
*/


public class Deck {
    // because deck needs to have cards added AND removed, 
    // vectors are easily applicable. stacks are an alternative.
    private Vector<Card> deck;

    // in case of an error, throw dummy
    private Card dummy;

    // main deck constructor
    public Deck() throws IOException {
        // initialize deck
        deck = new Vector<Card>();

        // generate deck as 52 in-order cards
        GenDeck();
        
        // shuffle deck
        RandomizeDeck();
    }

    public Deck(int vals) {
        // initialize deck
        deck = new Vector<Card>(vals);
    }

    private void GenDeck() throws IOException {
        // vectors of values
        Vector<SuitEnum> suits = new Vector<SuitEnum>(Arrays.asList(SuitEnum.values()));
        Vector<RankEnum> ranks = new Vector<RankEnum>(Arrays.asList(RankEnum.values()));

        // create card of every type in order
        for (SuitEnum s : suits) {
            for (RankEnum r : ranks) {
                deck.add(new Card(s, r, false));
            }
        }
    }

    // shuffles cards in deck
    private void RandomizeDeck() {
        // use Collections.shuffle() to shuffle
        Collections.shuffle(deck);
    }

    // return if a given deck is empty
    private boolean isEmpty() {
        return deck.isEmpty();
    }
    private int Size() {
        return deck.size();
    }

    // push cards to the front or back of vector
    private void pushFront(Card card) {
        deck.add(0, card);
    }
    private void pushBack(Card card) {
        deck.add(card);
    }

    // peek cards at the front of back of vector
    private Card peekFront() {
        return deck.firstElement();
    }
    private Card peekBack() {
        return deck.lastElement();
    }

    // pop cards from front of back of vector
    private Card popFront() {
        Card card = dummy;
        if (!isEmpty()) {
            card = deck.get(0);
            deck.remove(0);
        } 
        return card;
    }
    private Card popBack() {
        Card card = dummy;
        if (!isEmpty()) {
            card = deck.get(deck.size());
            deck.remove(0);
        }
        return card;
    }

    public Card getCard() {
        // pulls top card and removes it from the deck
        Card c = deck.get(0);
        deck.remove(0);
        return c;
    }
}