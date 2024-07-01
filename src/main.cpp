#include "include/CubbyMenu.hpp"

#include <iostream>
#include <vector>

using namespace std;

// Done Mechanism is not work properly

vector<class Account> db;
vector<class Tweet> tweets;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Account
{
private:
	string name;
	string familyName;
	string username;
	string email;
	string password;
	string dateOfBirth;
	string gender;

public:
	vector<string>follower ;
	vector<string>following ;
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
	void fieldSetter(int i, string s){
		switch(i) {
		case 6:
			this->gender = s ; 
		break;
		case 7: 
			this->dateOfBirth = s ;
			break ;
		}
	}
};

class Tweet
{
private:
	string username;
	string content;
	int likenum = 0 ; 
public:
	Tweet(string username, string content)
	{
		this->username = username;
		this->content = content;
	}

	string getTweetUsername()
	{
		return username;
	}

	string getTweetContent()
	{
		return content;
	}
	void like(){
		likenum++; 
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isValidEmail(string &email)
{
	bool hasAt = false, hasDot = false;
	for (char c : email)
	{
		if (c == '@')
			hasAt = true;
		if (hasAt && c == '.')
			hasDot = true;
	}

	return (hasAt && hasDot);
}

bool isValidPassword(string &password)
{
	if (password.length() < 8)
		return false;

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

void login(string &loggedInUser,int &flaglogin)
{
	string userInput;
	string password;

	cout << "Enter your username or email: ";
	cin >> userInput;

	cout << "Enter your password: ";
	cin >> password;

	for (auto &account : db)
	{
		if ((account.getUsername() == userInput || account.getEmail() == userInput) && (account.getPassword() == password))
		{
			loggedInUser = account.getUsername(); // Set the loggedInUser to the found username
			cout << "\nWelcome back, " << account.getName() << "!\n";
			flaglogin = 1;
			break;
		}
	}

	if (!flaglogin)
	{
		cout << "\nLogin failed. Invalid username/email or password. Please try again.\n";
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
string comp[9];

// check whether a field just complete or not...
int flag[8] = {0};

// The twitter fields
string field[8];


void sendTodb(string name, string familyName, string username, string password,string email)
{

	cout << "Your SignUp has been complited" << endl;
	auto x = Account(name, familyName, username, password,email);
	if(flag[6]){
			x.fieldSetter(6,comp[6]) ; 
}
	if(flag[7]){
		x.fieldSetter(7,comp[7]);
	}
	db.push_back(x);
}

void signInFields(int i, string (&field)[8], int (&flag)[8], string (&comp)[9])
{
	// A Boosted Cin
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
				if (comp[i].compare(x.getUsername()))
				{
					flag2 = 0;
					break;
				}
			}
		}
		if (flag2)
		{
			cout << "Done" << endl;
			addDone(field[i], refresh);
			flag[i] = 1;
		}
	}
}

void signUp()
{

	while (!flag[1] || !flag[2] || !flag[3] || !flag[4] || !flag[5])
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

		sign.print();
	}

	sendTodb(comp[1], comp[2], comp[3], comp[4],comp[5]);
}

////////////////////////////////////////////////////////////////////////////////////////////
void setting(int &loginCode)
{
	int i = 1;
	while (i)
	{
		CubbyMenu::Menu page;
		page.add_item("Click for Logout", [&i, &loginCode]()
					  { i = 0, loginCode = 0; });
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
	tweets.push_back(Tweet(loggedInUser, content));
	cout << "Your tweet posted successfully!" << endl;
}
void DeleteTweet(Tweet &tweet){
	int i = 0 ; 
	for(auto x : tweets){
		if(!(tweet.getTweetUsername().compare(x.getTweetUsername()))){
				if(!(tweet.getTweetContent().compare(x.getTweetContent()))){
					break ; 
				}
				}
				i++ ;
				}
				tweets.erase(tweets.begin() + i );
}
void TweetMenu(string LoggedInUser,Tweet &tweet){
	
	CubbyMenu::Menu page;
	page.add_header("What you want to do with this tweet ?"); 
	page.add_item("Like the tweet" ,[&tweet](){tweet.like();});
	if(!(tweet.getTweetUsername().compare(LoggedInUser))){
		page.add_item("Delete the tweet" ,[&tweet](){DeleteTweet(tweet);}) ; 
	}
	page.print() ; 
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
		Twits.add_item( tweet.getTweetUsername() + ":"+ tweet.getTweetContent() , [&loggedInUser,&tweet](){TweetMenu(loggedInUser,tweet);});
	}
	Twits.print();
}

void profile(string &loggedInUser)
{
	if (loggedInUser.empty())
	{
		cout << "You're not logged in! Please log in first." << endl;
		return;
	}

	for (auto &account : db)
	{
		if (account.getUsername() == loggedInUser)
		{
			cout << "Name: " << account.getName() << endl;
			cout << "Family Name: " << account.getFamilyName() << endl;
			cout << "Email: " << account.getEmail() << endl;
			cout << "Date of Birth: " << account.getDateOfBirth() << endl;
			cout << "Gender: " << account.getGender() << endl;
			return;
		}
	}

	cout << "Error: User profile not found!" << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void twitterLogo()
{
	int loginCode = 1;
	string loggedInUser;
	int flaglogin = 0 ; 
	while(!flaglogin) {
		login(loggedInUser,flaglogin) ; 
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

		page.add_item("The twitte page",[&loggedInUser] (){twitPage(loggedInUser);});

		page.add_item("Settings", [&loginCode]()
					  { setting(loginCode); });

		page.add_item("Post", [&loggedInUser]()
					  { post(loggedInUser); });

		page.add_item("Profile", [&loggedInUser]()
					  { profile(loggedInUser); });

		page.print();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int exitcode = 1;
	field[1] = "Name";
	field[2] = "FamilyName";
	field[3] = "Username ";
	field[4] = "Password";
	field[5] = "Email";
	field[6] = "Date Of Birth";
	field[7] = "Gender";
	

	while (exitcode)
	{
		CubbyMenu::Menu menu;
		menu.add_header("---------AP-Twitter-Project---------");

		menu.add_item("Login", &twitterLogo);

		menu.add_item("SignUp", &signUp);

		menu.add_item("Exit", [&exitcode]()
					  { exitcode = 0; });

/*
		menu.add_item("Post", [&loggedInUser]()
					  { post(loggedInUser); });

		menu.add_item("View Tweets", twitPage);

		menu.add_item("Profile", [&loggedInUser]()
					  { profile(loggedInUser); });
*/
		menu.print();
	}
}
