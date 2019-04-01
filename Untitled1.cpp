#include<stdio.h>
int main(){
	String a="void Floyd(DOTHI g)
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
}";
printf("%c",a);
	return 0;
}
