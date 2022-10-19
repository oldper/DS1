# include <iostream>
# include <string>
using namespace std;
	
bool cmdCorrect( string str ) {
	if ( str == "0" || str == "1" ) return true;
	cout << "Error!!!!!!!" << endl;
	return false;
} // check if the cmd correct.

string removeSpace( string str ) {
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( str[i] == ' ' ) str.erase( str.begin() + i );
	}
	return str;
}

string readCmd() {
	string cmd;
	do {
		cin >> cmd;
	} while ( !cmdCorrect( cmd ) );
	return cmd;
} // readCMD

int main() {
	cout << "-------------------------------" << endl;
	cout << "1. start" << endl;
	cout << "0. quit" << endl;
	cout << "-------------------------------" << endl;
	string cmd = readCmd();
	cin.get();

	while ( cmd != "0" ) { 
		string str;
		cout << "Input infix natation" << endl;	
		getline(cin,str);
		str = removeSpace( str );
		cout << str << endl;
		cmd = readCmd();
		cin.get();
	} //while
	  //
} // main()
