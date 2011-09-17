#ifndef GROUNDCONTROLWINDOW_H_
#define GROUNDCONTROLWINDOW_H_

#include <QtGui>
#include <QWidget>

#include "CompassWidget.h"

namespace naxsoft {


class AddressBook : public QMainWindow
{
    Q_OBJECT

public:
    AddressBook();
    CompassWidget *compassWidget;


private slots:
    void open();
    void save();
    void quit();

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

} // namespace

#endif /* GROUNDCONTROLWINDOW_H_ */
