#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

	// We still want to draw on a black background, so we need to draw
	// the background before we do anything with the brush
	ofBackground(255, 255, 255);
	ofSetLineWidth(4);

	draw_flag = 0;
	load_flag = 0;
	dot_diameter = 10.0f;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(127, 23, 31);  // Set the drawing color to brown

	// Draw shapes for ceiling and floor
	ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
	ofSetLineWidth(5);

	if (draw_flag) {

		/* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
		 Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
		 */

		for (int i = 0; i < vLine.size(); i++) {
			ofDrawLine(vLine[i].x1, vLine[i].y1, vLine[i].x2, vLine[i].y2);
		}

		for (int i = 0; i < vDot.size(); i++) {
			if (i == selected_dot) ofSetColor(255, 0, 0);
			else ofSetColor(0, 0, 0);
			ofDrawCircle(vDot[i].x1, vDot[i].y1, dot_diameter);
		}

		// 2nd week portion.
		ofSetLineWidth(2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'v') {
		// HACK: only needed on windows, when using ofSetAutoBackground(false)
		glReadBuffer(GL_FRONT);
		ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
	}
	if (key == 'q') {
		// Reset flags
		draw_flag = 0;

		// Free the dynamically allocated memory exits.
		vLine.clear();
		vDot.clear();

		cout << "Dynamically allocated memory has been freed." << endl;

		_Exit(0);
	}
	if (key == 'd') {
		if (load_flag != 1) return;
		
		/* COMSIL1-TODO 2: This is draw control part.
		You should draw only after when the key 'd' has been pressed.
		*/
		draw_flag = 1;
	}
	if (key == 's') {
		// 2nd week portion.
	}
	if (key == 'e') {
		// 2nd week portion.
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 'l') {
		// Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			processOpenFileSelection(openFileResult);
			load_flag = 1;
		}
	}

	/* COMSIL1-TODO 4: This is selection dot control part.
	 You can select dot in which water starts to flow by left, right direction key (<- , ->).
	 */

	if (key == OF_KEY_RIGHT) {
		//selected_dot++;
		if (selected_dot == num_of_dot-1) {
			selected_dot = 0;
		}
		else selected_dot++;

		cout << "Selcted Dot Coordinate is (" << vDot[selected_dot].x1 << ", " << vDot[selected_dot].y1  <<")" << endl;
	}
	if (key == OF_KEY_LEFT) {
		if (selected_dot == 0) {
			selected_dot = (num_of_dot-1);
		}
		else selected_dot--;
		
		cout << "Selcted Dot Coordinate is (" << vDot[selected_dot].x1 << ", " << vDot[selected_dot].y1 << ")" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	//Path to the comma delimited file
	//string fileName = "input.txt";

	string fileName = openFileResult.getName();
	ofFile file(fileName);

	if (!file.exists()) cout << "Target file does not exists." << endl;
	else cout << "We found the target file." << endl;

	ofBuffer buffer(file);

	/* This variable is for indicating which type of input is being received.
	 IF input_type == 0, then work of getting line input is in progress.
	 IF input_type == 1, then work of getting dot input is in progress.
	 */
	int input_type = 0;


	/* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
	 You must maintain those information. But, currently below code is not complete.
	 Also, note that all of coordinate should not be out of screen size.
	 However, all of coordinate do not always turn out to be the case.
	 So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
	*/

	int height = ofGetHeight();
	int width = ofGetWidth();

	// Read file line by line
	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;
		// Split line into strings
		vector<string> words = ofSplitString(line, " ");

		if (words.size() == 1) {
			if (input_type == 0) { // Input for the number of lines.
				num_of_line = atoi(words[0].c_str());
				cout << "The number of line is: " << num_of_line << endl;
				input_type = 1;
			}
			else { // Input for the number of dots.
				num_of_dot = atoi(words[0].c_str());
				cout << "The number of dot is: " << num_of_dot << endl;
			}
		}
		else if (words.size() >= 2) {
			int x1, y1, x2, y2;
			if (words.size()==4) { // Input for actual information of lines
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				x2 = atoi(words[2].c_str());
				y2 = atoi(words[3].c_str());
				if ((x1 >= width) && (y1 >= height)) {
					cout << "Error: Out of Window"<<'\n';
					if((x2 >= width) && (y2 >= height))
						cout << "Error: Out of Window" << '\n';
				}
				_Line temp;
				temp.x1 = x1; temp.y1 = y1;
				temp.x2 = x2; temp.y2 = y2;
				vLine.push_back(temp);
			}
			else { // Input for actual information of dots.
				x1 = atoi(words[0].c_str());
				y1 = atoi(words[1].c_str());
				if ((x1 >= width) && (y1 >= height)) {
					cout << "Error: Out of Window" << '\n';
				}
				_Dot temp;
				temp.x1 = x1; temp.y1 = y1;
				vDot.push_back(temp);
			}

		} // End of else if.
	} // End of for-loop (Read file line by line).
	//initializeWaterLines();
}

void ofApp::initializeWaterLines() {
	;
}