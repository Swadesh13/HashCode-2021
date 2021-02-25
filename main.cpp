#include<bits/stdc++.h>
using namespace std;

struct combo{
    set<int> pid;
    set<string> ing_list;
    int score;
};

class file_fns{
    char filename[50];
    public:
    file_fns(char* fn){
        strcpy(filename, fn);
    }
    vector<combo> create_t1(int& nop, int& T2, int& T3, int& T4){
        vector<combo> pl;
        ifstream fp(filename);
        if(fp.fail()){
            cout<<"File not opened!\n";
        }
        fp>>nop>>T2>>T3>>T4;
        for(int i=0;i<nop;i++){
            pl.push_back(combo());
            int n;
            fp>>n;
            pl[i].pid.insert(i);
            pl[i].score=n*n;
            while(n--){
                string s;
                fp>>s;
                pl[i].ing_list.insert(s);
            }
        }
        fp.close();
        return pl;
    }
};

int to_combine(combo t1){
    return *(t1.pid.rbegin());
}

vector<combo> create_next_combo(vector<combo> t1, vector<combo> t2){
    int n = t1.size(), count=0;
    vector<combo> t3;
    for(int i=0;i<t1.size();i++){
        for(int j=to_combine(t1[i])+1;j<t2.size();j++,count++){
            t3.push_back(combo());
            t3[count].pid.insert(t1[i].pid.begin(),t1[i].pid.end());
            t3[count].pid.insert(t2[j].pid.begin(),t2[j].pid.end());
            t3[count].ing_list.insert(t1[i].ing_list.begin(),t1[i].ing_list.end());
            t3[count].ing_list.insert(t2[j].ing_list.begin(),t2[j].ing_list.end());
            t3[count].score=t3[count].ing_list.size()*t3[count].ing_list.size();
        }
    }
    return t3;
}

int main(){
    char filename[] = "./Problem/a_example";
    int no_pizza, T2, T3, T4;
    file_fns ffns(filename);
    vector<combo> t1;
    t1 = ffns.create_t1(no_pizza, T2, T3, T4);
    vector<combo> t2 = create_next_combo(t1, t1);
    vector<combo> t3 = create_next_combo(t2, t1);
    vector<combo> t4 = create_next_combo(t3, t1);
    return 0;
}