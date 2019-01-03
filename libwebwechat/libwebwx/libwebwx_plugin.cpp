#include "libwebwx_plugin.h"
#include "libwebwx.h"

#include <qqml.h>

void LibwebwxPlugin::registerTypes(const char *uri)
{
    // @uri cn.deaglepc.wx
    qmlRegisterType<CLibWebwx>(uri, 1, 0, "CLibWebwx");
}

