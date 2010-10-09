package view;

import java.awt.FlowLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class LiveFeedPanel extends JPanel {
	public LiveFeedPanel() {
		this.setLayout(new FlowLayout());
		add(new JLabel("Live feed goes here."));
	}
}