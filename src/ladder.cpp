#include "ladder.h"
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error between " << word1 << " and " << word2 << ". " << msg <<endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d){
    if (str1.length() != str2.length()){
        return false;
    }

    int diff_count = 0;
    for (size_t i = 0; i < str1.length(); ++i){
        if (str1[i] != str2[i]){
            diff_count++;
        }
        if (diff_count > d){
            return false;
        }
    }
    return diff_count == d;
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

        if(current_word == end_word){
            return path;
        }

        for (const string& word :word_list){
            if(!visited.count(word) && is_adjacent(current_word, word)){
                visited.insert(word);
                vector<string> new_path = path;
                new_path.push_back(word);
                q.push(new_path);
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
    for (const string& word: ladder){
        cout << word << " ";
    }
    cout << endl;
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