#include <iostream>
#include <vector>
#include <string>

using namespace std;


bool is_duplicate(vector<string>& words, string word) {
    for(int i = 0; i < words.size(); ++i) {
        if(word.compare(words.at(i)) == 0) {
            return true;
        }
    }
    return false;
}


int main() {
    
    string word;
    vector<string> words;

    while(cin >> word) {
        if(is_duplicate(words, word)) {
            continue;
        } else {
            words.push_back(word);
        }
    }

    for(auto x : words) {
        cout << x << " ";
    }

    cout << endl;

}