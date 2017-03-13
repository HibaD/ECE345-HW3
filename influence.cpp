#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

class Graph{
private:
    int V;
    list< pair <int, double> > *adj;
    
public:
    Graph(int V);
    void addEdge(int u, int v, double w);
    int shortestPath(int s, int T);
};

Graph::Graph(int V){
    this->V = V;
    adj = new list< pair <int, double> > [V];
}

int count = 0;

void Graph::addEdge(int u, int v, double w){
    adj[u].push_back(make_pair(v, w));
    //adj[v].push_back(make_pair(w, u));
}

typedef pair<double, int> iPair;

int Graph::shortestPath(int src, int T)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    
    vector<double> dist(V, INT_MAX);
 
    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
 
        list< pair <int, double> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            double weight = (*i).second;
 
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    printf("Vertex Distance from Source\n");
    int spread = 0;
    for (int i = 0; i < V; ++i){
        printf("%d     %f\n", i, dist[i]);
        if (dist[i] <= T){
            spread++;
        }
    }
    return spread;
}

struct Influencers{
    int nodeA;
    int nodeB;
    double weight;
};

int numVertices = 0;

// check if parser works
void print(vector<Influencers> array){
  for (int i=0; i<array.size(); i++){
      cout << array[i].nodeA << " ";
      cout << array[i].nodeB << " ";
      cout << array[i].weight << " ";
      cout << "\n";
      if (array[i].nodeA > numVertices){
          numVertices = array[i].nodeA;
      }
      if (array[i].nodeB > numVertices){
          numVertices = array[i].nodeB;
      }
  }
}

Influencers lineToObject( string line){
  Influencers newInfluencer;
  istringstream ss(line);
  //store values into the structure
  ss >> newInfluencer.nodeA;
  ss >> newInfluencer.nodeB;
  ss >> newInfluencer.weight;
  
  return newInfluencer;
}

vector<Influencers> parser(char const *filename[]){
  //Open input file produced by command line argument
  ifstream file;
  file.open(filename[1], ifstream::in);
  //Initialize new vector of objects
  vector<Influencers> array;
  //read one line at a time
  string line;
  while(getline(file,line,'\n')){
    array.push_back(lineToObject(line));
  }
  file.close();
  return array;
}

void TopInfluencers (Graph g, int T){
    
    cout << "TOP-1 INFLUENCER: " << ", SPREAD: " << "TIME: " << "\n";
    cout << "TOP-2 INFLUENCER: " << ", MARGINAL SPREAD: " << "TIME: " << "\n";
}

int main(int argc, char const *argv[]) {
  vector<Influencers> array = parser(argv);
  print(array);
  
  Graph g(numVertices);
  for (int i=0; i < array.size(); i++){
      g.addEdge(array[i].nodeA, array[i].nodeB, array[i].weight);
  }
  
  int T = atoi(argv[2]);
  
  int TI1, temp, spread, spreadTI1 = 0;
  temp = 0;
  for (int i = 0; i < numVertices-1; i++){
      spread = g.shortestPath(i, T);
      if (spread > spreadTI1){
          TI1 = i;
          spreadTI1 = spread;
      }
  }
  
  cout << "TOP-1 INFLUENCER: " << TI1 << ", SPREAD: " << spreadTI1 << " TIME: " << "\n";
    
  //g.shortestPath(0, T);
  
  //TopInfluencers(g, T);
  //print(array);
  return 0;
}

