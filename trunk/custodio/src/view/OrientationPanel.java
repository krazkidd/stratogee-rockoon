package view;

import java.awt.Graphics;

import javax.swing.JPanel;

public class OrientationPanel extends JPanel {
	
	// matrices for the unit vectors
	double xUnit[][];
	double yUnit[][];
	double zUnit[][];
	
	public void paintComponent(Graphics g, double x, double y, double z) {
		if (x + y + z < 1.25 && x + y + z > 0.75) { // TODO what window around 1 is acceptable? I used +/- 0.25 here
			// we have about 1g, so there are no forces causing 
			// acceleration and we can measure tilt
			
		}
		else if (x + y + z < 0.1 && x + y + z > -0.1) {
			// free-fall
			// TODO
		}
		else {
			// acceleration is occuring
			
			// TODO
		}
	}
	
	public void paintComponent(Graphics g) {
        super.paintComponent(g);       
              
    }  

}
