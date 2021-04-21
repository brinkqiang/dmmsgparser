#include <iostream>
#include <chrono>
#include <iomanip>
#include <dmxlsx.h>

int main() {

    XLDocument doc;
    doc.OpenDocument("./github.xlsx");
    auto wkb = doc.Workbook();

    std::cout << std::endl;

    for (auto iter = 1; iter <= wkb.SheetCount(); ++iter)
    {
        std::cout << iter << ": " << wkb.Sheet(iter).Name() << std::endl;        
    }

    doc.SaveDocument();

    return 0;
}
