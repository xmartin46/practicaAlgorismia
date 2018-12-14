#ifndef STRINGTOINT
#define STRINGTOINT

#include <climits>
#include <unordered_map>
#include <string>

using namespace std;

// Class to convert shingles from strings to ints so that they only use 4 bytes of space
class StringToInt {
    
    private:

        // Here will be the instance stored. 
        static StringToInt* instance;

        // Private constructor to prevent instancing. 
        StringToInt();

        //Map to store conversions
        unordered_map<string, int> table;

        

    public:

        static StringToInt* getInstance();

        int toInt(string s) {
            // This string hasn't been mapped to an int yet
            // Assign next possible int to it
            if (table.find(s) == table.end()) {
                // mapping will increment by 1 after every insertion
                int mapping = (INT_MIN + table.size())%INT_MAX; 
                table.insert(make_pair(s, mapping));
                return mapping;
            }
            // This string has already been mapped before, so just
            // look for it in the map and return its int
            return table[s];
        }
};

// Null because we will initialize it on demand
StringToInt* StringToInt::instance = NULL;

StringToInt* StringToInt::getInstance() {
    if (instance == NULL) {
        instance = new StringToInt;
    }
    return instance;
}

StringToInt::StringToInt() {}

#endif