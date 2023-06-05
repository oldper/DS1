# include <iostream>
# include <vector>
# include <fstream>
# include <string>
# include <cstring>
# include <cmath>
using namespace std;
struct Order {
	int arrival;
	int orderID;
	int duration;
	int timeout;
};

struct ErrorList {
	int OID;
	int delay;
	int abort;
	int CID;
};



class Orders{
	private:
		vector<Order> orders;
	public:
		Order getFirst() {
			if ( orders.empty()) {
				Order od = { 99999, 0, 0 , 99999};
				return od; 
			}
			return  orders.at(0);
		}

		bool empty() {
			return orders.empty();
		}
		void clear() {
			orders.clear();
		}
		void eraseFirst() {
			if ( orders.size() == 1 ) {
				orders.clear();
			} else if ( orders.empty()) {
				
			} else {
			orders.erase( orders.begin());
			}
		}

		void build( vector<string> lines) {
			int size = lines.size();
			for ( int i = 0 ; i < lines.size();i++ ) {
				Order order;
				int len =  lines.at(i).length(), temp = 0, flag = 0;
				for ( int j = 0 ; j < len ; j++ ) {
					if ( lines.at(i)[j] == '\t' || j == len - 1 ) {
						if ( j == len - 1 ) j++;
						if ( flag == 0 ) order.orderID = stoi(lines.at(i).substr(temp, j));
						else if ( flag == 1 ) order.arrival = stoi( lines.at(i).substr(temp, j - temp  ));
						else if ( flag == 2 ) order.duration = stoi( lines.at(i).substr(temp, j - temp ));
						else order.timeout = stoi( lines.at(i).substr( temp, j - temp));
						flag++;
						temp = j + 1;
					}
				}

				orders.push_back( order );
			}
		}

		void printAll() {
			int size = orders.size();
			for ( int i = 0 ; i < size ; i++ ) {
				cout << orders.at(i).orderID << "\t" << orders.at(i).arrival << "\t" << orders.at(i).duration << "\t" << orders.at(i).timeout << endl;
			}
		}
		int size() {
			return orders.size();
		}
		void mission1( string name) {
			vector<Order>::iterator it = orders.begin();
			int size = orders.size();
			for (int span = size/2; span > 0; span /= 2) {
        		for (int i = span; i < size; i ++) {
            		Order temp = orders.at(i);
            		int j;           
            		for (j = i; j >= span && orders.at(j-span).arrival > temp.arrival ; j = j - span) {
						Order temp2 = orders.at(j-span);
						orders.erase(it+j);
						orders.insert(it+j, temp2);
					}
                	
            		orders.erase(it+j);
					orders.insert( it+j, temp );

        		}
    		}
    

			for (int span = size/2; span > 0; span /= 2) {
        		for (int i = span; i < size; i ++) {
            		Order temp = orders.at(i);
            		int j;           
            		for (j = i; j >= span && ( orders.at(j-span).arrival == temp.arrival && orders.at(j-span).orderID > temp.orderID ); j = j - span) {
						Order temp2 = orders.at(j-span);
						orders.erase(it+j);
						orders.insert(it+j, temp2);
					}
                	

            		orders.erase(it+j);
					orders.insert( it+j, temp );
					//arr[j] = temp;
        		}
    		}

			ofstream ofs( ("sort"+name+".txt").c_str());
			ofs << "OID\tArrival\tDuration\tTimeOut" << endl;
			for ( int i = 0 ; i < size ; i++ ) {
				ofs <<  orders.at(i).orderID << "\t" << orders.at(i).arrival << "\t" << orders.at(i).duration << "\t" << orders.at(i).timeout << "\n";
			}

			ofs.close();
	}
};

class Queue {
	private:
		vector<Order> queue;

	public:
		void enqueue(Order order) {
			queue.push_back(order);
		}

		void dequeue() {
			queue.erase(queue.begin());
		}

