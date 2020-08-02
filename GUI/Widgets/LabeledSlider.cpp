#include <iostream>

#include "LabeledSlider.h"

LabeledSlider::LabeledSlider(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
  
  //this->txtMin->setText(QString::number(this->horizontalSlider->mi