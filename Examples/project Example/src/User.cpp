#include "../include/User.h"

User::User(string u, string p, string f, string l) : username(u), password(p), firstname(f), lastname(l) {
    // add user to end of file user.txt
    ofstream username_file;
    username_file.open("../data/usernames.txt", ios::app);
    username_file << username << "\n";
    username_file.close();
    // make a folder for this users twitter
    string command = "mkdir ../data/" + username;
    system(command.c_str());

    // make a file for this users tweets
    ofstream password_file, firstname_file, lastname_file;
    password_file.open("../data/" + username + "/password.txt");
    password_file << password << '\n';
    password_file.close();
    firstname_file.open("../data/" + username + "/firstname.txt");
    firstname_file << firstname << '\n';
    firstname_file.close();
    lastname_file.open("../data/" + username + "/lastname.txt");
    lastname_file << lastname << '\n';
    lastname_file.close();
}

User::User(string u) {
    username = u;
}

void User::add_tweet(Tweet tweet) {
    ofstream id_tweets_file;
    id_tweets_file.open("../data/" + username + "/tweets_id.txt", ios::app);
    id_tweets_file << tweet.get_id() << "\n";
    id_tweets_file.close();

    ofstream tweet_text;
    string tmp = to_string(tweet.get_id());
    tweet_text.open("../data/" + username + "/" + tmp + ".txt");
    tweet_text << tweet.get_text() << '\n';
}

void User::view_tweets() {
    ifstream username_file;
    username_file.open("../data/usernames.txt");
    string username;
    while (username_file >> username) {
        ifstream id_tweets_file;
        id_tweets_file.open("../data/" + username + "/tweets_id.txt");
        string id_tweet;
        while (id_tweets_file >> id_tweet) {
            cout << username << ":\n";
            ifstream tweet_text;
            tweet_text.open("../data/" + username + "/" + id_tweet + ".txt");
            string text;
            getline(tweet_text, text);
            cout << "    " << text << "\n\n";
        }
    }
}

string User::get_username() {
    return username;
}