# include <iostream>
# include <string>
using namespace std;
// A node for linked list( List ) and Stack.
// compose with string and the next node
class Node {
        public:
		// member
                string str="";
                Node *next;

		
		// init method.
                Node( string strr ) { 
                        str = strr;
                        next = NULL;
                }

                Node( string strr, Node *nextN ) {  // define the node "next"
                        str = strr;
                        next = nextN;
                }

};


// Make stack by linked list. Every stack member using a node.
// push means put element in stack.
// And I practice stack by put the new node at the first space which means make new node as the head of the linked list.
// pop means delete the stack member.
// It means delete the top member of stack which mean delete the first member ( head ) of the list.
class Stack {
	public:

		// member
		Node *head = NULL; 
		


		// method
		void push( string str ) {
			if ( head == NULL ) head = new Node( str ); // if null init the list.
			else {
				Node *node = new Node( str, head );		// make new node and set it the head.
				head = node;
			}
		} // push
		  

		int size() {  // count how many members in the stack.
			Node *cur = head;
			int count = 0;
			while ( cur != NULL ) {
				count++;
				cur = cur->next;
			}

			return count;
		} // size
	
		bool isEmpty() { // just like its name.
			return head == NULL;
		}

		void pop() { // delete the first member of the list.
			if (head != NULL) {
				Node *temp = head;
				head = head->next;
				delete temp;
			}
		} // pop
		  
		string top() { // return first member's string.
			if ( head != NULL ) {
				return head -> str;
			} else return "";
		}
};


// the class is just a normal linked list.
// I think I don't need to explain.
class List {
	public:
		// member
		Node *head = NULL;




