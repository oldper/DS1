# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <algorithm>

using namespace std;
int gCount = 0;
int gNum = 1;
vector<int> gRecord;
struct Pokemon {
    string rawR;
    int no; // 0
    string name; // 1
    string tp1; // 2
    int tol; // 4
    int hp; // 5
    int atk; // 6
    int def; // 7
};

struct BSTree {
    BSTree *left, *right;
    vector<Pokemon> data;
};

void inputData(int a) {
    int size = gRecord.size(), flag = 0;
    for ( int i = 0 ; i < size ; i++ ) {
        if ( a == gRecord[i] ) flag++;
    }

    if ( !flag ) gRecord.push_back(a);
}

class PokemonList {
    vector<Pokemon> pSet;
    BSTree *root = NULL;    

    void mission2( BSTree* t, int a ) {
        if ( t !=NULL ) inputData( t->data[0].hp );
        if ( t == NULL ) return;
        if ( t->data[0].hp == a ) {
            printNode2(t);
            
            mission2(t->right, a );
        } 

        else if ( t->data[0].hp > a ) {
            if ( t -> left != NULL ) {
                mission2( t-> left, a );
            }

            
            printNode2(t);
            mission2( t->right, a);
        }

        else {

            mission2( t-> right, a);
        }
    }
    int getNum( string str ) {
        int size = str.size(), i = 0;
        string temp = "";
        while ( i < size ) {
            if ( str[i] <= '9' && str[i] >= '0') {
                temp = temp + str[i];
            }
            i++;
        }

        return atoi( temp.c_str() );

    }
    void buildOne( string str ) {
        int size = str.size();
        int i = 0, flag = 0, head = 0;
        Pokemon pokemon;
        pokemon.rawR = str;
        while ( i < size ) {
            if ( str[i] == '\t' ) {
                string temp = str.substr( head, i - head );
                if ( flag == 0 ) {
                    pokemon.no = getNum(temp);
                }
                else if ( flag == 1 ) {
                    pokemon.name = temp;
                }
                else if ( flag == 2 ) {
                    pokemon.tp1 = temp;
                }
                else if ( flag == 4 ) {
                    pokemon.tol = getNum(temp);
                }
                else if ( flag == 5 ) {
                    pokemon.hp = getNum(temp);
                }
                else if ( flag == 6 ) {
                    pokemon.atk = getNum(temp);
                }
                else if ( flag == 7 ) {
                    pokemon.def = getNum(temp);
                }

                flag++;
                head = i+1;
            } 

            i++;
        }

        pSet.push_back( pokemon );
    }


    BSTree *minNode( BSTree* node ) {
        BSTree* cur = node;
        while ( cur && cur -> left != NULL ) cur = cur -> left;
        return cur;
    }


    int largerHP( Pokemon p1, Pokemon p2 ) {
        if ( p1.hp == p2.hp ) return 0;
        else if ( p1.hp > p2.hp ) return 1;
        else return -1;
    }

    BSTree* insert( Pokemon pokemon, BSTree* t) {
        if ( t == NULL ) {
            t = new BSTree;
            t -> data.push_back(pokemon);
            t -> left = NULL;
            t -> right = NULL;
        }

        else if ( largerHP(pokemon, t->data.at(0) ) == 0 ) {
            t -> data.push_back(pokemon);
        }

        else if ( largerHP(pokemon, t->data.at(0)) == 1 ) {
            t -> right = insert( pokemon, t->right );
        } 

        else {
                t -> left = insert( pokemon, t-> left );
        }

        return t;
    }


    void search( BSTree * &cur, Pokemon pokemon, BSTree* &parent ) {
        while ( cur != NULL && largerHP( pokemon, cur -> data.at(0) ) != 0) {
            parent = cur;
            if ( largerHP( pokemon, cur -> data.at(0))) {
                cur = cur -> left;
            }

            else {
                cur = cur -> right;
            }
        }
    }

    void printNode2( BSTree* node ) {
        int size = node -> data.size();
        for ( int i = 0 ; i < size ; i++ ) {
            cout << "[" << gNum++ << "]" << "\t" << node -> data[i].no << "\t" << node -> data[i].name << "\t" << node -> data[i].tp1 << "\t" << node->data[i].tol << "\t" << node -> data[i].hp << "\t" << node -> data[i].atk << "\t" << node -> data[i].def << endl;
        }
    }

BSTree *deleteNode( BSTree* t,Pokemon pk) {
    if ( t == NULL ) {
        return t;
    }

    if ( largerHP( pk, t->data[0] ) == -1 ) {
        t -> left = deleteNode( t->left, pk);
    }

    else if ( largerHP( pk, t->data[0] ) == 1 ) {
        t -> right = deleteNode( t->right, pk);
    }

    else {
        if ( t -> left == NULL ) {
            BSTree *temp = t -> right ;
            cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp. Atk\t Sp. Def\tSpeed\tGeneration\tLegendary" << endl;
            for ( int i = 0 ; i < t->data.size() ; i++ ) {
                cout << t->data[i].rawR << endl;
            }
            delete t;
            return temp;
        }

        else if ( t -> right == NULL ) {
            BSTree *temp = t -> left ;
            cout << "#\tName\tType 1\tType 2\tTotal\tHP\tAttack\tDefense\tSp. Atk\t Sp. Def\tSpeed\tGeneration\tLegendary" << endl;
            for ( int i = 0 ; i < t->data.size() ; i++ ) {
                cout << t->data[i].rawR << endl;
            }
            delete t;
            return temp;
        }

        else {
            BSTree *temp = minNode( t->right );
            t -> data = temp -> data;
            t -> right = deleteNode(t->right, temp->data[0]);
            
        }
    }

    return t;
}

