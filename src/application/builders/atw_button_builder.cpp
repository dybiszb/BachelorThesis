// author: dybisz

#include "builders/atw_button_builder.h"

const TwBar *CAtwButtonBuilder::defaultOwner = NULL;
const string CAtwButtonBuilder::defaultId = "";
const TwButtonCallback CAtwButtonBuilder::defaultCallback = NULL;
const void *CAtwButtonBuilder::defaultData = NULL;
const string CAtwButtonBuilder::defaultLabel = "__defaultLabel";

CAtwButtonBuilder::CAtwButtonBuilder() {
    _owner = (TwBar *) defaultOwner;
    _id = defaultId;
    _callback = defaultCallback;
    _data = (void *) defaultData;
    _label = defaultLabel;
}

void CAtwButtonBuilder::build() {
    string parameters = "label='" + _label + "'";
    TwAddButton(_owner, _id.c_str(), _callback, _data, parameters.c_str());
}

CAtwButtonBuilder &CAtwButtonBuilder::setOwner(const TwBar *owner) {
    _owner = (TwBar *) owner;
}

CAtwButtonBuilder &CAtwButtonBuilder::setId(const string name) {
    _id = name;
}

CAtwButtonBuilder &CAtwButtonBuilder::setCallback(TwButtonCallback callback) {
    _callback = callback;
}

CAtwButtonBuilder &CAtwButtonBuilder::setData(const void *data) {
    _data = (void *) data;
}

CAtwButtonBuilder &CAtwButtonBuilder::setLabel(const string label) {
    // If no id has been provided set label as the id
    if(!_id.size()) {
        _id = label;
    }

    _label = label;
    return *this;
}