		// method
		void append( string str ) { // add an element in the end of the list
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
		

		void insert( string str, int pos ) { // insert the node in a special position.
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
			  
		} // insert
		  
		void printAll() { // print all member in the list.
			Node* cur = head;
			while ( cur != NULL ) {
				cout << cur->str<< " " ;
				cur = cur -> next;
			} // while
			  
			cout << endl;
		} // printAll()

		void deleteByPos( int pos ) { // delete the node in special position.
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
		  
		int size() { // size
			int count = 0;
			Node *cur = head;
			while ( cur != NULL ) {
				count++;
				cur = cur -> next;
			}

			return count;
		}
};// List
 

bool isDigit( char ch ) { // check if ch is a digit ex 1, 2, 3, 4..... 
	if ( ch >= '0' && ch <= '9' ) return true;
	return false;
} // isDigit
bool isLegalSig( char ch ) { // check if the ch is a legal operator
	if ( ch == '+' || ch == '-' || ch == '*' || ch == '/' ) return true;
	return false;
}

int isParenthesis( char ch ) { // check if the ch is a parenthesis 1 means open parenthesis 2 means close parenthesis.
	if ( ch == '(' ) return 1;
	else if ( ch == ')' ) return 2;
	else return 0;
}

bool isLegal( char ch ) { // check the ch is legal ( for mission1 error1 )
	if ( isDigit( ch ) || isLegalSig( ch ) || isParenthesis(ch) ) return true;
	return false;
}

bool cmdCorrect( string str , int mode ) { // check if the cmd is the program want.
	if ( str == "0" || str == "1" ) return true;
	if ( mode == 1 ) cout << "Error!!!!!!!" << endl;
	return false;
} // check if the cmd correct.

string removeSpace( string str ) {  // remove space from string.
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( str[i] == ' ' || str[i] == '\t' ) {
			str.erase( str.begin() + i );
			i--;
		}

	}
	return str;
}

int checkError( string str ) { // mission1
	// error1
	int len = str.length();
	for ( int i = 0 ; i < len ; i++ ) {
		if ( !isLegal( str[i] )) {
			cout << "Error 1 " << str[i] << " is not legal" << endl;
			return 1;
		}
	}

	// error2
	int count = 0;
	for ( int i = 0 ; i < len ; i++ ) { // check the parenthesis is couple and open parenthesis is input first.
		if ( str[i] == '(' ) count++; 
	       	else if ( str[i] == ')' ) count--;
		else if ( count < 0 ) {  // EX )()(()
			cout << "Error 2 Extra close parenthesis" << endl;
			return 2;
		}
	} 

	if ( count > 0 ) { // open parenthesis num larger than close
		cout << "Error 2 Extra open parenthesis" << endl;
		return 2;
	} else if ( count < 0 ) { // close parenthesis num larger than open
		cout << "Error 2 Extra close parenthesis" << endl;
		return 2;
	}

	// error3
	for ( int i = 0 ; i < len ; i++ ) {
		if ( i == len - 1 ) { // last char of string can be digit or close parenthesis
			if ( !( isDigit(str[i]) || isParenthesis(str[i]) == 2)) {
				if ( isLegalSig( str[i] )){ // if last char is operator, it will print error. 
							    // if last char is open parenthesis, it will filter by error2.
				cout << "Error 3 one Extra operater" << endl;
				return 3;
				}
			}
		}
	
		else if ( i == 0 ) { // first char can be digit or open parenthesis.
				     // if first char is close parenthesis, it will filter by error2.
				     // if first char is operator it will print error.
			if ( isLegalSig( str[i] ) ) {
				cout << "Error 3 extra operator" << endl;
				return 3;
			}
		}
		else if ( isDigit( str[i] ) ){ // if the char is digit and the next char should be digit or operator or close parenthesis.
			if ( !(isDigit( str[i+1] )|| isLegalSig( str[i+1]) || isParenthesis( str[i+1] )== 2) ) {
					cout << "Error 3 not infix" << endl;
					return 3;
			}
		}
		else if (  isLegalSig( str[i]) ) { // if the char is operator the next char should be digit or open parenthesis
			if ( !( isDigit( str[i+1]) || isParenthesis( str[i+1] )==1 ) ) {
				cout << "Error 3 not infix" << endl;
				return 3;
			}
		}
		else if ( isParenthesis( str[i] ) == 1 )  { // if the char is open parenthesis the next char should be digit or another open parenthesis
			if ( ! ( isDigit( str[i+1] ) || isParenthesis( str[i+1] ) == 1)) {
				cout << "Error 3 not infix" << endl;
				return 3;
			}
		}
		else if ( isParenthesis( str[i] ) == 2 ) { // if the char is close parenthesis the next char should be another close parenthesis or operater
			if ( !( isParenthesis( str[i+1]) == 2|| isLegalSig( str[i+1] ) ) ) {
				if ( isDigit( str[i+1] )) {
					cout << "Error 3 extra operand" << endl;
					return 3;
				}
				else { 
					cout << "Error 3 you need an operator between two parenthesis" << endl;
					return 3;
				}

			}
		}
		
	} // for

 	return 0;
} // checkerror


string readCmd() { // read command
	string cmd;
	do {
		getline(cin,cmd);
		cmd = removeSpace(cmd);
	} while ( !cmdCorrect( cmd , 1) );
	return cmd;
} // readCMD

List splitToken( string str ) { // ex. 1+1 -> 1, +, 1,    (1+1) -> (, 1, +, 1, )
				// str is legal infix expression and have no space.
	int length = str.size(), i = 0; 
	List list;
	while ( i < length ) {
		// if is digit then read all of the num 
		// ex 123345+1 then the function will append 123345 to list
		if ( isDigit( str[i] ) ) { 
			int head = i;
			while ( isDigit(str[i])) {
				i++;
			}
			list.append( str.substr(head, i - head) );
			i--;
		} // if is digit


		// if is operator then read the operator and append that to list
		// ex +1 then the function will append + to list
		else if ( isLegalSig( str[i] ) ) {
			list.append( str.substr(i, 1 ));
		}

		// if is parenthesis then read the parenthesis and append the to list
		// ex (1+1) then the function will append ( to list
		// ex )+1 then the function will append ) to list
		else if ( isParenthesis( str[i] ) ) {
			list.append( str.substr(i, 1 ));
		}
		else {
			cout << "error";
		} 

		i++; // go to next char of string
	}

	return list;
} // split

// infix to postfix.
List mission2( List list ) {
	Node* cur = list.head;
	List reList;
	Stack stack;
	while ( cur != NULL ) {
		if ( isDigit( cur->str[0] ) ) reList.append( cur->str );
		else if ( isLegalSig( cur->str[0] ) ) {
			if ( cur->str == "*" || cur->str == "/" ) {
					while (  stack.top() == "*" || stack.top() == "/" ) {
						reList.append( stack.head->str );
						stack.pop();
					}

					stack.push( cur->str );
			} 

			else if ( cur->str == "+" || cur->str == "-" ) {
				while ( stack.top() != "(" && !stack.isEmpty() ) {
					reList.append( stack.head->str);
					stack.pop();
				}

				stack.push(cur->str);
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
			cout << "legal infix expresion" << endl;
			list = mission2( list );
			cout << "Postfix: " ;
			list.printAll();
			mission3( list );
		}
		cout << "Enter another cmd" << endl;
		cmd = readCmd();
	} //while
} // main()
