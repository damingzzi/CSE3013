#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	/* WaterFall-related member variables Regions */
	
	typedef struct Line {
		int x1, x2;
		int y1, y2;
	}_Line;

	typedef struct Dot {
		int x1, y1;
	}_Dot;

	vector<_Line> vLine;
	vector<_Dot> vDot;

	// flag variables
	int draw_flag;
	int load_flag;

	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	int selected_dot=0;
	/* WaterFall-related member functions */

	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.

};