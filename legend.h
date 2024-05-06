#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QPair>
#include <QColor>
#include <QFontMetrics>
#include <QResizeEvent>
#include <QDebug>

///
/// \brief The Legend class - Легенда
///
class Legend : public QWidget
{
    Q_OBJECT
public:
    explicit Legend(QWidget *parent = nullptr);
    Legend(const QList<QPair<QColor, QString>>& items, QWidget *parent = nullptr);

    ///
    /// \brief setLegendItems - Добавление списка легенды
    /// \param items - Список (Цвет, Описание цвета)
    ///
    void setLegendItems(const QList<QPair<QColor, QString>>& items);
    ///
    /// \brief setAlignment - Позиция виджета относительно родителя
    /// \param parent - Виджет родителя
    /// \param alignment - Положение виджета
    ///
    void setAlignment(QWidget *parent, Qt::Alignment alignment);
    ///
    /// \brief setPosition - Отрисовка виджета при изменении размера родителя
    ///
    void setPosition();
    ///
    /// \brief updateWidgetSize - Вычисление размера виджета
    ///
    void updateWidgetSize();
private:
    QList<QPair<QColor, QString>> legendItems; //!< Отображающийся список
    const int itemHeight = 20; //!< Ширина прямоугольника цвета
    const int itemWidth = 50; //!< Длина прямоугольника цвета
    const int padding = 5; //!< Размер отступа
    int starty = padding; //!< Координата Y начала отрисовки виджета
    int startX = padding; //!< Координата X начала отрисовки виджета
    int maxHeight = 0; //!< Максимальная длина виджета
    int maxWidth = 0; //!< Максимальная ширина виджета
    Qt::Alignment m_alignment; //!< Положение виджета относительно родителя
    QWidget *m_parent; //!< Виджет родителя

protected:
    void paintEvent(QPaintEvent *event);


};

#endif // LEGEND_H
