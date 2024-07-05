#ifndef TWEET_H
#define TWEET_H

#include <bits/stdc++.h>
using namespace std;

class Tweet {
    private:
        string text;
        int id;
        static int allid;
    public:
        Tweet(string);
        int get_id();
        string get_text();
};

#endif