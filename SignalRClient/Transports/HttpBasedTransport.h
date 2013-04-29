#ifndef HTTPBASEDTRANSPORT_H
#define HTTPBASEDTRANSPORT_H

#include "ClientTransport.h"
#include "Connection.h"
#include "Transports/HttpClient.h"
#include "Helper/TransportHelper.h"
#include "SignalException.h"
#include <QQueue>

class HttpBasedTransport : public ClientTransport
{

protected:
    HttpClient* mHttpClient;

public:
    HttpBasedTransport(HttpClient* httpClient);
    ~HttpBasedTransport(void);

    void negotiate(Connection* connection, NEGOTIATE_CALLBACK negotiateCallback, void* state = NULL);
    void send(Connection* connection, QString data);
    virtual void stop(Connection* connection);
    void abort(Connection* connection);

    virtual const QString& getTransportType() = 0;

    void tryDequeueNextWorkItem();
private:    
    
    struct SendQueueItem
    {
        Connection* connection;
        QString url;
        QMap<QString, QString> postData;
    };
    
    QQueue<SendQueueItem*> _sendQueue;
    bool _sending;
    static void onSendHttpResponse(const QString& httpResponse, SignalException* error, void* state);
};

#endif