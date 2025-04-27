#pragma once
#ifndef VOLUMETRICCLOUDS_H
#define VOLUMETRICCLOUDS_H

namespace Arcane
{
	class Texture3D;
	class GLCache;
	class Shader;
	struct VolumetricCloudComponent;

	enum class CloudNoiseAlgorithm : int
	{
		CloudNoiseAlgorithm_Worley,
		CloudNoiseAlgorithm_Perlin,
		CloudNoiseAlgorithmSize
	};

	struct NoiseTextureParams
	{
		CloudNoiseAlgorithm NoiseAlgorithm = CloudNoiseAlgorithm::CloudNoiseAlgorithm_Worley;
		float Frequency = 8.0f;
		int Octaves = 8;
		glm::vec3 NoiseScale = glm::vec3(4.0f, 4.0f, 4.0f);
		std::mt19937::result_type Seed = 12345;
	};

	class VolumetricClouds
	{
	public:
		VolumetricClouds();

		void DrawClouds(const VolumetricCloudComponent* volumetricComponent);

		// Static Function for the editor to use to pre-generate a 3D noise texture that can be used for the volumetric cloud effect at runtime
		static Texture3D* Generate3DNoiseTexture(NoiseTextureParams& params);
	private:
		static void Generate3DTextureChunk(std::vector<unsigned char>& textureData, NoiseTextureParams& params, int width, unsigned int height, unsigned int depth, unsigned int zStart, unsigned int zEnd, glm::vec3& scale);
	private:
		Shader* m_VolumetricCloudShader;
		GLCache* m_GLCache;
	};
}
#endif
