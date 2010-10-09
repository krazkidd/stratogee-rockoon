package view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

/**
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO
 * SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS, TEAM TOKYO SEA LIONS,
 * 
 * 
 * @author Mark Ross
 */
public class AboutFrame extends JFrame {

	private static final long serialVersionUID = 1L;

	/**
	 * This constructor creates a new AboutFrame object which contains all the
	 * about information for our project
	 */
	public AboutFrame() {
		// icon
		JPanel pnlIcon = new JPanel();
		pnlIcon.setLayout(new BorderLayout());

		//ImageIcon icon = new ImageIcon("resources/images/other/seapimp.png");
		//JLabel lbl = new JLabel(icon);

		// close button
		JButton btnClose = new JButton("Close");
		btnClose.addActionListener(new btnCloseListener());

		// right side with labels
		JPanel pnl = new JPanel(new BorderLayout());
		JTextArea text = new JTextArea("This program was written by Mark Ross but the whole project was directly worked on by about 15 students. See\n" +
				"http://sites.google.com/site/uofarockoon\n" +
				"for more information about the project.");
		text.setLineWrap(true);
		pnl.add(text);

		// add stuff to panel
		pnlIcon.add(pnl, BorderLayout.CENTER);
		pnlIcon.add(btnClose, BorderLayout.SOUTH);

		// add panel and set window properties
		add(pnlIcon);
		setTitle("About Custodio");
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setResizable(false);
		setPreferredSize(new Dimension(650, 450));
		pack();
	}

	/**
	 * Listener for close window button
	 */
	private class btnCloseListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent arg0) {
			dispose();
		}
	}
}
