#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<limits.h>
#include<math.h>
//char *inputfile=new char[17];
//char *outputfile;
FILE *file1;
using namespace std;
class tree{
    public:
        long n;
        long e;
        set < pair<long, long> > edges;
        void tree_add_edge(long u,long v){
            if(v<u){
                long t=u;
                u=v;
                v=t;
            }
            pair<long,long> p = make_pair(u,v);
            edges.insert(p);
            e++;
        }
      
}steinerTree;
class graph{
    public:
        long n;
        long e;
        long t;
        vector <long> terminals;
        vector < pair < pair<long, long>, long> > edges;
        vector < vector<long> > adj_matrix;
        vector < vector<long> > dist;
        vector < vector<long> > next;
        vector < vector< vector<long> > >path;
        void graph_add_edge(long u,long v, long w){
            pair<long,long> p = make_pair(u,v);
            pair < pair<long, long>, long> ed= make_pair(p,w);
            edges.push_back(ed);
        }
        void create_adjmatrix(){
            for(long i=0;i<n;i++){
                vector<long> t(n,LONG_MAX);
                adj_matrix.push_back(t);
                adj_matrix[i][i]=0;
            }
            for(long i=0;i<e;i++){
 		           
                adj_matrix[edges[i].first.first][edges[i].first.second]=edges[i].second;
                adj_matrix[edges[i].first.second][edges[i].first.first]=edges[i].second;
            }
        }

        void All_Pairs_Shortest_Path ()
        {
            long i, j, k;
            for(long i=0;i<n;i++){
                vector<long> t(n); //creating a vector of size n 
                vector<long> ne(n,-1);
                vector<vector<long> > p(n);
                dist.push_back(t);
                next.push_back(ne);
                path.push_back(p);
            }
                 cout<<"\n---------------next matrix 0------------\n";
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < n;j++ )
                  cout<<next[i][j]<<" ";
            cout<<"\n";
            }
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++){
                    dist[i][j] = adj_matrix[i][j];
                    if(dist[i][j]<LONG_MAX){
                            next[i][j]=j;
                    }
                }
     cout<<"\n---------------next matrix 1------------\n";
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < n;j++ )
                  cout<<next[i][j]<<" ";
            cout<<"\n";
            }
       
            for (k = 0; k < n; k++)
            {
                for (i = 0; i < n; i++)
                {
                    for (j = 0; j < n; j++)
                    {
                        if (dist[i][k]!=LONG_MAX && dist[k][j]!=LONG_MAX)
                            if(dist[i][k] + dist[k][j] < dist[i][j]){
                                dist[i][j] = dist[i][k] + dist[k][j];
                                next[i][j] = next[i][k];
                            }
                    }
                }
            }
             //printing bellman distance matrix
           cout<<"\n---------------Bellman ford matrix------------\n";
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < n;j++ )
                  cout<<dist[i][j]<<" ";
            cout<<"\n";
            }
            cout<<"\n---------------next matrix------------\n";
            for(i = 0; i < n; i++)
            {
              for(j = 0; j < n;j++ )
                  cout<<next[i][j]<<" ";
            cout<<"\n";
            }
            
            //Shortest Path
            for(i=0;i<n;i++)
                for(j=0;j<n;j++){
                    Find_path(i,j);
                }
        }
        void Find_path(long u,long v){
            if(next[u][v]==-1)
                return;
            long i=u,j=v;
            path[i][j].push_back(u);
            cout<<"\npath("<<i<<","<<j<<")->";
            while(u!=v){
                u=next[u][v];
                cout<<u<<"->";
                path[i][j].push_back(u);
            }
        }

        void printPath(long u,long v){
            for(long k=0;k<path[u][v].size()-1;k++)
                steinerTree.tree_add_edge(path[u][v][k],path[u][v][k+1]);
                //fprintf(stdout, "%ld %ld\n",path[u][v][k]+1,path[u][v][k+1]+1);
        }
};
graph* graph_init()
{
   
    long n = 0;
    long e = 0;
    long t = 0;
    long u, v, w;
   
	FILE *fp;
	fp = fopen("t1.txt","r");
   
    graph *g = new graph();
    cout<<"Enter the number of Vertex\n";
    //cin>>n;
    fscanf(fp,"%ld",&n);
    g->n = n;
    cout<<"Enter the number of Edges\n";
  //  cin>>e;
    fscanf(fp,"%ld",&e);
    g->e = e;
    cout<<"Enter the number of Terminals\n";
    //cin>>t;
    //t++;
    fscanf(fp,"%ld",&t);
    g->t=t;
    cout<<"Enter Edges(u,v,wieght)\n";
    for(int i=0;i<e;i++)
    {
    fscanf(fp,"%ld %ld %ld", &u, &v, &w);
      g->graph_add_edge(u-1, v-1, w);
    }
    cout<<"Enter Terminals\n";
    for(int i=0;i<t;i++)
    {
    fscanf(fp,"%ld", &u);
      g->terminals.push_back(u-1);
    }
   
    cout<<"l";
    g->create_adjmatrix();
    g->All_Pairs_Shortest_Path();
    
    return g;
}
struct SteinerMin{
    long wt,minu,min_ind1,min_ind2;
};

// Subset_Creator(ST,terminals,r,t1,0,g,tprime);
//  for(long X_size=2;X_size<=g->t;X_size++){
  //      get_sublength_r(ST,g->terminals,X_size,g,tprime);
   // }
   //}
//void get_sublength_r(vector< vector <SteinerMin> >  &ST, vector<long>terminals,long r,graph *g,long tprime){
  //  vector<long> t1;
    //Subset_Creator(ST,terminals,r,t1,0,g,tprime);
