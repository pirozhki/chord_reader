/*
Coded by Pirozhki
Last Modified:2023/04/17
*/

#include "chord.h"

void ChordManager::AddChords(vector<string> &chord_names){
	for(auto itr = chord_names.begin(); itr<chord_names.end(); itr++){
		try{
			m_chords.push_back(AddChord(*itr));
		}
		catch (const char* e){}
	}
}

ChordData ChordManager::AddChord(string &chord_name) throw(const char*) {
	ChordData chord_data;
	string::iterator itr = chord_name.begin();

	// ���[�g�ʒu������
	switch(*itr) {
	case 'C':
		chord_data.root = C;
		break;
	case 'D':
		chord_data.root = D;
		break;
	case 'E':
		chord_data.root = E;
		break;
	case 'F':
		chord_data.root = F;
		break;
	case 'G':
		chord_data.root = G;
		break;
	case 'A':
		chord_data.root = A;
		break;
	case 'B':
		chord_data.root = B;
		break;
	default:
		if(chord_name.find("N.C")!=string::npos || chord_name.find("NC")!=string::npos) {
			chord_data.notes	= 0;
			chord_data.root	= 0;
			chord_data.bass		= 0;
			return chord_data;
		};
		throw "invalid chord";
	}
	itr++;
	if(itr!=chord_name.end()){
		if(*itr=='b') {
			chord_data.root==0 ? chord_data.root=11 : chord_data.root--;
		}
		if(*itr=='#') {
			chord_data.root==11 ? chord_data.root=0 : chord_data.root++;
		}
	}

	// �f�[�^�̐擪�͕K��root
	chord_data.notes.set(root, 1);

	// 3�x/4�x������
	if(chord_name.find("m")!=string::npos && chord_name.find("maj")==string::npos && chord_name.find("dim")==string::npos && chord_name.find("omit")==string::npos) {
		chord_data.notes.set(m3, 1);
	} else if(chord_name.find("sus4")!=string::npos) {
		chord_data.notes.set(pf4, 1);
	} else {
		chord_data.notes.set(M3, 1);
	}

	// 5�x������
	if(chord_name.find("b5")!=string::npos || chord_name.find("-5")!=string::npos || chord_name.find("dim")!=string::npos) {
		chord_data.notes.set(dim5, 1);
	} else if(chord_name.find("#5")!=string::npos || chord_name.find("+5")!=string::npos || chord_name.find("aug")!=string::npos) {
		chord_data.notes.set(aug5, 1);
	} else {
		chord_data.notes.set(pf5, 1);
	}

	// 6�x������
	if(chord_name.find("6")!=string::npos) {
		chord_data.notes.set(M6, 1);
	}

	// 7�x������
	if(chord_name.find("dim")!=string::npos) {
		chord_data.notes.set(M6, 1);
	} else if(chord_name.find("M7")!=string::npos || chord_name.find("maj7")!=string::npos || chord_name.find("Maj7")!=string::npos) {
		chord_data.notes.set(M7, 1);
	} else if(chord_name.find("7")!=string::npos) {
		chord_data.notes.set(m7, 1);
	}

	// 9�x������
	if(chord_name.find("b9")!=string::npos || chord_name.find("-9")!=string::npos) {
		chord_data.notes.set(m7, 1);
		chord_data.notes.set(m9, 1);
	} else if(chord_name.find("#9")!=string::npos || chord_name.find("+9")!=string::npos) {
		chord_data.notes.set(m7, 1);
		chord_data.notes.set(aug9, 1);
	} else if(chord_name.find("add9")!=string::npos) {
		chord_data.notes.set(M9, 1);
	} else if(chord_name.find("9")!=string::npos) {
		chord_data.notes.set(M9, 1);
		if(!chord_data.notes[M7] & !chord_data.notes[M6])chord_data.notes.set(m7, 1);
	}

	// 11�x������
	if(chord_name.find("#11")!=string::npos|| chord_name.find("+11")!=string::npos) {
		if(!chord_data.notes[M7] & !chord_data.notes[M6])chord_data.notes.set(m7, 1);
		chord_data.notes.set(aug11, 1);
	} else if(chord_name.find("11")!=string::npos) {
		if(!chord_data.notes[M7] & !chord_data.notes[M6])chord_data.notes.set(m7, 1);
		chord_data.notes.set(pf11, 1);
	}

	// 13�x������
	if(chord_name.find("b13")!=string::npos || chord_name.find("-13")!=string::npos) {
		chord_data.notes.set(m7, 1);
		chord_data.notes.set(m13, 1);
	} else if(chord_name.find("13")!=string::npos) {
		if(!chord_data.notes[M7])chord_data.notes.set(m7, 1);
		chord_data.notes.set(M13, 1);
	}

	// 5�x�����O
	if(chord_name.find("omit5")!=string::npos) {
		chord_data.notes.set(dim5, 0);
		chord_data.notes.set(pf5, 0);
		chord_data.notes.set(aug5, 0);
	}

	// 3�x�����O
	if(chord_name.find("omit3")!=string::npos) {
		chord_data.notes.set(m3, 0);
		chord_data.notes.set(M3, 0);
	}

	// �x�[�X��������
	itr = chord_name.end();
	if(chord_name.find("on")!=string::npos){
		chord_name.replace(chord_name.find("on"), 2, "/");
	}
	if(chord_name.find("/")!=string::npos){
		itr = chord_name.begin()+chord_name.find("/")+1;
	}
	if(itr != chord_name.end()) {	// �I���R�[�h�̏ꍇ
		switch(*itr) {
		case 'C':
			chord_data.bass = C;
			break;
		case 'D':
			chord_data.bass = D;
			break;
		case 'E':
			chord_data.bass = E;
			break;
		case 'F':
			chord_data.bass = F;
			break;
		case 'G':
			chord_data.bass = G;
			break;
		case 'A':
			chord_data.bass = A;
			break;
		case 'B':
			chord_data.bass = B;
			break;
		default:
			chord_data.bass = chord_data.root;
			break;
		}
		itr++;
		if(itr!=chord_name.end()){
			if(*itr=='b') {
				if(chord_data.bass==C)chord_data.bass=B;
				else chord_data.bass--;
			}
			if(*itr=='#') {
				if(chord_data.bass==B)chord_data.bass=C;
				else chord_data.bass++;
			}
		}
	} else {	// �I���R�[�h�łȂ��ꍇ
		chord_data.bass = chord_data.root;
	}

	m_chords.push_back(chord_data);

	return chord_data;
}

