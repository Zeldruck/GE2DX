#include <Engine/Model.hpp>
#include <nlohmann/json.hpp>
#include <fstream>

Model::Model(const std::string& texturePath)
{
	std::ifstream f(texturePath.c_str());
	nlohmann::json data = nlohmann::json::parse(f);

	m_texturePath = data["texture"].get<std::string>();
	m_indices = data["indices"].get <std::vector<int>>();

	for (auto vertex : data["vertices"])
	{
		VectorModel	vec;
		vec.position.x = vertex["position"]["x"].get<float>();
		vec.position.y = vertex["position"]["y"].get<float>();
		vec.uv = vertex["uv"].get<float>();

		m_vectorModels.push_back(vec);
	}
}

Model::~Model()
{
}
