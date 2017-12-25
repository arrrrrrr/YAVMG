#ifndef IPDATABASE_H
#define IPDATABASE_H

#include <windows.h>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdlib>

#define DB_READONLY 0
#define DB_READWRITE 1
#define DB_CREATE 2

typedef struct storedata {
    int brand;
    int store;
    std::string str;
} storedata_t;

class IPResult {
    bool status;
    storedata_t data;
    std::vector<std::string> address;

  public:
    IPResult(int storeid);
    bool get_status();
    std::vector<std::string> get_address_list();
    int get_num_address();
    
    storedata_t extract_data_from_storeid(int storeid);
    int extract_brand(std::string &sstr);
    int extract_store(std::string &sstr);
};

class IPDatabase {
    std::string db_file;
    // handle to a shared mutex
    HANDLE dbMutex;

  public:
    IPDatabase(std::string db);
    ~IPDatabase();
    sqlite3 *open_database(int flags);
    void close_database(sqlite3 *db);
};

#endif
