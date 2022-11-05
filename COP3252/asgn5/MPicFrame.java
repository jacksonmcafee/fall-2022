import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;

// This doesn't work, just draws a nice resizable green oval.
public class MPicFrame extends JPanel
{
	public void paintComponent(Graphics g)
	{		
		// create graphics2d obj
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D)g;

		// set x/y coords
		double x = (.35 * getWidth());
		double y = (.35 * getHeight());

		// width/height at 30% of w/h
		double w = (.3 * getWidth());
		double h = (.3 * getHeight());

		// create oval w/ locations & dims
		Ellipse2D.Double oval = new Ellipse2D.Double(x, y, w, h);
		
		// set color to green then fill
		g2d.setColor( Color.GREEN );
		g2d.fill(oval);
	}
}
