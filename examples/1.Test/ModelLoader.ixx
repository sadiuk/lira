export module ModelLoader;

import lira.math.Types;
import std.core;

export class ModelLoader
{
public:
	struct ModelData
	{
        struct Vertex
        {
            lira::math::f3 position;
            lira::math::f3 normal;
            lira::math::f2 texCoord;
        };
        struct Mesh
        {
            std::string name;
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
        };
        std::vector<Mesh> objects;
	};

    ModelData LoadModel(const std::string& path);
};