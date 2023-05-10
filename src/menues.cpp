#include "menues.hpp"

void Menues::display(Camera* cam)
{
    
    Scene* scene = Scene::getInstance();
    
    
    int i = 0;
    
    ImGui::Begin("Game objects");

    if(ImGui::TreeNode("Objects"))
    {
        for (auto& obj_ptr : scene->getObjects())
        {
            Object* obj = obj_ptr.get();

            if (ImGui::TreeNode((void*)(intptr_t)i, "Object %d", i))
            {
                // ImGui::Text(obj->)
                std::stringstream ss_name;
                ss_name << "Box [" << i << "] controls";
                ImGui::Text("Controls for box: ");
                std::stringstream ss_pos;
                ss_pos << "Box " << i << " pos : [X:Y:Z] = " << obj->_position.x << "," << obj->_position.y << "," << obj->_position.z;
                ImGui::Text(ss_pos.str().c_str());
                std::stringstream ss_distance;
                ss_distance << "Box " << i << " is " << glm::length(obj->_position-cam->Position) << " units away from you.";
                ImGui::Text(ss_distance.str().c_str());
                ImGui::SliderFloat("X pos: ", &obj->_position.x, -100.0f, 100.0f);
                ImGui::SliderFloat("Y pos: ", &obj->_position.y, -100.0f, 100.0f);
                ImGui::SliderFloat("Z pos: ", &obj->_position.z, -100.0f, 100.0f);

                ImGui::NewLine();

                ImGui::SliderFloat("X rotation", &obj->_rotation.x, -10.0f, 100.0f);
                ImGui::SliderFloat("Y rotation", &obj->_rotation.y, -10.0f, 10.0f);
                ImGui::SliderFloat("Z rotation", &obj->_rotation.z, -10.0f, 10.0f);

                ImGui::NewLine();

                ImGui::SliderFloat("X scale", &obj->_scale.x, 0.1f, 10.0f);
                ImGui::SliderFloat("Y scale", &obj->_scale.y, 0.1f, 10.0f);
                ImGui::SliderFloat("Z scale", &obj->_scale.z, 0.1f, 10.0f);
                ImGui::SliderFloat("Scale", &obj->_scaleScalar, 0.1f, 10.0f);
                
                ImGui::TreePop();
            }
            i++;
        }
        ImGui::TreePop();
    }
    ImGui::End();
}