// 11020140 電資二 葉柏榆
# include <time.h>
# include <string>
# include <iostream>
# include <cstring>
using namespace std;

typedef struct originalPlace{
    int number;
    int index;
}  OP; //偷懶用



// Just for input 
int getNum() { 
    string str;
    int flag = 0;
    while ( !flag ) {
        if ( str[0] == '-') {
            cout << "positive please~ ";
        }
        else {
            cout << "Input integer please~ ";
        }
        cin >> str;
        int count = 0, len = str.length();
        for ( int i = 0 ; i < len ; i++ ) {
            if ( str[i] >= '0' && str[i] <= '9' )  count++;
        }

        if ( count == len ) flag++;
    }

    cout << endl;
    return stoi( str);
}


int gCount = 0; // 算遞迴數 count recursion time.

void swap(OP *i, OP *k ) {
    OP tmp = *i;
    *i = *k;
    *k=tmp;
} // JUST A NORMAL swap

void PrintNumList( OP *arr, int size ) {
    for ( int i = 0; i < size; i++ ) {
        cout << arr[i].number ;
    }
    cout << endl;
} // 如名 Just like function name


void canUseInM1andM2( OP *arr, int head, int size ) {
    if ( head == size - 1 ) {  // 因為 SIZE-1 已經是最後一個也不用SWAP了 所以就不讓他進ELSE
        cout << "[" << ++gCount <<"] ";
        PrintNumList( arr, size );
    } // if  Print and count


    else {

        // 先排回來 為了要可以用在第二題所以就用struct偷懶計原來的index
        // sort it by selection sort. Because I need a dictionary order list.
        // Because I want to use this function in 2rd mission, I use the struct OP to record the original index.
        for ( int i = head ; i < size - 1 ; i++ ) {
            int minIndex = i;
            for ( int j = i+1; j <size ; j++ ) {
                if ( arr[j].index < arr[minIndex].index ) {
                    minIndex = j;
                }
            }

            if ( i != minIndex ) swap(&arr[minIndex] , &arr[i]);
        }


        // 就是排列本身
        // This function is the permutation function itself.
        // If there isn't a condition that should output in dictionary order, this part will be enough.

        for ( int i = head ; i < size ; i++ ) {
            swap(&arr[i], &arr[head]);
            canUseInM1andM2(arr, head+1, size);
            swap(&arr[i], &arr[head]);
        }
    }
}

/*
    This function is to find the smallest and not repeated number
    EX. [ 1, 2, 4, n]  n should be 3.
*/

int FindTheNum( int *arr, int size ) {
    int target = 0;
    // flag is use to control target( the int that will be returned ). 
    int flag = 0 ;
    while ( !flag ) {
        target++;
        // flag2 is used to check if there is the same number.
        int flag2 = 0;
        for ( int i = 0 ; i <= size; i++ ) {
            if ( arr[i] == target ) flag2++;
        }

        // if there is no the same num in the list, stop the while loop.
        if ( !flag2 ) flag++;
    }

    return target;
}


// 如果有一樣的數字就不print
// For the third mission if there is no repeat number, print it.
int same( int *arr, int size ) {
    int flag = 0 ;
    for ( int i = 0 ; i < size ; i++ ) {
        for ( int j = i ; j < size ; j++ ) {
            if ( arr[j] == arr[i] && i != j ) flag++;
        }
    }

    return flag;
}

// I don't know why I wrote this. Whatever OAO.
void setNum( int *a, int b ) {
    *a = b;
}

/* for the third mission */
void m3( int* arr, int now, int size, int m) {
    // now == size and doesn't have repeated number print it.
    if ( size == now ) {
        if ( !same( arr, size ) ) {
            gCount++;
            cout << "[" << gCount << "] ";
            for ( int i = 0  ; i < size ; i++ ) cout << *(arr+i) << " ";
            cout << endl;
        }
    }

    // 這應該也是遞迴吧
    // I think this is also a recursive function maybe.
    else {

        while( arr[now]<=m ) {

            setNum(arr+now+1, FindTheNum(arr, now));
            // The function will called it self
            m3(arr, now + 1, size, m );
            // equals arr[now]++;
            setNum(arr+now, arr[now]+1) ;
        }
    }
}

