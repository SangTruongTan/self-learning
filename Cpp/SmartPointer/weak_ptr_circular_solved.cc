#include <memory>
#include <iostream>

struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Use weak_ptr to avoid owning the previous node
    int mId;
    Node(int id = 0) : mId(id) {}
    ~Node() { std::cout << "[" << mId << "] Node destroyed" << std::endl; }
};

int main() {
    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);
    node2->next = node1;       // node1 owns node2
    node1->prev = node2;       // node2 weakly references node1

    std::cout << "End of main" << std::endl;
    // node1 and node2 are destroyed properly when main ends
    return 0;
}
