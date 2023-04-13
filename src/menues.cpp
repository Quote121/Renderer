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

            glm::vec3 pos = obj->getPosition();
            glm::vec3 scale = obj->getScale();

            if (ImGui::TreeNode((void*)(intptr_t)i, "Object %d", i))
            {
                std::stringstream ss_name;
                ss_name << "Box [" << i << "] controls";
                ImGui::Text("Controls for box: ");
                std::stringstream ss_pos;
                ss_pos << "Box " << i << " pos : [X:Y:Z] = " << pos.x << "," << pos.y << "," << pos.z;
                ImGui::Text(ss_pos.str().c_str());
                std::stringstream ss_distance;
                ss_distance << "Box " << i << " is " << glm::length(pos-cam->Position) << " units away from you.";
                ImGui::Text(ss_distance.str().c_str());
                ImGui::SliderFloat("X pos: ", &pos.x, -100.0f, 100.0f);
                ImGui::SliderFloat("Y pos: ", &pos.y, -100.0f, 100.0f);
                ImGui::SliderFloat("Z pos: ", &pos.z, -100.0f, 100.0f);

                ImGui::NewLine();

                ImGui::SliderFloat("X rotationalVelocity", &obj->vRotations.x, -10.0f, 100.0f);
                ImGui::SliderFloat("Y rotationalVelocity", &obj->vRotations.y, -10.0f, 10.0f);
                ImGui::SliderFloat("Z rotationalVelocity", &obj->vRotations.z, -10.0f, 10.0f);

                ImGui::NewLine();

                ImGui::SliderFloat("X scale", &obj->_scaleVector.x, 0.1f, 10.0f);
                ImGui::SliderFloat("Y scale", &obj->_scaleVector.y, 0.1f, 10.0f);
                ImGui::SliderFloat("Z scale", &obj->_scaleVector.z, 0.1f, 10.0f);
                ImGui::SliderFloat("Scale", &obj->_scale, 0.1f, 10.0f);

                if (ImGui::Button("Update scale"))
                {
                    obj->scale(obj->_scale);
                    obj->scale(obj->_scaleVector);
                }


                obj->rotate(obj->vRotations);
                // obj->setScale(obj->_scaleVector);
                // obj->setScale(obj->_scale);
                obj->setPosition(pos);
                
                ImGui::TreePop();
            }
            i++;
        }
        ImGui::TreePop();
    }
    ImGui::End();
}