#include "../release/cgraph.hpp"
#include "cxxtimer.hpp"

int main(int argc, char* const* argv) {
  Graph g;
  for (int i = 0; i < 10; i++) {
    g.add_node();
  }

  g.print_nodes();

  g.add_edge(0,2);

  // std::cout << node
}
