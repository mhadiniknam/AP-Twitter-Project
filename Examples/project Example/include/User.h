#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
#include "Tweet.h"

using namespace std;

class User {
    private:
        string username;
        string password;
        string firstname;
        string lastname;
    public:
        User(string, string, string, string);
        User(string);
        void add_tweet(Tweet);
        void view_tweets();
        string get_username();
};

#endif
