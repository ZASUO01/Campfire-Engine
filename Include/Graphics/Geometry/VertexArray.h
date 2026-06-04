#pragma once
#include <vector>

class VertexArray {
public:
    struct VertexAttribute {
        unsigned int index;
        int size;
        unsigned int type;
        bool normalized;
        size_t offset;
    };

    VertexArray(const float* vertices, unsigned int numVertices,
                const unsigned int* indices, unsigned int numIndices,
                unsigned int stride, std::vector<VertexAttribute> &layout);
    ~VertexArray();

    void SetActive() const;
    [[nodiscard]] unsigned int GetNumIndices() const { return mNumIndices; }
    [[nodiscard]] unsigned int GetNumVertices() const { return mNumVertices; }

    [[nodiscard]] unsigned int GetID() const { return mVertexArray; }

private:
    unsigned int mNumVertices;
    unsigned int mNumIndices;
    unsigned int mStride;
    unsigned int mVertexBuffer;
    unsigned int mIndexBuffer;
    unsigned int mVertexArray;
};