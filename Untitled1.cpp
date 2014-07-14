#include<stdio.h>
int visited[10]={0},n,cost[10][10],pop[10],k=0;
void dfs(int v)
{
  int w;
  visited[v]=1;
  for(w=1;w<=n;w++)
        if(cost[v][w]&& !visited[w])
                    dfs(w);

 k++;
 pop[k]=v;
}
main()
{
 int s,j,i;
 printf("Enter n : ");
 scanf("%d",&n);
 printf("Enter adjacency matrix\n");
 for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
            scanf("%d",cost[i][j]);
 printf("Enter source : ");
 scanf("%d",&s);
 dfs(s);
  if(k==n)
  for(i=n;i>=1;i--)
        printf("%d",pop[i]);
   else
        printf("NO topological order.\n");


}
