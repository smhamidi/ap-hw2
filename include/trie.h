#ifndef TRIE_H
#define TRIE_H

#include <functional>
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

class Trie {
public:
  // Node class

  class Node {
  public:
    Node(char _data, bool _is_finished);
    Node();

    std::vector<Node *> children;
    char data;
    bool is_finished;
  };
  Node *root;

  Trie();
  Trie(std::initializer_list<std::string> args);
  ~Trie();
  Trie(const Trie &trie);
  // Trie(Trie &&trie);

  void insert(std::string str);
  bool search(std::string query);
  void bfs(std::function<void(Node *&node)> func);
  // void operator=(const Trie &trie);
  // void operator=(Trie &&trie);

private:
};

#endif // TRIE_H