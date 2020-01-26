#include<stdio.h>
#include<stdlib.h>

struct mesh
{
    struct cell* start;
    int rows;
    int col;
};

struct cell
{
    int value;
    struct cell* r;
    struct cell* b;

};

struct cell* makell(int n,int fill)
{
    struct cell* x =(struct cell*)malloc(sizeof(struct cell));
    struct cell* h = x;
    x->r=NULL;
    x->b=NULL;
    x->value = fill;
    n=n-1;
    while(n>0)
    {
        x->r =(struct cell*)malloc(sizeof(struct cell));
        x = x->r;
        x->b = NULL;
        x->value = fill;
        n--;
    }
    return h;
}

void mergells(struct cell* x,struct cell* y, int n)
{
    while(n--)
    {
        x->b = y;
        x=x->r;
        y=y->r;
    }
}


struct mesh* make_mesh(int n,int m,int fill)
{
    struct mesh* ans= (struct mesh*)malloc(sizeof(struct mesh));
    ans->start = makell(m,fill);
    struct cell* end= makell(m,fill);
    struct cell* x = ans->start;

    n=n-1;
    while(n--)
    {
        mergells(x,end,m);
        x = end;
        end = makell(m,fill);
    }

    return ans;
}

void print_mesh(struct mesh* x,int n,int m)
{
    int i,j;
    struct cell* cellrecent=x->start;
    struct cell* cellstart=cellrecent;

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {

            if(j<m-1)
            {
                if(cellrecent->value<10)
                {
                    printf("%d   ", cellrecent->value);
                }
                else
                {
                    printf("%d  ", cellrecent->value);
                }
                cellrecent = cellrecent->r;
            }
            if(j==m-1)
            {
                printf("%d  \n", cellrecent->value);
                cellstart = cellstart->b;
                cellrecent = cellstart;
            }
        }
    }

}

int fstday(int month,int x[],int d)
{
    int i,day = d,y;

    for(i=0;i<month;i++)
    {
        y=(x[i]+day-8)%7;
        day = (y+1)%7;
    }

    return day;
}

int loc_to_date(int n,int m,int x[],int d)
{
    int ans;

    int month = (n/5);
    month = 3*month + (m/7);
    int dn,dm,fs;

    fs= fstday(month,x,d);

    dn=n/5;
    dn = 5*dn;
    dm =(m/7);
    dm = 7*dm+fs;

    int gap_n,gap_m;
    gap_n=n-dn;
    gap_m=m-dm;

    ans = 7*gap_n+gap_m+1;

    if(ans<0||ans>x[month])ans=0;

    return ans;
}

void mesh_cal(struct mesh* sh,int d,int leap)
{
    int x[12];
    x[0]=31;x[1]=28;x[2]=31;x[3]=30;x[4]=31;x[5]=30;x[6]=31;x[7]=31;x[8]=30;x[9]=31;x[10]=30;x[11]=31;
    if(leap==1)
    {
        x[1]=29;
    }

    int i,j;
    struct cell* today=sh->start;
    struct cell* last = today;
    for(i=0;i<20;i++)
    {
        for(j=0;j<21;j++)
        {
            today->value =  loc_to_date(i,j,x,d);

            if(j<20)
            {
                today = today->r;
            }
            else
            {
                today = last->b;
                last = today;
            }
        }
    }

}


int main()
{
    int i,n,m,fill;
    struct mesh* mymesh=NULL;

    printf("give the size of mesh to make :\n");
    scanf("%d %d %d",&n,&m,&fill);

    mymesh = make_mesh(n,m,fill);

    printf("give the start day and leap or not :\n");
    int leap,d1;
    scanf("%d %d",&d1,&leap);
    mesh_cal(mymesh,d1,leap);

    print_mesh(mymesh,n,m);

    return 0;
}

