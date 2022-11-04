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
      System.out.println("New DesktopFrame created!");
    }

    private void createFrame() {
        JInternalFrame frame = new JInternalFrame();        
        frame.setVisible(true);
        desktop.add(frame);
    }

    private JMenuBar createMenuBar() {
        JMenuBar menuBar = new JMenuBar();

        // make create menu and add to menubar
        JMenu create_menu = new JMenu("Create");
        menuBar.add(create_menu);

        // make quit menu and add to menubar
        JMenu quit_menu = new JMenu("Quit");
        menuBar.add(quit_menu);

        // creating create menu items
        JMenuItem p_frame = new JMenuItem("Picture Frame");
        p_frame.setActionCommand("npic");
        p_frame.addActionListener(this);
        create_menu.add(p_frame);

        JMenuItem mp_frame = new JMenuItem("Movable Picture Frame");
        mp_frame.setActionCommand("mpic");
        mp_frame.addActionListener(this);
        create_menu.add(mp_frame);

        JMenuItem quit_frame = new JMenuItem("Quit Program");
        quit_frame.setActionCommand("exit");
        quit_frame.addActionListener(this);
        quit_menu.add(quit_frame);

        return menuBar;
    }

    public void actionPerformed(ActionEvent e) {
        if ("npic".equals(e.getActionCommand())) {
            createFrame();
        }
        else if ("mpic".equals(e.getActionCommand())) {
            createFrame();
        }
        else if ("exit".equals(e.getActionCommand())) {
            System.exit(0);
        }
    }
}