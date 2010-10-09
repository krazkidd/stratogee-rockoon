package view;

import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ButtonPanel extends JPanel {
	JButton btnMasterAlarm;
	
	JLabel lblAlarmMessage;
	
	JButton btnLaunch;
	
	JLabel lblLaunchKey;
	
	JButton btnAbort;
	
	JLabel lblAbortKey;
	
	public ButtonPanel() {
		setLayout(new GridLayout(2,3));
		
		btnMasterAlarm = new JButton("Master Alarm");
		btnMasterAlarm.setEnabled(false);
		lblAlarmMessage = new JLabel();
		
		btnLaunch = new JButton("Launch");
		btnLaunch.setEnabled(false);
		ImageIcon icon = new ImageIcon("resources/keyswitch_off.png");
		JLabel lblLaunchKey = new JLabel(icon);
		
		btnAbort = new JButton("Abort");
		btnAbort.setEnabled(false);
		ImageIcon icon2 = new ImageIcon("resources/keyswitch_off.png");
		JLabel lblAbortKey = new JLabel(icon);
		
		// add everything
		add(btnMasterAlarm);
		add(btnLaunch);
		add(lblLaunchKey);
		add(lblAlarmMessage);
		add(btnAbort);
		add(lblAbortKey);
	}
}
