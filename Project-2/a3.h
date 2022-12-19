/*  Author Name: <Sunny Qi >                                */
/*      Completed Nov 29 2022                               */

#ifndef SDDS_TRIE_H
#define SDDS_TRIE_H

#include <string>


	const int LETTERS = 26;

	struct TrieNode {
		TrieNode* m_children[LETTERS];
		bool m_endofword;

		TrieNode();
	};

	class Trie {
	private:
		TrieNode* m_root;
	public:
		Trie();
		Trie(const std::string wordList[], int sz);
		void addWord(const std::string& newWord);
		bool lookup(const std::string& word) const;
		int beginsWith(const std::string& prefix, std::string resultList[]) const;
		// helper
		int startsWith(const std::string& prefix, std::string resultList[]) const;

		~Trie();
	};

#endif


