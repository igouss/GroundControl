#include "CompassWidget.h"

namespace naxsoft {

CompassWidget::CompassWidget(QWidget *parent) :
	QWidget(parent) {

    lightSand = QColor(0xFEF1E0);
    darkSand = QColor(0xA47F1A).lighter(230);
    lightWood = QColor(0x3B2E2A).lighter();
    darkWood = QColor(0x3B2E2A);
    compassPointer[0] = QPoint(7, -10);
    compassPointer[1] = QPoint(-7,-10);
    chars << "N" << "E" << "S" << "W";
    azimuth = 0;


}


CompassWidget::~CompassWidget() {
	// TODO Auto-generated destructor stub
}


void CompassWidget::setAzimuth(qreal azimuth) {
    this->azimuth = azimuth;
    update();
}


void CompassWidget::resizeEvent(QResizeEvent * /* event */) {
	totalWidth = qMin(width(), height());
	dialWidth = totalWidth * 0.8;
	textWidth = totalWidth * 0.2;
	center = QPoint(width() / 2, height() / 2);
	gradient = QRadialGradient(center, (dialWidth / 2) + 35);
	gradient.setColorAt(1.0, lightSand);
	gradient.setColorAt(0.9, lightSand);
	gradient.setColorAt(0.0, darkSand);
	compassPointer[2] = QPoint(0, (dialWidth / 2) * 0.75);

	font = QFont();
	font.setPixelSize(textWidth * 0.5);
	QFontMetrics metrics(font);
	for (int i = 0; i < 4; ++i) {
		charWidths[i] = metrics.width(chars[i]) / 2;
	}
}

void CompassWidget::paintEvent(QPaintEvent * /* event */) {
	QPainter painter(this);
	QPen pen;

	painter.fillRect(rect(), lightWood);

	painter.setRenderHint(QPainter::Antialiasing);

	painter.setBrush(gradient);
	pen.setColor(darkWood);
	pen.setWidth(2);
	painter.setPen(pen);

	painter.drawEllipse(center, dialWidth / 2, dialWidth / 2);

	painter.save();

	painter.translate(center);
	painter.rotate(azimuth);

	painter.setBrush(darkWood);

	pen.setColor(darkWood);
	pen.setWidth(3);
	painter.setPen(pen);

	painter.setFont(font);

	for (int i = 0; i < 4; ++i) {
		painter.drawLine(QPoint(0, dialWidth * 0.4), QPoint(0, dialWidth * 0.49));
		pen.setColor(lightSand);
		painter.setPen(pen);
		painter.drawText(-charWidths[i], -((dialWidth / 2) + 3), chars[i]);
		pen.setColor(darkWood);
		painter.setPen(pen);
		painter.rotate(90.0);
	}
	painter.rotate(90.0);

	pen.setWidth(2);
	painter.setPen(pen);

	int currRot = 0;
	for (int i = 0; i < 24; ++i) {
		if (currRot % 90) {
			pen.setWidth(2);
			painter.setPen(pen);
			painter.drawLine(QPoint(0, dialWidth * 0.47), QPoint(0, dialWidth * 0.49));
		}
		currRot += 15;
		painter.rotate(15);
	}

	painter.restore();

	painter.translate(center);

	pen.setColor(darkWood);
	pen.setWidth(3);
	painter.setPen(pen);
	painter.setBrush(lightWood);

	painter.rotate(static_cast<qreal> ((static_cast<int> (azimuth + 180) % 360)));
	painter.drawConvexPolygon(compassPointer, 3);
}

}
