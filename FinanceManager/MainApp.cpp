#include <QtGui/QApplication>
#include <QtGui/QtGui>

#include "MainApp.h"
#include "MainPages.h"

//#include "moc_MainApp.cpp"

#define CHECK_SQLITE(x) printf("SQLite error: %d\n", x);
#define printSQLError(q) qDebug() << "QSQLITE error: " << q.lastError().text();

const UINT MainApp::uTaskbarBtnCreatedMsg = RegisterWindowMessage(L"TaskbarButtonCreated");

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setOrganizationName("David Silaban");
	app.setApplicationName("Finance Manager");
	app.setApplicationVersion("1.0.0");

	MainApp *mainApp = new MainApp();
	mainApp->resize(640, 480);
	mainApp->show();
	return app.exec();
}

MainApp::MainApp(QWidget* parent)
	: QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	//QWidget *widget = new QWidget();
	
	hMainIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN_ICON));
	setWindowIcon(QIcon(QPixmap::fromWinHICON(hMainIcon)));
	DestroyIcon(hMainIcon);

	setWindowTitle("Finance Manager");

	// Setup database access
	dbFinance = QSqlDatabase::addDatabase("QSQLITE", "main_db_connection");
	financeData = new FinanceData();
	financeData->setParent(this);
	connect(financeData, SIGNAL(onDownloadProgress(qint64,qint64)), this, SLOT(updateTaskbarProgress(qint64,qint64)));
	connect(financeData, SIGNAL(onDownloadFinished()), this, SLOT(onFinanceDataFinished()));

	// Create menu bar items
	createMenusAndToolbars();

	// Create main menu dock
	createDockItems();

	//widget->setLayout(createMainScreen());
	//setCentralWidget(widget);
	createMainScreen();

	// Set the file opened flag
	setDatabaseOpened(false);

	// Set the file changed flag
	setDatabaseChanged(false);
}

bool MainApp::winEvent(MSG *message, long *result)
{
	if (message->message == uTaskbarBtnCreatedMsg) {
		QMessageBox::information(0, "Information", "Taskbar Button Created");
		QMessageBox::information(0, "Windows Version", QString("Windows version %1").arg(QSysInfo::windowsVersion()));
		if ((QSysInfo::windowsVersion() & QSysInfo::WV_NT_based) >= QSysInfo::WV_WINDOWS7) {
			CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (LPVOID*)&pITL);
		}
		result = 0;
		return true;
	}
	return false;
}

void MainApp::closeEvent(QCloseEvent *event)
{
	if (!closeDatabase()) {
		event->ignore();
	}
	//qApp->closeAllWindows();
}

MainApp::~MainApp()
{
	if (pITL) pITL->Release();
}

void MainApp::setDatabaseOpened(bool opened)
{
	if (!opened) {
		setWindowTitle("Finance Manager");
		mnuFileClose->setEnabled(false);
		tbMain->actions().at(2)->setEnabled(false);

		pagesWidget->setCurrentIndex(0);
		lstMainMenu->setCurrentItem(NULL);
		dock->setVisible(false);
		fileOpened = false;
	} else {
		setWindowTitle(tr("%1 - Finance Manager").arg(strFilename.right((strFilename.count()-strFilename.lastIndexOf("/"))-1)));
		mnuFileClose->setEnabled(true);
		tbMain->actions().at(2)->setEnabled(true);

		pagesWidget->setCurrentIndex(1);
		lstMainMenu->setCurrentItem(NULL);
		dock->setVisible(true);
		fileOpened = true;
	}
}

void MainApp::setDatabaseChanged(bool changed)
{
	if (!fileOpened) {
		fileChanged = false;
		return;
	}
	if (!changed) {
		setWindowTitle(tr("%1 - Finance Manager").arg(strFilename.right((strFilename.count()-strFilename.lastIndexOf("/"))-1)));
		enableSaving(false);
		fileChanged = false;
	} else {
		setWindowTitle(tr("%1* - Finance Manager").arg(strFilename.right((strFilename.count()-strFilename.lastIndexOf("/"))-1)));
		enableSaving(true);
		fileChanged = true;
	}
}

