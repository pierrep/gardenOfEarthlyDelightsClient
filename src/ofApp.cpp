#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // run at 60 fps
    //ofSetVerticalSync(true);

	// set bg to a nice grey!
	ofBackground(150);

	// load fonts to display stuff
	font.load("futura_book.otf", 12);
    curlyFont.load("Lobster.otf", 30);
    titleFont.load("futura_book.otf", 16);

	// Enable some logging information
	ofSetLogLevel(OF_LOG_VERBOSE);


    vector<string> options = {"1 - Travel", "2 - Home", "3 - Waste", "4 - Food", "5 - Water", "6 - Habitat", "7 - Divest"};
    dropdown = new ofxDatGuiDropdown("dropdown menu", options);
    dropdown->setPosition(700, 10);
    dropdown->expand();
    dropdown->onDropdownEvent(this, &ofApp::onDropdownEvent);
    components.push_back(dropdown);

    bDoSendMessage = false;

    string ip = "192.168.0.4";
    int port = 9001;

    if( xml.load("settings.xml") ){
        ofLogNotice() << "settings.xml loaded!";

        if(xml.exists("OSC"))
        {
            // This gets the first item (notice the [0], it's just like an array)
            xml.setTo("OSC[0]");
            if(xml.getName() == "OSC")
            {
                ip = xml.getValue<string>("ip");
                port = xml.getValue<int>("port");
            }


        }
    } else {
        ofLogError() << "Failed to load settings.xml";
    }

    clientDestination = ip;
    clientSendPort = port;
    clientSender.setup(clientDestination, clientSendPort);
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.child << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

    for(unsigned int i=0; i<components.size(); i++) components[i]->update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	//Display some information about the client on the screen with the font you loaded

    string debug = "Sending messages to " + string(clientDestination) + ":"+ ofToString(clientSendPort);
    string instructions = "Type to create a new message.\nHit ENTER to send!";

    ofSetColor(255,0,154);
    curlyFont.drawString("The Garden of Earthly Delights", 10, 50);

    ofSetColor(0);
    font.drawString(debug, 10, 75);
    titleFont.drawString(instructions, 10, 300);

	// what have we typed so far?
    font.drawString(clientTyping, 10, 400);

    for(int i=0; i<components.size(); i++) components[i]->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // hit Return, time to send the osc message
    if(key == OF_KEY_RETURN){
        // to send a string, create an ofxOscMessage object, give it an address
        // and add a string argument to the object
        ofxOscMessage m;
        m.setAddress("/entry");
        ofxDatGuiDropdownOption* o = dropdown->getSelected();
        int type = o->getIndex();
        m.addInt32Arg(type);
        clientTyping.erase(std::remove(clientTyping.begin(), clientTyping.end(), '\0'), clientTyping.end());
        m.addStringArg(clientTyping);
        ofLogNotice() << "Send message - type: " << type << " text: " << clientTyping;
        clientSender.sendMessage(m);

        // clear out "typing"
        clientTyping = "";
        clientTyping.clear();
        bDoSendMessage = false;
        return;
    }

    if(key != OF_KEY_BACKSPACE){
        if( (ispunct(key)) || (isalnum(key)) || (isspace(key)) ) {
            clientTyping += key;
        }
    }
    else{
        if(clientTyping.size() > 0){
            clientTyping.erase(clientTyping.end() - 1);
        }
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
