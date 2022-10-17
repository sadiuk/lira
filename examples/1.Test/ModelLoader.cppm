#include <cassert>
module ModelLoader;
import ModelLoader;

import OBJ_Loader;

import lira.math.Types;
import std.core;

import std.core;
export ModelLoader::ModelData ModelLoader::LoadModel(const std::string& path)
{
    using namespace lira::math;
    ModelData model = {};

    objl::Loader loader;
    
    bool loaded = loader.LoadFile(path);
    assert(loaded);
    auto meshes = loader.LoadedMeshes;
    for (auto& mesh : meshes)
    {
        model.objects.emplace_back();
        auto& newMesh = model.objects.back();
        newMesh.name = mesh.MeshName;
        for (auto& vtx : mesh.Vertices)
        {
            ModelData::Vertex attribs;
            attribs.position = reinterpret_cast<f3&>(vtx.Position);
            attribs.normal = reinterpret_cast<f3&>(vtx.Normal);
            attribs.texCoord = reinterpret_cast<f2&>(vtx.TextureCoordinate);
            newMesh.vertices.push_back(attribs);
        }
        newMesh.indices = mesh.Indices;
    }
    return model;
}