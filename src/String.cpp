#include "String.h"

namespace {
	int c_str_len(char const* c_str) {
		assert(c_str != NULL);

		char c;
		int i = 0;

		do {
			c = c_str[i];
			i++;
		} while (c != '\0');

		return i-1;
	}

	bool is_num(char c) {
		return c >= '0' && c <= '9';
	}
	bool is_alpha(char c) {
		return  (c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z');
	}
	bool is_whitespace(char c) {
		return c == ' ' || c == '\t' || c == '\n';
	}
}


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

template<>
String List<String>::join() {
	String sum;
	for (auto const& s: *this) {
		sum += s;
	}
	return sum;
}

std::size_t std::hash<String>::operator() (String const& string) const {
	std::hash<std::string> hasher;
	return hasher(std::string(string.begin()));
}