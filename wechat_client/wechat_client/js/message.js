
var recvMsgList = []
var sendMsgList = []

var MSG_TYPE = {MSGTYPE_TEXT: 1,
    MSGTYPE_IMAGE: 3,
    MSGTYPE_VOICE: 34,
    MSGTYPE_VIDEO: 43,
    MSGTYPE_MICROVIDEO: 62,
    MSGTYPE_EMOTICON: 47,
    MSGTYPE_APP: 49,
    MSGTYPE_VOIPMSG: 50,
    MSGTYPE_VOIPNOTIFY: 52,
    MSGTYPE_VOIPINVITE: 53,
    MSGTYPE_LOCATION: 48,
    MSGTYPE_STATUSNOTIFY: 51,
    MSGTYPE_SYSNOTICE: 9999,
    MSGTYPE_POSSIBLEFRIEND_MSG: 40,
    MSGTYPE_VERIFYMSG: 37,
    MSGTYPE_SHARECARD: 42,
    MSGTYPE_SYS: 10000,
    MSGTYPE_RECALLED: 10002,  // 撤销消息
};

var MSG_HINT = {MSGTYPE_TEXT: "",
    MSGTYPE_IMAGE: "[图片消息]请在手机查看",
    MSGTYPE_VOICE: "[语音消息]请在手机查看",
    MSGTYPE_VIDEO: "[视频消息]请在手机查看",
    MSGTYPE_MICROVIDEO: 62,
    MSGTYPE_EMOTICON: 47,
    MSGTYPE_APP: 49,
    MSGTYPE_VOIPMSG: 50,
    MSGTYPE_VOIPNOTIFY: 52,
    MSGTYPE_VOIPINVITE: 53,
    MSGTYPE_LOCATION: 48,
    MSGTYPE_STATUSNOTIFY: 51,
    MSGTYPE_SYSNOTICE: 9999,
    MSGTYPE_POSSIBLEFRIEND_MSG: 40,
    MSGTYPE_VERIFYMSG: 37,
    MSGTYPE_SHARECARD: 42,
    MSGTYPE_SYS: 10000,
    MSGTYPE_RECALLED: 10002,  // 撤销消息
};


// 处理消息的入口
function dealMessage(msg) {
    var jsonMsg = JSON.parse(msg)
    var addMsgList = jsonMsg["AddMsgList"]
    for(var i in addMsgList){
        var tmpMsg = addMsgList[i]
        var msgType = tmpMsg["MsgType"]
        var fromUser = tmpMsg["FromUserName"]
        var toUser = tmpMsg["ToUserName"]
        print(msgType)
        if (msgType === MSG_TYPE.MSGTYPE_STATUSNOTIFY && topBar.user_name === fromUser&& fromUser === toUser){
            addCurrentContact(tmpMsg)
        }
        else if (msgType === MSG_TYPE.MSGTYPE_TEXT){
            addCurrentMsg(tmpMsg)
        }
        else{

        }
    }
}

// 往最近联系人的ui里添加数据
function addCurrContactUser(user_name, head, nick, last_msg, time){
    var data = {"_user_name": user_name, "_head": head, "_nick": nick, "_last_msg": last_msg, "_time": time}
    currentContactList.user_list.append(data)
}

// 在全部联系人中通过username找一个好友，返回好友信息的json,找不到返回null
function findUser(userName){
    for(var i in all_friends){
        if (all_friends[i].UserName === userName){
            return all_friends[i]
        }
    }
    return null
}

var defaultHeadSource = "/res/ldh.jpg"

// 获取到的最近联系人列表，添加进ui, 主要是添加nick和username
function addCurrentContact(addMsg) {
    if (addMsg === undefined){
        return
    }
    var currFriends = addMsg["StatusNotifyUserName"]
    var friendsList = currFriends.split(",")
    for(var i in friendsList){
        var userName = friendsList[i]
        var userInfo = findUser(userName)
        if(userInfo === null){
            continue
        }
        var nick = userInfo.NickName
        addCurrContactUser(userName, defaultHeadSource, nick, "", "")
    }
}

// 在最近联系人中通过username找一个好友，返回在listview中的下标,找不到-1
function findCurrUserIndex(userName){
    var currRowCount = currentContactList.user_list.count
    for(var i = 0; i < currRowCount; i++){
        if (currentContactList.user_list.get(i)._user_name === userName){
            return i
        }
    }
    return -1
}

// 把 msgContent 文本加入 userName对应的最近联系人ui中
function addCurrentLastMsg(msgContent, userName){
    var index = findCurrUserIndex(userName)
    if (index === -1){
        return
    }

    currentContactList.user_list.get(index)._last_msg = msgContent
    var myDate = new Date()
    var nowTime = myDate.getHours().toString() + ":" + myDate.getMinutes().toString()
    currentContactList.user_list.get(index)._time = nowTime
}

// 把ui中最新收到消息的那个放到最上面
function topLastMsgCurrentUser(userName){
    var index = findCurrUserIndex(userName)
    if (index === -1){
        // 不存在的，新添加一条
        var userInfo = findUser(userName)
        if(userInfo === null){
            return
        }
        var nick = userInfo.NickName
        addCurrContactUser(userName, defaultHeadSource, nick, "", "")
        return
    }
    currentContactList.user_list.move(index, 0, 1)
}

// 最新的一条消息，在最近联系人的ui上显示
function addCurrentMsg(addMsg) {
    var msgContent = addMsg["Content"]
    if (msgContent === undefined){
        return
    }
    var fromUser = addMsg["FromUserName"]
    var toUser = addMsg["ToUserName"]
    if (fromUser === undefined || toUser === undefined){
        return
    }

    // send
    if (fromUser === topBar.user_name){
        sendMsgList.push(addMsg)
        topLastMsgCurrentUser(toUser)
        addCurrentLastMsg(msgContent, toUser)
    }
    // recv
    else if(toUser === topBar.user_name){
        recvMsgList.push(addMsg)
        topLastMsgCurrentUser(fromUser)
        addCurrentLastMsg(msgContent, fromUser)
        audioMsg.play()
    }
}
