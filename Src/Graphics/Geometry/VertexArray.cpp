#include "VertexArray.h"
#include  "glad/glad.h"

VertexArray::VertexArray(const float *vertices, const unsigned int numVertices, const unsigned int *indices,
                         const unsigned int numIndices, const unsigned int stride,
                         std::vector<VertexAttribute> &layout)
: mNumVertices(numVertices)
, mNumIndices(numIndices)
, mStride(stride)
, mVertexBuffer(0)
, mIndexBuffer(0)
, mVertexArray(0)
{
    // Create vertex array
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    // Create vertex buffer
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices * stride, vertices, GL_STATIC_DRAW);

    // Create index buffer
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long>(numIndices * sizeof(GLuint)), indices, GL_STATIC_DRAW);

    for (const auto&[index, size, type, normalized, offset] : layout){
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            size,
            type,
            normalized ? GL_TRUE : GL_FALSE,
            static_cast<GLsizei>(stride),
            reinterpret_cast<void*>(offset)
        );
    }
}


VertexArray::~VertexArray() {
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}


void VertexArray::SetActive() const {
    glBindVertexArray(mVertexArray);
}