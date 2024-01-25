#include <OpenXLSX.hpp>
#include <Windows.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace OpenXLSX;
#define curTime std::chrono::high_resolution_clock::now()
#define deltaTime(a, b) std::chrono::duration_cast<std::chrono::milliseconds>((b) - (a))
#define needDebugPrintExcel false

void printWorkbook(const XLWorkbook& wb)
{
    cout << "\nSheets in workbook:\n";
    for (const auto& name : wb.worksheetNames()) cout << wb.indexOfSheet(name) << " : " << name << "\n";
}

void test8000XLSX2()
{
    std::cout << " sizeof(OpenXLSXCellData)" << sizeof(OpenXLSXCellData) << "\n"
              << "RowPosInfo" << sizeof(RowPosInfo) << "\n";

    auto       t1 = curTime;
    XLDocument doc;
    doc.open("G:\\temp\\test1.xlsx");
    auto wks = doc.workbook().worksheet("testSheet");
    wks.iterateAllCells([](size_t rowInfoCount, void* rowInfos, size_t cellTotalCount, void* CellsData) {
        
    });
    auto t2 = curTime;
    auto costTime = deltaTime(t1, t2).count();
    std::cout << "read full excel cost " << costTime << "ms";
}
void test8000XLSX()
{
    std::cout << " sizeof(OpenXLSXCellData)" << sizeof(OpenXLSXCellData) << "\n" 
              << "RowPosInfo" << sizeof(RowPosInfo) << "\n";

    auto       t1 = curTime;
    XLDocument doc;
    doc.open("G:\\temp\\test1.xlsx");
    auto        wks = doc.workbook().worksheet("testSheet");
    std::string sb;
    auto        countAll = 0;
    auto        maxRow   = wks.lastCell().row();
    auto        maxCol   = wks.lastCell().column();

    auto     strCount = 0;
    uint64_t result   = 0;

#if false
     std::vector<std::string> values;
     for (auto& row : wks.rows()) {
         values = std::vector<std::string>(row.values());
         result += std::count_if(values.begin(), values.end(), [&strCount, &sb](const std::string& v) {
             strCount++;
             sb += v;
             return !v.empty();
         });
     }
#else
    std::vector<OpenXLSXCellData> vecCellDatas;
    std::vector<RowPosInfo>       vecRowPosInfos;
    std::vector<std::string>      vecStrs; 
    int                           rowCount  = 0;
    int                           rowLen    = 0;
    int                           cellTotal = 0;
    for (auto& row : wks.rows()) {
        const std::vector<XLCellValue> cells(row.values());
        int                            beginIndex = cellTotal;
        for (const XLCellValue& cell : cells) {
            vecCellDatas.push_back({0});
            auto& cellData     = vecCellDatas.back();
            auto  type         = cell.type();
            cellData.ValueType = (int32_t)type;
            switch (type) {
                case XLValueType::Empty:
#    if needDebugPrintExcel
                    sb += ("empty");
                    sb += ("|");
#    endif
                    break;
                case XLValueType::Error:
#    if needDebugPrintExcel
                    sb += ("Error");
                    sb += ("|");
#    endif
                    break;
                case XLValueType::Boolean:
#    if needDebugPrintExcel
                    sb += "bool";
                    sb += ("|");
#    endif
                    cellData.Value.boolV = cell.get<bool>();
                    break;
                case XLValueType::Integer:
#    if needDebugPrintExcel
                    sb += std::to_string(cell.get<int64_t>());
                    sb += ("|");
#    endif
                    cellData.Value.IntV = cell.get<int64_t>();
                    break;
                case XLValueType::Float:
#    if needDebugPrintExcel
                    sb += std::to_string(cell.get<double>());
                    sb += ("|");
#    endif
                    cellData.Value.floatV = cell.get<double>();
                    break;
                case XLValueType::String:
#    if needDebugPrintExcel
                    sb += (cell.get<string>());
                    sb += ("|");
#    endif
                    vecStrs.push_back(std::move(cell.get<string>()));
                    cellData.Value.PU8Str = static_cast<const void*>(vecStrs.back().c_str());
                    break;
                default:
                    break;
            }
            rowLen++;
            cellTotal++;
        }
        sb += '\n';
        vecRowPosInfos.push_back({ beginIndex, rowLen });
        rowCount++;
        rowLen = 0;
    }
#endif

    // for (uint32_t row = 1; row < maxRow; row++) {
    //     auto cellCount = maxCol;
    //     auto count     = cellCount > 12 ? 12 : cellCount;
    //     for (unsigned short col = 1; col <= count; col++) {
    //         //auto cell = wks.cell(XLCellReference(row, col)).value() = 1;
    //
    //         //auto cell = wks.cell(row, col);
    //          switch (wks.cell(row, col).value().type()) {
    //             case XLValueType::Empty:
    //                 sb += ("empty");
    //                 sb += ("|");
    //                 countAll += 1;
    //                 break;
    //             case XLValueType::Boolean:
    //                 sb +=  "bool";
    //                 sb += ("|");
    //                 countAll += 2;
    //                 break;
    //             case XLValueType::Integer:
    //                 sb += std::to_string(wks.cell(1, 2).value().get<int64_t>());
    //                 sb += ("|");
    //                 countAll += 3;
    //                 break;
    //             case XLValueType::Float:
    //                 sb += wks.cell(1, 2).value().get<double>();
    //                 sb += ("|");
    //                 countAll += 4;
    //                 break;
    //             case XLValueType::Error:
    //                 sb += ("Error");
    //                 sb += ("|");
    //                 countAll += 5;
    //                 break;
    //             case XLValueType::String:
    //                 sb += (wks.cell(1, 2).value().get<string>());
    //                 sb += ("|");
    //                 countAll += 6;
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }
    //    sb += "\n";
    //}
    doc.close();
    auto t2       = curTime;
    auto costTime = deltaTime(t1, t2).count();
    std::cout << ("excel content\n") << countAll << "\n"
