#include <OpenXLSX.hpp>
#include <Windows.h>
#include <ZYUnZipper.hpp>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;
using namespace OpenXLSX;
namespace fs = std::filesystem;

#define curTime std::chrono::high_resolution_clock::now()
#define deltaTime(a, b) std::chrono::duration_cast<std::chrono::milliseconds>((b) - (a))
#define needDebugPrintExcel true

void printWorkbook(const XLWorkbook& wb)
{
    cout << "\nSheets in workbook:\n";
    for (const auto& name : wb.worksheetNames()) cout << wb.indexOfSheet(name) << " : " << name << "\n";
}
void list_xlsx_files(const std::string& folder_path)
{
    // 检查输入的路径是否有效
    if (!fs::exists(folder_path)) {
        std::cerr << "指定的文件夹路径不存在: " << folder_path << std::endl;
        return;
    }

    if (!fs::is_directory(folder_path)) {
        std::cerr << "指定的路径不是一个文件夹: " << folder_path << std::endl;
        return;
    }

    // 遍历文件夹中的所有文件
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            std::string file_name = entry.path().filename().string();
            // 检查文件扩展名是否为.xlsx
            if (file_name.size() >= 5 && file_name.substr(file_name.size() - 5) == ".xlsx") {
                std::string path = entry.path().string();
                XLDocument  doc((char*)entry.path().u8string().c_str(), ZYZipArchive());
                doc.suppressWarnings();

                auto sheetCount = doc.workbook().sheetCount();
                for (size_t i = 1; i <= sheetCount; i++) {
                    auto wks = doc.workbook().worksheet(i);
                    wks.iterateAllCells([](size_t rowInfoCount, void* rowInfos, size_t cellTotalCount, void* CellsData) {
                        // if (needPrintInfo) {
                        //     std::cout
                        //         << "rowInfoCount " << rowInfoCount << "\n"
                        //         << "rowInfos " << rowInfos << "\n"
                        //         << "cellTotalCount " << cellTotalCount << "\n"
                        //         << "CellsData " << CellsData << "\n";
                        // }
                    });
                }
            }
        }
    }
}
int main()
{
    auto t1       = curTime;
    int  forCount = 10;
    for (int i = 0; i < forCount; ++i) {
        list_xlsx_files("F:\\temp\\testAllExcels");
    }
    auto t2       = curTime;
    auto costTime = deltaTime(t1, t2).count()/(double)forCount;
    std::cout << "read all excel cost " << costTime << "ms";
    return 0;
}
