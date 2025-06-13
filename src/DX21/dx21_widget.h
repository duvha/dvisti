#ifndef DX21_WIDGET_H
#define DX21_WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class dx21_widget;
}
QT_END_NAMESPACE

class dx21_widget : public QWidget
{
    Q_OBJECT

public:
    dx21_widget(QWidget *parent = nullptr);
    ~dx21_widget();

private:
    Ui::dx21_widget *ui;

private slots:
    void spinBox_frequency_1_valueChanged(int value);
    void spinBox_detune_1_valueChanged(int value);
    void spinBox_outputLevel_1_valueChanged(int value);
};
#endif // DX21_WIDGET_H
