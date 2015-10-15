#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void plot_color(int a, char *color);
void change_16(int a,char *b);

int main(void){
  FILE *gp;
  int i;
  char color[256];

  //sin,cosの画像出力
  gp=popen("gnuplot -persist","w");
  plot_color(2,color);
  fprintf(gp, "plot sin(x) lt rgb \"#%s\"\n",color);
  plot_color(3,color);
  fprintf(gp, "replot cos(x) lt rgb \"#%s\"\n",color);
  fprintf(gp, "set terminal postscript eps enhanced color\n");
  fprintf(gp, "set output \"image1.eps\"\n");
  fprintf(gp, "replot\n");
  //sin,cosの画像出力完了
  pclose(gp);

  gp=popen("gnuplot -persist","w");
  //ファイルからの画像出力
  plot_color(1,color);
  fprintf(gp, "plot \'list/folder/1/number.txt\' pt 13 ps 1 lt rgb \"#%s\"\n",color);
  plot_color(2,color);
  fprintf(gp, "replot \'list/folder/2/number.txt\' pt 13 ps 0.8 lt rgb \"#%s\"\n",color);
  fprintf(gp, "set terminal postscript eps enhanced color\n");
  fprintf(gp, "set output \"image2.eps\"\n");
  fprintf(gp, "replot\n");

  pclose(gp);

}

void plot_color(int a, char *color){
  int i,c,d;
  int r=0,g=0,b=0;
  char red[2];
  char green[2];
  char blue[2];

  a=a-1;

  c=a%6+1;
  d=a/6+1;

  if(c==1||c==4||c==5){
    r=255/d;
  }
  if(c==2||c==4||c==6){
    g=255/d;
  }
  if(c==3||c==5||c==6){
    b=255/d;
  }

  change_16(r,red);
  change_16(g,green);
  change_16(b,blue);

  strcpy(color,red);
  strcat(color,green);
  strcat(color,blue);
  printf("%s\n",color);
}

void change_16(int a,char *b){
  int l[2];
  int i,c,d;

  if(a>=16){
    for(i=0;a>0;a=a/16,i++){
      l[i]=a%16;
    }
  }
  else if(a<16&&a!=0){
    l[1]=0;
    l[0]=a;
    i=2;
  }
  else if(a==0){
    l[0]=0;
    l[1]=0;
    i=2;
  }

  for(c=i-1,d=0;c>=0;c--,d++){
    if(l[c]<=9){
    b[d]=l[c]+48;
    }
    else{
      b[d]=l[c]+87;
    }
  }
  b[d]='\0';
}
