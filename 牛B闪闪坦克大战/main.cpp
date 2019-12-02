/****************************************************************************************
 * Copyright © 2019 - 2023 by AngryKeyboard.
 * %Project% is licensed under MulanOWL BY v1.
 * You can use this software according to the terms and conditions of the MulanOWL BY v1.
 * You may obtain a copy of MulanOWL BY v1 at:
 *          http://license.coscl.org.cn/MulanOWLBYv1
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the MulanOWL BY v1 for more details.
****************************************************************************************/
#include "Class_GameWindow.h"

int main() {
  Class_GameWindow *game = new Class_GameWindow;
  game->play();
  delete game;

  return 0;
}

//////////////////////////////////////////////////////////////////
// 提取指定模块中的资源文件
// 参数：
//    strDstFile:   目标文件名。提取的资源将保存在这里；
//    strResType:   资源类型；
//    strResName:   资源名称；
// 返回值：
//    true: 执行成功；
//    false: 执行失败。
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName) {
  // 创建文件
  HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
  if (hFile == INVALID_HANDLE_VALUE)
    return false;

  // 查找资源文件中、加载资源到内存、得到资源大小
  HRSRC hRes = ::FindResource(NULL, strResName, strResType);
  HGLOBAL hMem = ::LoadResource(NULL, hRes);
  DWORD dwSize = ::SizeofResource(NULL, hRes);

  // 写入文件
  DWORD dwWrite = 0;    // 写入大小
  ::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
  ::CloseHandle(hFile);

  return true;
}
