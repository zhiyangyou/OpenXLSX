#include <iostream>
#include <chrono>
#include <iomanip>

//#include <OpenXLSX/OpenXLSX.h>
#include "../src/OpenXLSX.h"


using namespace std;
using namespace OpenXLSX;

/*
 * TODO: Sheet iterator
 * TODO: Asyncronous loading/saving of files
 * TODO: streaming directly to/from .zip file
 * TODO: Handling of named ranges
 * TODO: Column/Row iterators
 * TODO: correct copy/move operations for all classes
 * TODO: Find a way to handle overwriting of shared formulas.
 * TODO: Handling of Cell formatting
 * TODO: Handle chartsheets
 * TODO: Update formulas when changing Sheet Name.
 * TODO: Get vector for a Row or Column.
 * TODO: Conditional formatting
 * TODO: Fix the ConstIterator (currently it's not const)
 * TODO: Import/Export of .csv files
 * TODO: revert to returning objects by pointer
 */

void simpleTest();
void openLarge();
void speedTest();
void writeTest();
void cloneTest();
void copyRangeTest();
void copyFromConst();
void printRange();

int main()
{
    simpleTest();
    //openLarge();
    //speedTest();
    //writeTest();
    //cloneTest();
    //copyRangeTest();
    //copyFromConst();
    //printRange();

    //wks->Row(3)->SetHeight(500);
    //wks->Row(1)->SetHidden(true);
    //wks->Column(2)->SetWidth(50);
    //wks->Column(3);
    //wks->Column(5)->SetHidden(true);
    //wks->Column(8)->SetWidth(100);

    //XLFont Font("Verdana", 20, XLColor(30, 90, 220), true);
    //doc.Styles()->AddFont(Font);

    return 0;
}

void simpleTest() {
    XLDocument doc;

    doc.CreateDocument("Spreadsheet.xlsx");
    doc.Workbook()->AddWorksheet("MyWorksheet");
    auto wks = doc.Workbook()->Worksheet("MyWorksheet");

    auto arange = wks->Range(XLCellReference(1,1), XLCellReference(10,10));
    for (auto &iter : arange) {
        iter.Value()->Set("Hello OpenXLSX!");
    }

    doc.SaveDocument();
    doc.CloseDocument();

    XLDocument rdoc;
    rdoc.OpenDocument("Spreadsheet.xlsx");

    cout << "Content of cell B2: " << rdoc.Workbook()->Worksheet("MyWorksheet")->Cell("B2")->Value()->AsString();

    rdoc.CloseDocument();


}

void openLarge() {/*
    OpenXLSX::XLDocument doc;
    doc.OpenDocument("../Large.xlsx");
    auto wks = doc.Workbook()->Worksheet("Sheet1");

    auto rows = wks->RowCount();

    for (int i = 1; i <= 1000; ++i) {
        cout << setw(8) << i << ": ";
        cout << setw(10) << wks->Cell(i, 1).Value().AsString() << " ";
        cout << setw(38) << wks->Cell(i, 2).Value().AsString() << " ";
        cout << setw(38) << wks->Cell(i, 3).Value().AsString() << " ";
        cout << setw(38) << wks->Cell(i, 4).Value().AsString() << " ";
        cout << setw(38) << wks->Cell(i, 5).Value().AsString() << endl;

    }*/
}

void speedTest() {
    unsigned long time = 0;
    int numIter = 10;

    for (int i = 1; i <= numIter; i++) {

        OpenXLSX::XLDocument doc;
        doc.CreateDocument("../SpeedTest.xlsx");

        auto wks = doc.Workbook()->Worksheet("Sheet1");
        wks->Cell(1000, 1000)->Value()->Set(1);

        auto start = chrono::steady_clock::now();

        auto arange = wks->Range();
        for (auto &iter : arange) {
            iter.Value()->Set("Hello OpenXLSX!");
        }

        auto end = chrono::steady_clock::now();

        time += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (i >= numIter) doc.SaveDocument();
        doc.CloseDocument();
        cout << "Run #" << i << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;

        //wks->Print();

    }

    time = time / numIter;
    cout << "Average time: " << time << " milliseconds" << endl;
    cout << "Average cells per second: " << 1000000.0/time*1000 << endl;

}

