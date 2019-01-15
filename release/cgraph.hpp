#ifndef CGRAPH_RELEASE_CGRAPH_H
#define CGRAPH_RELEASE_CGRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>

/* ------------------------------------
     Basic graph class implementation
   ------------------------------------ */

template <typename T = int, typename P = int>
class BaseGraph {
protected:
  int nodes_count = 0;
  int edges_count = 0;

public:
  BaseGraph(){};
  std::vector<T> node;
  std::vector<std::vector<P>> edge;
  std::vector<std::list<int>> neighboors_list;

  int num_nodes() {
    return this->nodes_count;
  }

  int num_edges() {
    return this->edges_count;
  }

  int num_arcs() {
    return this->edges_count;
  }

  void add_node(T new_node) {
    this->node.push_back(new_node);

    P aux;
    for (int i = 0; i < this->edge.size(); i++) {
      this->edge[i].push_back(aux);
    }

    this->nodes_count++;
    std::vector<P> v (this->num_nodes());
    this->edge.push_back(v);

    std::list<int> aux_list;
    this->neighboors_list.push_back(aux_list);
  }

  void add_node() {
    this->add_node(static_cast<T> (0));
  }

  void remove_last_node() {
    this->node.pop_back();
    this->nodes_count--;
  }

  void remove_all_nodes() {
    this->remove_all_edges();
    this->node.resize(0);
    this->nodes_count = 0;
  }

  void print_nodes() {
    for (auto i : node) {
      std::cout << i << std::endl;
    }
  }

  void add_arc(int i, int j, P value) {
    if (i < this->num_nodes() && j < this->num_nodes() && i >= 0 && j >= 0) {
      this->edge[i][j] = value;
      // this->edge[j][i] = value;
      this->neighboors_list[i].push_back(j);
      // this->neighboors_list[j].push_back(i);
      this->edges_count++;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

  void add_arc(int i, int j) {
    this->add_arc(i, j, static_cast<P> (0));
  }

  void remove_arc(int i, int j) {
    for (int k : this->neighboors_list[i]) {
      if (k == j) {
        std::cout << "Edge does not exists!" << std::endl;
        return;
      }
    }

    if (i < this->nodes_count && j < this->nodes_count && i >= 0 && j >= 0) {
      this->neighboors_list[i].remove(j);
      this->edges_count--;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

};


/* ------------------------------
     Graph class implementation
   ------------------------------ */
template <typename T = int, typename P = int>
class Graph: public BaseGraph<T, P> {
public:
  Graph(){};

  void add_edge(int i, int j) {
    this->add_arc(i, j);
    this->add_arc(j, i);
    this->edges_count--;
  }

  void add_edge(int i, int j, P value) {
    this->add_arc(i, j, value);
    this->add_arc(j, i, value);
    this->edges_count--;
  }


  void remove_edge(int i, int j) {
    this->remove_arc(i, j);
    this->remove_arc(j, i);
    this->edges_count++;
  }

  void remove_all_edges() {
    for (int i = 0; i < this->nodes(); i++) {
      this->neighboors_list[i].clear();
    }
    this->edges_count = 0;
  }
};

/* --------------------------------
     Digraph class implementation
   -------------------------------- */
template <typename T = int, typename P = int>
class Digraph: public BaseGraph<T, P> {
public:
  Digraph(){};
};

#endif // CGRAPH_RELEASE_CGRAPH_H
