#include "../include/trie.h"

Trie::Node::Node(char _data, bool _is_finished)
    : data{_data}, is_finished{_is_finished} {}
Trie::Node::Node() {
  is_finished = false;
  data = '\0';
}

Trie::Trie() { root = new Node(); }
Trie::Trie(std::initializer_list<std::string> args) {
  root = new Node();
  for (auto i : args) {
    Trie::insert(i);
  }
}
Trie::~Trie() {
  if (root == nullptr)
    return;
  std::vector<Node *> nodes;
  this->bfs([&nodes](Trie::Node *&node) { nodes.push_back(node); });
  for (const auto &node : nodes)
    delete node;
}
Trie::Trie(const Trie &trie) {
  root = new Node();
  Node *primary{trie.root};
  Node *copyVersion{this->root};

  std::vector<Node *> primaryInProcess;
  std::vector<Node *> copyInProcess;
  for (auto i : primary->children) {
    primaryInProcess.push_back(i);
    Node *childToPush = new Node{i->data, i->is_finished};
    copyVersion->children.push_back(childToPush);
    copyInProcess.push_back(childToPush);
  }
  for (size_t i = 0; i < primaryInProcess.size(); i++) {
    primary = primaryInProcess[i];
    copyVersion = copyInProcess[i];
    for (auto i : primary->children) {
      primaryInProcess.push_back(i);
      Node *childToPush = new Node{i->data, i->is_finished};
      copyVersion->children.push_back(childToPush);
      copyInProcess.push_back(childToPush);
    }
  }
}

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

void Trie::bfs(std::function<void(Node *&node)> func) {

  Node *current{this->root};
  std::vector<Node *> inProcess;
  // inProcess.push_back(current);

  for (size_t i = 0; i < current->children.size(); i++) {
    inProcess.push_back(current->children[i]);
  }

  for (size_t j = 0; j < inProcess.size(); j++) {
    // visited.push_back(inProcess[j]);
    for (size_t k = 0; k < inProcess[j]->children.size(); k++) {
      inProcess.push_back(inProcess[j]->children[k]);
    }
  }

  inProcess.insert(inProcess.begin(), current);
  for (auto i : inProcess) {
    func(i);
  }
}

bool Trie::search(std::string query) {
  Node *current{this->root};
  bool FlagExist{true};
  for (size_t i = 0; i < query.size(); i++) {
    bool FlagExistInChildren{false};
    size_t indIfExist;
    for (size_t j = 0; j < current->children.size(); j++) {
      if (query[i] == current->children[j]->data) {
        FlagExistInChildren = true;
        indIfExist = j;
        break;
      }
    }
    if (FlagExistInChildren == false) {
      return false;
    } else {
      current = current->children[indIfExist];
    }
  }
  if (current->is_finished == true) {
    return true;
  } else {
    return false;
  }
}
