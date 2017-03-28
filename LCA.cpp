#include <bits/stdc++.h>
#define nodos 1000008
#define agregar 'a'
#define consultar 'c'
using namespace std;
int memoLCA[22][nodos];
int nivel[nodos];
int tope=0;
void inicializaNiveles(){
	for(int i=1;i<nodos;i++){
		nivel[i]=-1;
	}
}
int sacaLog(int x){
    if(x==0){
        return 0;
    }
    int i=1;
    while(1 << i <=x){
        i++;
    }
    return i-1;
}
void agregarNodo(int padreDirecto){
	nivel[++tope]=nivel[padreDirecto]+1;
	memoLCA[0][tope]=padreDirecto;
	for(int log=1;1 << log <= nivel[tope];log++){///llenado de columna de DP
		memoLCA[log][tope]=memoLCA[log-1][memoLCA[log-1][tope]];
	}
}
int consultarLCA(int a,int b){
	///hacer que siempre a sea el de nivel mayor
	if(nivel[b]>nivel[a]){
		a^=b;
		b^=a;
		a^=b;
	}
	///subir "a" para emparejar
	for(int log=sacaLog(nivel[a]);log>=0;log--){
		if(nivel[memoLCA[log][a]]>=nivel[b]){
			a=memoLCA[log][a];
		}
	}
	///encontrar LCA
	for(int log=sacaLog(nivel[b]);log>=0;log--){
		if(memoLCA[log][a]!=memoLCA[log][b]){
			a=memoLCA[log][a];
			b=memoLCA[log][b];
		}
	}
	if(a==b){
		return a;
	}
	return memoLCA[0][a];
}
int main()
{
	ios_base::sync_with_stdio(0);/*cin.tie(0);*/
	inicializaNiveles();
	char com;
	int a,b;
	while(1){
		cin>>com;
		if(com==agregar){
			cin>>a;
			agregarNodo(a);
			cout<<"ya agregue\n";
		}else{
			cin>>a>>b;
			cout<<consultarLCA(a,b)<<"\n";
		}	
	}
	return 0;	
}