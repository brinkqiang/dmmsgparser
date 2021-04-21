# dmxlsx

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmxlsx](https://img.shields.io/badge/brinkqiang-dmxlsx-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmxlsx)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmxlsx/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmxlsx.svg?label=Stars)](https://github.com/brinkqiang/dmxlsx) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmxlsx.svg?label=Fork)](https://github.com/brinkqiang/dmxlsx)

## Build status
| [Linux][lin-link] | [MacOSX][osx-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![osx-badge]       | ![win-badge]        |

[lin-badge]: https://travis-ci.org/brinkqiang/dmxlsx.svg?branch=master "Travis build status"
[lin-link]:  https://travis-ci.org/brinkqiang/dmxlsx "Travis build status"
[osx-badge]: https://travis-ci.org/brinkqiang/dmxlsx.svg?branch=master "Travis build status"
[osx-link]:  https://travis-ci.org/brinkqiang/dmxlsx "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/github/brinkqiang/dmxlsx?branch=master&svg=true "AppVeyor build status"
[win-link]:  https://ci.appveyor.com/project/brinkqiang/dmxlsx "AppVeyor build status"

## Intro
dmxlsx based on OpenXLSX
```cpp
#include <iostream>
#include <iomanip>
#include <dmxlsx.h>

using namespace std;

/*
 * TODO: Sheet iterator
 * TODO: Handling of named ranges
 * TODO: Column/Row iterators
 * TODO: correct copy/move operations for all classes
 * TODO: Find a way to handle overwriting of shared formulas.
 * TODO: Handling of Cell formatting
 * TODO: Handle chartsheets
 * TODO: Update formulas when changing Sheet Name.
 * TODO: Get vector for a Row or Column.
 * TODO: Conditional formatting
 */

int main() {

    XLDocument doc;
    doc.CreateDocument("./MyTest.xlsx");
    auto wks = doc.Workbook().Worksheet("Sheet1");

    wks.Cell("A1").Value() = 3.14159;
    wks.Cell("B1").Value() = 42;
    wks.Cell("C1").Value() = "Hello OpenXLSX!";
    wks.Cell("D1").Value() = true;
    wks.Cell("E1").Value() = wks.Cell("C1").Value();

    auto A1 = wks.Cell("A1").Value().Get<double>();
    auto B1 = wks.Cell("B1").Value().Get<unsigned int>();
    auto C1 = wks.Cell("C1").Value().Get<std::string>();
    auto D1 = wks.Cell("D1").Value().Get<bool>();
    auto E1 = wks.Cell("E1").Value().Get<std::string>();

    auto val = wks.Cell("E1").Value();
    cout << val.Get<std::string>() << endl;

    cout << "Cell A1: " << A1 << endl;
    cout << "Cell B1: " << B1 << endl;
    cout << "Cell C1: " << C1 << endl;
    cout << "Cell D1: " << D1 << endl;
    cout << "Cell E1: " << E1 << endl;

    doc.SaveDocument();

    return 0;
}

```
## Contacts
[![Join the chat](https://badges.gitter.im/brinkqiang/dmxlsx/Lobby.svg)](https://gitter.im/brinkqiang/dmxlsx)

## Thanks
