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

#ifndef BEACON_REQUEST_RESULT_H
#define BEACON_REQUEST_RESULT_H

#include <QObject>
#include <QString>

class RequestResultPrivate;

namespace beacon {

class RequestResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString version READ version)
    Q_PROPERTY(int frequency READ frequency)
    Q_PROPERTY(int timestamp READ timestamp)
    Q_PROPERTY(QString seed READ seed)
    Q_PROPERTY(QString previousValue READ previousValue)
    Q_PROPERTY(QString signature READ signature)
    Q_PROPERTY(QString output READ output)
    Q_PROPERTY(int status READ status)

    Q_DECLARE_PRIVATE(RequestResult)

public:
    explicit RequestResult(
        const QString& version,
        int frequency,
        const QString& timestamp,
        const QString& seed,
        const QString& previousValue,
        const QString& signature,
        const QString& output,
        int status,
        QObject *parent = 0);
    ~RequestResult();

    static RequestResult* fromXmlContent(const QString& content);

    QString version() const;
    int frequency() const;
    int timestamp() const;
    QString seed() const;
    QString previousValue() const;
    QString signature() const;
    QString output() const;
    int status() const;
    
private:
    QScopedPointer<RequestResultPrivate> d_ptr;
};

} // namespace beacon

#endif // BEACON_REQUEST_RESULT_H
