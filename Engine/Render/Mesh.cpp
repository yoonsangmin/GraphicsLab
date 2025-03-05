#include "Mesh.h"
#include "../Core/Engine.h"
#include "../Shader/Shader.h"

namespace GraphicsEngine
{
    MeshData::MeshData()
    {
    }

    MeshData::MeshData(std::vector<Vertex>&& vertices, std::vector<uint32>&& indices)
    {
        // 파라미터 복사.
        //this->vertices.assign(vertices.begin(), vertices.end());
        //this->indices.assign(indices.begin(), indices.end());

        // Move semantics로 벡터 이동.
        this->vertices = std::move(vertices);
        this->indices = std::move(indices);
        
        stride = Vertex::Stride();

        // 이동 후 원본 벡터를 비워두거나 상태를 관리
        vertices.clear();
        indices.clear();

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = stride * (uint32)this->vertices.size();
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // 정점 데이터.
        D3D11_SUBRESOURCE_DATA vertexData = {};
        vertexData.pSysMem = this->vertices.data();

        // 장치 얻어오기.
        ID3D11Device& device = Engine::Get().Device();

        // 정점 버퍼 생성.
        HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create vertex buffer",
                "Error",
                MB_OK
            );

            __debugbreak();
        }

        D3D11_BUFFER_DESC indexBufferDesc = {};
        indexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)this->indices.size();
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        // 인덱스 데이터.
        D3D11_SUBRESOURCE_DATA indexData = {};
        indexData.pSysMem = this->indices.data();

        // 인덱스 버퍼 생성.
        result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create index buffer",
                "Error",
                MB_OK
            );

            __debugbreak();
        }
    }

    //MeshData::MeshData(std::vector<Vertex>&& vertices, std::vector<uint32>&& indices)
    //{
    //    // rvalue reference를 사용하여 벡터 이동
    //    this->vertices = std::move(vertices);
    //    stride = Vertex::Stride();
    //    this->indices = std::move(indices);
    //}

    MeshData::~MeshData()
    {
        // 리소스 해제.
        if (vertexBuffer)
        {
            vertexBuffer->Release();
        }
        if (indexBuffer)
        {
            indexBuffer->Release();
        }
    }

    void MeshData::Bind()
    {
        // 컨텍스트 얻어오기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 정점/인덱스 버퍼 바인딩.
        static uint32 offset = 0;
        context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

        // 조립할 모양 설정.
        context.IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }

    void MeshData::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
    {
        // 파라미터 복사.
//this->vertices.assign(vertices.begin(), vertices.end());
// Move semantics로 벡터 이동.
        this->vertices.assign(vertices.begin(), vertices.end());

        // 정점 버퍼가 있으면, 해제 후 재생성.
        if (vertexBuffer)
        {
            vertexBuffer->Release();
            vertexBuffer = nullptr;
        }

        D3D11_BUFFER_DESC vertexBufferDesc = {};
        vertexBufferDesc.ByteWidth = stride * (uint32)this->vertices.size();
        vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        // 정점 데이터.
        D3D11_SUBRESOURCE_DATA vertexData = {};
        vertexData.pSysMem = this->vertices.data();

        // 장치 얻어오기.
        ID3D11Device& device = Engine::Get().Device();

        // 정점 버퍼 생성.
        HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

        if (FAILED(result))
        {
            MessageBoxA(
                nullptr,
                "Failed to create vertex buffer",
                "Error",
                MB_OK
            );

            __debugbreak();
        }
    }

    Mesh::Mesh()
    {
    }

    void Mesh::Draw()
    {
        // 컨텍스트 얻어오기.
        static ID3D11DeviceContext& context = Engine::Get().Context();

        // 루프 순회하면서 바인딩 & 드로우.
        for (int ix = 0; ix < (int32)meshes.size(); ++ix)
        {
            meshes[ix]->Bind();
            shaders[ix].lock()->Bind();
            // 드로우 콜.
            context.DrawIndexed(meshes[ix]->IndexCount(), 0, 0);
        }
    }
}