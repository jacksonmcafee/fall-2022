import projectPack.*;

public class Card {
    public SuitEnum suit;
    public RankEnum rank;
    public boolean isVisible; 

    public Card(SuitEnum suit, RankEnum rank) {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;

        isVisible = false;
    }

    public Card(SuitEnum suit, RankEnum rank, boolean visible) {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;
            
        isVisible = visible;
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

    public void setVisible(boolean visible) {
        this.isVisible = visible;
    }
}