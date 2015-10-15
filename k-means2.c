#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 256

int place(int a,int b,int cluster,int max,int min);
void change_int_char(char *b,int a);
void FILE_name(char *a, char b[MAX], int c, char d[MAX]);

int main(void){
  int data[MAX];
  int x,y,z;
  int i,l,k;
  int cluster_MAX;
  int MAX_number;
  int cluster[MAX][3];
  int max,min;
  char filename[MAX];
  char filename2[MAX];
  int folder_number;
  int number_one,number_two;
  clock_t start,end,f_start,l_end;
  FILE *fp,*fp2;

  printf("数を入力してください\n");
  printf("x=");
  scanf("%d",&x);
  printf("y=");
  scanf("%d",&y);
  printf("クラスタ数:");
  scanf("%d",&z);
  printf("最大:");
  scanf("%d",&max);
  printf("最小:");
  scanf("%d",&min);

  start=clock();//時間計測開始
  f_start=clock();

  //データ作り
  fp=fopen("list/number.txt", "w");
  for(i=0;i<x;i++){
    for(l=0;l<y;l++){
      data[l]=rand()%(max-min)+min;//データをそれぞれ作る
    }
    for(l=0;l<y;l++){
      fprintf(fp,"%d\t",data[l]);
      data[l]='\0';
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  //データ入力終了

  //クラスタデータ作成
  for(i=1;i<=z;i++){
    cluster[i][1]=rand()%(max-min)+min;//x軸
    cluster[i][2]=rand()%(max-min)+min;//y軸
    cluster[i][0]=place(cluster[i][1],cluster[i][2],z,max,min);//場所
  }
  //データ作成完了

  //数の設定
  MAX_number=y*(y-1);
  MAX_number=MAX_number/2;
  //数の設定終了

  //ファイルの作成
  for(i=1;i<=MAX_number;i++){
    system("mkdir ./list/folder/name");
    FILE_name(filename,"list/folder/",i,"");
    if((fp2=fopen(filename,"r"))==NULL){
      rename("./list/folder/name",filename);
    }
    else{
      remove("./list/folder/name");
      fclose(fp2);
    }
  }
  //ファイル作成完了

  cluster_MAX=z*z;//クラスタファイル作成の前準備
  //クラスタファイルの作成
  for(i=1;i<=MAX_number;i++){
    system("mkdir list/cluster");
    for(l=1;l<=cluster_MAX;l++){
      system("mkdir list/cluster/name");
      FILE_name(filename,"list/cluster/",l,"");
      if((fp2=fopen(filename,"r"))==NULL){
	rename("list/cluster/name",filename);
      }
      else{
	remove("list/cluster/name");
	fclose(fp2);
	//ここまで
      }
    }
    FILE_name(filename,"list/folder/",i,"/cluster");
    if((fp2=fopen(filename,"r"))==NULL){
      rename("list/cluster",filename); 
    }
  }
  //クラスタファイル作成完了

  //ファイルにデータ挿入
  fp=fopen("list/number.txt","r");
  for(i=1;i<=x;i++){
    for(l=1;l<=y;l++){
      fscanf(fp,"%d", &data[l]);
    }
    for(folder_number=1,number_one=1,number_two=2;folder_number<=MAX_number;folder_number++){
      FILE_name(filename,"list/folder/",folder_number,"/number.txt");
      if(i==1){
	fp2=fopen(filename,"w");
      }
      else{
	fp2=fopen(filename,"a");
      }
      fprintf(fp2,"%d\t%d\n",data[number_one],data[number_two]);
      if(number_two<y){
	number_two++;
      }
      else if(number_one<y){
	number_one++;
	number_two=number_one+1;
      }
      fclose(fp2);
    }
  }
  fclose(fp);

}

int place(int a,int b,int cluster,int max,int min){
  int i,l,c,k=0,s=0;
  int size_a,size_b;
  int scale;
  int half;

  scale=max-min;//大きさをはかる
  half=scale/cluster;//1つ1つの大きさをはかる

  for(i=min,l=0;i<=max;i=i+half,l++){
    if(i>a&&k==0){
      a=l;
      k=1;
    }
    if(i>b&&s==0){
      b=l;
      s=1;
    }
  }
  c=(a-1)*cluster+b;
}

void change_int_char(char *b,int a){
  int c,d;
    int i,l,k;

  for(i=1,l=0;i<=a;i=i*10,l++){
  }

  for(k=0,d=0,i=i/10;k<l;k++,i=i/10){
    c=a/i-d;
    d=a/i*10;
    b[k]=c+48;
  }
  b[k]='\0';
}

void FILE_name(char *a, char b[MAX], int c, char d[MAX]){
  char file[MAX];

  strcpy(a,b);
  change_int_char(file,c);
  strcat(a,file);
  strcat(a,d);
}
