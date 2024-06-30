#include "CubbyMenu/CubbyMenu.hpp"

#include <iostream>
#include <vector> 

// Done Mechanism is not work properly 

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
		string UsernameGetter(){
			return username ;
		}
};

void login()
{
	/*--- Yours ---*/
}
void addDone(string &s,int refresh){
	if(refresh){
		s = s + "(Done)"; 
	}
}
void SendTodb(string name , string familyname , string username , string password ){

	cout << "Your SignUp has been complited" << endl ; 
	db.push_back(Account(name,familyname, username, password) ) ; 
}
void signin_fields(int i, string(&field)[4], int(&flag)[5], string(&comp)[5]) {
	// A Boosted Cin 	
	int flager = 1 ; 
	int refresh = 1 ; 
	if(flag[i] == 1 ) { 

		CubbyMenu::Menu Y;
		Y.add_header("You had done this field do you want to edit it ?");
		Y.add_item("Yes",[&refresh](){refresh = 0;});
		Y.add_item("No",[&flager](){flager = 0 ;});
		Y.print() ;	
	}
	if(flager) {
		cout << "Enter Your " << field[i] << endl;
		cin >> comp[i];
		int  flag2 = 1 ; 
		if(i == 3 ){
			// I want to check the existance of the username 
			for(Account x : db ) {
				if(comp[i].compare(x.UsernameGetter())){
					flag2 = 0 ; 
					break ; 
				}
			}
		}
		if(flag2) {
			cout << "Done" << endl;
			addDone(field[i],refresh);
			flag[i] = 1;
		}
	}
}
// Attention : If you change the size of any array you must change the function input of signin_field as well 
// component 
string comp[5] ;

// check whether a field just complete or not...
int flag[5] = {0} ; 

//The twitter fields
string field[4]  ;

void SignUp(){


	while(!flag[1] || !flag[2] || !flag[3] || !flag[4]){ 
		CubbyMenu::Menu sign;
		sign.add_header("----------SignUp Menu----------");
		sign.add_item(field[1], [&]() {signin_fields(1,field,flag,comp) ; });
		sign.add_item(field[2], [&]() { signin_fields(2,field,flag,comp) ; } );
		sign.add_item(field[3], [&]() { signin_fields(3,field,flag,comp); } );
		sign.add_item(field[4], [&]() {signin_fields(4,field,flag,comp) ; });
		sign.print() ; 
	}

	SendTodb(comp[1] , comp[2] ,comp[3] ,comp[4]) ; 
}
void TwitPage(){

}
void Setting(int &logincode){
int i = 1; 
	while(i){
CubbyMenu::Menu page;
			page.add_item("Click for Logout",[&i,&logincode](){ i = 0 , logincode = 0 ; } );
			page.add_item("Return Back To menu",[&i]{ i= 0 ;});
			page.print();
}
}
void Post(){

}
void Profile(){

}
void twitter(){
	int logincode =  1;

	while(logincode){
		CubbyMenu::Menu page;
		cout << "-------------------------------------" << endl ;
		cout << "__ __|        _) |   |             " << endl ; 
		cout << "   |\\ \\  \\   / | __| __|  _ \\  __| " << endl;
		cout << "   | \\ \\  \\ /  | |   |    __/ |   " << endl ; 
	        cout << "  _|  \\_/\\_/  _|\\__|\\__|\\___|_|  " << endl ;
		cout << "-------------------------------------" << endl ; 	
		page.add_item("The twitte page", &TwitPage );
		page.add_item("Settings", [&logincode](){ Setting(logincode);} );

		page.add_item("Post",&Post);
		page.add_item("Profile",&Profile);

		page.print();
	}
}

int main()
{
	int exitcode = 1 ; 
	field[1] = "Name" ;
	field[2] = "FamilyName";
	field[3] = "Username " ;
	field[4] = "Password";

	while(exitcode){
		CubbyMenu::Menu menu;
		menu.add_header("---------AP-Twitter-Project---------");

		menu.add_item("Login", &twitter );
		menu.add_item("SignUp",&SignUp);
		menu.add_item("Exit", [&exitcode](){ exitcode = 0 ;} );


		menu.print();
	}
}
