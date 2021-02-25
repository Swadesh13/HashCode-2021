#include<bits/stdc++.h>
using namespace std;

class Pizza{
    int ing;
    vector<string> ing_list;
    public:
    void add_data(int i, vector<string> il){
        ing = i;
        ing_list = il;
    }
    void show_data(){
        cout<<ing<<" ";
        for(auto it=ing_list.begin(); it!=ing_list.end();it++){
            cout<<*it<<" ";
        }
        cout<<"\n";
    }
};

class Pizza_list{
    vector<Pizza> pl;
    public:
    void add_data(Pizza p){
        pl.push_back(p);
    }
    void show_data(){
        for(auto it=pl.begin(); it!=pl.end();it++){
            (*it).show_data();
        }
    }
};

class file_fns{
    char filename[50];
    public:
    file_fns(char* fn){
        strcpy(filename, fn);
    }
    void read_data(int& nop, int& T2, int& T3, int& T4, Pizza_list& pl){
        ifstream fp(filename);
        if(fp.fail()){
            cout<<"File not opened!\n";
        }
        fp>>nop>>T2>>T3>>T4;
        int i = nop;
        while(i--)
            Pizza p;
            
            pl.add_data(p);
        fp.close();
    }
};

int main(){
    char filename[] = "./Problem/a_example";
    int no_pizza, T2, T3, T4;
    file_fns ffns(filename);
    Pizza_list pl;
    ffns.read_data(no_pizza, T2, T3, T4, pl);
    cout<<no_pizza<<" "<<T2<<" "<<T3<<" "<<T4<<endl;
    pl.show_data();
    return 0;
}