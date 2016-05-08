//==============================================================================
// Attempt to encapsulate Ant Tweak Bar library's calls in a way that the
// user won't bother with string-parametrize procedures.
// One should mind that the class will manage only to create a single button
// connected with particular bar. Because of that, the builder requires
// pointer to its owner.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef ATW_BUTTON_BUILDER_H
#define ATW_BUTTON_BUILDER_H

#include <AntTweakBar.h>
#include <string>

using namespace std;

class CAtwButtonBuilder {
private:
    TwBar *          _owner;
    string           _id;
    TwButtonCallback _callback;
    void *           _data;
    string           _label;
public:
    static const TwBar *defaultOwner;
    static const string defaultId;
    static const TwButtonCallback defaultCallback;
    static const void *defaultData;
    static const string defaultLabel;

    void build();

    CAtwButtonBuilder();
    CAtwButtonBuilder& setOwner(const TwBar* owner);
    CAtwButtonBuilder& setId(const string id);
    CAtwButtonBuilder& setCallback(TwButtonCallback callback);
    CAtwButtonBuilder& setData(const void * data);
    CAtwButtonBuilder& setLabel(const string label);
};


#endif
