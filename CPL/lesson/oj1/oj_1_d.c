#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    char name[20], unit;
    int pre;
    double frac, factor;

    scanf("%19s %d %lf %lf %c", name, &pre, &frac, &factor, &unit);
    
    double value = pre + frac;
    char new_unit = unit - 32;
    if (strlen(name) >= 2){
        printf("%c%c: %d (%0.5lf) | %.5E %0.5lf %c\n",name[0],name[1], pre, frac, value, value * factor, new_unit);
    }
    else{
        printf("%s: %d (%0.5lf) | %.5E %0.5lf %c\n",name, pre, frac, value, value * factor, new_unit);
    }

    return 0;
}