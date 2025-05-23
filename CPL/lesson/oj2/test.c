#include <stdio.h>

int main(){
    int n=0;
    int N = 0;
    int N1,N2,N3,N4,N5,N6=0;
    int gap=0;
    int max,min=0;
    int sum=0;
    scanf("%d",&N);
    
    for(int i=0; N!=495 ;i++){
        int a= N/100;
        int b= N/10-a*10;
        int c=N%10;
        N1=a+b*10+c*100;
        N2=a+c*10+b*100;
        N3=b+a*10+c*100;
        N4=b+c*10+a*100;
        N5=c+b*10+a*100;
        N6=c+a*10+b*100;

        N2=(N1>N2)?N1:N2;
        N3=(N2>N3)?N2:N3;
        N4=(N3>N4)?N3:N4;
        N5=(N4>N5)?N4:N5;
        max=(N5>N6)?N5:N6;

        N2=(N1>N2)?N2:N1;
        N3=(N2>N3)?N3:N2;
        N4=(N3>N4)?N4:N3;
        N5=(N4>N5)?N5:N4;
        min=(N5>N6)?N6:N5;

        n=max-min;
        gap=N-n;
        if(gap>0){
            sum=sum+gap;
            N=n;
            }else{
                N=n+gap;
            }
        
        
    }
    printf("%d",sum);
    return 0;
}