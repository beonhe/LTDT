#include<conio.h>
#include<stdio.h>

#define MAX 10
#define inputfile "C:/Users/Administrator/Desktop/THLTDT/Bo du lieu test/test2.txt"
#define outputfile "C:/Users/Administrator/Desktop/THLTDT/Bo du lieu test/matran.txt"
typedef struct GRAPH
{	int n;
	int a[MAX][MAX];
}DOTHI;

//==============================================================
struct STACK
{
	int array[100];
	int size;
};
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
				printf("%d %d: %d\n",i,j,g.a[i][j]);
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
		printf("Dinh %d co bac: %d\n",i,bac[i]);
	}
	printf("So canh cua ma tran la: %d",canh);
}
//==============================================================
void XuatCoHuong(DOTHI g)
{	printf("So dinh cua do thi = %d\n",g.n);
	printf("Danh sach canh cua do thi la:\n");
	int canh=0;
	int br[g.n], bv[g.n];
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]!=0){
				printf("%d %d: %d\n",i,j,g.a[i][j]);
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
		printf("Dinh %d co ban bac ra = %d, bac vao = %d\n",i,br[i],bv[i]);
		
	}
	printf("So canh cua ma tran la: %d",canh);
}
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
        printf("\nSo than phan lien thong la: ");
		for(i=0; i<=SoThanhPhanLT; i++)
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
void DFS(DOTHI g, int i, int LT[]){
	printf("%4d",i+1);
	LT[i]=1;
	for(int j=0; j<g.n; j++)
		if(LT[j]==0 && g.a[i][j]==1)
			DFS(g,j, LT);
}
//==============================================================
int KTEuler(DOTHI g){
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
				return 1;
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
			return 1;
		}
	}
	return 0;
}
//==============================================================
int main()
{
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
		return 0;
	if(KiemTra(g)==0){
		printf("Do thi vo huong:");
		XuatVoHuong(g);
	}
	else{
		printf("Do thi co huong:");
		XuatCoHuong(g);
	}
//=============================
	for(int i=0; i<g.n; i++){
		LT[i]=0;
	}
	printf("\n");
	int dem=1;
//	XetLienThong(g);
/*	DFS(g,0,LT);
	for(int i=0; i<g.n; i++)
		if(LT[i]==0){
			dem++;
			printf("\n");
			DFS(g,i,LT);
		}
	printf("\n%d",dem);*/
	if(KTEuler(g)==1){
		printf("\nDo thi nay khong co chu trinh Euler!");
	}
	return 0;
}
