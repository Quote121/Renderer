// /////////////////
// //
// // This class is for holding all current game objects etc. that are loaded into the scene
// // It is responsible for holding the pointers to these objects as we dont want objects defined 
// // the stack in the main function as it makes them hard to access by other classes.
// // 
// // This class is temporary until the scope of the engine is more defined and will be a singlton
// // as currently there is no need for multiple scene classes.
// //
// //
// //  todo future - thread safe access
// //
// //
// ////////////////

// #include <vector>
// #include <memory>

// #include "object.hpp"


// class Scene
// {
// private:
//     std::vector<std::unique_ptr<Object>> scene_objects;

// protected:

//     Scene();
//     ~Scene()
//     {
//         delete(pinstance_);
//     }

//     static Scene* pinstance_;

// public:

//     Scene(Scene &other) = delete;
//     void operator=(const Scene &) = delete;
//     static Scene* getInstance();

//     void addObject(std::unique_ptr<Object> &obj);

//     // Returns true is found and removed
//     // false otherwise
//     bool removeObject(std::unique_ptr<Object> &obj);

//     std::vector<std::unique_ptr<Object>> getObjects()
//     {
//         return scene_objects;
//     }
// };