void MainApp::newFile()
{
	strFilename = QFileDialog::getSaveFileName(0, "Create New Database", QString(), "Database Files (*.fdb)");

	if (strFilename != "") {
		if (QFile::exists(strFilename)) {
			QFile::remove(strFilename);
		}
		openDatabase();
		newDatabase();
		setDatabaseOpened(true);
		setDatabaseChanged(false);
	}
}

void MainApp::openFile()
{
	strFilename = QFileDialog::getOpenFileName(0, "Open Existing Database", QString(), "Database Files (*.fdb);;All Files (*.*)");

	if (strFilename != "") {
		if (fileOpened) {
			closeDatabase();
		}
		if (!checkFileValidity(strFilename)) {
			QMessageBox::warning(this, "Invalid File", "Invalid Finance Manager file!");
			return;
		}
		openDatabase();
		setDatabaseOpened(true);
		setDatabaseChanged(false);
	}
}

void MainApp::createMenusAndToolbars()
{
	// Creates all the menu bar options
	mnuFile = new QMenu("&File");
	mnuFileNew = new QAction("&New", this);
	mnuFileNew->setShortcut(QKeySequence::New);
	mnuFileOpen = new QAction("&Open...", this);
	mnuFileOpen->setShortcut(QKeySequence::Open);
	mnuFileClose = new QAction("&Close", this);
	mnuFileClose->setShortcut(QKeySequence::Close);
	mnuFileSave = new QAction("&Save", this);
	mnuFileSave->setShortcut(QKeySequence::Save);
	mnuFileSaveAs = new QAction("Save &As...", this);
	mnuFileSaveAs->setShortcut(QKeySequence::SaveAs);
	mnuFileExit = new QAction("E&xit", this);
	mnuFileExit->setShortcut(QKeySequence::Quit);

	menuBarMain = this->menuBar();
	menuBarMain->addMenu(mnuFile);

	mnuFile->addAction(mnuFileNew);
	mnuFile->addAction(mnuFileOpen);
	mnuFile->addAction(mnuFileClose);
	mnuFile->addAction(mnuFileSave);
	mnuFile->addAction(mnuFileSaveAs);
	mnuFile->addSeparator();
	mnuFile->addAction(mnuFileExit);

	// Creates toolbar items

	// Load current style
	qWinStyle = new QWindowsStyle();

	tbMain = this->addToolBar("Main");

	tbMain->addAction(qWinStyle->standardIcon(QStyle::SP_FileDialogEnd), "New");
	tbMain->addAction(qWinStyle->standardIcon(QStyle::SP_DialogOpenButton), "Open");
	tbMain->addAction(qWinStyle->standardIcon(QStyle::SP_DialogCloseButton), "Close");
	tbMain->addAction(qWinStyle->standardIcon(QStyle::SP_DialogSaveButton), "Save");

	// Disable saving buttons
	enableSaving(false);

	connect(mnuFileNew, SIGNAL(triggered()), this, SLOT(newFile()));
	connect(mnuFileOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(mnuFileClose, SIGNAL(triggered()), this, SLOT(closeDatabase()));
	connect(mnuFileSave, SIGNAL(triggered()), this, SLOT(save()));
	connect(mnuFileExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	// Connect toolbar functions
	connect(tbMain->actions().at(0), SIGNAL(triggered()), this, SLOT(newFile()));
	connect(tbMain->actions().at(1), SIGNAL(triggered()), this, SLOT(openFile()));
	connect(tbMain->actions().at(2), SIGNAL(triggered()), this, SLOT(closeDatabase()));
	connect(tbMain->actions().at(3), SIGNAL(triggered()), this, SLOT(save()));

}

void MainApp::enableSaving(bool enable)
{
	// Set menu states
	mnuFileSave->setEnabled(enable);
	mnuFileSaveAs->setEnabled(enable);
	// Set save button state
	tbMain->actions().at(3)->setEnabled(enable);
}

void MainApp::addItem(QTableWidget *which, QString id, QDate date, QString desc, double amount)
{
	// This method adds a new item to the list
	int rowCount = which->rowCount();
	QTableWidgetItem *item[4];
	item[0] = new QTableWidgetItem(id);
	item[1] = new QTableWidgetItem(date.toString("dd-mm-yyyy"));
	item[2] = new QTableWidgetItem(desc);
	item[3] = new QTableWidgetItem(tr("%1").arg(amount));
}

void MainApp::createDockItems()
{
	dock = new QDockWidget(tr("Main Menu"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);
	dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

	lstMainMenu = new QListWidget();
	lstMainMenu->setViewMode(QListView::IconMode);
	lstMainMenu->setIconSize(QSize(96, 96));
	lstMainMenu->setMovement(QListView::Static);
	lstMainMenu->setMaximumWidth(128);
	lstMainMenu->setSpacing(12);

	// Load the "Insert Data" icon from the resource file
	hInsertPng = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_INSERT), L"PNG");
	hInsertIcon = LoadResource(GetModuleHandle(NULL), hInsertPng);
	lenInsertPng = SizeofResource(GetModuleHandle(NULL), hInsertPng);
	pmInsertIcon = new QPixmap();
	pmInsertIcon->loadFromData((uchar*)LockResource(hInsertIcon), lenInsertPng);

	// Load the "View Data" icon from the resource file
	hViewPng = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_VIEW), L"PNG");
	hViewIcon = LoadResource(GetModuleHandle(NULL), hViewPng);
	lenViewPng = SizeofResource(GetModuleHandle(NULL), hViewPng);
	pmViewIcon = new QPixmap();
	pmViewIcon->loadFromData((uchar*)LockResource(hViewIcon), lenViewPng);

	itemInputData = new QListWidgetItem(tr("Input Data"));
	itemInputData->setIcon(QIcon(*pmInsertIcon));
	itemInputData->setTextAlignment(Qt::AlignHCenter);
	itemInputData->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

	itemViewData = new QListWidgetItem(tr("View Data"));
	itemViewData->setIcon(QIcon(*pmViewIcon));
	itemViewData->setTextAlignment(Qt::AlignHCenter);
	itemViewData->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

	lstMainMenu->addItem(itemInputData);
	lstMainMenu->addItem(itemViewData);

	dock->setWidget(lstMainMenu);

	addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainApp::createMainScreen()
{
	// Initialize all elements of the main screen
	//mainStackWidget = new QStackedWidget();

	pagesWidget = new QStackedWidget();
	pagesWidget->addWidget(new NoFileOpenedPage);
	pagesWidget->addWidget(new InitialPage);
	pagesWidget->addWidget(new InsertDataPage(this));
	pagesWidget->addWidget(new ViewDataPage(this));

	//pagesWidget->setCurrentIndex(1);
	//pagesWidget->setVisible(true);

	connect(lstMainMenu, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listClicked(QListWidgetItem*)));
	connect(lstMainMenu, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));

	setCentralWidget(pagesWidget);

	/*
	mainLayout = new QGridLayout();
	calendarSelLayout = new QHBoxLayout();

	lblDate = new QLabel("Date");
	deDateSelector = new QDateEdit();
	calendarSelLayout->addWidget(lblDate);
	calendarSelLayout->addWidget(deDateSelector);

	deDateSelector->setDate(QDate::currentDate());

	mainLayout->addLayout(calendarSelLayout, 0, 0);

	splTblSplitter = new QSplitter(Qt::Orientation::Vertical);

	tblTransaction = new QTableWidget(0, 5);
	tblTransaction->setHorizontalHeaderLabels(QString("ID;Date;Code;Description;Amount").split(";"));
	lblTransaction = new QLabel("Transactions :");
	
	fmeTransaction = new QFrame();
	fmeTransaction->setLayout(new QVBoxLayout());
	fmeTransaction->layout()->addWidget(lblTransaction);
	fmeTransaction->layout()->addWidget(tblTransaction);
	//fmeOutcome->layout()->addWidget();

	splTblSplitter->addWidget(fmeTransaction);

	btnLayout = new QHBoxLayout();
	
	btnAdd = new QPushButton("Add");
	btnLayout->addWidget(btnAdd);

	//splTblSplitter->addWidget(btnLayout);

	mainLayout->addWidget(splTblSplitter);

	return mainLayout;
	*/
}

