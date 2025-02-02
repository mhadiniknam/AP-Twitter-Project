#include "include/CubbyMenu.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<class Account> db;
vector<class Tweet> tweets;
int id = 1;
const char *accountfile = "./Data/Accounts.txt";
const char *tweetfile = "./Data/Tweets.txt";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Account
{
private:
	string name;
	string familyName;
	string username;
	string email;
	string password;
	string dateOfBirth = "";
	string gender = "";

public:
	vector<string> follower;
	vector<string> following;

	Account(string name, string familyName, string username, string password, string email)
	{
		this->name = name;
		this->familyName = familyName;
		this->username = username;
		this->email = email;
		this->password = password;
	}

	string getUsername()
	{
		return username;
	}

	string getEmail()
	{
		return email;
	}

	string getPassword()
	{
		return password;
	}

	string getName()
	{
		return name;
	}

	string getFamilyName()
	{
		return familyName;
	}

	string getDateOfBirth()
	{
		return dateOfBirth;
	}

	string getGender()
	{
		return gender;
	}

	void fieldSetter(int i, string s)
	{
		switch (i)
		{
		case 1:
			this->name = s;
			break;
		case 2:
			this->familyName = s;
			break;
		case 3:
			this->username = s;
			break;
		case 4:
			this->password = s;
			break;
		case 5:
			this->email = s;
			break;
		case 6:
			this->dateOfBirth = s;
			break;
		case 7:
			this->gender = s;
			break;
		}
	}

	void addFollower(string &username)
	{
		follower.push_back(username);
	}

	void addFollowing(string &username)
	{
		following.push_back(username);
	}
};

class Tweet
{
private:
	string username;
	string content;
	int likenum = 0;
	int isReply;
	int id;
	int toReplyId;

public:
	Tweet(string username, string content, int id, int isReply)
	{
		this->username = username;
		this->content = content;
		this->id = id;
		this->isReply = isReply;
	}

	Tweet(string username, string content, int id, int isReply, int toReplyId, int like)
	{
		this->username = username;
		this->content = content;
		this->id = id;
		this->isReply = isReply;
		this->toReplyId = toReplyId;
		this->likenum = like;
	}

	string getTweetUsername()
	{
		return username;
	}

	string getTweetContent()
	{
		return content;
	}

	void like()
	{
		likenum++;
	}

	int getisReply()
	{
		return isReply;
	}

	int getlike()
	{
		return likenum;
	}

	int getid()
	{
		return id;
	}

