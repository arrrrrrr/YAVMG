#include "utility.h"

uint64_t FileUtils::filetime_to_uint64(FILETIME *ft) {
    uint64_t ut = 0;

    ut = (uint64_t)ft->dwLowDateTime;
    ut |= ((uint64_t)ft->dwHighDateTime << 32);

    return ut;
}

std::vector<std::string> StrUtils::split(std::string &str, const char *delim) {
    std::vector<std::string> tokens;
    char *token = NULL, *next_token = NULL;
    char *buf = new char[str.length() + 1];

    // copy the string to a temp buffer
    strncpy(buf, str.c_str(), str.length()+1);

    token = strtok_s(buf, delim, &next_token);

    while (token) {
        tokens.push_back(token);
        token = strtok_s(nullptr, delim, &next_token);
    }

    delete[] buf;
    return tokens;
}

std::string StrUtils::join(std::vector<std::string> &tokens, const char *delim) {
    // account for tokens-1 delimeters
    int length = (tokens.size() - 1) * strlen(delim);

    for (std::string s : tokens)
        length += s.length();

    char *buf = new char[length + 1], *pbuf = buf;

    // copy the first string
    strncpy(pbuf, tokens[0].c_str(), tokens[0].length());
    pbuf += tokens[0].length();

    for (int i = 1; i < tokens.size(); i++) {
        // append the delimiter
        strncpy(pbuf, delim, strlen(delim));
        pbuf += strlen(delim);
        // append the next string
        int curlen = tokens[i].length();
        strncpy(pbuf, tokens[i].c_str(), curlen);
        pbuf += curlen;
    }

    // apparently this is important!
    buf[length] = '\0';
    // convert the buffer to a string
    std::string str(buf);
    delete[] buf;

    return str;
}
