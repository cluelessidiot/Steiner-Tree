#include<iostream>
#include<bits/stdc++.h>
#include<algorithm>
#include<limits.h>
#include<math.h>
using namespace std;
class graph{
    public:
        long n;
        long e;
        long t;
         set < pair<long, long> > p_edges;
        pair<long,long> e_pair;
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
        void generate_adj_matrix(){
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
                vector<long> t(n);
                vector<long> ne(n,-1);
                vector<vector<long> > p(n);
                dist.push_back(t);
                next.push_back(ne);
                path.push_back(p);
            }
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++){
                    dist[i][j] = adj_matrix[i][j];
                    if(dist[i][j]<LONG_MAX){
                            next[i][j]=j;
                    }
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
            //for printing vertex in st_trace
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
            while(u!=v){
                u=next[u][v];
                path[i][j].push_back(u);
            }
        }
        void ST_path()
        {
              for (set<pair<long,long> >::iterator it=p_edges.begin(); it!=p_edges.end(); ++it)
                    fprintf(stdout, "%ld %ld\n", (*it).first,(*it).second);
        
        
        }
       void printPath(long u,long v){
            long k=0;
            for( k=0;k<path[u][v].size()-1;k++)
            {
            if(path[u][v][k]>path[u][v][k+1])
            {
             e_pair = make_pair(path[u][v][k+1]+1,path[u][v][k]+1);
             p_edges.insert(e_pair);
            }
            else
            {
                         e_pair = make_pair(path[u][v][k]+1,path[u][v][k+1]+1);
             p_edges.insert(e_pair);
            
            }
            
            }
	}
};
graph* graph_init(char *filename)
{
   
    long n = 0;
    long e = 0;
    long t = 0;
    long u, v, w;
   
	FILE *fp;
	fp = fopen(filename,"r");
    graph *g = new graph();
    //Enter the number of Vertex\n";
    fscanf(fp,"%ld",&n);
    g->n = n;
    //Enter the number of Edges\n";
    fscanf(fp,"%ld",&e);
    g->e = e;
    //Enter the number of Terminals\n";
	fscanf(fp,"%ld",&t);
    g->t=t;
   // cout<<"Enter Edges(u,v,wieght)\n";
    for(int i=0;i<e;i++)
    {
      fscanf(fp,"%ld %ld %ld", &u, &v, &w);
      g->graph_add_edge(u-1, v-1, w);
    }
    //cout<<"Enter Terminals\n";
    cout<<"terminals are ";
    for(int i=0;i<t;i++)
    {
      fscanf(fp,"%ld", &u);
     cout<<u<<" ";     
      g->terminals.push_back(u-1);
    }
    g->generate_adj_matrix();
    g->All_Pairs_Shortest_Path();
    return g;
}
struct SteinerMin{
    long wt,minu,min_ind1,min_ind2;
};
void ST_backtrace(vector< vector <SteinerMin> > ST,long index,long v, graph *g, vector<long> terminals){
        long u;
	bitset<10> tot(index);
	bitset<10> tot1(index-1);
       if(!(index&(index-1))){
               
                u=ST[index][v].minu;
        
                g->printPath(u,v);	
                return;
        }
        
        g->printPath(v,ST[index][v].minu);
        ST_backtrace(ST,ST[index][v].min_ind1,ST[index][v].minu,g,terminals);
        ST_backtrace(ST,ST[index][v].min_ind2,ST[index][v].minu,g,terminals);
}
void subset_maker(vector< vector <SteinerMin> > &ST, vector<long> terminals, long r, vector<long> t1, long terminal_ind,graph *g,long last_terminal){
    // i will enter this if stmnt iff t1 size equals subset size
    //this if ensures in taking all fixed size subsets
    if(t1.size()==r){
        long index=0;
        for(long k=0;k<r;k++){
            index+=(1<<t1[k]);
            
        }
        bitset<10> Ind(index);
        cout<<"\n subset<><> "<<Ind<<" \n";
        long min1,min2,min_ind1,min_ind2,sum,u,v,k,i,t1index,t2index;
        long total=(1<<r);
                  bitset<10> tot(total);
        for(v=0;v<g->n;v++){
            
            if(r==g->t)
                v=last_terminal;
            
            ST[index][v].wt=LONG_MAX;
            for(u=0;u<g->n;u++)
            {   
              
                min1=g->dist[v][u];
              
                min2=LONG_MAX;
                
                for(i=1;i<total-1;i++){
                    t1index=0;
                    t2index=0;
                    for(k=0;k<r;k++)
                    {
                        // Check if kth bit in the i is set. If the bit 
            		// is set, we consider jth element from set 
                        if(i&(1<<k)){
                            t1index+=(1<<t1[k]);
                        }
                        else{
                            t2index+=(1<<t1[k]);
                        }
                    }
                    sum=ST[t1index][u].wt+ST[t2index][u].wt;
                    if(min2>sum){
                        min2=sum;
                        min_ind1=t1index;
                        min_ind2=t2index;
                    }
                }
                min1+=min2;
                if(min1<ST[index][v].wt){
                    ST[index][v].wt=min1;
                         bitset<10> tot4(index);
                    ST[index][v].minu=u;
                    ST[index][v].min_ind1=t1index;
                    ST[index][v].min_ind2=t2index;
                }
            }
           
            
            if(r==g->t){
            
                fprintf(stdout,"wt of min steiner tree->  %ld\n",ST[index][v].wt);
               
                ST_backtrace(ST,index,v,g,terminals);
                g->ST_path();
              
                break;
            }
        }
        //cout<<"\n";
        return;
    }
    if(terminal_ind>=terminals.size())
        return;
    //similar to knapsack ,either take that vertex or not
    //below steps will give out all possible combinations
    t1.push_back(terminal_ind);//terminal_index included in t1
    subset_maker(ST,terminals,r,t1,terminal_ind+1,g,last_terminal);
    t1.pop_back();//terminal_index is not included in t1
    subset_maker(ST,terminals,r,t1,terminal_ind+1,g,last_terminal);
}

void Steiner_creator(graph *g){

    //last terminal.....
    long last_terminal=g->terminals[g->t-1];
    //all subset size....
    long u,index,v,i,k,siz=1<<g->t;
    //initializing steiner matrix.........
    vector< vector <SteinerMin> >ST(siz, vector< SteinerMin > (g->n));

    //Base case
    for(i=0;i<g->t;i++){
        index=1<<i;
        u=g->terminals[i];
        for(v=0;v<g->n;v++){
           
            ST[index][v].wt=g->dist[u][v];
            ST[index][v].minu=u;
	 }
	     
    }
    long X_size=2;
    while(X_size<=g->t){
        vector<long> t1;
        subset_maker(ST,g->terminals,X_size,t1,0,g,last_terminal);
       X_size++;
    }
}
int main(int argc, char** argv){
    
        graph *g=graph_init(argv[1]);
        Steiner_creator(g);
       
        return 0;
}

