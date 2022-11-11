import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.event.*;
import java.awt.*;

// holds card and card image
public class CardPanel extends JComponent {
    private Card card;
    private String filename;
    private BufferedImage image;

    private int locX = 0;
    private int locY = 0;
    private int myX = 0;
    private int myY = 0;

    public CardPanel(Card card) {
        setBorder(new LineBorder(Color.BLACK, 2));
        setBounds(0, 0, 100, 150);

        // all of this to make 
        addMouseListener(new MouseListener() {
            @Override
            public void mousePressed(MouseEvent e) {
                locX = e.getXOnScreen();
                locY = e.getYOnScreen();

                myX = getX();
                myY = getY();
            }
            
            @Override
            public void mouseClicked(MouseEvent e) { }
            @Override
            public void mouseReleased(MouseEvent e) { }
            @Override
            public void mouseEntered(MouseEvent e) { }
            @Override
            public void mouseExited(MouseEvent e) { }
            }
        ); 

        addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
              int dX = e.getXOnScreen() - locX;
              int dY = e.getYOnScreen() - locY;
      
              setLocation(myX + dX, myY + dY);

              // check for available snapping columns
            }
      
            @Override
            public void mouseMoved(MouseEvent e) { }
            }
        );


        this.card = card;
        setFileName();
        try {
            image = ImageIO.read(new File(filename));
        } catch (IOException e) {
            System.err.println("Image read was unsuccessful. Exiting...");
            System.exit(1);
        }
    }

    // gets image associated with card
    private void setFileName() {
        filename = "img/" + card.getRank().name().toLowerCase() + "-" + card.getSuit().name().toLowerCase() + ".png";
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, getWidth(), getHeight(), this);
    }
}