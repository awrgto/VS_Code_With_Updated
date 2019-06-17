#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define NAME 20
#define DATA 25

int main(){
    size_t iter = 0, great[DATA] = {0}, normal[DATA] = {0}, bad[DATA] = {0}, maxMark = -1, minMark = -1;
    size_t *sPtr[6] = {bad, bad, bad, normal, great, great};
    int i_list[DATA] = {0};
    char c_list[DATA][NAME] = {""}, txt[3][14] = {"\n<60 : ", "\n60<= , <80 :", "\n80<= :"};
    float av = 0, stdev = 0;
    FILE *frPtr = fopen("D:\\VirtualStudio_Code_Programming\\VS_Code_With_Updated\\Sample.txt", "r"), *fwPtr = fopen("D:\\VirtualStudio_Code_Programming\\VS_Code_With_Updated\\學號.txt", "a");

    if ( !frPtr ) {
        puts("can't open file");
        return -32;
    }

    for (; !feof(frPtr); iter++) {
        fscanf(frPtr, "%s%d", c_list[iter], &i_list[iter]); //printf("%s%d", c_list[iter], i_list[iter]);//debug
        sPtr[i_list[iter] / 20][iter]++; //printf("\t%d\n", i_list[iter] / 20);//debug
        if(i_list[iter]>i_list[maxMark] || maxMark == -1) maxMark = iter;
        if(i_list[iter]<i_list[minMark] || minMark == -1) minMark = iter;
        av += i_list[iter];
        fprintf(fwPtr, "%s %d\n", c_list[iter], i_list[iter]);
    }
    for (size_t o_iter = 0, o_mark = 0; o_iter < 3; o_iter++, o_mark = 0)
        for (iter = 0; iter < DATA; iter++){
            if( sPtr[o_iter + 2][iter])printf("%s\n\t%s %d", !o_mark++ ? txt[o_iter] : "", c_list[iter], i_list[iter]); //printf("o_iter :%zu", o_iter);//debug
            stdev += pow((float)i_list[iter] - av / DATA, 2);
        }
    fprintf(fwPtr, "\nav : %.2f", av / DATA);
    fprintf(fwPtr, "\nstdev : %.2f", sqrt(stdev / DATA));
    fprintf(fwPtr, "\nhighest\t%s %d", c_list[maxMark], i_list[maxMark]);
    fprintf(fwPtr, "\nlowest\t%s %d", c_list[minMark], i_list[minMark]);
    fclose(fwPtr);
    fclose(frPtr);
}