#include "ladder.h"
#include <queue>
#include <unordered_set>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << " -> " << word2 << ")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    if (abs(len1 - len2) > d) return false;

    int edits = 0;
    for (size_t i = 0, j = 0; i < len1 && j < len2; ++i, ++j) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;
            if (len1 > len2) --j; // Insertion in str1
            else if (len1 < len2) --i; // Deletion in str1
        }
    }
    return true;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {begin_word}; // Return a ladder of size 1 if start and end words are the same
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});

    unordered_set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (word == end_word) {
                    ladder.push_back(word);
                    return ladder;
                }

                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }

    return {}; // No ladder found
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in) throw runtime_error("Unable to open dictionary file");

    string word;
    while (in >> word) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n"; // Handle empty ladder case
        return;
    }

    cout << "Word ladder found: "; // Prefix for valid ladders
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size()) cout << " "; // Add space after each word, including the last one
    }
    cout << "\n"; // Add a newline at the end
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    auto test_ladder = [&](const string& start, const string& end, int expected_size) {
        auto ladder = generate_word_ladder(start, end, word_list);
        cout << "Ladder from " << start << " to " << end << ": ";
        print_word_ladder(ladder);
        cout << "Expected size: " << expected_size << ", Actual size: " << ladder.size() << endl;
    };

    test_ladder("cat", "dog", 4);
    test_ladder("marty", "curls", 6);
    test_ladder("code", "data", 6);
}