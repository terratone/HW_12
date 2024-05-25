#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

void processText(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File opening error" << endl;
        return;
    }

    map<string, int> wordFrequency; // Частотный словарь

    string word;
    while (file >> word) {
        if (word.empty()) { // Проверка на пустую строку
            continue;
        }

        transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return tolower(c); });

        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        wordFrequency[word]++;
    }
    file.close();

    ofstream output("result.txt");
    if (!output.is_open()) {
        cerr << "Error creating a result file." << endl;
        return;
    }

    for (const auto& pair : wordFrequency) {
        output << pair.first << ": " << pair.second << std::endl;
    }

    auto mostFrequentWord = max_element(wordFrequency.begin(), wordFrequency.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    output << "\nThe most frequent word: " << mostFrequentWord->first << endl;
    output.close();

    cout << "The count was successfully written to the file 'result.txt'." << endl;
}

int main() {
    processText("input.txt");
    cin.get();
    return 0;
}