#include "cutils.h"
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFile>
#include <QDataStream>

CUtils::CUtils()
{
}

bool CUtils::saveHeadImg(const QByteArray &data, const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    for (int i = 0; i < data.size(); ++i) {
        out << static_cast<qint8>(data[i]);
    }
    return file.exists(fileName);
}

bool CUtils::dealPath(const QString &path)
{
    if(path.isEmpty())
    {
        return false;
    }
    QDir dir(path);
    if (!dir.exists())
    {
        qDebug() << path;
        if(!dir.mkpath(path))
        {
            qDebug() << "make " << path << "fail";
            return false;
        }
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        //qDebug() << fi.fileName();
    }
    return true;
}