		Order getTop() {
			return queue.at(0);
		}

		int size() {
			return queue.size();
		}

		bool empty() {
			return queue.empty();
		}

		void printAll() {
			for ( int i = 0 ; i < size() ; i++ ) cout << queue[i].orderID << endl;
				
		}
};


class Cook {
	private:
	int freeTime;
	int CID;
	Queue queue;
	Order now = {0,0,0,0};
	bool free = true;

	public:
	Cook( int i ) {
		CID = i;
		freeTime = 0;
	}
	bool isEmpty() {
		return queue.empty();
	}


	int getFreeTime() {
		return freeTime;
	}

	int getCID() {
		return CID;
	}

	Order getNow() {
		return now;
	}
	ErrorList fullErrorlist(Order order) {
		ErrorList ab;
		ab.delay = 0;
		ab.OID = order.orderID;
		ab.abort = order.arrival;
		return ab;
	}

	void setNow( Order order) {
		free = false;
		now = order;
	}
	void takeOut() {
		if ( queue.empty() ) {
			free = true;
			return;
		}else {
			free = false;
			now = queue.getTop();
			queue.dequeue();
		}
	}


	bool isFull() {

		if ( queue.size() >= 3 ) return true;
		return false;
	}

	bool queueTimeout() {
		if ( free == true ) return false;
		if (  now.timeout <= freeTime ) {
			return true;
		} return false;
	}

	ErrorList queueErrorList() {
		ErrorList ab;
		ab.OID = now.orderID;
		ab.delay = freeTime - now.arrival;
		ab.abort = freeTime;
		return ab;
	}

	bool isFree() {
		return free;
	}
	void cook() {
		freeTime += now.duration;
	}

	bool doneTimeout() {

		if ( now.timeout < freeTime ) return true;
		return false;
	}

	ErrorList doneErrorList() {
		ErrorList ab;
		ab.OID = now.orderID;
		ab.delay = freeTime - now.duration - now.arrival;
		ab.abort = freeTime; // departure
		return ab;
	}

	void setFreetime( int t ) {
		freeTime = t;
	}

	void putIn( Order order) {
		queue.enqueue(order);
	}

	void Done() {
		if ( !queue.empty())
		queue.dequeue();
	}

	void printAll() {
		queue.printAll();
	}

	int size() {
		return queue.size();
	}
};

bool fileExist( string name, int mission ) {
	if ( mission == 1 ) {
		ifstream f(("input"+name+".txt").c_str());
		if ( f.good()) {
			f.close();
			return true;
		}

		cout << "error";
		f.close();
		return false;
	}

	else {
		ifstream f(("sort"+name+".txt").c_str());
		if ( f.good()){
			f.close();
			return true;
		}

		cout << "error";
		f.close();
		return true;
	}

}

int judgeCase( Cook cook1, Cook cook2) {
	bool cook1_free = cook1.isFree(), cook2_free = cook2.isFree();
	if ( cook1_free && cook2_free ) {
		return 2;
	} else if ( cook1_free || cook2_free ) {
		return 1;
	} else if ( !cook1.isFull() || !cook2.isFull()) {
		return 3;
	} else if ( cook1.isFull() && cook2.isFull()) {
		return 4;
	}
}

