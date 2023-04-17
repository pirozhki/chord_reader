#include <iostream>
#include <fstream>
#include <sstream>

#include "chord.h"

using namespace std;

int main() {
	ifstream ifs;
	ChordManager chord_manager;

	try{
		ifs.open("sample.txt");
	}
	catch (...){
		cout << "can't read a file" << endl;
	}

	// read chords and convert to int32
	string line;
	string s;
	while (getline(ifs, line)) {
		stringstream ss(line);
		while (ss.good()){
			ss >> s;
			try{
				chord_manager.AddChord(s);
			}
			catch (...){}
		}
		vector<ChordData> chords = chord_manager.GetChords();
		int key = chord_manager.EstimateKey();
		for (auto itr = chords.begin(); itr != chords.end(); itr++){
			if (itr->root - key < 0){
				itr->root = itr->root + 12 - key;
			}
			else{
				itr->root -= key;
			}
			if (itr->bass - key < 0){
				itr->bass = itr->bass + 12 - key;
			}
			else{
				itr->bass -= key;
			}
			cout << ChordManager::GetChordName(*itr) << " ";
		}
		cout << endl;
		chord_manager.Clear();
	}
}
