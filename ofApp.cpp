#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");
	
	ofBackground(0);
	ofSetColor(255);
	ofNoFill();
	ofSetCircleResolution(72);

	this->random_seed = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(this->random_seed);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofPushMatrix();
	ofTranslate(ofGetWindowSize() * 0.5);

	vector<ofColor> color_palette;
	color_palette.push_back(ofColor(255, 0, 0));
	color_palette.push_back(ofColor(0, 255, 0));
	color_palette.push_back(ofColor(0, 0, 255));
	color_palette.push_back(ofColor(255, 255, 0));
	color_palette.push_back(ofColor(255, 0, 255));
	color_palette.push_back(ofColor(0, 255, 255));

	auto number_of_sphere = 150;
	vector<glm::vec2> location_list;
	vector<float> radius_list;

	while (location_list.size() < number_of_sphere) {

		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		auto radius = ofRandom(8, 70);
		bool flag = true;
		for (int i = 0; i < location_list.size(); i++) {

			if (glm::distance(location, location_list[i]) < (radius + radius_list[i])) {

				flag = false;
				break;
			}
		}

		if (flag) {

			location_list.push_back(location);
			radius_list.push_back(radius);
		}
	}

	int count = 0;
	while (true) {

		auto all = true;

		for (int i = 0; i < location_list.size(); i++) {

			auto flag = true;
			for (int k = 0; k < location_list.size(); k++) {

				if (i == k) { continue; }

				if (glm::distance(location_list[i], location_list[k]) < (radius_list[i] + radius_list[k])) {

					flag = false;
				}
			}

			if (flag) {

				radius_list[i] += 1;
				all = false;
				break;
			}
		}

		if (all) {

			break;
		}

		count++;
	}

	for (int i = 0; i < location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(location_list[i]);

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		for (int radius = 8; radius <= radius_list[i]; radius += 4) {
		
			auto noise_param = glm::vec3(
				ofNoise(noise_seed.x, ofGetFrameNum() * 0.0025 + radius * 0.0003),
				ofNoise(noise_seed.y, ofGetFrameNum() * 0.0025 + radius * 0.0003),
				ofNoise(noise_seed.z, ofGetFrameNum() * 0.0025 + radius * 0.0003));

			ofRotateZ(noise_param.z < 0.45 ? ofMap(noise_param.z, 0, 0.45, -360, 0) : noise_param.z > 0.65 ? ofMap(noise_param.z, 0.65, 1, 0, 360) : 0);
			ofRotateY(noise_param.y < 0.45 ? ofMap(noise_param.y, 0, 0.45, -360, 0) : noise_param.y > 0.65 ? ofMap(noise_param.y, 0.65, 1, 0, 360) : 0);
			ofRotateX(noise_param.x < 0.45 ? ofMap(noise_param.x, 0, 0.45, -360, 0) : noise_param.x > 0.65 ? ofMap(noise_param.x, 0.65, 1, 0, 360) : 0);

			ofDrawCircle(glm::vec2(), radius);
		}

		ofPopMatrix();
	}

	ofPopMatrix();

}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}