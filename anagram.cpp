#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<string> findTwoWordAnagrams(map<int, vector<string>> mapOfWords,  string& sortedWord) {
    vector<string> foundAnagrams;
    int minLength = 2;
    
    // 1. iteration (map for first word sizes)
    for (auto it = mapOfWords.begin(); it != mapOfWords.end(); it++) {
        // If can't make 2 words out of them then break (input size - min length)
        if (it->first > sortedWord.size() - minLength)
            break;

        int sizeDiff = (int)sortedWord.size() - it->first;
        
        // First word
        for (string firstWord : it->second) {
            vector<string> secondWords = mapOfWords[sizeDiff];

            // Second word
            for (string secondWord : secondWords) {
                string combinedWord = firstWord + secondWord;

                // Sort by characters
                sort(combinedWord.begin(), combinedWord.end());

                if (combinedWord == sortedWord) {
                    // Don't repeat words in different order
                    if (!foundAnagrams.empty() && secondWord + " " + firstWord == foundAnagrams[0])
                        return foundAnagrams;
                    
                    // Found an anagram and push it to a vector
                    foundAnagrams.push_back(firstWord + " " + secondWord);
                }
            }
        }
    }
    return foundAnagrams;
}

// Map words with key as length, value as words with that length
map<int, vector<string>> wordsToMap() {
    map<int, vector<string>> mapOfWords;
    vector<string> words;
    string currentWord;

    // Open the File
    ifstream in("english_58000_lowercase.txt");
    
    // Read the next line from File untill it reaches the end.
    while (getline(in, currentWord)) {
        if (currentWord.size() <= 0)
            continue;

        // Fix for \r at the end
        currentWord.resize(currentWord.size() - 1);

        // Try to find key if it exists push word to it's vector of strings
        // If it doesn't exist insert a new key, value in map
        auto it = mapOfWords.find(currentWord.size());

        if (it != mapOfWords.end()) {
            (mapOfWords[currentWord.size()]).push_back(currentWord);
        } 
        else {
            vector<string> tmpVect;
            tmpVect.push_back(currentWord);
            mapOfWords.insert({currentWord.size(), tmpVect});
        }
    }

    return mapOfWords;
}

int main ()  {
    string inputWord;
    string sortedWord;

    map<int, vector<string>> mapOfWords = wordsToMap();

    do {
        cout << "Enter a word: " << endl;
        cin >> inputWord;
    } while (inputWord.size() < 2);

    // Word to lowercase
    for (char& letter : inputWord)
        letter = tolower(letter);

    sortedWord = inputWord;
    sort(sortedWord.begin(), sortedWord.end());

    vector<string> foundAnagrams = findTwoWordAnagrams(mapOfWords, sortedWord);
    if (foundAnagrams.empty())
        cout << "There are no two-word anagrams for this word." << endl;
    else {
        cout << "Found " + to_string(foundAnagrams.size()) + " two-word anagrams:" << endl;
        for (string anagram : foundAnagrams)
            cout << anagram << endl;
    }

    return 0;
}