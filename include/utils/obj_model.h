//==============================================================================
// Simple loader for .obj file. One is asked just to provide path to the
// model file and class will handle rest. What is important though, the class
// is not able to load every existing .obj file. It will throw an error if
// there are more materials than one, assigned to a shape. Term 'shape' relates
// to the sub-mesh of the model.
//
// NOTE: Private methods, as an internal part of the class rather than public
//       interface, are not commented.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef OBJ_MESH_H
#define OBJ_MESH_H

#include <cstddef>
#include <vector>
#include <string>
#include <algorithm>
#include "glm/glm.hpp"
#include "texture_2D.h"
#include "tiny_obj_loader.h"
#include "vertex_array.h"
#include "buffer.h"
#include "glsl_shader.h"
#include "renderable_object.h"
#include <climits>

using namespace std;
using namespace tinyobj;
using namespace glm;

namespace rendering {
    class COBJModel : public CRenderableObject {
    public:
        virtual ~COBJModel();

        /**
         * @param directory Path to the directory where obj file is located.
         * @param objName   Name of the .obj file that one wants to load.
         * @param loadData  If true all material and shapes from specified
         *                  object will be loaded. Otherwise - not.
         */
        COBJModel(string directory, string objName, bool loadData = true);


        /**
         * Obj model along with its textures is render with usage of shipped
         * matrices.
         *
         * @param view       View matrix of the scene.
         * @param projection Projection matrix of the scene.
         */
        virtual void render(const float *view,
                            const float *projection);

        /**
         * Updates model matrix. If one wants to e.g. shit or scale a model
         * it can be done via this procedure.
         *
         * @param modelMatrix New model matrix entries for .obj model.
         */
        void setModelMatrix(mat4 modelMatrix);

        /**
         * Updates current direction of the light. Shader will automatically
         * load the vector and use it in shading process.
         *
         * @param directionalLight Vector with light direction to be set.
         */
        void setDirectionalLight(vec3 &directionalLight);

        /**
         * Updates camera position. Shader will automatically load the point
         * and use it in shading process.
         *
         * @param cameraPosition Vector current camera position.
         */
        void setCameraPosition(vec3 &cameraPosition);

    protected:
        string              _directory;
        string              _objName;

        vector<CTexture2D*> _textures;
        vector<shape_t>     _shapes;
        vector<material_t>  _materials;

        CBuffer*            _verticesBuffer;
        CBuffer*            _indicesBuffer;
        CBuffer*            _normalsBuffer;
        CBuffer*            _texCoordBuffer;

        mat4                _modelMatrix;
        vec3                _directionalLight;
        vec3                _cameraPosition;

        void _loadShapesAndMaterials();

        void _findMinMax();

        bool _moreThanOneMaterialPerShape(string &errorMessage);

        void _createTexturesFromImages();

        void _createBuffers();

        void _loadDataToBuffers();

        void _getBuffersSizes(int *verticesSize, int *indicesSize,
                              int *texCoordSize);

        void _initializeShaderProgram();

        void _loadData();
    };
}


#endif
