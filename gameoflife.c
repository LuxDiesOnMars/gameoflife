/*Qualsiasi cella viva con meno di due celle vive adiacenti muore, come per effetto d'isolamento;
Qualsiasi cella viva con due o tre celle vive adiacenti sopravvive alla generazione successiva;
Qualsiasi cella viva con più di tre celle vive adiacenti muore, come per effetto di sovrappopolazione;
Qualsiasi cella morta con esattamente tre celle vive adiacenti diventa una cella viva, come per effetto di riproduzione.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define maxrig 30  //num max di righe MAX 40
#define maxcol 50  //num max di colonne MAX 83
#define DELAY 0.10 //delay tra una stampa e l altra
#define TIME 300   //durata tempo processo
#define MOLTEPLICITA 30 //da 0a 100,percentuale di valori inizializzati random a 1 a inizio processo

int main(void)
{

    COORD coord;
    coord.X=0;
    coord.Y=0;
    HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
    time_t now=clock();
    time_t seed;
    srand(time(&seed));
    int array[maxrig][maxcol]={0};
    /*TESTANDO NUOVA GENERAZIONE CASUALE
    for(int rig=0;rig<maxrig;rig++)
        for(int col=0;col<maxcol;col++)
            array[rig][col]=(int) ((float)2*rand()/RAND_MAX);
    */
    int c;
    int row,column;
    int rate=(int)(((float)maxrig*maxcol)/100)*MOLTEPLICITA;

    for(int k=0;k<rate;k++)
    {
        do{
            row=((int) ((float) maxrig*rand()/RAND_MAX));
            column=((int) ((float) maxcol*rand()/RAND_MAX));

            }while(array[row][column]!=0);

        array[row][column]=1;
    }




    for(int rig=0;rig<maxrig;rig++)
        for(int col=0;col<maxcol;col++)
        {
            printf("%d ",array[rig][col]);
            if(col==maxcol-1)printf("\n");
            if(rig==maxrig-1&&col==maxcol-1)printf("\n\n");
        }

    puts("matrice iniziale\npremere invio per iniziare\n");
    getchar();
    SetConsoleCursorPosition(hConsole,coord);
    for(int rig=0;rig<maxrig+10;rig++)
        for(int col=0;col<maxcol+20;col++)
        {
            printf(" ");
            if(col==maxcol+20-1)printf("\n");
        }
    SetConsoleCursorPosition(hConsole,coord);


    while(((clock()-now)/CLOCKS_PER_SEC)<TIME)
    {
        SetConsoleCursorPosition(hConsole,coord);
       /*QUESTA PARTE NON SERVE PERCHè SOVRASCRIVE DIRETTAMENTE IN OUTPUT(IN EFFETTI HA SENSO,PERCHè ALLO STESSO MODO SOVRASCRIVEVA ' ')
        for(int rig=0;rig<maxrig;rig++)
            for(int col=0;col<maxcol;col++)
            {
                printf(" ");
                if(col==maxcol-1)printf("\n");
            }
            SetConsoleCursorPosition(hConsole,coord);
        */
        int (*p)[maxcol]= (int *)malloc(sizeof(array));
        memcpy(p,array,sizeof(array));

        for(int rig=0;rig<maxrig;rig++)
            for(int col=0;col<maxcol;col++)
            {
                int contON=0;
                int contOFF=0;
                //su
                if(rig-1<0)
                    if(array[maxrig-1][col]==0)contOFF++;
                        else contON++;
                else if(array[rig-1][col]==0)contOFF++;
                        else contON++;
                //su sx
                if(rig-1<0&&col-1<0)
                    if(array[maxrig-1][maxcol-1]==0)contOFF++;
                        else contON++;
                else if(rig-1<0&&col-1>=0)
                    if(array[maxrig-1][col-1]==0)contOFF++;
                        else contON++;
                else if(rig-1>=0&&col-1<0)
                    if(array[rig-1][maxcol-1]==0)contOFF++;
                        else contON++;
                else if(rig-1>=0&&col-1>=0)
                    if(array[rig-1][col-1]==0)contOFF++;
                        else contON++;
                //sx
                if(col-1<0)
                    if(array[rig][maxcol-1]==0)contOFF++;
                        else contON++;
                else if(array[rig][col-1]==0)contOFF++;
                        else contON++;
                //giù sx

                if(rig+1>=maxrig&&col-1<0)
                    if(array[0][maxcol-1]==0)contOFF++;
                        else contON++;
                else if(rig+1>=maxrig&&col-1>=0)
                    if(array[0][col-1]==0)contOFF++;
                        else contON++;
                else if(rig+1<maxrig&&col-1<0)
                    if(array[rig+1][maxcol-1]==0)contOFF++;
                        else contON++;
                else if(rig+1<maxrig&&col-1>=0)
                    if(array[rig+1][col-1]==0)contOFF++;
                        else contON++;

                //giù
                if(rig+1>=maxrig)
                    if(array[0][col]==0)contOFF++;
                        else contON++;
                else if(array[rig+1][col]==0)contOFF++;
                        else contON++;

                //giù dx
                if(rig+1>=maxrig&&col+1>=maxcol)
                    if(array[0][0]==0)contOFF++;
                        else contON++;
                else if(rig+1>=maxrig&&col+1<maxcol)
                    if(array[0][col+1]==0)contOFF++;
                        else contON++;
                else if(rig+1<maxrig&&col+1>=maxcol)
                    if(array[rig+1][0]==0)contOFF++;
                        else contON++;
                else if(rig+1<maxrig&&col+1<maxcol)
                    if(array[rig+1][col+1]==0)contOFF++;
                        else contON++;
                //dx
                if(col+1>=maxcol)
                    if(array[rig][0]==0)contOFF++;
                        else contON++;
                else if(array[rig][col+1]==0)contOFF++;
                        else contON++;
                //su dx
                if(rig-1<0&&col+1>=maxcol)
                    if(array[maxrig-1][0]==0)contOFF++;
                        else contON++;
                else if(rig-1<0&&col+1<maxcol)
                    if(array[maxrig-1][col+1]==0)contOFF++;
                        else contON++;
                else if(rig-1>=0&&col+1>=maxcol)
                    if(array[rig-1][0]==0)contOFF++;
                        else contON++;
                else if(rig-1>=0&&col+1<maxcol)
                    if(array[rig-1][col+1]==0)contOFF++;
                        else contON++;


                //if(rig==n&&col==n)printf("\nvalore:%d on:%d off:%d\n",array[n][n],contON,contOFF); x verifica

                if(array[rig][col]==1)
                {
                    if(contON<2)p[rig][col]=0;
                    else if(contON==2||contON==3)p[rig][col]=1;
                    else if(contON>3)p[rig][col]=0;
                }
                else if(array[rig][col]==0)
                {
                    if(contON==3)p[rig][col]=1;
                    else p[rig][col]=0;
                }


            }
            memcpy(array,p,sizeof(array));
            free(p);

            for(int rig=0;rig<maxrig;rig++)
                for(int col=0;col<maxcol;col++)
                {
                    printf("%c ",array[rig][col]? 'O' : ' ');//modificato da 0 1 a char
                    if(col==maxcol-1)printf("\n");
                    if(rig==maxrig-1&&col==maxcol-1)printf("\n\n");
                }

            time_t now2=clock();
            while(((float)(clock()-now2)/CLOCKS_PER_SEC)<DELAY);

    }
        //printf("%d",array[n][n]); x verifica

}
