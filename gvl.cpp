#include <cstdio>

#include "gvl.h"

namespace gvl {

void PrintNodeId(FILE* fp, const NodeId& node_id) {
  fprintf(fp, "%s", node_id.name.data());

  if (!node_id.port.empty()) {
    fprintf(fp, ":%s", node_id.port.data());
  }
}

void PrintProperties(FILE* fp, const std::vector<Property>& properties) {
  if (!properties.empty()) {
    fprintf(fp, "[ ");
    for (const Property& prop : properties) {
      fprintf(fp, "%s=\"%s\" ", prop.name.data(), prop.value.data());
    }
    fprintf(fp, "]");
  }
}

void PrintEdge(FILE* fp, const Edge& edge) {
  PrintNodeId(fp, edge.from);
  fprintf(fp, " -> ");
  PrintNodeId(fp, edge.to);
  PrintProperties(fp, edge.properties);
  fprintf(fp, ";\n");
}

void PrintNode(FILE* fp, const Node& node) {
  PrintNodeId(fp, node.id);
  PrintProperties(fp, node.properties);
  fprintf(fp, ";\n");
}

void Graph::PrintCommonProperties(FILE* fp) const {
  if (!this->graph_props_.empty()) {
    fprintf(fp, "graph ");
    PrintProperties(fp, this->graph_props_);
    fprintf(fp, ";\n");
  }

  if (!this->common_edge_props_.empty()) {
    fprintf(fp, "edge ");
    PrintProperties(fp, this->common_edge_props_);
    fprintf(fp, ";\n");
  }

  if (!this->common_node_props_.empty()) {
    fprintf(fp, "node ");
    PrintProperties(fp, this->common_node_props_);
    fprintf(fp, ";\n");
  }
}

void Graph::RenderDot(FILE* fp) const {
  fprintf(fp, "digraph %s {\n", this->graph_name_.data());

  PrintCommonProperties(fp);

  for (const Node& node : this->nodes_) {
    PrintNode(fp, node);
  }

  for (const Edge& edge : this->edges_) {
    PrintEdge(fp, edge);
  }

  fprintf(fp, "}\n");
}

} // namespace gvl