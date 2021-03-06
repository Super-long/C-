#ifndef HTTPSTATUS_H_
#define HTTPSTATUS_H_

#include<iostream>

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

    enum HttpRequestMethod{
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
        HPSOK,
        HPSGAMEOVER,
        HPSGET,
        HPSPOST,
        HPSOPTION,
        HPSHEAD,
        HPSDELETE,
        HPSBetweenMU,
        HPSUriStart,
        HPSURIParser,
        HPSUriEnd,
        HPSVersionMajor,
        HPSVersionMinor,
        HPSVersionEnd,
        HPSLF,
        HPSCRLFCR,
        HPSHeader,
        HPSColon,
        HPSHeader_Value,
        HPSStore_Header,

    };

    enum HttpParserFault{
        HPFOK,
        HPFToLittleMessage,
        HPFInvaildMethod,
        HPFBetween_Method_URI_NoBlank, 
        HPFInvaildUri,
        HPFInvaildVersion,
        HPFNoSupportVersion,
        HPFInvaildHeader,
        HPFInvaildHeader_Value,
        HPFContentLength,
        HPFSetConnection,
        HPFContent,
        HPFCRLFCR,
        HPFContent_Nonatch_Length,
    };

    struct HttpParser_Content{
        HttpRequestMethod method = HRInit;
        HttpParserStatus Status = HPSOK;
        HttpParserFault Fault = HPFOK;

        const char* Uri = nullptr; //请求方式
        const char* Header = nullptr;
        const char* Value = nullptr;

        int Uri_length = 1;
        int Header_length = 1;
        int Value_length = 1;
        int Content_length = 0;

        int V_major = 0;
        int V_minor = 0;

        HttpFlag Set_Ka = Keep_Alive;
    };

    std::ostream& operator<<(std::ostream& os, const HttpParser_Content& para);

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
 inline bool isheader(char c) {
    return isalnum(c) || c == '-' || c == '_';
    }


    inline bool isuri(char c) {
    static bool isuri[] = {
    /*0   nul    soh    stx    etx    eot    enq    ack    bel     7*/
        false, false, false, false, false, false, false, false,
    /*8   bs     ht     nl     vt     np     cr     so     si     15*/
        false, false, false, false, false, false, false, false,
    /*16  dle    dc1    dc2    dc3    dc4    nak    syn    etb    23*/
        false, false, false, false, false, false, false, false,
    /*24  can    em     sub    esc    fs     gs     rs     us     31*/
        false, false, false, false, false, false, false, false,
    /*32  ' '    !      "      #     $     %     &     '          39*/
        false, false, false, true, true, true, true, false,
    /*40  (      )      *      +     ,     -     .     /          47*/
        false, false, false, true, true, true, true, true,
    /*48  0     1     2     3     4     5     6     7             55*/
        true, true, true, true, true, true, true, true,
    /*56  8     9     :     ;     <      =     >      ?           63*/
        true, true, true, true, false, true, false, true,
    /*64  @     A     B     C     D     E     F     G             71*/
        true, true, true, true, true, true, true, true,
    /*72  H     I     J     K     L     M     N     O             79*/
        true, true, true, true, true, true, true, true,
    /*80  P     Q     R     S     T     U     V     W             87*/
        true, true, true, true, true, true, true, true,
    /*88  X     Y     Z     [      \      ]      ^      _         95*/
        true, true, true, false, false, false, false, true,
    /*96  `      a     b     c     d     e     f     g           103*/
        false, true, true, true, true, true, true, true,
    /*104 h     i     j     k     l     m     n     o            113*/
        true, true, true, true, true, true, true, true,
    /*112 p     q     r     s     t     u     v     w            119*/
        true, true, true, true, true, true, true, true,
    /*120 x     y     z     {      |      }      ~      del      127*/
        true, true, true, false, false, false, false, false
    };

    return (c >= 0) ? isuri[c] : false;
    }

    inline bool isvalue(char c) {
    static bool isvalue[] = {
    /*0   nul    soh    stx    etx    eot    enq    ack    bel     7*/
        false, false, false, false, false, false, false, false,
    /*8   bs     ht     nl     vt     np     cr     so     si     15*/
        false, false, false, false, false, false, false, false,
    /*16  dle    dc1    dc2    dc3    dc4    nak    syn    etb    23*/
        false, false, false, false, false, false, false, false,
    /*24  can    em     sub    esc    fs     gs     rs     us     31*/
        false, false, false, false, false, false, false, false,
    /*32  ' '    !      "      #     $     %     &     '          39*/
        true, true, true, true, true, true, true, true,
    /*40  (      )      *      +     ,     -     .     /          47*/
        true, true, true, true, true, true, true, true,
    /*48  0     1     2     3     4     5     6     7             55*/
        true, true, true, true, true, true, true, true,
    /*56  8     9     :     ;     <      =     >      ?           63*/
        true, true, true, true, true, true, true, true,
    /*64  @     A     B     C     D     E     F     G             71*/
        true, true, true, true, true, true, true, true,
    /*72  H     I     J     K     L     M     N     O             79*/
        true, true, true, true, true, true, true, true,
    /*80  P     Q     R     S     T     U     V     W             87*/
        true, true, true, true, true, true, true, true,
    /*88  X     Y     Z     [      \      ]      ^      _         95*/
        true, true, true, true, true, true, true, true,
    /*96  `      a     b     c     d     e     f     g           103*/
        true, true, true, true, true, true, true, true,
    /*104 h     i     j     k     l     m     n     o            113*/
        true, true, true, true, true, true, true, true,
    /*112 p     q     r     s     t     u     v     w            119*/
        true, true, true, true, true, true, true, true,
    /*120 x     y     z     {      |      }      ~      del      127*/
        true, true, true, true, true, true, true, false
    };

    return (c >= 0) ? isvalue[c] : false;
    }
}



#endif