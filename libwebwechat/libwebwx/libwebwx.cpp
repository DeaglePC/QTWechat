#include "libwebwx.h"
#include "config.h"

CLibWebwx::CLibWebwx(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

CLibWebwx::~CLibWebwx()
{
}

void CLibWebwx::init()
{
    m_wxWorker = new CWebwxWork(nullptr);
    connect(m_wxWorker, &CWebwxWork::sglQrcodeOk, this, &CLibWebwx::sltSetQrcodeLink);
    connect(m_wxWorker, &CWebwxWork::sglHintMsg, this, &CLibWebwx::sltHintMsg);
    connect(m_wxWorker, &CWebwxWork::sglAllContactOk, this, &CLibWebwx::sltAllContactOk);
    connect(m_wxWorker, &CWebwxWork::sglNewMessage, this, &CLibWebwx::sltNewMessage);
    connect(m_wxWorker, &CWebwxWork::sglOneHeadOk, this, &CLibWebwx::sltOneHeadOk);
    connect(this, &CLibWebwx::sglGetHeadImg, m_wxWorker, &CWebwxWork::sltGetHeadImg);
    connect(this, &CLibWebwx::sglGetHeadImgByUsername, m_wxWorker, &CWebwxWork::sltGetHeadImgByUsername);
    connect(m_wxWorker, &CWebwxWork::sglGetUserselfFinished, this, &CLibWebwx::sltGetUserselfFinished);
    connect(this, &CLibWebwx::sglSendMsg, m_wxWorker, &CWebwxWork::sltSendMsg);
    // 不做处理，直接发出信号
    connect(m_wxWorker, &CWebwxWork::sglSendMsgFinished, this, &CLibWebwx::sglSendMsgFinished);
}

void CLibWebwx::getOneHead(const QString &headUrl)
{
    if (!m_wxWorker)
    {
        return;
    }
    // 改成直接发信号，不是调用函数
    emit sglGetHeadImg(headUrl);
}

void CLibWebwx::getOneHeadByUsername(const QString &userName)
{
    if (!m_wxWorker)
    {
        return;
    }
    emit sglGetHeadImgByUsername(userName);
}

void CLibWebwx::sendMsg(const QString &fromUser, const QString &toUser, const QString &content, const QString &localId)
{
    if (!m_wxWorker)
    {
        return;
    }
    emit sglSendMsg(fromUser, toUser, content, localId);
}

void CLibWebwx::work()
{
    init();
    m_tMainLoop = new QThread(nullptr);
    m_wxWorker->moveToThread(m_tMainLoop);
    connect(m_tMainLoop, &QThread::started, m_wxWorker, &CWebwxWork::sltMainLoop);

    connect(m_wxWorker, &CWebwxWork::sglMainLoopFinished, m_tMainLoop, &QThread::quit);
    connect(m_wxWorker, &CWebwxWork::sglMainLoopFinished, this, &CLibWebwx::sltMainLoopFinished);

    connect(m_tMainLoop, &QThread::finished, m_tMainLoop, &QThread::deleteLater);
    m_tMainLoop->start();
}

QString CLibWebwx::qrcode()
{
    return m_sQrcodeLink;
}

void CLibWebwx::sltSetQrcodeLink(const QString &link)
{
    if(link == m_sQrcodeLink)
    {
        return;
    }
    m_sQrcodeLink = link;
    emit sglQrcodeOk(m_sQrcodeLink);
}

void CLibWebwx::sltHintMsg(int msg)
{
    qDebug() << HINT_MSG_MAP[msg];
    emit sglHintMsg(msg, HINT_MSG_MAP[msg]);
}

void CLibWebwx::sltAllContactOk(QByteArray allContact)
{
    m_arryContact = CWebwxContact::transferData(allContact);
    QString tmp = CWebwxContact::transferShowData(m_arryContact);
    emit sglAllContactOk(tmp);
}

void CLibWebwx::sltOneHeadOk(const QString &headFileName)
{
    emit sglOneHeadOk(headFileName);
}

void CLibWebwx::sltNewMessage(QString newMsg)
{
    // 直接把消息内容给前端，前端负责区分
    emit sglNewMessage(newMsg);
}

void CLibWebwx::sltGetUserselfFinished(const QVariantHash &userselfData)
{
    if (userselfData.isEmpty())
    {
        return;
    }
    // 把用户信息转换成json字符串传给前端
    QJsonObject jsonUserselfData = QJsonObject::fromVariantHash(userselfData);
    QJsonDocument jsonDoc(jsonUserselfData);
    emit sglGetUserselfFinished(QString(jsonDoc.toJson()));
}

void CLibWebwx::sltMainLoopFinished()
{
    if (m_wxWorker)
    {
        delete m_wxWorker;
        m_wxWorker = nullptr;
    }
    emit sglGG();
}