//}
void Subset_Creator(vector< vector <SteinerMin> > &ST, vector<long> terminals, long r, vector<long> t1, long terminal_ind,graph *g,long tprime){
//cout<<"\n----------------------r"<<r<<"------------------\n";
 // cout<<"insidde esubset util\n";
  //cout<<"\nt1.size() "<<t1.size()<<" r>> "<<r<<"\n";
  //cout<<"\n r"<<r<<" terminal_ind"<<terminal_ind<<"\n";
  if(t1.size()==r)
  {
        long index=0;
        cout<<"\n";
        for(long k=0;k<r;k++)
        {   cout<<"{"<<t1[k]<<"}";
            index+=(1<<t1[k]);
            
            //cout<<terminals[t1[k]]+1<<" ";
        }
        cout<<"\n index<><>"<<index<<" ";
      //  cout<<"--------------------index"<<index;
        //cout<<"="<<index<<"\n";
        long min1,min2,min_ind1,min_ind2,sum,u,v,k,i,t1index,t2index,total=(1<<r);
        set<pair<long,long> >::iterator it;
        for(v=0;v<g->n;v++)
        {
        
        
            cout<<v<<"---===";
            if(r==g->t)
                v=tprime;//if r is size of tereminal, v
        
            ST[index][v].wt=LONG_MAX;
            
            	for(u=0;u<g->n;u++)
            	{
                		min1=g->dist[v][u];
                		min2=LONG_MAX;
                		
                		for(i=1;i<total-1;i++) //all subset iof subset
                		{
                    			t1index=0;
                    			t2index=0;
                    			for(k=0;k<r;k++)
                    			
                    			{ 
                    				int q=i&(1<<k);    
                    				if(i&(1<<k)) //X
                        			{    //cout<<"k"<<k<<" i"<<i;		
                            			     t1index+=(1<<t1[k]);
                            			     
                        			}
						else	//x-x'
						{  //cout<<"not k"<<k<<" i"<<i;
						    t2index+=(1<<t1[k]);
						    
						}
                    		
						
					}
						    
						    sum=ST[t1index][u].wt+ST[t2index][u].wt;
						    //cout<<"sum "<<sum<<"\n";
						    if(min2>sum)
						    {
							min2=sum;
							min_ind1=t1index;
							min_ind2=t2index;
						    }
					
                		}	
                min1+=min2;
                if(min1<ST[index][v].wt)
                {
                    ST[index][v].wt=min1;
                    ST[index][v].minu=u;
                    ST[index][v].min_ind1=t1index;
                    ST[index][v].min_ind2=t2index;
                   
                }
             }
            if(r==g->t){
		     cout<<index<<v;
		     fprintf(stdout,"VALUE %ld\n",ST[index][v].wt);
                cout<<"\nMinimum Steiner Tree is:";
                cout<<"\n--------------------------------------------------\n";
                for(int q=1;q<(1<<g->t);q++)
                { cout<<"\n";
                 for(int v=0;v<g->n;v++)
                 {
                   cout<<ST[q][v].wt<<" ";
                 
                 }
                }
                cout<<"\n--------------------------------------------------\n";
                
              //  ST[index][v].display();
                //cout<<"Weight of Tree is: "<<ST[index][v].first;
                
               
                steinerTree.n=g->n;
                
               
              
               // exit(0);
                break;
            }
        }
        //cout<<"\n";
        return;
  }
    if(terminal_ind>terminals.size())
        return;
    t1.push_back(terminal_ind);//terminal_index included in t1
    Subset_Creator(ST,terminals,r,t1,terminal_ind+1,g,tprime);
    t1.pop_back();//terminal_index is not included in t1
    Subset_Creator(ST,terminals,r,t1,terminal_ind+1,g,tprime);
}
void get_sublength_r(vector< vector <SteinerMin> >  &ST, vector<long>terminals,long r,graph *g,long tprime){
    vector<long> t1;
    Subset_Creator(ST,terminals,r,t1,0,g,tprime);
}
void Dreyfus_Wagner(graph *g){

    cout<<"inside loop";
    long tprime=g->terminals[g->t-1];
    cout<<"\nt[prime]"<<tprime;
    long u,index,v,i,k;
    long siz=1<<g->t;
    vector< vector <SteinerMin> >ST(siz, vector< SteinerMin > (g->n));
    
    g->terminals.pop_back();
    g->t;
    //Base case
    for(i=0;i<g->t;i++)
    {
        index=1<<i;
       // cout<<"b index"<<index<<" ";
        u=g->terminals[i];
       //base case................... 
       //he trivial case:  IfX={x}for somex∈T′then for everyv∈VwesetST({x},v) =distG(x,v)
        for(v=0;v<g->n;v++){
           // cout<<"\nu:"<<u<<", v:"<<v<<"\t";
            ST[index][v].wt=g->dist[u][v];
            ST[index][v].minu=u;

        } 
    }
                    cout<<"\n--------------------------------------------------\n";
                for(int q=0;q<(1<<(g->t));q++)
                { cout<<"\n";
                 for(int v=0;v<g->n;v++)
                 {
                   cout<<ST[q][v].wt<<" ";
                 
                 }
                
                }
                cout<<"\n--------------------------------------------------\n";
    //
    for(long X_size=2;X_size<=g->t;X_size++){
        get_sublength_r(ST,g->terminals,X_size,g,tprime);
    }
}
int main(int argc, char** argv){
 
        graph *g=graph_init();
 
       cout<<"to drefyfus wagner";
        Dreyfus_Wagner(g);
        
 
        return 0;
}
 
