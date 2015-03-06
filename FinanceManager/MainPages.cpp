#include <QtGui/QtGui>

#include "MainPages.h"

#include "moc_MainPages.cpp"

NoFileOpenedPage::NoFileOpenedPage(QWidget *parent)
	: QWidget(parent)
{
	// Initialize items for Initial page
	mainLayout = new QVBoxLayout();

	lblMessage = new QLabel("Please open a Finance Manager file.");
	lblMessage->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(lblMessage);
	setLayout(mainLayout);
}

InitialPage::InitialPage(QWidget *parent)
	: QWidget(parent)
{
	// Initialize items for Initial page
	mainLayout = new QVBoxLayout();

	lblMessage = new QLabel("Please select a menu from the left side of the screen.");
	lblMessage->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(lblMessage);
	setLayout(mainLayout);
}

/*********************************************
********* BEGIN InsertDataPage Section *******
**********************************************/
InsertDataPage::InsertDataPage(QWidget *parent)
	: QWidget(parent)
{
	// Initialize items for Insert Data page
	myParent = (MainApp*)this->parent();
	pageLayout = new QBoxLayout(QBoxLayout::Down);
	mainLayout = new QGridLayout();
	grpMain = new QGroupBox("Insert New Data");

	lblDate = new QLabel("Date :");
	lblType = new QLabel("Type :");
	lblCategory = new QLabel("Category :");
	lblDescription = new QLabel("Description :");
	lblAmount = new QLabel("Amount :");

	cboDate = new QComboBox();
	cboMonth = new QComboBox();
	spnYear = new QSpinBox();
	spnYear->setMinimum(0);
	spnYear->setMaximum(2147483647);
	cboType = new QComboBox();
	cboCategory = new QComboBox();
	cboCategory->setEditable(true);
	edtDescription = new QTextEdit();
	edtDescription->setAcceptRichText(false);
	edtAmount = new QLineEdit();

	btnSubmit = new QPushButton("Submit");
	btnReset = new QPushButton("Reset");
	btnRefresh = new QPushButton("Refresh Categories");

	// Fill comboboxes
	for (int date = 1; date <= 31; date++) {
		cboDate->addItem(tr("%1").arg(date));
	}
	cboMonth->addItems(QStringList() << "January" << "February" << "March" << "April" << "May" << "June" << "July" << "August" << "September" << "October" << "November" << "December");
	cboType->addItem("Income");
	cboType->addItem("Outcome");

	// Set date values
	cboDate->setCurrentIndex(QDate::currentDate().day()-1);
	cboMonth->setCurrentIndex(QDate::currentDate().month()-1);
	spnYear->setValue(QDate::currentDate().year());

	// Add to main layout
	mainLayout->addWidget(lblDate, 0, 0, 1, 3);
	mainLayout->addWidget(cboDate, 1, 0);
	mainLayout->addWidget(cboMonth, 1, 1);
	mainLayout->addWidget(spnYear, 1, 2);
	mainLayout->addWidget(lblType, 2, 0, 1, 3);
	mainLayout->addWidget(cboType, 3, 0, 1, 3);
	mainLayout->addWidget(lblCategory, 4, 0, 1, 3);
	mainLayout->addWidget(cboCategory, 5, 0, 1, 3);
	mainLayout->addWidget(lblDescription, 6, 0, 1, 3);
	mainLayout->addWidget(edtDescription, 7, 0, 1, 3);
	mainLayout->addWidget(lblAmount, 8, 0, 1, 3);
	mainLayout->addWidget(edtAmount, 9, 0, 1, 3);
	mainLayout->addWidget(btnSubmit, 10, 0);
	mainLayout->addWidget(btnRefresh, 10, 1);
	mainLayout->addWidget(btnReset, 10, 2);

	// Add to main group
	grpMain->setLayout(mainLayout);

	pageLayout->addWidget(grpMain);

	// Add button actions
	connect(btnSubmit, SIGNAL(pressed()), this, SLOT(addTransaction()));
	connect(btnReset, SIGNAL(pressed()), this, SLOT(resetForm()));
	connect(btnRefresh, SIGNAL(pressed()), this, SLOT(refreshCategories()));

	setLayout(pageLayout);
}

void InsertDataPage::addTransaction()
{
	myParent->insertTransaction(QDate(spnYear->value(), cboMonth->currentIndex()+1, cboDate->currentIndex()+1), cboType->currentText(), cboCategory->currentText(), edtDescription->toPlainText(), edtAmount->text().toDouble());
}

void InsertDataPage::resetForm()
{
	// Set date values
	cboDate->setCurrentIndex(QDate::currentDate().day()-1);
	cboMonth->setCurrentIndex(QDate::currentDate().month()-1);
	spnYear->setValue(QDate::currentDate().year());

	// Empty the fields
	edtDescription->setText("");
	edtAmount->setText("");
	cboCategory->setEditText("");

	// Reset the combo box
	cboType->setCurrentIndex(0);
}

