#include<bits/stdc++.h>
using namespace std;
const int N=2e7+10;
int n,m,c;
int u[N],v[N];
int main(){
    freopen("5000_500000.txt","w",stdout);
    n=5000,m=500000;
   for(int i=1;i<=m;i++){
        int x=rand()%n+1,y=rand()%n+1;
        if(x>y)swap(x,y);
        if(x==y){
            i--;continue;
        }
        int fl=0;
        for(int j=1;j<i;j++){
            if(u[j]==x&&v[j]==y){
                fl=1,i--;break;
            }
        }
        if(!fl){
            u[i]=x,v[i]=y;
        }
    }
    printf("%d %d\n",n,m);
    for(int i=1;i<=m;i++)
        printf("%d %d\n",u[i],v[i]);
 
    return 0;
}
