#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
    glm::vec3 position(0.0f, 1.0f, 2.0f);
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
    
    return 0;
}
