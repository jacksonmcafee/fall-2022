import java.util.Collections;
import java.util.ArrayList;
import java.util.Arrays;
import projPack.*;

public class Deck {
    private ArrayList<Card> deck;
    private Card dummy;

    public Deck() {
        // initialize deck
        deck = new ArrayList<Card>();

        // generate deck as 52 in-order cards
        GenDeck();
        
        // shuffle deck
        RandomizeDeck();
    }

    private void GenDeck() {
        // arraylists of values
        ArrayList<SuitEnum> suits = new ArrayList<SuitEnum>(Arrays.asList(SuitEnum.values()));
        ArrayList<RankEnum> ranks = new ArrayList<RankEnum>(Arrays.asList(RankEnum.values()));

        // create card of every type in order
        for (SuitEnum s : suits) {
            for (RankEnum r : ranks) {
                deck.add(new Card(s, r));
            }
        }
    }

    // shuffles cards in deck
    private void RandomizeDeck() {
        // use Collections.shuffle() to shuffle
        Collections.shuffle(deck);
    }

    // pulls the top card from the deck
    public Card Pull() {
        if (deck.isEmpty()) {
            // if there are no more pullable cards, return a joker
            return dummy;
        }
        
        // store return card, remove it from deck
        Card retcard = deck.get(0);
        deck.remove(0);
        return retcard;
    }

    /* Testing Purposes Only */
    public void PrintDeck() {
        for (Card c : deck) {
            System.out.println(c);
        }
    }

    public int size() {
        return deck.size();
    }
}