#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<glm::vec2> locations;
	for (int i = 0; i < 25; i++) {

		auto location = glm::vec2(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0, ofGetWidth()), 
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0, ofGetHeight()));
		locations.push_back(location);
	}

	auto radius = 20.f;
	for (int i = 0; i < locations.size(); i++) {

		auto min_distance = 100.f;
		for (int k = 0; k < locations.size(); k++) {

			if (i == k) { continue; }

			auto angle_i = std::atan2(locations[k].y - locations[i].y, locations[k].x - locations[i].x);
			auto satellite_point_i = locations[i] + glm::vec2(radius * cos(angle_i), radius * sin(angle_i));
			auto angle_k = std::atan2(locations[i].y - locations[k].y, locations[i].x - locations[k].x);
			auto satellite_point_k = locations[k] + glm::vec2(radius * cos(angle_k), radius * sin(angle_k));
			
			auto distance = glm::distance(satellite_point_i, satellite_point_k);
			if (distance < 100) {
				
				ofSetColor(39, ofMap(distance, 0, 100, 255, 0));
				ofDrawLine(satellite_point_i, satellite_point_k);
				ofDrawCircle(satellite_point_i, radius * 0.3);

				if (distance < min_distance) { min_distance = distance; }
			}
		}

		ofSetColor(39);
		ofNoFill();
		ofDrawCircle(locations[i], radius);

		ofFill();
		ofDrawCircle(locations[i], ofMap(min_distance, 0, 100, radius * 0.7, 0));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}