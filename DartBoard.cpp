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

#include "DartBoard.h"
#include "ui_dartboard.h"

DartBoard* DartBoard::StaticInstance;

DartBoard::DartBoard(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::DartBoard)
    , bActive(true)
    , lastKeyUpCode(0)
    , lastKeyUpTime(0)
{
    ui->setupUi(this);
    DartBoard::StaticInstance = this;
    SetWindowsHookExA(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, 0);

    connect(this, SIGNAL(targetHit(DartModifier,uint)), this, SLOT(debugTargetHit(DartModifier,uint)));
}

DartBoard::~DartBoard()
{
    delete ui;
}

void DartBoard::combinationReceived(DWORD keyModifier, DWORD keyValue) {
    DartModifier dartModifier = DartModifier_None;
    int dartValue = 0;

    if(keyModifier == VK_LWIN) {
        switch(keyValue) {
            case 0x71: { dartModifier = DartModifier_None;      dartValue = 15; break; }
            case 0x33: { dartModifier = DartModifier_Double;    dartValue = 15; break; }
            case 0x45: { dartModifier = DartModifier_Triple;    dartValue = 15; break; }
            case 0x44: { dartModifier = DartModifier_None;      dartValue = 20; break; }
            case 0x72: { dartModifier = DartModifier_Triple;    dartValue = 20; break; }
            case 0x43: { dartModifier = DartModifier_None;      dartValue = 25; break; }
            case 0x73: { dartModifier = DartModifier_None;      dartValue = 50; break; }
        }
    }
    else if(keyModifier == VK_RWIN) {
        switch(keyValue) {
            case 0xbb: { dartModifier = DartModifier_None;	    dartValue =  3; break; }
            case 0x38: { dartModifier = DartModifier_Double;	dartValue =  3; break; }
            case 0x49: { dartModifier = DartModifier_Triple;    dartValue =  3; break; }
            case 0x75: { dartModifier = DartModifier_None;	    dartValue =  4; break; }
            case 0x4b: { dartModifier = DartModifier_None;	    dartValue =  9; break; }
            case 0xdd: { dartModifier = DartModifier_Triple;    dartValue =  9; break; }
            case 0xbc: { dartModifier = DartModifier_None;	    dartValue = 18; break; }
        }
    }
    else if(keyModifier == 0){
        switch(keyValue) {
            case 0x46: { dartModifier = DartModifier_None;	    dartValue =  1; break; }
            case 0x42: { dartModifier = DartModifier_Double;	dartValue =  1; break; }
            case 0x54: { dartModifier = DartModifier_Triple;    dartValue =  1; break; }
            case 0x36: { dartModifier = DartModifier_None;	    dartValue =  2; break; }
            case 0x37: { dartModifier = DartModifier_Double;	dartValue =  2; break; }
            case 0x55: { dartModifier = DartModifier_Triple;    dartValue =  2; break; }
            case 0x26: { dartModifier = DartModifier_Double;	dartValue =  4; break; }
            case 0xde: { dartModifier = DartModifier_Triple;    dartValue =  4; break; }
            case 0x4a: { dartModifier = DartModifier_None;	    dartValue =  5; break; }
            case 0x4e: { dartModifier = DartModifier_Double;	dartValue =  5; break; }
            case 0x59: { dartModifier = DartModifier_Triple;    dartValue =  5; break; }
            case 0x56: { dartModifier = DartModifier_None;	    dartValue =  6; break; }
            case 0x6f: { dartModifier = DartModifier_Double;	dartValue =  6; break; }
            case 0x4d: { dartModifier = DartModifier_Triple;    dartValue =  6; break; }
            case 0x2d: { dartModifier = DartModifier_None;	    dartValue =  7; break; }
            case 0x7b: { dartModifier = DartModifier_Double;	dartValue =  7; break; }
            case 0x68: { dartModifier = DartModifier_Triple;    dartValue =  7; break; }
            case 0x63: { dartModifier = DartModifier_None;	    dartValue =  8; break; }
            case 0x6d: { dartModifier = DartModifier_Double;	dartValue =  8; break; }
            case 0x66: { dartModifier = DartModifier_Triple;    dartValue =  8; break; }
            case 0x5c: { dartModifier = DartModifier_Double;	dartValue =  9; break; }
            case 0x35: { dartModifier = DartModifier_None;	    dartValue = 10; break; }
            case 0x34: { dartModifier = DartModifier_Double;	dartValue = 10; break; }
            case 0x52: { dartModifier = DartModifier_Triple;    dartValue = 10; break; }
            case 0x62: { dartModifier = DartModifier_None;	    dartValue = 11; break; }
            case 0x27: { dartModifier = DartModifier_Double;	dartValue = 11; break; }
            case 0x65: { dartModifier = DartModifier_Triple;    dartValue = 11; break; }
            case 0xba: { dartModifier = DartModifier_None;	    dartValue = 12; break; }
            case 0xbf: { dartModifier = DartModifier_Double;	dartValue = 12; break; }
            case 0xdb: { dartModifier = DartModifier_Triple;    dartValue = 12; break; }
            case 0x47: { dartModifier = DartModifier_None;	    dartValue = 13; break; }
            case 0x60: { dartModifier = DartModifier_Double;	dartValue = 13; break; }
            case 0x48: { dartModifier = DartModifier_Triple;    dartValue = 13; break; }
            case 0x0d: { dartModifier = DartModifier_None;	    dartValue = 14; break; }
            case 0x25: { dartModifier = DartModifier_Double;	dartValue = 14; break; }
            case 0x5d: { dartModifier = DartModifier_Triple;    dartValue = 14; break; }
            case 0x21: { dartModifier = DartModifier_None;	    dartValue = 16; break; }
            case 0x22: { dartModifier = DartModifier_Double;	dartValue = 16; break; }
            case 0x69: { dartModifier = DartModifier_Triple;    dartValue = 16; break; }
            case 0xbd: { dartModifier = DartModifier_None;	    dartValue = 17; break; }
            case 0x30: { dartModifier = DartModifier_Double;	dartValue = 17; break; }
            case 0x50: { dartModifier = DartModifier_Triple;    dartValue = 17; break; }
            case 0x13: { dartModifier = DartModifier_Double;	dartValue = 18; break; }
            case 0xdc: { dartModifier = DartModifier_Triple;    dartValue = 18; break; }
            case 0x24: { dartModifier = DartModifier_None;	    dartValue = 19; break; }
            case 0x23: { dartModifier = DartModifier_Double;	dartValue = 19; break; }
            case 0x6b: { dartModifier = DartModifier_Triple;    dartValue = 19; break; }
            case 0x5b: { dartModifier = DartModifier_Double;	dartValue = 20; break; }
            case 0x6a: { dartModifier = DartModifier_Power;	    dartValue =  0; break; }
            case 0x6e: { dartModifier = DartModifier_Restart;   dartValue =  0; break; }
        }
    }

    // Publish hit target
    emit targetHit(dartModifier, dartValue);
}


