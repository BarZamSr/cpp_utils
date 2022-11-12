#include <iostream>

#include "src/List.h"
#include "src/String.h"

int main() {
	String s1 = "We're going on a trip in our favorite rocket ship";
	String s2 = "Zooming through the sky, Little Einsteins";
	String s3 = "Climb aboard, get ready to explore";
	String s4 = "There's so much to find, Little Einsteins";

	List S = {s1, s2, s3, s4};

	std::cout << S.join('\n') << std::endl;

	return 0;
}