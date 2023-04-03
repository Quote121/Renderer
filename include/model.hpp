#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

#include "mesh.hpp"

/*
    Model class holds a vector of mesh objects.

    This is the class where we directly pass the model file to import into our project

*/
class Model
{
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    // Helper funtion
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

public:
    Model(const std::string& path);
    
    void Draw(Shader &shader);
};


#endif // MODEL_H