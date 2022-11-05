import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.util.Random;

public class RPicFrame extends JPanel {
	
	public void paintComponent(Graphics g)
	{		
		// create graphics2d obj
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;

		// create random number 1-5
		Random r = new Random();		
		int x = r.ints(1,5).findFirst().getAsInt();

		for (int i = 0; i < x; i++) {
			generateRect(g2d);
		}
	}

	private Rectangle2D.Double generateRect(Graphics2D g2d) {
		// get colors
		Random random = new Random();
		int r = random.ints(0,255).findFirst().getAsInt();
		int g = random.ints(0,255).findFirst().getAsInt();
		int b = random.ints(0,255).findFirst().getAsInt();

		// get location
		double x = random.nextDouble() * (this.getWidth());
		double y = random.nextDouble() * (this.getHeight());

		// get dimensions
		double w = 1.0 + random.nextDouble() * (this.getWidth() * .5 - 1);
		double h = 1.0 + random.nextDouble() * (this.getHeight() * .5 - 1);

		// create rectangle
		Rectangle2D.Double rect = new Rectangle2D.Double(x, y, w, h);

		// set color, fill rect, then return
		g2d.setColor(new Color(r, g, b));
		g2d.fill(rect);
		return rect;
	}
}