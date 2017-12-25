#include "ipdatabase.h"

IPResult::IPResult(int storeid) {
    // quick validity check, must be at most 4 digits
    if (storeid >= 10000) {
        status = false;
        return;
    }

    data = extract_data_from_storeid(storeid);
    status = true;
}

bool IPResult::get_status() {
    return status;
}

// convert the store id to a struct containing the data
storedata_t IPResult::extract_data_from_storeid(int storeid) {
    char buf[5];
    // zeropad the storeid if necessary
    std::snprintf(buf, 5, "%04d", storeid);

    storedata_t sd = {0};
    sd.str = buf;
    sd.brand = extract_brand(sd.str);
    sd.store = extract_store(sd.str);

    return sd;
}

int IPResult::extract_brand(std::string &str) {
    int bid = atoi(str.substr(0,1).c_str());
    return bid;
}

int IPResult::extract_store(std::string &str) {
    int sid = atoi(str.substr(1,3).c_str());
    return sid;
}

IPDatabase::IPDatabase(std::string db) {

}

IPDatabase::~IPDatabase() {

}

sqlite3 *IPDatabase::open_database(int flags) {
    sqlite3 *pdb = nullptr;
    int db_flags = 0;

    // how to open the database
    switch (flags) {
        case DB_READONLY:
            db_flags = SQLITE_OPEN_READONLY;
            break;
        case DB_READWRITE:
            db_flags = SQLITE_OPEN_READWRITE;
            break;
        case DB_CREATE:
            db_flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
            break;
    }

    auto ret = sqlite3_open_v2(db_file.c_str(), &pdb, db_flags, nullptr);

    if (ret == SQLITE_OK)
        return pdb;

    printf("Failed to open database. Error Code: %d, Message: %s\n", ret, sqlite3_errmsg(pdb));

    return nullptr;
}

