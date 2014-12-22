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
