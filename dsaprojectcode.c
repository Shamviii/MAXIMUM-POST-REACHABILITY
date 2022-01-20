#include<stdio.h>
#include<conio.h>

struct node
{
    int vertex;
    struct node *next;
};

int total=0,best=0;
int proper[80];
struct node *gnode;
void displayG(struct node *adj[],int no_of_nodes);
void evaluateG(struct node *adj[],int no_of_nodes);
void readG(struct node *adj[],int no_of_nodes);
void fileinput(struct node *adj[],int no_of_nodes);

void main()
{
    struct node *Adj[80];
    int i,no_of_nodes;

    printf("\nEnter the number of total friends in a social network : ");
    scanf("%d",&no_of_nodes);
    for(i=0;i<no_of_nodes;i++)
    {
        Adj[i]=NULL;
    }

    readG(Adj,no_of_nodes);

    printf("\n---------------------------------------\n");

    printf("\n The social network is: ");

    displayG(Adj,no_of_nodes);
    total++;

    evaluateG(Adj,no_of_nodes);
    fileinput(Adj,no_of_nodes);

}

void readG(struct node *Adj[],int no_of_nodes)
{
    struct node *new_node, *last;
    int i,j,n,val;
    total=total+no_of_nodes;
    for(i=0;i<no_of_nodes;i++)
    {
        last=NULL;

        printf("\nEnter the number of friends of %d : ",i);

        scanf("%d",&n);
        total+=n;
        for(j=0;j<n;j++)
        {
            printf("\nEnter the friend of %d of %d :",j,i);
            scanf("%d",&val);
            new_node=(struct node*)malloc(sizeof(struct node));
            new_node->vertex=val;
            new_node->next=NULL;

            if(Adj[i]==NULL)
            {
                Adj[i]=new_node;
            }

            else
            {
                last->next=new_node;
            }
            last=new_node;
        }
    }
}

void displayG(struct node *Adj[], int no_of_nodes)
{
    struct node *ptr;
    int i;


    for(i=0;i<no_of_nodes;i++)
    {
        ptr=Adj[i];
        printf("\n The friends of %d are : ", i);

        while(ptr!=NULL)
        {
            printf("\t%d",ptr->vertex);
            ptr=ptr->next;
        }
    }
}

void evaluateG(struct node *Adj[],int no_of_nodes)
{
    struct node *ptr;
    int i,j;

    int s[total];

    for(i=0;i<no_of_nodes;i++)
    {
        ptr=Adj[i];

        s[j]=i;
        j++;

        while(ptr!=NULL)
        {
            s[j]=ptr->vertex;
            j++;
            ptr=ptr->next;
        }
    }

    printf("\n-----------------------\n");


    int check=0,t=0;
    for(i=0;i<total;i++)
    {
        check=s[i];
        t=0;
        for(j=i+1;j<total;j++)
        {
            if(s[j]==check)
            {
                t++;
                s[j]=-1;
            }

        }
        if(t!=0)
            s[i]=-1;
    }

    printf("\n Minimum number of people information has to passed on:");
    for(i=0;i<total;i++)
    {
        if(s[i]!=-1 && s[i]<1000)
        {
            proper[best]=s[i];
            best++;
            printf("\n%d",s[i]);
        }
    }
    printf("\n-------------------------\n");

}

void fileinput(struct node *Adj[],int no_of_nodes)
{
    FILE *f1;
    struct node *ptr;
    int i;
    char c;
    f1=fopen("SOCIAL NETWORK","w");


    for(i=0;i<no_of_nodes;i++)
    {
        ptr=Adj[i];
        putw(i,f1);
        putc('-',f1);

        while(ptr!=NULL)
        {
            putw(ptr->vertex,f1);
            ptr=ptr->next;
        }

    }
    for(i=0;i<best;i++)
        putw(proper[i],f1);


    fclose(f1);
    f1=fopen("SOCIAL NETWORK","r");
    int k=0,l=0;
    printf("\n Social Network Is :\n");
    for(i=0;i<no_of_nodes;i++)
    {
        ptr=Adj[i];
        k=getw(f1);
        printf("%d",k);
        c=getc(f1);
        printf("%c",c);
        printf("\t");
        l=0;

        while(ptr!=NULL)
        {
            k=getw(f1);
            l++;
            printf("%d\t",k);
            ptr=ptr->next;
        }
        if(l==0)
            printf("This person can't forward a post to anyone");
        printf("\n");

    }

    printf("\n---------------------------\n");
    printf("The minimum number of people post to be forwarded are \n");

    for(i=0;i<best;i++)
    {
        k=getw(f1);
        printf("\n%d",k);
    }

    fclose(f1);
}

