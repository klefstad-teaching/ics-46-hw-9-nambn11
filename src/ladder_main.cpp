#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");  
    
    string begin_word = "code";
    string end_word = "data";
    
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    
    if (!ladder.empty()) {
        cout << "Word Ladder: ";
        print_word_ladder(ladder);
    } else {
        cout << "No ladder found!" << endl;
    }
    
    return 0;
}