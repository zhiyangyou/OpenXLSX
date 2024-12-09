#pragma once
#include "OpenXLSX-Exports.hpp"
#include <cstdint>
#include <memory>
#include <mio.hpp>
#include <string>
#include <string>
#include <unordered_map>
#include <vector>

#pragma pack(push, 1)
struct ZipLocalFileHeader
{
    uint32_t signature;             //
    uint16_t version_needed;        //
    uint16_t general_purpose;       //
    uint16_t compression;           //
    uint16_t last_mod_time;         //
    uint16_t last_mod_date;         //
    uint32_t crc32;                 // CRC-32
    uint32_t compressed_size;       //
    uint32_t uncompressed_size;     //
    uint16_t filename_length;       //
    uint16_t extra_field_length;    //
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ZipCentralDirectoryFileHeader
{
    uint32_t signature;                   //
    uint16_t version_made_by;             //
    uint16_t version_needed;              //
    uint16_t general_purpose;             //
    uint16_t compression;                 //
    uint16_t last_mod_time;               //
    uint16_t last_mod_date;               //
    uint32_t crc32;                       // CRC-32
    uint32_t compressed_size;             //
    uint32_t uncompressed_size;           //
    uint16_t filename_length;             //
    uint16_t extra_field_length;          //
    uint16_t file_comment_length;         //
    uint16_t disk_number_start;           //
    uint16_t internal_file_attributes;    //
    uint32_t external_file_attributes;    //
    uint32_t local_header_offset;         //
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ZipEndOfCentralDirectoryRecord
{
    uint32_t signature;                               //
    uint16_t disk_number;                             //
    uint16_t start_disk_number;                       //
    uint16_t number_of_records_on_this_disk;          //
    uint16_t total_number_of_records;                 //
    uint32_t size_of_central_directory;               //
    uint32_t offset_of_start_of_central_directory;    //
    uint16_t comment_length;                          //
};
#pragma pack(pop)

struct ZipEntry
{
    std::string name;
    uint32_t    compressed_size;
    uint32_t    uncompressed_size;
    uint32_t    local_header_offset;
    uint32_t    file_content_offset;
    ;
};
namespace OpenXLSX
{
    class OPENXLSX_EXPORT ZYZipArchive
    {
    public:
        ZYZipArchive();
        ~ZYZipArchive();
        ZYZipArchive(const ZYZipArchive& other)                       = default;
        ZYZipArchive(ZYZipArchive&& other)                            = default;
        ZYZipArchive&            operator=(const ZYZipArchive& other) = default;
        ZYZipArchive&            operator=(ZYZipArchive&& other)      = default;
        explicit                 operator bool() const;
        bool                     isValid() const;
        bool                     isOpen() const;
        void                     open(const std::string& fileName);
        void                     close();
        void                     save(const std::string& path = "");
        void                     addEntry(const std::string& name, const std::string& data);
        void                     deleteEntry(const std::string& entryName);
        std::string              getEntry(const std::string& name) const;
        const char*              getEntry(const std::string& name, unsigned int* u8Len) const;
        std::vector<std::string> getAllEntryNames() const;
        bool                     hasEntry(const std::string& entryName) const;
        size_t                   fileSize() const;

    private:
        std::string                                 _curPath;
        std::shared_ptr<mio::mmap_source>           _mmapSource;
        std::vector<ZipEntry>                       _vecEntries;
        mutable std::unordered_map<uint32_t, char*> _mapUnCompressData;
    };
}    // namespace OpenXLSX