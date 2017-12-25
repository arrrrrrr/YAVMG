#ifndef INTERNALDATA_H
#define INTERNALDATA_H

#include <string>
#include <list>
#include <cstdint>

typedef struct ipdatafile_hdr {
    int numentry;
} ipdatafile_hdr_t;

typedef struct ipdatafile_entry {
    char filename[1024];
    uint64_t lastmodified;
} ipdatafile_entry_t;

class IPDataFiles {
	static const std::string storefile;
    int num_files;
    static const std::string ipdatafile_store;
    std::list<ipdatafile_entry_t> ipfiles;

  public:
    IPDataFiles(int num);
    ~IPDataFiles();

    void read_datafile();
    void write_datafile();
    void add_file(std::string filename);
    void update_file(std::string filename, uint64_t lastmodified);
    bool is_file_updated(std::string filename, uint64_t lastmodified);
};

const std::string IPDataFiles::storefile = "ipdata.bin";

#endif

