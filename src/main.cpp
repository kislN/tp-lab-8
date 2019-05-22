#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <iterator>

using namespace std;

const int NPREF = 2; // êîëè÷åñòâî ñëîâ â ïðåôèêñå
const int MAXGEN = 1000; //îáúåì íà âûõîäå
typedef deque<string> prefix;          // î÷åðåäü ïðåôèêñîâ

int main() {
  
    int n;
    prefix pref;
    vector<string> vec;
    map<prefix, vector<string> > statetab; // ïðåôèêñ-ñóôôèêñû
    string st;
    vector<string> p;
    ifstream fin("input.txt");

    if (fin.is_open()) {
        for (int i = 0; i < NPREF; i++) {
            fin >> st;
            p.push_back(st);
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

    for (int i = 0; i < NPREF; i++) {
        pref.push_back(p[i]);
    }

    ofstream out("output.txt");
    srand(time(0));
    out << pref[0] << " " << pref[1];
    for (int i = 0; i < MAXGEN - 2; i++) {
        if (statetab.count(pref)) {
            n = rand() % statetab[pref].size();
            out << statetab[pref][n] << " ";
            if((i + 1) % 10 == 0) out << endl;
            pref.push_back(statetab[pref][n]);
            pref.pop_front();

        }
        else break;
    }
    out.close();

    return 0;

}
