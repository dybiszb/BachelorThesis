// author: dybisz

#include "builders/atw_var_builder.h"
#include <iostream>
using namespace std;
const TwBar *CAtwVarBuilder::defaultOwner = NULL;
const string CAtwVarBuilder::defaultId = "";
const ETwType CAtwVarBuilder::defaultDataType = TW_TYPE_UNDEF;
const void *CAtwVarBuilder::defaultObservableData = NULL;
const string CAtwVarBuilder::defaultLabel = "__defaultLabel";
const string CAtwVarBuilder::defaultStep = "";
const string CAtwVarBuilder::defaultGroup = "";
const string CAtwVarBuilder::defaultReadOnly = "false";
const string CAtwVarBuilder::defaultOpened = "";
const string CAtwVarBuilder::defaultShowVal = "";

CAtwVarBuilder::CAtwVarBuilder() {
    _owner = (TwBar *) defaultOwner;
    _id = defaultId;
    _dataType = defaultDataType;
    _observableData = (void *) defaultObservableData;
    _label = defaultLabel;
    _step = defaultStep;
    _group = defaultGroup;
    _readOnly = defaultReadOnly;
    _opened = defaultOpened;
    _showVal = defaultShowVal;
}

void CAtwVarBuilder::build() {
    string parameters = "label='" + _label + "' ";

    if(_step.size() > 0) {
        parameters += " step=" + _step;
    }

    // Group specified
    if(_group.size() > 0) {
        parameters += " group=" + _group +"";
    }

    // Opened specified
    if(_opened.size() > 0) {
        parameters += " opened=true";
    }

    // ShowVal opened
    if(_showVal.size() > 0) {
        parameters += " shovval=" + _showVal;
    }

    parameters += " readonly=" + _readOnly;

    TwAddVarRW(_owner, _id.c_str(), _dataType, _observableData,
               parameters.c_str());
}

CAtwVarBuilder &CAtwVarBuilder::setOwner(const TwBar *owner) {
    _owner = (TwBar *) owner;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setId(const string id) {
    _id = id;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setDataType(const ETwType dataType) {
    _dataType = dataType;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setObservableData(void *observableData) {
    _observableData = observableData;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setLabel(const string label) {
    // If no id has been provided set label as the id
    if (!_id.size()) {
        _id = label;
    }

    _label = label;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setStep(const float step) {
    _step = to_string(step);
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setGroup(const string group) {
    _group = group;
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setReadOnly(const bool readOnly) {
    _readOnly = to_string(readOnly);
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setOpened(const bool opened){
    _opened = to_string(opened);
    return *this;
}

CAtwVarBuilder &CAtwVarBuilder::setShowVal(const bool showVal) {
    _showVal = to_string(showVal);
    return *this;
}