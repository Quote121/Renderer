// #include "scene.hpp"


// Scene* Scene::pinstance_ = nullptr;

// Scene* Scene::getInstance()
// {
//     if (pinstance_ == nullptr)
//     {
//         pinstance_ = new Scene();
//     }
//     return pinstance_; 
// }

// void Scene::addObject(std::unique_ptr<Object> &obj)
// {
//     scene_objects.push_back(obj);
// }

// bool Scene::removeObject(std::unique_ptr<Object> &obj)
// {
//     auto result = std::find(scene_objects.begin(), scene_objects.end(), obj);
//     if (result == std::end(scene_objects))
//     {
//         // Not found
//         return false;
//     }
//     // Found
//     scene_objects.erase(result);
// }

