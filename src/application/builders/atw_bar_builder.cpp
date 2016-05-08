// author: dybisz

#include "builders/atw_bar_builder.h"

const string CAtwBarBuilder::defaultLabel = "__defaultLabel";
const string CAtwBarBuilder::defaultColor = "255 0 0";
const string CAtwBarBuilder::defaultPosition = "0 0";
const string CAtwBarBuilder::defaultSize = "500 100";
const string CAtwBarBuilder::defaultContained = "false";
const string CAtwBarBuilder::defaultAlpha = "128";
const string CAtwBarBuilder::defaultFontsize = "2";

CAtwBarBuilder::CAtwBarBuilder() {
    _label = defaultLabel;
    _color = defaultColor;
    _position = defaultPosition;
    _size = defaultSize;
    _contained = defaultContained;
    _alpha = defaultAlpha;
    _fontsize = defaultFontsize;
}

TwBar *CAtwBarBuilder::build() {
    TwBar *bar = TwNewBar(_label.c_str());
    string parameters = _label +
                        " color='" + _color + "'" +
                        " position='" + _position + "'" +
                        " size='" + _size + "'" +
                        " contained=" + _contained +
                        " alpha='" + _alpha + "'" +
                        " fontsize=" + _fontsize;
    TwDefine(parameters.c_str());
    return bar;
}

CAtwBarBuilder &CAtwBarBuilder::setLabel(const string label) {
    _label = label;
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setColor(int red, int green, int blue) {
    _color = to_string(red) + " " + to_string(green) + " " + to_string(blue);
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setPosition(int x, int y) {
    _position = to_string(x) + " " + to_string(y);
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setSize(int width, int height) {
    _size = to_string(width) + " " + to_string(height);
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setContained(bool contained) {
    _contained = (contained) ? "true" : "false";
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setAlpha(int alpha) {
    _alpha = to_string(alpha);
    return *this;
}

CAtwBarBuilder &CAtwBarBuilder::setFontsize(int fontsize) {
    _fontsize = to_string(fontsize);
    return *this;
};