void MainApp::listClicked(QListWidgetItem *item)
{
	if (!pagesWidget->isVisible())
		pagesWidget->setVisible(true);

	pagesWidget->setCurrentIndex(lstMainMenu->row(item)+2);
}

void MainApp::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	//pagesWidget->setCurrentIndex(lstMainMenu->row(current)+1);
}

void MainApp::insertTransaction(QDate date, QString type, QString category, QString desc, double amount) {
	// Inserts a new item to the database
	int iType = (type == "Income") ? 0 : 1;
	int cat_id = -1;
	QString new_cat = category.at(0).isUpper() == false ? category.replace(0, 1, category.at(0).toUpper()) : category;
	QSqlQuery query(dbFinance);

	// Search for category ID in the database, if not found then add the category first to the Categories table and then get the category ID from the table
	query.exec("SELECT cat_id, cat_name FROM Categories WHERE cat_name LIKE '%" + category + "%'");
	printSQLError(query);
	query.next();
	qDebug() << query.size();

	dbFinance.transaction(); // Starts a transaction on the database 
	printSQLError(query);
	if (!query.isValid()) {
		// Insert the category to the Categories table
		query.exec(QString("INSERT INTO Categories (cat_name) VALUES ('%1')").arg(new_cat));
		printSQLError(query);

		// Get the category ID from the inserted data
		query.exec("SELECT cat_id, cat_name FROM Categories WHERE cat_name LIKE '%" + category + "%'");
		printSQLError(query);
		query.next();
		cat_id = query.value(0).toInt();
	} else {
		cat_id = query.value(0).toInt();
	}

	// Insert the data to the database
	QString insert_query = QString("INSERT INTO Transactions (date, type, category, description, amount) VALUES('%1-%2-%3', %4, %5, '%6', %7)").arg(date.year()).arg(date.month()).arg(date.day()).arg(iType).arg(cat_id).arg(desc).arg(amount);
	query.exec(insert_query);
	qDebug() << insert_query;
	printSQLError(query);
	if (query.lastError().type() == QSqlError::NoError) {
		QMessageBox::information(this, "Success", "The data has been input successfully.");
		setDatabaseChanged(true);
	} else {
		QMessageBox::warning(this, "Error", "Unable to input data: " + query.lastError().text());
	}
}

