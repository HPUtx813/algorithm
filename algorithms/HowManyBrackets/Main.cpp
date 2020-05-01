#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
输入n表示n个括号
输出f表示n个括号可以组成的合法的括号数
*/
class option{
public:
    int n;
    int lefts;
    int rights;
    vector< vector<int> > sum;//用于存储所有可行结果
    vector< int> stack;//用于存储单个可行结果
    vector< int> test;//用于测试括号匹配
    
    option(int t){
        n = t;
        lefts = t;
        rights = t;
    }
};

bool solve(option& op,int step){
queue<int> a;

    if(step==op.n*2){
        op.sum.push_back(op.stack);
        return true;
    }
    int t = 0;
    for (int i = 0; i < 2; i++)
    {
            if(i==0&&op.lefts!=0){//当前还有左括号可以用
            //记录
                op.stack.push_back(-1);
                op.test.push_back(-1);
                op.lefts--;
                solve(op,step+1);
            //撤销
                op.stack.pop_back();
                op.test.pop_back();
                op.lefts++;
            }
            if(i==1&&op.rights!=0){//当前还有右括号可以用
                if(!op.test.empty()&&op.test.back()==-1){
            //记录
                    op.stack.push_back(1);
                    int t = op.test.back();
                    op.test.pop_back();
                    op.rights--;
                    solve(op,step+1);
            //撤销
                    op.stack.pop_back();
                    op.test.push_back(t);
                    op.rights++;
                }
            }
    }
    return false;
}

int main(){
    int t;
    cin>>t;
    option op(t);
    solve(op,0);
    for(vector<int> &i:op.sum){
        for(int& j:i){
            cout<< (j==-1?"(":")");
        }
        cout<<endl;
    }
    getchar();
    return 0;
}