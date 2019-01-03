#ifndef CWEBWXCONTACT_H
#define CWEBWXCONTACT_H
#include <QString>
#include <QVector>

struct WxUserInfo
{
    using UserArry = QVector<WxUserInfo>;
    QString     UserName;
    QString     NickName;
    QString     HeadImgUrl;
    QString     RemarkName;
    QString     Signature;
    QString     PYInitial;
    QString     PYQuanPin;
    QString     RemarkPYInitial;
    QString     RemarkPYQuanPin;
    QString     Province;
    QString     City;
    UserArry    MemberList;
    int         Sex;
    int         MemberCount;
    int         ContactFlag;
    int         VerifyFlag;

    QString getDisplayName() const
    {
        if (!RemarkName.isEmpty())
        {
            return RemarkName;
        }
        return NickName;
    }

    QString getDisplayPYInitial() const
    {
        if(!RemarkPYInitial.isEmpty())
        {
            return RemarkPYInitial;
        }
        return PYInitial;
    }

    QString getDisplayPYQuanPin() const
    {
        if(!RemarkPYQuanPin.isEmpty())
        {
            return RemarkPYQuanPin;
        }
        return PYQuanPin;
    }

    friend bool operator<(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName < u2.UserName;
    }

    friend bool operator>(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName > u2.UserName;
    }

    friend bool operator==(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName == u2.UserName;
    }

    friend bool operator!=(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName != u2.UserName;
    }
};


using UserArry = QVector<WxUserInfo>;

class CWebwxContact
{
public:
    CWebwxContact();

    static bool cmpUserByUserNameAsc(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName < u2.UserName;
    }

    static bool cmpUserByUserNameDes(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        return u1.UserName > u2.UserName;
    }

    // 默认显示顺序，按拼音简称排序
    static bool cmpDeafultShow(const WxUserInfo &u1, const WxUserInfo &u2)
    {
        // 群组放最前
        bool isRoom1 = u1.UserName.startsWith("@@");
        bool isRoom2 = u2.UserName.startsWith("@@");
        if (isRoom1 != isRoom2)
        {
            return isRoom1;
        }

        // 不是字母开头的放最前
        bool isLetter1 = u1.getDisplayPYInitial().isEmpty();
        bool isLetter2 = u2.getDisplayPYInitial().isEmpty();
        if (isLetter1 != isLetter2)
        {
            return isLetter1;
        }

        if (u1.getDisplayPYInitial()[0] != u2.getDisplayPYInitial()[0])
        {
            return u1.getDisplayPYInitial()[0] < u2.getDisplayPYInitial()[0];
        }
        return u1.getDisplayPYQuanPin().toLower() < u2.getDisplayPYQuanPin().toLower();
    }

    // 把请求返回的json字符串转换成结构体数组，存放用户数据
    static UserArry transferData(const QByteArray& userData);
    // 转成json字符串
    static QString transferDataToJsonString(const QByteArray& userData);
    // 把数据整理成前端需要的格式，先排序后转json字符串
    static QString transferShowData(UserArry users);
};

#endif // CWEBWXCONTACT_H
