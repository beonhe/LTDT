#include<conio.h>
#include<stdio.h>
#include<limits.h>
#define MAX 100
#define VOCUC 100000
#define inputfile "D:/test1.txt"
#define outputfile "D:/matran.txt"
int Sau_Nut[MAX][MAX];
int L[MAX][MAX];
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;
//==============================================================
//================================================================
//Tim chu trinh cua do thi

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
	{	for(int j=0;j<g.n;j++){
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
void Floyd(DOTHI g)
{
	int i,j;
	for(i=1;i<=g.n;i++)
	{
		for(j=1;j<=g.n;j++)
		{
			if(g.a[i][j]>0)
			{
				Sau_Nut[i][j]=j;
				L[i][j]=g.a[i][j];
			}
			else
			{
				Sau_Nut[i][j]=-1;
				L[i][j]=VOCUC;
			}
		}
	}
	for(int k=1;k<=g.n;k++)
	{
		for(i=1;i<=g.n;i++)
		{
			for(j=1;j<=g.n;j++)
			{
				if(L[i][j]>L[i][k]+L[k][j])
				{
					L[i][j]=L[i][k]+L[k][j];
					Sau_Nut[i][j]=Sau_Nut[i][k];
				}
			}
		}
	}
	int S,F;
	printf("\nnhap dinh bat dau");
	scanf("%d",&S);
	printf("\nnhap dinh ket thuc");
	scanf("%d",&F);
	if(Sau_Nut[S][F]==-1)
	{
		printf("ko co duong di");
	}
	else{
		printf("\nduong di ngan nhat tu dinh %d den dinh %d\n",S,F);
		printf("\t%d",S);
		int u=S;
		while(Sau_Nut[u][F]!=F)
		{
			u=Sau_Nut[u][F];
			printf("->%d",u);
		}
	}
	printf("->%d",F);
	printf("\nvoi tong trong so la %d",L[S][F]);
}

//==============================================================

//===============================================================

//===============================================================

//===============================================================
int main()
{
	DOTHI g;
	if(DocMaTranKe(inputfile, g)==1) //doc file duoc
	{
		printf("Da lay thong tin do thi tu file thanh cong.\n\n");
		if(KTMaTranKe(g)==1){
		printf("\nDay la ma tran ke hop le:");
		}
	}
	else
		return 0;//khong doc duoc thi dung lai
	//=======================================================
	//xuat do thi, neu la vo huong thi xuat thong tin cua dt vo huong, co huong thi xuat thong tin dt co huong
	XuatMaTranKe(g);
	if(KiemTra(g)==0){
		printf("Do thi vo huong:");
		XuatVoHuong(g);
	}
	else{
		printf("Do thi co huong:");
		XuatCoHuong(g);
	}
	Floyd(g);
	return 0;
}
