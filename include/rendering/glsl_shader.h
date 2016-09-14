/**
 * Taken from OpenGL Development Cookbook by Muhammad Mobeen Movania.
 * Github: https://github.com/mmmovania/opengl33_dev_cookbook_2013.git
 *
 * NOTE: Class presented 'as is' (e.g. no comments added) to preserve the
 *       original form.
 */

#ifndef GLSL_SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <map>
#include <string>
#include "error_handling.h"

using namespace std;
using namespace utils;

class GLSLShader
{
public:
    GLSLShader(void);
    ~GLSLShader(void);
    void LoadFromString(GLenum whichShader, const string& source);
    void LoadFromFile(GLenum whichShader, const string& filename);
    void CreateAndLinkProgram();
    void Use();
    void UnUse();
    void AddAttribute(const string& attribute);
    void AddUniform(const string& uniform);

    //An indexer that returns the location of the attribute/uniform
    GLuint operator[](const string& attribute);
    GLuint operator()(const string& uniform);
    void DeleteShaderProgram();

private:
    enum ShaderType {VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER};
    GLuint	_program;
    int _totalShaders;
    GLuint _shaders[3];//0->vertexshader, 1->fragmentshader, 2->geometryshader
    map<string,GLuint> _attributeList;
    map<string,GLuint> _uniformLocationList;
};
#endif
