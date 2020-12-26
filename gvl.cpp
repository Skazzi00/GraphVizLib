#include <cstdio>
#include <ostream>

#include "gvl.h"

namespace gvl {

std::ostream& operator<<(std::ostream& out, const NodeId& node_id) {
  out << node_id.name;

  if (!node_id.port.empty()) {
    out << ":" << node_id.port;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<Property>& properties) {
  if (!properties.empty()) {
    out << "[ ";
    for (const Property& prop : properties) {
      out << prop.name << "=\"" << prop.value << "\" ";
    }
    out << "]";
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Edge& edge) {
  out << edge.from << " -> " << edge.to << edge.properties << ";\n";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Node& node) {
  out << node.id << node.properties << ";\n";
  return out;
}

void Graph::PrintCommonProperties(std::ostream& out) const {
  if (!this->graph_props_.empty()) {
    out << "graph " << this->graph_props_ << ";\n";
  }

  if (!this->common_edge_props_.empty()) {
    out << "edge " << this->common_edge_props_ << ";\n";
  }

  if (!this->common_node_props_.empty()) {
    out << "node " << this->common_node_props_ << ";\n";
  }
}

void Graph::RenderDot(std::ostream& out) const {
  out << "digraph " << this->graph_name_ << " {\n";

  PrintCommonProperties(out);

  for (const Node& node : this->nodes_) {
    out << node;
  }

  for (const Edge& edge : this->edges_) {
    out << edge;
  }

  out << "}";
}

} // namespace gvl