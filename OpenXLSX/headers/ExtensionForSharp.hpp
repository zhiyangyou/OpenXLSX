#pragma once
#pragma pack(push, 4)
extern "C"
{
    typedef void (*OnReadSheetData)(size_t rowInfoCount, void* rowInfos, size_t cellTotalCount, void* CellsData);

    struct OpenXLSXCellData
    {
        int32_t ValueType;
        union
        {
            bool        boolV;
            double      floatV;
            int64_t     IntV;
            const void* PU8Str;
        } Value;
    };

    struct RowPosInfo
    {
        int BeginIndex;
        int RowCellCount;
    };
}

void init_mimalloc_to_pugi();
#pragma pack(pop)