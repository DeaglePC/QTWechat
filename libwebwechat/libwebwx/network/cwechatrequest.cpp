#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QThread>
#include <QXmlStreamReader>
#include <QRandomGenerator64>

#include "cwechatrequest.h"
#include "config.h"

CWechatRequest::CWechatRequest(QObject *parent) : QObject(parent)
{
    makeDeviceid();
    this->m_netManager = new QNetworkAccessManager(nullptr);
}

CWechatRequest::~CWechatRequest()
{
    if(m_netManager)
    {
        delete m_netManager;
        m_netManager = nullptr;
    }
}

bool CWechatRequest::makeUuid()
{
    QUrlQuery urlQuery;
    QUrl url(WechatRequestUrl::GET_UUID);
    QNetworkRequest request;

    urlQuery.addQueryItem("appid", WechatRequestValue::APP_ID);
    urlQuery.addQueryItem("fun", "new");
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);

    QNetworkReply *reply = this->m_netManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return false;
    }
    QString content = reply->readAll();
    reply->deleteLater();

    QRegularExpression re(R"(^window.QRLogin.code = (\d+); window.QRLogin.uuid = "(\S+?)\")");
    QRegularExpressionMatch match = re.match(QString(content));
    if(match.hasMatch())
    {
        if(match.captured(1) == "200")
        {
            this->m_sUuid = match.captured(2);
            qDebug() << "reply:" << content;
            qDebug() << "uuid:" << this->m_sUuid;
            return true;
        }
    }
    return false;
}

bool CWechatRequest::makeQrcode()
{
    if (!this->m_sUuid.isEmpty())
    {
        this->m_sQrcodeLink = WechatRequestUrl::GET_QRCODE + this->m_sUuid;
        return true;
    }
    return false;
}

QString CWechatRequest::getQrcode()
{
    return m_sQrcodeLink;
}

bool CWechatRequest::checkLogin()
{
    if(m_sUuid.isEmpty())
    {
        return false;
    }
    QUrlQuery urlQuery;
    QUrl url(WechatRequestUrl::CHECK_LOGIN);
    QNetworkRequest request;

    QDateTime time = QDateTime::currentDateTime();
    uint timeStamp = time.toTime_t();
    QString strTimeStamp = QString::number(timeStamp);

    urlQuery.addQueryItem("loginicon", "true");
    urlQuery.addQueryItem("uuid", m_sUuid);
    urlQuery.addQueryItem("tip", "1");
    urlQuery.addQueryItem("_", strTimeStamp);
    urlQuery.addQueryItem("r", QString::number(-int(timeStamp)/1579));
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);

    QNetworkReply *reply = this->m_netManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return false;
    }
    QString content = reply->readAll();
    reply->deleteLater();

    QRegularExpression re(R"(window.code=(\d+))");
    QRegularExpressionMatch match = re.match(content);

    if(match.hasMatch())
    {
        if(match.captured(1) == "200")
        {
            re.setPattern(R"(window.redirect_uri=\"(\S+)\";)");
            match = re.match(content);
            if (match.hasMatch())
            {
                this->m_sRedirectUri = match.captured(1);
                qDebug() << "re uri:" << this->m_sRedirectUri;
                return true;
            }
        }
    }
    return false;
}

bool CWechatRequest::goRedirectUri()
{
    if(m_sRedirectUri.isEmpty())
    {
        return false;
    }
    QUrl url(m_sRedirectUri);
    QNetworkRequest request;

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);

    QNetworkReply *reply = this->m_netManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return false;
    }
    QXmlStreamReader xml(reply);
    while(!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if(!xml.isStartElement())
        {
            continue;
        }
        if (xml.name() == "skey")
        {
            m_sSkey = xml.readElementText();
        }
        else if(xml.name() == "wxsid")
        {
            m_sWxsid = xml.readElementText();
        }
        else if(xml.name() == "wxuin")
        {
            m_sWxuin = xml.readElementText();
        }
        else if(xml.name() == "pass_ticket")
        {
            m_sPassTicket = xml.readElementText();
        }
    }
    reply->deleteLater();
    if(m_sSkey.isEmpty() || m_sWxsid.isEmpty() || m_sWxuin.isEmpty() || m_sPassTicket.isEmpty())
    {
        return false;
    }
    return true;
}

