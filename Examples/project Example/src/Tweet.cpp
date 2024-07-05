#include "../include/Tweet.h"

Tweet::Tweet(string text) : text(text), id(allid++) {
    ofstream file;
    file.open("../data/count_tweet.txt");
    file << allid;
}

int Tweet::get_id() {
    return id;
}

string Tweet::get_text() {
    return text;
}

int count_tweet() {
    ifstream file;
    file.open("../data/count_tweet.txt");
    int cnt;
    file >> cnt;
    return cnt;
}

int Tweet::allid = count_tweet();