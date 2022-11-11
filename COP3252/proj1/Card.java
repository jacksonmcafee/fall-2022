import projPack.*;

public class Card {
    public SuitEnum suit;
    public RankEnum rank;
    public boolean faceUp; 

    public Card(SuitEnum suit, RankEnum rank) {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;

        faceUp = false;
    }

    public Card(SuitEnum suit, RankEnum rank, boolean faceUp) {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;
            
        this.faceUp = faceUp;
    }

    public SuitEnum getSuit() {
        return suit;
    }
    public RankEnum getRank() {
        return rank;
    }

    public String toString() {
        return rank.name() + " of " + suit.name();
    }

    public void setFaceUp(boolean faceUp) {
        this.faceUp = faceUp;
    }
}