bool CWechatRequest::makePrefixUrl()
{
    if (m_sRedirectUri.isEmpty())
    {
        return false;
    }
    int index = m_sRedirectUri.lastIndexOf('/');
    if(index == -1)
    {
        return false;
    }
    m_sPrefixUrl = m_sRedirectUri.left(index + 1);
    qDebug() << m_sPrefixUrl;
    return true;
}

void CWechatRequest::makeDeviceid()
{
    quint64 value = QRandomGenerator64::global()->generate() % 899999999999999LL + 100000000000000LL;
    m_sDeviceid = QString("e").append(QString::number(value));
}

bool CWechatRequest::goWebinit()
{
    if (m_sPrefixUrl.isEmpty() || m_sWxuin.isEmpty() ||
            m_sWxsid.isEmpty() || m_sSkey.isEmpty() || m_sDeviceid.isEmpty())
    {
        return false;
    }
    QUrlQuery urlQuery;
    QUrl url(m_sPrefixUrl + WechatRequestValue::WEBWXINIT);
    QNetworkRequest request;

    QDateTime time = QDateTime::currentDateTime();
    uint timeStamp = time.toTime_t();
    urlQuery.addQueryItem("r", QString::number(-int(timeStamp)/1579));
    urlQuery.addQueryItem("pass_ticket", m_sPassTicket);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QJsonObject jsonData;
    m_jsonBaseRequest.insert("Uin", m_sWxuin);
    m_jsonBaseRequest.insert("Sid", m_sWxsid);
    m_jsonBaseRequest.insert("Skey", m_sSkey);
    m_jsonBaseRequest.insert("DeviceID", m_sDeviceid);
    jsonData.insert("BaseRequest", m_jsonBaseRequest);
    QByteArray postData = QJsonDocument(jsonData).toJson();
    qDebug() << "postdata:" << postData;

    QNetworkReply *reply = this->m_netManager->post(request, postData);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return false;
    }

    QByteArray content = reply->readAll();
    reply->deleteLater();
    m_jsonInitContent = QJsonDocument::fromJson(content);

    //qDebug() << "content:" << m_jsonCurrentContact;
    qDebug() << "msg:" << m_jsonInitContent["BaseResponse"]["Ret"];
    qDebug() << "msg:" << m_jsonInitContent["SyncKey"]["List"];
    qDebug() << "userself:" << m_jsonInitContent["User"].toObject().toVariantHash();
    // 用户本身的信息
    emit sglGetUserselfFinished(m_jsonInitContent["User"].toObject().toVariantHash());
    return true;
}

bool CWechatRequest::makeSyncKey()
{
    if (m_jsonInitContent.isEmpty())
    {
        return false;
    }
    QJsonArray arrySynckeyList = m_jsonInitContent["SyncKey"]["List"].toArray();
    m_sSyncKey = CWechatRequest::spliceSyncKey(arrySynckeyList);
    m_jsonSyncKey = m_jsonInitContent["SyncKey"].toObject();
    qDebug() << "makeSyncKey:" << m_jsonSyncKey;
    return true;
}

bool CWechatRequest::goStatusNotify()
{
    if (m_jsonInitContent.isEmpty())
    {
        return false;
    }
    QUrlQuery urlQuery;
    QUrl url(m_sPrefixUrl + WechatRequestValue::WEBWXSTATUSNOTIFY);
    QNetworkRequest request;

    urlQuery.addQueryItem("lang", "zh_CN");
    urlQuery.addQueryItem("pass_ticket", m_sPassTicket);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QJsonObject jsonData;
    jsonData.insert("BaseRequest", m_jsonBaseRequest);
    jsonData.insert("Code", 3);
    jsonData.insert("FromUserName", m_jsonInitContent["User"]["UserName"].toString());
    jsonData.insert("ToUserName", m_jsonInitContent["User"]["UserName"].toString());
    jsonData.insert("ClientMsgId", int(QDateTime::currentDateTime().toTime_t()));
    QByteArray postData = QJsonDocument(jsonData).toJson();
    //qDebug() << "+++post data :" << postData;

    QNetworkReply *reply = this->m_netManager->post(request, postData);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return false;
    }
    reply->deleteLater();
    return true;
}

