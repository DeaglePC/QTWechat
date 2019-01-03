

var defaultHeadSource = "/res/ldh.jpg"
var headSourceScheme = "file://"


// 往所有联系人列表里添加数据,获取头像
function addAllContactUser(user_name, head, nick, pyname){
    var data = {"_user_name": user_name, "_nick": nick, "_head": defaultHeadSource, "_pyname": pyname}
    //wx.getOneHead(head)
    allContactList.user_list.append(data);
}

// 获取一个头像
function allContactImgStatusChanged(_user_name, _status, _head){
    if(_status === Image.Ready){
        if(_head.indexOf(defaultHeadSource) !==-1 && _user_name !== ""){
            wx.getOneHeadByUsername(_user_name)
        }
    }
}

// 接收到联系人的信号后开始处理数据，加进ui
function dealAllContact(allContact){
    var jsonContact = JSON.parse(allContact);
    var memberList = jsonContact["MemberList"]
    all_friends = memberList
    for(var i in memberList){
        addAllContactUser(memberList[i].UserName, memberList[i].HeadImgUrl, memberList[i].NickName, memberList[i].PyName)
    }
    print("add all done!!!")
}

// 把本地的头像加到listview里, 一个头像获取成功后执行
function addContactHead(headFileName){
    //print(headFileName)
    var startIndex = headFileName.lastIndexOf("/")
    var endIndex = headFileName.lastIndexOf(".")
    var userName = headFileName.substring(startIndex + 1, endIndex)

    if (topBar.user_name === userName){
        topBar.head_image_url = headSourceScheme + headFileName
        return
    }

    // 加进全部联系人列表
    var rowCount = allContactList.user_list.count;
    for(var i = 0; i < rowCount; i++){
        var data = allContactList.user_list.get(i)
        if (data._user_name === userName){
            allContactList.user_list.get(i)._head = headSourceScheme + headFileName
        }
    }

    // 加进最近联系人列表
    var currRowCount = currentContactList.user_list.count
    for(var j = 0; j < currRowCount; j++){
        var dataCurr = currentContactList.user_list.get(j)
        if (dataCurr === undefined){
            continue
        }
        if (dataCurr._user_name === userName){
            currentContactList.user_list.get(j)._head = headSourceScheme + headFileName
        }
    }
}

// 把用户本人的信息加进ui
function addUserselfData(strUserselfData) {
    topBar.json_data = strUserselfData
    var jsonObj = JSON.parse(strUserselfData);
    topBar.user_name = jsonObj["UserName"]
    topBar.nick_name = jsonObj["NickName"]
    wx.getOneHead(jsonObj["HeadImgUrl"])
}
