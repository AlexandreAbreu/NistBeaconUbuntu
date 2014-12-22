/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Alexandre Abreu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

