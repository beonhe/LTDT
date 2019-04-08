#include<conio.h>
#include<stdio.h>

#define MAX 100
#define inputfile "D:/DFS.txt"
#define outputfile "D:/matran.txt"
int LuuVet[MAX];
int ChuaXet[MAX];
int Duong[MAX];
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;
//==============================================================
struct QUEUE
{
	int size;
	int array[MAX];
};
void InitQ(QUEUE &q){
	q.size=0;
}
int PushQ(QUEUE &q, int value){
	if(q.size+1>=100)
		return 0;
	q.array[q.size]=value;
	q.size++;
	return 1;
}
int PullQ(QUEUE &q, int &value){
	if(q.size<=0)
		return 0;
	value=q.array[0];
	for(int i=0; i<q.size-1; i++){
		q.array[i]=q.array[i+1];
	}
	q.size--;
	return 1;
}
int isEmptyQ(QUEUE q){
	if(q.size<=0)
		return 1;
	return 0;
}
//==============================================================
struct STACK
{
	int array[100];
	int size;
};
void Init(STACK &stack){
	stack.size=0;
}
void Push(STACK &st, int value){
	if(st.size+1>=100){
		return;
	}
	st.array[st.size]=value;
	st.size++;
}
//================================================================
//Tim chu trinh cua do thi
void TimDuong(int i, DOTHI &g, STACK &st){
	for(int j=0; j<g.n; j++){
		if(g.a[i][j]!=0){
			g.a[i][j]=g.a[j][i]=0;
			TimDuong(j,g,st);
		}
	}
	Push(st,i);
	
}
//==============================================================

