// project1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

vector<string> loadInstName;
vector<int> loadInstNumber;
vector<string> instFirst;
vector<string> instSecond;
vector<string> instThird;
vector<string> loopName;
vector<string> instName;
vector<int> instLocation;
vector<int> loopLocation;
string first, second, third;

int outcomeChange(string s);
void do2BitHistroy(string s, vector<int> &state, vector<int> &st, vector<int> &outcome, int &count);
int stateLimit(int state);
int returnLoadValue(string str);
bool isExist(string str);
int returnLoop(string str);
//void convertStateAndPrint(int state);
//void convertStAndPrint(vector<int> st);
//void convertPredAndPrint(int pred);
//int stateLimit(int state);
//int state1BitLimit(int state);
//void predSave(int st, vector<int> &pred);
//void differentOrNot(vector<char> &correct, int input, int pred);
//void do2BitHistory2BC(vector<int> input, vector<int> &state, vector<int> &st, vector<int> &pred, vector<char> &correct);
//void do1BitHistory2BC(vector<int> input, vector<int> &state1Bit, vector<int> &st1Bit, vector<int> &pred1Bit, vector<char> &correct1Bit);
//
//void convertStateAndPrint(int state) {
//	if (state == 0) {
//		cout << "00";
//	}
//	else if (state == 1) {
//		cout << "01";
//	}
//	else if (state == 2) {
//		cout << "10";
//	}
//	else if (state == 3) {
//		cout << "11";
//	}
//}
//
//void convert1BitStateAndPrint(int state) {
//	if (state == 0) {
//		cout << "0";
//	}
//	else if (state == 1) {
//		cout << "1";
//	}
//}
//
//void convertStAndPrint(vector<int> st) {
//	for (int i = 0; i < st.size(); i++) {
//		if (st[i] == 0) {
//			cout << "SN";
//			if (i < st.size() - 1)
//				cout << ",";
//		}
//		else if (st[i] == 1) {
//			cout << "WN";
//			if (i < st.size() - 1)
//				cout << ",";
//		}
//		else if (st[i] == 2) {
//			cout << "WT";
//			if (i < st.size() - 1)
//				cout << ",";
//		}
//		else if (st[i] == 3) {
//			cout << "ST";
//			if (i < st.size() - 1)
//				cout << ",";
//		}
//	}
//}
//
//void convertPredAndPrint(int pred) {
//	if (pred == 0) {
//		cout << "N";
//	}
//	else if (pred == 1) {
//		cout << "T";
//	}
//}

struct Entry {
	vector<int> outcome;
	vector<int> state; // 0:00, 1:01, 2:10, 3:11
	vector<int> st; // 0:SN, 1:WN, 2:WT, 3:ST
	int count = 0;
};

