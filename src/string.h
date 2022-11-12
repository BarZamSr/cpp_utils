#pragma once

#include "list.h"

class String: public List<char> {
	String(int);
public:
	String();
	String(char const*);
	String(char const*, int);
	String(List<char>);
	String(std::string);
	
	List<String> split(char);
};

bool operator== (String const&, String const&);
// bool operator!= (String const&, String const&);

String operator+ (String const&, String const&);

// opposite of the split function
template<>
template<>
String List<String>::join(char);