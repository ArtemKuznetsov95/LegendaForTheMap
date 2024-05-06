# LegendaForTheMap
1. Первый вариант создания легенды и добавления списка через функцию
   ```c
    legendWidget = new Legend(this);  
    legendWidget->setLegendItems(listLegend);
   ```
3. Второй вариант создания легенды через конструктор  
    ```c
    legendWidget = new Legend(listLegend, this);  
    legendWidget->setAlignment(this, Qt::AlignBottom | Qt::AlignRight);    
    ```
5. Изменение положения легенды при изменении размера виджета родителя  
    Переопределить метод родителя **resizeEvent(QResizeEvent \*event)**
    ```c
    {
    ...
    QWidget::resizeEvent(event);  
        if (legendWidget) {  
            legendWidget->setPosition();  
        }
    ...
    }
    ```
