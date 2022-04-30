#include "Lexical_scanning.cpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include<fstream>  //ifstream
#include <io.h>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

unordered_map<string , string> Syn_G;
unordered_map<char , int> Syn_state_kinds;
void init_Syn_G(){
    Syn_state_kinds['E'] = 2;
    Syn_state_kinds['T'] = 2;
    Syn_state_kinds['S'] = 2;
    Syn_G["E1"] = "Tfbea";  //E -> aebfT    这里直接进行逆序处理
    Syn_G["E2"] = "Tfe";    //E -> efT
    Syn_G["T1"] = "SbTa";   //T->aTbS
    Syn_G["T2"] = "Se";     //T -> eS;
    Syn_G["S1"] = "Tc";     //S->cT;
    Syn_G["S2"] = "Td";     //S->dT;
    //Syn_G["S3"] = "0";      //S -> ε  
}

//将词法扫描到的字符，转译为语法分析的状态符号
char Lex2Syn(int Lex_id);

//获得当前队列
int get_check_str(int now_index , vector< pair<string , int> > now , queue<char>& LexId_q);

string Syn_op(char now_state , char now_c);

bool check_LL_1(vector< pair<string , int> > now);


bool check_SLR(vector< pair<string , int> > now);

//
unordered_map<int , vector<pair<char , int > > > LR_map;
unordered_map<int,vector<string> > LR_reduce; 
void init_LR_map(){

    //reduce , 做逆栈处理，方便后续出栈
    LR_reduce[1] = {"Tfbea" , "E"};     //aebfT
    LR_reduce[2] = {"Tfe" , "E"};       //efT
    LR_reduce[3] = {"SbTa" , "T"};      //aTbS
    LR_reduce[4] = {"Se" , "T"};        //eS
    LR_reduce[5] = {"T*" , "S"};        //*T              做特殊处理，将cd合并为*，简化代码过程
    //LR_reduce[6] = {"dT" , "S"};
    LR_reduce[6] = {"e" , "T"};
    LR_reduce[7] = {"bTa" , "T"};       //aTb          

    vector< pair<char , int > > tmp;
    //0
    tmp.push_back(make_pair('a' , 2));
    tmp.push_back(make_pair('e' , 7));
    tmp.push_back(make_pair('E' , 1));
    LR_map[0] = tmp;
    tmp.clear();
    //1
    //2
    tmp.push_back(make_pair('e' , 3));
    LR_map[2] = tmp;
    tmp.clear();
    //3
    tmp.push_back(make_pair('b' , 4));
    LR_map[3] = tmp;
    tmp.clear();    

    //4
    tmp.push_back(make_pair('f' , 5));
    LR_map[4] = tmp;
    tmp.clear();
    //5
    tmp.push_back(make_pair('a' , 10));
    tmp.push_back(make_pair('e' , 14));
    tmp.push_back(make_pair('T' , 6));
    LR_map[5] = tmp;
    tmp.clear();
    //6
    // tmp.push_back(make_pair('R' , 1));
    // LR_map[6] = tmp;
    // tmp.clear();
    //7
    tmp.push_back(make_pair('f' , 8));
    LR_map[7] = tmp;
    tmp.clear();
    //8
    tmp.push_back(make_pair('a' , 10));
    tmp.push_back(make_pair('e' , 14));
    tmp.push_back(make_pair('T' , 9));
    LR_map[8] = tmp;
    tmp.clear();
    //9
    // tmp.push_back(make_pair('R' , 2));
    // LR_map[9] = tmp;
    // tmp.clear();
    //10
    tmp.push_back(make_pair('a' , 10));
    tmp.push_back(make_pair('e' , 14));
    tmp.push_back(make_pair('T' , 11));
    LR_map[10] = tmp;
    tmp.clear();
    //11
    tmp.push_back(make_pair('b' , 12));
    LR_map[11] = tmp;
    tmp.clear();
    //12
    tmp.push_back(make_pair('c' , 16));
    tmp.push_back(make_pair('d' , 16));
    tmp.push_back(make_pair('S' , 13));
    tmp.push_back(make_pair('~' , 7));
    LR_map[12] = tmp;
    tmp.clear();
    //13
    // tmp.push_back(make_pair('R' , 3));
    // LR_map[13] = tmp;
    // tmp.clear();
    //14
    tmp.push_back(make_pair('c' , 16));
    tmp.push_back(make_pair('d' , 16));
    tmp.push_back(make_pair('S' , 15));
    tmp.push_back(make_pair('?' , 6));
    LR_map[14] = tmp;
    tmp.clear();
    //15
    // tmp.push_back(make_pair('R' , 4));
    // LR_map[15] = tmp;
    // tmp.clear();
    //16
    tmp.push_back(make_pair('a' , 10));
    tmp.push_back(make_pair('e' , 14));
    tmp.push_back(make_pair('T' , 17));
    LR_map[16] = tmp;
    tmp.clear();
    //17
    // tmp.push_back(make_pair('R' , 5));
    // LR_map[17] = tmp;
    // tmp.clear();

    return ;
}


