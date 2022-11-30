import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JButton;

public class Board extends JFrame {
    JFrame frame;
    JButton button;

    Board() {
        frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800,800);
        button = new JButton("Press");
        frame.getContentPane().add(button);
        frame.setVisible(true);
    }
}