#include "cwebwxwork.h"
#include <QThread>
#include "cutils.h"
#include "config.h"

CWebwxWork::CWebwxWork(QObject* parent) : QObject(parent)
{
    initFlag();
}

CWebwxWork::~CWebwxWork()
{
    //delAll();
}

void CWebwxWork::sltMainLoop()
{
    initFlag();
    initAll();
    do
    {
        // 扫二维码
        if(!generateQrcode())
        {
            emit sglHintMsg(HTTP_BAD_REQUEST);
            break;
        }
        emit sglQrcodeOk(m_sQrcodeLink);

        // 检查扫了没
        quint16 nTryTime = 0;
        while (!checkLogin())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            qDebug() << "check login...";
            if(++nTryTime > MAX_CHECKOUT_LOGIN_TIME)
            {
                break;
            }
        }
        if(++nTryTime > MAX_CHECKOUT_LOGIN_TIME)
        {
            qDebug() << "refresh qrcode!!";
            continue;
        }
        qDebug() << "login success";
        emit sglHintMsg(LOGIN_SUCCESS);

        // 扫完开始初始化
        if(!initLogin())
        {
            emit sglHintMsg(HTTP_BAD_REQUEST);
            break;
        }
        qDebug() << "init success!";
        emit sglHintMsg(WX_INIT_SUCCESS);
        m_bIsLogin = true;

        // 获取通讯录
        if(!getContact())
        {
            emit sglHintMsg(WX_GET_ALL_CONTACT_FAILED);
            break;
        }
        qDebug() << "get contact success!";
        emit sglHintMsg(WX_GET_ALL_CONTACT_SUCCESS);

        // 进入主循环
        if (recvMsgLoop() == SYNC_FAILED)
        {
            emit sglHintMsg(SYNC_FAILED);
            break;
        }

    }while(!m_bEndMainThread);

    emit sglMainLoopFinished();
    delAll();
}

void CWebwxWork::sltGetHeadImg(const QString &url)
{
    if(!m_wechatRequest)
    {
        return;
    }
    m_wechatRequest->getHeadImage(url);
}

void CWebwxWork::sltGetHeadImgByUsername(const QString &userName)
{
    if(!m_wechatRequest)
    {
        return;
    }
    m_wechatRequest->getHeadImageByUsername(userName);
}

// 把原始数据存到本地，返回图片绝对路径+文件名
void CWebwxWork::sltGetHeadFinished(const QString &userName, const QByteArray &content)
{
    // 发出信号，头像图片本地文件名
    QString fileName = HEAD_LOCAL_PATH + userName + ".jfif";
    if (CUtils::saveHeadImg(content, fileName))
    {
        emit sglOneHeadOk(fileName);
    }
    else
    {
        qDebug() << "CUtils::saveHeadImg failed";
    }
}

void CWebwxWork::sltGetUserselfFinished(const QVariantHash &userselfData)
{
    emit sglGetUserselfFinished(userselfData);
}

void CWebwxWork::sltSendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId)
{
    if(!m_wechatRequest)
    {
        return;
    }
    // TODO  m_wechatRequest->sendMsg();
    m_wechatRequest->sendMsg(fromUser, toUser, content, localId);
}

/*void CWebwxWork::sltSendMsgFinished(const QString &retContent)
{

}*/

void CWebwxWork::initFlag()
{
    m_bIsLogin = false;
    m_bEndMainThread = false;
}

void CWebwxWork::initAll()
{
    m_wechatRequest = new CWechatRequest(nullptr);
    connect(m_wechatRequest, &CWechatRequest::sglGetHeadFinished, this, &CWebwxWork::sltGetHeadFinished);
    connect(m_wechatRequest, &CWechatRequest::sglGetUserselfFinished, this, &CWebwxWork::sltGetUserselfFinished);
    //connect(m_wechatRequest, &CWechatRequest::sglSendMsgFinished, this, &CWebwxWork::sltSendMsgFinished);
    connect(m_wechatRequest, &CWechatRequest::sglSendMsgFinished, this, &CWebwxWork::sglSendMsgFinished);

    // 保存头像图片的目录清理和创建
    CUtils::dealPath(HEAD_LOCAL_PATH);
}

bool CWebwxWork::generateQrcode()
{
    if(!m_wechatRequest->makeUuid())
    {
        return false;
    }
    if(!m_wechatRequest->makeQrcode())
    {
        return false;
    }
    m_sQrcodeLink = m_wechatRequest->getQrcode();
    return !m_sQrcodeLink.isEmpty();
}

bool CWebwxWork::checkLogin()
{
    return m_wechatRequest->checkLogin();
}

bool CWebwxWork::initLogin()
{
    if(!m_wechatRequest->goRedirectUri())
    {
        return false;
    }
    if(!m_wechatRequest->makePrefixUrl())
    {
        return false;
    }
    if(!m_wechatRequest->goWebinit())
    {
        return false;
    }
    if(!m_wechatRequest->makeSyncKey())
    {
        return false;
    }
    if(!m_wechatRequest->goStatusNotify())
    {
        return false;
    }
    m_wechatRequest->makeFileSyncUrl();
    return true;
}

bool CWebwxWork::getContact()
{
    QByteArray content = m_wechatRequest->getContact();
    if (content.isEmpty())
    {
        return false;
    }
    emit sglAllContactOk(content);
    return true;
}

int CWebwxWork::recvMsgLoop()
{
    int nTry = 0;
    while (nTry < MAX_SYNC_TRY)
    {
        int ret = m_wechatRequest->goSyncCheck();
        if (ret < 0)
        {
            nTry++;
            qDebug() << "sync check failed!";
        }
        else if (ret == 0)
        {
            nTry = 0;
            qDebug() << "ok:" << ret;
        }
        else
        {
            nTry = 0;
            qDebug() << "new msg!";
            QByteArray msg = m_wechatRequest->getMsg();
            m_wechatRequest->updateSyncKey(msg);
            emit sglNewMessage(msg);
        }
        QThread::msleep(50);
    }
    return SYNC_FAILED;
}

void CWebwxWork::delAll()
{
    if(m_wechatRequest)
    {
        delete m_wechatRequest;
        m_wechatRequest = nullptr;
    }
}