int DocMaTranKe(const char* TenFile,DOTHI &g)
{	FILE* f;
	f = fopen(TenFile,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++){
			fscanf(f,"%d",&g.a[i][j]);			
		}
	fclose(f);
	return 1;
}
//==============================================================
void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			printf("%4d",g.a[i][j]);
		printf("\n");
	}
}
//==============================================================
void XuatFileMaTran(const char* TenFile,DOTHI &g)
{	
	FILE* f;
	f = fopen(TenFile,"wt");
	fprintf(f,"%d",g.n);
	fprintf(f,"\n");
	for(int i=0;i<g.n;i++){
		for(int j=0;j<g.n;j++)
			fprintf(f,"%d    ",g.a[i][j]);
		fprintf(f,"\n");
	}
	fclose(f);
}
//==============================================================
//Kien tra la do thi vo huong hay co huong, dua vao tinh doi xung cua  ma tran
int KiemTra(DOTHI g)
{
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++)
			if(g.a[i][j]!=g.a[j][i]){
				return 1;
			}
	}
	return 0;
}
//==============================================================
void XuatVoHuong(DOTHI g)
{	
	printf("So dinh cua do thi = %d\n",g.n);
	printf("Danh sach canh cua do thi la:\n");
	int canh=0;
	int bac[g.n];
	for(int i=0;i<g.n;i++)
	{	
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]!=0 && i<j){
				printf("%d %d: %d\n",i+1,j+1,g.a[i][j]);
				canh++;
			}
		
	}	
	for(int i=0;i<g.n;i++)
	{
		bac[i]=0;	
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]!=0){
				bac[i]++;
			}
		printf("Dinh %d co bac: %d\n",i+1,bac[i]);
	}
	printf("So canh cua ma tran la: %d",canh);
}
//==============================================================
void XuatCoHuong(DOTHI g)
{	
	printf("So dinh cua do thi = %d\n",g.n);
	printf("Danh sach canh cua do thi la:\n");
	int canh=0;
	int br[g.n], bv[g.n];
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]!=0){
				printf("%d %d: %d\n",i+1,j+1,g.a[i][j]);
				canh++;
			}
	}
	for(int i=0;i<g.n;i++)
	{
		br[i]=0;
	
		for(int j=0;j<g.n;j++){
			if(g.a[i][j]!=0)
				br[i]++;
				bv[j]=0;
			for(int l=0; l<g.n; l++){
				
				if(g.a[l][j]!=0)
					bv[j]++;
			}
		}
		printf("Dinh %d co ban bac ra = %d, bac vao = %d\n",i+1,br[i],bv[i]);
		
	}
	printf("So canh cua ma tran la: %d",canh);
}
//==============================================================
//kiem tra xem ma tran nhap vao co phai la ma tran ke hay khong, duong cheo=0;
int KTMaTranKe(DOTHI g){
	for(int i=0; i<g.n; i++)
		{
			if(g.a[i][i]!=0)
				return 0;
		}
	return 1;
}
//==============================================================
void DiTimCacDinhLienThong (DOTHI g, int nhan[MAX], int i) 
{ 
        for (int j = 0; j < g.n; j++) 
        { 
               if (g.a[i][j] != 0 && nhan[j]  != nhan[i])
                { 
                       nhan[j] = nhan[i]; 
                       DiTimCacDinhLienThong (g, nhan, j);
                } 
        } 
} 
//===============================================================
void XetLienThong(DOTHI g) 
{ 
        int Nhan[MAX]; 
        int i; 
        for (i=0;i<g.n;i++)
               Nhan[i] =0; 
        int SoThanhPhanLT = 0;
        for (i=0; i<g.n; i++) 
        { 
               if (Nhan[i] == 0)  
                { 
                       SoThanhPhanLT ++; 
                       Nhan[i] = SoThanhPhanLT; 
                       DiTimCacDinhLienThong(g, Nhan, i);
               } 

        }
        if(SoThanhPhanLT==1)
        {
        	printf("\nDo thi lien thong!");
		}
		else
			printf("\nDo thi khong lien thong!");
        printf("\nSo than phan lien thong la: %d",SoThanhPhanLT);
		for(i=1; i<=SoThanhPhanLT; i++)
        {
	        	printf("\nThan phan lien thong thu %d gom cac dinh: ",i);
				for(int j=0; j<g.n; j++){
					if(Nhan[j]==i)
						printf("%2d",j+1);
				}
				printf("\n");
		}
}
//=============================================================
void DFSS(DOTHI g, int i, int LT[]){
	printf("%4d",i+1);
	LT[i]=1;//danh dau da kiem tra dinh i
	for(int j=0; j<g.n; j++)
		if(LT[j]==0 && g.a[i][j]==1)//neu dinh j chua xet va co canh ij thi thuc hien
			DFSS(g,j, LT);
}
void DFS2(DOTHI g,int LT[]){
	for(int i=0; i<g.n; i++){//Khoi tao do thi khong lien thong
		LT[i]=0;
	}
	printf("\n");
	int dem=1;//dem so thanh phan lien thong
	printf("Thanh phan lien thong thu %d: ",dem);
	DFSS(g,0,LT);//kiem tra thanh phan lien thong bat dau tu dinh 0
	for(int i=0; i<g.n; i++)
		if(LT[i]==0){
			dem++;
			printf("\n");
			printf("Thanh phan lien thong thu %d: ",dem);
			DFSS(g,i,LT);
		}
	printf("\nDo thi co %d thanh phan lien thong",dem);
}
//==============================================================
int KTCTEuler(DOTHI g){
	int br[g.n], bv[g.n];
	int bac[g.n];
	if(KiemTra(g)==0){
		for(int i=0;i<g.n;i++)
		{
			bac[i]=0;	
			for(int j=0;j<g.n;j++)
				if(g.a[i][j]!=0){
					bac[i]++;
				}
			if(bac[i]%2==1){
				return 0;
			}
		}
	}
	else{
		for(int i=0;i<g.n;i++)
		{
		br[i]=0;
	
		for(int j=0;j<g.n;j++){
			if(g.a[i][j]!=0)
				br[i]++;
				bv[j]=0;
			for(int l=0; l<g.n; l++){
				
				if(g.a[l][j]!=0)
					bv[j]++;
			}
		}
		if(br[i]!=bv[i])
			return 0;
		}
	}
	return 1;
}
//===============================================================
int KTDDEuler(DOTHI g){
	int br[g.n], bv[g.n];
	int bac[g.n];
	int dem=0;
	if(KiemTra(g)==0){
		for(int i=0;i<g.n;i++)
		{
			bac[i]=0;	
			for(int j=0;j<g.n;j++)
				if(g.a[i][j]!=0){
					bac[i]++;
				}
			if(bac[i]%2==1){
				dem++;
			}
		}
		if(dem!=2)
			return 0;
	}
	else{
		for(int i=0;i<g.n;i++)
		{
		br[i]=0;
	
		for(int j=0;j<g.n;j++){
			if(g.a[i][j]!=0)
				br[i]++;
				bv[j]=0;
			for(int l=0; l<g.n; l++){
				
				if(g.a[l][j]!=0)
					bv[j]++;
			}
		}
		if(br[i]!=bv[i])
			return 0;
		}
	}
	return 1;
	
}
//==============================================================
int CTEuler(DOTHI g, STACK &st)
{
	int i,j;
	int x = 0; 
	int flag = 0;
	//Tim diem x la diem bat dau tim chu trinh Euler, diem x phai co bac >0;
	for(int i=0; i<g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			if (g.a[i][j] != 0) 
			{
				x=i;//lay diem x la diem dau tien dc tim thay co bac >0
				flag=1;
				break;
			}
		} 
		if(flag==1)
				break;
	
	}
	DOTHI temp = g; //copy do thi g sang do thi temp de xu ly tren temp
	TimDuong(x,temp, st);//tim chu trinh Euler tren do thi temp bang cach xoa canh
	//Neu con co canh chua xoa thi khong co chu trinh Euler
	for (i = 0; i < temp.n; i++)
	{
		for (j = 0; j < temp.n; j++)
		{
			if (temp.a[i][j] != 0) 
				return 0;
		}
	}
	if (st.array[st.size - 1] != st.array[0])
		return 0;
	return 1; 
}

