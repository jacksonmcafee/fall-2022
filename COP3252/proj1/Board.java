import javax.swing.JFrame;
import java.awt.Color;
import projPack.*;

public class Board extends JFrame {
    JFrame frame;

    public Board() {
        frame = new JFrame();
        frame.getContentPane().setBackground(new Color(13, 75, 13));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);
        frame.setSize(1000,800);


        // each foundation needs a snapping location
        for (int i = 0; i < 4; ++i) {

        }

        // the hand and deck needs a snapping location

        Card card = new Card(SuitEnum.Hearts, RankEnum.Queen);
        CardPanel cardPanel = new CardPanel(card);
        frame.add(cardPanel);


        frame.setVisible(true);

    }
}