#include<bits/stdc++.h>
using namespace std;

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}

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

int sort_function(combo t1, combo t2){
    return t1.score>t2.score;
}

void compare(vector<combo> t2, vector<combo> t3, vector<combo> t4, int nop, int T2, int T3, int T4){
    set<int> select_ind;
    vector<vector<int>> pid;
    int count[]={0,0,0,0};
    // int i2=0, i3=0, i4=0;
    while(count[0]<=nop){
        int flag=0;
        if(sort_function(t3[0], t2[0]) && count[2]<T3){
            if(sort_function(t4[0], t3[0])&& count[3]<T4){
                select_ind.insert(t4[0].pid.begin(), t4[0].pid.end());
                vector<int> x;
                x.push_back(4);
                for(auto it = t4[0].pid.begin(); it!= t4[0].pid.end(); it++){
                    x.push_back(*it);
                };
                pid.push_back(x);
                count[3]+=1;
                pop_front(t4);
            }
            else{
                select_ind.insert(t3[0].pid.begin(), t3[0].pid.end());
                vector<int> x;
                x.push_back(3);
                for(auto it = t3[0].pid.begin(); it!= t3[0].pid.end(); it++){
                    x.push_back(*it);
                };
                pid.push_back(x);
                count[2]+=1;
                pop_front(t3);
            }
        }
        else if(flag==0){
            if(sort_function(t4[0], t2[0]) && count[1]<T2){
                select_ind.insert(t4[0].pid.begin(), t4[0].pid.end());
                vector<int> x;
                x.push_back(4);
                for(auto it = t4[0].pid.begin(); it!= t4[0].pid.end(); it++){
                    x.push_back(*it);
                };
                pid.push_back(x);
                count[3]+=1;
                pop_front(t4);
            }
            else{
                select_ind.insert(t2[0].pid.begin(), t2[0].pid.end());
                vector<int> x;
                x.push_back(2);
                for(auto it = t2[0].pid.begin(); it!= t2[0].pid.end(); it++){
                    x.push_back(*it);
                };
                pid.push_back(x);
                count[1]+=1;
                pop_front(t2);
            }
        }
        count[0]+=count[1]*2+count[2]*3+count[3]*4;
    }
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
    sort(t2.begin(), t2.end(), sort_function);
    sort(t3.begin(), t3.end(), sort_function);
    sort(t4.begin(), t4.end(), sort_function);
    compare(t2, t3, t4, no_pizza, T2, T3, T4);
    return 0;
}