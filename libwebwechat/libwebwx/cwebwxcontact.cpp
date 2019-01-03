#include "cwebwxcontact.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantHash>
#include <QtAlgorithms>
#include <QDebug>

CWebwxContact::CWebwxContact()
{

}

UserArry CWebwxContact::transferData(const QByteArray &userData)
{
    if(userData.isEmpty())
    {
        return UserArry();
    }
    QJsonDocument jsonContent = QJsonDocument::fromJson(userData);
    int ret = jsonContent["BaseResponse"]["Ret"].toInt();

    if (ret != 0)
    {
        qDebug() << "CWebwxContact::transferData none data";
        return UserArry();
    }
    QJsonArray arryMembers = jsonContent["MemberList"].toArray();

    UserArry users;
    for(auto it = arryMembers.constBegin();
        it != arryMembers.constEnd(); it++)
    {
        QVariantHash hashItem = (*it).toObject().toVariantHash();
        WxUserInfo user;
        user.UserName = hashItem.contains("UserName") ? hashItem["UserName"].toString() : "";
        user.NickName = hashItem.contains("NickName") ? hashItem["NickName"].toString() : "";
        user.HeadImgUrl = hashItem.contains("HeadImgUrl") ? hashItem["HeadImgUrl"].toString() : "";
        user.RemarkName = hashItem.contains("RemarkName") ? hashItem["RemarkName"].toString() : "";
        user.Signature = hashItem.contains("Signature") ? hashItem["Signature"].toString() : "";
        user.PYInitial = hashItem.contains("PYInitial") ? hashItem["PYInitial"].toString() : "";
        user.PYQuanPin = hashItem.contains("PYQuanPin") ? hashItem["PYQuanPin"].toString() : "";
        user.RemarkPYInitial = hashItem.contains("RemarkPYInitial") ? hashItem["RemarkPYInitial"].toString() : "";
        user.RemarkPYQuanPin = hashItem.contains("RemarkPYQuanPin") ? hashItem["RemarkPYQuanPin"].toString() : "";
        user.Province = hashItem.contains("Province") ? hashItem["Province"].toString() : "";
        user.City = hashItem.contains("City") ? hashItem["City"].toString() : "";
        user.Sex = hashItem.contains("Sex") ? hashItem["Sex"].toInt() : 0;
        user.MemberCount = hashItem.contains("MemberCount") ? hashItem["MemberCount"].toInt() : 0;
        user.ContactFlag = hashItem.contains("ContactFlag") ? hashItem["ContactFlag"].toInt() : 0;
        user.VerifyFlag = hashItem.contains("VerifyFlag") ? hashItem["VerifyFlag"].toInt() : 0;
        users.append(user);
    }
    return users;
}

QString CWebwxContact::transferDataToJsonString(const QByteArray &userData)
{
    QJsonDocument jsonContent = QJsonDocument::fromJson(userData);
    return jsonContent["MemberList"].toString();
}

QString CWebwxContact::transferShowData(UserArry users)
{
    if(users.size() == 0)
    {
        return "";
    }
    qSort(users.begin(), users.end(), cmpDeafultShow);
    QJsonArray resArry;
    for(const auto& item : users)
    {
        if (item.VerifyFlag != 0)
        {
            continue;
        }
        QVariantHash hashResData;
        hashResData["UserName"] = item.UserName;
        hashResData["NickName"] = item.getDisplayName();
        hashResData["Sex"] = item.Sex;
        hashResData["Signature"] = item.Signature;
        hashResData["HeadImgUrl"] = item.HeadImgUrl;
        // 对群组特殊处理
        if (item.UserName.startsWith("@@"))
        {
            hashResData["PyName"] = "群组";
        }
        else
        {
            QString sTmpPyname = item.getDisplayPYInitial(); // 注意，这里的PyName是自己起的名字哦;
            hashResData["PyName"] = sTmpPyname.isEmpty() ? "?" : sTmpPyname;
        }
        resArry.append(QJsonObject::fromVariantHash(hashResData));
    }
    QJsonObject jsonRes;
    jsonRes.insert("MemberList", resArry);
    return QString(QJsonDocument(jsonRes).toJson());
}
