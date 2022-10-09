# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
using namespace std;

struct Data {
    int schoolCode; // 0
    string schoolName; // 1
    int departmentCode; // 2
    string departmentName; // 3
    string division; // 4
    string level; // 5
    int studentNum; // 6
    int teacherNum; // 7
    int graduateNum; // 8
    string locationName; // 9
    string system; // 10
};

class File {
   
    public:
        bool sameSchoolAndDepartment ( vector<Data> data2, int index, int index2 ) {
            if ( index2 == -1 ) index2++;
            if ( data2[index2].departmentName == data[index].departmentName && data2[index2].schoolName == data[index].schoolName ) return true;
            return false;
        }

        void mission3( string filename1, string filename2, File file2 ) {
            ofstream file( ("output"+filename1+"_"+filename2+".txt").c_str() );
            int count = 0;
            int now1 = 0, now2 = 0;
            vector<Data> data2 = file2.data;
            vector<string> lines2 = file2.lines;
            int size1 = lines.size(), size2 = lines2.size();

            while ( now1 < size1 || now2 < size2 ) {
                file << lines[now1++] << "\n";
                cout << "[" << ++count << "]" << lines[now1-1] << endl;
                
                while ( sameSchoolAndDepartment(data, now1, now1-1 ) ) {
                    file << lines[now1++] << "\n";
                    cout << "[" << ++count << "]" << lines[now1-1] << endl;
                }

                while ( sameSchoolAndDepartment(data2, now1-1, now2-1) ) {
                    file << lines2[now2++] << "\n";
                    cout << "[" << ++count << "] " << lines2[now2-1] << endl;
                }

                if ( now1 >= size1 ) {
                    while ( now2 < size2 ) {
                        file << lines2[now2++] << "\n";
                        cout << "[" << ++count << "]" << lines2[now2-1] << endl;
                    }
                }

                else if ( now2 >= size2 ) {
                    while ( now1 < size1 ) {
                        file << lines[now1++] << "\n";
                        cout << "[" << ++count << "]" << lines[now1-1] << endl;
                    }
                }
                
                else if ( data[now1].schoolName != data[now1-1].schoolName) {
                    while ( data2[now2].schoolName == data[now1-1].schoolName ) {
                        file << lines2[now2++] << "\n";
                        cout << "[" << ++count << "]" << lines2[now2-1] << endl;
                    }
                }
            }

            cout << "Total: " << count << endl;
            file.close();
        }

        int getDepartmentCode( int index ) {
            return data[index].departmentCode;
        }

        int getSchoolCode( int index ) {
            return data[index].schoolCode;
        }
        void mission2( string fileName, int minStudentNum, int minGraduateNum ) {
            ofstream outputFile( ("copy"+fileName+".txt").c_str() );
            int now = 0, num = 0;
            int size = lines.size();
            while ( now < size ) {
                if ( data[now].studentNum >= minStudentNum && data[now].graduateNum >= minGraduateNum ) {
                    outputFile << lines[now] << "\n";
                    cout << "[" << ++num << "] " << lines[now] << endl;
                }

                now++;
            }

            cout << "Total number( Student number bigger than " << minStudentNum << " and  graduate number bigger than " << minGraduateNum << " ): " << num << endl;
            
            outputFile.close();
        }

        void BuildAll( string fileName ) {
            inputLines( fileName.c_str() );
            buildDatabase();
        }

        void inputLines( string fileName ) { 
            ifstream inputFile(fileName.c_str());
            string line;
            if ( fileName.substr(0,5) == "input" ) {
                for ( int i = 0 ; i < 3 ; i++ ) {
                    getline(inputFile, line);
                }
            } 

            while ( getline(inputFile, line)) {
                lines.push_back(line);
            }

            inputFile.close();
        }

