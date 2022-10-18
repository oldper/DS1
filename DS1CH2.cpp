// 11020107 蘇伯勳 11020140葉柏榆
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
using namespace std;

// To store the data of each line.
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
    bool putIn;
};

class File {
   
    public:

        /*
            This function is to input useful lines in vector "lines".
            fileName.substr(0,5) is to filter the first to third line of the original file out.
        */
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

        // build the data by the string.
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

        // use flag to make data to go to where they should be. If the data is null aka head == tail, the function will give it a value. 
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
                    data[stringIndex].putIn = false;
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

        // use buildOne to build vector data( aka database )
        void buildDatabase() {
            int now = 0, size = lines.size();
            while ( now < size ) {
                buildOne( now );
                now++;
            }
        }

        // inputLine and build database
        void BuildAll( string fileName ) {
            inputLines( fileName.c_str() );
            buildDatabase();
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

            return stoi( restr );
        }


        /*
            Because of the pre-process, the function will just output the string.
        */
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

        /*
            Because of the pre-process, the function is really easy that I don't need to explain.
        */
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
        /*
            I think this is the easiest way to do the task. putIn means that is the data be put in or not.
            In the other word, putIn is to prevent the data from repeat. And "flag" is to prevent that same 
            department but be apart by another department. If there isn't the "flag", the department will be 
            output together. 

            First, the function will output the first data. And it will find the same and continuous department and school 
            in first file. Then it will find the same and continuous department and school in second file. This is what it do.
            And there are two special case. First is that now and now-1 present another school. If this happen, the function will
            output all data that has the same schoolName with now-1. The second case is that first data's amount is bigger than second's.
            In this case, the function will output all the data that have not been output in the second file.
        */
        void mission3( string filename1, string filename2, File file2 ) {
            ofstream file( ("output"+filename1+"_"+filename2+".txt").c_str() );
            int count = 0;
            int now1 = 0;
            vector<Data> data2 = file2.data;
            vector<string> lines2 = file2.lines;
            int size1 = lines.size(), size2 = lines2.size();
            for ( int i = 0 ; i < size2 ; i++ ) {
                data2[i].putIn = false;
            }
            for ( int i = 0 ; i < size1 ; i++ ) {
                data[i].putIn = false;
            }

            while ( now1 < size1 ) {
                int flag2 = 0;
                if ( data[now1].putIn == false ) {
                    file << lines[now1++] << "\n";
                    cout << "[" << ++count << "]" << lines[now1-1] << endl;
                    data[now1-1].putIn = true;
                }
                else {
                    now1++;
                    flag2++;
                } 

                if ( now1 < size1 && !flag2 ) {
                    int flag = 0;
                    for ( int i = 0 ; i < size1 ; i++ ) {
                        if ( data[i].departmentName == data[now1-1].departmentName && data[i].schoolName == data[now1-1].schoolName && data[i].putIn == false) {
                            file << lines[i] << "\n";
                            cout << "[" << ++count << "]" << lines[i] << endl;
                            data[i].putIn = true;
                            flag++; 
                        }
                        if ( flag && ( data[i].departmentName != data[now1-1].departmentName || data[i].schoolName != data[now1-1].schoolName ) ) break;
                    }

                    flag = 0;
                    for ( int i = 0 ; i < size2 ; i++ ) {
                        if ( data[now1-1].departmentName == data2[i].departmentName && data[now1-1].schoolName == data2[i].schoolName && data2[i].putIn == false  && !( data[now1-1].level[0] == '5' ||  data[now1-1].level[0] == '2')) {
                            file << lines2[i] << "\n";
                            cout << "[" << ++count << "]" << lines2[i] << endl;
                            data2[i].putIn = true;
                            flag++;
                        }

                        if ( flag && ( data[now1-1].departmentName != data2[i].departmentName || data[now1-1].schoolName != data2[i].schoolName ) && !( data[now1-1].level[0] == '5' ||  data[now1-1].level[0] == '2')) break;
                        
                    }
                

                }

                if ( data[now1].schoolName != data[now1-1].schoolName ) {
                    for ( int i = 0 ; i < size2 ; i++ ) {
                        if ( data2[i].schoolName == data[now1-1].schoolName && data2[i].putIn == false ) {
                            file << lines2[i] << "\n";
                            cout << "[" << ++count << "]" << lines2[i] << endl;
                            data2[i].putIn = true;
                        }
                    }
                }

                if ( now1 >= size1 ) {
                    for ( int i = 0 ; i < size2 ; i++ ) {
                        if ( data2[i].putIn == false) {
                            file << lines2[i] << "\n";
                            cout << "[" << ++count << "]" << lines2[i] << endl;
                            data2[i].putIn = true;
                        }
                    }
                }

            }

            cout << "Total: " << count << endl;
            file.close();
        }
        void putInInit() {
            int length = lines.size();
            for ( int i = 0 ; i < length ; i++ ) {
                data[i].putIn = false;
            }
        }

