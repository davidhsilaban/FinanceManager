#pragma once

#include <queue>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <Windows.h>

#include "resource.h"
#include "sqlite3.h"

class QPushButton;

class MainApp :
	public QMainWindow
{
	Q_OBJECT
public:
	MainApp(QWidget *parent = 0);
	~MainApp();

protected:

	// Enums
	typedef enum FinanceType {
		financeOutcome = 0,
		financeIncome
	} tFinanceType;

	// Events
	void closeEvent(QCloseEvent *event);

private slots:
	void commitData();
	void save();
	void listClicked(QListWidgetItem *item);
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
	void openFile();
	void newFile();
	bool closeDatabase();

private:
	// Structures
	typedef struct {
		QString id; // ID = type + (day+month+year+len(desc)); type = "I/O"
		QDate date;
		QString desc;
		double amount;
	} _tPendingData;

	std::queue<_tPendingData> pendingData;
	int cntPendingData;

private:

	// Variables
	int lenViewPng, lenInsertPng;

	// Resource objects
	HICON hMainIcon;
	HGLOBAL hViewIcon, hInsertIcon;
	HRSRC hViewPng, hInsertPng;

	// Qt Styles
	QWindowsStyle *qWinStyle;

	// Qt Pixmaps
	QPixmap *pmInsertIcon;
	QPixmap *pmViewIcon;

	// Qt GUI Controls
	QStackedWidget *pagesWidget, *mainStackWidget;
	QGridLayout *mainLayout;

	QHBoxLayout *calendarSelLayout, *btnLayout;
	QLabel *lblDate, *lblTransaction;
	QDateEdit *deDateSelector;
	QPushButton *btnAdd;
	QPushButton *btnDel;
	QGridLayout *layBtnOutcome, *layBtnIncome;

	// Menu objects
	QMenuBar *menuBarMain;

	QMenu *mnuFile;
	QAction *mnuFileNew, *mnuFileOpen, *mnuFileClose, *mnuFileSave, *mnuFileSaveAs, *mnuFileExit;

	QToolBar *tbMain;

	QTableWidget *tblTransaction;
	QTableModel *mdlOutcome, *mdlIncome;

	// Dock items
	QDockWidget *dock;
	QListWidget *lstMainMenu;
	QListWidgetItem *itemInputData;
	QListWidgetItem *itemViewData;

	// Objects
	//sqlite3* sqlite3Obj;
	QSqlDatabase dbFinance;

	QString strFilename;

	int totalOutcomes, totalIncomes;
	QDate earliestDateOutcome, earliestDateIncome;

	QSplitter *splTblSplitter;
	QFrame *fmeTransaction;

	bool fileOpened;
	bool fileChanged;

	// Functions
private:
	//QLayout* createMainScreen();
	void createMainScreen();
	void createDockItems();
	void createMenusAndToolbars();
	void openDatabase();
	void addItem(QTableWidget *which, QString id, QDate date, QString desc, double amount);
	void enableSaving(bool enable);
	bool checkFileValidity(QString fileName);
	void newDatabase();
	void setDatabaseOpened(bool opened);
	void setDatabaseChanged(bool changed);

public:
	// Public methods
	void insertTransaction(QDate date, QString type, QString category, QString desc, double amount);
	QStringList getCategories();
	QSqlDatabase getFinanceDatabase();

};

