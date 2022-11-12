#include <cstring>

#include "string.h"



String::String(): List<char>() {}

String::String(char const* c_str): List<char>(c_str, strlen(c_str)) {}

String::String(const char * A, int n): List<char>(A, n) {}

String::String(List<char> other): List<char>(other) {}

String::String(std::string other): List<char>(other.c_str(), strlen(other.c_str())) {}

String::String(int n): List<char>(n) {} // private

List<String> String::split(char c) {
	List<String> sub_strings;

	int curr = find(c), last=0;
	while(curr != ERR_VAL) {
		if (curr != last) { // skip empty strings
			sub_strings.push(
				String(array+last, curr-last)
			);
		}

		last = curr+1;
		curr = find(c, last);
	}
	if (len != last) { // skip empty strings
		sub_strings.push(
			String(array+last, len-last)
		);
	}

	return sub_strings;
}

bool operator== (String const& lhs, String const& rhs) {
	if (lhs.get_len() != rhs.get_len()) {
		return false;
	}
	else {
		return std::memcmp(lhs.begin(), rhs.begin(), lhs.get_len()) == 0;
	}
}
bool operator!= (String const& lhs, String const& rhs) { return !(lhs == rhs); }


String operator+ (String const& lhs, String const& rhs) {
	String retval(lhs);
	retval += rhs;
	return retval;
}

std::ostream & operator<< (std::ostream & stream, String const& string) {
	for(char const& c: string) {
		stream << c;
	}
	return stream;
}

template<>
template<>
String List<String>::join(char c) {
	String sum;
	for(auto & s: *this) {
		sum += s;
		sum.push(c);
	}
	assert(sum.pop() == c);
	return sum;
}