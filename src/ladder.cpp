#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error between " << word1 << " and " << word2 << ". " << msg <<endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1 == str2) return d == 1; 

    int len1 = str1.size();
    int len2 = str2.size();

    if (abs(len1 - len2) > 1){ 
        return false; 
    }

    int diff_count = 0;
    int i = 0; 
    int j = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            diff_count++;
            if (diff_count > 1) return false;

            if (len1 > len2) {
                i++;  
            } else if (len1 < len2) {
                j++;  
            } else {
                i++, j++;  
            }
        } else {
            i++, j++;  
        }
    }

    if (i < len1 || j < len2) diff_count++;

    return diff_count == 1;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word) {
        vector<string> empty;
        return empty;
    }

    queue<vector<string>> q;
    set<string> visited;
    q.push({begin_word});
    visited.insert(begin_word);

    while(!q.empty()){
        vector<string> path = q.front();
        q.pop();
        string current_word = path.back();
        
        for (const string& word :word_list){
            if(visited.find(word) == visited.end() && is_adjacent(current_word, word)){
                visited.insert(word);
                vector<string> new_path = path;
                new_path.push_back(word);
                if(current_word == end_word){
                    return path;
                }
                q.push(new_path);
            }
        }
    }
    vector<string> empty;
    return empty;
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