//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <list>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class simple_request
{
public:
    simple_request(const string& uri);
    simple_request(const method&,const string& uri);
    
    void add_header(const string& key, const string& value);
        
public:
    boost::asio::streambuf request;
    std::ostream request_stream;(&request);
};

simple_request::simple_request(const string& uri):
    request(), request_stream(&request)
{
    request_stream << "GET " << uri << " HTTP/1.0\r\n"; 
}

simple_request::simple_request(const string& method, const string& uri):
    request(), request_stream(&request)
{
    request_stream << method <<" " << uri << " HTTP/1.0\r\n"; 
}

simple_request::add_header(const string& key, const string& value)
{
    request_stream << key <<": "  << valude << "\r\n";
}

class http_connect
{
public:
    http_connect();
    void connect(const *host, int port = 80);
    http_respone *send_request(const char *method, const char *url);
    void close();
private:
    tcp::socket sock_;
    boost::io_service&  io_service_;
};

http_connect::http_connect(boost::io_service& io_service)
    :io_service_(io_service), sock_(io_service)
{
}

void http_connect::http_connect(const char* method, const char* url){
    // Get a list of endpoints corresponding to the server name.
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], "http");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Try each endpoint until we successfully establish a connection.
    //tcp::socket socket(io_service);
    boost::asio::connect(sock_, endpoint_iterator);
}

http_response*  http_connect::send_request(simple_request& req){
    // Send the request.
    boost::asio::write(sock_, req.request);
   
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, "\r\n");

    http_response* resp = new http_response;
    // get that response 
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
      throw  "Invalid response";
    }
    resp.status_code_ = status_code;
    
     // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(socket, response, "\r\n\r\n");

    // Process the response headers.
    std::string header;
    while (std::getline(response_stream, header) && header != "\r"){
        resp.headers.push_back(header);    
    }
}

    
class http_response
{
    public:
        typedef std::list<std::string> header_list;
        simple_response();
        
        int     get_stauts() { return status_code_;}
        header_list&    get_header() {return headers_;}
        void    get_data(string& out){}
        enum {INVAILD_STATUS_CODE=0XFFFF;}
    private:
        unsigned int        status_code_;
        std::list<string>   headers_;
    friend class http_connect;
};

http_response(): 
    status_code(INVAILD_STATUS_CODE),
{
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cout << "Usage: sync_client <server> <path>\n";
            std::cout << "Example:\n";
            std::cout << "  sync_client www.boost.org /LICENSE_1_0.txt\n";
            return 1;
        }
        boost::io_service io_service;
        http_connect conn(io_service);
        conn.connect(argv[1]);

        simple_request req("HEAD",argv[2]);
        req.add_header("HOST", argv[1]);
        req.add_header("connection", "close");
        http_response * send_request(req);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;

}
