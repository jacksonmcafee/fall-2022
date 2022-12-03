import java.util.Vector;
import javax.swing.JLayeredPane;
import java.awt.Dimension;
import java.awt.Component; 
import java.io.IOException;
import projPack.*;

public class Pile extends JLayeredPane {
    // storage for cards
    public Vector<Card> pile;
    Card baseCard;
    SuitEnum allowedSuit;
    
    // when cards are rendered, offset each by 20 from top of previous card
    int cardOffset = 20;
    int width;
    Pile parentPile;
    PileEnum pileType;

    public Pile(int width) throws IOException {
        pile = new Vector<Card>();
        this.width = width;

        baseCard = new Card(null, null, true);
        add(baseCard, 1, 0);

        pileType = PileEnum.Normal;
    }

    public void Add(Card card) {
        card.setLocation(0, cardOffset * pile.size());
        pile.add(card);

        this.add(card, 1, 0);
        updateSize();
    }

    public void Remove(Card card) {
        pile.remove(card);
        this.remove(card);

        updateSize();
    }

    // returns information about card at index
    public Card Get(int index) {
        return pile.get(index);
    }

    // returns information on first card
    public Card Peek() {
        return Get(pile.size() - 1);
    }

    public int Size() {
        return pile.size();
    }

    public void Clear() {
        pile.clear();
    }

    public void setWidth(int width) {
        this.width = width;
        updateSize();
    }

    // updates the size of a pile 
	public void updateSize() {
		int height = baseCard.getSize().height;
		
		if(!pile.isEmpty()) {
			height += cardOffset * (pile.size() - 1);
		}

		this.setPreferredSize(new Dimension(width, height));
		this.setSize(width, height);
	}

    public void setOffset(int offset) {
        this.cardOffset = offset;
        updateSize();
    }

    public Pile splitPile(Card card) throws IOException {
        Pile p = new Pile(100);

        for (int i = 0; i < pile.size(); ++i) {
            if (pile.get(i) == card) {
                for (int j = i; j < pile.size();) {
                    p.Add(pile.get(i));
                    Remove(pile.get(i));
                }
            }
        }

        p.parentPile = this;
        return p;
    }

    public void mergePile(Pile p) {
        for (Card card : p.pile) {
            Add(card);
        }
        updateSize();
    }

    public Card searchCard(int val, String suitName) {
        for (Card card : pile) {
            if (card.getRankInt() == val && card.getSuitStr().equals(suitName)) {
                return card;
            }
        }
        return null;
    }

    public boolean isStackable(Pile p) {
        if (this == p) { return false; }
    
        Card card = p.pile.get(0);
        Card topCard;

        switch (pileType) {
            case Normal:
                if (pile.isEmpty()) {
                    if (card.getRankInt() == 14) {
                        return true;
                    } else {
                        return false;
                    }
                }

                topCard = pile.get(pile.size() - 1);
                if (topCard.isVisible()) {
                    return false;
                } 

                if (topCard.suit.isBlack() != card.suit.isBlack()) {
                    if (topCard.getRankInt() == card.getRankInt() + 1 || topCard.getRankInt() == 12 && card.getRankInt() == 10) {
                        return true;
                    }
                }
                break;

            case Final:
                if (p.pile.size() > 1) { return false; }

                if (pile.isEmpty() && card.getRankInt() == 1) {
                    allowedSuit = card.suit;
                    return true;
                }

                if (allowedSuit != card.suit) {
                    return false;
                }
                topCard = pile.get(pile.size() - 1);
                if (topCard.getRankInt() == card.getRankInt() - 1 || topCard.getRankInt() == 10 && card.getRankInt() == 12) {
                        return true;
                    }
                break;
                }

            return false;
        }

        @Override
        public Component.BaselineResizeBehavior getBaselineResizeBehavior() {
            return Component.BaselineResizeBehavior.CONSTANT_ASCENT;
        }
    
        @Override
        public int getBaseline(int width, int height) {
            return 0;
        }
}