    public:
        vector<string> lines;
        vector<Data> data;
 
};

// make sure that user enter number.
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
// to ensure the file is exist. missionType1 and 2 just mean copy or input
// return 1 means the user only enter the number like 201.
// return 2 means the user enter the whole file name.
// return 0 means the file does exist.
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

string correctFilename( string filename ) {
    if ( isFileExist(filename, 2 ) ) return filename;
    else if ( isFileExist("copy"+filename+".txt", 2) ) return "copy"+filename+".txt";
    return "-1" ;
}

int main() {
    int cmd = 1, flag;
    while ( cmd != 0 ) {
        cout << "-------------------------------" << endl;
        cout << "1. copy txt" << endl;
        cout << "2. filter" << endl;
        cout << "3. combine a and b" << endl;
        cout << "4. Challenge" << endl;
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

        else if ( cmd == 4 ) {
            File file;
            string  fileName2;
            int num = 0, count = 0;
            cout << "Number?" ;
            cin >> num;
            cout << "There is no way back." << endl;
            cout << "FileName  ";
            cin >> fileName ;
            fileName = correctFilename( fileName );
            while ( fileName == "-1" ) {
                cout << "ERROR!";
                cin >> fileName;
                fileName = correctFilename( fileName );
            }

            if ( isFileExist( fileName, 2 ) == 1 ) file.BuildAll(("copy"+fileName+".txt").c_str()); 
            else file.BuildAll( fileName );
            vector<string> outputLines;
            vector<Data> outputData;
            count++;
            int length = file.data.size();
            int i = 0;
            
            while ( i < length ) {
                    outputLines.push_back( file.lines[i]);
                    file.data[i].putIn = true;
                    outputData.push_back( file.data[i]);
                    i++;
            } 
            string outputFileName = "output";
            if ( fileName.substr(0, 4 ) == "copy" ) {
                outputFileName = outputFileName + fileName.substr( 4, 3) + "_";
            } else {
                outputFileName = outputFileName + fileName + "_";
            }
            while ( count < num ) {
                cout << "FileName: ";
                cin >> fileName2 ;
                fileName2 = correctFilename( fileName2 );
                while ( fileName2 == "-1" ) {
                    cout << "ERROR";
                    cin >> fileName2;
                    fileName2 = correctFilename( fileName2 );
                }
                count++;
                if ( fileName2.substr(0,4) == "copy" ) {
                    outputFileName = outputFileName + fileName2.substr( 4, 3) +"_";
                } else {
                    outputFileName = outputFileName + fileName2 + "_";
                }
                File file2;
                if ( isFileExist( fileName2 , 2) == 1 ) file2.BuildAll(("copy"+fileName2+".txt").c_str()); 
                else file2.BuildAll( fileName2 );

                int length2 = file2.lines.size();
                int now = 0;

                now = 0;
                int now2 = 0;
                while( now < outputLines.size() ) {
                    while ( now2 < length2 ) {
                        if ( outputData[now].schoolName == file2.data[now2].schoolName && outputData[now].departmentName == file2.data[now2].departmentName && file2.data[now2].putIn == false ) {
                            outputLines.insert( outputLines.begin()+now+1, file2.lines[now2]);
                            file2.data[now2].putIn = true;
                            outputData.insert( outputData.begin()+now+1, file2.data[now2] );
                            now++;
                        } 
                        now2++;
                    }
                    
                    if ( outputData[now].schoolName != outputData[now+1].schoolName ) {
                        for ( int i = 0 ; i < length2 ; i++ ) {
                            if ( outputData[now].schoolName == file2.data[i].schoolName && file2.data[i].putIn == false ) {
                                outputLines.insert( outputLines.begin()+now+1, file2.lines[i] );
                                file2.data[i].putIn = true;
                                outputData.insert(outputData.begin()+now+1, file2.data[i] );
                                now++;
                            }
                        }
                    }

                    now++;
                }
            }

            outputFileName = outputFileName.substr( 0, outputFileName.length()-1) + ".txt";
            ofstream outputFile( outputFileName.c_str() );
            int size = outputLines.size();
            int countNum = 0;
            cout << outputLines.size() << endl;
            for ( int i = 0 ; i < size ; i++ ) {
                outputFile << outputLines[i] << "\n";
                cout << "[" << ++countNum << "]" << outputLines[i] <<endl;
            }

            cout << "Total: " << countNum << endl;
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