void CWechatRequest::makeFileSyncUrl()
{
    for(auto i = WechatRequestValue::DETAIL_URL.begin();
        i != WechatRequestValue::DETAIL_URL.end(); ++i)
    {
        if(m_sRedirectUri.indexOf(i.key()) != -1)
        {
            m_sFileUrl = QString("https://%1/cgi-bin/mmwebwx-bin/").arg(i.value()[0]);
            m_sSyncUrl = QString("https://%1/cgi-bin/mmwebwx-bin/").arg(i.value()[1]);
            qDebug() << "fileurl:" << m_sFileUrl << "sync url:" << m_sSyncUrl;
            return;
        }
    }
    m_sFileUrl = m_sRedirectUri;
    m_sSyncUrl = m_sRedirectUri;
    qDebug() << "-fileurl:" << m_sFileUrl << "sync url:" << m_sSyncUrl;
}

int CWechatRequest::goSyncCheck()
{
    QUrlQuery urlQuery;
    QUrl url(m_sSyncUrl + WechatRequestValue::SYNC_CHECK);
    QNetworkRequest request;

    QString timeStamp = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
    urlQuery.addQueryItem("r", timeStamp);
    urlQuery.addQueryItem("skey", m_sSkey);
    urlQuery.addQueryItem("sid", m_sWxsid);
    urlQuery.addQueryItem("uin", m_sWxuin);
    urlQuery.addQueryItem("deviceid", m_sDeviceid);
    urlQuery.addQueryItem("synckey", m_sSyncKey);
    urlQuery.addQueryItem("_", timeStamp);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);

    QNetworkReply *reply = this->m_netManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return -1;
    }
    QString content = reply->readAll();
    reply->deleteLater();

    qDebug() << "goSyncCheck content" << content;

    QRegularExpression re(R"(window.synccheck={retcode:"(\d+)\",selector:"(\d+)\"})");
    QRegularExpressionMatch match = re.match(content);

    if(!match.hasMatch() || match.captured(1) != "0")
    {
        return -2;
    }
    return match.captured(2).toInt();
}

QByteArray CWechatRequest::getMsg()
{
    if (m_jsonSyncKey.isEmpty())
    {
        qDebug() << "m_jsonSyncKey empty!!!!!";
        return QByteArray();
    }
    QUrlQuery urlQuery;
    QUrl url(m_sPrefixUrl + WechatRequestValue::GET_MSG);
    QNetworkRequest request;

    urlQuery.addQueryItem("skey", m_sSkey);
    urlQuery.addQueryItem("sid", m_sWxsid);
    //urlQuery.addQueryItem("pass_ticket", m_sPassTicket);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QJsonObject jsonData;
    jsonData.insert("BaseRequest", m_jsonBaseRequest);
    jsonData.insert("SyncKey", m_jsonSyncKey);
    jsonData.insert("rr", ~int(QDateTime::currentDateTime().toTime_t()));
    QByteArray postData = QJsonDocument(jsonData).toJson();

    QNetworkReply *reply = this->m_netManager->post(request, postData);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return QByteArray();
    }
    QByteArray content = reply->readAll();
    reply->deleteLater();
    return content;
}

bool CWechatRequest::updateSyncKey(const QByteArray &content)
{
    if(content.isEmpty())
    {
        return false;
    }
    QJsonDocument jsonContent = QJsonDocument::fromJson(content);
    QJsonArray arrySynckeyList = jsonContent["SyncKey"]["List"].toArray();
    m_sSyncKey = CWechatRequest::spliceSyncKey(arrySynckeyList);
    m_jsonSyncKey = jsonContent["SyncKey"].toObject();
    qDebug() << "updateSyncKey:" << m_sSyncKey;
    return true;
}

