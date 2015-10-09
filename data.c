#include <stdio.h>
#include <string.h>

int main(void){
  char name[256][256];
  int data[256][256];
  FILE *fp;
  int i,k,l,number,loop;
  int a,b;
  int len;
  char data_name[256][256];
  int data_number;
  char filename[256];

  //ファイル名の入力
  for(k=0;k==0;){
    printf("ファイル名を入力して下さい:");
    scanf("%s", filename);
    fp=fopen(filename, "r");
    printf("%s\n", filename);
    if(fp==NULL){
      printf("error\n");
    }
    else{
      k=1;
    }
  }

  //データの入力
  fscanf(fp, "%s", data_name[0]); //最初の行を読み込む
  len=strlen(data_name[0]);
  printf("%s\n", data_name[0]);

  for(l=0,i=1,data_number=0;l<len;data_number++,i++){
  for(k=0;data_name[0][l]!='"'&&data_name[0][l]!='\0';l++,k++){
    if(data_name[0][l]==','&&data_name[0][l+1]!='"'){
      l++;
    }
    name[data_number][k]=data_name[0][l];
  }
  l++;
  k++;
  printf("%s\n", name[data_number]);
  if(data_name[0][l]==','){
    l++;
  }
  }
  printf("%d\n", i/2);

  /*
  for(k=0,loop=0;loop==0;k++){    //データ読み込み
    for(l=0;l<i;l++){
      fscanf(fp, "%d", &data[k][l]);
    }
    if(k!=0){
    loop=1;
    for(l=0;l<=i;l++){
      if(data[k][l]!=data[k-1][l]){
	loop=0;
      }
    }
    }
  }
  fclose(fp);

  fp=fopen("data.txt", "w");
  for(a=0;a<=l;a++){
    for(b=0;b<k;b++){
      fprintf(fp, "%d ", data[a][b]);
    }
    fprintf(fp, "\n\n");
    }*/
  fclose(fp); 
}
