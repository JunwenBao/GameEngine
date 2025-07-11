#pragma

#include <glm/glm.hpp>

namespace GameEngine::Math {

	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& yranslation, glm::vec3& rotation, glm::vec3& scale);

}