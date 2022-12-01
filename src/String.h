#pragma once

#include "List.h"

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

std::ostream & operator<< (std::ostream &, String const&);

// opposite of the split function
template<>
template<>
String List<String>::join(char);

template<>
String List<String>::join();

template <>
class std::hash<String> {
public:
	std::size_t operator() (String const&) const;
};