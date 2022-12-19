Over the course of the term, you have been exposed to a variety of data structures. Considering the functionality of a Trie, pick two other data structure we have studied and discuss the following:

How efficient is the creation Trie vs your chosen data structures.
How good will that data structure be at the main look up tasks of a Trie(search and begins_with).
How can each of the chosen data structures support the two look up tasks (can you use the exist functionality or do you need to do something extra to what is typically returned?)
To get full marks on this discussion, please provide details about the data structure you are comparing with the Trie, its features, and how well is it able to handle each of the three tasks of the Trie.

## Trie vs Hash Map
A creation of a trie is extremely efficient for our purpose.
When creating a word, we only create a new node if one representing the current letter doesn't already exist.
The worst case for time complexity when inserting a word is the length of the word.

Hash map will be excellent at search and insert, accomplishing both in constant time since we have a key. However, the beginsWith method, our Trie far outperforms it.
Since we do not have a key, the hash map must iterate through the entire map, looking at the value at each key and making sure that our prefix is a part of that.
The Trie must only go down 1 path.
The current implementation of our Trie is not the most efficient way. If we pass a pointer to the current node to the beginsWith method, it can skip the whole first half where it finds the current Node given a prefix.


## Trie vs Linked List
Creation of a Trie is again, more efficient than a linked list for this purpose.
When implementing this functionality using a Linked list, The head will store the shortest asciibetical word, followed by the next longer, and so on.
When inserting, the list will iterate down until the word to be inserted has a lower ascibetical value, and be inserted in that position.
When searching for existance, We must travel down the entire list in the worst case.
When searching begins with, we iterate down the list until we find a value which is equal to our prefix, and return the next element until next.value is no longer a part of our prefix.
In every case, when requiring this functionality.
