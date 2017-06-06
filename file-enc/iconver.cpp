
#include "iconver.hpp"

iconver:: iconver(const char * to_charset_name, const char * from_charset_name)
    : _errno(0)
{   
    _iconv_t = iconv_open(to_charset_name, from_charset_name);
    if( !is_vaild(_iconv_t) )
    {   
        _info.set_re_type(CONVERSION_NOT_SUPPORT);
    }
}
iconver::~iconver()
{   
    if( !is_vaild(_iconv_t) )
        iconv_close(_iconv_t);
}

iconv_re iconver::convert(buffer_t &in, buffer_t &out)
{   
    if( !is_vaild(_iconv_t) )
    {
       return _info; 
    }
    if( in.size() == 0 )      return  _info;
     
    const char * i_buf_ptr = &in[0];
    size_t       i_buf_len = in.size();

    out.reserve( i_buf_len * 4 );
    char *       o_buf_ptr = &out[0];
    size_t       o_buf_len = i_buf_len * 4;
    
    size_t res = iconv(_iconv_t, &i_buf_ptr, &i_buf_len, &o_buf_ptr, &o_buf_len);
    if( res == (size_t)(-1) )
    {
        switch( errno )
        {
            case E2BIG:
                //FIXME. need relloc the new memory?
                 _info.set_re_type(OUTPUT_BUFFER_FULL);
                 break;
            case EINVAL:
                 _info.set_re_type(INVALID_MULTIBYTE_SEQUENCE);
                 break;
            case EILSEQ:
                 _info.set_re_type(INCOMPLETE_MULTIBYTE_SEQUENCE);
                 break;
            default:
                 _info.set_re_type(UNKNOW_ERROR);
                 return ;
        }
    }
    return _info;
}
