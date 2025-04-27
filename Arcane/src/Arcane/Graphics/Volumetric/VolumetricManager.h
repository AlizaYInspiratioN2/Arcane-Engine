#pragma once
#ifndef VOLUMETRICMANAGER_H
#define VOLUMETRICMANAGER_H

namespace Arcane
{
	class Scene;
	struct TransformComponent;
	struct VolumetricCloudComponent;

	class VolumetricManager
	{
	public:
		VolumetricManager(Scene* scene);
		~VolumetricManager();

		void Init();
		void Update();
	private:
		void FindClosestVolumetricCloud();
	private:
		Scene* m_Scene;

		// Currently only supports one volumetric cloud volume at a time, so keep track of the closest so come transparent rendering time we can use that volumetric cloud component
		VolumetricCloudComponent* m_ClosestVolumetricCloudComponent;
		TransformComponent* m_ClosestVolumetricCloudTransform;
	};
}

#endif
