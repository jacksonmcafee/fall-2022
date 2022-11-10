import java.util.ArrayList;
import projPack.*;

public class Pile {
    public ArrayList<Card> pile;

    public Pile() {
        pile = new ArrayList<Card>();
        for (int i = 0; i < 13; ++i) {
            pile.add(new Card(SuitEnum.Null, RankEnum.Null));
        }
    }

    public void Add(Card card) {
        pile.add(card);
    }

    public void Remove(int index) {
        pile.remove(index);
    }

    public Card Get(int index) {
        return pile.get(index);
    }

    public int Size() {
        return pile.size();
    }

    public void Clear() {
        pile.clear();
    }
}
