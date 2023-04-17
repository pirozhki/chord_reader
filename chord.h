/*
	Coded by Pirozhki
	Last Modified:2023/04/17
	�R�[�h�����R�[�h�f�[�^�ɕϊ�����N���X
*/

#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <vector>

#define aug5 m6
#define dim7 M6

using namespace std;

enum Root{
	C, CS, D, DS, E, F, FS, G, GS, A, AS, B
};

enum Constituent{
	root, m2, M2, m3, M3, pf4, dim5, pf5, m6, M6, m7, M7,
	pf8, m9, M9, aug9, m10, pf11, aug11, pf12, m13, M13, m14, M14,
};

// �R�[�h��\���\���́B�R�[�h����ށA���[�g�A�x�[�X�ɕ����ĕێ�����
struct ChordData
{
	ChordData(): notes(0), root(0), bass(0){}
	~ChordData(){};

    bitset<24>		notes;			// �R�[�h�̎��(�\�����̊Ԋu)��\���r�b�g��B�f�[�^�̐擪���珇��root, m2, ... , M14�����蓖�Ă��`
    unsigned char	root;			// ���[�g�� (0��C, 1��C#...)
    unsigned char	bass;			// �x�[�X�� (0��C, 1��C#...)
};

class ChordManager
{
public:
	ChordManager(){}
    ~ChordManager(){}
	
    ChordData			AddChord(string &chord_name);			// �R�[�h���ŃR�[�h��ǉ�
	void				AddChords(vector<string> &chord_names) throw(const char*);	// �R�[�h���܂Ƃ߂Ēǉ�
	vector<ChordData>	GetChords(){return m_chords;}			// �R�[�h�f�[�^���擾
    unsigned int		EstimateKey();							// �ێ����Ă���R�[�h����L�[�𐄒�
    void				Print();								// �R�[�h����\��
	void				Clear(){m_chords.clear();}				// �ێ����Ă���R�[�h��S�č폜
	
	static bitset<12>	GetChordNotes(ChordData &chord_data);	// �R�[�h�̍\�������r�b�g��Ŏ擾�BC(0),D(1)...B(11)
	static string		GetChordName(ChordData &chord_data);	// �R�[�h�f�[�^���R�[�h���ɕϊ�
	static string		GetNoteLetter(unsigned int note);		// �x�����m�[�g���ɕϊ�(0���h, 1����...)
private:
    vector<ChordData>	m_chords;
};
