#include "../include/Panel.h"

Panel::Panel() {
    user_menu.menu_head("my twitter");
    user_menu.add("add tweet", 1, "add new tweet");
    user_menu.add("view tweets", 2, "view all tweets");
    user_menu.add("logout", 3);

    login_menu.menu_head("Twitter");
    login_menu.add("login", 1, "i already have an account");
    login_menu.add("signup", 2, "create new account");
    login_menu.add("Exit");

    setting_menu.menu_head("setting");
    setting_menu.add("logout", 1);
}

void Panel::login_panel() {
    while (true) {
        string username;
        int type = login_menu.display();
        switch (type) {
            case 1:
                login();
                break;
            case 2:
                sign_up();
                sleep_for(seconds(5));
                break;
            case 3:
                cout << "Thank You!\n";
                sleep_for(seconds(5));
                exit(0);
            default:
                cout << type << endl;
                break;
        }
        getch();
    }
}

void Panel::login() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream username_file, password_file;
    username_file.open("../data/usernames.txt");

    string username_in_file, password_in_file;
    while (username_file >> username_in_file) {
        if (username == username_in_file) {
            password_file.open("../data/" + username + "/password.txt");
            password_file >> password_in_file;
            password_file.close();
            username_file.close();
            if (password == password_in_file) {
                cout << "Login is confirmed\n";
                sleep_for(seconds(5));
                user_panel(User(username));
                return;
            }
            sleep_for(seconds(5));
            cout << "The password is invalid\n";
            return;
        }
    }
    username_file.close();
    sleep_for(seconds(5));
    cout << "User with this username was not found\n";
    return;
}

void Panel::sign_up() {
    string firstname, lastname, username, password;
    cout << "Enter your firstname: ";
    cin >> firstname;
    cout << "Enter your secondname: ";
    cin >> lastname;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream username_file;
    username_file.open("../data/usernames.txt");

    string username_in_file;
    while (username_file >> username_in_file) {
        if (username == username_in_file) {
            cout << "Duplicate username\n";
            username_file.close();
            return; 
        }
    }
    cout << "The account was created successfully\n";
    username_file.close();
    User new_user(username, password, firstname, lastname);
    return;
}

void Panel::user_panel(User user) {
    int type;
    while (true) {
        getch();
        type = user_menu.display();
        string tweet_text;
        switch (type) {
            case 1:
                cout << "Enter the text of the tweet: ";
                cin.ignore();
                getline(cin, tweet_text);
                user.add_tweet(Tweet(tweet_text));
                cout << "Accepted\n";
                sleep_for(seconds(2));
                break;
            case 2:
                user.view_tweets();
                sleep_for(seconds(10));
                break;
            case 3:
                getch();
                login_panel();
            default:
                cout << type << endl;
                break;
        }
        getch();
    }
}

int main() {
    Panel main_panel;
    main_panel.login_panel();
    return 0;
}