int main()
{
	//while (1) {
	//	string s;
	//	cout << "input pattern" << endl;
	//	cin >> s;
	//	vector<int> input;
	//	vector<int> state; // 0:00, 1:01, 2:10, 3:11
	//	state.push_back(0); // initial state
	//	vector<int> st; // 0:SN, 1:WN, 2:WT, 3:ST
	//	for (int i = 0; i < 4; i++)
	//		st.push_back(0); // initial SN,SN,SN,SN
	//	vector<int> pred; // predict 0:N, 1:T
	//	vector<char> correct; // correct or not (O or X)

	//	for (int i = 0; i < s.size(); i++) {
	//		if (s[i] == 'N') {
	//			input.push_back(0);
	//		}
	//		else if (s[i] == 'T') {
	//			input.push_back(1);
	//		}
	//		//cout << input[i];
	//	}
	//	cout << endl;
	//	do2BitHistory2BC(input, state, st, pred, correct);

	//	vector<int> state1Bit; // 0, 1
	//	state1Bit.push_back(0); // initial state
	//	vector<int> st1Bit; // 0:SN, 1:WN, 2:WT, 3:ST
	//	st1Bit.push_back(0); // initial SN,SN
	//	st1Bit.push_back(0);
	//	vector<int> pred1Bit;
	//	vector<char> correct1Bit;
	//	do1BitHistory2BC(input, state1Bit, st1Bit, pred1Bit, correct1Bit);
	//}

	ifstream input;
	vector<string> inputContent;
	string inp;
	input.open("example1.txt", ios::in);
	if (!input) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}

	while (!input.eof()) {
		while (getline(input, inp, '\n')) {
			inputContent.push_back(inp);
		}
	}

	//for (int i = 0; i < inputContent.size(); i++) {
	//	cout << inputContent[i] << endl;
	//}
	//vector<string> loadInstName;
	//vector<int> loadInstNumber;
	//vector<string> instFirst;
	//vector<string> instSecond;
	//vector<string> instThird;
	//vector<string> loopName;
	//vector<string> instName;
	//vector<int> instLocation;
	//vector<int> loopLocation;
	//string first, second, third;
	loadInstName.push_back("R0");
	loadInstNumber.push_back(0);
	/*parser start====================================================================================*/
	for (int i = 0; i < inputContent.size(); i++) {
		for (int j = 0; j < inputContent[i].size(); j++) {
			if (inputContent[i][j] >= 'A'&&inputContent[i][j] <= 'Z') {
				string loop;
				for (int k = j; k < inputContent[i].size(); k++) {
					if (inputContent[i][k] == ':') {
						break;
					}
					loop.push_back(inputContent[i][k]);
				}
				loopName.push_back(loop);
				loopLocation.push_back(i);
				loop.clear();
				break;
			}
			else if (inputContent[i][j] >= 'a'&&inputContent[i][j] <= 'z') {
				string inst;
				int l = 0;
				for (int k = j; k < inputContent[i].size(); k++) {
					if (inputContent[i][k] == ' ') {
						//continue;
						l = ++k;
						break;
					}
					inst.push_back(inputContent[i][k]);
				}
				if (inst == "li") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							l++;
							for (int m = l; m < inputContent[i].size(); m++) {
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							//cout << stoi(second) << endl;
							loadInstNumber.push_back(stoi(second));
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					loadInstName.push_back(first);
					instName.push_back(inst);
					instThird.push_back("no");
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "beq") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "bne") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "add") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "sub") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "subi") {
				for (; l < inputContent[i].size(); l++) {
					if (inputContent[i][l] == ',') {
						for (int m = ++l; m < inputContent[i].size(); m++) {
							if (inputContent[i][m] == ',') {
								for (int n = ++m; n < inputContent[i].size(); n++) {
									third.push_back(inputContent[i][n]);
								}
								instThird.push_back(third);
								third.clear();
								//m = inputContent[i].size();
								break;
							}
							second.push_back(inputContent[i][m]);
						}
						instSecond.push_back(second);
						second.clear();
						//l = inputContent[i].size();
						break;
					}
					first.push_back(inputContent[i][l]);
				}
				instFirst.push_back(first);
				instName.push_back(inst);
				instLocation.push_back(i);
				first.clear();
				}
				else if (inst == "mul") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "addi") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				else if (inst == "andi") {
					for (; l < inputContent[i].size(); l++) {
						if (inputContent[i][l] == ',') {
							for (int m = ++l; m < inputContent[i].size(); m++) {
								if (inputContent[i][m] == ',') {
									for (int n = ++m; n < inputContent[i].size(); n++) {
										third.push_back(inputContent[i][n]);
									}
									instThird.push_back(third);
									third.clear();
									//m = inputContent[i].size();
									break;
								}
								second.push_back(inputContent[i][m]);
							}
							instSecond.push_back(second);
							second.clear();
							//l = inputContent[i].size();
							break;
						}
						first.push_back(inputContent[i][l]);
					}
					instFirst.push_back(first);
					instName.push_back(inst);
					instLocation.push_back(i);
					first.clear();
				}
				//cout << inst << endl;
				inst.clear();
				break;
			}
		}
	}
	/*parser end====================================================================================*/

	//for (int m = 0; m < loadInstName.size(); m++) {
	//	cout << loadInstName[m] <<"*"<< loadInstNumber[m] << endl;
	//}
	//for (int m = 0; m < loopName.size(); m++) {
	//	cout << loopName[m] << " " << loopLocation[m] << endl;
	//}
	//for (int m = 0; m < instFirst.size(); m++) {
	//	cout << instName[m] << " " << instFirst[m] << " " << instSecond[m] << " " << instThird[m] << " " << instLocation[m] << endl;
	//}
	//cout << instName.size() << endl;

	int entries;
	cout << "input entry size" << endl;
	cin >> entries;
	//cout << "input one outcome" << endl;

	vector<Entry> entry;
	for (int i = 0; i < entries; i++) {
		Entry e;
		e.outcome.push_back(0); // initial 0: NT
		e.outcome.push_back(0);
		e.outcome.push_back(0);
		e.state.push_back(0);
		for (int i = 0; i < 4; i++)
			e.st.push_back(0); // initial SN,SN,SN,SN

		entry.push_back(e);
	}

	/*run start====================================================================================*/
	for (int i = 0; i < instName.size(); i++) { // run for loop
		if (instName[i] == "beq") {
			if (returnLoadValue(instFirst[i]) == returnLoadValue(instSecond[i])) {
				//cout << "beq T " << instLocation[i] << endl;
				//cout << returnLoop(instThird[i]) << endl;
				cout << endl << "entry: " << i % entries << "	";
				cout << instName[i] << " " << instFirst[i] << "," << instSecond[i] << "," << instThird[i] << endl;
				do2BitHistroy("T", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
				i = returnLoop(instThird[i]) - 1;
			}
			else {
				//cout << "beq N " << instLocation[i] << endl;
				cout << endl << "entry: " << i % entries << "	";
				cout << instName[i] << " " << instFirst[i] << "," << instSecond[i] << "," << instThird[i] << endl;
				do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
				
			}
		}
		else if (instName[i] == "bne") {
			if (returnLoadValue(instFirst[i]) != returnLoadValue(instSecond[i])) {
				//cout << "bne T " << instLocation[i] << endl;
				//cout << returnLoop(instThird[i]) << endl;
				cout << endl << "entry: " << i % entries << "	";
				cout << instName[i] << " " << instFirst[i] << "," << instSecond[i] << "," << instThird[i] << endl;
				do2BitHistroy("T", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
				i = returnLoop(instThird[i]) - 1;
			}
			else {
				//cout << "bne N " << instLocation[i] << endl;
				cout << endl << "entry: " << i % entries << "	";
				cout << instName[i] << " " << instFirst[i] << "," << instSecond[i] << "," << instThird[i] << endl;
				do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			}
		}
		else if (instName[i] == "andi") {
			//cout << "andi N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int andi = 0;
			int d = stoi(instThird[i]) + 1;
			andi = returnLoadValue(instSecond[i]) % d;
			//cout << instFirst[i] << " " << andi << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = andi;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(andi);
			}
		}
		else if (instName[i] == "add") {
			//cout << "add N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int add = 0;
			add = returnLoadValue(instSecond[i]) + returnLoadValue(instThird[i]);
			//cout << instFirst[i] << " " << add << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = add;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(add);
			}
		}
		else if (instName[i] == "sub") {
			//cout << "sub N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int sub = 0;
			sub = returnLoadValue(instSecond[i]) - returnLoadValue(instThird[i]);
			//cout << instFirst[i] << " " << sub << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = sub;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(sub);
			}
		}
		else if (instName[i] == "mul") {
			//cout << "mul N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int mul = 0;
			mul = returnLoadValue(instSecond[i]) * returnLoadValue(instThird[i]);
			//cout << instFirst[i] << " " << mul << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = mul;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(mul);
			}
		}
		else if (instName[i] == "addi") {
			//cout << "addi N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int addi = 0;
			addi = returnLoadValue(instSecond[i]) + stoi(instThird[i]);
			//cout << instFirst[i] << " " << addi << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = addi;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(addi);
			}
		}
		else if (instName[i] == "subi") {
			//cout << "subi N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			int subi = 0;
			subi = returnLoadValue(instSecond[i]) - stoi(instThird[i]);
			//cout << instFirst[i] << " " << subi << endl;
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = subi;
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(subi);
			}
		}
		else if (instName[i] == "li") {
			//cout << "li N " << instLocation[i] << endl;
			//cout << "entry: " << i % entries << " ";
			//do2BitHistroy("N", entry[i%entries].state, entry[i%entries].st, entry[i%entries].outcome, entry[i%entries].count);
			if (isExist(instFirst[i])) {
				for (int j = 0; j < loadInstName.size(); j++) {
					if (loadInstName[j] == instFirst[i]) {
						loadInstNumber[j] = stoi(instSecond[i]);
					}
				}
			}
			else { // not exist
				loadInstName.push_back(instFirst[i]);
				loadInstNumber.push_back(stoi(instSecond[i]));
			}
		}
	}
	cout << endl;
	/*run end====================================================================================*/

	//entries = 0;
	//while (1) {
	//	string s;
	//	cin >> s;
	//	do2BitHistroy(s, entry[0].state, entry[0].st, entry[0].outcome, entry[0].count);
	//	if (entries == 0) {
	//		do2BitHistroy(s, entry[0].state, entry[0].st, entry[0].outcome, entry[0].count);
	//		entries = 1;
	//	}
	//	else if (entries == 1) {
	//		do2BitHistroy(s, entry[1].state, entry[1].st, entry[1].outcome, entry[1].count);
	//		entries = 0;
	//	}
	//}
	system("pause");
}

