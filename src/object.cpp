#include "object.hpp"

void Object::Draw(glm::mat4 view, glm::mat4 projection, glm::vec4 colour)
{
    if (_shader == nullptr)
    {
        std::cerr << "NO SHADER LOADED TO OBJECT CLASS" << std::endl;
    }
    else
    {
        _shader->use();
        _shader->setMat4("view", view);
        _shader->setMat4("projection", projection);
        _shader->setMat4("model", _matrix);
        _shader->setVec4("colour", colour);
        _model->Draw(*_shader);
    }
}