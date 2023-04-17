/*
	Coded by Pirozhki
	Last Modified:2023/04/17
	コード名をコードデータに変換するクラス
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

// コードを表す構造体。コードを種類、ルート、ベースに分けて保持する
struct ChordData
{
	ChordData(): notes(0), root(0), bass(0){}
	~ChordData(){};

    bitset<24>		notes;			// コードの種類(構成音の間隔)を表すビット列。データの先頭から順にroot, m2, ... , M14を割り当てた形
    unsigned char	root;			// ルート音 (0→C, 1→C#...)
    unsigned char	bass;			// ベース音 (0→C, 1→C#...)
};

class ChordManager
{
public:
	ChordManager(){}
    ~ChordManager(){}
	
    ChordData			AddChord(string &chord_name);			// コード名でコードを追加
	void				AddChords(vector<string> &chord_names) throw(const char*);	// コードをまとめて追加
	vector<ChordData>	GetChords(){return m_chords;}			// コードデータを取得
    unsigned int		EstimateKey();							// 保持しているコードからキーを推定
    void				Print();								// コード名を表示
	void				Clear(){m_chords.clear();}				// 保持しているコードを全て削除
	
	static bitset<12>	GetChordNotes(ChordData &chord_data);	// コードの構成音をビット列で取得。C(0),D(1)...B(11)
	static string		GetChordName(ChordData &chord_data);	// コードデータをコード名に変換
	static string		GetNoteLetter(unsigned int note);		// 度数をノート名に変換(0→ド, 1→レ...)
private:
    vector<ChordData>	m_chords;
};
