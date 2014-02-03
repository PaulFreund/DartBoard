//###################################################################################################
/*
    Copyright (c) since 2014 - Paul Freund

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/
//###################################################################################################

#ifndef DARTBOARD_H
#define DARTBOARD_H

#include <QMainWindow>
#include <windows.h>
#include <map>

namespace Ui {
class DartBoard;
}

enum DartModifier {
    DartModifier_None,
    DartModifier_Double,
    DartModifier_Triple,
    DartModifier_Power,
    DartModifier_Restart
};

class DartBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit DartBoard(QWidget *parent = 0);
    ~DartBoard();

public:
    Ui::DartBoard *ui;

public:
    const static unsigned int COMBINATION_TIMEOUT = 100;

    bool bActive;
    static DartBoard* StaticInstance;

    DWORD lastKeyUpCode;
    DWORD lastKeyUpTime;

    std::map<DWORD, bool> vecKeyStates;

private:
    void combinationReceived(DWORD keyModifier = 0, DWORD keyValue = 0);

public slots:
    void changeEvent( QEvent* e );
    void debugTargetHit(DartModifier modifier = DartModifier_None, unsigned int value = 0);

public:
    static LRESULT KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);


signals:
    void targetHit(DartModifier modifier = DartModifier_None, unsigned int value = 0);
};

#endif // DARTBOARD_H
