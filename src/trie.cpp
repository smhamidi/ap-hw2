#include "../include/trie.h"

Trie::Node::Node(char _data, bool _is_finished)
    : data{_data}, is_finished{_is_finished} {}
Trie::Node::Node() {
  is_finished = false;
  data = '\0';
}

Trie::Trie() { root = new Node(); }

void Trie::insert(std::string str) {

  Node *ourNode{this->root};

  for (size_t i = 0; i < str.size(); i++) {
    bool FlagExist = false;
    size_t indexIfExist{};
    for (size_t j = 0; j < ourNode->children.size(); j++) {
      if (str[i] == ourNode->children[j]->data) {
        FlagExist = true;
        indexIfExist = j;
      }
    }

    if (FlagExist == false) {
      Node *addNode{new Node{str[i], false}};
      ourNode->children.push_back(addNode);
      size_t ourNodeSize{ourNode->children.size()};
      ourNode = ourNode->children[ourNodeSize - 1];
    } else {
      ourNode = ourNode->children[indexIfExist];
    }
  }
  ourNode->is_finished = true;
}

// Trie::~Trie() {
//   if (root == nullptr)
//     return;
//   std::vector<Node *> nodes;
//   this->bfs([&nodes](Trie::Node *&node) { nodes.push_back(node); });
//   for (const auto &node : nodes)
//     delete node;
// }