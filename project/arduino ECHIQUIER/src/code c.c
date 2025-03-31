#include <stdio.h>
/*#include <stdio.h>

typedef struct {
    int horiz;
    int vert;
} Deplacement;

Deplacement deplacement(char empl1[2], char empl2[2]) {
    Deplacement result;
    result.horiz = empl2[0] - empl1[0];
    result.vert = empl2[1] - empl1[1];
    return result;
}

int main() {
    char empl1[2] = {'B', '2'};
    char empl2[2] = {'C', '3'};
    
    Deplacement result = deplacement(empl1, empl2);
    
    printf("Deplacement: horiz = %d, vert = %d\n", result.horiz, result.vert);
    
    return 0;
}
*/ 
char Dep[] ="B1";
char Arr[] ="C1";

int main() {
    printf("difference entre B et C : %d",Arr[0]-Dep[0]);
    return 0;
}
    