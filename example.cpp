#include "gvl.h"
#include <fstream>

int main() {
  std::ofstream out("out.gv");
  gvl::Graph g("G");
  g.AddGraphProperty("rankdir", "RL");
  g.AddCommonNodeProperty("shape", "box");
  g.AddNode("1");
  g.AddNode("2");
  g.AddNode("3");
  g.AddEdge("1", "2");
  g.AddEdge("2", "3");
  g.AddEdge("1","3");
  g.AddEdge("1","1");
  g.RenderDot(out);
  return 0;
}
