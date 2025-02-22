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
    to a set of words based on the criteria given in the assignment
    -Splits at punctuation marks
    -Ignores words with fewer than 2 characters
   
    **/
set<string> parseStringToWords(string rawWords)
{


    set<string> keywords;
    string temp = ""; // Store the temporary word

    for (char ch : rawWords) {
        if (isalpha(ch)) {
            temp += tolower(ch); // Convert to lowercase because the match is case-insentive.
        }
        else {
            // If the ch is punctuation, store the word in temp to keywords if the word is valid (length >= 2)
            if (temp.length() >= 2) {
                keywords.insert(temp);
            }
            temp = ""; // Reset for the next word
        }
    }

    // Add the last word if it's valid (in case the rawWords ends with a letter so the last part of the rawWords is not stored in keywords set)
    if (temp.length() >= 2) {
        keywords.insert(temp);
    }

    return keywords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// trim from start (left trim)
string &ltrim(string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
        }));
    return s;
}

// trim from end
string& rtrim(string& s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
        }).base(), s.end());
    return s;
}

// trim from both ends
string& trim(string& s) {
    rtrim(s);  // First, trim right
    return ltrim(s);  // Then, trim left and return the modified string
}