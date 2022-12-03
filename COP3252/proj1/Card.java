import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage; 
import java.io.IOException;
import java.awt.Dimension;

import projPack.*;

public class Card extends JLabel {
    // variables related to card state
    public SuitEnum suit;
    public RankEnum rank;
    public boolean faceUp; 

    // variables related to card image display
    private String filename;
    private BufferedImage image;
    private BufferedImage image_back;
    private final static int CARD_HEIGHT = 150;
    private final static int CARD_WIDTH = 100;

    // variables related to card location for placement 
    private int myX, myY;
    private Dimension dim;

    public Card(SuitEnum suit, RankEnum rank, boolean faceUp) throws IOException {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;            
        this.faceUp = faceUp;

        // load image for card
        setFileName();
        image = getImage(filename);
        image_back = getImage("img/card-back.png");

        // set default location values
        myX = myY = 0;
    
        // set frame size and location
        setPosition(myX, myY);
        setSize(new Dimension(CARD_WIDTH, CARD_HEIGHT));
    }

    public Card(SuitEnum suit, RankEnum rank, boolean faceUp, int posX, int posY) {
        // assign suit and rank val to card
        this.suit = suit;
        this.rank = rank;            
        this.faceUp = faceUp;
        
        // load image for card
        setFileName();
        image = getImage(filename);
        image_back = getImage("img/card-back.png");
        
        // set temp location values
        myX = posX;
        myY = posY;

        // set frame size and location
        setPosition(myX, myY);
        setSize(new Dimension(CARD_WIDTH, CARD_HEIGHT));
    }

    // getters for rank/suit enums
    public SuitEnum getSuit() { return suit; }
    public RankEnum getRank() { return rank; }

    // getters for rank/suit String names
    public String getSuitStr() { return suit.name(); }
    public String getRankStr() { return rank.name(); }

    public int getRankInt() {
        switch (rank) {
            case Ace:
                return 14;
            case King:
                return 13;
            case Queen:
                return 12;
            case Jack:
                return 11;
            case Ten:
                return 10;
            case Nine:
                return 9;    
            case Eight:
                return 8;
            case Seven:
                return 7;
            case Six:
                return 6;
            case Five:
                return 5;
            case Four:
                return 4;
            case Three:
                return 3;
            case Two:
                return 2;
            default:
                return 1; 
        }
    }

    // setter and getter for faceup bool
    public void setFaceUp(boolean faceUp) {
        this.faceUp = faceUp;
    }
    public boolean getFaceUp() {
        return faceUp;
    }
    
    // gets image associated with card
    private void setFileName() {
        filename = "img/" + getRank().name().toLowerCase() + "-" + getSuit().name().toLowerCase() + ".png";
    }

    private BufferedImage getImage(String filename) throws IOException {
        BufferedImage retImage = null;
        try {
            retImage = ImageIO.read(new File(filename));
            return retImage;
        } catch (IOException e) {
            System.err.println("Image read was unsuccessful. Exiting...");
            System.exit(1);
        }
        return retImage;
    }

    // draws image onto cards 
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (faceUp) {
            g.drawImage(image, 0, 0, getWidth(), getHeight(), this);
        } else {
            g.drawImage(image_back, 0, 0, getWidth(), getHeight(), this);
        }
    }
    
    @Override
	public boolean contains(Point p)
	{
		Rectangle rect = new Rectangle(location.x, location.y, Card.CARD_WIDTH, Card.CARD_HEIGHT);
		return (rect.contains(p));
	}
}