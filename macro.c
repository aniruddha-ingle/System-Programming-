#include<stdio.h>
#include<string.h>
int mntc=-1,mdtc=-1;
typedef struct name_tab{
	char name[10];
	int pp;
	int mdtp;
}name_tab;
typedef struct def_tab{
	int pcount;
	int para[5];
	char card[80];
}def_tab;
int lookupALA(char a[][5], char ele[5], int pctr)
{
	for(int i=0;i<=pctr;i++)
	{
		if(!strcmp(ele,a[i]))
		{
			return i;
		}
	}
	return -1;
}
int lookupMNT(name_tab mnt[], char ele[], int mntc)
{
	for(int i=0;i<=mntc;i++)
	{
		if(!strcmp(ele,mnt[i].name))
		{
			return mnt[i].mdtp;
		}
	}
	return -1;
}
void main()
{
	FILE *ip,*op;
	ip=fopen("ip.txt","r+");
	op=fopen("op.txt","w+");
	
	name_tab mnt[10];
	def_tab mdt[80];
	
	int mf=0,pf=0,k=0,pctr=0;
	char ipbuf[80], pop[10], ps[10], delim1[] = ",", ala[10][5], alp[10][5], *ptr;
	
	while(fgets(ipbuf,80,ip)!= NULL)
	{
		//printf("%s",ipbuf);
		sscanf(ipbuf,"%s %s",pop,ps);//printf("%s %s\n",pop,ps);
		if(strcmp(pop,"macro")==0)
		{	
			mf=1;
			fgets(ipbuf,80,ip);//printf("%s",ipbuf);
			sscanf(ipbuf,"%s %s",pop,ps);//printf("%s %s\n",pop,ps);
			mdtc++;
			mntc++;
			strcpy(mnt[mntc].name,pop); //printf("\t%s\n",mnt[mntc].name);
			ptr = strtok(ps,delim1);
			while(ptr != NULL)
			{
				strcpy(ala[pctr],ptr);
				mdt[mdtc].para[pctr] = pctr;//printf("%d",mdt[mdtc].para[pctr]);
				pctr++;
				ptr = strtok(NULL,delim1);
			}
			mnt[mntc].pp = pctr; //printf("\t%d\n",mnt[mntc].pp);
			mnt[mntc].mdtp = mdtc;
			strcpy(mdt[mdtc].card,pop);
			mdt[mdtc].pcount = pctr;
			/*for(int i=0;i<pctr;i++)
				printf("\t%d",mdt[mdtc].para[i]);
			printf("\n");*/
		}
		else if(mf)
		{
			
			if(!strcmp(pop,"mend"))
			{
				mdtc++;
				strcpy(mdt[mdtc].card,pop);
				pctr=0;
				mf=0;
				continue;
			}
			int pctr_1 = 0;
			int i = 0;
			mdtc++;
			ptr = strtok(ps,delim1);
			while(ptr != NULL)
			{
				pctr_1++;
				mdt[mdtc].para[i++] = lookupALA(ala,ptr,pctr);//printf("%d",mdt[mdtc].para[i]);
				ptr = strtok(NULL,delim1);
			}
			strcpy(mdt[mdtc].card,pop);
			mdt[mdtc].pcount = pctr_1;	
		}
		else
		{
			
			if(lookupMNT(mnt,pop,mdtc)!= -1)
			{
				//printf("**%d ",lookupMNT(mnt,pop,mdtc));
				int ip = lookupMNT(mnt,pop,mdtc);
				int mdtc_1 = mnt[ip].mdtp+1; 
				ptr = strtok(ps,delim1);
				int i = 0;
				while(ptr !=NULL)
				{
					strcpy(alp[i++],ptr);
					ptr = strtok(NULL,delim1);
				}
				while(strcmp(mdt[mdtc_1].card,"mend")!=0)
				{
					fprintf(op,"%s ",mdt[mdtc_1].card);
					for(int j=0;j<mdt[mdtc_1].pcount;j++)
					{
						if(j == mdt[mdtc_1].pcount-1)
							fprintf(op,"%s",alp[mdt[mdtc_1].para[j]]);
						else	fprintf(op,"%s,",alp[mdt[mdtc_1].para[j]]);
					}
					mdtc_1++;
					fprintf(op,"\n");
				}
			}
			else
			{
				fprintf(op,"%s",ipbuf);
			}
		}
	}
	
	printf("\nMNT\nName\tNo:pp\tMDTP\n");
	for(int i=0;i<=mntc;i++)
		printf("%s\t%d\t%d\n",mnt[i].name,mnt[i].pp,mnt[i].mdtp);
	printf("\n");
	
	printf("MDT\n");
	for(int i=0;i<=mdtc;i++)
	{
		printf("%d\t%s\t",i,mdt[i].card);
		for(int j=0;j<mdt[i].pcount;j++)
			printf("%d ",mdt[i].para[j]);
		printf("\n");
	}
	printf("\n");
}			
