#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#include "ofxDatGui.h"

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

        void onDropdownEvent(ofxDatGuiDropdownEvent e);

        ofTrueTypeFont curlyFont; // standard font
		ofTrueTypeFont font; // standard font
		ofTrueTypeFont titleFont; // font for some info in the title line

		//----------------------------------------
		// Client side:

		ofxOscSender clientSender; // all-important ofxOscSender object
		string clientDestination; // IP address we're sending to
		int clientSendPort; // port we're sending to
		string clientTyping; // what we're going to send: some stuff you typed

        vector<ofxDatGuiComponent*> components;

        ofxDatGuiDropdown* dropdown;

        bool bDoSendMessage;


        ofXml xml;
};
