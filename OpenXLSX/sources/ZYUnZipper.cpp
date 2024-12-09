#include "ZYUnZipper.hpp"
#include <iostream>
#include <libdeflate.h>
#include <mio.hpp> 
#include <fstream>
//#include <mimalloc-new-delete.h>
#include <mimalloc.h>

static bool s_has_init_mimalloc_to_libdeflate = false;
void init_mimalloc_to_libdeflate()
{
	if (s_has_init_mimalloc_to_libdeflate) return;
	std::cout << "libdeflate_set_memory_allocator\n"
		<< mi_malloc << "\n"
		<< mi_free << "\n"
		;
	libdeflate_set_memory_allocator(mi_malloc, mi_free);
	s_has_init_mimalloc_to_libdeflate = true;
}

std::vector<ZipEntry> parse_zip2(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		throw std::runtime_error("open file failed");
	}

	std::vector<ZipEntry> entries;

	file.seekg(-22, std::ios::end);
	ZipEndOfCentralDirectoryRecord eocd;
	file.read(reinterpret_cast<char*>(&eocd), sizeof(eocd));
	if (eocd.signature != 0x06054b50) {
		throw std::runtime_error("unvalid zip file ");
	}

	file.seekg(eocd.offset_of_start_of_central_directory, std::ios::beg);
	for (uint16_t i = 0; i < eocd.total_number_of_records; ++i) {
		ZipCentralDirectoryFileHeader cdh;
		file.read(reinterpret_cast<char*>(&cdh), sizeof(cdh));
		if (cdh.signature != 0x02014b50) {
			throw std::runtime_error(" no ZipCentralDirectoryFileHeader data ");
		}

		std::string filename(cdh.filename_length, '\0');
		file.read(&filename[0], cdh.filename_length);

		entries.push_back({
			filename,
			cdh.compressed_size,
			cdh.uncompressed_size,
			cdh.local_header_offset
			});

		file.seekg(cdh.extra_field_length + cdh.file_comment_length, std::ios::cur);
	}

	return entries;
}

std::vector<ZipEntry> parse_zip(const char* fileData, size_t fileLen) {
	std::vector<ZipEntry> entries;

	const ZipEndOfCentralDirectoryRecord* eocd = reinterpret_cast<const ZipEndOfCentralDirectoryRecord*>(fileData + fileLen - sizeof(ZipEndOfCentralDirectoryRecord));
	if (eocd->signature != 0x06054b50) {
		std::cerr << "Invalid ZIP file: End of Central Directory Record not found." << std::endl;
		return entries;
	}

	const char* central_dir_start = fileData + eocd->offset_of_start_of_central_directory;
	for (uint16_t i = 0; i < eocd->total_number_of_records; ++i) {
		const ZipCentralDirectoryFileHeader* cdh = reinterpret_cast<const ZipCentralDirectoryFileHeader*>(central_dir_start);
		if (cdh->signature != 0x02014b50) {
			std::cerr << "Invalid ZIP file: Central Directory File Header not found." << std::endl;
			return entries;
		}

		const char* local_header_start = fileData + cdh->local_header_offset;
		const ZipLocalFileHeader* lfh = reinterpret_cast<const ZipLocalFileHeader*>(local_header_start);
		if (lfh->signature != 0x04034b50) {
			std::cerr << "Invalid ZIP file: Local File Header not found." << std::endl;
			return entries;
		}

		ZipEntry entry;
		entry.name = std::string(local_header_start + sizeof(ZipLocalFileHeader), lfh->filename_length);
		entry.compressed_size = cdh->compressed_size;
		entry.uncompressed_size = cdh->uncompressed_size;
		entry.local_header_offset = cdh->local_header_offset;
		entry.file_content_offset = cdh->local_header_offset + sizeof(ZipLocalFileHeader) + cdh->filename_length + cdh->extra_field_length;

		if (entry.uncompressed_size > 0) {
			entries.emplace_back(entry);
		}
		central_dir_start += sizeof(ZipCentralDirectoryFileHeader) + cdh->filename_length + cdh->extra_field_length + cdh->file_comment_length;
	}

	return entries;
}

bool unCompressDataUseLibDeflate(const  char* compressData, size_t dataLen, size_t unCompressDataLen, char* bugUnCompress) {


	// 
	struct libdeflate_decompressor* d = libdeflate_alloc_decompressor();
	if (d == nullptr) {
		std::cerr << "unCompressDataUseLibDeflate Failed to allocate libdeflate decompressor\n";
		return false;
	}

	// 
	size_t realUnCompressData = 0;
	libdeflate_result ret = libdeflate_deflate_decompress(d, compressData, dataLen, bugUnCompress, unCompressDataLen, &realUnCompressData);
	if (ret != LIBDEFLATE_SUCCESS) {
		std::cerr << "unCompressDataUseLibDeflate .Decompression failed ret:" << ret << "\n";
		libdeflate_free_decompressor(d);
		return false;
	}

	libdeflate_free_decompressor(d);
	bugUnCompress[unCompressDataLen] = '\0';
	return true;
}


