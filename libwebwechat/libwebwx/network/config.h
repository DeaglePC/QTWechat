#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QByteArray>
#include <QHash>
#include <QVector>
#include <QPair>


namespace WechatRequestValue
{

using qvPair = std::pair<QString,QVector<QString>>;

const QString APP_ID = "wx782c26e4c19acffb";
const QString WEBWXINIT = "webwxinit";
const QString WEBWXSTATUSNOTIFY = "webwxstatusnotify";
const QHash<QString, QVector<QString> > DETAIL_URL = {qvPair("wx2.qq.com",      {"file.wx2.qq.com", "webpush.wx2.qq.com"}),
                                                      qvPair("wx8.qq.com",      {"file.wx8.qq.com", "webpush.wx8.qq.com"}),
                                                      qvPair("qq.com",          {"file.wx.qq.com", "webpush.wx.qq.com"}),
                                                      qvPair("web2.wechat.com", {"file.web2.wechat.com", "webpush.web2.wechat.com"}),
                                                      qvPair("wechat.com",      {"file.web.wechat.com", "webpush.web.wechat.com"})};
const QString SYNC_CHECK = "synccheck";
const QString GET_MSG = "webwxsync";
const QString GET_CONTACT = "webwxgetcontact";
}

namespace WechatRequestUrl
{
const QString GET_UUID      = "https://login.weixin.qq.com/jslogin";
const QString GET_QRCODE    = "https://login.weixin.qq.com/qrcode/";
const QString CHECK_LOGIN   = "https://login.wx.qq.com/cgi-bin/mmwebwx-bin/login";
const QString ICON_BASE_URL = "https://wx.qq.com";
const QString ICON_FULL_URL = "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgeticon";
const QString IMG_FULL_URL  = "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxgetheadimg";
}

namespace WechatRequestHeader
{
const QByteArray USER_AGENT("Mozilla/5.0 "
                            "(Macintosh; Intel Mac OS X 10_11_6) "
                            "AppleWebKit/537.36 (KHTML, like Gecko) "
                            "Chrome/54.0.2840.71 Safari/537.36'");
}



#endif // CONFIG_H
