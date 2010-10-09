package view;

import java.awt.FlowLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class MessagePanel extends JPanel {
	
	public MessagePanel(String msg) {
		this.setLayout(new FlowLayout());
		JLabel lblMessage = new JLabel(msg);
		this.add(lblMessage);
	}
}
