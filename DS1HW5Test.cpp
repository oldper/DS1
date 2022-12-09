// env C++11
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <algorithm>
// quick sort
// radix sort
using namespace std;
struct Data {
    string line;
    int graduateNum; // 8
};

struct Basin {
    vector<Data> arr;
    int num;
};

class File {
    public :

        vector<Data> data;
        void BuildAll(string name) {
            ifstream ifs(name);
            string line;
            getline(ifs,line) ;
            getline(ifs,line) ;
            getline(ifs,line) ;
            while ( getline(ifs,line) ){
                BuildOne(line);
            }
        }
        int size() {
            return data.size();
        }


        void baubleSort() {
            int size = data.size();
            for ( int i = size - 1; i  > 0 ; i--) {
                for ( int j = 0 ; j <= i -1; j++ ) {
                    if ( data[j].graduateNum < data[j+1].graduateNum ) {
                        //swapData( j, j+1 );
                        iter_swap( data.begin()+j, data.begin()+j+1);
                    }
                }      
            }
        }

        void selectionSort() {
            int size = data.size();
            for ( int i = 0 ; i < size ; i++ ) {
                int minIndex = i;
                for ( int j = i + 1; j < size ; j++ ) {
                    if ( data[j].graduateNum > data[minIndex].graduateNum ) {
                        minIndex = j;
                   }
                }


                //swapData( minIndex, i);
                iter_swap(data.begin()+minIndex, data.begin()+i);
                
            }
        }

        void mergeSortForMain() {
            vector<Data> temp = data;
            data = mergeSort(temp);
        }

        vector<Data> mergeSort( vector<Data> arr) {
            if ( arr.size() <= 1 ) {
                return arr;
            }
            else {
                int middle = ( arr.size()) / 2;
                vector<Data> left = { arr.begin(), arr.begin()+middle};
                vector<Data> right = { arr.begin()+middle, arr.end()};
                return merge( mergeSort(left), mergeSort(right));
            }
        }

        vector<Data> merge( vector<Data> left, vector<Data> right) {
            vector<Data> arr;
            while (  left.size() && right.size() ) {
                Data pushbackElement ;
                if (left[0].graduateNum > right[0].graduateNum) {
                    pushbackElement = left.at(0);
                    left.erase(left.begin());
                } else {
                    pushbackElement = right.at(0);
                    right.erase(right.begin());
                }

                arr.push_back(pushbackElement);

            }

            while ( left.size() > 0 ) {
                Data pushbackElement = left.at(0);
                left.erase(left.begin());
                arr.push_back(pushbackElement);
            }

            while ( right.size() > 0 ) {
                Data pushbackElement  = right.at(0);
                right.erase(right.begin());
                arr.push_back(pushbackElement);
            }

            return arr;
        }

        void quickSortForMain() {
            quickSort(0, data.size()-1);
        }
        int partition(  int start,  int end ) {
            int pivot = data.at(end).graduateNum, i = start - 1;
            for ( int j = start; j < end; j++ ) {
                if ( data[j].graduateNum > pivot ) {
                    i++;
                    //swapData(i,j);
                    iter_swap(data.begin()+i, data.begin()+j);
               }
            }

            i++;
     //       swapData(i,end);
            iter_swap(data.begin()+i, data.begin()+end);
            return i;
        }

        void quickSort(  int start, int end ) {
            if ( start < end ) {
                int pivot = partition( start, end);
                quickSort(  start, pivot - 1 );
                quickSort( pivot+1, end );
            }
        }

        int getMax() {
            int max = data[0].graduateNum;
            for ( int i = 0 ; i < data.size() ; i++ ) {
                if ( data[i].graduateNum > max ) max = data[i].graduateNum;
            }
            return max; 
        }
        void radixSort() {
            vector<Basin> basins;
            for ( int i = 0 ; i <= 9 ; i++ ) {
                Basin basin;
                basin.num = i;
                basins.push_back(basin);
            }

            int size = data.size();
            bool flag = true;
            int max = getMax();
            int maxPow = getPow(max);
            for ( int i = 0 ; flag ; i++ ) {
                if ( i == maxPow ) flag = false;
                for ( int j = 0 ; j < size ; j++ ) {
                    int num = getNum( data.at(j).graduateNum, i );
                    basins[num].arr.push_back( data[j] );
                }

                data.clear();
                for ( int i = 9 ; i >= 0 ; i-- ) {
                    int sizeB =basins[i].arr.size();
                    for ( int j = sizeB - 1 ; j >= 0 ; j-- ) {
                        data.push_back( basins[i].arr[j]);      
                    }

                    basins[i].arr.clear();
                }
            }
        }


        void compare( File file ) {
            int size = data.size(), count = 0;
            for ( int i = 0 ; i< size ; i++ ) {
                if ( file.data[i].graduateNum == data[i].graduateNum ) {
                    count++;
                }
            }

            if ( count == size ) printf( "Ok" );
        }
    private:
/*
        void swapData( int i, int j ) {
            Data temp1= data[i], temp2 = data[j];
            data.erase( data.begin()+i);
            data.insert( data.begin()+i, temp2);
            data.erase( data.begin()+j );
            data.insert( data.begin()+j, temp1 );
        }
*/
        void BuildOne(string str) {
            int size = str.size();
            int i=0, flag = 0;
            while( flag != 8 ) {
                if ( str[i] == '\t' ) flag++;
                i++;
            }

            int head = i;
            while ( str[i] != '\t') i++;
            if ( head == i ) {
                Data putInData = {str, 0 };
            }
            else {
                Data putInData = {str, toNum(str.substr(head,i-head))};
                data.push_back(putInData);
            }
        }




        /* 
            Because that if the number is bigger than or equal to 1000, it will have some characters that not a number.
            And that will make stoi can't use. So I program the function to deal with that.
        */
        int toNum(string str) {
            int len = str.size();
            string restr;
            for ( int i = 0 ; i < len ; i++ ) {
                if ( str[i] >= '0' && str[i] <= '9' ) {
                    restr.push_back(str[i]);
                }
            }

            return atoi( restr.c_str() );
        }

        string numToString( int num ) {
            if ( num == -1 ) return "";
            else {

            }
        }    

        int getNum( int num, int i ) {
            int j = 0, re = 1;
            while ( j < i  ) {
                j++;
                re *= 10;
            }

            return ( num / re ) % 10;
        }


        int getPow( int num ) {
            if ( num == 0 ) return 0;
            int i = -1;
            while ( num != 0 ) {
                i++;
                num /= 10;
            } 
            return i;
        }
        



 
};



int main() {
    string name1, name2;
    cout << "name1" << endl;
    cin >> name1;
    cout << "name2" << endl;
    cin >> name2;
    File file1, file2;
    file1.BuildAll(name1.c_str());
    file2.BuildAll(name2.c_str());

    file1.compare(file2);
    
}