#include "ladder.h"
#include <algorithm>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error between " << word1 << " and " << word2 << ". " << msg <<endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();

    // Create a 2D DP table to calculate Levenshtein distance
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    // Initialize the base case
    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            if (i == 0) {
                dp[i][j] = j;  // Insertions
            } else if (j == 0) {
                dp[i][j] = i;  // Deletions
            } else {
                dp[i][j] = std::min({dp[i - 1][j] + 1,       // Deletion
                                     dp[i][j - 1] + 1,       // Insertion
                                     dp[i - 1][j - 1] + (str1[i - 1] != str2[j - 1])}); // Substitution
            }
        }
    }

    // Calculate the edit distance
    int distance = dp[len1][len2];

    // Return true if the distance is exactly d
    return distance == d;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> q;
    set<string> visited;

    q.push({begin_word});
    visited.insert(begin_word);
    while(!q.empty()){
        vector<string> path = q.front();
        q.pop();
        string current_word = path.back();
        
        // Debugging: print the current path
        // cout << "Current path: ";
        // for (const string& word : path) {
        //     cout << word << " ";
        // }
        // cout << endl;

        if(current_word == end_word){
            return path;
        }
        
        for (const string& word :word_list){
            if(!visited.count(word) && is_adjacent(current_word, word)){
                visited.insert(word);
                vector<string> new_path = path;
                new_path.push_back(word);
                q.push(new_path);
                // cout << "Enqueuing: " << word << endl;
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name){
    ifstream file(file_name);
    string word;
    while (file >> word){
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (const string& word: ladder){
            cout << word << " ";
        }
        cout << endl;
    } else {
        cout << "No word ladder found." << endl;
    }
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");


    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);


    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);


    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);


    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);


    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);


    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}