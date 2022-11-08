#pragma once

#include <Engine/Color.hpp>
#include <Engine/Export.hpp>
#include <Engine/Renderable.hpp>
#include <Engine/vector2.hpp>
#include <nlohmann/json_fwd.hpp> //< header sp�cial qui fait des d�clarations anticip�es des classes de la lib
#include <SDL.h>
#include <filesystem>
#include <memory>
#include <vector>

class SDLpp_renderer;
class SDLpp_texture;
class Transform;

struct ModelVertex
{
	Vector2f pos;
	Vector2f uv;
	Color color;
};

class GE2DX_ENGINE_API Model : public Renderable // Un ensemble de triangles
{
public:
	Model() = default;
	Model(std::shared_ptr<const SDLpp_texture> texture, std::vector<ModelVertex> vertices, std::vector<int> indices);
	Model(const Model&) = default;
	Model(Model&&) = default;
	~Model() = default;

	void Draw(SDLpp_renderer& renderer, const Transform& cameraTransform, const Transform& transform) override;

	bool IsValid() const;

	bool SaveToFile(const std::filesystem::path& filepath) const;
	nlohmann::ordered_json SaveToJSon() const;

	Model& operator=(const Model&) = delete;
	Model& operator=(Model&&) = default;

	static Model LoadFromFile(const std::filesystem::path& filepath);
	static Model LoadFromJSon(const nlohmann::json& doc);

private:
	bool SaveToFileRegular(const std::filesystem::path& filepath) const;
	bool SaveToFileCompressed(const std::filesystem::path& filepath) const;
	bool SaveToFileBinary(const std::filesystem::path& filepath) const;

	static Model LoadFromFileRegular(const std::filesystem::path& filepath);
	static Model LoadFromFileCompressed(const std::filesystem::path& filepath);
	static Model LoadFromFileBinary(const std::filesystem::path& filepath);

	std::shared_ptr<const SDLppTexture> m_texture;
	std::vector<ModelVertex> m_vertices;
	std::vector<SDL_Vertex> m_sdlVertices;
	std::vector<int> m_indices;
};