int returnLoop(string str) {  // input loopName, return inst location
	for (int i = 0; i < loopName.size(); i++) {
		if (loopName[i] == str) {
			if (loopLocation[i] + 1 > instLocation[instLocation.size() - 1]) { // final step
				return instName.size();
			}
			for (int j = 0; j < instName.size(); j++) {
				if (instLocation[j] == (loopLocation[i] + 1)) {
					return j;
				}
			}
		}
	}
}

bool isExist(string str) {
	for (int i = 0; i < loadInstName.size(); i++) {
		if (loadInstName[i] == str) {
			return true;
		}
		else if (loadInstName[i] != str && i == loadInstName.size() - 1) {
			return false;
		}
	}
	//return false;
}

int returnLoadValue(string str) {
	for (int i = 0; i < loadInstName.size(); i++) {
		if (loadInstName[i] == str) {
			return loadInstNumber[i];
		}
	}
	return -1;
}

int outcomeChange(string s) {
	if (s == "T")
		return 1;
	if (s == "N")
		return 0;
}

int returnStateNumber(vector<int> outcome) {
	if (outcome[0] == 0)
	{
		if (outcome[1] == 0) {
			return 0;
		}
		else if (outcome[1] == 1) {
			return 1;
		}
	}
	else if (outcome[0] == 1) {
		if (outcome[1] == 0) {
			return 2;
		}
		else if (outcome[1] == 1) {
			return 3;
		}
	}
}