//===============================================================
void DFS(int v, DOTHI g){
	ChuaXet[v]=1;
	int u;
	for(u=0; u<g.n; u++){
		if(g.a[v][u]!=0 && ChuaXet[u]==0){
			LuuVet[u]=v;
			DFS(u,g);
		}
	}
}
int Stack[MAX];
int Free[MAX];
int Trace[MAX];
int S,F,Last=0;
void PushS(int v){
	Last++;
	Stack[Last]=v;
}
int PopS(){
	int x=Stack[Last];
	Last--;
	return x;
}
void StackDFS(DOTHI g){
	int u,v;
	printf("%d",S+1);
	ChuaXet[S]=1;
	PushS(S);
	do{
		u=PopS();
		for(v=0; v<g.n;v++){
			if(ChuaXet[v]==0 && g.a[u][v]!=0)
			{
				printf("%d",v);
				ChuaXet[v]=1;
				LuuVet[v]=u;
				PushS(u);
				PushS(v);
				break;
			}
		}
	}while(Last!=0);
}
void StackDuyetDFS(DOTHI g, int S, int F){
	S--;
	F--;
	int i;
	int dem=-1;
	for(i=0; i<g.n; i++){
		LuuVet[i]=-1;
		ChuaXet[i]=0;
		Duong[i]=-1;
	}
	StackDFS(g,S);
	if(ChuaXet[F]==1){
		printf("\n%d->%d:",S+1,F+1);
		i=F;
		dem++;
		Duong[dem]=F+1;
		while(LuuVet[i]!=S){
			dem++;
			Duong[dem]=LuuVet[i]+1;
			i=LuuVet[i];
		}
		dem++;
		Duong[dem]=LuuVet[i]+1;
		for(int i=dem; i>=0; i--)
			printf("%2d",Duong[i]);
	}
	else{
		printf("\nKhong co duong di");
	}
}
//===============================================================
void DuyetDFS(int S, int F, DOTHI g){
	S--;
	F--;
	int i;
	int dem=-1;
	for(i=0; i<g.n; i++){
		LuuVet[i]=-1;
		ChuaXet[i]=0;
		Duong[i]=-1;
	}
	DFS(S,g);
	if(ChuaXet[F]==1){
		printf("\n%d->%d:",S+1,F+1);
		i=F;
		dem++;
		Duong[dem]=F+1;
		while(LuuVet[i]!=S){
			dem++;
			Duong[dem]=LuuVet[i]+1;
			i=LuuVet[i];
		}
		dem++;
		Duong[dem]=LuuVet[i]+1;
		for(int i=dem; i>=0; i--)
			printf("%2d",Duong[i]);
	}
	else{
		printf("\nKhong co duong di");
	}
}
//===============================================================

void BFS(int v, DOTHI g){
	QUEUE q;
	InitQ(q);
	PushQ(q,v);
	while(!isEmptyQ(q)){
		PullQ(q,v);
		ChuaXet[v]=1;
		for(int u=0; u<g.n; u++){
			if(g.a[v][u]!=0 && ChuaXet[u]==0){
				PushQ(q,u);
				LuuVet[u]=v;
			}
		}
	}
}
void DuyetBFS(int S, int F, DOTHI g){
	S--;
	F--;
	int i;
	for(i=0; i<g.n; i++){
		LuuVet[i]=-1;
		ChuaXet[i]=0;
	}
	BFS(S,g);
	if(ChuaXet[F]==1){
		printf("\n%d->%d:",S+1,F+1);
		i=F;
		printf("%d",F+1);
		while(LuuVet[i]!=S){
			printf("%3d",LuuVet[i]+1);
			i=LuuVet[i];
		}
		printf("%3d",LuuVet[i]+1);
	}
	else{
		printf("\nKhong co duong di");
	}
}

//===============================================================
int main()
{
	STACK st;
	Init(st);
	DOTHI g;
	int LT[MAX];
	if(DocMaTranKe(inputfile, g)==1) //doc file duoc
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		if(KTMaTranKe(g)==1){
		printf("\nDay la ma tran ke hop le:");
		XuatMaTranKe(g);
		}
	}
	else
		return 0;//khong doc duoc thi dung lai
	//=======================================================
	//xuat do thi, neu la vo huong thi xuat thong tin cua dt vo huong, co huong thi xuat thong tin dt co huong
	if(KiemTra(g)==0){
		printf("Do thi vo huong:");
		XuatVoHuong(g);
	}
	else{
		printf("Do thi co huong:");
		XuatCoHuong(g);
	}
	//===============================================================
/*	if(KTCTEuler(g)==1){
		if(CTEuler(g,st)==1){//neu co chu trinh Euler thi xuat ra
			printf("\nChu trinh Euler cua do thi la: ");
			for(int i = st.size - 1; i >= 0 ; i--) 
				printf("%2d ",st.array[i] + 1);
		}
	}
	else//neu khong co thi bao khong co
		printf("\nDo thi khong co chu trinh Euler");*/
	DuyetBFS(3,6,g);
	return 0;
}
