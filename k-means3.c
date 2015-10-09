#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 256

void change_int_char(char *b,int a);
void FILE_name(char *a, char b[MAX], int c, char d[MAX]);

typedef struct {
  int data[MAX];
  int add[MAX];
  int a[MAX];
  int number;
} new_data;

typedef struct {
  int data;
  int number;
} old_data;

int main(void){
  new_data new[MAX];
  old_data old[MAX];
  clock_t start,end,f_start,l_end;
  int data[MAX];
  int k_means[MAX][MAX];
  int cluster_add[MAX][MAX];
  int absolute,add,loop,same,distance;
  int i,l,z,c;
  int x,y,k;
  int number_one,number_two;
  int cluster,MAX_number,folder_number;
  char filename[MAX],filename2[MAX],filename3[MAX];
  FILE *fp;
  FILE *fp2;
  FILE *fp3;
  FILE *fp4;
  FILE *fp5;
  FILE *fp6;
  srand((unsigned)time(NULL));

  printf("数を入力してください\n");
  printf("行:");
  scanf("%d", &x);
  printf("列:");
  scanf("%d", &y);
  printf("クラスタ数を入力してください:");
  scanf("%d", &k);

  start=clock();//時間計測開始
  f_start=clock();

  //データ作り
  fp=fopen("list/number.txt", "w");
  for(i=0;i<x;i++){
    for(l=0;l<y;l++){
      data[l]=rand()%10000;//データをそれぞれ作る
    }
    for(l=0;l<y;l++){
      fprintf(fp,"%d\t",data[l]);
      data[l]='\0';
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  //データ入力終了

  //クラスタの初期設定
  fp=fopen("list/cluster.txt","w");
  for(i=0;i<k;i++){   //kの初期値入力
    for(l=1;l<=y;l++){
      k_means[i][l]=rand()%10000;
      fprintf(fp, "%d\t", k_means[i][l]);
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"\n");
  fclose(fp);
  //初期設定終了

  //数の設定
  MAX_number=y*(y-1);
  MAX_number=MAX_number/2;
  //数の設定終了

  //ファイルの作成
  for(i=1;i<=MAX_number;i++){
    system("mkdir ./list/folder/name");
    strcpy(filename,"./list/folder/");
    change_int_char(filename2,i);
    strcat(filename,filename2);
    if((fp2=fopen(filename,"r"))==NULL){
      rename("./list/folder/name",filename);
    }
    else{
      remove("./list/folder/name");
    }
  }
  //ファイル作成完了
  
  //ファイルにデータ挿入
  fp3=fopen("list/number.txt","r");
  for(i=1;i<=x;i++){
    for(l=1;l<=y;l++){
      fscanf(fp3,"%d", &data[l]);
    }
    for(folder_number=1,number_one=1,number_two=2;folder_number<=MAX_number;folder_number++){
      strcpy(filename,"./list/folder/");
      change_int_char(filename2,folder_number);
      strcat(filename,filename2);
      strcat(filename,"/number.txt");
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
  fclose(fp3);
  //データ挿入完了

  //クラスタ情報挿入
  fp3=fopen("list/cluster.txt","r");
  for(i=1;i<=k;i++){
    for(l=1;l<=y;l++){
      fscanf(fp3,"%d",&data[l]);//クラスターデータ読み込み
    }
    for(folder_number=1,number_one=1,number_two=2;folder_number<=MAX_number;folder_number++){
      FILE_name(filename,"list/folder/",folder_number,"/result_cluster.txt");
      if(i==1){
	fp2=fopen(filename,"w");
      }
      else{
	fp2=fopen(filename,"a");
      }
      FILE_name(filename,"list/folder/",folder_number,"/last_cluster_data.txt");
      if(i==1){
	fp=fopen(filename,"w");
      }
      else{
	fp=fopen(filename,"a");
      }
      fprintf(fp2,"%d\t%d\n",data[number_one],data[number_two]);
      fprintf(fp,"%d\t%d\n",data[number_one],data[number_two]);
      if(number_two<y){
	number_two++;
      }
      else if(number_one<y){
	number_one++;
	number_two=number_one+1;
      }
      if(i==k){
	fprintf(fp2,"\n");
      }
      fclose(fp2);
      fclose(fp);
    }
  }
  fclose(fp3);
  //クラスタ情報挿入完了

  end=clock();//時間計測終了

  fp6=fopen("list/time.txt","w");
  fprintf(fp6,"準備にかかった時間は%.2f秒です\n",(double)(end-start)/CLOCKS_PER_SEC);
  fclose(fp6);

  for(folder_number=1;folder_number<=MAX_number;folder_number++){//クラスタ毎
    start=clock();
    FILE_name(filename,"list/folder/",folder_number,"/result_cluster.txt");
    fp=fopen(filename, "a");
    FILE_name(filename,"list/folder/",folder_number,"/result_number.txt");
    fp2=fopen(filename, "w");
    for(loop=1;;loop++){
      //k-means開始
      FILE_name(filename,"list/folder/",folder_number,"/number.txt");
      fp3=fopen(filename, "r");
      FILE_name(filename,"list/folder/",folder_number,"/last_cluster.txt");
      fp4=fopen(filename, "w");
      FILE_name(filename,"list/folder/",folder_number,"/last_cluster_data.txt");
      fp5=fopen(filename, "r");
      for(i=1;i<=x;i++){//調べたい値
	fscanf(fp3,"%d",&data[1]);
	fscanf(fp3,"%d",&data[2]);
	for(z=1;z<=k;z++){
	  fscanf(fp5,"%d",&k_means[z][1]);
	  fscanf(fp5,"%d",&k_means[z][2]);
	}
	for(z=1;z<=k;z++){//クラスタの値
	  for(l=1,add=0;l<=2;l++){//何列目か
	    absolute=k_means[z][l]-data[l];//それぞれの距離
	    absolute=absolute*absolute;//2乗
	    add=add+absolute;//合計
	  }
	  if(z==1){//初期値を入れる
	    distance=add;//合計値
	    cluster=1;//クラスタ名
	  }
	  if(distance>add){//もしも距離の差が小さかったら
	    distance=add;
	    cluster=z;
	  }
	}
	fprintf(fp2,"%d ",cluster);
	fprintf(fp4,"%d ",cluster);
      }
      fprintf(fp2,"\n\n");
      fclose(fp3);
      fclose(fp4);
      fclose(fp5);

      //初期化
      for(z=1;z<=k;z++){
	new[z].number=0;
	cluster_add[z][1]=0;
	cluster_add[z][2]=0;
      }
      //初期化終了
  
      //それぞれの重心を求める
      FILE_name(filename,"list/folder/",folder_number,"/number.txt");
      fp3=fopen(filename, "r");
      FILE_name(filename,"list/folder/",folder_number,"/last_cluster.txt");
      fp4=fopen(filename, "r");
      for(i=1;i<=x;i++){
	fscanf(fp4,"%d",&cluster);
	FILE_name(filename,"list/new_cluster/",cluster,".txt");
	if(new[cluster].number==0){
	  fp5=fopen(filename,"w");
	}
	else{
	  fp5=fopen(filename,"a");
	}
	fprintf(fp5,"%d ",i);
	fclose(fp5);
	fscanf(fp3,"%d\t%d",&data[1],&data[2]);
	cluster_add[cluster][1]=data[1]-k_means[cluster][1]+cluster_add[cluster][1];//x軸の合計
	cluster_add[cluster][2]=data[2]-k_means[cluster][2]+cluster_add[cluster][2];//y軸の合計
	new[cluster].number++;//数を増やす
      }
      fclose(fp3);
      fclose(fp4);

      FILE_name(filename,"list/folder/",folder_number,"/last_cluster_data.txt");
      fp3=fopen(filename,"w");
      for(z=1;z<=k;z++){//重心確定
	if(new[z].number!=0){
	  fprintf(fp3,"%d\t%d\n",cluster_add[z][1]/new[z].number+k_means[z][1],cluster_add[z][2]/new[z].number+k_means[z][2]);
	  fprintf(fp,"%d\t%d\n",cluster_add[z][1]/new[z].number+k_means[z][1],cluster_add[z][2]/new[z].number+k_means[z][2]);
	}
	else{
	  fprintf(fp3,"0\t0\n");
	  fprintf(fp,"0\t0\n");
	}
      }
      fprintf(fp,"\n\n");
      fclose(fp3);

      FILE_name(filename,"list/folder/",folder_number,"/result.txt");
      if(loop==1){
	fp3=fopen(filename, "w");
      }
      else if(loop!=1){
	fp3=fopen(filename, "a");
      }
      for(z=1;z<=k;z++){
	fprintf(fp3,"クラスタ%dにある数字の数:%d\n",z,new[z].number);
      }
      fprintf(fp3,"\n\n");
      fclose(fp3);
  
      //終了条件
      for(z=1,same=1;z<=k;z++){
	if(new[z].number==0){//もし新しい方に何も入ってなければ
	  //古い方のファイルの準備
	  FILE_name(filename,"list/old_cluster/",z,".txt");
	  fp3=fopen(filename,"w");
	  //ファイルの準備終了
	  fclose(fp3);
	}
	if(new[z].number!=0){//新しい方に何か入っていれば
	  //新しい方のファイルの準備
	  FILE_name(filename,"list/new_cluster/",z,".txt");
	  fp3=fopen(filename,"r");
	  //ファイルの準備終了
	  if(loop==1||old[z].number==0||same==0){
	    //1周目もしくは古いデータに何も入ってないもしくはデータが違うと判明している
	    same=0;
	    FILE_name(filename,"list/old_cluster/",z,".txt");
	    fp4=fopen(filename,"w");
	    for(i=1;i<=new[z].number;i++){
	      fscanf(fp3,"%d",&data[z]);
	      fprintf(fp4,"%d\n",data[z]);
	    }
	    fclose(fp3);
	    fclose(fp4);
	  }
	  else{//それ以外なら
	    //古いデータの準備
	    FILE_name(filename,"list/old_cluster/",z,".txt");
	    fp4=fopen(filename,"r");
	    //データの準備終了
	    if(new[z].number!=old[z].number){//数が違ったら
	      same=0;//違う判定
	    }
	    else if(new[z].number==old[z].number){//数が一緒なら
	      for(i=0;i<new[z].number;i++){
		fscanf(fp3,"%d",&new[z].data[0]);
		fscanf(fp4,"%d",&old[z].data);
		if(old[z].data!=new[z].data[0]){
		  same=0;
		  break;
		}
	      }
	      fclose(fp3);
	      fclose(fp4);
	    }
	    //新しい方のファイルの準備
	    FILE_name(filename,"list/new_cluster/",z,".txt");
	    fp3=fopen(filename,"r");
	    //ファイルの準備終了
	    //古い方のファイルの準備
	    FILE_name(filename,"list/old_cluster/",z,".txt");
	    fp4=fopen(filename,"w");
	    //ファイルの準備終了
	    for(i=0;i<new[z].number;i++){
	      fscanf(fp3,"%d",&data[z]);
	      fprintf(fp4,"%d\n",data[z]);
	    }
	    fclose(fp3);
	    fclose(fp4);
	  }
	}
	old[z].number=new[z].number;
      }

      if(same==1){
	break;
      }
    }

    end=clock();

    if(folder_number==1){
      fp3=fopen("list/loop.txt","w");
    }
    else{
      fp3=fopen("list/loop.txt","a");
    }
    fprintf(fp3,"%dのループ回数は%dです\n",folder_number, loop);
    fclose(fp3);
    fp4=fopen("list/time.txt","a");
    fprintf(fp4,"%dの計測時間は%.2f秒です\n",folder_number,(double)(end-start)/CLOCKS_PER_SEC);
    fclose(fp4);

    fclose(fp);
    fclose(fp2);
  }

  l_end=clock();
  fopen("list/time.txt","a");
  fprintf(fp6,"かかった時間の合計は%.2fです\n",(double)(l_end-f_start)/CLOCKS_PER_SEC);
  fclose(fp6);
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
