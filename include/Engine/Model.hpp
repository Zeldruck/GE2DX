#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include <Engine/Export.hpp>
#include <Engine/vector2.hpp>
#include <string>
#include <vector>

struct VectorModel;

class GE2DX_ENGINE_API Model
{
public:
	Model(const std::string& texturePath);
	~Model();

private:
	std::string m_texturePath;
	std::vector<int> m_indices;
	std::vector<VectorModel> m_vectorModels;
};

struct VectorModel
{
	Vector2f position;
	float uv;
	//Color
};

#endif // !_MODEL_HPP_