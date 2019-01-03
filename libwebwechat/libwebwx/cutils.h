#ifndef CUTILS_H
#define CUTILS_H

#include <QString>


class CUtils
{
public:
    CUtils();

    static bool saveHeadImg(const QByteArray &data, const QString &fileName);
    static bool dealPath(const QString &path);
};

#endif // CUTILS_H
