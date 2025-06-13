#include "dx21_widget.h"
#include "ui_dx21_widget.h"

dx21_widget::dx21_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dx21_widget)
{
    ui->setupUi(this);
    connect(ui->spinBox_frequency_1, SIGNAL(valueChanged(int)), this, SLOT(spinBox_frequency_1_valueChanged(int)));
    connect(ui->spinBox_detune_1, SIGNAL(valueChanged(int)), this, SLOT(spinBox_detune_valueChanged(int)));
    connect(ui->spinBox_outputLevel_1, SIGNAL(valueChanged(int)), this, SLOT(spinBox_outputLevel_1_valueChanged(int)));
}

void dx21_widget::spinBox_frequency_1_valueChanged(int value)
{
    //ui->spinBox1->setValue(value);
}

void dx21_widget::spinBox_detune_1_valueChanged(int value)
{
    //ui->spinBox2->setValue(value);
}

void dx21_widget::spinBox_outputLevel_1_valueChanged(int value)
{
    //ui->spinBox3->setValue(value);
}


dx21_widget::~dx21_widget()
{
    delete ui;
}
