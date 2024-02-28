#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 15
#define maxx 1000
int movecontrol(int matris[][MAX],char move,int x,int y,int matrissize);
double ScoringSystem(double time,int GameMode,double MatrixSize,int GameAreaType,int undo,double TotalScore);

int main()
{
    int NameSize =0;
    printf("\t\tWELCOME\n");
    printf("  please press any key to continue\n");
    getchar();
    system("CLS");
    MainMenu(NameSize);
    return 0;
}
void MainMenu(int NameSize)
{
    srand(time(NULL));
    int x,y,choice,i,j,MatrisSize,matris[MAX][MAX]={{0}},gameareatype;
    double scores[MAX]={{0}};
    char names[MAX][MAX],registercontrol;
    char fileName[20],randommatrixcontrol;
    do
    {
        printf("\n 1-Generate Random Matrix:\n");
        printf(" 2-Create Matrix from File:\n");
        printf(" 3-Show Users Scores\n");
        printf(" 4-Player Registration\n");
        printf(" 5-Exit\n\n");
        printf(" Choice : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            gameareatype =2;
            do
            {
            i=0;
            printf("Please Enter Your Matrix Size : \n");
            scanf("%d",&MatrisSize);
            zeromatrix(matris,MatrisSize);
            while(i!=(MatrisSize*2))
            {
                x = rand() % MatrisSize;
                y = rand() % MatrisSize;
                if(matris[x][y]==0)
                {
                    matris[x][y] = (i/2)+1;
                    i++;
                }
            }
            drawBoard(matris,MatrisSize);
            printf("\nDo you accept this game area :\n");
            printf("Please press y to accept or press other key to refuse : \n");
            scanf(" %c",&randommatrixcontrol);
            }while(randommatrixcontrol != 'y' && randommatrixcontrol != 'Y');
            drawBoard(matris,MatrisSize);
            GameMenu(names,scores,NameSize,matris,MatrisSize,gameareatype);
        }
        else if(choice==2)
        {
            gameareatype=1;
            printf("Please Enter N(size) Value : ");
            scanf("%d",&MatrisSize);
            zeromatrix(matris,MatrisSize);
            printf("Please Enter Your File Name : ");
            scanf("%s",&fileName);
            readFromFile(matris, fileName);
            drawBoard(matris,MatrisSize);
            GameMenu(names,scores,NameSize,matris,MatrisSize,gameareatype);
        }
        else if(choice==3)
        {
            for(i=0;i<NameSize;i++)
            {
                printf("%d - %s : %lf \n",i+1,names[i],scores[i]) ;
            }
        }
        else if(choice==4)
        {
            do
            {
                 NameSize=UserControl(names,NameSize);
                 printf("Enter any key for add one more register\n");
                 printf("Enter x for return Main menu \n");
                 printf("Choice : ");
                 scanf(" %c",&registercontrol);
            }while(registercontrol != 'x' && registercontrol != 'X');
        }
        else
        {
                printf(" Please enter current value to process\n");
        }
    }while(choice != 5);
    printf("\n Thanks for play this game \n Have a nice day...");
}
void GameMenu(char names[][MAX],double scores[MAX],int NameSize,int matris[][MAX],int MatrisSize,int gameareatype)
{
    time_t start,end;
    int choice,Playerindex,x,y,boardcontrol1=0,undocounter=0, undocoordinate[maxx][2],xykontrol,gamemove=0,gameundo=0;
    char move,undo[maxx];
    double elapsedtime;
    do
    {
        printf("\n1-Manuel Mode \n");
        printf("2-Automatic Mode \n");
        printf("3-Main Menu \n");
        printf("Choice : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            Playerindex = UserIndex(names,NameSize,scores);
            time (&start);
            while(boardcontrol1==0)
            {
                drawBoard(matris,MatrisSize);
                printf("\nnumber of moves : %d",gamemove);
                printf("\nnumber of undos : %d",gameundo);
                xykontrol =1;
                printf("\nPlease choose direction : (left : l ,rigth : r , up : u , down : d)or press f to take back your last move\n");
                scanf(" %c",&move);
                if(move=='f' || move == 'F')
                {
                    xykontrol=0;
                }
                while(xykontrol==1)
                {
                    printf("\nPlease enter start coordinate : \n");
                    printf("column :");
                    scanf("%d",&x);
                    printf("row :");
                    scanf("%d",&y);
                    if(matris[x][y]!=0)
                    {
                        xykontrol = 0;
                    }
                }
                if(move=='f')
                {
                    undoaction(matris,undo,&undocounter,undocoordinate,&gameundo);
                }
                else
                {
                    if(movecontrol(matris,move,x,y,MatrisSize)==1)
                    {
                         moveaction(move,matris,undo,undocoordinate,&undocounter,x,y,&gamemove);
                    }
                    boardcontrol1 = boardcontrol(matris,MatrisSize);
                }
            }
            if(boardcontrol1==1)
            {
                time (&end);
                elapsedtime = end-start;
                printf("Congutulations you win");
                drawBoard(matris,MatrisSize);
                scores[Playerindex]=ScoringSystem(elapsedtime,1,MatrisSize,gameareatype,gameundo,scores[Playerindex]);

            }
        }
        else if(choice==2)
        {
            printf("Our game will add aoutamaticly mode at next update :)");
        }
        else if(choice==3)
        {
            printf("Main Menu Loading...");
            return 0;
        }
        else
        {
            printf(" Please enter current value to process\n");
        }
    }while(1);
}
void readFromFile(int matris[][MAX], char *fileName){
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);
		matris[i][j]=temp;
    }
  	fclose(data);
}
void drawBoard(int matris[][MAX], int N){
    int i,j,k;
    for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
        for(j=0;j<N;j++)
            if (matris[i][j]!=0)
                printf("  %d   |",matris[i][j]);
            else
                 printf("      |",matris[i][j]);
    }
}
double ScoringSystem(double time,int GameMode,double MatrixSize,int GameAreaType,int undo,double TotalScore)
{
   TotalScore += ((GameMode*(MatrixSize/2)*GameAreaType)/((time/100)))-(undo*2);

   return TotalScore;
}
int UserControl(char names[][MAX],int NameSize)
{
    int i=0;
    char name[MAX];
    printf("Please Enter Your UserName (max %d character) : ",MAX);
    scanf(" %s",name);
    while(name[i] != '\0')
    {
        names[NameSize][i]=name[i];
        i++;
    }
    return NameSize+1; //indexi döndürüyor
}
int UserIndex(char names[][MAX], int NameSize, double scores[MAX]) // oyuna baslamadan once oyuncu indexi alıp dondurur ve skor tablosunda bu sayi sayesinde islem yapariz
{
    int i, index;
    for (i = 0; i < NameSize; i++)
    {
        printf("%d - %s : %lf \n", i + 1, names[i], scores[i]);
    }
    printf("Please Enter the index of your name: ");
    scanf("%d", &index);
    return index - 1;
}
void zeromatrix(int matris[][MAX],int n) // oyun alaninin sifirlar
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            matris[i][j]=0;
        }
    }
}
int movecontrol(int matris[][MAX],char move,int x,int y,int matrissize) // hameleye izin varsa 1 yoksa 0
{
    if(move == 'r' || move == 'R' )
    {
        if (matris[x][y+1] == 0 && y != matrissize-1)
        {
            return 1;
        }
        else
        {
            printf("Please enter available move ");
            return 0;
        }
    }
    else if(move == 'l' || move == 'L' )
    {
        if (matris[x][y-1] == 0 && y != 0)
        {
            return 1;
        }
        else
        {
            printf("Please enter available move ");
            return 0;
        }
    }
    else if(move == 'u' || move == 'U' )
    {
         if (matris[x-1][y] == 0 && x != 0)
        {
            return 1;
        }
        else
        {
            printf("Please enter available move ");
            return 0;
        }
    }
    else if(move == 'd' || move == 'D' )
    {
         if (matris[x+1][y] == 0 && x != matrissize-1)
        {
            return 1;
        }
        else
        {
            printf("Please enter available move ");
            return 0;
        }
    }
}
int boardcontrol(int matris[][MAX],int n) //1 dönerse oyun biter  0 döner ise devam
{
    int i,j,control=1,counter=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if (matris[i][j]==0)
            {
                control = 0;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(matris[i][j]==matris[i+1][j] || matris[i][j]==matris[i-1][j] || matris[i][j+1]==matris[i][j] || matris[i][j-1]==matris[i][j])
                {
                    counter+=1;
                }
        }
    }
    if(control == 1 && counter==n*n)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void moveaction(char chocenmove,int matris[][MAX],char undo[maxx],int undocoordinate[][2],int *undocounter,int x,int y,int *gamemove) // hareket
{
    if(chocenmove == 'r' || chocenmove == 'R' )
    {
        matris[x][y+1] = matris[x][y];
        undo[*undocounter]='r';
        undocoordinate[*undocounter][0] = x;
        undocoordinate[*undocounter][1] = y;
        (*undocounter)++;
        (*gamemove)++;
    }
    else if(chocenmove == 'l' || chocenmove == 'L' )
    {
        matris[x][y-1] = matris[x][y];
        undo[*undocounter]='l';
        undocoordinate[*undocounter][0] = x;
        undocoordinate[*undocounter][1] = y;
        (*undocounter)++;
        (*gamemove)++;
    }
    else if(chocenmove == 'u' || chocenmove == 'U' )
    {
        matris[x-1][y] = matris[x][y];
        undo[*undocounter]='u';
        undocoordinate[*undocounter][0] = x;
        undocoordinate[*undocounter][1] = y;
        (*undocounter)++;
        (*gamemove)++;
    }
    else if(chocenmove == 'd' || chocenmove == 'D' )
    {
        matris[x+1][y] = matris[x][y];
        undo[*undocounter]='d';
        undocoordinate[*undocounter][0] = x;
        undocoordinate[*undocounter][1] = y;
        (*undocounter)++;
        (*gamemove)++;
    }
}
void undoaction(int matris[][MAX],char undo[maxx],int *undocounter,int undocoordinate[][2],int *undomove) // undo
{
    int x,y;
    if((*undocounter)==0)
    {
        printf("Please do one move before undo action");
    }
    else if(undo[(*undocounter)-1]=='r')
    {
        x=undocoordinate[*undocounter-1][0];
        y=undocoordinate[*undocounter-1][1];
        matris[x][y+1]=0;
        (*undocounter)--;
        (*undomove)++;
    }
    else if(undo[(*undocounter)-1]=='l')
    {
        x=undocoordinate[*undocounter-1][0];
        y=undocoordinate[*undocounter-1][1];
        matris[x][y-1]=0;
        (*undocounter)--;
        (*undomove)++;
    }
    else if(undo[(*undocounter)-1]=='u')
    {
        x=undocoordinate[*undocounter-1][0];
        y=undocoordinate[*undocounter-1][1];
        matris[x-1][y]=0;
        (*undocounter)--;
        (*undomove)++;
    }
    else if(undo[(*undocounter)-1]=='d')
    {
        x=undocoordinate[*undocounter-1][0];
        y=undocoordinate[*undocounter-1][1];
        matris[x+1][y]=0;
        (*undocounter)--;
        (*undomove)++;
    }

}