        void mission1( string fileName) {
            ofstream outputFile( ("copy"+fileName+".txt").c_str() );
            int num = 0;
            int size = lines.size();
            for ( int i = 0 ; i < size ; i++ ) {
                outputFile << lines[i] << "\n";
                cout << "[" << ++num << "] " << lines[i] << endl;
            }

            cout << "Total " << num << endl;
            outputFile.close();
        }

        void buildDatabase() {
            int now = 0, size = lines.size();
            while ( now < size ) {
                buildOne( now );
                now++;
            }
        }


        void buildOne( int stringIndex ) {
            int now = 0, length = lines[stringIndex].size();
            int flag = 0, head = 0;
            Data newData;
            data.push_back( newData );
            while ( now < length ) {
                if ( lines[stringIndex][now] == '\t' || now == length - 1 ) {
                    if ( now == length - 1 ) now++;
                    insertData( stringIndex, head, now, flag );
                    head = now + 1;
                    flag++;
                }

                now++;
            }
        }

        void insertData( int stringIndex, int head, int tail, int flag ) {
            if ( head == tail ) { // the data is null
                if( flag == 0 ) {
                    data[stringIndex].schoolCode = -1;
                } else if( flag == 1 ) {
                    data[stringIndex].schoolName = "";
                } else if( flag == 2 ) {
                    data[stringIndex].departmentCode = -1;
                } else if( flag == 3 ) {
                    data[stringIndex].departmentName = "";
                } else if( flag == 4 ) {
                    data[stringIndex].division = "";
                } else if( flag == 5 ) {
                    data[stringIndex].level = "";
                } else if( flag == 6 ) {
                    data[stringIndex].studentNum = -1;
                } else if( flag == 7 ) {
                    data[stringIndex].teacherNum = -1;
                } else if( flag == 8 ) {
                    data[stringIndex].graduateNum = -1;
                } else if( flag == 9 ) {
                    data[stringIndex].locationName = "";
                } else if( flag == 10 ) {
                    data[stringIndex].system = "";
                }
            }

            else {
                if( flag == 0 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].schoolCode = toNum(str);
                } else if( flag == 1 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].schoolName = str;
                } else if( flag == 2 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].departmentCode = stoi(str);
                } else if( flag == 3 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].departmentName = str;
                } else if( flag == 4 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].division = str;
                } else if( flag == 5 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].level = str;
                } else if( flag == 6 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].studentNum = toNum( str );
                } else if( flag == 7 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].teacherNum = toNum(str);
                } else if( flag == 8 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].graduateNum = toNum(str);
                } else if( flag == 9 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].locationName = str;
                } else if( flag == 10 ) {
                    string str = lines[stringIndex].substr(head, tail-head );
                    data[stringIndex].system = str;
                }
            }
        }

        int toNum(string str) {
            int len = str.size();
            string restr;
            for ( int i = 0 ; i < len ; i++ ) {
                if ( str[i] >= '0' && str[i] <= '9' ) {
                    restr.push_back(str[i]);
                }
            }

            return stoi( restr );
        }


    public:
        vector<string> lines;
        vector<Data> data;
 
};


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
    return stoi( str );
}

int isFileExist( string fileName, int missionType ) {
    if ( missionType == 1 ) {
        ifstream f( ( "input" + fileName +".txt" ).c_str() );
        if ( f.good() ) return 1;
        if ( fileName.substr( 0, 5) == "input"  ) {
            ifstream isf( fileName.c_str());
            if ( isf.good() ) return 2;
        }
        else return 0;
    }

    else if ( missionType == 2 ) {
        ifstream f( ("copy"+fileName+".txt").c_str());
        if ( f.good() ) return 1;
        if ( fileName.substr( 0, 4 ) == "copy" ) {
            ifstream ifs( fileName.c_str() );
            if ( ifs.good()) return 2;
        }

        else return 0;
    }

    return 0;
}

