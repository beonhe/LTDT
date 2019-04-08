//dfs de quy
int LuuVet[MAX];
int ChuaXet[MAX];
void KhoiTao(){
	for(int i=1;i<=MAX;i++){
	//	LuuVet[i]=-1;
		ChuaXet[i]=1;
	}
}
void DFS(int v,DOTHI g){
	ChuaXet[v]=0;
	printf("%2d",v);
	for(int i=1;i<=g.n;i++){
		if(ChuaXet[i]==1&&g.a[v][i]!=0){
			DFS(i,g);
		}
	}
	
}
//bfs ko de quy
void BFS(int u,DOTHI g){
	int queue[MAX], dau=0,cuoi=0;
  	for(int i=1;i<=MAX;i++) queue[i]=0;
   	 	queue[cuoi]=u;
   		ChuaXet[u]=0;
   		printf("%2d",u);
  
	while(dau>=cuoi)
 	{
  	  	int p=queue[cuoi];
 	   	cuoi++;
 	  	for(int i=1;i<=g.n;i++)
  	   		if(ChuaXet[i]==1&&g.a[p][i]!=0)
  	   		{ 
 	      		dau++;
    	    	queue[dau]=i;
  	      		ChuaXet[i] =0;
   	     		printf("%2d",i);
  	 	 	}
  	 }
}