ZYZipArchive::ZYZipArchive()
{
	_curPath = "none";
	_mmapSource = nullptr;

}

ZYZipArchive::operator bool() const
{
	return isValid();
}

bool ZYZipArchive::isValid() const
{
	return isOpen()
		//&& xx
		;
}

bool ZYZipArchive::isOpen() const
{
	return _mmapSource->is_open();
}

void ZYZipArchive::open(const std::string& fileName)
{
	init_mimalloc_to_libdeflate();
	_curPath = fileName;
	try {
		_mmapSource = std::make_shared<mio::mmap_source >(fileName);
		if (!_mmapSource->is_open()) {
			std::cerr << "ZYZipArchive::open Failed to open file: " << fileName << std::endl;
			return;
		}
		_vecEntries = parse_zip(_mmapSource->data(), _mmapSource->size());
		//std::cout << "entry Count " << _vecEntries.size() << "\n";
		//for (const auto& e : _vecEntries) {
		//	std::cout
		//		<< "Name:" << e.name << "\n"
		//		<< "local_header_offset:" << e.local_header_offset << "\n"
		//		<< "compressed_size:" << e.compressed_size << "\n"
		//		<< "uncompressed_size:" << e.uncompressed_size << "\n"
		//		<< "----------------" << "\n"
		//		;
		//}
	}
	catch (const std::system_error& e) {
		std::cerr << "Error opening file: " << e.what() << std::endl;
		return;
	}
}

void ZYZipArchive::close()
{ 
	for (const auto& kv : _mapUnCompressData) {
		mi_free(kv.second);
	}
	_mapUnCompressData.clear();
}

void ZYZipArchive::save(const std::string& path /*= ""*/) {
	throw std::exception("@youzy2:  ZYZipArchive::save not implement...");
}

void ZYZipArchive::addEntry(const std::string& name, const std::string& data) {
	throw std::exception("@youzy2:  ZYZipArchive::addEntry not implement...");
}

void ZYZipArchive::deleteEntry(const std::string& entryName)
{
	throw std::exception("@youzy2:  ZYZipArchive::deleteEntrynot not implement...");
}

std::string ZYZipArchive::getEntry(const std::string& name) const
{
	unsigned int len = 0;
	const char* uncompressData = getEntry(name, &len);
	if (uncompressData != nullptr) {
		return std::string(uncompressData);
	}
	else {
		return "";
	}

}

const char* ZYZipArchive::getEntry(const std::string& name, unsigned int* u8Len) const
{
	for (const auto& e : _vecEntries) {
		if (e.name == name) {
			//const uint32_t offset = e.local_header_offset;
			const uint32_t offset = e.file_content_offset;
			*u8Len = e.uncompressed_size;

			if (_mapUnCompressData.find(offset) !=_mapUnCompressData.end() ) {
				char* unCompressData = _mapUnCompressData.at(offset);
				return unCompressData;
			}
			else {
				char* unCompressDataBuffer = static_cast<char*>(mi_malloc(e.uncompressed_size + 1));
				_mapUnCompressData.emplace(offset, unCompressDataBuffer);
				const char* pCompressData = _mmapSource->data() + offset;
				bool success = unCompressDataUseLibDeflate(pCompressData, e.compressed_size, e.uncompressed_size, unCompressDataBuffer);
				if (!success)return nullptr;
				return unCompressDataBuffer;
			}
			break;
		}
	}

	std::cerr << " ZYZipArchive::getEntry entry not found" << name << "\n";
	*u8Len = 0;
	return nullptr;
}

std::vector<std::string>ZYZipArchive::getAllEntryNames()const
{
	std::vector<std::string> ret;
	for (const auto& e : _vecEntries) {
		ret.emplace_back(e.name);
	}
	return ret;
}

bool ZYZipArchive::hasEntry(const std::string& entryName) const
{
	for (const auto& e : _vecEntries) {
		if (e.name == entryName) {
			return true;
		}
	}
	return false;
}

size_t ZYZipArchive::fileSize() const
{
	if (!isOpen()) {
		return 0;
	}
	else {
		return _mmapSource->size();
	}
}

ZYZipArchive::~ZYZipArchive()
{
	close();
}