int main() {
    int cmd = 1, flag;
    while ( cmd != 0 ) {
        cout << "-------------------------------" << endl;
        cout << "1. copy txt" << endl;
        cout << "2. filter" << endl;
        cout << "3. combine a and b" << endl;
        cout << "0. quit" << endl;
        cout << "-------------------------------" << endl;
        cmd = getNum();
        string fileName;
        if ( cmd == 1 ) {
            do {
                cout << "Input the num of file \"0\" quit( your file name must be like input201.txt, you can input 201 or input201.txt ):  ";
                cin >> fileName;
            } while ( !isFileExist(fileName, 1) && fileName != "0" );
            
            flag = isFileExist(fileName, 1);

            if ( flag == 1 ) {
                
                File file;
                file.BuildAll( "input"+fileName+".txt" );
                file.mission1( fileName );
                
            }
            
            else if ( flag == 2 ) {
                File file;
                file.BuildAll( fileName );
                file.mission1( fileName.substr(5, 3) );
            }
        }

        else if ( cmd == 2 ) {
            do {
                cout << "Input the num of file. We only use the copy file \"0\" quit.( your file name must be like copy201.txt => 201 ): ";
                cin >> fileName;
            } while ( !isFileExist(fileName, 2) && fileName != "0");

            flag = isFileExist(fileName, 2 );
            if ( flag == 1 ) {
                File file;
                int minStudentNum, minGraduateNum;
                cout << "Input minStudentNum ";
                cin >> minStudentNum;
                cout << "Input minGraduateNum ";
                cin >> minGraduateNum; 
                file.BuildAll( "copy" + fileName + ".txt" );
                file.mission2(fileName, minStudentNum, minGraduateNum );
            }

            else if ( flag == 2 ) {
                File file; 
                int minStudentNum, minGraduateNum;
                cout << "Input minStudentNum ";
                cin >> minStudentNum;
                cout << "Input minGraduateNum ";
                cin >> minGraduateNum; 
                file.BuildAll(  fileName );
                file.mission2(fileName.substr(4,3), minStudentNum, minGraduateNum ); 
            }
        }

        else if ( cmd == 3 ) {
            do {
                cout << "(first) Input the num of file. We only use the copy file \"0\" quit.( your file name must be like copy201.txt => 201 ): ";
                cin >> fileName;
            } while ( !isFileExist(fileName, 2) && fileName.c_str() != "0" );
            cout << atoi(fileName.c_str()) << endl;
            string fileName2;
            do {
                cout << "(second) Input the num of file. We only use the copy file \"0\" quit.( your file name must be like copy201.txt => 201 ): ";
                cin >> fileName2;
            } while ( !isFileExist(fileName2, 2) && fileName2 != "0" && fileName != "0");

            int flag2;
            flag = isFileExist(fileName, 2);
            flag2 = isFileExist(fileName2, 2);
            cout << flag << " " << flag2 << "";
            if ( flag == 1 && flag2 == 1 ) {
                File file;
                file.BuildAll("copy"+fileName+".txt");
                File file2;
                file2.BuildAll("copy"+fileName2+".txt");
                file.mission3(fileName, fileName2, file2);
            }

            else if ( flag == 1 && flag2 == 2 ) {
                File file;
                file.BuildAll( "copy" + fileName + ".txt");
                File file2;
                file2.BuildAll( fileName2 );
                file.mission3(fileName, fileName2.substr(4,3), file2);
            }

            else if ( flag == 2 && flag2 == 1 ) {
                File file;
                file.BuildAll( fileName );
                File file2;
                file2.BuildAll("copy"+fileName2+".txt");
                file.mission3(fileName.substr(4,3), fileName2, file2);
            }

            else if ( flag == 2 && flag2 == 2 ) {
                File file;
                file.BuildAll( fileName );
                File file2;
                file2.BuildAll( fileName2 );
                file.mission3( fileName.substr(4,3), fileName2.substr(4,3), file2);
            }
        }

        else if ( cmd == 0 ) {
            cout << "Bye!\n";
        }

        else {
            cout << "Error!\n";
        }
    }

    system( "pause" );
}