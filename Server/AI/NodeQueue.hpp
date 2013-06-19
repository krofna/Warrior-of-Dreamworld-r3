#ifndef HEAP_HPP
#define HEAP_HPP

#include "Shared/Vector2.hpp"
#include "Shared/BasicTypes.hpp"

#include <vector>
#include <cstring>
#include <limits>

struct Node
{
    Node()
    {
        Reset();
    }

    void Reset()
    {
        Color = 0;
    }

    Vector2<uint16> Position;
    Node* pParent;
    uint16 Cost;
    uint16 Color;
    size_t i;
};

class NodeQueue
{
public:
    NodeQueue();
    
    bool Empty();
    void Clear();
    void Insert(Node* pNode);
    void DecreaseKey(size_t i);
    Node* ExtractMin();

private:
    void Heapify(size_t i);

    inline size_t Parent (size_t i) { return (i - 1) / 2; }
    inline size_t Left   (size_t i) { return (i * 2) + 1; }
    inline size_t Right  (size_t i) { return (i * 2) + 2; }
    
    size_t Size;
    std::vector<Node*> A;
};

#endif
