#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int n,m=0,p,i=0,j=0;
char a[10][10],f[10];

void follow(char c);
void first(char c);

int main(){
    FILE *f;
    int i;
    int z;
    char c,ch;
    //clrscr();
    f=fopen("entrada0.txt","r"); //READ this txt file
    printf("Introduzca el numero de reglas de la gramatica:\n");
    scanf("%d",&n);
    while(!feof(f))
    {
        fscanf(f,"%s",pro[n].lhs);
            if( strcmp(pro[n].lhs,pro[n-1].lhs) == 0 )
            {
                pro[n].lhs[0]='\0';
                fscanf(f,"%s",pro[n-1].rhs[pro[n-1].n]);
                pro[n-1].n++;
                continue;
            }
        fscanf(f,"%s",pro[n].rhs[pro[n].n]);
        pro[n].n++;
        n++;
    }
    printf("Enter the productions:\n");
    for(i=0;i<n;i++)
        scanf("%s%c",a[i],&ch);
    do{
        m=0;
        printf("Enter the elemets whose fisrt & follow is to be found:");
        scanf("%c",&c);
        first(c);
        printf("First(%c)={",c);
        for(i=0;i<m;i++)
            printf("%c",f[i]);
        printf("}\n");
        strcpy(f," ");
        //flushall();
        m=0;
        follow(c);
        printf("Follow(%c)={",c);
        for(i=0;i<m;i++)
            printf("%c",f[i]);
        printf("}\n");
        printf("Continue(0/1)?");
        scanf("%d%c",&z,&ch);
    }while(z==1);
    system("pause");
return(0);
}

void first(char c){
    int k;
    if(!isupper(c))
        f[m++]=c;
    for(k=0;k<n;k++){
        if(a[k][0]==c){
            if(a[k][2]=='#')
                follow(a[k][0]);
            else if(islower(a[k][2]))
                f[m++]=a[k][2];
        else first(a[k][2]);
        }
    }
}

void follow(char c){
    if(a[0][0]==c)
        f[m++]='#';
    for(i=0;i<n;i++){
        for(j=2;j<strlen(a[i]);j++){
            if(a[i][j]==c){
                if(a[i][j+1]!='\0')
                    first(a[i][j+1]);
                if(a[i][j+1]=='\0' && c!=a[i][0])
                    follow(a[i][0]);
            }
        }
    }
}

/* OUTPUT:
Enter the no of prooductions:
5
Enter the productions:
S=AbCd
A=Cf
A=a
C=gE
E=h
Enter the elemets whose fisrt & follow is to be found:S
First(S)={ga}
Follow(S)={$}
Continue(0/1)?1
Enter the elemets whose fisrt & follow is to be found:A
First(A)={ga}
Follow(A)={b}
Continue(0/1)?1
Enter the elemets whose fisrt & follow is to be found:C
First(C)={g}
Follow(C)={df}
Continue(0/1)?1
Enter the elemets whose fisrt & follow is to be found:E
First(E)={h}
Follow(E)={df}
Continue(0/1)?0
*/
