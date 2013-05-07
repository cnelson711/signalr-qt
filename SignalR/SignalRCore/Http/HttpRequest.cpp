#include "HttpRequest.h"
#include <QStringList>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 2)
#include <QUrlQuery>
#endif

#define HTTP_HEADER_SEPERATOR "\r\n"
HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{

}

HttpRequest *HttpRequest::parse(QString data)
{
    //TODO: Parse Http Stream
    HttpRequest* req = new HttpRequest();

    QStringList lst = data.split(HTTP_HEADER_SEPERATOR);

    foreach(QString h, lst)
    {
        if(h.isEmpty())
            continue;

        if(h.startsWith("GET"))
        {
            req->setMethod("GET");
            req->setQuery(h.split(' ')[1]);
        }
        else if(h.startsWith("POST"))
        {
            req->setMethod("POST");
            req->setQuery(h.split(' ')[1]);
        }
        else
        {
            req->addHeader(h.split(':')[0], QString(h.split(':')[1]).simplified());
        }
    }

    return req;
}

void HttpRequest::setQuery(QString url)
{


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 2)
    QUrl urlq(url);
    QUrlQuery qurl(urlq.query());
#else
   QUrl qurl(url);
#endif

    for(int i = 0; i < qurl.queryItems().count(); i++)
    {
        addQuery(qurl.queryItems()[i].first, qurl.queryItems()[i].second);
    }

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 2)
    urlq.setQuery(qurl);
    setUrl(urlq);
#else
   setUrl(qurl);
#endif



}