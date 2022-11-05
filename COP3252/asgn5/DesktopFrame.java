import javax.swing.JDesktopPane;
import javax.swing.JFrame;
import javax.swing.JInternalFrame;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JMenuBar;

import java.awt.event.*;
import java.awt.*;

public class DesktopFrame extends JFrame implements ActionListener {

    // declare desktop to be used later
    JDesktopPane desktop;

    // DesktopFrame constructor
    public DesktopFrame() {
      super("Desktop Frame");

      desktop = new JDesktopPane();     // create JDP
      setContentPane(desktop);          // set desktop as current ContentPane
      setJMenuBar(createMenuBar());     // create & set menu bar
    }

    private void createFrame(String name) {
        JInternalFrame frame = new JInternalFrame(name, true, true, true, true);
        if (name.equals("Picture Frame")) {
            // set background color to blue
            frame.setBackground( Color.BLUE );

            // create picture object and add to frame
            PicFrame pic = new PicFrame();
            frame.add(pic);
        } else if (name.equals("Movable Picture Frame")) {
            // set background color to white
            frame.setBackground( Color.WHITE );
            
            // create picture object and add to frame
            MPicFrame pic = new MPicFrame();
            frame.add(pic);
        } else {
            // set background color to white
            frame.setBackground( Color.WHITE );

            // create picture object and add to frame
            RPicFrame pic = new RPicFrame();
            frame.add(pic);
        }
        // set default dims, make visible, add to desktop
        frame.setSize(400, 400);  
        frame.setVisible(true);
        desktop.add(frame);
    }

    private JMenuBar createMenuBar() {
        // create menubar object
        JMenuBar menuBar = new JMenuBar();

        // make create menu and add to menubar
        JMenu create_menu = new JMenu("Create");
        menuBar.add(create_menu);

        // make quit menu and add to menubar
        JMenu quit_menu = new JMenu("Quit");
        menuBar.add(quit_menu);

        // creating create menu items
        JMenuItem p_frame = new JMenuItem("Picture");
        p_frame.setActionCommand("npic");
        p_frame.addActionListener(this);
        create_menu.add(p_frame);

        JMenuItem mp_frame = new JMenuItem("Movable Picture");
        mp_frame.setActionCommand("mpic");
        mp_frame.addActionListener(this);
        create_menu.add(mp_frame);

        JMenuItem rp_frame = new JMenuItem("Randomized Picture");
        rp_frame.setActionCommand("rpic");
        rp_frame.addActionListener(this);
        create_menu.add(rp_frame);

        // create quit menu item
        JMenuItem quit_frame = new JMenuItem("Quit Program");
        quit_frame.setActionCommand("exit");
        quit_frame.addActionListener(this);
        quit_menu.add(quit_frame);

        return menuBar;
    }

    public void actionPerformed(ActionEvent e) {
        // define how to act when interacted with
        if ("npic".equals(e.getActionCommand())) {
            createFrame("Picture Frame");
        }
        else if ("mpic".equals(e.getActionCommand())) {
            createFrame("Movable Picture Frame");
        }
        else if ("rpic".equals(e.getActionCommand())) {
            createFrame("Randomized Picture Frame");
        }
        else if ("exit".equals(e.getActionCommand())) {
            System.exit(0);
        }
    }
}