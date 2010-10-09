package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class TelemetryPanel extends JPanel {
	
	public TelemetryPanel() {
		setLayout(new GridLayout(10, 1));
		
		setTelemetryText("N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A", "N/A");
		

	}
	
	public void setTelemetryText(String latitude, String longitude, String altitude, String acceloX, String acceloY, String acceloZ, String angle, String temp) {
		this.removeAll();
		
		this.add(new JLabel("## GPS ##"));
		this.add(new JLabel("Latitude: " + latitude));
		this.add(new JLabel("Longitude: " + longitude));
		this.add(new JLabel("Altitude: " + altitude));
		this.add(new JLabel("## Accelo (g) ##"));
		this.add(new JLabel("X: " + acceloX));
		this.add(new JLabel("Y: " + acceloY));
		this.add(new JLabel("Z: " + acceloZ));
		this.add(new JLabel("Angle: " + angle));
		this.add(new JLabel("## Temp (degrees C) ##"));
		this.add(new JLabel("Fuel: " + temp));
	}
}
