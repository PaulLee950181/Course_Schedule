#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>

using namespace std;

struct lec
{
    char color;
    int num;
    lec *next;
    vector<lec*> AF;
    lec()
    {
        color = 'W';
        next = NULL;
    }
};


struct DFS
{
    lec *root;
	char *out;
    DFS( char *argv )
    {
        root = new lec;
		out = argv;
    }
    void DFS_V( lec *u )
    {
        u->color = 'G';
        int n = u->AF.size();
        if( n > 0 ){
            for( int i = 0 ; i < n ; i++ ){
                if( u->AF[i]->color == 'W' ){
                    DFS_V( u->AF[i] );
                }
                else if( u->AF[i]->color == 'G' ){
                    print();
                    exit(0);
                }
            }
        }
        u->color = 'B';
        u->next = root->next;
        root->next = u;
    }
	void print()
	{
		ofstream output1(out);
		output1 << "Conflict";
		output1.close();
	}
};



int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    DFS x(argv[2]);
    int n;
    lec *ptr;
    input >> n;
    vector<lec> cond(n);
    for( int j = 0 ; j < n ; j++ ){
        cond[j].num = j;
    }
    int before, after;
    while( input >> after >> before ){
        ptr = &cond[after];
        cond[before].AF.push_back(ptr);
    }
    for( int i = 0 ; i < n ; i++ ){
        if( cond[i].color == 'W' ){
            ptr = &cond[i];
            x.DFS_V( ptr );
        }
    }
    ofstream output(argv[2]);
    lec *y = x.root->next;
    while( y != NULL ){
        output << y->num << " ";
        y = y->next;
    }
    input.close();
    output.close();
    return 0;
}