string ChordManager::GetChordName(ChordData &chord_data){
	bitset<24> notes = chord_data.notes;
	string chord_name;

	chord_name += GetNoteLetter(chord_data.root);

	// �R�[�h���ɏ��������Ă���
	bool tension = false;
	// 6th�̏ꍇ��b5�̏ꍇ��m��t����Bdim5��dim7�ǂ��������ꍇ����dim7�Ȃ̂�m�͗v��Ȃ�
	if(notes[m3] & !(notes[dim5] & notes[dim7]))chord_name += "m";
	if(notes[m3] & notes[dim5] & notes[dim7])chord_name += "dim";
	if(notes[aug5])chord_name += "aug";
	if(notes[M6] & !notes[dim5])chord_name += "6";
	if(notes[m7])chord_name += "7";
	if(notes[M7])chord_name += "M7";
	if(notes[pf4])chord_name += "sus4";
	if((!notes[dim7] & !notes[m7] & !notes[M7]) & notes[M9])chord_name += "add9";
	if((notes[dim5] & !notes[dim7]) | notes[m9] | (bool)((notes[dim7] | notes[m7] | notes[M7]) & notes[M9]) | notes[pf11] | notes[aug11] | notes[m13] | notes[M13])chord_name += "(";
	if(notes[dim5] & !notes[dim7]) {
		chord_name += "b5";
		tension = true;
	}
	if(tension & (notes[m9] | ((notes[dim7] | notes[m7] | notes[M7]) & notes[M9])))chord_name += ",";
	if(notes[m9]) {
		chord_name += "b9";
		tension = true;
	}
	if((notes[dim7] | notes[m7] | notes[M7]) & notes[M9]) {
		chord_name += "9";
		tension = true;
	}
	if(tension & (notes[pf11] | notes[aug11]))chord_name+=",";
	if(notes[pf11]) {
		chord_name += "11";
		tension = true;
	}
	if(notes[aug11]) {
		chord_name += "#11";
		tension = true;
	}
	if(tension & (notes[m13] | notes[M13]))chord_name += ",";
	if(notes[m13])chord_name += "b13";
	if(notes[M13])chord_name += "13";
	if((notes[dim5] & !notes[dim7]) | notes[m9] | (bool)((notes[dim7] | notes[m7] | notes[M7]) & notes[M9]) | notes[pf11] | notes[aug11] | notes[m13] | notes[M13])chord_name += ")";
	if(!notes[m3] & !notes[M3] & !notes[pf4])chord_name += "omit3";
	if(!notes[dim5] & !notes[pf5] & !notes[aug5])chord_name += "omit5";

	if(chord_data.root != chord_data.bass) {
		chord_name += "/";
		chord_name += GetNoteLetter(chord_data.bass);
	}

	return chord_name;
}

