#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

#define EFT_CODE_LEN 4

class EftposHelper {
  private:
    char eft_code[EFT_CODE_LEN+1];
    wchar_t eft_code_w[EFT_CODE_LEN+1];

  public:
    EftposHelper() {
        update_eft_code();
    }

    auto get_eft_code() {
        return eft_code;
    }

    void update_eft_code() {
        time_t t = time(NULL);
        struct tm *now = localtime(&t);
        // format time as DDMMYY
        char buf[6];
        strftime(buf, 6, "%d%m%y", now);
        // divide by 13
        auto time_int = atoi(buf);
        time_int /= 13;
        // zero-pad 4 chars long
        std::snprintf(eft_code, EFT_CODE_LEN+1, "%04d", time_int);
        std::swprintf(eft_code_w, EFT_CODE_LEN+1, L"%04d", time_int);
    }

    void print_eft_code() {
        std::printf("eft code: %s\n", eft_code);
    }
};