void MainApp::commitData()
{
	// TODO: Change SQLite DB API

	/*
	for (int i; i < tblTransaction->rowCount(); i++)
	{
		CHECK_SQLITE(sqlite3_exec(sqlite3Obj, tr("INSERT OR REPLACE INTO tblTransaction VALUES(%1,%2,%3,%4)").arg(tblTransaction->item(i, 0)->text(),tblTransaction->item(i, 1)->text(),tblTransaction->item(i, 2)->text(),tblTransaction->item(i, 3)->text()).toLatin1(), 0, 0, 0));
	}
	*/
	//dbFinance->commit();

	//if (totalOutcomes == 0) CHECK_SQLITE(sqlite3_exec(sqlite3Obj, tr("REPLACE INTO tblProperties(earliestDateOutcome) VALUES(%1)").arg((QDate(1970,1,1).daysTo(deDateSelector->date()))*24*3600).toLatin1(), 0, 0, 0));
	//CHECK_SQLITE(sqlite3_exec(sqlite3Obj, tr("REPLACE INTO tblProperties(totalOutcomes,latestDateOutcome) VALUES(%1,%2)").arg(totalOutcomes).arg((QDate(1970,1,1).daysTo(QDate::currentDate()))*24*3600).toLatin1(), 0, 0, 0));
	dbFinance.commit();
}

