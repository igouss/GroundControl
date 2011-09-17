#ifndef COMPASSWIDGET_H_
#define COMPASSWIDGET_H_

#include <QtGui>

namespace naxsoft {

class CompassWidget: public QWidget {
Q_OBJECT

public slots:
	void setAzimuth(qreal azimuth);


public:
	CompassWidget(QWidget *parent = 0);
	virtual ~CompassWidget();

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *);

private:
	qreal azimuth;
	//![0]
	QStringList chars;
	int charWidths[4];
	QPoint compassPointer[3];
	QPoint center;
	QColor lightSand;
	QColor darkSand;
	QColor darkWood;
	QColor lightWood;
	QRadialGradient gradient;
	QFont font;

	int totalWidth;
	int dialWidth;
	int textWidth;

}; // class


} // namespace

#endif /* COMPASSWIDGET_H_ */