//LR文法
pair<char ,int> Syn2State(pair<char , int> now_sT , char now_c);

bool check_SLR(vector< pair<string , int> > now);


int main(){

    //获得词法分析之后的表格
    vector< pair<string , int> > now;
    now = Lexical_scanning();
    int op = 0;
    cout<<"plz input whitch you want to play:"<<endl;
    cout<<"1 : LL(1)"<<endl;
    cout<<"2 : LR"<<endl;
    cin>>op;
    if(op == 1){
        check_LL_1(now);
    }
    else if(op == 2){
        init_LR_map();
        check_SLR(now);
    }
    else{
        cout<<"error choice"<<endl;
    }
    // check_LL_1(now);
    //cout<<LR_map[0].size()<<" "<<LR_map[2].size()<<endl;
    return 0;
}

//LR文法



pair<char ,int> Syn2State(pair<char , int> now_sT , char now_c){
    int state = now_sT.second;
    
    vector< pair<char , int > > check = LR_map[state];
    
    //归约状态
    switch (state){
        case 6:
            return make_pair('R' , 1);
        case 9: 
            return make_pair('R' , 2);
        case 13:
            return make_pair('R' , 3);
        case 15:
            return make_pair('R' , 4);
        case 17:
            return make_pair('R' , 5);
    }


    for(int i = 0 ; i < check.size(); i++){
        if(check[i].first == now_c){
            return check[i];
        }
        else if(check[i].first == '?'){
            return make_pair('R' , 6);
        }
        else if(check[i].first == '~'){
            return make_pair('R' , 7);
        }
    }
    // for(int i = 0 ; i < check.size() ; i++){
    //     cout<<check[i].first<<" "<<check[i].second<<endl;
    // }
    // cout<<now_sT.first<<" "<<now_sT.second<<" "<<now_c<<endl;
    return make_pair('!' , -1);


}

bool check_SLR(vector< pair<string , int> > now){

    int n = now.size();


    int now_index = 0;
    int line_count = 0;
    while(now_index < n){
        line_count++;
        queue<char> LexId_q;
        now_index = get_check_str(now_index , now , LexId_q);
        if(now_index < 0){
            cout<<"error! can't get right str from Lex_scanning. line : "<<line_count<<endl;
            return false;
        }
        // while(!LexId_q.empty()){
        //     cout<<LexId_q.front();
        //     LexId_q.pop();
        // }
        // cout<<endl;
        stack<pair<char , int> > Syn_stack;
        Syn_stack.push(make_pair('#' , 0));
        //int right_count = 1;
        //int now_state = 0;
        while(!Syn_stack.empty()){
            pair<char ,int> now_sT = Syn_stack.top();
            if(now_sT.first == 'E' && now_sT.second == 1 && LexId_q.front() == '#'){
                cout<<"true. line: "<<line_count<<endl;
                break;
            }
                
            
            char now_c = LexId_q.front();
            // cout<<"asdadsd:"<<endl;
            // cout<<now_c<<endl;
            pair<char ,int> next_sT = Syn2State(now_sT , now_c);

            if(next_sT.first == '!'){
                cout<<"false: can't get right next_state. line : "<<line_count<<endl;
                // while(!LexId_q.empty()){
                //     cout<<LexId_q.front();
                //     LexId_q.pop();
                // }
                // cout<<endl;    
                // while(!Syn_stack.empty()){
                //     cout<<Syn_stack.top().first<<" "<<Syn_stack.top().second<<endl;
                //     Syn_stack.pop();
                //     cout<<endl;
                // } 
                break;           
                //return false;
            }
            //cout<<next_sT.first<<" "<<next_sT.second<<" "<<now_c<<endl;
            if(next_sT.first == 'R'){
                vector<string> reduce_tmp = LR_reduce[next_sT.second];
                if(next_sT.second == 5){
                    for(char c : reduce_tmp[0]){
                        pair<char ,int> tmp_sT = Syn_stack.top();
                        if(tmp_sT.first == c){
                            Syn_stack.pop();
                        }
                        else if(c == '*'){
                            if(tmp_sT.first == 'c' || tmp_sT.first == 'd'){
                                Syn_stack.pop();
                            }
                            else{
                                cout<<"false : Reduce *T the 5th is error. line : "<<line_count<<endl;
                                break;
                                //return false;                                
                            }
                        }
                        else{
                            cout<<"false"<<endl;
                            break;
                            //return false;
                        }
                    }
                }
                else{
                    for(char c : reduce_tmp[0]){
                        pair<char ,int> tmp_sT = Syn_stack.top();
                        if(tmp_sT.first == c){
                            Syn_stack.pop();
                        }
                        else{
                            cout<<"false : Reduce the "<< next_sT.second <<"th is error. line:"<<line_count<<endl;
                            //return false;
                            break;
                        }
                    }
                }
                now_sT = Syn_stack.top();
                pair<char ,int> next_sT = Syn2State(now_sT , reduce_tmp[1][0]);
                Syn_stack.push(next_sT);
            }
            else{
                Syn_stack.push(next_sT);
                LexId_q.pop();
            }
        }
        //cout<<"true"<<endl;
    }
    return true;
}



