#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;

    if (start == end) {
        error(start, end, "Start and end words must be different");
        return 1;
    }

    vector<string> ladder = generate_word_ladder(start, end, word_list);
    if (ladder.empty()) {
        cout << "No ladder found from " << start << " to " << end << endl;
    } else {
        print_word_ladder(ladder);
    }

    return 0;
}