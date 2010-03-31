/*
* Copyright (C) 2010, Muguntharaj Subramanian
*
* This file is part of eKalappai.
*
* eKalappai is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* eKalappai is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License version 3
* along with eKalappai.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QDialog>
#include <windows.h>

QT_BEGIN_NAMESPACE
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
class QLibrary;
QT_END_NAMESPACE


class Window : public QDialog
{
    Q_OBJECT

public:
    Window();

    void setVisible(bool visible);

    //choosen keyboard
    int selected_keyboard;

    //status of the current keyboard including no keyboard
    int current_keyboard;

    virtual bool winEvent( MSG* message, long* result );

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showTrayMessage(int index);
    void processKeypressEvent();

private:
    void createIconGroupBox();
    void createActions();
    void createTrayIcon();
    void callHook(int kb_index);
    void removeHook();
    void changeKeyboard(int index);
    void implementTamil99();
    void implementPhonetic();
    void generatekey(int,bool);
    bool SearchArray (DWORD array[], DWORD key, int length);
    bool IsPrevkeyGrantha();

    QGroupBox *iconGroupBox;
    QLabel *iconLabel;
    QComboBox *iconComboBox;
    QCheckBox *showIconCheckBox;


    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *settingsAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QLibrary *myLib;
    HHOOK hkb;

    typedef HHOOK (*MyPrototype)(HINSTANCE, bool, HWND);
    typedef void (*CleanupHook)(HHOOK);
    typedef void (*DisableKeyboard)();
    typedef bool (*GetKeyboardStatus)();
    typedef DWORD (*GetKeyPress)();
    typedef void (*GenerateKey)(int, bool);
    typedef bool (*GetShiftKeyPress)();
    typedef bool (*GetControlKeyPress)();

    GenerateKey generatekeyLib;

    BOOL shiftkey_pressed;
    BOOL controlkey_pressed;
    DWORD current_vkCode;
    DWORD previous_1_vkCode;
    DWORD previous_2_vkCode;

    int previous_1_character;
    int previous_2_character;

    QVector<DWORD> meiezhuthukkal;
    QVector<DWORD> meiezhuthukkal_phonetic;
};

#endif
