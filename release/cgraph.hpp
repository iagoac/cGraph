#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

template <typename T = int, typename P = int>
class Graph {
private:
  int nodes = 0;
  int edges = 0;

public:
  Graph(){};

  std::vector<T> node;
  std::vector<std::vector<P>> edge;
  std::vector<std::list<int>> neighboors_list;

  void add_node() {
    this->node.push_back(static_cast<T> (0));
    nodes++;
  }

  void add_node(T new_node) {
    this->node.push_back(new_node);
    this->nodes++;

    std::vector<P> v;
    this->edge.push_back(v);
  }

  void remove_last_node() {
    this->node.pop_back();
    this->nodes--;
  }

  void remove_all_nodes() {
    this->remove_all_edges();
    this->node.resize(0);
    this->nodes = 0;
  }

  void print_nodes() {
    for (auto i : node) {
      std::cout << i << std::endl;
    }
  }

  void add_edge(int i, int j, P value) {
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0) {
      this->edge[i][j] = value;
      this->edge[j][i] = value;
      this->neighboors_list[i].push_back(j);
      this->neighboors_list[j].push_back(i);
      this->edges++;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

  void remove_edge(int i, int j) {
    if () {
      std::cout << "Edge does not exists!" << std::endl;
    }
    if (i < this->nodes && j < this->nodes && i >= 0 && j >= 0) {
      this->neighboors_list[i].remove(j);
      this->neighboors_list[j].remove(i);
      this->edges--;
    } else {
      std::cout << "Nodes does not exist" << std::endl;
    }
  }

  void remove_all_edges() {
    for (int i = 0; i < this->nodes; i++) {
      this->neighboors_list[i].clear();
    }
    this->edges = 0;
  }

};

// template <typename T = int>
// class Digraph {
//   int nodes = 0;
//   int arcs = 0;
//
//   std::vector<T> node;
//
// public:
//   Digraph(){};
// };
