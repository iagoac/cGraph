#include "../release/cgraph.hpp"
#include "cxxtimer.hpp"

int main(int argc, char* const* argv) {
  Graph g;
  for (int i = 0; i < 10; i++) {
    g.add_node(i);
  }

  g.print_nodes();

  g.add_edge(0,2,5);
  g.add_edge(2,1,3);
  g.add_edge(2,4,1);

  std::cout << g.nodes() << " " << g.edges() << std::endl;

  // std::cout << g.edge[0][2] << " " << g.edge[3][5] << std::endl;
  for (auto i : g.neighboors_list[2]) {
    std::cout << i << std::endl;
  }

  // std::cout << node
}
