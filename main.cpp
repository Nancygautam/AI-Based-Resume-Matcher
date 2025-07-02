#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

// Convert text to lowercase
string toLower(const string& text) {
    string result = text;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Read file content
string readFile(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return toLower(buffer.str());
}

// Get word frequency map
unordered_map<string, int> getWordFreq(const string& text) {
    unordered_map<string, int> freq;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        // Remove punctuation
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        freq[word]++;
    }
    return freq;
}

// Compute cosine similarity
double computeCosineSimilarity(unordered_map<string, int>& f1, unordered_map<string, int>& f2) {
    double dot = 0.0, mag1 = 0.0, mag2 = 0.0;

    for (auto& pair : f1) {
        dot += pair.second * f2[pair.first];
        mag1 += pair.second * pair.second;
    }

    for (auto& pair : f2) {
        mag2 += pair.second * pair.second;
    }

    if (mag1 == 0 || mag2 == 0) return 0.0;
    return dot / (sqrt(mag1) * sqrt(mag2));
}

int main() {
    string resumeText = readFile("C:\\Users\\NANCY GAUTAM\\Downloads\\resume.txt");
    string jdText = readFile("C:\\Users\\NANCY GAUTAM\\Documents\\ResumeProject\\job_description.txt");

    auto resumeFreq = getWordFreq(resumeText);
    auto jdFreq = getWordFreq(jdText);

    double similarity = computeCosineSimilarity(resumeFreq, jdFreq);

    cout << "?? Resume Matching Score: " << similarity * 100 << " %" << endl;

    return 0;
}

