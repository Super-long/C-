#ifndef HTTPSTATUS_H_
#define HTTPSTATUS_H_

namespace ws{

    enum HttpStatusCode{
        HSCInit = 0,
        //2XX Successful
        HSCOK = 200,
        HSCNoContent = 204,
        HSCPartialContent = 206,
        //3XX Redirect
        HSCMovedPermanently = 301,
        HSCFound = 302,
        HSCSeeOther = 303,
        HSCNotModified = 304,
        HSCTemporaryRedirect = 307,
        //4XX Error in client
        HSCBadRequest = 400,
        HSCUnauthorized = 401,
        HSCForbidden = 403,
        HSCNotFound = 404,
        //5XX Error in Server
        HSCInternalServerError = 500,
        HSCServiceUnavailable = 503,
        kHCGatewayTimeout = 504,
        kHCHttpVersionNotSupported = 505
    };

    enum HttpRequest{
        HRGet = 0,
        HRHead,
        HRDELETE,
        HRPost,
        HRPut,
        HROptions,
        HRInit,
    };

    enum HttpFlag{
        Close = 0,
        Keep_Alive,
    };

    enum HttpParserStatus{

    };

    enum HttpParserFault{

    };

    struct HttpParser_Content{
        HttpRequest method;
        HttpParserStatus Status;
        HttpParserFault Fault;

        const char* Uri = nullptr; //请求方式
        const char* Header = nullptr;
        const char* Value = nullptr;

        int Uri_length = 0;
        int Header_length = 0;
        int Value_length = 0;

        int V_major = 0;
        int V_minor = 0;

        HttpFlag Set_Ka = Keep_Alive;
    };

    constexpr const char* StatusCode_to_String(int statuscode){
        HttpStatusCode para = static_cast<HttpStatusCode>(statuscode);
        switch(para)
        {
            case HSCOK:
                return "OK."; 
            case HSCNoContent:
                return "No Content.";
            case HSCPartialContent:
                return "Partial Content.";
            case HSCMovedPermanently:
                return "Moved Permanently.";
            case HSCFound:
                return "Found.";
            case HSCSeeOther:
                return "See Other.";
            case HSCNotModified:
                return "Not Modified.";
            case HSCTemporaryRedirect:
                return "Temporary Redirect.";
            case HSCBadRequest:
                return "Bad Request.";
            case HSCUnauthorized:
                return "Unauthorized.";
            case HSCForbidden:
                return "Forbidden.";
            case HSCNotFound:
                return "Not Found.";
            case HSCInternalServerError:
                return "Internal Server Error.";
            case HSCServiceUnavailable:
                return "Service Unavailable.";
            case kHCGatewayTimeout:
                return "Gateway Timeout.";
            case kHCHttpVersionNotSupported:
                return "Http Version Not Supported.";
            default:
                return "Parser error, Don't have this httpstatuscode.";
        }
    }
}

#endif