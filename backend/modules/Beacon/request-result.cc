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

#include "request-result.h"

#include <QDomDocument>
#include <QDebug>

using namespace beacon;

class RequestResultPrivate
{
public:
  RequestResultPrivate(
        const QString& ver,
        int f,
        const QString& tp,
        const QString& seed,
        const QString& pv,
        const QString& sig,
        const QString& out,
        int s)
    : version(ver),
      frequency(f),
      seed(seed),
      previousValue(pv),
      signature(sig),
      output(out),
      status(s)
  {
    timestamp = tp.toInt();
  }

  QString version;
  int frequency;
  int timestamp;
  QString seed;
  QString previousValue;
  QString signature;
  QString output;
  int status;
};


//static
RequestResult* RequestResult::fromXmlContent(
    const QString& content)
{
  QDomDocument document("beacon");
  if (! document.setContent(content.toUtf8()))
    {
      return NULL;
    }

  QDomElement docelement =
      document.documentElement();

  QString version;
  QString frequency;
  QString timestamp;
  QString seed;
  QString previousValue;
  QString signature;
  QString output;
  QString status;

  QDomNode n = docelement.firstChild();
  while (!n.isNull())
    {
      QDomElement e = n.toElement();
      if (!e.isNull())
        {
          if (e.tagName() == "version")
            {
              version = e.text();
            }
          else if (e.tagName() == "frequency")
            {
              frequency = e.text().toInt();
            }
          else if (e.tagName() == "timeStamp")
            {
              timestamp = e.text();
            }
          else if (e.tagName() == "seedValue")
            {
              seed = e.text();
            }
          else if (e.tagName() == "previousOutputValue")
            {
              previousValue = e.text();
            }
          else if (e.tagName() == "signatureValue")
            {
              signature = e.text();
            }
          else if (e.tagName() == "outputValue")
            {
              output = e.text();
            }
          else if (e.tagName() == "statusCode")
            {
              status = e.text().toInt();
            }
        }
      n = n.nextSibling();
    }

  return new RequestResult(
          version,
          frequency.toInt(),
          timestamp,
          seed,
          previousValue,
          signature,
          output,
          status.toInt()
      );
}


RequestResult::RequestResult(
    const QString& version,
    int frequency,
    const QString& timestamp,
    const QString& seed,
    const QString& previousValue,
    const QString& signature,
    const QString& output,
    int status,
    QObject *parent)
      : d_ptr(
          new RequestResultPrivate(
              version,
              frequency,
              timestamp,
              seed,
              previousValue,
              signature,
              output,
              status)) {}

RequestResult::~RequestResult() {}

QString RequestResult::version() const
{
  Q_D(const RequestResult);
  return d->version;
}

int RequestResult::frequency() const
{
  Q_D(const RequestResult);
  return d->frequency;
}

int RequestResult::timestamp() const
{
  Q_D(const RequestResult);
  return d->timestamp;
}

QString RequestResult::seed() const
{
  Q_D(const RequestResult);
  return d->seed;
}

QString RequestResult::previousValue() const
{
  Q_D(const RequestResult);
  return d->previousValue;
}

QString RequestResult::signature() const
{
  Q_D(const RequestResult);
  return d->signature;
}

QString RequestResult::output() const
{
  Q_D(const RequestResult);
  return d->output;
}

int RequestResult::status() const
{
  Q_D(const RequestResult);
  return d->status;
}


