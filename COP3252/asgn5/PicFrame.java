import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

public class PicFrame extends JPanel
{	
	public void paintComponent(Graphics g)
	{
		// create graphics2d obj
		Graphics2D g2d = (Graphics2D)g;
	
		// no need to draw shape for background
		// set background color when extern frame made

		// set ground color 
		g2d.setColor(new Color(110, 38, 14));
		
		// draw ground at bottom of screen
		double y = (.9 * this.getHeight());
		
		// width = frame width, height = 10% of frame height
		double w = this.getWidth();
		double h = (.1 * this.getHeight());
		
		// create ground object
		Rectangle2D.Double ground = new Rectangle2D.Double(0.0, y, w, h);
	
		// draw ground
		g2d.fill(ground);

		// declare sun obj
		Ellipse2D.Double sun;

		// resize based on height/width ratio of frame
		if(this.getHeight() < this.getWidth())
		{
			sun = new Ellipse2D.Double(.7 * this.getWidth(), .1 * this.getHeight(), .25 * this.getHeight(), .25 * this.getHeight());
		}
		else
			sun = new Ellipse2D.Double(.7 * this.getWidth(), .1 * this.getHeight(), .25 * this.getWidth(), .25 * this.getWidth());
	
		// set sun color, fill obj
		g2d.setColor( Color.YELLOW );
		g2d.fill(sun);	
	}
}
