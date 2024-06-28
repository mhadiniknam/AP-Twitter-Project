#include "D:\AUT doc\Project\AP-Twitter-Project\include\CubbyMenu.hpp"

#include <iostream>
#include <vector> 

using namespace std ; 

vector <class Account> db ; 

class Account{
	private : 
		string name ; 
		string familyname; 
		string username; 
		string password ;
	public : 
		Account(string name , string familyname , string username , string password ){
			this->name = name ; 
			this->familyname = familyname ; 
			this->username = username ; 
			this->password = password ;
		}	

};

void login()
{
	/*--- Yours ---*/
}
void addDone(string &s){
	s = s + "(Done)"; 
}
void SignUpEnter(string name , string familyname , string username , string password ){

}

void SignUp(){
	/*
	CubbyMenu::Menu sign;
	sign.add_header("----------SignUp Menu----------");

	string name ; 
	string familyname ;
	string username ; 
	string password ;
	int flags[5] = {0} ; 

	string field[4]  ;
	field[1] = "1. Name" ;
	field[2] = "2. FamilyName";
	field[3] ="3. username " ;
	field[4] ="4. Password";

	sign.add_item(field[1],( 
			cout << "Enter Your name" << endl  ;
			cin >> name ;
			cout << "Done" << endl ;	
			addDone(field[4]);
			flag[4]++ ; )	);

	sign.add_item(field[2],{
			cout << "Enter Your FamilyName" ;
			cin >> familyname ;
			cout << "Done" << endl ;
			addDone(field[2]);
			flag[2]++ ; 
			}	);

	sign.add_item(field[3],{
			cout << "Enter Your Username" ;
			cin >> familyname ;
			cout << "Done" << endl ;	
			addDone(field[3]);
			flag[3]++ ;
		    	}
		     );

	sign.add_item(field[4],{
			cout << "Enter Your Password" ;
			cin >> familyname ;
			cout << "Done" << endl ;
			addDone(field[4]);
			flag[4]++ ; 
			}    );
	if(flag[1] && flag[2] && flag[3] && flag[4] ) {
		sign.add_item("SEND" , &SignUpEnter(string name , string familyname , string username , string password ));
	}
	*/
}
void Exit(){
	cout << "Have a great time!" << endl ; 
	exit(0) ;
}
int main()
{
	CubbyMenu::Menu menu;
	menu.add_header("---------AP-Twitter-Project---------");

	menu.add_item("Login", &login );
	menu.add_item("SignUp",&SignUp);
	menu.add_item("Exit", &Exit   );

	menu.print();
}
