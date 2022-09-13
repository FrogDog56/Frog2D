#include "Transformation.h"

glm::mat4 getTransformationMatrix(glm::vec2 position)
{
	glm::mat4 transformationMatrix = glm::mat4(1.0f);
	transformationMatrix = glm::translate(transformationMatrix, glm::vec3(position.x, position.y, 0.0f));
	return transformationMatrix;
}
