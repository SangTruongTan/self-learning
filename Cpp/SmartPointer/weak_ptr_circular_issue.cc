#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;
    ~Node() { std::cout << "Node destroyed" << std::endl; }
};

int main() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2; // node1 points to node2
    node2->next = node1; // node2 points to node1

    // Reference count of node1 and node2 is 2 each (one from the variable, one from the other node)
    std::cout << "End of main" << std::endl;
    // Destructor never called due to circular reference!
    return 0;
}
