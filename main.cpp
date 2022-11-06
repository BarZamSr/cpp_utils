#include <iostream>

#include "list.cpp"
#include "string.cpp"

int main() {
	String s1 = "We're going on a trip in our favorite rocket ship ";
	String s2 = "Zooming through the sky, Little Einsteins ";
	String s3 = "Climb aboard, get ready to explore ";
	String s4 = "There's so much to find, Little Einsteins ";

	LOG(s1.split(' ').join(' '));

	return 0;
}
