#include "GroundControlWindow.h"
namespace naxsoft {

AddressBook::AddressBook()
{
    openAction = new QAction(tr("&Open"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(quit()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    compassWidget = new CompassWidget;
    setCentralWidget(compassWidget);

    setWindowTitle(tr("Notepad"));
}

void AddressBook::open() {

}
void AddressBook::save() {

}
void AddressBook::quit() {
	qApp->quit();
}



} // namespace
