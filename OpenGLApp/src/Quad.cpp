#include "Quad.hpp"

//#include <algorithm>
//#include <iostream>

Quad QuadNs::createQuad(const float texID, const float mvpID) {
    Vertex v0;
    v0.position = { -0.5f, -0.5f, 0.0f };
    v0.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    v0.texCoords = { 0.0f, 0.0f };
    v0.texID = texID;
    v0.mvpID = mvpID;

    Vertex v1;
    v1.position = { 0.5f, -0.5f, 0.0f };
    v1.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    v1.texCoords = { 1.0f, 0.0f };
    v1.texID = texID;
    v1.mvpID = mvpID;

    Vertex v2;
    v2.position = { 0.5f, 0.5f, 0.0f };
    v2.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    v2.texCoords = { 1.0f, 1.0f };
    v2.texID = texID;
    v2.mvpID = mvpID;

    Vertex v3;
    v3.position = { -0.5f, 0.5f, 0.0f };
    v3.color = { 0.0f, 0.0f, 0.0f, 0.0f };
    v3.texCoords = { 0.0f, 1.0f };
    v3.texID = texID;
    v3.mvpID = mvpID;

    return { v0, v1, v2, v3 };
}

Quads QuadNs::createQuads(const unsigned int quantity, const float texID, const float mvpID) {
    Quads quads;

    for (unsigned int i = 0; i < quantity; i++) {
        quads.emplace_back(createQuad(texID, mvpID));
    }

    return quads;
}

VertexBuf QuadNs::getVertexBuf(const Quad& quad, bool bColor, bool bTexCoords, bool bTexID, bool bMvpID) {
    std::vector<float> vBuf;
    vBuf.reserve(sizeof(quad) / sizeof(float));

    //std::cout << "vBuf.capacity() = " << vBuf.capacity() << std::endl;
    for (const Vertex& v : quad) {
        //vBuf.push_back(v.position.x);
        //vBuf.push_back(v.position.y);
        //vBuf.push_back(v.position.z);
        //if (bColor) {
        //	vBuf.push_back(v.color.r);
        //	vBuf.push_back(v.color.g);
        //	vBuf.push_back(v.color.b);
        //	vBuf.push_back(v.color.a);
        //}
        //if (bTexCoords) {
        //	vBuf.push_back(v.texCoords.x);
        //	vBuf.push_back(v.texCoords.y);
        //}
        //if (bTexID)
        //	vBuf.push_back(v.texID);
        //if (bMvpID)
        //	vBuf.push_back(v.mvpID);

        vBuf.insert(vBuf.end(), { v.position.x, v.position.y, v.position.x });
        if (bColor)     vBuf.insert(vBuf.end(), { v.color.r, v.color.g, v.color.b, v.color.a });
        if (bTexCoords) vBuf.insert(vBuf.end(), { v.texCoords.x, v.texCoords.y });
        if (bTexID)     vBuf.insert(vBuf.end(), v.texID);
        if (bMvpID)     vBuf.insert(vBuf.end(), v.mvpID);

    }

    //std::cout << "vBuf.capacity() = " << vBuf.capacity() << std::endl;
    //std::cout << "vBuf.size() = " << vBuf.size() << std::endl;
    vBuf.shrink_to_fit();
    //std::cout << "vBuf.capacity() = " << vBuf.capacity() << std::endl;
    //std::cout << "vBuf.size() = " << vBuf.size() << std::endl;

    return vBuf;
}

VertexBuf QuadNs::getVertexBuf(const Quads& quads, bool bColor, bool bTexCoords, bool bTexID, bool bMvpID) {
    VertexBuf vBuf;

    vBuf.reserve(sizeof(quads) / sizeof(float));

    for (const Quad& quad : quads) {

        for (const Vertex& v : quad) {
            vBuf.insert(vBuf.end(), { v.position.x, v.position.y, v.position.x });
            if (bColor)     vBuf.insert(vBuf.end(), { v.color.r, v.color.g, v.color.b, v.color.a });
            if (bTexCoords) vBuf.insert(vBuf.end(), { v.texCoords.x, v.texCoords.y });
            if (bTexID)     vBuf.insert(vBuf.end(), v.texID);
            if (bMvpID)     vBuf.insert(vBuf.end(), v.mvpID);
        }
    }
    vBuf.shrink_to_fit();
    return vBuf;
}


Indices QuadNs::getIndices(const unsigned int quantity) {
    Indices indices(quantity * 6);

    for (unsigned int vInd = 0; vInd < quantity; vInd++) {
        unsigned int ind = vInd * 6;
        unsigned int vOffset = vInd * 4;
        indices[ind]   = 0 + vOffset;
        indices[ind+1] = 1 + vOffset;
        indices[ind+2] = 2 + vOffset;
        indices[ind+3] = 2 + vOffset;
        indices[ind+4] = 3 + vOffset;
        indices[ind+5] = 0 + vOffset;
    }

    return indices;
}