    BSTree* findMax( BSTree* t ) {
        if ( t == NULL ) return NULL;
        while ( t -> right != NULL ) t = t -> right;
        return t;
    }

    int bigger( int a, int b ) {
        if ( a > b ) return a;
        else return b;
    }

    int height( BSTree* t ) {
        if ( t == NULL ) return 0;
        else return 1 + bigger( height( t -> left ), height( t -> right ) );
    }

    void printNode( BSTree* node ) {
        int size = node -> data.size();
        for ( int i = 0 ; i < size ; i++ ) {
            cout << "[" << gNum++ << "]" << "\t" << node -> data[i].no << "\t" << node -> data[i].name << "\t" << node -> data[i].tp1 << "\t" << node -> data[i].hp << "\t" << node -> data[i].atk << "\t" << node -> data[i].def << endl;
        }
    }

    void printTree( BSTree* root ) {
        if ( root == NULL ) return ;
        printNode( root );
        gCount++;
        printTree( root -> left );
        printTree( root -> right );
    }

    BSTree* search( int a, BSTree* t) {
       // if ( t == NULL ) {
       //     cout << "not Found";
       //     return NULL;
       // }
        if ( t -> data[0].hp > a ) {
            gCount++;
            return search( a, t->left );
        }

        else {
            return t;
        }
    }

    void buildBST() {
        int size = pSet.size();
        for ( int i = 0 ; i < size ; i++ ) {
            root = insert(pSet[i], root);
        }
    }

    public:

    int findMaxHP() {
        BSTree *cur = root;
        while ( cur -> right != NULL ) {
            cur = cur -> right;
        }
        
        return cur -> data[0].hp;
    }

    void printAll() {
        int size = pSet.size();
        cout << "\t\t#\tName\tType 1\tHP\tAttack\tDefense" << endl;
        for ( int i = 0 ; i < size ; i++ ) {
            cout << "[" << i+1 << "]" << "\t" << pSet[i].no << "\t" << pSet[i].name << "\t" << pSet[i].tp1 << "\t" << pSet[i].hp << "\t" << pSet[i].atk << "\t" << pSet[i].def << endl;
        }
    }

    void build( string name ) {
        pSet.clear();
        root =NULL;
        ifstream ifs( ("input"+name+".txt") );
        string line, line2;
        getline( ifs, line );
        while ( getline( ifs, line) ) {
            buildOne( line );
        }
        ifs.close();
        buildBST();

    }

    int height() {
        return height( root );
    }

    void mission2( int a ) {
        gCount = 0;
        gNum = 1;
        gRecord.clear();
        mission2(root, a);
    }

    void mission3() {
        
        if ( root == NULL ) {
            cout << "Tree is NULL " << endl;
        }
        BSTree* temp = findMax( root );
        Pokemon temp2 = temp->data[0];
        root = deleteNode( root, temp2 );
        
    }
};

int main() {
    PokemonList pl;
    string name, cmd;
    bool flag = false;
    cout << "**********************" << endl;
    cout << "1." << endl;
    cout << "2." << endl;
    cout << "3." << endl;
    cout << "**********************" << endl;
    cin >> cmd;
    while ( cmd != "0" ) {
        if ( cmd == "1" ) {
            cout << "Enter name: ";
            cin >> name;
            ifstream ifs("input"+name+".txt" );
            if ( ifs.good() ) {
                pl.build(name);
                pl.printAll();
                cout << "height: " << pl.height() << endl;
                flag = true;
            } 

            else {
                flag = false;
                cout << "input" << name << ".txt" << " not found" << endl;
            }
        }
        else if ( cmd == "2" ) {
            if ( flag == false ) {
                cout << "Mission1 first " << endl;
            } 

            else {
                int hp;
                cin >> hp;
                while ( ( hp <= 0 ) || (pl.findMaxHP() < hp )) {
                    if ( hp <= 0 ) {
                        cout << "Error! Must be positive integer" << endl;
                    }

                    else {
                        cout << "Number must < " << pl.findMaxHP() << endl;
                    }

                    cin >> hp;
                }

                pl.mission2(hp);
                cout << "walk through: " << gRecord.size() << endl;
            }
        }
        else if ( cmd == "3" ) {
                if ( flag == false ) {
                    cout << "Mission1 first " << endl;
                } 

                else {
                    pl.mission3();
                    cout << "height: " << pl.height() << endl;
                }
        } 

        else {
            cout << "Error!!" << endl;
        }
        cout << "Enter cmd: ";
        cin >> cmd;

    }
}