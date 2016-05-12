//==============================================================================
// Attempt to encapsulate Ant Tweak Bar library's calls in a way that the
// user won't bother with string-parametrize procedures.
// One should mind that the class will manage only to create object of type
// TwVar connected with particular bar. Because of that, the builder requires
// pointer to its owner.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef ATW_VAR_BUILDER_H
#define ATW_VAR_BUILDER_H

#include <AntTweakBar.h>
#include <string>

using namespace std;

class CAtwVarBuilder {
private:
    TwBar *_owner;
    string _id;
    ETwType _dataType;
    void *_observableData;
    string _label;
    string _step;
    string _group;
    string _readOnly;
    string _opened;
    string _showVal;

public:
    static const TwBar *defaultOwner;
    static const string defaultId;
    static const ETwType defaultDataType;
    static const void *defaultObservableData;
    static const string defaultLabel;
    static const string defaultStep;
    static const string defaultGroup;
    static const string defaultReadOnly;
    static const string defaultOpened;
    static const string defaultShowVal;

    CAtwVarBuilder();

    void build();

    CAtwVarBuilder &setOwner(const TwBar *owner);

    CAtwVarBuilder &setId(const string id);

    CAtwVarBuilder &setDataType(const ETwType dataType);

    CAtwVarBuilder &setObservableData(void *observableData);

    CAtwVarBuilder &setLabel(const string label);

    CAtwVarBuilder &setStep(const float step);

    CAtwVarBuilder &setGroup(const string group);

    CAtwVarBuilder &setReadOnly(const bool readOnly);

    CAtwVarBuilder &setOpened(const bool opened);

    CAtwVarBuilder &setShowVal(const bool showVal);

};


#endif
