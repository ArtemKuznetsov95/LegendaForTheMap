#include "legend.h"
#include <QLayout>

Legend::Legend(QWidget *parent) : QWidget(parent) {}

Legend::Legend(const QList<QPair<QColor, QString>> &items, QWidget *parent)
    : QWidget(parent), legendItems(items) {
  updateWidgetSize();
}

void Legend::setLegendItems(const QList<QPair<QColor, QString>> &items) {
  legendItems = items;
  updateWidgetSize();
}

void Legend::setAlignment(QWidget *parent, Qt::Alignment alignment) {
  if (!parent)
    return;
  m_parent = parent;
  m_alignment = alignment;
  int start_X = 0;
  int start_Y = 0;

  switch (alignment) {
  case Qt::AlignLeft:
    start_X = padding;
    start_Y = (parent->height() - maxHeight) / 2;
    break;
  case Qt::AlignRight:
    start_X = parent->width() - maxWidth - padding;
    start_Y = (parent->height() - maxHeight) / 2;
    break;
  case Qt::AlignBottom:
    start_Y = parent->height() - maxHeight - padding;
    start_X = (parent->width() - maxWidth) / 2;
    break;
  case Qt::AlignTop:
    start_Y = padding;
    start_X = (parent->width() - maxWidth) / 2;
    break;
  case Qt::AlignTop | Qt::AlignRight:
    start_Y = padding;
    start_X = parent->width() - maxWidth - padding;
    break;
  case Qt::AlignBottom | Qt::AlignRight:
    start_Y = parent->height() - maxHeight - padding;
    start_X = parent->width() - maxWidth - padding;
    break;
  case Qt::AlignTop | Qt::AlignLeft:
    start_Y = padding;
    start_X = padding;
    break;
  case Qt::AlignBottom | Qt::AlignLeft:
    start_Y = parent->height() - maxHeight - padding;
    start_X = padding;
  default:
    break;
  }

  this->move(start_X, start_Y);
  update();
}

void Legend::setPosition() { setAlignment(m_parent, m_alignment); }

void Legend::paintEvent(QPaintEvent *event) {
  if (legendItems.size()) {
    (void)event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(rect(), 10, 10);

    int startY = starty;
    int startx = startX;

    for (const auto &item : legendItems) {
      painter.setPen(Qt::NoPen);
      painter.setBrush(item.first);
      painter.drawRect(startx, startY, itemWidth, itemHeight);
      painter.setPen(Qt::black);
      painter.drawText(startx + itemWidth + padding, startY, width() - padding,
                       itemHeight, Qt::AlignLeft | Qt::AlignVCenter,
                       item.second);

      startY += itemHeight + padding;
    }
  } else
    QWidget::paintEvent(event);
}

void Legend::updateWidgetSize() {
  maxHeight = legendItems.size() * (itemHeight + padding) + 2 * padding;

  QFontMetrics fm(font());

  for (const auto &item : legendItems) {
    int textWidth = fm.horizontalAdvance(item.second);
    maxWidth = qMax(maxWidth, textWidth + 2 * padding + itemWidth + padding);
  }
  setFixedSize(maxWidth, maxHeight);
}
