#include <iostream>
#include <unordered_map>

#include "src/List.h"
#include "src/String.h"

void string_join_test();
void string_hash_test();

int main() {
	

	return 0;
}

void string_join_test() {
	String s1 = "We're going on a trip in our favorite rocket ship";
	String s2 = "Zooming through the sky, Little Einsteins";
	String s3 = "Climb aboard, get ready to explore";
	String s4 = "There's so much to find, Little Einsteins";

	List S = {s1, s2, s3, s4};

	std::cout << S.join('\n') << std::endl;
}

void string_hash_test() {
	std::unordered_map<String,int> map;
}