//LL文法
char Lex2Syn(int Lex_id){
    if(Lex_id >= 4 && Lex_id <= 36){
        return 'n';
    }
    else if(Lex_id >= 59 && Lex_id <= 69){
        return 'f';
    }
    switch (Lex_id){
        case 70:
            return 'a';
        case 71:
            return 'b';
        case 40:
        case 41:
            return 'c';
        case 37:
        case 38:
        case 39:
            return 'd';
        case 0:
        case 3:
            return 'e';
        // case 59:
        //     return 'f';
        case 78:
            return '#';
    }
    return '!';
}

int get_check_str(int now_index , vector< pair<string , int> > now , queue<char>& LexId_q){
    while(now_index < now.size()){
        char c = Lex2Syn(now[now_index].second);
        now_index++;
        if(c == 'n')
            continue;
        if(c == '#'){
            LexId_q.push(c);
            return now_index;
        }
        else if(c == '!'){
            //cout<<c<<" "<<now[now_index].second<<" "<<now[now_index].first<<endl;
            return -1;
        }
            
        LexId_q.push(c);
    }
    return -1;
}


string Syn_op(char now_state , char now_c){
    if(now_state == now_c)
        return "allpop";
    //matching
    int kinds = Syn_state_kinds[now_state];
    for(int i = 1 ; i <= kinds ; i++){
        string tmp;
        tmp += now_state;
        tmp += to_string(i);
        string now_tmp = Syn_G[tmp];
        if(now_tmp[now_tmp.size()-1] == now_c){
            //cout<<now_tmp<<endl;
            return now_tmp;
        }
    }
    //S -> ε 
    if(now_state == 'S')
        return "0";

    return "notfind";
}


bool check_LL_1(vector< pair<string , int> > now){

    int n = now.size();
    //起始栈
    init_Syn_G();


    int now_index = 0;
    int right_count = 0;
    while(now_index < n){
        right_count++;
        queue<char> LexId_q;
        now_index = get_check_str(now_index , now , LexId_q);
        if(now_index < 0){
            cout<<"error: the now_index < 0. line : "<<right_count<<endl;
            return false;
        }
        // while(!LexId_q.empty()){
        //     cout<<LexId_q.front();
        //     LexId_q.pop();
        // }
        // cout<<endl;
        stack<char> Syn_stack;
        Syn_stack.push('#');
        Syn_stack.push('E');
        while(!Syn_stack.empty()){
            char now_state = Syn_stack.top();
            Syn_stack.pop();
            char now_c = LexId_q.front();

            //cout<<now_state<<"  "<<now_c<<endl;
            

            if(now_state == '#' && now_c == '#'){
                cout<<"true"<<right_count<<endl;
                break;
            }
            string res = Syn_op(now_state , now_c);
            if(res == "notfind"){
                cout<<"error : notfind. line :"<<right_count<<endl;
                // while(!Syn_stack.empty()){
                //     cout<<Syn_stack.top();
                //     Syn_stack.pop();
                // }
                // cout<<endl;
                // while(!LexId_q.empty()){
                //     cout<<LexId_q.front()<<endl;
                //     LexId_q.pop();
                // }
                // cout<<endl;
                //return false;
                break;
            }
            else if(res == "0"){
                continue;
            }
            else if(res == "allpop"){
                LexId_q.pop();
                continue;
            }
            for(char c : res){
                Syn_stack.push(c);
            }
        }
    }
    return true;

}