QByteArray CWechatRequest::getContact()
{
    QUrlQuery urlQuery;
    QUrl url(m_sPrefixUrl + WechatRequestValue::GET_CONTACT);
    QNetworkRequest request;

    urlQuery.addQueryItem("r", QString::number(QDateTime::currentDateTime().toTime_t()));
    urlQuery.addQueryItem("skey", m_sSkey);
    urlQuery.addQueryItem("pass_ticket", m_sPassTicket);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QNetworkReply *reply = this->m_netManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->errorString();
        return QByteArray();
    }
    QByteArray content = reply->readAll();
    reply->deleteLater();
    return content;
}

void CWechatRequest::getHeadImage(const QString &urlHead)
{
    QUrl url(WechatRequestUrl::ICON_BASE_URL + urlHead);
    QNetworkRequest request;

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QNetworkReply *reply = this->m_netManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &CWechatRequest::sltGetHeadFinished);
}

void CWechatRequest::getHeadImageByUsername(const QString &userName)
{
    QString sUrl = userName.startsWith("@@") ? WechatRequestUrl::IMG_FULL_URL : WechatRequestUrl::ICON_FULL_URL;
    QUrlQuery urlQuery;
    QUrl url(sUrl);
    QNetworkRequest request;

    urlQuery.addQueryItem("seq", "0");
    urlQuery.addQueryItem("username", userName);
    urlQuery.addQueryItem("skey", m_sSkey);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);

    QNetworkReply *reply = this->m_netManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &CWechatRequest::sltGetHeadFinished);
}

void CWechatRequest::sendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId)
{
    QUrlQuery urlQuery;
    QUrl url(m_sPrefixUrl + WechatRequestValue::SEND_MSG);
    QNetworkRequest request;

    urlQuery.addQueryItem("pass_ticket", m_sPassTicket);
    url.setQuery(urlQuery);

    request.setUrl(url);
    request.setRawHeader("User-Agent", WechatRequestHeader::USER_AGENT);
    request.setRawHeader("ContentType", "application/json; charset=UTF-8");
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    QJsonObject jsonMsg;
    jsonMsg.insert("ClientMsgId", localId);
    jsonMsg.insert("LocalID", localId);
    jsonMsg.insert("Content", content);
    jsonMsg.insert("FromUserName", fromUser);
    jsonMsg.insert("ToUserName", toUser);
    jsonMsg.insert("Type", 1);

    QJsonObject jsonData;
    jsonData.insert("BaseRequest", m_jsonBaseRequest);
    jsonData.insert("Msg", jsonMsg);
    jsonData.insert("Scene", 0);
    QByteArray postData = QJsonDocument(jsonData).toJson();
    QNetworkReply *reply = this->m_netManager->post(request, postData);
    connect(reply, &QNetworkReply::finished, this, &CWechatRequest::sltSendMsgFinished);
}

QString CWechatRequest::spliceSyncKey(const QJsonArray &arrySynckeyList)
{
    QStringList keyList;
    for(QJsonArray::const_iterator it = arrySynckeyList.constBegin();
        it != arrySynckeyList.constEnd(); it++)
    {
        QVariantHash hashItem = (*it).toObject().toVariantHash();
        QString key = hashItem["Key"].toString();
        QString val = hashItem["Val"].toString();
        keyList << key + "_" + val;
    }
    return keyList.join('|');
}

void CWechatRequest::sltGetHeadFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray content = reply->readAll();
    QString url = reply->url().toString();

    // 拿出user_name
    QRegularExpression re(R"(username=(.+)&skey)");
    QRegularExpressionMatch match = re.match(url);
    if(match.hasMatch())
    {
        QString userName = match.captured(1);
        emit sglGetHeadFinished(userName, content);
    }

    reply->deleteLater();
}

void CWechatRequest::sltSendMsgFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray content = reply->readAll();
    emit sglSendMsgFinished(content);
    reply->deleteLater();
}