void distribute( Cook & cook1, Cook & cook2, Orders & orders, vector<ErrorList> & abortList, int & time ) {
		int a = judgeCase( cook1, cook2);
		switch (a) {
			case 1:
				if ( cook1.isFree() ) {
					cook1.setNow(orders.getFirst());
					if ( cook1.getFreeTime() < orders.getFirst().arrival ) 
						cook1.setFreetime(orders.getFirst().arrival);
						cook1.cook();
				} else if ( cook2.isFree() ) {
					cook2.setNow(orders.getFirst());
					if ( cook2.getFreeTime() < orders.getFirst().arrival )
					cook2.setFreetime(orders.getFirst().arrival);
					cook2.cook();
				}

				break;
			case 2:
				cook1.setNow(orders.getFirst());
				if ( cook1.getFreeTime() < orders.getFirst().arrival )
					cook1.setFreetime(orders.getFirst().arrival+orders.getFirst().duration);
					cook1.cook();
				break;

			case 3 :
				if ( cook1.size() > cook2.size() ) {
					cook2.putIn( orders.getFirst());
				} else if ( cook1.size() == cook2.size() ) {
					cook1.putIn(orders.getFirst());
				} else {
					cook1.putIn(orders.getFirst());
				}
				break;
			case 4:
				ErrorList er ;
				er.abort = time;
				er.CID = 0;
				er.OID = orders.getFirst().orderID;
				er.delay = 0;
				abortList.push_back(er);
				break;

			default:
				cout << "Error"<< endl;
		}
		orders.eraseFirst();
}
int main() {
	int cmd;

	do {
		cout << "1.\n2.\n3.\n";
		cin >> cmd;
		if ( cmd == 1 ) {
			Orders orders;
			string name;
			cout << "Input num of file ( input401.txt -> 401" << endl; 
			cin >> name;
			if ( fileExist( name, 1 ) ) {
				ifstream f(("input"+name+".txt").c_str());
				vector<string> lines;
				string line;
				getline( f, line );
				while ( getline(f,line)) {
					lines.push_back(line);
					cout << line << endl;
				}

				orders.build( lines );
				cout << endl;
				orders.mission1(name);
				orders.printAll();
				orders.clear();
			} else {
				cout << "input" << name << ".txt" << "   Not Found!" << endl;
			}

		}
		else if ( cmd == 2 ) {
			Orders orders;
			string name;
			cout << "Input num of file ( sort401.txt -> 401" << endl; 
			cin >> name;
			if ( fileExist( name, 2 )) {
				ifstream f(("sort"+name+".txt").c_str()) ;
				vector<string> lines;
				string line;
				getline( f, line );
				while ( getline(f, line)) {
					lines.push_back(line);
				}

				orders.build( lines );
			} 
			else {
				cout << "sort" << name << ".txt" << "   Not Found!!" << endl;
			}



			Cook cook(1);
			vector<ErrorList> abortList;
			vector<ErrorList> timeoutList;
			int count = orders.size();
			bool first = true;
			while ( !orders.empty() ) {
				if ( first ) {
					cook.setNow(orders.getFirst());
					cook.setFreetime(orders.getFirst().arrival);
					cook.cook();
					orders.eraseFirst();
					while(cook.getFreeTime() > orders.getFirst().arrival && !orders.empty()) {
						if ( cook.isFull()) {
							ErrorList er = cook.fullErrorlist(orders.getFirst());
							abortList.push_back(er);
						} 
						else {
							cook.putIn(orders.getFirst());
						}

						orders.eraseFirst();
					}

					first = false;

					cook.takeOut();
				}



				while ( cook.getFreeTime() > orders.getFirst().arrival ) {
					if ( cook.isFull()) {
						ErrorList er = cook.fullErrorlist(orders.getFirst());
						abortList.push_back(er);
					} else {
						cook.putIn(orders.getFirst());
					}

					orders.eraseFirst();
				}

				if ( cook.isFree() && !cook.isEmpty()) {
					cook.takeOut();
				}
				if ( cook.isFree() && cook.isEmpty()) {
					first = true;
				}

				if ( cook.queueTimeout() ) {
					while ( cook.queueTimeout() ) {
						ErrorList er = cook.queueErrorList() ;
						abortList.push_back(er);
						cook.takeOut();
					}
					while ( cook.getFreeTime() == orders.getFirst().arrival ) {
						if ( cook.isFull()) {
							ErrorList er = cook.fullErrorlist(orders.getFirst());
							abortList.push_back(er);
						}
						else {
							cook.putIn(orders.getFirst());
						}

						orders.eraseFirst();
					}
				}

				else {
					while ( cook.getFreeTime() == orders.getFirst().arrival ) {
						if ( cook.isFull()) {
							ErrorList er = cook.fullErrorlist(orders.getFirst());
							abortList.push_back(er);
						}
						else {
							cook.putIn(orders.getFirst());
						}

						orders.eraseFirst();
					}
					cook.cook();
					if ( cook.doneTimeout() ) {
						ErrorList er = cook.doneErrorList();
						timeoutList.push_back(er);
					}	

					cook.takeOut();
					
				}

			}

			while ( !cook.isFree()) {
				if ( cook.queueTimeout()) {
					ErrorList er = cook.queueErrorList();
					abortList.push_back(er);
					cook.takeOut();
				}

				else {
					cook.cook();
					if ( cook.doneTimeout()) {
						ErrorList er = cook.doneErrorList();
						timeoutList.push_back(er);
					}

					cook.takeOut();
					
				}
			}

			int delay = 0, fail = 0;
			ofstream ofs( ("one"+name+".txt").c_str());
			ofs << "[abortList]\n";
			ofs << "OID\tArrival\tDuration\tTimeOut" << endl;
			for ( int i = 0 ; i < abortList.size() ; i++ ) {
				ofs <<  abortList.at(i).OID << "\t" << abortList.at(i).delay << "\t" << abortList.at(i).abort  << "\n";
				cout <<  abortList.at(i).OID << "\t" << abortList.at(i).delay << "\t" << abortList.at(i).abort  << "\n";
				delay += abortList.at(i).delay;
				fail++;
			}
			ofs << "\n[timeoutList]\n";

			for ( int i = 0 ; i < timeoutList.size() ; i++ ) {
				ofs << timeoutList.at(i).OID << "\t" << timeoutList.at(i).delay << "\t" << timeoutList.at(i).abort << "\n";
				cout << timeoutList.at(i).OID << "\t" << timeoutList.at(i).delay << "\t" << timeoutList.at(i).abort << "\n";
				delay += timeoutList.at(i).delay;
				fail++;

			}

			ofs << "\n[Total Delay]\n" << delay << " min.\n";
			cout << "\n[Total Delay]\n" << delay << " min.\n";
			float a = (float)count,b =(float)fail;
			cout << timeoutList.size() << " " << abortList.size() << endl;
			cout << a << "  " << b<< endl;
			ofs << "\n[Faliure Percentage]\n" << round(100 * b / a*100)/100 << " %\n"; 
			cout << "\n[Faliure Percentage]\n" << round(100 * b / a*100)/100 << " %\n"; 

			
		}
	
		else if ( cmd == 3 ) {
			Orders orders;
			string name;
			cout << "Input num of file ( sort401.txt -> 401" << endl; 
			cin >> name;
			if ( fileExist( name, 2 )) {
				ifstream f(("sort"+name+".txt").c_str()) ;
				vector<string> lines;
				string line;
				getline( f, line );
				while ( getline(f, line)) {
					lines.push_back(line);
				}

				orders.build( lines );
			} 
			else {
				cout << "sort" << name << ".txt" << "   Not Found!!" << endl;
			}



			Cook cook1(1),cook2(2);
			vector<ErrorList> abortList;
			vector<ErrorList> timeoutList;
			int time = 0;
			bool first = true;
			while ( !orders.empty()) {
				time = orders.getFirst().arrival;
				if ( orders.getFirst().arrival == time ) {
					distribute(cook1,cook2,orders,abortList, time);
					orders.eraseFirst();
				}
				
				if ( time == cook1.getFreeTime() ) {
					if ( cook1.doneTimeout() ) {
						ErrorList er = cook1.doneErrorList();
						timeoutList.push_back(er);

					}
				}



				time++;
			}

		
		}
		else if ( cmd == 0 ) {
			break;
		}
		else {
		  cout << "Error!";
		}	  
	} while ( 1 );
}
