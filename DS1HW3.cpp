# include <iostream>
# include <string>
using namespace std;

class Node {
	public:
		string str;
		Node *next;
		Node( string strr ) {
			str = strr;
			next = NULL;
		}

		Node( string strr, Node *nextN ) {
			str = strr;
			next = nextN;
		}

};

class List {
	private:
		Node *head;
		int size = 0;
	public:
		List( string str ) {
			head = new Node(str);
		}

		void append( string str ) {
			Node *cur = head;
			while ( cur -> next != NULL ) {
				cur = cur -> next;
			}
			size++;
			cur -> next = new Node(str);
		} // append
		

		void insert( string str, int pos ) {
			if ( pos == 0 ) {
				Node* newHead= new Node(str,head);
				head = newHead;
				size++;
			} else {
				Node *cur = head, *temp = NULL;
				for ( int i = 0 ; i < pos ; i++ ) {
					temp = cur;
					cur = cur -> next;
				}

				Node *putIn = new Node( str, cur );
				temp -> next = putIn;
				size++;
			} // else
			  //
			  
		} // insert
		  
		void printAll() {
			Node* cur = head;
			while ( cur != NULL ) {
				cout << cur->str<< " " ;
				cur = cur -> next;
			} // while
			  //
			cout << endl;
		} // printAll()
		  //

		void deleteByPos( int pos ) {
			Node *cur = head, *temp = NULL;
			if ( pos == 0 ) {
				temp = head;
				head = head -> next;
				delete temp;
			} else {
				for ( int i = 0 ; i < pos ; i++ ) {
					temp = cur;
					cur = cur -> next;
				} // for
				
				temp -> next = cur -> next;
				delete cur;
			} // else
		} // deleteByPosition
};// List
 

bool isDigit( char ch ) {
	if ( ch >= '0' && ch <= '9' ) return true;
	return false;
} // isDigit
bool isLegalSig( char ch ) {
	if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) return true;
	return false;
}

int isParenthesis( char ch ) {
	if ( ch == '(' ) return 1;
	else if ( ch == ')' ) return 2;
	else return 0;
}

bool isLegal( char ch ) {
	if ( isDigit( ch ) || isLegalSig( ch ) || isParenthesis(ch) ) return true;
	return false;
}

bool cmdCorrect( string str ) {
	if ( str == "0" || str == "1" ) return true;
	cout << "Error!!!!!!!" << endl;
	return false;
} // check if the cmd correct.

string removeSpace( string str ) {
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( str[i] == ' ' || str[i] == '\t' ) {
			str.erase( str.begin() + i );
			i--;
		}
	}
	return str;
}

int checkError( string str ) {
	// error1
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( !isLegal( str[i] )) {
			cout << str[i] << "is not legal" << endl;
			return 1;
		}
	}

	// error2
	int count = 0;
	for ( int i = 0 ; i < len ; i++ ) {
		if ( str[i] == '(' ) count++;
	       	else if ( str[i] == ')' ) count--;
		else if ( count < 0 ) {
			cout << "Extra close parenthesis" << endl;
			return 2;
		}
	} 

	if ( count != 0 ) {
		cout << "Extra open parenthesis" << endl;
		return 2;
	}

	// error3
	for ( int i = 0 ; i < len ; i++ ) {
		if ( i == len - 1 ) {
			if ( !( isDigit(str[i]) || isParenthesis(str[i]) == 2)) {
				if ( isLegalSig( str[i] )){
				cout << "one Extra operater" << endl;
				return 3;
				}
			}
		}

		else {
			if ( isDigit( str[i] ) ){
				if ( !(isDigit( str[i+1] )|| isLegalSig( str[i+1]) || isParenthesis( str[i+1] )== 2) ) {
						cout << "not infix" << endl;
						return 3;
				}
			}

			else if (  isLegalSig( str[i]) ) {
				if ( !( isDigit( str[i+1]) || isParenthesis( str[i+1] ) ) ) {
					cout << "not infix" << endl;
					return 3;
				}
			}

			else if ( isParenthesis( str[i] ) == 1 )  {
				if ( ! ( isDigit( str[i+1] ) || isParenthesis( str[i+1] == 1 ))) {
					cout << "not infix" << endl;
					return 3;
				}
			}

			else if ( isParenthesis( str[i] ) == 2 ) {
				if ( !( isParenthesis( str[i+1]) || isLegalSig( str[i+1] ) ) ) {
					cout << "not infix" << endl;
					return 3;
				}
			}

		} // else
	} // for

	  	return 0;
} // checkerror

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
		if ( !checkError( str ) ) {
		//	toPostfix( str )
		cout << checkError(str);
		cout << str;
		}
		cmd = readCmd();
		cin.get();
	} //while
} // main()