#if needDebugPrintExcel
              << "content\n"

              << sb << "\n"
#endif
              << "maxRow " << maxRow << "\n"
        //<< "values.size " << rowValues.size() << "\n"
        ;
    std::cout << "read full excel cost " << costTime << "ms";
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);

    //test8000XLSX();
    test8000XLSX2();
    // cout << "********************************************************************************\n";
    // cout << "DEMO PROGRAM #03: Sheet Handling\n";
    // cout << "********************************************************************************\n";

    //// OpenXLSX can be used to create and delete sheets in a workbook, as well as re-ordering of sheets.
    //// This example illustrates how this can be done. Please note that at the moment, chartsheets can only
    //// be renamed and deleted, not created or manipulated.

    //// First, create a new document and store the workbook object in a variable. Print the sheet names.
    // XLDocument doc;
    // doc.create("./Demo03.xlsx");
    // auto wbk = doc.workbook();
    // printWorkbook(wbk);

    //// Add two new worksheets. The 'addWorksheet' method takes the name of the new sheet as an argument,
    //// and appends the new workdheet at the end.
    //// Only worksheets can be added; there is no 'addChartsheet' method.
    // wbk.addWorksheet("Sheet2");
    // wbk.addWorksheet("Sheet3");
    // printWorkbook(wbk);

    // cout << "Sheet1 active: "  << (wbk.worksheet("Sheet1").isActive() ? "true" : "false") << endl;
    // cout << "Sheet2 active: "  << (wbk.worksheet("Sheet2").isActive() ? "true" : "false") << endl;
    // cout << "Sheet3 active: "  << (wbk.worksheet("Sheet3").isActive() ? "true" : "false") << endl;

    // wbk.worksheet("Sheet3").setActive();

    // cout << "Sheet1 active: "  << (wbk.worksheet("Sheet1").isActive() ? "true" : "false") << endl;
    // cout << "Sheet2 active: "  << (wbk.worksheet("Sheet2").isActive() ? "true" : "false") << endl;
    // cout << "Sheet3 active: "  << (wbk.worksheet("Sheet3").isActive() ? "true" : "false") << endl;

    //// OpenXLSX provides three different classes to handle workbook sheets: XLSheet, XLWorksheet, and
    //// XLChartsheet. As you might have guessed, XLWorksheet and XLChartsheet represents worksheets
    //// and chartsheets, respectively. XLChartsheet only has a limited set of functionality.
    //// XLSheet, on the other hand, is basically a std::variant that can hold either an XLWorksheet,
    //// or an XLChartsheet object. XLSheet has a limited set of functions that are common to
    //// both XLWorksheet and XLChartsheet objects, such as 'clone()' or 'setIndex()'. XLSheet is
    //// not a parent class to either XLWorksheet or XLChartsheet, and therefore cannot be used
    //// polymorphically.

    //// From an XLSheet object you can retrieve the contained XLWorksheet or XLChartsheet object by
    //// using the 'get<>()' function:
    // auto s1 = wbk.sheet("Sheet2").get<XLWorksheet>();

    //// Alternatively, you can retrieve the contained object, by using implicit conversion:
    // XLWorksheet s2 = wbk.sheet("Sheet2");

    //// Existing sheets can be cloned by calling the 'clone' method on the individual sheet,
    //// or by calling the 'cloneSheet' method from the XLWorkbook object. If the latter is
    //// chosen, both the name of the sheet to be cloned, as well as the name of the new
    //// sheet must be provided.
    //// In principle, chartsheets can also be cloned, but the results may not be as expected.
    // wbk.sheet("Sheet1").clone("Sheet4");
    // wbk.cloneSheet("Sheet2", "Sheet5");
    // printWorkbook(wbk);

    //// The sheets in the workbook can be reordered by calling the 'setIndex' method on the
    //// individual sheets (or worksheets/chartsheets).
    // wbk.deleteSheet("Sheet1");
    // wbk.worksheet("Sheet5").setIndex(1);
    // wbk.worksheet("Sheet4").setIndex(2);
    // wbk.worksheet("Sheet3").setIndex(3);
    // wbk.worksheet("Sheet2").setIndex(4);
    // printWorkbook(wbk);

    //// The color of each sheet tab can be set using the 'setColor' method for a
    //// sheet, and passing an XLColor object as an argument.
    // wbk.sheet("Sheet2").setColor(XLColor(0, 0, 0));
    // wbk.sheet("Sheet3").setColor(XLColor(255, 0, 0));
    // wbk.sheet("Sheet4").setColor(XLColor(0, 255, 0));
    // wbk.sheet("Sheet5").setColor(XLColor(0, 0, 255));

    // doc.save();

    return 0;
}
