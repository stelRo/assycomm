/**
 * conflib.cpp ---- configuration file parser! 
 * Copyright (c) 2015 Stelmach Ro 
 * 
 * Author: Stelmach Ro (xtasy) <stelmach.ro@gmail.com> , 
 * Credits: Sarmanu for configuration code implementation
 * 
 * This file is part of Assy Comm.
 * 
 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <typeinfo>

using namespace std;

class Convert
{
public:
	        // Convert T, which should be a primitive, to a string.
	template <typename T>
	static string T_to_string(T const &val) 
	{
		ostringstream ostr;
		ostr << val;

		return ostr.str();
	}
		
	template <typename T>
	        // Convert a string to T.  
	static T string_to_T(string const &val) 
	{
		
		istringstream istr(val);
		T returnVal;
		if (!(istr >> returnVal))
			cout << "Configuration file: Not a valid " << (
				string)typeid(T).name() << " received!\n";

		return returnVal;
	}

	static 
	string string_to_T(
		string const &val)
	{
		return val;
	}
};


class ConfigFile
{
private:
	
	map<string,string> contents;
	
	string fName;

	void removeComment(string &line) const
	{
		if (line.find('/') != line.npos)
			line.erase(line.find('/'));
	}

	bool onlyWhitespace(const string &line) const
	{
		return (line.find_first_not_of(' ') == line.npos);
	}
	bool validLine(const string &line) const
	{
		
		string temp = line;
		temp.erase(0, temp.find_first_not_of("\t "));
		if (temp[0] == '=')
			return false;

		for (size_t i = temp.find('=') + 1; i < temp.length(); i++)
			if (temp[i] != ' ')
				return true;

		return false;
	}

	void extractKey(string &key, size_t const &sepPos, const string &line) const
	{
		key = line.substr(0, sepPos);
		if (key.find('\t') != line.npos || key.find(' ') != line.npos)
			key.erase(key.find_first_of("\t "));
	}
	void extractValue(string &value, size_t const &sepPos, const string &line) const
	{
		value = line.substr(sepPos + 1);
		value.erase(0, value.find_first_not_of("\t "));
		value.erase(value.find_last_not_of("\t ") + 1);
	}

	void extractContents(const string &line) 
	{
		
		string temp = line;
		        // Erase leading whitespace from the line.
		temp.erase(0, temp.find_first_not_of("\t "));
		size_t sepPos = temp.find('=');

		
		string key, value;
		extractKey(key, sepPos, temp);
		extractValue(value, sepPos, temp);

		if (!keyExists(key))
			contents.insert(
				pair<
			string, 
			string>(key, value));
		else
			cout << "Configuration File: Can only have unique key names!\n";
	}

	// lineNo = the current line number in the file.
	// line = the current line, with comments removed.
	void parseLine(const string &line, size_t const lineNo)
	{
		if (line.find('=') == line.npos)
			cout << "Configuration File: Couldn't find separator on line: " << Convert::T_to_string(lineNo) << "\n";

		if (!validLine(line))
			cout << "Configuration File: Bad format for line: " << Convert::T_to_string(lineNo) << "\n";

		extractContents(line);
	}

	void ExtractKeys()
	{
		
		ifstream file;
		file.open(fName.c_str());
		if (!file)
			cout << "Configuration File: File " << fName << " couldn't be found!\n";

		
		string line;
		size_t lineNo = 0;
		while (
			getline(file, line))
		{
			lineNo++;
			
			string temp = line;

			if (temp.empty())
				continue;

			removeComment(temp);
			if (onlyWhitespace(temp))
				continue;

			parseLine(temp, lineNo);
		}

		file.close();
	}
public:
	ConfigFile(const string &fName)
	{
		this->fName = fName;
		ExtractKeys();
	}

	bool keyExists(const 
		string &key) const
	{
		return contents.find(key) != contents.end();
	}

	template <typename ValueType>
	ValueType getValueOfKey(const string &key, ValueType const &defaultValue = ValueType()) const
	{
		if (!keyExists(key))
			return defaultValue;

		return Convert::string_to_T<ValueType>(contents.find(key)->second);
	}
};
