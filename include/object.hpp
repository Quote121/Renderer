#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glm/glm.hpp> // opengl mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "model.hpp"


// An encapsulation of an object
class Object {

private:
    std::string _objectPath;
    glm::mat4 _matrix; // Position and orientation
    glm::vec4 _colour;
    Shader* _shader = nullptr;
    // TODO MAKE CONSTRUCTOR PRIVATE
    Model* _model;

public:
    glm::vec3 vRotations = {0.0f, 0.0f, 0.0f};
    glm::vec3 _scaleVector = {1.0f, 1.0f, 1.0f};
    float _scale = 1.0f;

    // Constructor with shader
    Object(const std::string &objectPath, Shader &shader, glm::vec3 pos_in = glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3 scale_in = glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3 colour_in = glm::vec3{0.0f, 0.0f, 0.0f})
    : _objectPath{objectPath}, _colour{colour_in, 1.0f}
    {
        this->setShader(shader);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos_in);
        model = glm::scale(model, scale_in);
        this->_matrix = model;
        _model = new Model(objectPath);
    };

    ~Object()
    {
        delete(_model);
        _shader = nullptr;
        _model = nullptr;
    }

    void Draw(Shader &shader)
    {
        _model->Draw(shader);
    }

    // Set shader already no need to change it
    // Can just pass in view and projection matrices
    void Draw(glm::mat4 view, glm::mat4 projection, glm::vec4 colour = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f});

    void setShader(Shader &shader)
    {
        _shader = &shader;
    }

    glm::mat4 getMatrix()
    {
        return _matrix;
    }
    
    glm::vec3 getColour()
    {
        return glm::vec3(_colour);
    }

    // With alpha channel
    glm::vec4 getColourAlpha()
    {
        return _colour;
    }

    glm::vec3 getPosition()
    {
        return glm::vec3(_matrix[3]);
    }

    glm::vec3 getScale();

    // Riddled with problems (we loose accuracy at low level due to floating point errors)
    void setPosition(glm::vec3 position);

    void setScale(glm::vec3 newScale);
    void setScale(float newScale);

    void rotate(float x, float y, float z);
    void rotate(glm::vec3 rotation);

    void scale(float factor);
    void scale(glm::vec3 factor);

};

#endif // OBJECT_HPP