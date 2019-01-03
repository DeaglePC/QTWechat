
function centerUi(uiWindow){
    var pos_x = (screen_width - uiWindow.width) / 2
    var pos_y = (screen_height - uiWindow.height) / 2
    uiWindow.x = pos_x
    uiWindow.y = pos_y
}

function runWx() {
    wx.work()
    login.visible = true
    mainUi.visible = false;
    root.width = 300
    root.height = 350
    centerUi(root)
}

function dealHintMsg(msg_type, msg) {
    login.hint_msg = msg
    if (msg_type === WxLogin.RET_MSG.WX_INIT_SUCCESS){
        initUi()
    }
}

function initUi(){
    login.visible = false
    mainUi.visible = true;
    root.width = 1000
    root.height = 650
    centerUi(root)
}

function delUi(){
    allContactList.user_list.clear()
    currentContactList.user_list.clear()
    all_friends = null
}

function gameOver(){
    delUi()
    runWx()
    login.hintMsgText = "登录失效，请重新扫二维码登录"
}

// start tab切换
function showCurrentContact(){
    currentContactList.visible = true
    allContactList.visible = false
}

function showAllContact(){
    currentContactList.visible = false
    allContactList.visible = true
}

function onChatBtnClicked(){
    showCurrentContact()
}

function onPublicBtnClicked(){

}

function onFriendsBtnClicked(){
    showAllContact()
}
// end tab切换
