#include <iostream>
#include <vector>
using namespace std;
int gcd(int a,int b){
    int tmp;
    if(a<b){
        tmp=a;
        a=b;
        b=tmp;
    }
    while(b!=0){   
        tmp=a%b;
        a=b;
        b=tmp;
    }
    return a;
}

int lcm(int a,int b){
    return a*b/gcd(a,b);
}

int main()
{
    int num;
    cin >> num;
    vector<int> factors;
    for (int i = num; i > 0; i--){
        if (num % i == 0){
            factors.push_back(i);
        }
    }

    cout<<"因子：";
    for(auto num:factors){
        cout<<num<<"  ";
    }
    cout<<endl;

    vector< vector<bool> > matrix;
    for(auto factor1:factors){
        vector<bool> line;
        for(auto factor2:factors){
            line.push_back( (factor1 % factor2)==0 );
        }
        matrix.push_back(line);
    }

    cout<<"盖住集：";
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<factors.size();j++){
            if(i==j || !matrix[i][j]) continue;
            bool flag=true;
            for(int k=0;k<factors.size();k++){
                if(k==i || k == j) continue;
                if(matrix[i][k] && matrix[k][j]){
                    flag = false;
                }
            }
            if(flag){
                cout << "(" <<factors[i] << "," << factors[j] << ")  ";
            }
        }
    }
    cout<<endl;

    bool all_flag=true;
    for(int i=0;i<matrix.size();i++){
        bool flag=false;
        for(int j=0;j<factors.size();j++){
            flag = flag || ( gcd(factors[i],factors[j]) == 1 && lcm(factors[i],factors[j]) == num );
        }
        all_flag = all_flag && flag;
    }
    if(all_flag){
        cout<<"该格是有补格。"<<endl;
    }else{
        cout<<"该格不是有补格。"<<endl;
    }

    return 0;
}