#include <glm/glm.hpp> // opengl mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "model.hpp"

// An encapsulation of an object
class Object {

private:
    std::string _objectPath;
    glm::mat4 _model_mat; // Position and orientation
    glm::vec4 _colour;
    Shader* _shader = nullptr;
    // TODO MAKE CONSTRUCTOR PRIVATE
    Model* _model;

public:
    Object(const std::string &objectPath, glm::vec3 pos_in = glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3 scale_in = glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3 colour_in = glm::vec3{0.0f, 0.0f, 0.0f})
        : _objectPath{objectPath}, _colour{colour_in, 1.0f}
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos_in);
        model = glm::scale(model, scale_in);
        this->_model_mat = model;

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
    void Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 colour = glm::vec3{0.0f, 0.0f, 0.0f});

    void scale(glm::vec3 scalar)
    {
        this->_model_mat = glm::scale(_model_mat, scalar);
    }
    
    void translate(glm::vec3 position)
    {
        this->_model_mat = glm::translate(_model_mat, position);
    }

    void rotate(float magnitude, glm::vec3 axis)
    {
        this->_model_mat = glm::rotate(_model_mat, glm::radians(magnitude), axis);
    }

    //////////////////////////
    //
    // Getters and setters
    //
    //////////////////////////
    glm::mat4 getModel()
    {
        return _model_mat;
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

    void setShader(Shader &shader)
    {
        _shader = &shader;
    }
};