#ifndef CONFIG_H
#define CONFIG_H

#include <QHash>
#include <QDir>
#include "cwebwxwork.h"

using hint_map = QHash<int, QString>;
using hint_pv = std::pair<int, QString>;

const hint_map HINT_MSG_MAP = {hint_pv(CWebwxWork::RET_MSG::LOGIN_SUCCESS,      "登录成功"),
                               hint_pv(CWebwxWork::RET_MSG::LOGIN_FAILED,       "登录失败"),
                               hint_pv(CWebwxWork::RET_MSG::HTTP_BAD_REQUEST,   "请求失败"),
                               hint_pv(CWebwxWork::RET_MSG::WX_INIT_SUCCESS,    "初始化成功")
                              };
const QString HEAD_LOCAL_PATH = QDir::homePath() + "/ddwx/head/";

#endif // CONFIG_H
