//==============================================================================
// To prevent introducing Google Test's framework syntax within main
// project's source code, classes called wrappers are presented in the
// following file. They provide access to protected/private methods in order
// to share them to the tests.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#include "obj_model.h"

#ifndef WRAPPERS_H
#define WRAPPERS_H

using namespace rendering;

class UnitTests_ObjModelWrapper : public COBJModel {
public:
    UnitTests_ObjModelWrapper(string directory, string name, bool loadData) :
            COBJModel(directory, name, loadData) {

    }
    ~UnitTests_ObjModelWrapper() {}
};

#endif
