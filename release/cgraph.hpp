#ifndef CGRAPH_RELEASE_CGRAPH_H
#define CGRAPH_RELEASE_CGRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <iostream>

/* --------------------------------
     Digraph class implementation
   -------------------------------- */

template <typename T = int, typename P = int>
class Digraph {
protected:
  int edges_count = 0;

public:
  Digraph(){};
  std::vector<T> node;
  std::vector<std::vector<P>> edge;
  std::vector<std::list<int>> adjacency_list;
  std::vector<std::list<int>> in_node;
  std::vector<std::list<int>> out_node;
  std::vector<int> terminals;
  std::vector<int> terminal_list;

  int num_nodes() { return this->node.size(); }

  int num_edges() { return this->edges_count; }

  int num_arcs() { return this->edges_count; }

  void add_node(T new_node) {
    this->node.push_back(new_node);
    this->terminals.push_back(0);

    P aux;
    for (int i = 0; i < this->edge.size(); i++) {
      this->edge[i].push_back(aux);
    }

    std::vector<P> v (this->num_nodes());
    this->edge.push_back(v);

    std::list<int> aux_list;
    this->adjacency_list.push_back(aux_list);
    this->in_node.push_back(aux_list);
    this->out_node.push_back(aux_list);

  }

  void add_node() {
    this->add_node(static_cast<T> (0));
  }

  void add_nodes(int quantity) {
    for (int i = 0; i < quantity; i++) {
      this->add_node();
    }
  }

  void remove_all_nodes() {
    this->remove_all_edges();
    this->node.resize(0);
    this->adjacency_list.resize(0);
    this->in_node.resize(0);
    this->out_node.resize(0);
    this->terminals.resize(0);
    this->terminal_list.resize(0);
  }

  void print_nodes() {
    for (auto i : node) {
      std::cout << i << std::endl;
    }
  }

  void add_arc(int i, int j, P value) {
    if (i < this->num_nodes() && j < this->num_nodes() && i >= 0 && j >= 0) {
      this->edge[i][j] = value;
      this->adjacency_list[i].push_back(j);
      this->in_node[j].push_back(i);
      this->out_node[i].push_back(j);
      this->edges_count++;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

  void add_arc(int i, int j) {
    this->add_arc(i, j, static_cast<P> (0));
  }

  void remove_arc(int i, int j) {
    for (int k : this->adjacency_list[i]) {
      if (k == j) {
        std::cout << "Edge does not exists!" << std::endl;
        return;
      }
    }

    if (i < this->num_nodes() && j < this->num_nodes() && i >= 0 && j >= 0) {
      this->neighboors_list[i].remove(j);
      this->in_node[j].remove(i);
      this->out_node[i].remove(j);
      this->edges_count--;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

  void add_edge(int i, int j) { this->add_arc(i,j); }
  void add_edge(int i, int j, P value) { this->add_arc(i, j, value); }
  void remove_edge(int i, int j) { this->remove_arc(i, j); }
  bool is_terminal(int i) { return (this->terminals[i]); }
  void set_terminal(int i) { this->terminals[i] = 1; this->terminal_list.push_back(i); }
  int num_terminals(void) { return (this->terminal_list.size()); }

  /*********************************************************************
  ********************** Shortest path algorithms **********************
  *********************************************************************/
std::vector<int> dijkstra(std::vector<std::std::vector<double>> costs) {
  /* Creating the Dijktra's predefined and distance vectors */
  std::vector<double> dist(this->num_nodes(), std::numeric_limits<double>::max());
  std::vector<int>    prev(this->num_nodes(), -1);
  dist[0] = 0.0;

  /* Priority queue of nodes that were not yet analyzed
  Queue uses a std::pair<int, int> where the first int
  is the distance and the second is the node number */
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int,int>>,
                      std::greater<std::pair<int,int>>> q;
  q.emplace(dist[0], 0);

  while (!q.empty()) {
    /* Gets the node with minimum distance */
    int next = q.top().second;
    q.pop();

    /* For all of its neigboors
    make the dijkstra relaxation step */
    for (auto j : this->out_node[next]) {
      int new_dist = dist[next] + cost[i][j];
      if (dist[j] > new_dist) {
        prev[j] = next;
        dist[j] = new_dist;
        q.emplace(dist[j], j);
      }
    }
  }
  /* Returns the shortest path tree */
  return (prev);
  }

  std::vector<int> dijkstra(double multiplier) {
    /* Creating the Dijktra's predefined and distance vectors */
    std::vector<double> dist(this->num_nodes(), std::numeric_limits<double>::max());
    std::vector<int>    prev(this->num_nodes(), -1);
    dist[0] = 0.0;

    /* Priority queue of nodes that were not yet analyzed
    Queue uses a std::pair<int, int> where the first int
    is the distance and the second is the node number */
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int,int>>,
                        std::greater<std::pair<int,int>>> q;
    q.emplace(dist[0], 0);

    while (!q.empty()) {
      /* Gets the node with minimum distance */
      int next = q.top().second;
      q.pop();

      /* For all of its neigboors
      make the dijkstra relaxation step */
      for (auto j : this->out_node[next]) {
        int new_dist = dist[next] + this->edge[next][j].lower +
                       multiplier * (this->edge[next][j].upper - this->edge[next][j].lower);
        if (dist[j] > new_dist) {
          prev[j] = next;
          dist[j] = new_dist;
          q.emplace(dist[j], j);
        }
      }
    }
    /* Returns the shortest path tree */
    return (prev);
  }
};


/* ------------------------------
     Graph class implementation
   ------------------------------ */
template <typename T = int, typename P = int>
class Graph: public Digraph<T, P> {
public:
  Graph(){};

  void add_edge(int i, int j, P value) {
    this->Digraph<T,P>::add_arc(i, j, value);
    this->Digraph<T,P>::add_arc(j, i, value);

    /* Needed to keep the in_node and out_node as in the
    instance file description. This is needed for not
    duplicating some constraints along with the model */
    this->in_node[i].pop_back();
    this->out_node[j].pop_back();

    /* Remove one edge from the counter, for obvious reasons */
    this->edges_count--;
  }

  void add_edge(int i, int j) {
    this->add_edge(i, j, static_cast<P> (0));
  }

  void remove_edge(int i, int j) {
    this->Digraph<T,P>::remove_arc(i, j);
    this->Digraph<T,P>::remove_arc(j, i);
    this->edges_count++;
  }

  void remove_all_edges() {
    for (int i = 0; i < this->nodes(); i++) {
      this->neighboors_list[i].clear();
      this->in_node[i].clear();
      this->out_node[i].clear();
    }
    this->edges_count = 0;
  }

  void add_arc(int i, int j) { this->add_edge(i, j); };
  void add_arc(int i, int j, P value) { this->add_edge(i, j, value); };
  void remove_arc(int i, int j) { this->remove_edge(i, j); }
  void remove_all_arcs(void) { this->remove_all_edges(); }
};

#endif // CGRAPH_RELEASE_CGRAPH_H