	int gettoReplyId()
	{
		return toReplyId;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteAccounts()
{
	string s = ",";
	string buf;
	ofstream file;
	file.open(accountfile);
	if (file.is_open())
	{
		for (auto &x : db)
		{
			s = s + x.getName();
			s = s + ",";
			s = s + x.getFamilyName();
			s = s + ",";
			s = s + x.getUsername();
			s = s + ",";
			s = s + x.getPassword();
			s = s + ",";
			s = s + x.getEmail();
			s = s + ",";
			s = s + x.getDateOfBirth();
			s = s + ",";
			for (auto &y : x.follower)
			{
				s = s + y + " ";
			}
			s = s + ",";
			for (auto &y : x.following)
			{
				s = s + y + " ";
			}
			s = s + ",\n";
			if (file.is_open())
			{
				file << s;
			}
			s = ",";
		}
	}
	else
	{
		cout << "There is a problem in writing the " << accountfile << endl;
	}
	file.close();
}

void ReadAccount()
{
	string s;
	ifstream file;
	file.open(accountfile);
	if (file.is_open())
	{
		string token;

		// The tokenizer
		while (getline(file, s))
		{
			vector<string> tokens;
			stringstream ss(s);
			while (getline(ss, token, ','))
			{
				tokens.push_back(token);
			}

			int isValid = 1;
			for (int i = 1; i <= 5; i++)
			{
				if (tokens[i].empty())
				{
					isValid = 0;
					break;
				}
			}
			if (isValid)
			{
				Account x(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
				if (!(tokens[6].empty()))
				{
					x.fieldSetter(6, tokens[6]);
				}
				if (!(tokens[7].empty()))
				{
					x.fieldSetter(7, tokens[7]);
				}
				std::stringstream s2(tokens[8]);
				// We also can use somethings like getline(s2,token,' ');
				while (getline(s2, token, ' '))
				{
					x.follower.push_back(token);
				}
				std::stringstream s3(tokens[9]);
				while (s3 >> token)
				{
					x.following.push_back(token);
				}
				db.push_back(x);
			}
			else
			{
				cout << "There is a problem in the format of the input file" << endl;
			}
		}
	}
	else
	{
		cout << "There is a problem in Reading the " << accountfile << endl;
		cout << "Go to the " << accountfile << "and add the Accounts.txt " << endl;
	}
	file.close();
	if (remove(accountfile) != 0)
	{
		cout << "There is some sort of problem with removing the account file " << endl;
	}
}

void WriteTweet()
{
	string s = ",";
	string buf;
	ofstream file;
	file.open(tweetfile);
	if (file.is_open())
	{
		for (auto &x : tweets)
		{
			s = s + x.getTweetUsername();
			s = s + ",";
			s = s + x.getTweetContent();
			s = s + ",";
			s = s + to_string(x.getlike());
			s = s + ",";
			s = s + to_string(x.getisReply());
			s = s + ",";
			s = s + to_string(x.getid());
			s = s + ",";
			s = s + to_string(x.gettoReplyId());
			s = s + ",\n";
			if (file.is_open())
			{
				file << s;
			}
			s = ",";
		}
	}
	else
	{
		cout << "There is a problem in writing the " << tweetfile << endl;
	}
	file.close();
}

void ReadTweet()
{
	string s;
	ifstream file;
	file.open(tweetfile);
	if (file.is_open())
	{
		string token;

		// The tokenizer
		while (getline(file, s))
		{
			vector<string> tokens;
			stringstream ss(s);
			while (getline(ss, token, ','))
			{
				tokens.push_back(token);
			}

			int isValid = 1;
			for (int i = 1; i <= 6; i++)
			{
				if (tokens[i].empty())
				{
					isValid = 0;
					break;
				}
			}
			if (isValid)
			{
				Tweet x(tokens[1], tokens[2], std::stoi(tokens[5]), std::stoi(tokens[4]), std::stoi(tokens[6]), std::stoi(tokens[3]));
				tweets.push_back(x);
			}
			else
			{
				cout << "There is a problem in the format of the input file" << endl;
				cout << "Go to the " << tweetfile << "and add the Accounts.txt " << endl;
			}
		}
	}
	else
	{
		cout << "There is a problem in Reading the " << tweetfile << endl;
	}
	file.close();
	if (remove(tweetfile) != 0)
	{
		cout << "There is some sort of problem with removing the account file " << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void twitPage(string &loggedInUser);
void setting(int &loginCode, string &loggedInUser);
void post(string &loggedInUser);
void profile(string &loggedInUser);
void searchPage();

void mainPage(string &loggedInUser)
{
	int loginCode = 1;
	while (loginCode)
	{
		CubbyMenu::Menu page;
		page.add_item("The twitte page", [&loggedInUser]()
					  { twitPage(loggedInUser); });

		page.add_item("Settings", [&loginCode, &loggedInUser]()
					  { setting(loginCode, loggedInUser); });

		page.add_item("Post", [&loggedInUser]()
					  { post(loggedInUser); });

		page.add_item("Profile", [&loggedInUser]()
					  { profile(loggedInUser); });

		page.add_item("Search", searchPage);

		page.print();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayProfile(string &loggedInUser, string &profileUser);
void TweetMenu(string LoggedInUser, Tweet &tweet);

void searchAccount()
{
	string input;
	cout << "Enter username, first name, or family name to search: ";
	cin.ignore();
	getline(cin, input);

	bool found = false;
	for (auto &account : db)
	{
		if (account.getUsername() == input || account.getName() == input || account.getFamilyName() == input)
		{
			string loggedInUser;
			std::string username = account.getUsername();
			displayProfile(loggedInUser, username);
			found = true;
			break;
		}
	}

	if (!found)
	{
		cout << "No account found with the given input." << endl;
	}
}

void searchTweet()
{
	string input;
	cout << "Enter tweet ID or tweet text to search: ";
	cin.ignore();
	getline(cin, input);

	bool found = false;
	for (auto &tweet : tweets)
	{
		if (to_string(tweet.getid()) == input || tweet.getTweetContent().find(input) != string::npos)
		{
			string loggedInUser;
			TweetMenu(loggedInUser, tweet);
			found = true;
			break;
		}
	}

	if (!found)
	{
		cout << "No tweet found with the given input." << endl;
	}
}

void searchPage()
{
	int i = 1;
	while (i)
	{
		CubbyMenu::Menu searchMenu;
		searchMenu.add_header("Search Page");
		searchMenu.add_item("Search Accounts", searchAccount);
		searchMenu.add_item("Search Tweets", searchTweet);
		searchMenu.add_item("Back to Main Menu", [&i]()
							{ i = 0; });

		searchMenu.print();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isValidEmail(string &email)
{
	size_t atPos = email.find('@');
	size_t dotPos = email.find('.', atPos + 1);

	if (atPos != -1 && dotPos != -1 && atPos < dotPos)
	{
		if (atPos > 0 && dotPos > atPos + 1 && dotPos < email.length() - 1)
		{
			return true;
		}
	}

	return false;
}

bool isValidPassword(string &password)
{
	if (password.length() < 8)
	{
		return false;
	}

	bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
	for (char c : password)
	{
		if (islower(c))
			hasLower = true;
		else if (isupper(c))
			hasUpper = true;
		else if (isdigit(c))
			hasDigit = true;
		else
			hasSpecial = true;
	}

	return (hasLower && hasUpper && hasDigit && hasSpecial);
}

// Left trim
static inline void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
									{ return !std::isspace(ch); }));
}

// Right trim
static inline void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
						 { return !std::isspace(ch); })
				.base(),
			s.end());
}

int attempt = 0;
void login(string &loggedInUser, int &flaglogin)
{
	string userInput;
	string password;
	cout << "You have " << 3 - attempt << " time for login" << endl;
	// 1. using special character
	// 2. suing ctrl + c
	// 3. using time
	// 4. give them some attempt

	cout << "Enter your username or email: ";
	cin >> userInput;

	cout << "Enter your password: ";
	cin >> password;
	ltrim(userInput);
	rtrim(userInput);
	ltrim(password);
	rtrim(password);

	for (auto &account : db)
	{
		if ((account.getUsername() == userInput || account.getEmail() == userInput) && (account.getPassword() == password))
		{
			if (account.getUsername() == userInput)
			{
				loggedInUser = account.getUsername();
			}
			else
			{
				loggedInUser = account.getEmail();
			}

			cout << "\nWelcome back, " << account.getName() << "!\n";
			flaglogin = 1;
			mainPage(loggedInUser);

			break;
		}
	}

	if (!flaglogin)
	{
		attempt++;
		cout << "\nLogin failed. Invalid username/email or password. Please try again.\n";
	}
	if (attempt == 3)
	{
		flaglogin = 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void addDone(string &s, int refresh)
{
	if (refresh)
	{
		s = s + "(Done)";
	}
}
// Attention : If you change the size of any array you must change the function input of signin_field as well
// component
string static comp[9];

// check whether a field just complete or not...
int static flag[8] = {0};

// The twitter fields
string static field[8];

void sendTodb(string name, string familyName, string username, string password, string email)
{

	cout << "Your SignUp has been completed" << endl;
	auto x = Account(name, familyName, username, password, email);
	if (flag[6])
	{
		x.fieldSetter(6, comp[6]);
	}
	if (flag[7])
	{
		x.fieldSetter(7, comp[7]);
	}
	db.push_back(x);
}

int signInFields(int i, string (&field)[8], int (&flag)[8], string (&comp)[9])
{
	// -------------------------A Boosted & Compact Cin----------------------
	int flager = 1;
	int refresh = 1;
	if (flag[i] == 1)
	{

		CubbyMenu::Menu Y;
		Y.add_header("You had done this field do you want to edit it ?");
		Y.add_item("Yes", [&refresh]()
				   { refresh = 0; });
		Y.add_item("No", [&flager]()
				   { flager = 0; });
		Y.print();
	}

	if (flager)
	{
		cout << "Enter Your " << field[i] << endl;
		cin >> comp[i];
		int flag2 = 1;
		if (i == 3)
		{
			// I want to check the existance of the username
			for (Account x : db)
			{
				if (!(comp[i].compare(x.getUsername())))
				{
					flag2 = 0;
					break;
				}
			}
		}
		bool a = true;
		bool b = true;
		// cout << i << comp[i] << endl;
		if (i == 4)
		{
			a = isValidPassword(comp[4]);
		}
		if (i == 5)
		{
			b = isValidEmail(comp[5]);
		}
		if (flag2 && a && b)
		{
			cout << "Done" << endl;
			addDone(field[i], refresh);
			flag[i] = 1;
			return 1;
		}
		else
		{
			if (i == 4)
			{
				cout << "Sorry You choose an Inappropriate Password! The Standard Password is at least 8 characters and has at least one numeric character, one lowercase character, one uppercase character and one special character!" << endl;
				return 0;
			}

			if (i == 5)
			{
				cout << "Your email address is invalid!" << endl;
				return 0;
			}
			if (i == 3)
			{
				cout << "Your Username is not unique!" << endl;
				return 0;
			}
		}
	}
	return 0;
}
void passwordRefresher(int &r)
{

	string userInput;
	string password;
	int flagx = 0;
	Account *y;
	while (r)
	{

		cout << "Enter your username or email: ";
		cin >> userInput;

		cout << "Enter your password: ";
		cin >> password;

		for (auto &account : db)
		{
			if ((account.getUsername() == userInput || account.getEmail() == userInput) && (account.getPassword() == password))
			{
				y = &account;
				flagx = 1;
				r = 0;
				break;
			}
		}
		if (flagx)
		{
			int x = 1;
			string s1;
			bool a = false;
			while (x)
			{
				cout << "Enter Your New Password" << endl;
				cin >> s1;
				cin.ignore();
				a = isValidPassword(s1);
				if (a)
				{
					if (!(s1.compare(y->getPassword())))
					{
						cout << "Sorry Your password is the same as your previous one!" << endl;
					}
					else
					{
						y->fieldSetter(4, s1);
						cout << "Your password has changed successfully." << endl;
						x = 0;
					}
				}
				else
				{
					cout << "Sorry You choose an Inappropriate Password! The Standard Password is at least 8 characters and has at least one numeric character, one lowercase character, one uppercase character and one special character!" << endl;
				}
			}
		}
		else
		{
			cout << "Wrong Username or Password , Try again ... " << endl;
		}
	}
}

void signUp()
{
	int r = 1;
	int z = 1;
	while ((!flag[1] || !flag[2] || !flag[3] || !flag[4] || !flag[5]) && z)
	{
		CubbyMenu::Menu sign;
		sign.add_header("----------SignUp Menu----------");
		sign.add_item(field[1], [&]()
					  { signInFields(1, field, flag, comp); });
		sign.add_item(field[2], [&]()
					  { signInFields(2, field, flag, comp); });
		sign.add_item(field[3], [&]()
					  { signInFields(3, field, flag, comp); });
		sign.add_item(field[4], [&]()
					  { signInFields(4, field, flag, comp); });
		sign.add_item(field[5], [&]()
					  { signInFields(5, field, flag, comp); });
		sign.add_item(field[6], [&]()
					  { signInFields(6, field, flag, comp); });
		sign.add_item(field[7], [&]()
					  { signInFields(7, field, flag, comp); });
		sign.add_item("Do you forget your password ?", [&r]()
					  { passwordRefresher(r); });
		sign.add_item("Back to Menu", [&z]()
					  { z = 0; });

		sign.print();
	}
	if (z == 1)
	{
		sendTodb(comp[1], comp[2], comp[3], comp[4], comp[5]);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void changeInfo(string &loggedInUser)
{
	int j = 1;
	int k = 100;
	string s;
	Account *y = nullptr;
	int index1;
	int w;
	for (auto &x : db)
	{
		if (!(x.getUsername().compare(loggedInUser)))
		{
			y = &x;
			break;
		}
	}
	while (j)
	{

		CubbyMenu::Menu change;
		change.add_header("What do you want to change ?");
		for (int i = 1; i <= 7; i++)
		{
			change.add_item(field[i], [&, i]()
							{w = signInFields(i, field, flag, comp) ;cin.ignore(); index1=i ; });
		}
		change.add_item("Back to Settings", [&j]()
						{ j = 0; });
		change.print();
		if (w)
		{
			y->fieldSetter(index1, comp[index1]);
		}
	}
}
void setting(int &loginCode, string &loggedInUser)
{
	int i = 1;
	while (i)
	{
		CubbyMenu::Menu page;
		page.add_item("Click for Logout", [&i, &loginCode]()
					  { i = 0, loginCode = 0; });
		page.add_item("Change The Personal Information", [&loggedInUser]()
					  { changeInfo(loggedInUser); });
		page.add_item("Return Back To menu", [&i]
					  { i = 0; });
		page.print();
	}
}

void post(string &loggedInUser)
{
	if (loggedInUser.empty())
	{
		cout << "You're not logged in! Please log in first." << endl;
		return;
	}

	string content;
	cout << "Enter tweet content: ";
	cin.ignore();
	getline(cin, content);
	id++;
	int isReply = 0;
	tweets.push_back(Tweet(loggedInUser, content, id, isReply));
	cout << "Your tweet posted successfully!" << endl;
}

void DeleteTweet(Tweet &tweet)
{
	int i = 0;
	for (auto x : tweets)
	{
		if (!(tweet.getTweetUsername().compare(x.getTweetUsername())))
		{
			if (!(tweet.getTweetContent().compare(x.getTweetContent())))
			{
				break;
			}
		}
		i++;
	}
	tweets.erase(tweets.begin() + i);
}

void DoReply(string LoggedInUser, Tweet &tweet)
{
	cout << "Write your Reply" << endl;
	string content;
	cin >> content;
	cin.ignore();
	id++;
	int isReply = 1;
	tweets.push_back(Tweet(LoggedInUser, content, id, isReply, tweet.getid(), 0));
}

void showReply(Tweet &tweet)
{

	CubbyMenu::Menu Twits;
	string username;
	for (auto x : tweets)
	{
		if (x.gettoReplyId() == tweet.getid())
		{
			if (x.getisReply())
			{
				Twits.add_item(x.getTweetUsername() + ":" + x.getTweetContent(), [username = x.getTweetUsername(), &x]()
							   { TweetMenu(username, x); });
			}
		}
	}

	Twits.print();
}

void TweetMenu(string LoggedInUser, Tweet &tweet)
{

	CubbyMenu::Menu page;
	page.add_header("What you want to do with this tweet ?");
	page.add_item("Do Reply", [&LoggedInUser, &tweet]()
				  { DoReply(LoggedInUser, tweet); });
	page.add_item("Show Replies", [&tweet]()
				  { showReply(tweet); });
	page.add_item("Like the tweet", [&tweet]()
				  { tweet.like(); });
	if (!(tweet.getTweetUsername().compare(LoggedInUser)))
	{
		page.add_item("Delete the tweet", [&tweet]()
					  { DeleteTweet(tweet); });
	}
	page.print();
}

void twitPage(string &loggedInUser)
{
	if (tweets.empty())
	{
		cout << "No tweets available now!" << endl;
		return;
	}

	CubbyMenu::Menu Twits;
	for (auto &tweet : tweets)
	{
		Twits.add_item(tweet.getTweetUsername() + ":" + tweet.getTweetContent(), [&loggedInUser, &tweet]()
					   { TweetMenu(loggedInUser, tweet); });
	}
	Twits.print();
}

void followUser(string &loggedInUser, string &profileUser);

void displayProfile(string &loggedInUser, string &profileUser)
{
	bool isFollowing = false;

	for (auto &account : db)
	{
		if (account.getUsername() == profileUser)
		{
			cout << "Name: " << account.getName() << " " << account.getFamilyName() << endl;
			cout << "Username: " << account.getUsername() << endl;

			cout << "Tweets:" << endl;
			for (auto &tweet : tweets)
			{
				if (tweet.getTweetUsername() == profileUser)
				{
					cout << tweet.getTweetContent() << endl;
				}
			}

			cout << "Followers:" << endl;
			for (const auto &follower : account.follower)
			{
				cout << follower << endl;
			}

			cout << "Following:" << endl;
			for (const auto &following : account.following)
			{
				cout << following << endl;
			}

			for (const auto &follower : account.follower)
			{
				if (follower == loggedInUser)
				{
					isFollowing = true;
					break;
				}
			}

			if (!isFollowing)
			{
				cout << "Follow this user? (y/n): ";
				char choice;
				cin >> choice;
				if (choice == 'y')
				{
					followUser(loggedInUser, profileUser);
					cout << "You are now following " << profileUser << endl;
				}
			}
			else
			{
				cout << "You are already following this user." << endl;
			}

			break;
		}
	}
}

void followUser(string &loggedInUser, string &profileUser)
{
	for (auto &account : db)
	{
		if (account.getUsername() == loggedInUser)
		{
			account.addFollowing(profileUser);
		}
		if (account.getUsername() == profileUser)
		{
			account.addFollower(loggedInUser);
		}
	}
}

void profile(string &loggedInUser)
{
	if (loggedInUser.empty())
	{
		cout << "You're not logged in! Please log in first." << endl;
		return;
	}

	string profileUser;
	cout << "Enter the username of the profile you want to view: ";
	cin >> profileUser;

	displayProfile(loggedInUser, profileUser);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void twitterLogo()
{
	int loginCode = 1;
	string loggedInUser;
	int flaglogin = 0;
	while (!flaglogin)
	{
		login(loggedInUser, flaglogin);
	}
	while (loginCode && flaglogin)
	{
		CubbyMenu::Menu page;
		cout << "-------------------------------------" << endl;
		cout << "__ __|        _) |   |             " << endl;
		cout << "   |\\ \\  \\   / | __| __|  _ \\  __| " << endl;
		cout << "   | \\ \\  \\ /  | |   |    __/ |   " << endl;
		cout << "  _|  \\_/\\_/  _|\\__|\\__|\\___|_|  " << endl;
		cout << "-------------------------------------" << endl;

		page.add_item("The twitte page", [&loggedInUser]()
					  { twitPage(loggedInUser); });

		page.add_item("Settings", [&loginCode, &loggedInUser]()
					  { setting(loginCode, loggedInUser); });

		page.add_item("Post", [&loggedInUser]()
					  { post(loggedInUser); });

		page.add_item("Profile", [&loggedInUser]()
					  { profile(loggedInUser); });

		page.add_item("Search", searchPage);
		page.print();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	ReadAccount();
	ReadTweet();
	field[1] = "Name";
	field[2] = "FamilyName";
	field[3] = "Username ";
	field[4] = "Password";
	field[5] = "Email";
	field[6] = "Date Of Birth";
	field[7] = "Gender";
	int j = 1;
	db.push_back(Account("root", "root", "root", "Ab@123456", "root@root.com"));

	while (j)
	{
		CubbyMenu::Menu menu;
		menu.add_header("---------AP-Twitter-Project---------");
		cout << "Do not use ctrl + C for terminating the program just use Exit provided here" << endl;
		menu.add_item("Login", []()
					  {
            string loggedInUser;
            int flaglogin = 0;
            login(loggedInUser, flaglogin); });
		menu.add_item("Sign Up", &signUp);

		menu.add_item("Exit", [&j]()
					  { j = 0; });

		menu.print();
	}

	WriteAccounts();
	WriteTweet();
}
