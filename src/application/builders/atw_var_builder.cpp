// author: dybisz

#include "builders/atw_var_builder.h"

const TwBar *CAtwVarBuilder::defaultOwner = NULL;
const string CAtwVarBuilder::defaultId = "";
const ETwType CAtwVarBuilder::defaultDataType = TW_TYPE_UNDEF;
const void *CAtwVarBuilder::defaultObservableData = NULL;
const string CAtwVarBuilder::defaultLabel = "__defaultLabel";
const string CAtwVarBuilder::defaultStep = "0.1";

CAtwVarBuilder::CAtwVarBuilder() {
    _owner = (TwBar *) defaultOwner;
    _id = defaultId;
    _dataType = defaultDataType;
    _observableData = (void *) defaultObservableData;
    _label = defaultLabel;
    _step = defaultStep;
}

void CAtwVarBuilder::build() {
    string parameters = "label='" + _label + "' ";
    switch(_dataType) {
        case TW_TYPE_BOOL32:
            break;
        // All types besides boolean has step parameter
        default:
            parameters += "step=" + _step;
    }


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