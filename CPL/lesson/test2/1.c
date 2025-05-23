#include <stdio.h>

int main(){
    int a[3][3];
    int b[3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            scanf("%d ", &a[i][j]);
        }
        scanf("\n");
    }

    for(int i=0; i<3; i++){
        scanf("%d ", &b[i]);
    }

    int max_socre = 0;

    //x, y to a

    for(int x1=0; x1<3; x1++){
        for(int y1 = 0; y1<3; y1++){
            for(int x2=0; x2<3; x2++){
                for(int y2=0; y2<3; y2++){
                    if(x1==x2&&y1==y2){
                        continue;
                    }
                    for(int x3=0; x3<3; x3++){
                        for(int y3=0; y3<3; y3++){
                            if((x3==x1&&y3==y1)||(x3==x2&&y3==y2)){
                                continue;
                            }
                            if((x2-x1)*(y3-y1)==(y2-y1)*(x3-x1)){
                                continue;
                            }

                            int score = b[0]*a[x1][y1]+b[1]*a[x2][y2]+b[2]*a[x3][y3];
                            if(score>max_socre){
                                max_socre=score;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d", max_socre);
    return 0;
    
    
}