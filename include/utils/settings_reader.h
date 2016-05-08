//==============================================================================
// Set of functions designated to read the settings from a particular source.
// Currently only .ini files are supported.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef SETTINGS_READER_H
#define SETTINGS_READER_H

#include <iostream>
#include <string>
#include "settings_struct.h"
#include "INIReader.h"

using namespace std;

namespace utils {
    Settings readFromINI(string pathToINI);
}


#endif
