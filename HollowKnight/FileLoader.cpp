#include "FileLoader.h"

string GetLineByIndex(const int _index, const string& _path)
{
	ifstream _stream = ifstream(_path);

	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return string();
	}

	string _line;
	int _lineIndex = 0;

	while (getline(_stream, _line))
	{
		if (_lineIndex == _index) return _line;
		_lineIndex++;
	}
	_lineIndex++;
	return _line;
}

string GetLineByText(const string& _text, const string& _path)
{
	ifstream _stream = ifstream(_path);

	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return string();
	}

	string _line;

	while (getline(_stream, _line))
	{
		if (ContainsText(_line, _text))
		{
			return _line;
		}
	}

	return string();
}

int GetIndexByText(const string& _text, const string& _path)
{
	ifstream _stream = ifstream(_path);

	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return int();
	}

	string _line;
	int _index = 0;

	while (getline(_stream, _line))
	{
		if (ContainsText(_line, _text))
		{
			return _index;
		}
		_index++;
	}

	return -1;
}

string GetWordByIndex(int _index, const string& _path, const string& _symbol)
{
	ifstream _stream = ifstream(_path);

	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return string();
	}

	string _word;

	while (_stream >> _word)
	{
		if (_word != _symbol)
		{
			_index++;
		}
		else return _word;
	}

	return string();
}

string GetStringAfterSymbol(const string& _text, const string& _symbol)
{
	const int _textSize = static_cast<int>(_text.size());
	const int _symbolSize = static_cast<int>(_symbol.size());

	int _index = 0;

	for (int _charIndex = 0; _charIndex < _textSize; _charIndex++)
	{
		const char _char = _text[_charIndex];

		if (_char == _symbol[_index])
		{
			_index++;
			if (_index >= _symbolSize)
			{
				return GetStringAfterIndex(_text, _charIndex + 1);
			}

			continue;
		}

		_index = 0;
	}

	return string();
}

string GetStringAfterIndex(const string& _text, const int _index)
{
	string _string = string();

	const int _textSize = (int)_text.size();
	for (int _charIndex = _index; _charIndex < _textSize; _charIndex++)
	{
		_string.push_back(_text[_charIndex]);
	}

	return _string;
}

void Save(const string& _text, const string& _path)
{
	ofstream _stream = ofstream(_path);
	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return;
	}
	_stream << _text;
}

void ReadAllFile(const string& _path, vector<string>& _array)
{
	ifstream _stream = ifstream(_path);
	if (!_stream)
	{
		cerr << "Le flux n'a pas été correctement construit !" << endl;
		return;
	}

	string _line;
	while (getline(_stream, _line))
	{
		_array.push_back(_line);
	}
}

bool ContainsText(const string& _text, const string& _word)
{
	return _text.find(_word) != string::npos;
}