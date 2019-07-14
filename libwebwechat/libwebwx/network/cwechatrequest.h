#ifndef CWECHATREQUEST_H
#define CWECHATREQUEST_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager> //链接网络
#include <QtNetwork/QNetworkReply> //处理接收数据
#include <QtNetwork/QNetworkRequest> //处理请求数据
#include <QNetworkCookie> //单个cookie
#include <QNetworkCookieJar> //储存cookie
#include <QString>
#include <QQuickImageProvider>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class CWechatRequest : public QObject
{
    Q_OBJECT
public:
    explicit CWechatRequest(QObject *parent = nullptr);
    virtual ~CWechatRequest();

    bool makeUuid();
    bool makeQrcode();
    QString getQrcode();

    bool checkLogin();
    bool goRedirectUri();
    bool makePrefixUrl();
    void makeDeviceid();
    bool goWebinit();
    bool makeSyncKey();
    bool goStatusNotify();
    void makeFileSyncUrl();
    int goSyncCheck();
    QByteArray getMsg();
    bool updateSyncKey(const QByteArray&);
    QByteArray getContact();
    void getHeadImage(const QString&);
    void getHeadImageByUsername(const QString&);
    void sendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId);

    static QString spliceSyncKey(const QJsonArray&);


protected:
    QString m_sUuid;
    QString m_sQrcodeLink;
    QString m_sRedirectUri;
    QString m_sPrefixUrl;
    QJsonObject m_jsonBaseRequest;
    QJsonDocument m_jsonInitContent;

    QString m_sSkey;
    QString m_sWxsid;
    QString m_sWxuin;
    QString m_sPassTicket;
    QString m_sDeviceid;
    QString m_sSyncKey;
    QJsonObject m_jsonSyncKey;

    QString m_sFileUrl;
    QString m_sSyncUrl;

public slots:
    void sltGetHeadFinished();
    void sltSendMsgFinished();

signals:
    void sglGetHeadFinished(QString userName, QByteArray headImgData);
    void sglGetUserselfFinished(const QVariantHash &userselfData);
    void sglSendMsgFinished(const QString &retContent);


private:
    QNetworkAccessManager* m_netManager;

};

#endif // CWECHATREQUEST_H
