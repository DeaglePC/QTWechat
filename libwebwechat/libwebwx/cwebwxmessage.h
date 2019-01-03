#ifndef CWEBWXMESSAGE_H
#define CWEBWXMESSAGE_H




class CWebwxMessage
{
public:
    CWebwxMessage();

    enum MSG_TYPE
    {
        MSGTYPE_TEXT = 1,               // 文本消息
        MSGTYPE_IMAGE = 3,              // 图片消息
        MSGTYPE_VOICE = 34,             // 语音消息
        MSGTYPE_FRIEND = 37,            // 好友确认消息
        MSGTYPE_VIDEO = 43,             // 视频消息
        MSGTYPE_MICROVIDEO = 62,        // 小视频
        MSGTYPE_EMOTICON = 47,          // 动画表情
        MSGTYPE_APP = 49,               // 分享链接
        MSGTYPE_VOIPMSG = 50,           // VOIPMSG
        MSGTYPE_VOIPNOTIFY = 52,        // VOIPNOTIFY
        MSGTYPE_VOIPINVITE = 53,        // VOIPINVITE
        MSGTYPE_LOCATION = 48,          // 位置消息
        MSGTYPE_STATUSNOTIFY = 51,      // 微信初始化消息
        MSGTYPE_SYSNOTICE = 9999,       // SYSNOTICE
        MSGTYPE_POSSIBLEFRIEND_MSG = 40,// POSSIBLEFRIEND_MSG
        MSGTYPE_VERIFYMSG = 37,         // 好友确认消息
        MSGTYPE_SHARECARD = 42,         // 共享名片
        MSGTYPE_SYS = 10000,            // 系统消息
        MSGTYPE_RECALLED = 10002,       // 撤销消息
    };
};

#endif // CWEBWXMESSAGE_H