void InsertDataPage::refreshCategories()
{
	// Read available categories from the database
	QStringList categories = myParent->getCategories();

	// Clear the categories combo box items
	cboCategory->clear();

	// Insert the categories into the combo box
	cboCategory->addItems(categories);
}

/*********************************************
********* END InsertDataPage Section *********
**********************************************/

/*********************************************
********* BEGIN ViewDataPage Section *******
**********************************************/
ViewDataPage::ViewDataPage(QWidget *parent)
	: QWidget(parent)
{
	// Set parent object pointer
	myParent = (MainApp*)this->parent();
	// Initialize database related objects
	tblModel = new QSqlRelationalTableModel(this, myParent->getFinanceDatabase());
	// Initialize items for View Data page
	mainLayout = new QVBoxLayout();

	grpFilter = new QGroupBox("Filter Data");

	filterFormLayout = new QGridLayout();

	lblDate = new QLabel("Date :");
	lblType = new QLabel("Type :");
	lblCategory = new QLabel("Category :");
	lblDescription = new QLabel("Description :");
	lblAmount = new QLabel("Amount :");

	cboDate = new QComboBox();
	cboMonth = new QComboBox();
	spnYear = new QSpinBox();
	spnYear->setMinimum(0);
	spnYear->setMaximum(2147483647);
	cboType = new QComboBox();
	cboCategory = new QComboBox();
	edtDescription = new QLineEdit();
	edtAmount = new QLineEdit();


	btnClearFilter = new QPushButton("Clear Filter");
	btnFilter = new QPushButton("Filter");
	btnRefresh = new QPushButton("Refresh Data");

	filterFormLayout->addWidget(lblDate, 0, 0, 1, 3);
	filterFormLayout->addWidget(cboDate, 1, 0);
	filterFormLayout->addWidget(cboMonth, 1, 1);
	filterFormLayout->addWidget(spnYear, 1, 2);
	filterFormLayout->addWidget(lblType, 2, 0, 1, 3);
	filterFormLayout->addWidget(cboType, 3, 0, 1, 3);
	filterFormLayout->addWidget(lblCategory, 4, 0, 1, 3);
	filterFormLayout->addWidget(cboCategory, 5, 0, 1, 3);
	filterFormLayout->addWidget(lblDescription, 6, 0, 1, 3);
	filterFormLayout->addWidget(edtDescription, 7, 0, 1, 3);
	filterFormLayout->addWidget(lblAmount, 8, 0, 1, 3);
	filterFormLayout->addWidget(edtAmount, 9, 0, 1, 3);
	filterFormLayout->addWidget(btnClearFilter, 10, 0);
	filterFormLayout->addWidget(btnRefresh, 10, 1);
	filterFormLayout->addWidget(btnFilter, 10, 2);

	grpFilter->setLayout(filterFormLayout);

	// Fill the combo box items
	for (int date = 1; date <= 31; date++) {
		cboDate->addItem(tr("%1").arg(date));
	}
	cboMonth->addItems(QStringList() << "January" << "February" << "March" << "April" << "May" << "June" << "July" << "August" << "September" << "October" << "November" << "December");
	
	// Set the correct dates
	cboDate->setCurrentIndex(QDate::currentDate().day()-1);
	cboMonth->setCurrentIndex(QDate::currentDate().month()-1);
	spnYear->setValue(QDate::currentDate().year());

	// Create the table
	tblTransaction = new QTableView();
	//tblTransaction->setHorizontalHeaderLabels(QString("ID;Date;Type;Category;Description;Amount").split(";"));
	tblTransaction->setModel(tblModel);

	// Connect signals
	connect(btnRefresh, SIGNAL(pressed()), this, SLOT(refreshTable()));

	mainLayout->addWidget(grpFilter);
	mainLayout->addWidget(tblTransaction);
	setLayout(mainLayout);
}

void ViewDataPage::refreshTable()
{
	tblModel->setTable("Transactions");
	tblModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	tblModel->setRelation(3, QSqlRelation("Categories", "cat_id", "cat_name"));

	tblModel->setHeaderData(0, Qt::Horizontal, "ID");
	tblModel->setHeaderData(1, Qt::Horizontal, "Date");
	tblModel->setHeaderData(2, Qt::Horizontal, "Type");
	tblModel->setHeaderData(3, Qt::Horizontal, "Category");
	tblModel->setHeaderData(4, Qt::Horizontal, "Description");
	tblModel->setHeaderData(5, Qt::Horizontal, "Amount");

	tblModel->select();
	tblTransaction->setModel(tblModel);
	tblTransaction->setItemDelegate();
}

/*********************************************
********* END ViewDataPage Section *********
**********************************************/