bool MainApp::checkFileValidity(QString fileName)
{
	{
		QSqlDatabase db;

		db = QSqlDatabase::addDatabase("QSQLITE", "check_file_connection");
		db.setDatabaseName(fileName);
		if (!db.open())
			return false;

		if (db.tables() != (QStringList() << "Transactions" << "Categories")) {
			db.close();
			return false;
		}

		db.close();
	}
	QSqlDatabase::removeDatabase("check_file_connection");
	return true;
}

void MainApp::newDatabase()
{
	QSqlQuery query(dbFinance);

	query.exec("CREATE TABLE IF NOT EXISTS Transactions(transaction_id INTEGER PRIMARY KEY, date INTEGER, type INTEGER, category INTEGER REFERENCES Categories(cat_id) ON UPDATE CASCADE, description TEXT, amount REAL)");
	printSQLError(query);
	query.exec("CREATE TABLE IF NOT EXISTS Categories (cat_id INTEGER PRIMARY KEY, cat_name TEXT)");
	printSQLError(query);
}

void MainApp::openDatabase()
{
	// TODO: Change SQLite DB API
	/*
	CHECK_SQLITE(sqlite3_open(strFilename.toLatin1(), &sqlite3Obj));

	CHECK_SQLITE(sqlite3_exec(sqlite3Obj, "CREATE TABLE tblProperties(date int, totalOutcomes int, totalIncomes int)", 0, 0, 0));
	CHECK_SQLITE(sqlite3_exec(sqlite3Obj, "CREATE TABLE tblTransaction(id text unique primary key, date int, desc text, amount int)", 0, 0, 0));
	*/

	dbFinance.setDatabaseName(strFilename);
	dbFinance.open();
	printSQLError(dbFinance);
}

bool MainApp::closeDatabase()
{
	// TODO: Change SQLite DB API
	//CHECK_SQLITE(sqlite3_close(sqlite3Obj));

	if (fileChanged) {
		int prompt = QMessageBox::question(this, "Save File", "Do you want to save your file before closing?" , QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
		if (prompt == QMessageBox::Yes) {
			commitData();
		} else if (prompt == QMessageBox::Cancel) {
			return false;
		}
	}
	dbFinance.rollback();
	dbFinance.close();
	setDatabaseChanged(false);
	setDatabaseOpened(false);
	return true;
}

void MainApp::save()
{
	//openDatabase();
	commitData();
	setDatabaseChanged(false);
	//closeDatabase();
}

QStringList MainApp::getCategories()
{
	QSqlQuery query(dbFinance);
	QStringList result;

	if (!dbFinance.isOpen()) return QStringList();

	query.exec("SELECT cat_name FROM Categories");

	while (query.next()) {
		result.append(query.value(0).toString());
	}

	return result;
}

QSqlDatabase MainApp::getFinanceDatabase()
{
	return dbFinance;
}

FinanceData *MainApp::getFinanceDataInstance()
{
	return financeData;
}

void MainApp::showTaskbarProgress(bool show) {
	if (pITL) {
		if (show) {
			pITL->SetProgressState(this->winId(), TBPF_NORMAL);
		} else {
			pITL->SetProgressState(this->winId(), TBPF_NOPROGRESS);
		}
	}
}

void MainApp::setTaskbarProgress(quint64 value, quint64 max_value) {
	if (pITL) {
		pITL->SetProgressValue(this->winId(), value, max_value);
	}
}

void MainApp::updateTaskbarProgress(qint64 current, qint64 total) {
	showTaskbarProgress(true);
	setTaskbarProgress(current, total);
}

void MainApp::onFinanceDataFinished() {
	showTaskbarProgress(false);
}