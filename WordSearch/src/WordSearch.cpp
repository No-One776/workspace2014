//
//  WordSearch.cpp
//  CS263-HW4
//
//  Created by Hans Dulimarta on 10/19/14.
//  Copyright (c) 2014 SoCIS. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>  // needed for transform()
#include <exception>
#include "WordSearch.h"


WordSearch::WordSearch() {
    /* default constructor requires no additional code */
    unsigned long wordCount = 0;
    map<int, set<string>> lengthMap;
    map<string, unsigned int> wordFrequency;
    map<unsigned int, set<string>, less<int>> leastFrequent;
    map<string, map<string, int>> predictWord;
    map<string, set<string>> wordFileMap;
}

WordSearch::WordSearch(const string& topdir, const string& ignore_file) {
    load_ignored_words(ignore_file);
    /* filter the directory only for files ending with "txt" */
    gvsu::FileSystem dir (topdir);
    unsigned long wordCount = 0;
    map<int, set<string>> lengthMap;
    map<string, unsigned int> wordFrequency;
    map<unsigned int, set<string>> leastFrequent;
    map<string, map<string, int>> predictWord;
    map<string, set<string>> wordFileMap;


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
    ifstream txt (file_name); /* file is aumatically open */

    string one_line;

    int line = 1;
    string prev = "";

    while (getline(txt, one_line)) {
        /* change to lowercase */
        transform(one_line.begin(), one_line.end(), one_line.begin(), ::tolower);

        /* replace non-alpha with a space */
        replace_if (one_line.begin(), one_line.end(),
        	[] (const char c) {
        	return !isalpha(c);
        }, ' ');
        istringstream tokens{one_line};
        string word;
        while (tokens >> word) {
            if (word.length() < 3) continue;
            if (ignored_words.find(word) == ignored_words.end()) {

                wordCount++;
                lengthMap[word.length()].insert(word);
		wordFrequency[word]++;
		wordFileMap[word].insert(file_name);

		if (prev != "") {
			predictWord[prev][word]++;
		}
                prev = word;

            }
        }
        line++;
    }
    txt.close(); /* close the file */

	for (auto iter = wordFrequency.begin(); iter != wordFrequency.end();iter++){
		leastFrequent[iter->second].insert(iter->first);
	}
}

/**
** WORKS
**/
unsigned long WordSearch::word_count() const {
    return wordCount;
}

/**
** WORKS
**/
set<string> WordSearch::words_of_length (int L) const {
	if (lengthMap.find(L) != lengthMap.end())
   		return lengthMap.at(L);
	return set<string>();
}

/**
** WORKS
**/
pair<unsigned int,set<string>> WordSearch::most_frequent_words() const throw (length_error) {
    if (leastFrequent.rbegin() == leastFrequent.rend()) // Err if empty
    	throw length_error ("length error");
    return make_pair(leastFrequent.rbegin()->first,leastFrequent.rbegin()->second); 
// Otherwise return the end of the map (map is already sorted least to greatest)
}

/**
** WORKS.......sorta
**/
set<string> WordSearch::least_frequent_words(int count) const {
	set<string> words;


	//for (auto iter = temp.begin(); iter!=temp.end(); iter++){
	//	files.insert(wordFileMap[*iter].begin(),wordFileMap[*iter].end());
	//}


    	for (int i = 1; i<=count;i++){  // Iterate through 0->Count   
		if (leastFrequent.find(i) != leastFrequent.end()){
			set<string> temp = leastFrequent.at(i);
			for (auto iter = temp.begin(); iter!=temp.end(); iter++){
				words.insert(*iter);
			}
		}
	}
    return words;
}

/**
** WORKS
**/
set<string> WordSearch::files_with_most_frequent_words()  throw(length_error) {
	if (leastFrequent.rbegin() == leastFrequent.rend()) // Err if empty
		throw length_error ("length error");

	set<string> files;
	for (auto iter = leastFrequent.rbegin()->second.begin(); iter!=leastFrequent.rbegin()->second.end(); iter++){
			files.insert(wordFileMap[*iter].begin(),wordFileMap[*iter].end());
	}
    return files;
}

/**
** WORKS.......sorta
**/
set<string> WordSearch::files_with_least_frequent_words(int N) const
{
	set<string> files;
	set<string> findWords = least_frequent_words(N);
	for (auto iter = findWords.begin(); iter!=findWords.end(); iter++){
		//set<string> fileList = wordFileMap.at(*iter);
		//files.insert(fileList.begin(),fileList.end());
		files.insert(wordFileMap.at(*iter).begin(),wordFileMap.at(*iter).end());
	}


    return files;
}

string WordSearch::most_probable_word_after(const string& word) const {
	string mostProbable = "";
	int frequency = 0;
	if (predictWord.find(word)!=predictWord.end()){
		map<string,unsigned int> wordsMap = predictWord.at(word);
		map<unsigned int, set<string>> frequencyOrder;
		
		for (auto iter = wordsMap.begin(); iter != wordsMap.end(); iter++){
			frequencyOrder[iter->second].insert(iter->first);
//			if (iter->second >= frequency)
//				mostProbable = iter->first;
		}
		return *frequencyOrder.rbegin()->second.begin();
	
	}
    return mostProbable;
}
