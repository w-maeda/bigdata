#include <stdio.h>
#include <math.h>

int main(void){
  FILE *gp;

  //sin,cosの画像出力
  gp=popen("gnuplot -persist","w");
  fprintf(gp, "plot sin(x)\n");
  fprintf(gp, "replot cos(x)\n");
  fprintf(gp, "set terminal postscript eps enhanced color\n");
  fprintf(gp, "set output \"image1.eps\"\n");
  fprintf(gp, "replot\n");
  //sin,cosの画像出力完了
  pclose(gp);

  gp=popen("gnuplot -persist","w");
  //ファイルからの画像出力
  fprintf(gp, "plot \'list/folder/1/number.txt\' lt rgb \"green\"\n");
  fprintf(gp, "set terminal postscript eps enhanced color\n");
  fprintf(gp, "set output \"image2.eps\"\n");
  fprintf(gp, "replot\n");

  pclose(gp);

}
