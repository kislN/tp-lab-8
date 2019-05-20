#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <iterator>

using namespace std;

const int NPREF = 2; // ���������� ���� � ��������
const int MAXGEN = 1000; //����� �� ������
typedef deque<string> prefix;          // ������� ���������

int main() {
	setlocale(LC_ALL, "RUS");
	int n;
	prefix pref;
	vector<string> vec;
	map<prefix, vector<string> > statetab; // �������-��������
	string st;
	ifstream fin("input.txt");
	if (fin) {
		for (int i = 0; i < NPREF; i++) {
			fin >> st;
			pref.push_back(st);
		}
		while (fin >> st) {
			if (statetab.count(pref) == 0) {
				vec.push_back(st);
				statetab.insert(pair<prefix, vector<string>>(pref, vec));
				vec.clear();
			}
			else {
				statetab[pref].push_back(st);
			}
			pref.pop_front();
			pref.push_back(st);
		}
	}
	else {
		cout << "File is not found" << endl;
	}
	fin.close();
	pref.clear();

	ifstream f("input.txt");
	for (int i = 0; i < NPREF; i++) {
		f >> st;
		pref.push_back(st);
	}
	f.close();

	ofstream out("output.txt");
	srand(time(0));
	out << pref[0] << " " << pref[1];
	for (int i = 0; i < MAXGEN - 2; i++) {
		if (statetab.count(pref)) {
			n = rand() % statetab[pref].size();
			out << statetab[pref][n] << " ";
			pref.push_back(statetab[pref][n]);
			pref.pop_front();
		}
		else break;
	}
	out.close();


	system("pause");
	return 0;


}