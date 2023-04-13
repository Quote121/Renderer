#include "object.hpp"

void Object::Draw(glm::mat4 view, glm::mat4 projection, glm::vec4 colour)
{
    
    if (_shader == nullptr)
    {
        std::cerr << "NO SHADER LOADED TO OBJECT CLASS" << std::endl;
    }
    else
    {
        // Apply all position and scaling before drawing
        _shader->use();
        _shader->setMat4("view", view);
        _shader->setMat4("projection", projection);
        _shader->setMat4("model", _matrix);
        _shader->setVec4("colour", colour);
        _model->Draw(*_shader);
    }
}

void Object::rotate(float x, float y, float z)
{
    this->_matrix = glm::rotate(_matrix, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->_matrix = glm::rotate(_matrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->_matrix = glm::rotate(_matrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Object::rotate(glm::vec3 rotation)
{
    this->_matrix = glm::rotate(_matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->_matrix = glm::rotate(_matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->_matrix = glm::rotate(_matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Object::scale(float factor)
{
    _matrix = glm::scale(_matrix, glm::vec3{factor*1.0f, factor*1.0f, factor*1.0f});
}

void Object::scale(glm::vec3 factor)
{
    _matrix = glm::scale(_matrix, factor);
}

glm::vec3 Object::getScale()
{
    glm::vec3 scale;
    scale.x = glm::length(_matrix[0]);
    scale.y = glm::length(_matrix[1]);
    scale.z = glm::length(_matrix[2]);
    return scale;
}

void Object::setScale(glm::vec3 newScale)
{
    _matrix[0] *= newScale.x / getScale().x;
    _matrix[1] *= newScale.y / getScale().y;
    _matrix[2] *= newScale.z / getScale().z;
}

void Object::setScale(float newScale)
{
    _matrix[0] *= newScale / glm::length(getScale());
    _matrix[1] *= newScale / glm::length(getScale());
    _matrix[2] *= newScale / glm::length(getScale());
}

void Object::setPosition(glm::vec3 position)
{
    _matrix[3] = glm::vec4(position, 1.0f);
}
