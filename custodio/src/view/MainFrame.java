package view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JCheckBoxMenuItem;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;


/**
 * TODO
 * 
 * @author Mark Ross
 */
public class MainFrame extends JFrame {
	// attributes ///////////////////////////////////////////

	private static final long serialVersionUID = 1L;
	/**
	 * The menu of this window.
	 */
	private JMenuBar menuBar;

	// constructors /////////////////////////////////////////

	/**
	 * Creates a new MainFrame which is a Rube Goldberg game.
	 */
	public MainFrame() {
		// set window properties
		setLayout(new BorderLayout());
		setDefaultCloseOperation(DO_NOTHING_ON_CLOSE); // TODO add window listener to prompt
		setPreferredSize(new Dimension(1024, 768));
		setTitle("Custodio - UA SEDS Rockoon Ground Control Station");

		// create menu bar and top level menu items
		menuBar = new JMenuBar();
		JMenu fileMenu = new JMenu("File");
		JMenu helpMenu = new JMenu("Help");
		menuBar.add(fileMenu);
		menuBar.add(helpMenu);

		// create second level menu items and add them
		JMenuItem exitMenuItem = new JMenuItem("Exit");
		JMenuItem aboutMenuItem = new JMenuItem("About");
		
		// add listeners
		exitMenuItem.addActionListener(new mnuExitListener());
		aboutMenuItem.addActionListener(new mnuAboutListener());
		
		// add items to menu
		fileMenu.add(exitMenuItem);
		helpMenu.add(aboutMenuItem);

		// create panels
		MessagePanel messagePanel = new MessagePanel("Welcome!");
		TelemetryPanel telemetryPanel = new TelemetryPanel();
		ButtonPanel buttonPanel = new ButtonPanel();
		buttonPanel.setPreferredSize(new Dimension(this.getWidth(), 100));
		LiveFeedPanel liveFeedPanel = new LiveFeedPanel();
		OrientationPanel orientationPanel = new OrientationPanel();

		// add everything to the window
		this.setJMenuBar(this.menuBar);
		this.add(messagePanel, BorderLayout.NORTH);
		this.add(telemetryPanel, BorderLayout.WEST);
		//this.add(liveFeedPanel, BorderLayout.CENTER);
		this.add(orientationPanel, BorderLayout.CENTER);
		this.add(buttonPanel, BorderLayout.SOUTH);

		this.pack();
	}

	// main /////////////////////////////////////////////////

	/**
	 * Main entry point of the program. Creates and displays a new window.
	 */
	public static void main(String[] args) {
		// create the window and display it
		new MainFrame().setVisible(true);
	}

	// listeners ////////////////////////////////////////////

	/**
	 * This ActionListener creates a pop-up dialog containing about information.
	 */
	private class mnuAboutListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			AboutFrame abt = new AboutFrame();
			abt.setLocationRelativeTo(null);
			abt.setVisible(true);
		}
	}

	/**
	 * This ActionListener exits the program.
	 */
	private class mnuExitListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent arg0) {
			// TODO change this to prompt
			System.exit(0);
		}
	}
}
