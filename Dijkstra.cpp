#include<conio.h>
#include<stdio.h>
#include<limits.h>
#define MAX 100
#define VOCUC 100
#define inputfile "D:/test.txt"
#define outputfile "D:/matran.txt"
int LuuVet[MAX];
int ChuaXet[MAX];
int DoDaiDuongDiToi[MAX];
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;
//==============================================================
//================================================================
//Tim chu trinh cua do thi

//==============================================================

int DocMaTranKe(const char* T,DOTHI &g)
{	FILE* f;
	f = fopen(T,"rt");
	if(f==NULL)
	{
		printf("Khong mo duoc file\n");
		return 0;
	}
	fscanf(f,"%d",&g.n);
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++){
			fscanf(f,"%d",&g.a[i][j]);
			if(i!=j && g.a[i][j]==0)
				g.a[i][j]= INT_MAX;			
		}
	fclose(f);
	return 1;
}
//==============================================================
void XuatMaTranKe(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Ma tran ke cua do thi la:\n");
	for(int i=0;i<g.n;i++)
	{	for(int j=0;j<g.n;j++){
			if(g.a[i][j]==INT_MAX)
				printf("   -");
			else
				printf("%4d",g.a[i][j]);
		}
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
int TimDuongDiNhoNhat(DOTHI g){
	int li=-1;
	float p=VOCUC;
	for(int i=0; i<g.n; i++){
		if(DoDaiDuongDiToi[i]<p && ChuaXet[i]==0 ){
			p=DoDaiDuongDiToi[i];
			li=i;
		}
	}
	return li;
}

//==============================================================
void CapNhatDuongDi(int u, DOTHI g){
	ChuaXet[u]=1;
	for(int v=0; v<g.n; v++){
		if(ChuaXet[v]==0 && g.a[u][v]>0 && g.a[u][v]<VOCUC){
			if(DoDaiDuongDiToi[v]>DoDaiDuongDiToi[u]+g.a[u][v]){
				DoDaiDuongDiToi[v]=DoDaiDuongDiToi[u]+g.a[u][v];
				LuuVet[v]=u;
			}
		}
	}
}

int Chuyen[MAX];
//===============================================================
void Dijkstra(int S, int F, DOTHI g){
	int d=0;
	int i;
	S--;
	F--;
	for(i=0; i<g.n;i++){
		ChuaXet[i]=0;
		DoDaiDuongDiToi[i]=VOCUC;
		LuuVet[i]=-1;
	}
	DoDaiDuongDiToi[S]=0;
	while(ChuaXet[F]==0){
		int u = TimDuongDiNhoNhat(g);
		if(u==-1)
			break;
		CapNhatDuongDi(u,g);
	}
	if(ChuaXet[F]==1){
		printf("\nDuong di ngan nhat tu dinh %d toi dinh %d la: ",S+1,F+1);
		i=F;
		Chuyen[d]=F+1;
		while(LuuVet[i]!=S){
			Chuyen[++d]=LuuVet[i]+1;
			i=LuuVet[i];
		}
		Chuyen[++d]=LuuVet[i]+1;
		printf("%d",S+1);
		for(int i=d-1; i>=0; i--)
			printf("-->%d",Chuyen[i]);
		printf("\t Voi do dai la: %d",DoDaiDuongDiToi[F]);
	}
	else
	{
		printf("\nKhong co duong di tu dinh %d toi dinh %d",S+1,F+1);
	}
}
//===============================================================
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
void Floyd(DOTHI g, int S, int F){
	S--;
	F--;
	int i,j,k;
	for(i=0; i<g.n; i++)
	{
		for(j=0; j<g.n; j++)
		{
			if(g.a[i][j]>0 && g.a[i][j]<INT_MAX)
			{
				Sau_Nut[i][j]=j;
				L[i][j]=g.a[i][j];
			}
		}
	}
	for(k=0; k<g.n; k++)
	{
		for(i=0; i<g.n; i++)
		{
			for(j=0; j<g.n; j++)
			{
				if(L[i][j]>L[i][k]+L[k][j])
				{
					L[i][j]=L[i][k]+L[k][j];
					Sau_Nut[i][j]=Sau_Nut[i][k];
				}
			}
		}
	}
	if(Sau_Nut[S][F]==-1){
		printf("\nKhong co duong di!");
	}
	else{
		printf("\nDuong di ngan nhat tu %d->%d: ",S+1,F+1);
		printf("\t%d",S+1);
		int u=S;
		while(Sau_Nut[u][F]!=F){
			u=Sau_Nut[u][F];
			printf("-->%d",u+1);
		}
		printf("-->%d",F+1);
		printf("\n\tVoi tong trong so la %d",L[S][F]);
	}
}
//===============================================================

//===============================================================
int main()
{
	DOTHI g;
	const char *t;
	printf("Nhap duong dan file: ");
	scanf("%c",&t);
	if(DocMaTranKe(t, g)==1) //doc file duoc
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
	int S,F;
	printf("\nNhap diem bat dau va diem ket thuc: ");
	scanf("%d%d",&S,&F);
	int c;
	do{
		printf("\n1.Dijkstra\n2.Floyd\n0.Dung");
		scanf("%d",&c);
		switch(c){
			case 1:
				Dijkstra(S,F,g);
				break;
			case 2:
				for(int i=0; i<MAX; i++)
					for(int j=0; j<MAX; j++)
						{
			
							Sau_Nut[i][j]=-1;
							L[i][j]=VOCUC;
			
						}
				Floyd(g,S,F);
				break;
			case 0:
				return 0;
		}
	}while(c!=0); 
	return 0;
}
