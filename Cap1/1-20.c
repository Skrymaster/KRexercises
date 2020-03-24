#include <stdio.h>
#include <stdlib.h>
// la întrebarea variabilă sau parametru simbolic, mai bine variabilă, pentru că dacă folosim variabilă, nu trebuie să recompilăm programul şi putem folosi parametri la executarea programului pentru a da valoarea
int main(int argc,char *argv[]){

    unsigned long tab=15, pos=1;
    int c;

    if (argc>1)
        tab = strtoul(argv[1],NULL,10);
    if (tab==0)
        tab=15;

    while ((c=getchar()) != EOF) {
        switch (c) {
            case '\t': c=' ';
                while (pos++ < tab)
                    putchar(' ');
            case '\n': pos=0;
        }
        putchar(c);
        if (pos==tab) pos=1;
        else pos++;
    }

    return 0;
}