void writeTest() {/*
    OpenXLSX::XLDocument doc;
    doc.CreateDocument("../WriteTest.xlsx");

    auto wks = doc.Workbook()->Worksheet("Sheet1");
    wks->Cell(10, 10).Value().Set(1);

    auto arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set("RapidXL!");
    }

    doc.Workbook()->AddWorksheet("Sheet2");
    wks = doc.Workbook()->Worksheet("Sheet2");
    wks->Cell(10, 10).Value().Set(1);

    arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set(3.14159);
    }

    doc.Workbook()->AddWorksheet("Sheet3");
    wks = doc.Workbook()->Worksheet("Sheet3");
    wks->Cell(10, 10).Value().Set(1);

    arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set(XLBool::False);
    }

    doc.Workbook()->AddWorksheet("Sheet4");
    doc.Workbook()->DeleteSheet("Sheet1");

    doc.SaveDocument();
    doc.CloseDocument();
    */
}

void cloneTest() {/*
    OpenXLSX::XLDocument doc;
    doc.CreateDocument("../CloneTest.xlsx");

    auto wks = doc.Workbook()->Worksheet("Sheet1");
    wks->Cell(10, 10).Value().Set(1);

    auto arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set("RapidXL!");
    }

    doc.Workbook()->AddWorksheet("Sheet2");
    wks = doc.Workbook()->Worksheet("Sheet2");

    arange = wks->Range(XLCellReference("A1"), XLCellReference("J10"));
    for (auto &iter : arange) {
        iter.Value().Set(42);
    }

    doc.Workbook()->AddWorksheet("Sheet3");
    wks = doc.Workbook()->Worksheet("Sheet3");
    wks->Cell(10, 10).Value().Set(1);

    arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set(XLBool::False);
    }

    doc.Workbook()->AddWorksheet("Sheet4");

    doc.Workbook()->CloneWorksheet("Sheet1", "Sheet1_Clone");
    doc.Workbook()->CloneWorksheet("Sheet2", "Sheet2_Clone");
    doc.Workbook()->CloneWorksheet("Sheet3", "Sheet3_Clone");
    doc.Workbook()->CloneWorksheet("Sheet4", "Sheet4_Clone");

    doc.SaveDocument();
    doc.CloseDocument();
    */
}

void copyRangeTest() {/*
    OpenXLSX::XLDocument doc;
    doc.CreateDocument("../CopyRangeTest.xlsx");

    auto wks = doc.Workbook()->Worksheet("Sheet1");
    wks->Cell(10, 10).Value().Set(1);

    auto arange = wks->Range();
    for (auto &iter : arange) {
        iter.Value().Set("RapidXL!");
    }

    doc.Workbook()->AddWorksheet("Sheet2");
    doc.Workbook()->AddWorksheet("Sheet3");

    auto srange = wks->Range(XLCellReference("A1"), XLCellReference("E2"));
    doc.Workbook()->Worksheet("Sheet2").Cell("A1") = srange;

    srange.Transpose(true);
    doc.Workbook().Worksheet("Sheet3").Cell("A1") = srange;

    doc.SaveDocument();
    doc.CloseDocument();
    */
}

void copyFromConst() {/*
    const OpenXLSX::XLDocument cdoc("../WriteTest.xlsx");
    OpenXLSX::XLDocument doc;
    doc.CreateDocument("../CopyConstTest.xlsx");

    auto swks = &cdoc.Workbook().Worksheet("Sheet1");
    auto srange = swks->Range(XLCellReference("A1"), XLCellReference(1100, 1100));
    doc.Workbook().Worksheet("Sheet1").Cell("A1") = srange;

    doc.SaveDocument();
    doc.CloseDocument();
    cdoc.CloseDocument();
    */
}

void printRange() {/*
    OpenXLSX::XLDocument doc("../WriteTest.xlsx");
    auto wks = &doc.Workbook().Worksheet("Sheet2");
    auto rng = wks->Range(XLCellReference("A1"), XLCellReference(20, 10));

    for (auto &iter : rng) {
        cout << iter.Value().Float() << endl;
    }

    doc.CloseDocument();

    const OpenXLSX::XLDocument cdoc("../WriteTest.xlsx");
    auto cwks = &cdoc.Workbook().Worksheet("Sheet1");
    auto crng = cwks->Range(XLCellReference("A1"), XLCellReference(20, 10));


    for (auto &iter : crng) {
        cout << iter.Value().String() << endl;
        iter.Value().Set(1);
        cout << iter.Value().Float() << endl;
    }

    cdoc.CloseDocument();
    */
}