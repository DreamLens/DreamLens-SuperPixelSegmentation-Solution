#include <iostream>

#include "LabeledSlider.h"

LabeledSlider::LabeledSlider(QWidget *parent) : QWidget(parent)
{
  setupUi(this);
  
  //this->txtMin->setText(QString::number(this->horizontalSlider->minimum()));
  //this->txtMax->setText(QString::number(this->horizontalSlider->maximum()));

  this->horizontalSlider->setMinimum(this->txtMin->text().toInt());
  this->horizontalSlider->setMaximum(this->txtMax->text().toInt());

  this->lblCurrent->setText(QString::number(this->horizontalSlider->value()));

  this->Validator = new QIntValidator(0, 10000, this);
  this->txtMin->setValidator(this->Validator);
  this->txtMax->setValidator(this->Validat