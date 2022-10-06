#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	std::set<std::string> rawWord;
	int counter = 0;
	int length = rawWords.size();
	// all the punctuations and one letters in the given string is converted to spaces
	for(int i = 0; i < length; i = i + 1){
		if(ispunct(rawWords[i])){
			if(rawWords[i+1] != ' ' && rawWords[i-1] != ' '){
				rawWords[i] = ' ';
			}
	}
	}

	// the length of a key word is calculated
	for(int i = 0; i < length; i = i + 1){
		if(rawWords[i] != ' '){
			
				counter = counter + 1;
		}
		// when the keyword ends the keyword is added to the set
		if (rawWords[i] == ' ' && counter >= 2){
			rawWord.insert(rawWords.substr(i-counter, counter));
			counter = 0;
		}
		// the edge case where we are dealing with the last word of the string
		// this is an edge case becasue usually we understand how a word ends by the space
		// at the end but since the last word may not have a space at the end we use the following
		// condition
		else if (i == length - 1 && counter >= 2){
			rawWord.insert(rawWords.substr(i-(counter - 1), counter));
		}
	}
	return rawWord;
}

	/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}