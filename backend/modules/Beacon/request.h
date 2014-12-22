#ifndef BEACON_REQUEST_H
#define BEACON_REQUEST_H

#include <QObject>
#include <QNetworkReply>

#include "request-result.h"

class RequestPrivate;

namespace beacon {
  
class Request : public QObject
{
    Q_OBJECT

    Q_ENUMS(RequestStatus)

    Q_DECLARE_PRIVATE(Request)

public:
    enum RequestStatus
    {
      RequestSuccess,
      RequestFailed
    };

public:
    explicit Request(QObject *parent = 0);
    ~Request();

    Q_INVOKABLE void requestLatestBeacon();

Q_SIGNALS:
    void beaconRequestResult(
        RequestStatus status,
        RequestResult *result);

private Q_SLOTS:
  void onRequestFinished(QNetworkReply*);

private:
    QScopedPointer<RequestPrivate> d_ptr;
};

} // namespace beacon

#endif // BEACON_REQUEST_H

