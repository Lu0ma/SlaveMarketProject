#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string GetLineByIndex(const int _index, const string& _path);
string GetLineByText(const string& _text, const string& _path);
string GetStringAfterSymbol(const string& _text, const string& _symbol);
string GetStringAfterIndex(const string& _text, const int _index);
void ReadAllFile(const string& _path, vector<string>& _array);
bool ContainsText(const string& _text, const string& _word);