#pragma once

#include "ofMain.h"
#include <math.h>
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
		double x1, y1;
	}_Dot;

	typedef struct Water {
		int x1, x2;
		int y1, y2;
		float m;
	}_WaterLine;

	vector<_Line> vLine;
	vector<_Dot> vDot;
	vector<_WaterLine> vWLine;
	vector<_Dot> vWDot;

	// flag variables
	int draw_flag;
	int load_flag;
	int water_flag;

	// Line segment and dot related variables
	int num_of_line, num_of_dot;
	float dot_diameter;
	int selected_dot=0;
	int selected_line = -1;
	float epsilon = 0.016;
	double wX, wY;
	int height = 0;
	/* WaterFall-related member functions */
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.
	void WaterLines(int h);
};