bitset<12> ChordManager::GetChordNotes(ChordData &chord_data){
	bitset<36> notes = chord_data.notes.to_ulong() << chord_data.root;
	notes |= notes>>24;	// 3�I�N�^�[�u�ڂ̉���1�I�N�^�[�u�ڂɂ����Ă���
	notes &= 0xFFFFFF;
	notes |= notes>>12;	// 2�I�N�^�[�u�ڂ̉���1�I�N�^�[�u�ڂɂ����Ă���
	notes &= 0xFFF;
	return notes.to_ulong();
}

unsigned int ChordManager::EstimateKey() {
	unsigned int key;
	int note_count[12] = {0};

	/*
	�R�[�h�\�����ƃ��W���[�X�P�[�����璲(�L�[)�𐄒肷��
	�������}�C�i�[�X�P�[���͕��s���̃��W���[�X�P�[���Ƃ݂Ȃ��A�]���͍l�����Ȃ�
	*/
	for(unsigned int i=0; i<m_chords.size(); i++) {
		bitset<12> notes = GetChordNotes(m_chords[i]);
		for(int j=0; j<12; j++) {
			if(notes[j]) {
				note_count[j]++;
			}
		}
	}

	int sum[12] = {0};
	// �e�L�[�Ń_�C�A�g�j�b�N�X�P�[����̉��𑫂����킹�A�X�P�[���O�̉����}�C�i�X����
	for(int i=0; i<12; i++) {
		sum[i] += note_count[i];
		sum[i] -= note_count[(i+m2)%12];
		sum[i] += note_count[(i+M2)%12];
		sum[i] -= note_count[(i+m3)%12];
		sum[i] += note_count[(i+M3)%12];
		sum[i] += note_count[(i+pf4)%12];
		sum[i] -= note_count[(i+dim5)%12];
		sum[i] += note_count[(i+pf5)%12];
		sum[i] -= note_count[(i+m6)%12];	// SDM, Dominant7th in harmonic minor
		sum[i] += note_count[(i+M6)%12];
		sum[i] -= note_count[(i+m7)%12];
		sum[i] += note_count[(i+M7)%12];
	}

	// �_�C�A�g�j�b�N��̉������ő�ɂȂ����Ƃ��̃L�[�����̋Ȃ̃L�[
	int sum_max = INT_MIN;
	for(int i=0; i<12; i++) {
		if(sum_max < sum[i]) {
			key = i;
			sum_max = sum[i];
		}
	}
	//cout << "key=" << key << "\n";
	return key;
}

void ChordManager::Print() {
	for(ChordData& chord : m_chords){
		cout << GetChordName(chord) << endl;
	}
	cout << endl;
}

string ChordManager::GetNoteLetter(unsigned int note){
	switch(note%12){
	case C:		return "C";
	case CS:	return "C#";
	case D:		return "D";
	case DS:	return "D#";
	case E:		return "E";
	case F:		return "F";
	case FS:	return "F#";
	case G:		return "G";
	case GS:	return "G#";
	case A:		return "A";
	case AS:	return "A#";
	case B:		return "B";
	default:	throw;
	}
}