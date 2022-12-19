/*  Author Name: <Sunny Qi >                                */
/*      Completed Nov 29 2022                               */

#include <iostream>
#include <string>
#include <sstream>
#include "a3.h"

using namespace std;

	int getIdx(char ch) {
		return ch - 'a';
	}

	char getLetter(int num) {
		return 'a' + num;
	}

	TrieNode::TrieNode() {
		for (size_t i = 0; i < LETTERS; i++)
		{
			m_children[i] = nullptr;
		}
		m_endofword = false;
	}

	Trie::Trie() {
		m_root = nullptr;
	}

	Trie::Trie(const std::string wordList[], int sz) {
		m_root = nullptr;
		for (size_t i = 0; i < sz; i++)
		{
			addWord(wordList[i]);
		}
	}

	void Trie::addWord(const std::string& newWord) {
		// check if the current letter is in the root
		if (m_root == nullptr)
		{
			m_root = new TrieNode;
		}
		// traverse the tree starting at the root
		TrieNode* current = m_root;
		for (size_t i = 0; i < newWord.length(); i++)
		{
			char currentletter = newWord[i];

			if (current->m_children[getIdx(currentletter)] == nullptr)
			{
				// the root does not contain this word
				// create an empty TrieNode at this letter index
				current->m_children[getIdx(currentletter)] = new TrieNode;
				current = current->m_children[getIdx(currentletter)];
			}
			else
			{
				current = current->m_children[getIdx(currentletter)];
			}
		}
		current->m_endofword = true;
	}

	// returns true iff word is a complete word in the Trie
	bool Trie::lookup(const std::string& word) const {
		bool found = false;
		bool stop = false;
		// if the Trie is empty, no word is in
		if (m_root == nullptr)
		{
			return false;
		}
		// parse through entire tree looking for the word letter by letter
		TrieNode* current = m_root;
		for (size_t i = 0; i < word.length() && !stop; i++)
		{
			char currentletter = word[i];
			if (current->m_children[getIdx(currentletter)] == nullptr)
			{
				// if a letter isn't found - the word isn't in the Trie
				stop = true;
			}
			else
			{ // continue looking until the end
				current = current->m_children[getIdx(currentletter)];
			}
		}
		if (!stop)
		{	// if we didnt break out early, check if the found word is marked as the end of a word
			found = current->m_endofword;
		}
		return found;
	}

	// tool to format recursive algorithm to split strings
	// here to avoid dynamically allocating memory for resultList
	int Trie::beginsWith(const std::string& prefix, std::string* resultList)const {
		string myresults[100];
		int numfound = startsWith(prefix, myresults);
		int count = 0;
		stringstream ss(myresults[0]);
		for (size_t i = 0; i < myresults[0].size(); i++)
		{
			if (myresults[0][i] == ',')
			{
				count++;
			}
		}
		for (size_t i = 0; i < count; i++)
		{
			getline(ss, resultList[i], ',');
		}
		return numfound;
	}

	// returns number of full words beginning with prefix
	// resultList stores the full words found
	int Trie::startsWith(const std::string& prefix, std::string* resultList) const {
		
		int numfound = 0;
		int index = 0;
		TrieNode* current = m_root;
		// get the position of my prefix
		bool found = false;
		bool stop = false;
		// if the Trie is empty, no word is in
		if (m_root == nullptr)
		{
			return false;
		}
		// parse through entire tree looking for the word letter by letter
		for (size_t i = 0; i < prefix.length() && !stop; i++)
		{
			char currentletter = prefix[i];
			if (current->m_children[getIdx(currentletter)] == nullptr)
			{
				// if a letter isn't found - the word isn't in the Trie
				stop = true;
			}
			else
			{ // continue looking until the end
				current = current->m_children[getIdx(currentletter)];
			}
		}
		if (!stop) // the whole prefix is found.
		{	
			// current is the position of the last letter of my prefix
			// if the prefix is a whole word, append it and increment found by 1
			if (current->m_endofword)
			{
				resultList->append(prefix + ',');
				numfound++;
			}

			for (size_t i = 0; i < LETTERS; i++)
			{
				string newprefix = prefix;
				if (current->m_children[i] != nullptr)
				{
					newprefix += getLetter(i);
					numfound += startsWith(newprefix, resultList);
				}
			}
		}
		return numfound;
	}


	Trie::~Trie() {
		delete[] m_root;
	}

