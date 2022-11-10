import javax.swing.JFrame;
import javax.swing.JButton;

public class Board extends JFrame {
    JFrame frame;
    JButton button;

    public Board() {
        frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800,800);
        frame.setVisible(true);
    }
}