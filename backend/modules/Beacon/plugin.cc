#include "plugin.h"

#include <QtQml>
#include <QtQml/QQmlContext>

#include "request.h"
#include "request-result.h"


void Plugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Beacon"));

    qmlRegisterType<beacon::Request>(uri, 1, 0, "NistBeaconRequest");
    qmlRegisterUncreatableType<beacon::RequestResult>(
        uri, 1, 0, "NistBeaconRequestResult", "NistBeaconRequestResult is only created as a result of a Request");
}

void Plugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}

