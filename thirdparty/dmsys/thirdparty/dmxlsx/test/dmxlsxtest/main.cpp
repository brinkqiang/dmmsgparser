#include <iostream>
#include <iomanip>
#include <dmxlsx.h>

int main() {

    XLDocument doc;
    doc.CreateDocument("./github.xlsx");
    doc.Workbook().AddWorksheet("public");
    doc.Workbook().AddWorksheet("private");
    doc.Workbook().DeleteSheet("Sheet1");

    auto wkb = doc.Workbook().Worksheet("public");
    wkb.Cell("A1").Value() = 3.14159;
    wkb.Cell("B1").Value() = 42;
    wkb.Cell("C1").Value() = "Hello OpenXLSX!";
    wkb.Cell("D1").Value() = true;
    wkb.Cell("E1").Value() = wkb.Cell("C1").Value();

    auto A1 = wkb.Cell(1, 1).Value().Get<double>();
    auto B1 = wkb.Cell(1, 2).Value().Get<unsigned int>();
    auto C1 = wkb.Cell("C1").Value().Get<std::string>();
    auto D1 = wkb.Cell("D1").Value().Get<bool>();
    auto E1 = wkb.Cell("E1").Value().Get<std::string>();

    auto val = wkb.Cell("E1").Value();

    std::cout << val.Get<std::string>() << std::endl;

    std::cout << "Cell A1: " << A1 << std::endl;
    std::cout << "Cell B1: " << B1 << std::endl;
    std::cout << "Cell C1: " << C1 << std::endl;
    std::cout << "Cell D1: " << D1 << std::endl;
    std::cout << "Cell E1: " << E1 << std::endl;

    doc.SaveDocument();

    return 0;
}