void DartBoard::changeEvent( QEvent* e ) {
    if( e->type() == QEvent::ActivationChange )
        DartBoard::bActive = this->isActiveWindow();

    QMainWindow::changeEvent( e );
}

void DartBoard::debugTargetHit(DartModifier modifier, unsigned int value) {
    switch(modifier) {
        case DartModifier_Double:   this->ui->DisplayModifier->setText("Double");   break;
        case DartModifier_Triple:   this->ui->DisplayModifier->setText("Triple");   break;
        case DartModifier_Power:    this->ui->DisplayModifier->setText("Power");    break;
        case DartModifier_Restart:  this->ui->DisplayModifier->setText("Restart");  break;
        case DartModifier_None:     this->ui->DisplayModifier->setText(" ");        break;
    }

    if(value == 0)
        this->ui->DisplayValue->setText(" ");
    else
        this->ui->DisplayValue->setText(QString::number(value));
}

LRESULT DartBoard::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    DartBoard* self = DartBoard::StaticInstance;
    KBDLLHOOKSTRUCT* details = (KBDLLHOOKSTRUCT*)lParam;

    // Key down
    if(details->flags == 0 || details->flags == 1) {
        self->vecKeyStates[details->vkCode] = true;
    }

    // Key up
    else if(details->flags == LLKHF_UP || details->flags == (LLKHF_UP|LLMHF_INJECTED)) {
        self->vecKeyStates[details->vkCode] = false;

        // Check if any other key is currently pressed
        bool bOtherKeyPressed = false;
        for(std::map<DWORD, bool>::iterator it = self->vecKeyStates.begin(); it != self->vecKeyStates.end(); it++) {
            if(it->second == true) {
                bOtherKeyPressed = true;
                break;
            }
        }

        // If no other key is pressed, we can process the signals
        if(!bOtherKeyPressed) {
            DWORD keyModifier = 0;
            DWORD keyValue = 0;

            // Check if this is a combination
            if((details->time - self->lastKeyUpTime) < COMBINATION_TIMEOUT) {
                // Current key is modifier
                if(details->vkCode == VK_LWIN || details->vkCode == VK_RWIN) {
                    keyModifier =  details->vkCode;
                    keyValue = self->lastKeyUpCode;
                }
                // Last key was modifier
                else if(self->lastKeyUpCode == VK_LWIN || self->lastKeyUpCode == VK_RWIN) {
                    keyModifier = self->lastKeyUpCode;
                    keyValue = details->vkCode;
                }
            }
            // No combination
            else {
                keyValue = details->vkCode;
            }

            // All keys are up, we have values
            self->combinationReceived(keyModifier, keyValue);
        }

        // Remember last keyUp
        self->lastKeyUpCode = details->vkCode;
        self->lastKeyUpTime = details->time;
    }

    // Pass message and exit
    if( !self->bActive || nCode != HC_ACTION )
        return CallNextHookEx((HHOOK)NULL, nCode, wParam, lParam);

    // Hold message
    return 1;
}