void printState(int state) {
	if (state == 0) {
		cout << "(00";
	}
	else if (state == 1) {
		cout << "(01";
	}
	else if (state == 2) {
		cout << "(10";
	}
	else if (state == 3) {
		cout << "(11";
	}
}

int returnPrediction(int st) {
	if (st == 0 || st == 1) {
		return 0;
	}
	else if (st == 2 || st == 3) {
		return 1;
	}
}

string printPreAndOut(int n) {
	if (n == 0) {
		return "N";
	}
	else if (n == 1) {
		return "T";
	}
}

string printSt(int st) {
	if (st == 0) {
		return "SN";
	}
	else if (st == 1) {
		return "WN";
	}
	else if (st == 2) {
		return "WT";
	}
	else if (st == 3) {
		return "ST";
	}
}

void do2BitHistroy(string s, vector<int> &state, vector<int> &st, vector<int> &outcome, int &count) {
	outcome[2] = outcomeChange(s);
	printState(returnStateNumber(outcome));
	for (int i = 0; i < st.size(); i++) {
		cout << ", " << printSt(st[i]);
	}
	cout << ") " << printPreAndOut(returnPrediction(st[returnStateNumber(outcome)])) << " " << printPreAndOut(outcome[2]);
	if (returnPrediction(st[returnStateNumber(outcome)]) != outcome[2])
		count++;
	cout << "		misprediction: " << count << endl;

	if (outcome[2] == 0) {
		st[returnStateNumber(outcome)] = stateLimit(--st[returnStateNumber(outcome)]);
	}
	else if (outcome[2] == 1) {
		st[returnStateNumber(outcome)] = stateLimit(++st[returnStateNumber(outcome)]);
	}

	for (int i = 0; i < outcome.size() - 1; i++) {
		outcome[i] = outcome[i + 1];
	}
}

int stateLimit(int state) {
	if (state > 3)
		state = 3;
	if (state < 0)
		state = 0;
	return state;
}

//int state1BitLimit(int state) {
//	if (state > 1)
//		state = 1;
//	if (state < 0)
//		state = 0;
//	return state;
//}

