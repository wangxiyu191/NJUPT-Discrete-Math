#include <iostream>
#include <cstring>
#include <cstdio>
using std::cin;
using std::cout;
using std::endl;

bool checkReflexivity(int n, const bool **r ){
    bool result=true;
    for(int i=0;i<n;i++){
        if(!r[i][i]){
            cout<<i<<endl;
            result = false;
            break;
        }
    }
    return result;
}

bool checkAntiReflexivity(int n, const bool **r ){
    bool result=true;
    for(int i=0;i<n;i++){
        if(r[i][i]){
            result = false;
            break; 
        }
    }
    return result;
}

bool checkSymmetry(int n, const bool **r ){
    bool result=true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(r[i][j]!=r[j][i]){
                result=false;
                break;
            }
        }
    }
    return result;
}
bool checkAntiSymmetry(int n, const bool **r ){
    bool result=true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(r[i][j]==r[j][i]){
                result=false;
                break;
            }
        }
    }
    return result;
}

bool checkTransitivity(int n, const bool **r){
    bool result=true;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(!r[i][j] && (r[i][k] && r[k][j])){
                    result=false;
                    goto END;
                }
            }
        }
    }
    END:
    return result;
}

int main(int argc, char const *argv[])
{
    cout<<"请输入集合内元素个数："<<endl;
    int n;
    cin>>n;
    cout<<"集合中元素代号为: ";
    for(int i=0;i<n;i++){
        cout<<i<<" ";
    }
    cout<<endl;
    bool* relation[n];
    for(int i=0;i<n;i++){
        relation[i]=(bool *)malloc(n*sizeof(bool));
    }

    cout <<"请输入关系数量："<<endl;
    int relation_num;
    cin>>relation_num;
    for(int i=0;i<relation_num;i++){
        cout<<"请输入第"<<i+1<<"组关系 (x y)"<<endl;
        int x,y;
        cin>>x>>y;
        relation[x][y]=true;
        relation[y][x]=true;
    }

    if(checkReflexivity(n,(const bool**)relation)){
        cout<<"满足自反性"<<endl;
    }
    if(checkAntiReflexivity(n,(const bool**)relation)){
        cout<<"满足反自反性"<<endl;
    }
    if(checkSymmetry(n,(const bool**)relation)){
        cout<<"满足对称性"<<endl;
    }
    if(checkAntiSymmetry(n,(const bool**)relation)){
        cout<<"满足反对称性"<<endl;
    }
    if(checkTransitivity(n,(const bool**)relation)){
        cout<<"满足传递性"<<endl;
    }



    return 0;
}

