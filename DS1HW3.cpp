# include <iostream>
# include <string>
using namespace std;
class Node {
        public:
                string str="";
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

class Stack {
	public:
		Node *head = NULL;
		
		void push( string str ) {
			if ( head == NULL ) head = new Node( str );
			else {
				Node *node = new Node( str, head );
				head = node;
			}
		} // push
		  //
		int size() {
			Node *cur = head;
			int count = 0;
			while ( cur != NULL ) {
				count++;
				cur = cur->next;
			}

			return count;
		} // size
	
		bool isEmpty() {
			return head == NULL;
		}

		void pop() {
			if (head != NULL) {
				Node *temp = head;
				head = head->next;
				delete temp;
			}
		} // pop
		  //
		string top() {
			if ( head != NULL ) {
				return head -> str;
			} else return "";
		}
};



class List {
	public:
		Node *head = NULL;

		void append( string str ) {
			if ( head == NULL ) {
				head = new Node(str);
			} else {
				Node *cur = head;
				while ( cur -> next != NULL ) {
					cur = cur -> next;
				}
				cur -> next = new Node(str);
				
			}
		} // append
		

		void insert( string str, int pos ) {
			if ( pos == 0 ) {
				Node* newHead= new Node(str,head);
				head = newHead;
			} else {
				Node *cur = head, *temp = NULL;
				for ( int i = 0 ; i < pos ; i++ ) {
					temp = cur;
					cur = cur -> next;
				}

				Node *putIn = new Node( str, cur );
				temp -> next = putIn;
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
		  //
		int size() {
			int count = 0;
			Node *cur = head;
			while ( cur != NULL ) {
				count++;
				cur = cur -> next;
			}

			return count;
		}
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

bool cmdCorrect( string str , int mode ) {
	if ( str == "0" || str == "1" ) return true;
	if ( mode == 1 ) cout << "Error!!!!!!!" << endl;
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
	// error
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( !isLegal( str[i] )) {
			cout << str[i] << "Error 1 is not legal" << endl;
			return 1;
		}
	}

	// error2
	int count = 0;
	for ( int i = 0 ; i < len ; i++ ) {
		if ( str[i] == '(' ) count++;
	       	else if ( str[i] == ')' ) count--;
		else if ( count < 0 ) {
			cout << "Error 2 Extra close parenthesis" << endl;
			return 2;
		}
	} 

	if ( count != 0 ) {
		cout << "Error 2 Extra open parenthesis" << endl;
		return 2;
	}

	// error3
	for ( int i = 0 ; i < len ; i++ ) {
		if ( i == len - 1 ) {
			if ( !( isDigit(str[i]) || isParenthesis(str[i]) == 2)) {
				if ( isLegalSig( str[i] )){
				cout << "Error 3 one Extra operater" << endl;
				return 3;
				}
			}
		}
	
		else if ( i == 0 ) {
			if ( isLegalSig( str[i] ) ) {
				cout << "Error 3 extra operator" << endl;
				return 3;
			}
		}
		else if ( isDigit( str[i] ) ){
			if ( !(isDigit( str[i+1] )|| isLegalSig( str[i+1]) || isParenthesis( str[i+1] )== 2) ) {
					cout << "Error 3 not infix" << endl;
					return 3;
			}
		}
		else if (  isLegalSig( str[i]) ) {
			if ( !( isDigit( str[i+1]) || isParenthesis( str[i+1] ) ) ) {
				cout << "Error 3 not infix" << endl;
				return 3;
			}
		}
		else if ( isParenthesis( str[i] ) == 1 )  {
			if ( ! ( isDigit( str[i+1] ) || isParenthesis( str[i+1] == 1 ))) {
				cout << "Error 3 not infix" << endl;
				return 3;
			}
		}
		else if ( isParenthesis( str[i] ) == 2 ) {
			if ( !( isParenthesis( str[i+1]) || isLegalSig( str[i+1] ) ) ) {
				cout << "Error 3 not infix" << endl;
				return 3;
			}
		}
		
	} // for

 	return 0;
} // checkerror


string readCmd() {
	string cmd;
	do {
		getline(cin,cmd);
		cmd = removeSpace(cmd);
	} while ( !cmdCorrect( cmd , 1) );
	return cmd;
} // readCMD

List splitToken( string str ) {
	int length = str.size(), i = 0;
	List list;
	while ( i < length ) {
		if ( isDigit( str[i] ) ) {
			int head = i;
			while ( isDigit(str[i])) {
				i++;
			}
			list.append( str.substr(head, i - head) );
			i--;
		} // if is digit

		else if ( isLegalSig( str[i] ) ) {
			list.append( str.substr(i, 1 ));
		}
		else if ( isParenthesis( str[i] ) ) {
			list.append( str.substr(i, 1 ));
		}
		else {
			cout << "error";
		} 

		i++;
	}

	return list;
} // split

List mission2( List list ) {
	Node* cur = list.head;
	List reList;
	Stack stack;
	while ( cur != NULL ) {
		if ( isDigit( cur->str[0] ) ) reList.append( cur->str );
		else if ( isLegalSig( cur->str[0] ) ) {
			if ( cur->str == "*" || cur->str == "/" ) {
				stack.push( cur->str );
			} 

			else if ( cur->str == "+" || cur->str == "-" ) {
				if ( stack.top()=="*" || stack.top()== "/" ) {
					while ( !stack.isEmpty() && stack.top() != "(" ) {

						reList.append(stack.head->str );
						stack.pop();
					}

					stack.push( cur->str );
				} // if
				else {
					stack.push( cur->str);
				}
			}
		}
		else if ( isParenthesis( cur->str[0] ) ) {
			if ( isParenthesis( cur->str[0] ) == 1 ) stack.push(cur -> str);
			else {
				while ( stack.top() != "(" ) {
					reList.append(stack.head->str);
					stack.pop();
				}

				stack.pop();
			}
		}

		cur = cur -> next;
	}


	while ( !stack.isEmpty() ) {
		reList.append( stack.top() );
		stack.pop();
	}

	return reList;
}
		
void mission3( List list ) {
	Stack stack;
	Node *listCur = list.head;
	while ( listCur != NULL ) {
		if ( isDigit( listCur->str[0] ) ) 
			stack.push( listCur->str );
		else if ( listCur->str == "+" ) {
			float a = (float)stoi( stack.top() );
			stack.pop();
			float b = (float)stoi( stack.top() );
			stack.pop();
			float sum = a + b;
			stack.push(to_string((int)sum));
		}

		else if ( listCur->str == "-" ) {
			float a = (float)stoi( stack.top() );
                        stack.pop();
                        float b = (float)stoi( stack.top() );
                        stack.pop();
                        float sum = a - b;
                        stack.push(to_string((int)sum));
			
                }

		else if ( listCur->str == "*" ) {
                        float a = (float)stoi( stack.top() );
                        stack.pop();
                        float b = (float)stoi( stack.top() );
                        stack.pop();
                        float sum = a * b;
                        stack.push(to_string((int)sum));
                }

		else if ( listCur->str == "/" ) {
                        float a = (float)stoi( stack.top() );
                        stack.pop();
                        float b = (float)stoi( stack.top() );
                        stack.pop();
			if ( a == 0.0 ) {
				cout << "Dont divide by ZERO!!!!" << endl;
				return;
			}
			else {
				int sum = b/a;
                        	stack.push(to_string((int)sum));
			}
                }

		listCur = listCur -> next;
	}

	cout << "Answer: " << stoi(stack.top() ) << endl;
}
int main() {
	cout << "-------------------------------" << endl;
	cout << "1. start" << endl;
	cout << "0. quit" << endl;
	cout << "-------------------------------" << endl;
	string cmd = readCmd();

	while ( cmd != "0" ) { 
		string str;
		cout << "Input infix natation" << endl;	
		getline(cin,str);
		str = removeSpace( str );
		if ( !checkError( str ) ) {
 			List list = splitToken(str);
			list.printAll();
			list = mission2( list );
			list.printAll();
			mission3( list );
		}
		cout << "Enter another cmd" << endl;
		cmd = readCmd();
	} //while
} // main()