//void predSave(int st, vector<int> &pred) {
//	if (st == 0 || st == 1) {
//		pred.push_back(0);
//	}
//	else if (st == 2 || st == 3) {
//		pred.push_back(1);
//	}
//}
//
//void differentOrNot(vector<char> &correct, int input, int pred) {
//	if (input == pred) {
//		correct.push_back('O');
//	}
//	else if (input != pred) {
//		correct.push_back('X');
//	}
//}
//
//void do2BitHistory2BC(vector<int> input, vector<int> &state, vector<int> &st, vector<int> &pred, vector<char> &correct) {
//	// print
//	convertStateAndPrint(state[0]);
//	cout << " ";
//	convertStAndPrint(st);
//	cout << "  ";
//	int stateSave = state[0]; // stateSave == 0 (00)
//	predSave(st[stateSave], pred);
//	convertPredAndPrint(pred[0]);
//	cout << "  ";
//	convertPredAndPrint(input[0]);
//	differentOrNot(correct, input[0], pred[0]);
//	cout << "  " << correct[0];
//	cout << endl;
//
//	for (int i = 1; i < input.size(); i++) {
//		if (input[i-1]) { // T
//			st[stateSave]++;
//			st[stateSave] = stateLimit(st[stateSave]);
//			stateSave++;
//			state.push_back(stateLimit(stateSave));
//		}
//		else { // N
//			st[stateSave]--;
//			st[stateSave] = stateLimit(st[stateSave]);
//			stateSave--;
//			state.push_back(stateLimit(stateSave));
//		}
//
//		// print
//		convertStateAndPrint(state[i]);
//		cout << " ";
//		convertStAndPrint(st);
//		cout << "  ";
//		stateSave = state[i];
//		predSave(st[stateSave], pred);
//		convertPredAndPrint(pred[i]);
//		cout << "  ";
//		convertPredAndPrint(input[i]);
//		differentOrNot(correct, input[i], pred[i]);
//		cout << "  " << correct[i];
//		cout << endl;
//	}
//
//	// miss calculation
//	int miss = 0;
//	for (int i = 0; i < correct.size(); i++) {
//		if (correct[i] == 'X') {
//			miss++;
//		}
//	}
//	cout << "2-bit history missprediction: " << miss << endl;
//	cout << "===========================" << endl << endl;
//}
//
//void do1BitHistory2BC(vector<int> input, vector<int> &state1Bit, vector<int> &st1Bit, vector<int> &pred1Bit, vector<char> &correct1Bit) {
//	// print
//	convert1BitStateAndPrint(state1Bit[0]);
//	cout << " ";
//	convertStAndPrint(st1Bit);
//	cout << "  ";
//	int stateSave = state1Bit[0]; // stateSave == 0 (00)
//	predSave(st1Bit[stateSave], pred1Bit);
//	convertPredAndPrint(pred1Bit[0]);
//	cout << "  ";
//	convertPredAndPrint(input[0]);
//	differentOrNot(correct1Bit, input[0], pred1Bit[0]);
//	cout << "  " << correct1Bit[0];
//	cout << endl;
//
//	for (int i = 1; i < input.size(); i++) {
//		if (input[i - 1]) { // T
//			st1Bit[stateSave]++;
//			st1Bit[stateSave] = stateLimit(st1Bit[stateSave]);
//			stateSave++;
//			state1Bit.push_back(state1BitLimit(stateSave));
//		}
//		else { // N
//			st1Bit[stateSave]--;
//			st1Bit[stateSave] = stateLimit(st1Bit[stateSave]);
//			stateSave--;
//			state1Bit.push_back(state1BitLimit(stateSave));
//		}
//
//		// print
//		convert1BitStateAndPrint(state1Bit[i]);
//		cout << " ";
//		convertStAndPrint(st1Bit);
//		cout << "  ";
//		stateSave = state1Bit[i];
//		predSave(st1Bit[stateSave], pred1Bit);
//		convertPredAndPrint(pred1Bit[i]);
//		cout << "  ";
//		convertPredAndPrint(input[i]);
//		differentOrNot(correct1Bit, input[i], pred1Bit[i]);
//		cout << "  " << correct1Bit[i];
//		cout << endl;
//	}
//
//	int miss = 0;
//	for (int i = 0; i < correct1Bit.size(); i++) {
//		if (correct1Bit[i] == 'X') {
//			miss++;
//		}
//	}
//	cout << "1-bit history missprediction: " << miss << endl;
//	cout << "===========================" << endl << endl;
//}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的秘訣: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
