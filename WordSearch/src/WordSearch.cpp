//============================================================================
// Name        : WordSearch.cpp
// Author      : Justin Rohr, Alex Banker, & Alex Zurek
// Version     : 1.0
// Description : Word Search
//============================================================================
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
#include <regex>
#include "WordSearch.h"

WordSearch::WordSearch() {
	/* default constructor requires no additional code */
}

WordSearch::WordSearch(const string& topdir, const string& ignore_file) {
	load_ignored_words(ignore_file);
	/* filter the directory only for files ending with "txt" */
	gvsu::FileSystem dir(topdir, regex { "txt$" });

	for (auto entry : dir) {
		cout << "Reading words from " << entry.second << endl;
		read_words(entry.first + "/" + entry.second);
	}
}

void WordSearch::load_ignored_words(const string& fname) {
	ifstream ign_file(fname);
	if (!ign_file.is_open()) {
		throw ios_base::failure { "Unable to load ignored.txt" };

	}
	string word;
	while (getline(ign_file, word))
		ignored_words.insert(word);
	ign_file.close();
}

void WordSearch::read_words(const string &file_name) {
#ifndef __MINGW32__
	/* a word is THREE OR MORE alphabetical characters (lowercase) */
	const regex word_re {"[a-z]{3,}"};

	/* Alternate declaration of the above regular expr
	 const regex word_re {"[[:alpha:]]{3,}"};
	 */
#endif
	ifstream txt(file_name); /* file is aumatically open */

	string one_line;

	int line = 1;
	string prev = "";
	while (getline(txt, one_line)) {
		/* change to lowercase */
		transform(one_line.begin(), one_line.end(), one_line.begin(),
				::tolower);
#ifndef __MINGW32__
		/*--------------------------------------------------------*
		 * The following block of code is for Linux or OS X users *
		 *--------------------------------------------------------*/
		/* iterate over the string using a regular expression */
		auto re_begin = sregex_iterator {one_line.begin(),one_line.end(), word_re};
		auto re_end = sregex_iterator {};
		for (auto word = re_begin; word != re_end; ++word) {
			/* if the word is in the ignored list, don't print it */
			if (ignored_words.find(word->str()) == ignored_words.end())
			{
				/* TODO: REMOVE the following cout line */
				cout << "Current word is " << word->str() << endl;

				/* TODO: use the current word to update your data structures */
			}
		}
#else
		/*--------------------------------------------------*
		 * The following block of code is for Windows users *
		 *--------------------------------------------------*/

		/* replace non-alpha with a space */
		replace_if(one_line.begin(), one_line.end(), [] (const char c) {
			return !isalpha(c);
		}, ' ');
		istringstream tokens { one_line };
		string word;
		while (tokens >> word) {
			if (word.length() < 3)
				continue;
			if (ignored_words.find(word) == ignored_words.end()) {
				/* TODO: REMOVE the following cout line */
				cout << "Current word is " << word << endl;

				/* TODO: use the current word to update your data structures */
			}
		}
#endif
		line++;
	}
	txt.close(); /* close the file */
}

unsigned long WordSearch::word_count() const {
	/* TODO complete this function */
	return 0;
}

set<string> WordSearch::words_of_length(int L) const {
	/* TODO complete this function */
	return set<string>(); /* return an empty set */
}

pair<unsigned int, set<string>> WordSearch::most_frequent_words() const
		throw (length_error) {
	set<string> words;

	/* TODO complete this function */

	return make_pair(0, words);
}

set<string> WordSearch::least_frequent_words(int count) const {
	set<string> words;
	/* TODO complete this function */

	return words;
}

set<string> WordSearch::files_with_most_frequent_words() throw (length_error) {
	set<string> files;

	/* TODO complete this function */

	return files;
}

set<string> WordSearch::files_with_least_frequent_words(int N) const {
	set<string> files;

	/* TODO complete this function */

	return files;

}

string WordSearch::most_probable_word_after(const string& word) const {

	/* TODO complete this function */

	return "";
}
