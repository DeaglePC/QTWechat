#ifndef CWEBWXWORK_H
#define CWEBWXWORK_H

#include <QObject>
#include "network/cwechatrequest.h"

const quint16 MAX_CHECKOUT_LOGIN_TIME = 15;
const int MAX_SYNC_TRY = 5;

class CWebwxWork : public QObject
{
    Q_OBJECT
public:
    CWebwxWork(QObject* parent = nullptr);
    virtual ~CWebwxWork();

    // 各种提示类消息
    enum RET_MSG
    {
        LOGIN_SUCCESS = 10001,
        LOGIN_FAILED,
        HTTP_BAD_REQUEST = 20001,
        WX_INIT_SUCCESS = 30001,
        WX_GET_ALL_CONTACT_SUCCESS = 40001,
        WX_GET_ALL_CONTACT_FAILED,
        SYNC_FAILED = 50001
    };

public slots:
    void sltMainLoop();
    void sltGetHeadImg(const QString &url);
    void sltGetHeadImgByUsername(const QString &userName);
    void sltGetHeadFinished(const QString &userName, const QByteArray &content); // 图片原始数据
    void sltGetUserselfFinished(const QVariantHash &userselfData);  // 用户信息
signals:
    void sglQrcodeOk(const QString &qrcode);
    void sglHintMsg(int msg);
    void sglAllContactOk(QByteArray allContact);
    void sglOneHeadOk(const QString &headFileName);
    void sglNewMessage(QString newMsg);
    void sglGetUserselfFinished(const QVariantHash &userselfData);

    void sglMainLoopFinished();


private:
    bool m_bEndMainThread;
    bool m_bIsLogin;
    CWechatRequest* m_wechatRequest;

    QString m_sQrcodeLink;

    void initFlag();
    void initAll();
    bool generateQrcode();  // 生成登录的二维码
    bool checkLogin();      // 检查是否扫描了二维码
    bool initLogin();       // 登录后的一些初始化工作
    bool getContact();      // 获取全部通讯录
    int recvMsgLoop();      // 接收消息的主循环

    void delAll();
};

#endif // CWEBWXWORK_H
