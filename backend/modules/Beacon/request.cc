#include "request.h"

#include <QNetworkAccessManager>
#include <QUrl>


namespace
{

const char *const kLastRecordUrl =
    "https://beacon.nist.gov/rest/record/last";
const char *const kPreviousRecordUrlPrefix =
    "https://beacon.nist.gov/rest/record/previous/";

}

class RequestPrivate
{
public:
  RequestPrivate() : requestReply(0) {}
  QNetworkReply *requestReply;
  QScopedPointer<QNetworkAccessManager> networkManager;
};


using namespace beacon;

Request::Request(QObject *parent) :
  QObject(parent),
  d_ptr(new RequestPrivate())
{}

Request::~Request() {}

void Request::requestLatestBeacon()
{
  Q_D(Request);

  if (! d->networkManager)
    {
      d->networkManager.reset(
          new QNetworkAccessManager());
      QObject::connect(
          d->networkManager.data(),
          SIGNAL(finished(QNetworkReply*)),
          this,
          SLOT(onRequestFinished(QNetworkReply*)));
    }

  QNetworkRequest
    request = QNetworkRequest(QUrl(kLastRecordUrl));

  d->networkManager->get(request);
}

void Request::onRequestFinished(QNetworkReply *reply)
{
  Q_D(Request);
  if (Q_UNLIKELY(!reply))
    {
      qDebug() << "Invalid request received";
      Q_EMIT beaconRequestResult(RequestFailed, NULL);
      return;
    }
  if (reply->error() != QNetworkReply::NoError)
    {
      Q_EMIT beaconRequestResult(RequestFailed, NULL);
      return;
    }

  QByteArray bytes =
      reply->readAll();

  QString resultContent = QString::fromUtf8(bytes.data(), bytes.size());
  Q_EMIT beaconRequestResult(
      RequestSuccess,
      RequestResult::fromXmlContent(resultContent));
}

