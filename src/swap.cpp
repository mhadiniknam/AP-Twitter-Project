void changeField(string &loggedInUser){
	int j = 1 ; 
	CubbyMenu::Menu change;
	int k = 100 ;
	string s ; 
	Account * y = nullptr ;
	int index1;
	for(auto &x : db){
		if(!(x.getUsername().compare(loggedInUser))){
			y = &x ;
			break ; 
		}
	}
	change.add_header("What do you want to change ?");
	while(j){
		for(int i = 1 ; i <= 7 ; i++ ) {
			change.add_item(field[i], [&s,&index1,&i]()
					// Here I could use signInFields but I'd prefere to make the changes in Setter 
					{cin >> s ;cin.ignore(); index1=i ;});
		}
		change.add_item("Back to Settings",[&j](){j = 0;});
		change.print() ;
		//int w = y->fieldSetter(index1 , s ); 

	}
}
void setting(int &loginCode,string &loggedInUser)
{
	int i = 1;
	while (i)
	{
		CubbyMenu::Menu page;
		page.add_item("Click for Logout", [&i, &loginCode]()
				{ i = 0, loginCode = 0; });
		page.add_item("Change the field", [&loggedInUser]()
				{changeField(loggedInUser);});
		page.add_item("Return Back To menu", [&i]
				{ i = 0; });
		page.print();
	}
}

		int fieldSetter(int i, string s){
			switch(i) {
				case 1 :
					this->name = s ; 
					break ;
				case 2 :
					this->familyName = s ;
					break ;
				case 3 :
					for (Account x : db)
					{
						if (comp[i].compare(x.getUsername()))
						{
							flagx = 0;
							break;
						}
					}
					if(flagx){
						this->username = s ;
						return 1;
					}else{
						return 0;
					}
					break ;
				case 4 :
					if(isValidEmail(s)){
						this->email = s; 
						return 1; 
					}else{
						return 0; 
					}
					break ;
				case 5 :
					if(isValidPassword(s)){
						this->password = s ;
						return 1; 
					}else{
						return 0 ;
					}
					break ;
				case 6:
					this->gender = s ; 
					return 1; 
					break;
				case 7: 
					this->dateOfBirth = s ;
					return 1; 
					break ;
			}
		}
		page.add_item("Settings", [&loginCode, &loggedInUser]()
				{ setting(loginCode,loggedInUser); });
