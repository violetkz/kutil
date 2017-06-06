
#ifndef ICONVER_HPP___
#define ICONVER_HPP___

#include "iconv.h"
#include <vector>


static typedef enum {
    CONVERSION_SUCCESS,                            
    CONVERSION_NOT_SUPPORT,
    OUTPUT_BUFFER_FULL,
    INVALID_MULTIBYTE_SEQUENCE,
    INCOMPLETE_MULTIBYTE_SEQUENCE,
    UNKNOW_ERROR
}CONV_RE_CODE;

static char * CONV_INFO[] = {
  "conversion success",
  "The  conversion from fromcode to tocode is not supported by the implementation.",
  "There is not sufficient room at *outbuf", 
  "An invalid multibyte sequence has been encountered in the input",
  "An incomplete multibyte sequence has been encountered in the input"
};
    

class iconv_re
{   
private:
    CONV_RE_CODE    __re;
public:
    iconver_re(CONV_RE_CODE re=0): __re(re) {}
    void set_re_type(CONV_RE_CODE re)       { __re = re; }
    bool is_ok()
    {
        return __re == CONV_RE_CODE.SUCCESS ? true:false;
    }
    std::string get_info()
    {   
        return  CONV_INFO[__re];
    }
};

class iconver
{   
public:
    iconver(char * form_charset_name, char * to_charset_name);
    iconv_re convert(buffer_t &in, buffer_t &out);
    iconv_re convert(const char * in, size_t in_len, buttfer_t &out);
    ~iconver();

    typedef  std::vector<char>  buffer_t;
private:
    inline bool is_vaild(iconv_t c) {
        return  c != (iconv_t)(-1) ? true : false;
    }
private:
    iconv_t         _iconv_t;           // conversion descriptor
    iconv_re        _info;          
};

#endif
