#include "WinAPI.h"
#include <QHBoxLayout>
#include <windows.h>
#include <QWindow>

WinAPI::WinAPI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton, &QPushButton::clicked, this, &WinAPI::btnSlot);
}

void WinAPI::btnSlot()
{
    QString path = "D:\\Notepad++\\notepad++.exe";
    QString file = "test.txt";
	ShellExecuteA(0, "open", path.toLatin1().data(), file.toLatin1().data(), NULL, true);
	Sleep(2 * 1000);

	WId wid = (WId)FindWindow(L"Notepad++", NULL);
	QWindow* m_window;
	m_window = QWindow::fromWinId(wid);

	QHBoxLayout* wLayout = new QHBoxLayout(ui.widget);
	QWidget* m_widget;
	m_widget = QWidget::createWindowContainer(m_window, ui.widget);
	wLayout->addWidget(m_widget);

	wid = (WId)FindWindow(NULL, L"WinAPI");
	FlashWindow((HWND)wid, true);
}