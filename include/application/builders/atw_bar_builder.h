//==============================================================================
// Attempt to encapsulate Ant Tweak Bar library's calls in a way that the
// user won't bother with string-parametrize procedures. The class will
// produce a bar, which can be later on filled with other UI elements.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef ATW_BAR_BUILDER_H
#define ATW_BAR_BUILDER_H

#include <AntTweakBar.h>
#include <string>

using namespace std;

class CAtwBarBuilder {
private:
    string _label;
    string _color;
    string _position;
    string _size;
    string _contained;
    string _alpha;
    string _fontsize;

public:
    static const string defaultLabel;
    static const string defaultColor;
    static const string defaultPosition;
    static const string defaultSize;
    static const string defaultContained;
    static const string defaultAlpha;
    static const string defaultFontsize;

    CAtwBarBuilder();

    TwBar *build();

    CAtwBarBuilder& setLabel(const string label);

    CAtwBarBuilder& setColor(int red, int green, int blue);

    CAtwBarBuilder& setPosition(int x, int y);

    CAtwBarBuilder& setSize(int width, int height);

    CAtwBarBuilder& setContained(bool contained);

    CAtwBarBuilder& setAlpha(int alpha);

    CAtwBarBuilder& setFontsize(int fontsize);
};

#endif
