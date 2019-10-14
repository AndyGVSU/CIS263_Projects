//
//  WordSearch.cpp
//  CS263-HW4
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  // needed for transform()
#include <exception>
#include <regex>
#include "WordSearch.h"

WordSearch::WordSearch() {
    /* default constructor requires no additional code */
}

WordSearch::WordSearch(const string& topdir, const string& ignore_file) {
    load_ignored_words(ignore_file);
    /* filter the directory only for files ending with "txt" */
    gvsu::FileSystem dir (topdir, regex{"txt$"});
    
    for (auto entry : dir) {
        cout << "Reading words from " << entry.second << endl;
        read_words (entry.first + "/" + entry.second);
    }
}

void WordSearch::load_ignored_words(const string& fname) {
    ifstream ign_file (fname);
    if (!ign_file.is_open()) {
        throw ios_base::failure {"Unable to load ignored.txt"};
        
    }
    string word;
    while (getline(ign_file, word))
        ignored_words.insert(word);
    ign_file.close();
}

void WordSearch::read_words(const string &file_name)
{
    /* a word is THREE OR MORE alphabetical characters (lowercase) */
    const regex word_re {"[a-z]{3,}"};
    
    /* Alternate declaration of the above regular expr
     const regex word_re {"[[:alpha:]]{3,}"};
     */
    ifstream txt (file_name); /* file is automatically open */
    
    string one_line;
    
    int line = 1;
    string lastWord = "";
    while (getline(txt, one_line)) {
        /* change to lowercase */
        transform(one_line.begin(), one_line.end(), one_line.begin(), ::tolower);
        /* iterate over the string using a regular expression */
        auto re_begin = sregex_iterator {one_line.begin(),one_line.end(), word_re};
        auto re_end = sregex_iterator{};

        //lastWord = "";
        for (auto word = re_begin; word != re_end; ++word) {
            /* if the word is in the ignored list, don't print it */
            if (ignored_words.find(word->str()) == ignored_words.end())
            {
                string w = word->str();
                /* TODO: use the current word to update your data structures */
                //words_of_length
                int wordLength = w.size();
                auto wordIter = lengthMap.find(wordLength);
                if (wordIter != lengthMap.end())
                    (lengthMap.at(wordLength)).insert(w);
                else {
                    lengthMap.insert(make_pair(wordLength, set<string>()));
                    (lengthMap.at(wordLength)).insert(w);
                }
                //word frequency
                auto freqIter = freqMap.find(w);
                if (freqIter == freqMap.end())
                    freqMap.insert(make_pair(w,1));
                else
                    freqMap[w]++;
                //next word
                auto nextIter = nextMap.find(lastWord);
                if (nextIter == nextMap.end()) { //if no match is found for last word
                    if (lastWord != "") { //if this is not the first word
                        nextMap.insert(make_pair(lastWord, map<string, int>()));
                        nextMap[lastWord].insert(make_pair(w,1));
                    }
                } else { //if a match was found for the last word
                    nextMap[lastWord][w]++;
                }
                lastWord = w;
            }
        }
        line++;
    }
    txt.close(); /* close the file */
}


unsigned long WordSearch::word_count() const {
    /* TODO complete this function */
    unsigned long wordCount = 0;

    auto freqIter = freqMap.rbegin();
    while(freqIter != freqMap.rend()) {
        wordCount += freqIter->second;
        freqIter++;
    }
    return wordCount;
}

set<string> WordSearch::words_of_length (int L) const {
    /* TODO complete this function */
    auto iter = lengthMap.find(L);
    if (iter != lengthMap.end())
        return lengthMap.at(L);
    return set<string>(); /* return an empty set */
}

pair<unsigned int,set<string>> WordSearch::most_frequent_words() const
#ifndef _WIN32
  throw (length_error)
#endif
{
    /* TODO complete this function */
    auto freqIter = freqMap.rbegin();
    if (freqIter == freqMap.rend())
        throw std::length_error("No documents loaded.");

    int occurrences = 0;
    set<string> words;

    //get max occurrence count
    while(freqIter != freqMap.rend()) {
        if (freqIter->second >= occurrences)
            occurrences = freqIter->second;
        freqIter++;
    }

    freqIter = freqMap.rbegin();
    while(freqIter != freqMap.rend()) {
        if (freqIter->second == occurrences)
            words.insert(freqIter->first);
        freqIter++;
    }

    return make_pair(occurrences, words);
}

set<string> WordSearch::least_frequent_words(int count) const {
    set<string> words;
    /* TODO complete this function */

    auto freqIter = freqMap.rbegin();
    if (freqIter == freqMap.rend())
        throw std::length_error("No documents loaded.");

    freqIter = freqMap.rbegin();
    while(freqIter != freqMap.rend()) {
        if (freqIter->second <= count)
            words.insert(freqIter->first);
        freqIter++;
    }

    return words;
}

string WordSearch::most_probable_word_after(const string& word) const {
    
    /* TODO complete this function */
    int occurrence = 0;
    string occurString = "";

    auto iterCheck = nextMap.find(word);
    if (iterCheck != nextMap.end()) {
        auto iter = (nextMap.at(word)).begin();
        while (iter != nextMap.at(word).end()) {
            if (iter->second > occurrence) {
                occurrence = iter->second;
                occurString = iter->first;
            }
            iter++;
        }
    }

    return occurString;
}