int main () {
    // cmd = command
    int cmd = 1;

    while ( cmd != 0 ) {
        cout << "--------------------------------\n";
        cout << "1. 1~n permutation\n";
        cout << "2. n numbers permutation\n" ;
        cout << "3. 1~9 catch n permutation\n";
        cout << "4. 1~m catch n permutation\n" ;
        cout << "0. Quit\n" ; 
        cout << "--------------------------------\n\n";
        cmd = getNum();
        // 歸零
        gCount = 0;

        // Mission1
        if ( cmd == 1 ) {

            cout << "How many?\n" ;
            int target;
            target = getNum();
            while ( target <= 0 ) {
                cout << "positive please~\n";
                target = getNum();
            }
            OP arr[target];
            for ( int i = 0 ; i < target ; i++ ) {
                arr[i].index = i;
                arr[i].number = i + 1;
            }

            canUseInM1andM2( arr, 0, target );
            cout << "L = " << target << endl;
            cout << gCount << " permutations" << endl;
            free(arr);
        }

        // Mission2
        else if ( cmd == 2 ) {
            int num;
            cout << "How many numbers do you want?\n";
            num = getNum();
            while ( !( num >= 2 && num <= 9 )) { 
                cout << "Between 2 and 9 please~  \n";
                num = getNum();
            }
            OP arr[num];
            for ( int i = 0 ; i < num ; i++ ) {
                arr[i].index = i;
                cout << "Still have "<< num - i << " left" << endl;
                arr[i].number = getNum();
                while ( arr[i].number <= 0 ) {
                    cout << "positive please~ \n" ;
                    arr[i].number = getNum();
                }
            }
            double start = clock();
            canUseInM1andM2( arr, 0, num );
            double end = clock();
            cout << gCount << " Permutations" << endl;
            cout << (int)(end - start) << "ms" << endl;
            free (arr);
        }

        else if ( cmd == 3 ) {
            int num;
            cout << "between 1 and 9 please\n" ;
            num = getNum();
            while ( !( num >= 1 && num <= 9 )) { 
                cout << "between 1 and 9 please~  \n";
                num = getNum(); 
            }
            int arr[num];
            for ( int i = 1 ; i <= num ; i++ ) {
                arr[i-1] = i;
            }
            double start = clock();
            m3( arr, 0, num, 9);
            double end = clock();
            cout << gCount << " Permutations" << endl;
            cout << (int)(end - start) << "ms" << endl;
        }

        else if ( cmd == 4 ) {
            int num, num2;
            cout << "N " ;
            num = getNum();
            while ( num <= 0 ) {
                cout << "positive please~  \n";
                num = getNum();
            }
            cout << "M ";
            num2 = getNum();
            while ( num2 > num || num2 <= 0) { 
                if ( num2 > num ) cout << "M must lower than N\n";
                else cout << "positive please~ \n";
                num2 = getNum(); 
            }
            int arr[num2];
            for ( int i = 1 ; i <= num2 ; i++ ) {
                arr[i-1] = i;
            }
            double start = clock();
            m3( arr, 0, num2, num);
            double end = clock();
            cout << gCount << " Permutations" << endl;
            cout << (int)(end - start) << "ms" << endl;
        }
        else if ( cmd == 0 ) {
            cout << "Bye!\n" ;
        }

        else cout << "Error!!\n" ;


        cout << endl;
    }

    system( "pause" );
}



/*  I think you may think that why I wrote in two ways.
    This is a nice problem. The reason is I didn't want to
    spend to much time thinking how to solve it in the same way
    so I chose the easier way to solve it. And this way is also
    a recursive way. Thanks for reading my code.
*/
