#include "include/CubbyMenu.hpp"

#include <iostream>
#include <vector>

using namespace std;

// Done Mechanism is not work properly

vector<class Account> db;

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
	Account(string name, string familyName, string username, string email, string password, string dateOfBirth = "", string gender = "")
	{
		this->name = name;
		this->familyName = familyName;
		this->username = username;
		this->email = email;
		this->password = password;
		this->dateOfBirth = dateOfBirth;
		this->gender = gender;
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

void login(string &loggedInUser)
{
	string userInput;
	string password;

	cout << "Enter your username or email: ";
	cin >> userInput;

	cout << "Enter your password: ";
	cin >> password;

	bool found = false;
	for (auto &account : db)
	{
		if ((account.getUsername() == userInput || account.getEmail() == userInput) && (account.getPassword() == password))
		{
			loggedInUser = account.getUsername(); // Set the loggedInUser to the found username
			cout << "\nWelcome back, " << account.getName() << "!\n";
			found = true;
			break;
		}
	}

	if (!found)
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

void sendTodb(string name, string familyName, string username, string password)
{

	cout << "Your SignUp has been complited" << endl;
	db.push_back(Account(name, familyName, username, password));
}

void signInFields(int i, string (&field)[4], int (&flag)[5], string (&comp)[5])
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

// Attention : If you change the size of any array you must change the function input of signin_field as well
// component
string comp[5];

// check whether a field just complete or not...
int flag[5] = {0};

// The twitter fields
string field[4];

void signUp()
{

	while (!flag[1] || !flag[2] || !flag[3] || !flag[4])
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
		sign.print();
	}

	sendTodb(comp[1], comp[2], comp[3], comp[4]);
}

void twitPage()
{
}

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

void post()
{
}

void profile()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void twitterLogo()
{
	int loginCode = 1;

	while (loginCode)
	{
		CubbyMenu::Menu page;
		cout << "-------------------------------------" << endl;
		cout << "__ __|        _) |   |             " << endl;
		cout << "   |\\ \\  \\   / | __| __|  _ \\  __| " << endl;
		cout << "   | \\ \\  \\ /  | |   |    __/ |   " << endl;
		cout << "  _|  \\_/\\_/  _|\\__|\\__|\\___|_|  " << endl;
		cout << "-------------------------------------" << endl;
		page.add_item("The twitte page", &twitPage);
		page.add_item("Settings", [&loginCode]()
					  { setting(loginCode); });

		page.add_item("Post", &post);
		page.add_item("Profile", &profile);

		page.print();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int exitcode = 1;
	// field[1] = "Name";
	// field[2] = "FamilyName";
	// field[3] = "Username ";
	// field[4] = "Password";
	string loggedInUser;

	while (exitcode)
	{
		CubbyMenu::Menu menu;
		menu.add_header("---------AP-Twitter-Project---------");

		menu.add_item("Login", [&loggedInUser]()
					  { login(loggedInUser); });
		menu.add_item("SignUp", &signUp);
		menu.add_item("Exit", [&exitcode]()
					  { exitcode = 0; });

		menu.print();
	}
}
