#ifndef LIBWEBWX_H
#define LIBWEBWX_H

#include <QQuickItem>
#include <QThread>
#include "cwebwxwork.h"
#include "cwebwxcontact.h"

class CLibWebwx : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(CLibWebwx)

public:
    CLibWebwx(QQuickItem *parent = nullptr);
    virtual ~CLibWebwx();

    Q_INVOKABLE void work();
    Q_INVOKABLE void getOneHead(const QString &headUrl);
    Q_INVOKABLE void getOneHeadByUsername(const QString &userName);
    Q_INVOKABLE void sendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId);

    QString qrcode();

public slots:
    void sltSetQrcodeLink(const QString &link);
    void sltHintMsg(int msg);
    void sltAllContactOk(QByteArray allContact);
    void sltOneHeadOk(const QString &headFileName);
    void sltNewMessage(QString newMsg);
    void sltGetUserselfFinished(const QVariantHash &userselfData);
    void sltSendMsgFinished(const QString &retContent);

    void sltMainLoopFinished();

signals:
    void sglQrcodeChanged();
    void sglQrcodeOk(const QString &link);
    void sglHintMsg(int msg_type, QString msg);
    void sglAllContactOk(QString allContact);
    void sglGetHeadImg(const QString &url);
    void sglGetHeadImgByUsername(const QString &userName);
    void sglOneHeadOk(const QString &headFileName);
    void sglNewMessage(QString newMsg);
    void sglGetUserselfFinished(const QString &strUserselfData);
    void sglSendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId);
    void sglSendMsgFinished(const QString &retContent);

    void sglGG();

private:
    CWebwxWork* m_wxWorker;
    QThread* m_tMainLoop;

    QString m_sQrcodeLink;
    UserArry m_arryContact;

    void init();
};

#endif // LIBWEBWX_H
